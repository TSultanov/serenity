#!/usr/bin/env -S bash ../.port_include.sh

port="xtrans"
version="1.3.5"
workdir=xorg-lib-libxtrans-xtrans-1.3.5
useconfigure="true"
files="https://github.com/freedesktop/xorg-lib-libxtrans/archive/refs/tags/xtrans-1.3.5.tar.gz xtrans-1.3.5.tar.gz"
depends=()
configopts=("--prefix=/usr/local")

pre_configure() {
    NOCONFIGURE=1 run ./autogen.sh
    run sed -i 's@irix\* \\@irix* | *serenity* \\@' config.sub
}
