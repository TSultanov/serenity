#!/usr/bin/env -S bash ../.port_include.sh
port=libepoxy
version=1.5.10
useconfigure="true"
config_sub_paths=("build-aux/config.sub")
use_fresh_config_sub="false"
files="https://github.com/anholt/libepoxy/archive/refs/tags/${version}.tar.gz v${version}.tar.xz"
configopts=("--cross-file" "cross_file.txt" "-Degl=no" "-Dtests=false")
depends=()

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
