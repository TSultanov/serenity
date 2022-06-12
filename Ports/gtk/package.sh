#!/usr/bin/env -S bash ../.port_include.sh
port=gtk
version=3.24.34
useconfigure="true"
config_sub_paths=("config.sub")
use_fresh_config_sub="true"
files="https://download.gnome.org/sources/gtk+/3.24/gtk%2B-${version}.tar.xz gtk+-${version}.tar.xz"
configopts=("")
depends=("cairo" "fontconfig")
