#!/usr/bin/bash

case "$1" in
start)
  echo "start"
  sudo /usr/local/apache2/bin/apachectl start
  ;;

stop)
  echo "stop"
  sudo /usr/local/apache2/bin/apachectl stop
  ;;

restart)
  echo "restart"
  sudo /usr/local/apache2/bin/apachectl restart
  ;;

config)
  echo "edit config"
  sudo vi /usr/local/apache2/conf/httpd.conf
  ;;

dav-config)
  echo "edit config"
  sudo vi /usr/local/apache2/conf/extra/httpd-dav.conf
  ;;

*)
  echo ""
  ;;
esac

