#!/usr/bin/env bash

curl \
-H "Host: lamp.local" \
-H "Connection: keep-alive" \
-H "Content-Length: 0" \
-H "Cache-Control: max-age=0" \
-H "Upgrade-Insecure-Requests: 1" \
-H "Origin: http://lamp.local" \
-H "Content-Type: application/x-www-form-urlencoded" \
-H "User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_14_6) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/81.0.4044.122 Safari/537.36" \
-H "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9" \
-H "Referer: http://lamp.local/" \
-H "Accept-Encoding: gzip, deflate" \
-H "Accept-Language: en-US,en;q=0.9" \
-X POST -d "" lamp.local:80/lamp/on

echo ""
echo ""

curl \
-H "Host: lamp.local" \
-H "Connection: keep-alive" \
-H "Content-Length: 0" \
-H "Cache-Control: max-age=0" \
-H "Upgrade-Insecure-Requests: 1" \
-H "Origin: http://lamp.local" \
-H "Content-Type: application/x-www-form-urlencoded" \
-H "User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_14_6) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/81.0.4044.122 Safari/537.36" \
-H "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9" \
-H "Referer: http://lamp.local/" \
-H "Accept-Encoding: gzip, deflate" \
-H "Accept-Language: en-US,en;q=0.9" \
-X POST -d "" lamp.local:80/lamp/off

echo ""
