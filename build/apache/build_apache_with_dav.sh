#!/usr/bin/bash

MIRROR_SITE='https://dlcdn.apache.org/'

#----------------

WORK_DIR=`pwd`

#----------------

APR_VER='1.7.0'


echo 'build apr'
curl -O ${MIRROR_SITE}/apr/apr-${APR_VER}.tar.bz2
tar jxf apr-${APR_VER}.tar.bz2
cd ./apr-${APR_VER}
./configure
make
sudo make install


#----------------
# requirements:
# - libexpat1-dev
# $ sudo apt install libexpat1-dev

APR_UTIL_VER='1.6.1'

echo 'build apr-util'
cd $WORK_DIR
curl -O ${MIRROR_SITE}/apr/apr-util-${APR_UTIL_VER}.tar.bz2
tar jxf apr-util-${APR_UTIL_VER}.tar.bz2
cd apr-util-${APR_UTIL_VER}
./configure --with-apr=/usr/local/apr
make
sudo make install


#----------------
# requirements:
# - libpcre3
# - libpcre3-dev
# $ sudo apt install libpcre3 libpcre3-dev

HTTPD_VER='2.4.53'

echo 'build httpd'
cd $WORK_DIR
curl -O ${MIRROR_SITE}/httpd/httpd-${HTTPD_VER}.tar.bz2
tar jxf httpd-${HTTPD_VER}.tar.bz2
cd httpd-${HTTPD_VER}
./configure  \
  --with-apr=/usr/local/apr  \
  --enable-dav  \
  --enable-dav-fs  \
  --enable-dav-lock
make
sudo make install

exit 0

