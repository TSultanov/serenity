#!/usr/bin/env -S bash ../.port_include.sh

port="libXrender"
version="0.9.10"
workdir=libxrender-libXrender-0.9.10
useconfigure="true"
files="https://gitlab.freedesktop.org/xorg/lib/libxrender/-/archive/libXrender-0.9.10/libxrender-libXrender-0.9.10.tar.bz2 libxrender-libXrender-0.9.10.tar.bz2"
depends=("renderproto")
configopts=("--prefix=/usr/local")

pre_configure() {
    run sed -i 's@XORG_CHECK_MALLOC_ZERO@# XORG_CHECK_MALLOC_ZERO@' configure.ac
    NOCONFIGURE=1 run ./autogen.sh
    run sed -i 's@irix\* \\@irix* | *serenity* \\@' config.sub
}
