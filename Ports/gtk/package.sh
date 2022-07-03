#!/usr/bin/env -S bash ../.port_include.sh
port=gtk+
version=3.24.30
useconfigure="true"
config_sub_paths=("build-aux/config.sub")
use_fresh_config_sub="true"
files="https://download.gnome.org/sources/gtk+/3.24/gtk%2B-${version}.tar.xz gtk+-${version}.tar.xz"
configopts=("--with-sysroot=${SERENITY_INSTALL_ROOT}")
depends=("cairo" "fontconfig" "atk" "pango" "gdk-pixbuf" "libepoxy" "fribidi")

export LDFLAGS="-lcore -lgui -lgfx"