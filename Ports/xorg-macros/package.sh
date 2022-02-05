#!/usr/bin/env -S bash ../.port_include.sh

port="xorg-macros"
version="1.19.3"
workdir=macros-util-macros-1.19.3
useconfigure="true"
files="https://gitlab.freedesktop.org/xorg/util/macros/-/archive/util-macros-1.19.3/macros-util-macros-1.19.3.tar.bz2 macros-util-macros-1.19.3.tar.bz2"
depends=()
configopts=("--prefix=/usr/local")

pre_configure() {
    NOCONFIGURE=1 run ./autogen.sh
}