#!/bin/sh

case "$1" in
apr)
    tar jxf apr-1.4.8.tar.bz2
    cd apr-1.4.8
    ./configure --prefix=$HOME/opt/apr-1.4.8
    make
    make install
    ;;
apr-util)
    tar jxf apr-util-1.5.2.tar.bz2
    cd apr-util-1.5.2
    ./configure --prefix=$HOME/opt/apr-util-1.5.2 --with-apr=$HOME/opt/apr-1.4.8/bin
    make
    make install
    ;;
apr-util.dbd)
    tar jxf apr-util-1.5.2.tar.bz2
    cd apr-util-1.5.2
    ./configure --prefix=$HOME/opt/apr-util-1.5.2  \
    --with-apr=$HOME/opt/apr-1.4.8/bin  \
    --with-mysql=/usr/local/mysql  \
    --with-pgsql=$HOME/opt/postgresql-9.3.2
    make
    make install
    ;;
httpd)
    # require:
    #   % sudo yum install pcre-devel

    tar jxf httpd-2.4.6.tar.bz2
    cd httpd-2.4.6
    ./configure --prefix=$HOME/opt/httpd-2.4.6 \
      --with-apr=$HOME/opt/apr-1.4.8  \
      --with-apr-util=$HOME/opt/apr-util-1.5.2  \
      --enable-dbd
    make
    make install
    ;;
git)
    tar zxf git-1.8.3.4.tar.gz
    cd git-1.8.3.4
    ./configure --prefix=$HOME/opt/git-1.8.3.4 --without-tcltk --with-curl
    make
    make install
    ;;
postgresql)
    tar jxf postgresql-9.3.2.tar.bz2
    cd postgresql-9.3.2
    ./configure --prefix=$HOME/opt/postgresql-9.3.2 --with-openssl
    make
    make install
    ;;
cmake)
    tar zxf cmake-2.8.12.tar.gz
    cd cmake-2.8.12
    ./bootstrap --prefix=$HOME/opt/cmake-2.8.12
    make
    make install
    ;;
jansson)
    tar zxf jansson.tar.gz
    cd jansson
#   cmake -DBUILD_SHARED=1 -DCMAKE_INSTALL_PREFIX:PATH=$HOME/opt/jansson
    cmake -DBUILD_SHARED_LIBS=1 -DCMAKE_INSTALL_PREFIX:PATH=$HOME/opt/jansson
    make install
    ;;
mysql)
    tar zxf mysql-5.5.34.tar.gz
    cd mysql-5.5.34
    cmake   \
    -DCMAKE_INSTALL_PREFIX=$HOME/opt/mysql-5.5.34  \
    -DWITH_SSL=yes
    make
    make install
#   tar zxf mysql-5.6.14.tar.gz
#   cd mysql-5.6.14
#   cmake   \
#   -DCMAKE_INSTALL_PREFIX=$HOME/opt/mysql-5.6.14  \
#   -DWITH_SSL=yes
#   make
#   make install
    ;;
clearsilver)
    tar zxf clearsilver-0.10.5.tar.gz
    cd clearsilver-0.10.5
    ./configure --prefix=$HOME/opt/clearsilver-0.10.5
    make
    make install

    mkdir $HOME/opt/clearsilver-0.10.5/include/ClearSilver/cs
    cp -p cs/cs.h $HOME/opt/clearsilver-0.10.5/include/ClearSilver/cs
    cp -p libs/libneo_cs.a $HOME/opt/clearsilver-0.10.5/lib

    ;;
discount)
     tar jxf discount-2.1.6.tar.bz2
     cd discount-2.1.6
     ./configure.sh --prefix=$HOME/opt/discount-2.1.6
     make
     make install
    ;;
ctemplate)
    tar zxf ctemplate-2.2.tar.gz
    cd ctemplate-2.2
    ./configure --prefix=$HOME/opt/ctemplate-2.2
    make
    make install
    ;;
*)
    echo "-> not "
    ;;
esac

