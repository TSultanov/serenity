#!/usr/bin/env -S bash ../.port_include.sh

port="recordproto"
version="1.14.2"
workdir=recordproto-recordproto-1.14.2
useconfigure="true"
files="https://gitlab.freedesktop.org/xorg/proto/recordproto/-/archive/recordproto-1.14.2/recordproto-recordproto-1.14.2.tar.bz2 recordproto-recordproto-1.14.2.tar.bz2"
depends=()
configopts=("--prefix=/usr/local")

pre_configure() {
    run autoreconf
    run sed -i 's@irix\* \\@irix* | *serenity* \\@' config.sub
}
