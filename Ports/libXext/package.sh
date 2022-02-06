#!/usr/bin/env -S bash ../.port_include.sh

port="libXext"
version="1.3.4"
workdir=libxext-libXext-1.3.4
useconfigure="true"
files="https://gitlab.freedesktop.org/xorg/lib/libxext/-/archive/libXext-1.3.4/libxext-libXext-1.3.4.tar.bz2 libxext-libXext-1.3.4.tar.bz2"
depends=()
configopts=("--prefix=/usr/local")

pre_configure() {
    NOCONFIGURE=1 run ./autogen.sh
    run sed -i 's@irix\* \\@irix* | *serenity* \\@' config.sub
}
