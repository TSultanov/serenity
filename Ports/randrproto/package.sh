#!/usr/bin/env -S bash ../.port_include.sh

port="randrproto"
version="1.5.0"
workdir=randrproto-randrproto-1.5.0
useconfigure="true"
files="https://gitlab.freedesktop.org/xorg/proto/randrproto/-/archive/randrproto-1.5.0/randrproto-randrproto-1.5.0.tar.bz2 randrproto-randrproto-1.5.0.tar.bz2"
depends=()
configopts=("--prefix=/usr/local")

pre_configure() {
    NOCONFIGURE=1 run ./autogen.sh
    run sed -i 's@irix\* \\@irix* | *serenity* \\@' config.sub
}
