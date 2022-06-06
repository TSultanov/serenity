set(SOURCES
        Display.cpp
        Color.cpp
        ObjectManager.cpp
        Window.cpp
        XWindow.cpp)

serenity_lib(LibX11 X11)
target_link_libraries(LibGUI LibGfx)
serenity_install_headers(.)
