#!/bin/sh

. ./config.sh

curl -i  \
  -X MKCOL  \
  $WEBDAV_HOST$WEBDAV_PATH/$1

