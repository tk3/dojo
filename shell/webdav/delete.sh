#!/bin/sh

. ./config.sh

if [ x$1 = x ]; then
  echo "not allow empty"
  exit 0
fi

curl -i  \
  -X DELETE  \
  $WEBDAV_HOST$WEBDAV_PATH/$1

