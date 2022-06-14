set(SOURCES
        shape-stubs.cpp
        stubs.cpp
        sync-macros.cpp
        sync-stubs.cpp
        XShm.cpp)

serenity_lib(LibXext Xext)
target_link_libraries(LibGUI LibGfx LibCore LibX11)
