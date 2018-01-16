
```shell
#!/bin/bash

backlog_host='https://xxxx.backlog.com/'
api_key='xxxx'

user_name=sample
user_id=xxxx

echo "crawl $user_name"
./main.rb crawl --from=2016-12-01 --url=$backlog_host --api_key=$api_key --user_id=$user_id > activeties-$user_name.csv

echo "convert $user_name"
./main.rb convert activeties-$user_name.csv > data.js
```