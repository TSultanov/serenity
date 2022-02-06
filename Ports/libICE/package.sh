#!/usr/bin/env -S bash ../.port_include.sh

port="libICE"
version="1.0.10"
workdir=libice-libICE-1.0.10
useconfigure="true"
files="https://gitlab.freedesktop.org/xorg/lib/libice/-/archive/libICE-1.0.10/libice-libICE-1.0.10.tar.bz2 libice-libICE-1.0.10.tar.bz2"
depends=()
configopts=("--prefix=/usr/local")

pre_configure() {
    run sed -i 's@XORG_CHECK_MALLOC_ZERO@# XORG_CHECK_MALLOC_ZERO@' configure.ac
    NOCONFIGURE=1 run ./autogen.sh
    run sed -i 's@irix\* \\@irix* | *serenity* \\@' config.sub
}
