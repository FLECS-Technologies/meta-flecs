DESCRIPTION = "A Fast and Easy to use microframework for the web. "
LICENSE = "BSD-3-Clause"

DEPENDS = "boost"

SRC_URI = "git://github.com/CrowCpp/Crow.git;protocol=https;nobranch=1"

SRCREV = "edf12f699ec3bf6f751cf73cb97f32919e48ca6e"

LIC_FILES_CHKSUM = "file://LICENSE;md5=50b5835246dde78e0929b8b9cdcd2f95"

S = "${WORKDIR}/git"

inherit cmake

EXTRA_OECMAKE = "-DCROW_BUILD_TESTS=NO"
