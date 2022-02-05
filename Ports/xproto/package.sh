#!/usr/bin/env -S bash ../.port_include.sh

port="xproto"
version="7.0.31"
workdir=xorg-proto-x11proto-xproto-7.0.31
useconfigure="true"
files="https://github.com/freedesktop/xorg-proto-x11proto/archive/refs/tags/xproto-7.0.31.tar.gz xproto-7.0.31.tar.gz"
depends=()
configopts=("--prefix=/usr/local")

pre_configure() {
    NOCONFIGURE=1 run ./autogen.sh
    run sed -i 's@irix\* \\@irix* | *serenity* \\@' config.sub
}
