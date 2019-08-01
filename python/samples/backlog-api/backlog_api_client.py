#!/usr/bin/env python
# -*- coding: utf-8 -*-

import requests

class BacklogApiClient:
    def __init__(self, url, api_key):
        self.__url = url
        self.__api_key = api_key

    @property
    def url(self):
        return self.__url

    @property
    def api_key(self):
        return self.__api_key

    def get_space(self):
        payload = { 'apiKey': self.__api_key }
        api_space_url = self.__url + '/api/v2/space'
        r = requests.get(api_space_url, params = payload)
        return r.json()

if __name__ == "__main__":
    from dotenv import load_dotenv
    import os

    load_dotenv()

    backlog_url = os.getenv('BACKLOG_URL')
    api_key = os.getenv('BACKLOG_API_KEY')

    client = BacklogApiClient(backlog_url, api_key)

    print(client.url)
    print(client.api_key)

    response = client.get_space()
    print(response)

