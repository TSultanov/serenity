#!/usr/bin/env -S bash ../.port_include.sh

port="inputproto"
version="2.3.2"
workdir=xorg-inputproto-inputproto-2.3.2
useconfigure="true"
files="https://github.com/freedesktop/xorg-inputproto/archive/refs/tags/inputproto-2.3.2.tar.gz inputproto-2.3.2.tar.gz"
depends=()
configopts=("--prefix=/usr/local")

pre_configure() {
    NOCONFIGURE=1 run ./autogen.sh
    run sed -i 's@irix\* \\@irix* | *serenity* \\@' config.sub
}
