#!/usr/bin/env -S bash ../.port_include.sh
port=cairo
version=1.17.4
useconfigure="true"
config_sub_paths=("build/config.sub")
use_fresh_config_sub="true"
files="https://cairographics.org/snapshots/cairo-${version}.tar.xz cairo-${version}.tar.xz"
configopts=("")
depends=("libpng" "pixman")
