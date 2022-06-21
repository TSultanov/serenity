#!/usr/bin/env -S bash ../.port_include.sh
port=azpainter
version=2.1.6
useconfigure="true"
config_sub_paths=("build-aux/config.sub")
use_fresh_config_sub="false"
files="https://github.com/Symbian9/azpainter/releases/download/v${version}/azpainter-2.1.6.tar.xz azpainter-${version}.tar.xz"
configopts=("")
depends=("freetype" "fontconfig" "libpng" "libjpeg" "zlib")
