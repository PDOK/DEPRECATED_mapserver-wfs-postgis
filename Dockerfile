FROM pdok/mapserver-wfs-postgis

COPY /etc/natura2000.map /srv/data/natura2000.map
COPY /etc/connection.inc /srv/data/connection.inc
COPY /etc/header.inc /srv/data/header.inc