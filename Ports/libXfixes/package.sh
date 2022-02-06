#!/usr/bin/env -S bash ../.port_include.sh

port="libXfixes"
version="6.0.0"
workdir=libxfixes-libXfixes-6.0.0
useconfigure="true"
files="https://gitlab.freedesktop.org/xorg/lib/libxfixes/-/archive/libXfixes-6.0.0/libxfixes-libXfixes-6.0.0.tar.bz2 libxfixes-libXfixes-6.0.0.tar.bz2"
depends=("xorgproto")
configopts=("--prefix=/usr/local")

pre_configure() {
    run sed -i 's@XORG_CHECK_MALLOC_ZERO@# XORG_CHECK_MALLOC_ZERO@' configure.ac
    NOCONFIGURE=1 run ./autogen.sh
    run sed -i 's@irix\* \\@irix* | *serenity* \\@' config.sub
}
