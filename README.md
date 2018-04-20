# Mapserver WFS Postgis

## Introduction
This project aims to fulfill two needs:
1. create a [OGC WFS](http://www.opengeospatial.org/standards/wfs) service that is deployable on a scalable infrastructure.
2. create a useable [Docker](https://www.docker.com) base image.

Fulfilling the first need the many purpose is to create an Docker base image that eventually can be run on a platform like [Kubernetes](https://kubernetes.io/).

Regarding the second need, finding a usable Mapserver Docker image is a challenge. Most images expose the &map=... QUERY_STRING in the getcapabilities, don't run in fastcgi and are based on Apache.

## What will it do
It will create an WFS-only Mapserver application run with a modern web application NGINX in which the map=.. QUERY_STRING is fixed. The application will work best incombination with GDAL/OGR vector datasources like: [Geopackage](http://www.geopackage.org/) of SHAPE files. 

## Components
This stack is composed of the following:
* [Mapserver](http://mapserver.org/)
* [Postgis](http://postgis.net/)
* [NGINX](https://www.nginx.com/)
* [Supervisor](http://supervisord.org/)

### Mapserver
Mapserver is the platform that will provide the WFS service.

### NGINX
NGINX is the web server we use to run Mapserver as a fastcgi web application. 

### Postgis
Postgis is a spatial database in which the vector data is stored.

### Supervisor
Because we are running 2 processes (Mapserver CGI & NGINX) in a single Docker image we use Supervisor as a controller.

## Docker image

The Docker image contains 2 stages:
1. builder
2. Service

### builder
The builder stage compiles Mapserver. The Dockerfile contains all the available Mapserver build option explicitly, so it is clear which options are enabled and disabled. In this case the options like -DWITH_WFS are enabled and -DWITH_WMS are disabled, because we want only an WFS service.

### service
The service stage copies the Mapserver, build in the first stage, and configures NGINX and Supervisor.

## Usage

### Build
```
docker build -t pdok/mapserver-wfs-postgis .
```

### Run
This image can be run straight from the commandline. A volumn needs to be mounted on the container directory /srv/data. The mounted volumn needs to contain at least one mapserver *.map file. The name of the mapfile will determine the URL path for the service.
```
docker run -d -p 80:80 --name mapserver-run-example -v /path/on/host:/srv/data pdok/mapserver-wfs-postgis
```

The prefered way to use it is as a Docker base image for an other Dockerfile, in which the necessay files are copied into the right directory (/srv/data)
```
FROM pdok/mapserver-wfs-postgis

COPY /etc/example.map /srv/data/example.map
```
Running the example above will create a service on the url: http:/localhost/example/wfs? An working example can be found: https://github.com/PDOK/mapserver-wfs-postgis/tree/natura2000-example

A third way is to set ENV variables that will populate a connection.inc file
```
CONNECTIONTYPE POSTGIS
CONNECTION "host=${HOST} dbname=${DBNAME} user=${USER} password=${PASSWORD} port=${PORT}"
```
The ENV variables are:
- HOST
- DBNAME
- USER
- PASSWORD
- PORT

```
docker run -e HOST='your_host' -e PORT='your_port' -e DBNAME='your_dbname' -e USER='your_user' -e=PASSWORD='your_password' -d -p 80:80 --name mapserver-run-example -v /path/on/host:/srv/data pdok/mapserver-wfs-postgis
```

## Misc
### Why no WMS
If one wants a [OGC WMS](http://www.opengeospatial.org/standards/wms) service, then we have our [pdok/mapserver-wms-postgis](https://github.com/PDOK/mapserver-wms-postgis) image.
So why are those (WFS and WMS) seperated? We regard both service as completly different. Regarding microservices it is logical to split those from each other. Also in our experience we have run to often into issues that the same data is exposed as a WMS and WFS.

### Why NGINX
We would like to run this on a scalable infrastructure like Kubernetes that has it's Ingress based on NGINX. By keeping both the same we hope to have less differentiation in our application stack.

### Used examples
* https://github.com/srounet/docker-mapserver
* https://github.com/Amsterdam/mapserver
