#!/usr/bin/env ruby

require "sinatra"
require "json"

get "/article" do
  content_type :json
  {
    "id": 8,
    "title": "title",
    "content": "content",
    "created": "2017-05-06T15:10:30Z",
    "updated": "2017-05-10T07:55:37Z",
    "createdUser": {
      "id": 345,
      "userId": "Taro"
    },
    "attachmentFiles": [
      {
        "id": 6789,
        "fileName": "image0001.png"
      },
      {
        "id": 7890,
        "fileName": "image0002.png"
      }
    ]
  }.to_json
end

get "/articles" do
  content_type :json
  [
    {
      "id": 20,
      "title": "title 01",
      "content": "content.\ncontent 01.",
      "created": "2017-07-06T15:10:30Z",
      "updated": "2018-01-10T07:55:37Z",
      "createdUser": {
        "id": 123,
        "userId": "Bod"
      },
      "attachmentFiles": [
        {
          "id": 2468,
          "fileName": "image2201.png"
        },
        {
          "id": 2489,
          "fileName": "image2202.png"
        }
      ]
    },

    {
      "id": 22,
      "title": "title 02",
      "content": "content02",
      "created": "2017-08-06T15:10:30Z",
      "updated": "2017-12-12T08:20:56Z",
      "createdUser": {
        "id": 456,
        "userId": "Mike"
      },
      "attachmentFiles": [
        {
           "id": 3568,
          "fileName": "image4301.png"
        },
        {
          "id": 5432,
          "fileName": "image4302.png"
        }
      ]
    },
  ].to_json
end
