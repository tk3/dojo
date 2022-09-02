#!/bin/bash

. ./config.sh

curl -i  \
  --request PUT  \
  --data-binary @$2  \
  $WEBDAV_HOST$WEBDAV_PATH/$1

