#undef None
#include <LibGUI/Application.h>
#include "ObjectManager.h"
#include <LibGfx/Rect.h>
#include <LibGfx/DisjointRectSet.h>

namespace XLib {
extern "C" {
#include <X11/Xlib.h>
#include <X11/Xlibint.h>
#include <X11/Xutil.h>
}
}

struct ClipMask {
    Gfx::DisjointRectSet region;
};

extern "C" XLib::GC
XLib::XCreateGC(XLib::Display* display, XLib::Window /*window*/,
    unsigned long mask, XGCValues* gc_values)
{
    XLib::GC gc = new XLib::_XGC;
    gc->values.function = GXcopy;
    gc->values.foreground = BlackPixel(display, 0);
    gc->values.background = WhitePixel(display, 0);
    gc->values.line_style = LineSolid;
    gc->values.line_width = 0;
    gc->values.cap_style = CapButt;
    gc->values.join_style = JoinMiter;
    gc->values.fill_style = FillSolid;
    gc->values.fill_rule = EvenOddRule;
    gc->values.arc_mode = ArcChord;
    gc->values.font = 0;
    gc->values.subwindow_mode = ClipByChildren;
    gc->values.clip_x_origin = gc->values.clip_y_origin = 0;
    gc->values.clip_mask = None;
    gc->dirty = True;
    XChangeGC(display, gc, mask, gc_values);
    return gc;
}

extern "C" int
XLib::XChangeGC(XLib::Display *display, XLib::GC gc, unsigned long mask, XGCValues *values)
{
    if (mask & GCFunction)
        gc->values.function = values->function;
    if (mask & GCPlaneMask)
        gc->values.plane_mask = values->plane_mask;
    if (mask & GCForeground)
        gc->values.foreground = values->foreground;
    if (mask & GCBackground)
        gc->values.background = values->background;
    if (mask & GCLineWidth)
        gc->values.line_width = values->line_width;
    if (mask & GCLineStyle)
        gc->values.line_style = values->line_style;
    if (mask & GCCapStyle)
        gc->values.cap_style = values->cap_style;
    if (mask & GCJoinStyle)
        gc->values.join_style = values->join_style;
    if (mask & GCFillStyle)
        gc->values.fill_style = values->fill_style;
    if (mask & GCFillRule)
        gc->values.fill_rule = values->fill_rule;
    if (mask & GCArcMode)
        gc->values.arc_mode = values->arc_mode;
    if (mask & GCTile)
        gc->values.tile = values->tile;
    if (mask & GCStipple)
        gc->values.stipple = values->stipple;
    if (mask & GCTileStipXOrigin)
        gc->values.ts_x_origin = values->ts_x_origin;
    if (mask & GCTileStipYOrigin)
        gc->values.ts_y_origin = values->ts_y_origin;
    if (mask & GCFont)
        gc->values.font = values->font;
    if (mask & GCSubwindowMode)
        gc->values.subwindow_mode = values->subwindow_mode;
    if (mask & GCGraphicsExposures)
        gc->values.graphics_exposures = values->graphics_exposures;
    if (mask & GCClipXOrigin)
        gc->values.clip_x_origin = values->clip_x_origin;
    if (mask & GCClipYOrigin)
        gc->values.clip_y_origin = values->clip_y_origin;
    if (mask & GCClipMask) {
        // Presume this is a real pixmap, as we don't control GCValues.
        XSetClipMask(display, gc, values->clip_mask);
    }
    if (mask & GCDashOffset)
        gc->values.dash_offset = values->dash_offset;
#if 0
	// TODO
	if (mask & GCDashList)
		XSetDashes(display, gc, &values->dashes, 2);
#endif
    gc->dirty = True;
    return 0;
}

extern "C" int
XLib::XSetForeground(Display */*display*/, GC gc, unsigned long color)
{
    gc->values.foreground = color;
    gc->dirty = True;
    return 0;
}

extern "C" int
XLib::XSetFont(XLib::Display */*display*/, XLib::GC gc, XLib::Font font)
{
    gc->values.font = font;
    gc->dirty = True;
    return 0;
}

static inline ClipMask*
gc_clip_mask(XLib::GC gc, bool allocate = true)
{
    ClipMask* mask = (ClipMask*)gc->values.clip_mask;
    if (!mask && allocate) {
        mask = new ClipMask;
        gc->values.clip_mask = (XLib::Pixmap)mask;
    }
    return mask;
}

extern "C" Status
XLib::XSetClipMask(Display* /*display*/, GC gc, Pixmap pixmap)
{
    auto pxm = ObjectManager::the().get_pixmap(pixmap);
    if (pxm.is_null())
        return BadPixmap;

    ClipMask* mask = gc_clip_mask(gc);
    mask->region.clear();
    mask->region.add(pxm->bitmap()->rect());

    // TODO: Actually use the pixmap for clipping!
    dbgln("XSetClipMask unimplmeted");

    gc->dirty = True;
    return Success;
}
