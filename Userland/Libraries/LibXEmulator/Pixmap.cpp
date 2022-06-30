#include "XPixmap.h"
#include "ObjectManager.h"
#include <LibGfx/ImageDecoder.h>

namespace XLib {
extern "C" {
#include <X11/Xlib.h>
}
}

extern "C" XLib::Pixmap
XLib::XCreatePixmap(Display* display, Drawable /*d*/,
    unsigned int width, unsigned int height, unsigned int /*depth*/)
{
    Gfx::IntRect rect(0, 0, width, height);
    auto pixmap = MUST(XPixmap::try_create(display, rect));
    return pixmap->id();
}

extern "C" int
XLib::XFreePixmap(Display */*display*/, Pixmap pxm)
{
    auto pixmap = ObjectManager::the().get_pixmap(pxm);
    if (pixmap.is_null())
        return BadPixmap;
    ObjectManager::the().remove_pixmap(pxm);
    return Success;
}

extern "C" XLib::Pixmap
XLib::XCreateBitmapFromData(Display* display, Drawable /*d*/,
	const char* data, unsigned int width, unsigned int height)
{
    Gfx::IntRect rect(0, 0, width, height);
    auto pixmap = XPixmap::construct(display, rect);

    AK::Span<const u8> span(data, width * height);
    auto decoder = Gfx::ImageDecoder::try_create(span);
    auto frame = MUST(decoder->frame(0));
    auto bitmap = frame.image;

    pixmap->painter().draw_tiled_bitmap(rect, *bitmap);
    //pixmap ->ImportBits(data, width * height, (width+7)/8, 0, B_GRAY1);
    return pixmap->id();
}
