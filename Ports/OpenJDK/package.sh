#!/usr/bin/env -S bash ../.port_include.sh

port="OpenJDK"
version="17"
workdir=jdk-jdk-17-ga
useconfigure="true"
files="https://github.com/openjdk/jdk/archive/refs/tags/jdk-17-ga.tar.gz jdk-17-ga.tar.gz"
depends=()

# bash configure --host=x86_64-unknown-linux-gnu --target=${SERENITY_ARCH}-pc-serenity --build=x86_64-unknown-linux-gnu