#!/usr/bin/env -S bash ../.port_include.sh
port=fribidi
version=1.0.12
useconfigure="true"
use_fresh_config_sub="true"
files="https://github.com/fribidi/fribidi/releases/download/v${version}/fribidi-${version}.tar.xz fribidy-${version}.tar.xz"
configopts=("")

export CFLAGS="--std=gnu89"
