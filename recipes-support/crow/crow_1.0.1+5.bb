DESCRIPTION = "A Fast and Easy to use microframework for the web."
LICENSE = "BSD-3-Clause"

DEPENDS = "boost"

SRC_URI = "git://github.com/FLECS-Technologies/Crow.git;protocol=https;nobranch=1"

SRCREV = "b60d7d2eff20f581416ddf104176fe6fe4d3599b"

LIC_FILES_CHKSUM = "file://LICENSE;md5=50b5835246dde78e0929b8b9cdcd2f95"

S = "${WORKDIR}/git"

inherit cmake

EXTRA_OECMAKE = "-DCROW_BUILD_TESTS=NO -DCROW_BUILD_EXAMPLES=NO"
