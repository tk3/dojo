#!/bin/sh

sudo yum -y install pcre-devel
sudo yum -y install zlib-devel

sudo apt install -y libpcre3-dev

_version=1.7.12

[ -f ./nginx-${_version}.tar.gz ] || curl -O http://nginx.org/download/nginx-${_version}.tar.gz

tar zxf nginx-${_version}.tar.gz
cd ./nginx-${_version}
./configure --prefix=/usr/local/nginx
make
sudo make install
