#!/usr/bin/env python
# -*- coding: utf-8 -*-

from dotenv import load_dotenv
import os
import requests

load_dotenv()

backlog_url = os.getenv('BACKLOG_URL')
api_key = os.getenv('BACKLOG_API_KEY')

print(backlog_url)
print(api_key)

payload = { 'apiKey': api_key }

api_space_url = backlog_url + '/api/v2/users/myself'

r = requests.get(api_space_url, params=payload)

print(r)
print(r.json())

