#!/bin/bash

. ./config.sh

curl -i  \
  -X PROPFIND  \
  -H 'Depth: 1'  \
  $WEBDAV_HOST$WEBDAV_PATH/$1

