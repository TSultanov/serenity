#!/usr/bin/env -S bash ../.port_include.sh
port='harfbuzz'
version='4.3.0'
files="https://github.com/harfbuzz/harfbuzz/releases/download/${version}/harfbuzz-${version}.tar.xz harfbuzz-${version}.tar.xz a49628f4c4c8e6d8df95ef44935a93446cf2e46366915b0e3ca30df21fffb530"
useconfigure='true'
auth_type='sha256'
depends=("freetype" "libicu")
configopts=("--cross-file" "cross_file.txt" "-Dcairo=disabled" "-Dtests=disabled" "-Ddocs=disabled")

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