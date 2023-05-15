#!/bin/bash

if amixer -c 0 get Master | grep -q off
then
	amixer set Master unmute
	amixer set Headphone unmute
	amixer set Speaker unmute
	amixer set PCM unmute
else
	amixer set Master mute
fi

bash $DWM_HOME/scripts/dwm-status-refresh.sh
