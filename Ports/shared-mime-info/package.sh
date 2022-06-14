#!/usr/bin/env -S bash ../.port_include.sh
port=shared-mime-info
version=2.2
useconfigure="true"
use_fresh_config_sub="false"
files="https://gitlab.freedesktop.org/xdg/shared-mime-info/-/archive/${version}/shared-mime-info-${version}.tar.gz shared-mime-info-${version}.tar.xz"
configopts=("--cross-file" "cross_file.txt")
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
