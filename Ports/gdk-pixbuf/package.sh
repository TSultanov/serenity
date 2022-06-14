#!/usr/bin/env -S bash ../.port_include.sh
port=gdk-pixbuf
version=2.42.6
useconfigure="true"
use_fresh_config_sub="false"
files="https://download.gnome.org/sources/gdk-pixbuf/2.42/gdk-pixbuf-${version}.tar.xz gdk-pixbuf-${version}.tar.xz"
configopts=("--cross-file" "cross_file.txt" "-Dgtk_doc=false")
depends=("cairo" "glib" "shared-mime-info")

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
