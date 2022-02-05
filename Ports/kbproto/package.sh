#!/usr/bin/env -S bash ../.port_include.sh

port="kbproto"
version="1.0.7"
workdir=xorg-kbproto-kbproto-1.0.7
useconfigure="true"
files="https://github.com/freedesktop/xorg-kbproto/archive/refs/tags/kbproto-1.0.7.tar.gz kbproto-1.0.7.tar.gz"
depends=()
configopts=("--prefix=/usr/local")

pre_configure() {
    NOCONFIGURE=1 run ./autogen.sh
    run sed -i 's@irix\* \\@irix* | *serenity* \\@' config.sub
}
