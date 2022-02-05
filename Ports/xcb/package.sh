#!/usr/bin/env -S bash ../.port_include.sh

port="xcb"
version="1.14"
workdir=libxcb-libxcb-1.14
useconfigure="true"
files="https://gitlab.freedesktop.org/xorg/lib/libxcb/-/archive/libxcb-1.14/libxcb-libxcb-1.14.tar.bz2 libxcb-libxcb-1.14.tar.bz2"
depends=("xcb-proto" "python3" "xorg-macros" "libXau" "pthread-stubs")
configopts=("--prefix=/usr/local")

export PYTHON_PREFIX=/usr/local

pre_configure() {
    NOCONFIGURE=1 run ./autogen.sh
    run sed -i 's@irix\* \\@irix* | *serenity* \\@' build-aux/config.sub
}
