#!/usr/bin/env -S bash ../.port_include.sh
port=cairo
version=1.17.4
useconfigure="true"
config_sub_paths=("build/config.sub")
use_fresh_config_sub="true"
files="https://cairographics.org/snapshots/cairo-${version}.tar.xz cairo-${version}.tar.xz"
configopts=("--cross-file" "cross_file.txt" "-Dxlib=enabled")
depends=("libpng" "pixman" "fontconfig" "glib" "libexpat")

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
