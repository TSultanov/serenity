#!/usr/bin/env -S bash ../.port_include.sh
port=cairo
version=1.12.2
useconfigure="true"
config_sub_paths=("build/config.sub")
use_fresh_config_sub="true"
files="https://www.cairographics.org/releases/cairo-${version}.tar.xz cairo-${version}.tar.xz"
configopts=("--with-sysroot=${SERENITY_INSTALL_ROOT}" "--enable-xlib")
depends=("libpng" "pixman" "fontconfig" "glib" "libexpat")
