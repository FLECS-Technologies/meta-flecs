DESCRIPTION = "JSON for Modern C++"
LICENSE = "MIT"

SRC_URI = "https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz"
SRC_URI[sha256sum] = "d6c65aca6b1ed68e7a182f4757257b107ae403032760ed6ef121c9d55e81757d"

LIC_FILES_CHKSUM = "file://LICENSE.MIT;md5=f969127d7b7ed0a8a63c2bbeae002588"

S = "${WORKDIR}/json"

inherit cmake

EXTRA_OECMAKE = "-DJSON_BuildTests=NO"
