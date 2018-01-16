#!/bin/bash -eu

. ./.env

user_name=sample
user_id=$BACKLOG_USER_ID

echo $BACKLOG_HOST
echo $BACKLOG_API_KEY

echo "crawl $user_name"
bundle exe ./main.rb crawl --from=2016-12-01 --url=$BACKLOG_HOST --api_key=$BACKLOG_API_KEY --user_id=$user_id > activeties-$user_name.csv

echo "convert $user_name"
bundle exe ./main.rb convert activeties-$user_name.csv > data.js

