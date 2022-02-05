#!/usr/bin/env -S bash ../.port_include.sh

port="libXau"
version="1.0.9"
workdir=libxau-libXau-1.0.9
useconfigure="true"
files="https://gitlab.freedesktop.org/xorg/lib/libxau/-/archive/libXau-1.0.9/libxau-libXau-1.0.9.tar.bz2 libxau-libXau-1.0.9.tar.bz2"
depends=("xproto")
configopts=("--prefix=/usr/local")

pre_configure() {
    NOCONFIGURE=1 run ./autogen.sh
    run sed -i 's@irix\* \\@irix* | *serenity* \\@' config.sub
}
