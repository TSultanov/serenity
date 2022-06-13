#!/usr/bin/env -S bash ../.port_include.sh
port=pango
version=1.50.7
useconfigure="true"
use_fresh_config_sub="false"
files="https://download.gnome.org/sources/pango/1.50/pango-${version}.tar.xz pango-${version}.tar.xz"
configopts=("--cross-file" "cross_file.txt" "-Dgtk_doc=false")
depends=("cairo" "freetype" "glib" "harfbuzz" "fribidi")

pre_configure() {
    run cp "../cross_file-${SERENITY_ARCH}${SERENITY_TOOLCHAIN}.txt" "cross_file.txt"
    run sed "s%SERENITY_BUILD_DIR%${SERENITY_BUILD_DIR}%g" -i "cross_file.txt"
}

configure() {
    run meson _build "${configopts[@]}"
}

build() {
    run ninja -C _build
}

install() {
    export DESTDIR="${SERENITY_INSTALL_ROOT}"
    run meson install -C _build
}
