#!/usr/bin/env python
# -*- coding: utf-8 -*-

import unittest
from unittest.mock import patch, MagicMock
from backlog_api_client import BacklogApiClient
import json

class TestBacklogApiClient(unittest.TestCase):

    def test_property(self):
        client = BacklogApiClient('aaa', 'bbb')
        self.assertEqual(client.url, 'aaa')
        self.assertEqual(client.api_key, 'bbb')

    def test_get_space_1(self):
        mock_json_res = json.dumps({'method': 'POST'})

        client = BacklogApiClient('http://example.com/api', '________apiKey________')
        client.get_space = MagicMock(return_value=mock_json_res)
        actual = client.get_space()

        expected = json.dumps({'method': 'POST'})

        self.assertEqual(actual, expected)

    def test_get_space_2(self):
        mock_json_res = json.dumps({'method': 'POST'})

        mock = Mock()
        mock.get.json.return_value = 100

        client = BacklogApiClient('http://example.com/api', '________apiKey________')
        client.requests = mock
        actual = client.get_space()

        expected = json.dumps({'method': 'POST'})

        self.assertEqual(actual, expected)

    @patch('backlog_api_client.requests')
    def test_get_space_3(self, mock):
        mock_json_res = json.dumps({'method': 'GET'})
        mock.get.json = MagicMock(return_value=mock_json_res)

        client = BacklogApiClient('http://example.com/api', '________apiKey________')
        actual = client.get_space()

        expected = json.dumps({'method': 'POST'})

        self.assertEqual(actual, expected)

if __name__ == '__main__':
    unittest.main()

