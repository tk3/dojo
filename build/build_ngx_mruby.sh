#!/bin/sh

NGINX_VERSION=1.11.1 
NGINX_SRC=`pwd`/nginx-${NGINX_VERSION}
NGX_MRUBY_SRC=`pwd`/ngx_mruby

[ -f ./nginx-${NGINX_VERSION}.tar.gz ] || curl -O http://nginx.org/download/nginx-${NGINX_VERSION}.tar.gz
[ -d ./ngx_mruby ] || git clone --depth=1 https://github.com/matsumoto-r/ngx_mruby.git

tar zxf nginx-${NGINX_VERSION}.tar.gz

cd ${NGX_MRUBY_SRC}
git submodule init
git submodule update
./configure --with-ngx-src-root=${NGINX_SRC}
make generate_gems_config
make build_mruby
NGINX_OPT_LDFLAGS="`./mruby/bin/mruby-config --ldflags`"
NGINX_OPT_LIBS="`./mruby/bin/mruby-config --libs` `./mruby/bin/mruby-config --ldflags-before-libs` ${NGX_MRUBY_SRC}/mruby/build/host/lib/libmruby.a"

cd ${NGINX_SRC}
./configure  \
  --prefix=$HOME/opt/nginx-${NGINX_VERSION}  \
  --with-ld-opt="$NGINX_OPT_LDFLAGS $NGINX_OPT_LIBS"  \
  --with-http_ssl_module  \
  --add-module=${NGX_MRUBY_SRC}  \
  --add-module=${NGX_MRUBY_SRC}/dependence/ngx_devel_kit

make

#make install

