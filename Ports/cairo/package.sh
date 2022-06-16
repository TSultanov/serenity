#!/usr/bin/env -S bash ../.port_include.sh
port=cairo
version=1.11.4
useconfigure="true"
config_sub_paths=("build/config.sub")
use_fresh_config_sub="true"
files="https://cairographics.org/snapshots/cairo-${version}.tar.gz cairo-${version}.tar.gz"
configopts=("--with-sysroot=${SERENITY_INSTALL_ROOT}")
depends=("libpng" "pixman" "fontconfig" "glib" "libexpat")
