#!/bin/bash

name=`ls $PIC_HOME/wallpaper/`
name_arr=(${name})
N=${#name_arr[*]}
r=$(($RANDOM%$N))
wall_var=${name_arr[$r]}
feh --recursive --bg-fill $PIC_HOME/wallpaper/$wall_var
