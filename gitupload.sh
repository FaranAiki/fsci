#/usr/bin/env bash

git init
git add .
git commit -m "Updating with date of $(date +%F)"
git remote add origin https://github.com/faranaiki/fsci.git
git remote show origin
git pull origin master
git push --force -u origin master
