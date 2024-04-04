DESCRIPTION = "A YAML parser and emitter in C++"
LICENSE = "MIT"

SRC_URI = "https://github.com/jbeder/yaml-cpp/archive/refs/tags/0.8.0.tar.gz"
SRC_URI[sha256sum] = "fbe74bbdcee21d656715688706da3c8becfd946d92cd44705cc6098bb23b3a16"

LIC_FILES_CHKSUM = "file://LICENSE;md5=6a8aaf0595c2efc1a9c2e0913e9c1a2c"

inherit cmake

EXTRA_OECMAKE = "-DYAML_BUILD_SHARED_LIBS=YES -DYAML_CPP_BUILD_TESTS=NO"
