#!/bin/sh
base64 smarthosts_64x64.png |xargs -I {} echo " "{}>smarthosts.base64

