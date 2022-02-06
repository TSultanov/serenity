#!/usr/bin/env -S bash ../.port_include.sh

port="libXrandr"
version="1.5.2"
workdir=libxrandr-libXrandr-1.5.2
useconfigure="true"
files="https://gitlab.freedesktop.org/xorg/lib/libxrandr/-/archive/libXrandr-1.5.2/libxrandr-libXrandr-1.5.2.tar.bz2 libxrandr-libXrandr-1.5.2.tar.bz2"
depends=("randrproto" "libXext" "libXrender" "renderproto")
configopts=("--prefix=/usr/local")

pre_configure() {
    NOCONFIGURE=1 run ./autogen.sh
    run sed -i 's@irix\* \\@irix* | *serenity* \\@' config.sub
}
