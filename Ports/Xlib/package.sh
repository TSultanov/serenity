#!/usr/bin/env -S bash ../.port_include.sh

port="Xlib"
version="1.7.3.1"
workdir=libx11-libX11-1.7.3.1
useconfigure="true"
files="https://gitlab.freedesktop.org/xorg/lib/libx11/-/archive/libX11-1.7.3.1/libx11-libX11-1.7.3.1.tar.bz2 libx11-libX11-1.7.3.1.tar.bz2"
depends=("xproto" "xextproto" "xtrans" "kbproto" "inputproto" "xcb")
configopts=("--prefix=/usr/local" "--with-keysymdefdir=${SERENITY_INSTALL_ROOT}/usr/local/include/X11")

export ACLOCAL="aclocal -I ${SERENITY_INSTALL_ROOT}/usr/local/share/aclocal"

pre_configure() {
    NOCONFIGURE=1 run ./autogen.sh
    run sed -i 's@irix\* \\@irix* | *serenity* \\@' config.sub
}
