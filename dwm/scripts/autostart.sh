#!/bin/bash

sh $DWM_HOME/scripts/dualmon.sh
sh $DWM_HOME/scripts/dwm-status.sh &
sh $DWM_HOME/scripts/wp-autochange.sh &
$CLASH_HOME/clash-verge_1.3.1_amd64.AppImage &
picom --experimental-backends --config $DWM_HOME/scripts/picom/picom.conf &
# picom -b
xfce4-power-manager &
xfce4-volumed-pulse &
$DWM_HOME/scripts/autostart_wait.sh &
