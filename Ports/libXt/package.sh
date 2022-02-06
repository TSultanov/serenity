#!/usr/bin/env -S bash ../.port_include.sh

port="libXt"
version="1.2.1"
workdir=libxt-libXt-1.2.1
useconfigure="true"
files="https://gitlab.freedesktop.org/xorg/lib/libxt/-/archive/libXt-1.2.1/libxt-libXt-1.2.1.tar.bz2 libxt-libXt-1.2.1.tar.bz2"
depends=("libSM")
configopts=("--prefix=/usr/local")

pre_configure() {
    run sed -i 's@XORG_CHECK_MALLOC_ZERO@# XORG_CHECK_MALLOC_ZERO@' configure.ac
    NOCONFIGURE=1 run ./autogen.sh
    run sed -i 's@irix\* \\@irix* | *serenity* \\@' config.sub
}
