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
        Extension.cpp)

serenity_lib(LibX11 X11)
target_include_directories(LibX11 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(LibGUI LibGfx LibCore LibC)
serenity_install_headers(.)
