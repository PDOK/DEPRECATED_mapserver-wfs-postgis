# Mapserver WFS Postgis

## TL;DR

```docker
docker build -t pdok/mapserver-wfs-postgis .
docker run -e MS_MAPFILE='/srv/data/example.map' -d -p 80:80 --name mapserver-example -v /path/on/host:/srv/data pdok/mapserver-wfs-postgis

docker stop mapserver-example
docker rm mapserver-example
```

## Introduction

This project aims to fulfill two needs:

1. create a [OGC WFS](http://www.opengeospatial.org/standards/wfs) service that is deployable on a scalable infrastructure.
2. create a useable [Docker](https://www.docker.com) base image.

Fulfilling the main purpose of the first need is to create an Docker base image that eventually can be run on a platform like [Kubernetes](https://kubernetes.io/).

Regarding the second need, finding a usable Mapserver Docker image is a challenge. Most images expose the &map=... QUERY_STRING in the getcapabilities and don't run in fastcgi.

## What will it do

It will create an WFS-only Mapserver application run with a lightweight web application Lighttpd in which the map=.. QUERY_STRING issue is fixed and the vector data source is extracted from a(external) Postgis spatial database.

## Components

This stack is composed of the following:

* [Mapserver](http://mapserver.org/)
* [Postgis](http://postgis.net/)
* [Lighttpd](https://www.lighttpd.net/)

### Mapserver

Mapserver is the platform that will provide the WMS service.

### Postgis

Postgis is a spatial database in which the vector data is stored.

### Lighttpd

Lighttpd is the web server we use to run Mapserver as a fastcgi web application.

## Docker image

The Docker image contains 2 stages:

1. builder
2. service

### builder

The builder stage compiles Mapserver. The Dockerfile contains all the available Mapserver build option explicitly, so it is clear which options are enabled and disabled. In this case the options like -DWITH_WFS are enabled and -DWITH_WMS are disabled, because we want only an WMS service.

### service

The service stage copies the Mapserver, build in the first stage, and configures Lighttpd.

## Usage

### Build

```docker
docker build -t pdok/mapserver-wms-postgis .
```

### Run

This image can be run straight from the commandline. A volumn needs to be mounted on the container directory /srv/data. The mounted volumn needs to contain at least one mapserver *.map file. And the mapfile needs to be passed as an environment variable.

```docker
docker run -d -p 80:80 --name mapserver-run-example -v /path/on/host:/srv/data pdok/mapserver-wfs-postgis
```

The good way to use it is as a Docker base image for an other Dockerfile, in which the necessay files are copied into the right directory (/srv/data)

```docker
FROM pdok/mapserver-wms-postgis

ENV MS_MAPFILE /srv/data/example.map

COPY /etc/example.map /srv/data/example.map
```

Running the example above will create a service on the url <http://localhost/?request=getcapabilities&service=wfs>

The ENV variables that can be set are:

* DEBUG
* MIN_PROCS
* MAX_PROCS
* MAX_LOAD_PER_PROC
* IDLE_TIMEOUT
* MS_MAPFILE

The ENV variables, with the exception of MS_MAPFILE have a default value set in the Dockerfile.

```docker
docker run -e DEBUG=0 -e MIN_PROCS=1 -e MAX_PROCS=3 -e MAX_LOAD_PER_PROC=4 -e IDLE_TIMEOUT=20 -e MS_MAPFILE='/srv/data/example.map' -d -p 80:80 --name mapserver-run-example -v /path/on/host:/srv/data pdok/mapserver-wms-postgis
```

## Misc

### Why no WMS

If one wants a [OGC WMS](http://www.opengeospatial.org/standards/wms) service, then we have our [pdok/mapserver-wms-postgis](https://github.com/PDOK/mapserver-wms-postgis) image.
So why are those (WMS and WFS) seperated? We regard both service as completly different. Regarding microservices it is logical to split those from each other. Also in our experience we have run to often into issues that the same data is exposed as a WMS and WFS.

### Why Lighttpd

In our previous configurations we would run NGINX, while this is a good webservice and has a lot of configuration options, it runs with multiple processes. There for we needed supervisord for managing this, whereas Lighthttpd runs as a single proces. Also all the routing configuration options aren't needed, because that is handled by the infrastructure/platform, like Kubernetes. If one would like to configure some simple routing is still can be done in the lighttpd.conf.

### Used examples

* <https://github.com/srounet/docker-mapserver>
* <https://github.com/Amsterdam/mapserver>