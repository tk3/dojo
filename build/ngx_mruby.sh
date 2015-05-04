#!/bin/sh

sudo yum -y install pcre-devel
sudo yum -y install zlib-devel
sudo yum -y install bison

_version=1.7.12

[ -f ./nginx-${_version}.tar.gz ] || curl -O http://nginx.org/download/nginx-${_version}.tar.gz

git clone https://github.com/matsumoto-r/ngx_mruby.git

tar zxf nginx-${_version}.tar.gz
_nginx_src=`pwd`/nginx-${_version}
_nginx_mruby_src=`pwd`/ngx_mruby
cd ngx_mruby
git submodule init
git submodule update
NGINX_CONFIG_OPT_ENV='--prefix=/usr/local' NGINX_SRC_ENV=$_nginx_src sh build.sh

sudo make install
