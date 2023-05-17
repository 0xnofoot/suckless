#!/bin/bash

sleep 1

nm-applet &
libinput-gestures-setup start &
fcitx5 &
$CLASH_HOME/clash-verge_1.3.1_amd64.AppImage &
