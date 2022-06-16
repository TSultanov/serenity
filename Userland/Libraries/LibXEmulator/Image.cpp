#include "ObjectManager.h"
#include "Drawing.h"
#include <LibGfx/Bitmap.h>

namespace XLib {
extern "C" {
#include <X11/Xlib.h>
}
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