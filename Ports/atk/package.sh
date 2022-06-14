#!/usr/bin/env -S bash ../.port_include.sh
port=atk
version=2.38.0
useconfigure="true"
use_fresh_config_sub="false"
files="https://download.gnome.org/sources/atk/2.38/atk-${version}.tar.xz atk-${version}.tar.xz"
configopts=("--cross-file" "cross_file.txt" "-Dintrospection=false")

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
