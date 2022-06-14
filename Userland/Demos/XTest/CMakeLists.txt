serenity_component(
        XTest
        TARGETS XTest
)

set(SOURCES xhello.c)

serenity_app(XTest ICON filetype-executable)
target_link_libraries(XTest LibX11 LibXext LibCore LibGUI LibGfx)