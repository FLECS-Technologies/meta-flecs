SUMMARY = "FLECS WebApp"
DESCRIPTION = "FLECS is the ultimate open marketplace for industrial automation. We simplify your technology integration and enable the effortless, scalable sales and delivery of your innovative automation solutions."
HOMEPAGE = "https://flecs.tech"
LICENSE = "Apache-2.0"

RDEPENDS:${PN} = "flecs nginx"

INSANE_SKIP:${PN} = "file-rdeps"

SRC_URI:append = "\
    git://github.com/FLECS-Technologies/flecs-webapp.git;protocol=https;nobranch=1 \
    file://path_to_react-scripts.patch \
    npmsw://${THISDIR}/${BPN}/${PV}/npm-shrinkwrap.json;dev=1 \
"

LIC_FILES_CHKSUM = "file://LICENSE;md5=731715b1956ae120be8d41d68e0890be"

S = "${WORKDIR}/git"

inherit npm

RDEPENDS:${PN}:remove = "nodejs"

FLECS_WEBAPP_PORT ?= "8080"
FLECS_WEBAPP_PROTO ?= "http"
FLECS_WEBAPP_HOST ?= "localhost"
FLECS_WEBAPP_ROUTE ?= "flecs"
FLECS_WEBAPP_HOME = "${FLECS_WEBAPP_PROTO}://${FLECS_WEBAPP_HOST}/${FLECS_WEBAPP_ROUTE}/"

do_patch:append() {
    import subprocess

    cmd = [
        "sed",
        "-i",
        "s#^\\(.*\\)\"homepage\":.*$#\\1\"homepage\": \"%s\",#g" % (d.getVar("FLECS_WEBAPP_HOME")),
        "package.json"
    ]
    subprocess.run(cmd, cwd=d.getVar("S"), shell=False, check=True)

    cmd = [
        "sed",
        "-i",
        "s#^\\(.*\\)<Router basename=.*$#\\1<Router basename=\x27%s\x27>#g" % (d.getVar("FLECS_WEBAPP_ROUTE")),
        "src/index.js"
    ]
    subprocess.run(cmd, cwd=d.getVar("S"), shell=False, check=True)

    cmd = [
        "sed",
        "-i",
        "s#^\\(.*\\)listen.*$#\\1listen %s;#g" % (d.getVar("FLECS_WEBAPP_PORT")),
        "docker/conf.d/default.conf"
    ]
    subprocess.run(cmd, cwd=d.getVar("S"), shell=False, check=True)

    cmd = [
        "sed",
        "-i",
        "s#^\\(.*\\)server_name.*$#\\1server_name %s;#g" % (d.getVar("FLECS_WEBAPP_HOST")),
        "docker/conf.d/default.conf"
    ]
    subprocess.run(cmd, cwd=d.getVar("S"), shell=False, check=True)

    cmd = [
        "sed",
        "-i",
        "s#flecs-flecsd#%s#g" % (d.getVar("FLECS_WEBAPP_HOST")),
        "docker/conf.d/default.conf"
    ]
    subprocess.run(cmd, cwd=d.getVar("S"), shell=False, check=True)

    cmd = [
        "sed",
        "-i",
        "s#ui#%s#g" % (d.getVar("FLECS_WEBAPP_ROUTE")),
        "docker/conf.d/default.conf"
    ]
    subprocess.run(cmd, cwd=d.getVar("S"), shell=False, check=True)

    cmd = [
        "sed",
        "-i",
        "s#^\\(.*\\)root /usr/share/nginx/html/.*$#\\1root %s/html/flecs-webapp/;#g" % (d.getVar("datadir")),
        "docker/conf.d/default.conf"
    ]
    subprocess.run(cmd, cwd=d.getVar("S"), shell=False, check=True)
}

python do_compile() {
    import subprocess

    cmd = "npm run build:production --if-present"
    cmd += " --cache=%s" % (d.getVar("NPM_CACHE"))

    # Pack and install the main package
    subprocess.run(cmd.split(), shell=False, check=True)
}

do_install() {
    install -d ${D}/${datadir}/html/flecs-webapp/${FLECS_WEBAPP_ROUTE}/
    install -d ${D}${sysconfdir}/nginx/sites-available/
    install -d ${D}${sysconfdir}/nginx/sites-enabled/

    cp --preserve=mode -rt ${D}/${datadir}/html/flecs-webapp/${FLECS_WEBAPP_ROUTE} ${S}/build/*
    install -m 0644 ${S}/docker/conf.d/default.conf ${D}${sysconfdir}/nginx/sites-available/50_flecs-webapp.conf
    ln -s ${sysconfdir}/nginx/sites-available/50_flecs-webapp.conf ${D}${sysconfdir}/nginx/sites-enabled/50_flecs-webapp.conf
}

FILES:${PN}:append = "\
    ${datadir}/html/flecs-webapp \
    ${sysconfdir}/nginx/sites-available/50_flecs-webapp.conf \
    ${sysconfdir}/nginx/sites-enabled/50_flecs-webapp.conf \
"
