#!/usr/bin/env -S bash ../.port_include.sh

port="pthread-stubs"
version="0.4"
workdir=pthread-stubs-0.4
useconfigure="true"
files="https://gitlab.freedesktop.org/xorg/lib/pthread-stubs/-/archive/0.4/pthread-stubs-0.4.tar.bz2 pthread-stubs-0.4.tar.bz2"
depends=()
configopts=("--prefix=/usr/local")

pre_configure() {
    NOCONFIGURE=1 run ./autogen.sh
}
