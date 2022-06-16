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
        Image.cpp)

serenity_lib(LibX11 X11)
target_link_libraries(LibGUI LibGfx LibCore)
serenity_install_headers(.)
