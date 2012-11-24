#!/bin/sh

lupdate ../qml/*qml -ts smarthosts.ts
lupdate ../qml/*qml -ts smarthosts_zh.ts
lrelease smarthosts_zh.ts


