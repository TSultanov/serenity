#!/usr/bin/env -S bash ../.port_include.sh

port="renderproto"
version="0.11.1"
workdir=renderproto-renderproto-0.11.1
useconfigure="true"
files="https://gitlab.freedesktop.org/xorg/proto/renderproto/-/archive/renderproto-0.11.1/renderproto-renderproto-0.11.1.tar.bz2 renderproto-renderproto-0.11.1.tar.bz2"
depends=()
configopts=("--prefix=/usr/local")

pre_configure() {
    # run sed -i 's@XORG_CHECK_MALLOC_ZERO@# XORG_CHECK_MALLOC_ZERO@' configure.ac
    run autoreconf
    run sed -i 's@irix\* \\@irix* | *serenity* \\@' config.sub
}
