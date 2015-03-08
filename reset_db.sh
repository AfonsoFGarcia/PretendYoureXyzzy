#!/bin/bash

sudo service tomcat7 stop
export PGPASSWORD=12345
gcc -o cardparser cardparser.c
./cardparser blackcards.txt whitecards.txt twitter.sql
sudo -u postgres ./drop.sh
psql -h localhost -d cahdb -U cah -f cah_cards.sql
psql -h localhost -d cahdb -U cah -f twitter.sql
sudo service tomcat7 start
