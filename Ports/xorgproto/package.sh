#!/usr/bin/env -S bash ../.port_include.sh

port="xorgproto"
version="2021.5"
workdir=xorgproto-xorgproto-2021.5
useconfigure="true"
files="https://gitlab.freedesktop.org/xorg/proto/xorgproto/-/archive/xorgproto-2021.5/xorgproto-xorgproto-2021.5.tar.bz2 xorgproto-xorgproto-2021.5.tar.bz2"
depends=()
configopts=("--prefix=/usr/local")

pre_configure() {
    # run sed -i 's@XORG_CHECK_MALLOC_ZERO@# XORG_CHECK_MALLOC_ZERO@' configure.ac
    NOCONFIGURE=1 run ./autogen.sh
    run sed -i 's@irix\* \\@irix* | *serenity* \\@' config.sub
}
