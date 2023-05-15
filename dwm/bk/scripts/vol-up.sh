#!/bin/bash

amixer -qM set Master 5%+ umute
bash $DWM_HOME/scripts/dwm-status-refresh.sh
