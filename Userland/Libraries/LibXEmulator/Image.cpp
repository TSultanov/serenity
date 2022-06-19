#include "ObjectManager.h"
#include "Drawing.h"
#include <LibGfx/Bitmap.h>

namespace XLib {
extern "C" {
#include <X11/Xlib.h>
}
}

static int
DestroyImage(XLib::XImage* image)
{
    free(image->data);
    delete image;
    return Success;
}

static inline uint8_t*
GetImageDataPointer(XLib::XImage* image, int x, int y)
{
    return (uint8_t*)&(image->data[
        (y * image->bytes_per_line) + ((x * image->bitmap_unit) / CHAR_BIT)]);
}

static unsigned long
ImageGetPixel(XLib::XImage* image, int x, int y)
{
    unsigned long pixel = 0;
    uint8_t* srcPtr = GetImageDataPointer(image, x, y);

    switch (image->bits_per_pixel) {
    case 1:
        pixel = ((*srcPtr) & (0x80 >> (x % 8))) ? 1 : 0;
        break;
    case 8:
        pixel = *srcPtr;
        break;
    case 15:
    case 16:
        pixel = srcPtr[0] | (srcPtr[1] << 8);
        break;
    case 24:
        pixel = srcPtr[0] | (srcPtr[1] << 8) | (srcPtr[2] << 16);
        break;
    case 32:
        pixel = srcPtr[0] | (srcPtr[1] << 8) | (srcPtr[2] << 16) | (srcPtr[3] << 24);
        break;
    }
    return pixel;
}

static int
ImagePutPixel(XLib::XImage* image, int x, int y, unsigned long pixel)
{
    uint8_t* destPtr = GetImageDataPointer(image, x, y);
    uint8_t* srcPtr = (uint8_t*)&pixel;
    switch (image->bits_per_pixel) {
    case 1: {
        int mask = (0x80 >> (x % 8));
        if (pixel) {
            (*destPtr) |= mask;
        } else {
            (*destPtr) &= ~mask;
        }
        break;
    }
    case 8:
        *destPtr = pixel;
        break;
    case 15:
    case 16:
        destPtr[0] = srcPtr[0];
        destPtr[1] = srcPtr[1];
        break;
    case 24: {
        destPtr[0] = srcPtr[0];
        destPtr[1] = srcPtr[1];
        destPtr[2] = srcPtr[2];
        break;
    }
    case 32:
        destPtr[0] = srcPtr[0];
        destPtr[1] = srcPtr[1];
        destPtr[2] = srcPtr[2];
        destPtr[3] = srcPtr[3];
        break;
    }
    return 0;
}


extern "C" Status
XLib::XInitImage(XImage* image)
{
    if (image->bytes_per_line == 0) {
        image->bytes_per_line = image->width * (image->bitmap_unit / 8);

		const int align = image->bitmap_pad / 8;
        if (align)
            image->bytes_per_line = ((image->bytes_per_line + align - 1) / align) * align;
    }

    memset(&image->f, 0, sizeof(image->f));
    image->f.destroy_image = DestroyImage;
    image->f.get_pixel = ImageGetPixel;
    image->f.put_pixel = ImagePutPixel;

    return 1;
}


extern "C" XLib::XImage*
XLib::XGetSubImage(Display* /*display*/, Drawable d,
    int x, int y, unsigned int width, unsigned int height,
    unsigned long /*plane_mask*/, int format,
    XImage* dest_image, int dest_x, int dest_y)
{
    auto pixmap = ObjectManager::the().get_pixmap(d);
    if (pixmap.is_null())
        return NULL;

    if (format != ZPixmap)
        return NULL;

    auto cropped = MUST(pixmap->bitmap()->cropped(Gfx::IntRect (x, y, width, height)));

    // TODO: plane_mask?

    if (!dest_image->data)
        dest_image->data = (char*)malloc(dest_image->bytes_per_line * dest_image->height);

    auto dest_bitmap = MUST(Gfx::Bitmap::try_create(Gfx::BitmapFormat::BGRA8888, Gfx::IntSize(width, height)));

    Gfx::Painter painter(dest_bitmap);
    painter.draw_tiled_bitmap(Gfx::IntRect(dest_x, dest_y, width, height), cropped);

    memcpy(dest_image->data, dest_bitmap->anonymous_buffer().data<char>(), dest_image->height * dest_image->bytes_per_line);
    return dest_image;
}