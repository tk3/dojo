#!/bin/sh

_username=""
_user_token=''
_path="/v1/users/$_username/webhooks"

curl -X POST https://pixe.la/$_path  \
	-H "X-USER-TOKEN: $_user_token"  \
	-d '{"graphID":"tk3-bookmarks","type":"increment"}'

https://pixe.la/v1/users/<username>/webhooks/<WebhookHashString>

