#!/usr/bin/env -S USECCACHE=false bash ../.port_include.sh

port="OpenJDK"
version="17.0.2"
workdir=jdk17u-dev-jdk-17.0.2-ga
useconfigure="true"
files="https://github.com/openjdk/jdk17u-dev/archive/refs/tags/jdk-17.0.2-ga.tar.gz jdk-17.0.2-ga.tar.gz"
depends=("fontconfig" "libffi")

configure() {
    run bash configure --host=${SERENITY_ARCH}-pc-serenity --target=${SERENITY_ARCH}-pc-serenity --build=x86_64-unknown-linux-gnu --with-jvm-variants=zero --enable-headless-only --with-debug-level=fastdebug --with-native-debug-symbols=internal
}

build() {
    run make java.base
}

install() {
    run pwd
    run sh -c "cp ./build/serenity-* ${SERENITY_INSTALL_ROOT}/usr/Ports/ -rf"
}
