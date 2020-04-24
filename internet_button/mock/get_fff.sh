#!/usr/bin/env bash

LIBRARYSRC=./fff-src

git clone https://github.com/meekrosoft/fff.git ${LIBRARYSRC}

cp ${LIBRARYSRC}/*.h .

rm -rf ${LIBRARYSRC}
