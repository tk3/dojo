#!/bin/sh

_username=""
_user_token=''
_path="/v1/users/$_username/graphs"

curl -X GET https://pixe.la/$_path  \
	-H "X-USER-TOKEN: $_user_token"

