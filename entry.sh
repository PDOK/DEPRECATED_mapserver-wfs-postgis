#!/usr/bin/env bash

cd /srv/template
for f in $(find ./ -regex '.*\.inc'); do envsubst < $f > "/srv/data/$f"; done

/usr/bin/supervisord -c /etc/supervisor/conf.d/supervisord.conf