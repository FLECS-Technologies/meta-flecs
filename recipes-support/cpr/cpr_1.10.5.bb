DESCRIPTION = "C++ Requests: Curl for People"
LICENSE = "MIT"

DEPENDS = "curl"

SRC_URI = "https://github.com/libcpr/cpr/archive/refs/tags/1.10.5.tar.gz"
SRC_URI[sha256sum] = "c8590568996cea918d7cf7ec6845d954b9b95ab2c4980b365f582a665dea08d8"

LIC_FILES_CHKSUM = "file://LICENSE;md5=08beaae5deae1c43c065592da8f38095"

inherit cmake

EXTRA_OECMAKE = "-DCPR_BUILD_TESTS=NO -DCPR_USE_SYSTEM_CURL=YES"
