set(SOURCES
        Display.cpp
        Color.cpp
        ObjectManager.cpp
        Window.cpp
        XWindow.cpp
        GC.cpp
        Font.cpp
        Event.cpp
        Drawing.cpp
        XPixmap.cpp
        Image.cpp
        Stubs.cpp
        Pixmap.cpp
        Macros.cpp
        Extension.cpp
        Atom.cpp
        Property.cpp
        Keyboard.cpp
        Resource.cpp
        xorg/Context.c
        xorg/Depths.c
        xorg/Geom.c
        xorg/ParseCmd.c
        xorg/ParseGeom.c
        xorg/RdBitF.c
        xorg/reallocarray.c
        xorg/ScrResStr.c
        xorg/StrToText.c
        xorg/TextToStr.c
        xorg/WMGeom.c
        xorg/Xrm.c)

serenity_lib(LibX11 X11)
target_include_directories(LibX11 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(LibGUI LibGfx LibCore LibC)
serenity_install_headers(.)
