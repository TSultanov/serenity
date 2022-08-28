#!/usr/bin/env -S bash ../.port_include.sh

port=xlibe
version=0.1.4
files="https://github.com/waddlesplash/xlibe/archive/refs/tags/${version}.tar.gz ${version}.tar.gz"
useconfigure=true
depends=("libiconv" "xorgproto")
configopts=("-DCMAKE_TOOLCHAIN_FILE=${SERENITY_BUILD_DIR}/CMakeToolchain.txt")

configure() {
    run cmake "${configopts[@]}"
}

install() {
    run make install
}
