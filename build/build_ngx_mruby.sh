#!/bin/sh

NGINX_VERSION=1.11.1 
NGINX_SRC=`pwd`/nginx-${NGINX_VERSION}
NGX_MRUBY_SRC=`pwd`/ngx_mruby
NGINX_PREFIX="$HOME/opt/nginx-${NGINX_VERSION}"

[ -f ./nginx-${NGINX_VERSION}.tar.gz ] || curl -O http://nginx.org/download/nginx-${NGINX_VERSION}.tar.gz
[ -d ./ngx_mruby ] || git clone --depth=1 https://github.com/matsumoto-r/ngx_mruby.git

tar zxf nginx-${NGINX_VERSION}.tar.gz

cd $NGX_MRUBY_SRC
git submodule init
git submodule update
./configure --with-ngx-src-root=$NGINX_SRC
make build_mruby
make generate_gems_config

cd $NGINX_SRC
./configure  \
  --prefix=$NGINX_PREFIX  \
  --with-http_ssl_module  \
  --add-module=${NGX_MRUBY_SRC}  \
  --add-module=${NGX_MRUBY_SRC}/dependence/ngx_devel_kit

make

make install

