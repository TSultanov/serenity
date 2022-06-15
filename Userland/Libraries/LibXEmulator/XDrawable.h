#pragma once

#include "LibGUI/Painter.h"

class XDrawable : public Core::Object {
    C_OBJECT_ABSTRACT(XDrawable)
public:
    virtual GUI::Painter& painter() = 0;
    virtual ~XDrawable() = default;
};