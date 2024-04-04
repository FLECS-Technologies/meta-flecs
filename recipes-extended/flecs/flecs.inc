SUMMARY = "FLECS"
DESCRIPTION = "FLECS is the ultimate open marketplace for industrial automation. We simplify your technology integration and enable the effortless, scalable sales and delivery of your innovative automation solutions."
HOMEPAGE = "https://flecs.tech"
LICENSE = "Apache-2.0"

DEPENDS = "cpr crow curl libarchive libusb1 nlohmann-json openssl yaml-cpp zenoh-c"
RDEPENDS:${PN} = "docker zenoh-c"

SRC_URI = "gitsm://github.com/FLECS-Technologies/flecs-public.git;protocol=https;nobranch=1"

LIC_FILES_CHKSUM = "file://LICENSE;md5=86d3f3a95c324c9479bd8986968f4327"

S = "${WORKDIR}/git"

INSANE_SKIP:${PN}-dev += " dev-elf"

inherit cmake
inherit systemd

do_install:append() {
    echo DESTDIR='${D}' ${CMAKE_VERBOSE} cmake --install '${B}' --component native
    DESTDIR='${D}' ${CMAKE_VERBOSE} cmake --install '${B}' --component native
    DESTDIR='${D}' ${CMAKE_VERBOSE} cmake --install '${B}' --component native-systemd
}

SYSTEMD_SERVICE:${PN} = "flecs.service"

FILES:${PN} = "\
    /usr/bin/flecsd \
    /usr/lib/libFLECS.daemon.so \
    /usr/lib/libflunder.so \
    /usr/lib/libflunder.so.3 \
    /lib/systemd/system/flecs.service \
"
