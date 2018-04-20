#!/usr/bin/env bash

cd /opt/geoserver/templates
for f in $(find ./ -regex '.*\.xml'); do envsubst < $f > "/opt/geoserver/data_dir/$f"; done