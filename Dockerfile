FROM pdok/mapserver-wfs-postgis

COPY /etc/natura2000.map /srv/data/natura2000.map
COPY /etc/header.inc /srv/data/header.inc