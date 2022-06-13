#!/usr/bin/env -S bash ../.port_include.sh
port='pixman'
version='0.40.0'
useconfigure='true'
files="https://www.cairographics.org/releases/pixman-${version}.tar.gz pixman-${version}.tar.gz 6d200dec3740d9ec4ec8d1180e25779c00bc749f94278c8b9021f5534db223fc"
auth_type='sha256'
configopts=("--cross-file" "${SERENITY_BUILD_DIR}/meson-cross-file.txt")

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
