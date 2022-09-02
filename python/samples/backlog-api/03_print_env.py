#!/usr/bin/env python
# -*- coding: utf-8 -*-

from dotenv import load_dotenv
import os

load_dotenv()

backlog_url = os.getenv('BACKLOG_URL')
api_key = os.getenv('BACKLOG_API_KEY')

print('BACKLOG_URL: ' + backlog_url)
print('BACKLOG_API_KEY: ' + api_key)

