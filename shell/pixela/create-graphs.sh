#!/bin/sh

_username=""
_user_token=''
_path="/v1/users/$_username/graphs"

curl -X POST https://pixe.la/$_path  \
	-H "X-USER-TOKEN: $_user_token"  \
	-d '{"id":"tk3-bookmarks","name":"tk3-bookmarks","unit":"updates","type":"int","color":"shibafu","timezone":"Asia/Tokyo"}'

