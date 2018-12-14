#!/bin/sh
 
case "$1" in
apr)
  APR_VER=1.6.3
  curl -O http://ftp.riken.jp/net/apache//apr/apr-$APR_VER.tar.bz2
  tar jxf apr-$APR_VER.tar.bz2
  cd apr-$APR_VER
  ./configure --prefix=$HOME/opt/apr-$APR_VER
  make
  make install
  ;;
apr-util)
  # sudo apt install libexpat1-dev
  APR_VER=1.6.3
  APR_UTIL_VER=1.6.1
  curl -O http://ftp.riken.jp/net/apache//apr/apr-util-$APR_UTIL_VER.tar.bz2
  tar jxf apr-util-$APR_UTIL_VER.tar.bz2
  cd apr-util-$APR_UTIL_VER
  ./configure --prefix=$HOME/opt/apr-util-$APR_UTIL_VER --with-apr=$HOME/opt/apr-$APR_VER/bin
  make
  make install
  ;;
httpd | apache)
  # sudo apt install libpcre3-dev
  APR_VER=1.6.3
  APR_UTIL_VER=1.6.1
  APACHE_VER=2.4.34
  curl -O http://ftp.yz.yamagata-u.ac.jp/pub/network/apache//httpd/httpd-$APACHE_VER.tar.bz2
  tar jxf httpd-$APACHE_VER.tar.bz2
  cd httpd-$APACHE_VER
  ./configure --prefix=$HOME/opt/httpd-$APACHE_VER  \
    --with-apr=$HOME/opt/apr-$APR_VER  \
    --with-apr-util=$HOME/opt/apr-util-$APR_UTIL_VER  \
    --enable-dav  \
    --enable-dav-fs  \
    --enable-dav-lock
  make
  make install
  ;;
apache-config)
  APACHE_VER=2.4.34
  echo 'export PATH="$HOME/opt/httpd-'$APACHE_VER'/bin:$PATH"' >> ~/.bashrc
  exec $SHELL -l
  ;;
*)
  echo "$0 apr"
  echo "$0 apr-util"
  echo "$0 httpd | apache"
  ;;

esac

