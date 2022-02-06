#!/usr/bin/env -S bash ../.port_include.sh

port="libSM"
version="1.2.3"
workdir=libsm-libSM-1.2.3
useconfigure="true"
files="https://gitlab.freedesktop.org/xorg/lib/libsm/-/archive/libSM-1.2.3/libsm-libSM-1.2.3.tar.bz2 libsm-libSM-1.2.3.tar.bz2"
depends=("libICE")
configopts=("--prefix=/usr/local")

pre_configure() {
    run sed -i 's@XORG_CHECK_MALLOC_ZERO@# XORG_CHECK_MALLOC_ZERO@' configure.ac
    NOCONFIGURE=1 run ./autogen.sh
    run sed -i 's@irix\* \\@irix* | *serenity* \\@' config.sub
}
