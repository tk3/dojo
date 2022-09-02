#!/usr/bin/env python
# -*- coding: utf-8 -*-

import requests

class BacklogApiClient:
    def __init__(self, url, api_key):
        self.url = url
        self.api_key = api_key

    def get_space(self):
        payload = { 'apiKey': self.api_key }
        api_space_url = self.url + '/api/v2/space'
        r = requests.get(api_space_url, params = payload)
        #return r.json()
        return r.status

if __name__ == "__main__":
    from dotenv import load_dotenv
    import os

    load_dotenv()

    backlog_url = os.getenv('BACKLOG_URL')
    api_key = os.getenv('BACKLOG_API_KEY')

    print(backlog_url)
    print(api_key)

    client = BacklogApiClient(backlog_url, api_key)
    response = client.get_space()

    print(response)

