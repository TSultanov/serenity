#!/usr/bin/env -S bash ../.port_include.sh

port="xcb-proto"
version="1.14.1"
workdir=xcbproto-xcb-proto-1.14.1
useconfigure="true"
files="https://gitlab.freedesktop.org/xorg/proto/xcbproto/-/archive/xcb-proto-1.14.1/xcbproto-xcb-proto-1.14.1.tar.bz2 xcbproto-xcb-proto-1.14.1.tar.bz2"
depends=("python3")
configopts=("--prefix=/usr/local")

pre_configure() {
    NOCONFIGURE=1 run ./autogen.sh
}

post_configure() {
    run sed -i 's@${PYTHON_PREFIX}@/usr/local@' xcb-proto.pc
}