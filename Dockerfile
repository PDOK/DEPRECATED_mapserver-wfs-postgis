FROM pdok/mapserver-wfs-postgis

RUN apt-get update \
  && apt-get -y install gettext-base \
  && apt-get clean \
  && rm -rf /var/lib/apt/lists/*

COPY /etc/natura2000.map /srv/data/natura2000.map
COPY /etc/header.inc /srv/data/header.inc

COPY /template/connection.inc /srv/template/connection.inc

COPY entry.sh /entry.sh
RUN chmod +x /entry.sh

CMD /entry.sh