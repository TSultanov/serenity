#!/usr/bin/env -S bash ../.port_include.sh

port="libXtst"
version="1.2.3"
workdir=libxtst-libXtst-1.2.3
useconfigure="true"
files="https://gitlab.freedesktop.org/xorg/lib/libxtst/-/archive/libXtst-1.2.3/libxtst-libXtst-1.2.3.tar.bz2 libxtst-libXtst-1.2.3.tar.bz2"
depends=("libXi" "recordproto")
configopts=("--prefix=/usr/local")

pre_configure() {
    NOCONFIGURE=1 run ./autogen.sh
    run sed -i 's@irix\* \\@irix* | *serenity* \\@' config.sub
}
