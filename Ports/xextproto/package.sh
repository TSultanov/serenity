#!/usr/bin/env -S bash ../.port_include.sh

port="xextproto"
version="7.3.0"
workdir=xorg-xextproto-xextproto-7.3.0
useconfigure="true"
files="https://github.com/freedesktop/xorg-xextproto/archive/refs/tags/xextproto-7.3.0.tar.gz xextproto-7.3.0.tar.gz"
depends=()
configopts=("--prefix=/usr/local")

pre_configure() {
    NOCONFIGURE=1 run ./autogen.sh
    run sed -i 's@irix\* \\@irix* | *serenity* \\@' config.sub
}

# bash configure --openjdk-target=${SERENITY_ARCH}-pc-serenity --without-x