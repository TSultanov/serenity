#!/usr/bin/env -S bash ../.port_include.sh

port="xorgproto"
version="2022.2"
useconfigure="true"
use_fresh_config_sub=true
files="https://www.x.org/releases/individual/proto/xorgproto-${version}.tar.xz xorgproto-${version}.tar.xz"
depends=()
