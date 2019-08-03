
DB_HOME = $(HOME)/var/lib/postgresql/main

default:
	@echo "makefile for postgresql operation"

start:
	/usr/lib/postgresql/10/bin/pg_ctl -D $(DB_HOME) start

stop:
	/usr/lib/postgresql/10/bin/pg_ctl -D $(DB_HOME) stop

edit-config:
	vim $(DB_HOME)/postgresql.conf  \
	  /home/vagrant/var/lib/postgresql/main/pg_hba.conf

