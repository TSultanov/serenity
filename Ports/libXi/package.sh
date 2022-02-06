#!/usr/bin/env -S bash ../.port_include.sh

port="libXi"
version="1.8"
workdir=libxi-libXi-1.8
useconfigure="true"
files="https://gitlab.freedesktop.org/xorg/lib/libxi/-/archive/libXi-1.8/libxi-libXi-1.8.tar.bz2 libxi-libXi-1.8.tar.bz2"
depends=("xorgproto" "libXfixes")
configopts=("--prefix=/usr/local")

pre_configure() {
    run sed -i 's@XORG_CHECK_MALLOC_ZERO@# XORG_CHECK_MALLOC_ZERO@' configure.ac
    NOCONFIGURE=1 run ./autogen.sh
    run sed -i 's@irix\* \\@irix* | *serenity* \\@' config.sub
}
