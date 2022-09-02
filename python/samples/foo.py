#!/usr/bin/env python
# -*- coding: utf-8 -*-

import requests

r = requests.get('Http://localhost:10080/')

print('status_code: %d' % (r.status_code))

print('headers')
for k in r.headers:
    print(k + ': ' + r.headers[k])

print('header')
print('Content-Type: ' + r.headers['content-type'])
print('Content-Type: ' + r.headers.get('content-type'))

