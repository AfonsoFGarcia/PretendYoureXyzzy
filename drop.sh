#!/bin/bash
cd /home/osboxes/Documents/PretendYoureXyzzy
psql -f drop.sql
dropdb cah
createdb cah
psql -f create.sql
