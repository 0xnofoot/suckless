#!/bin/bash

# 检查 hjkl 是否已经映射为箭头键
if xmodmap -pke | grep -q 'keycode  43 = h'; then
	# 将 hjkl 映射为上下左右箭头键
	xmodmap -e 'keycode  43 = Left'
	xmodmap -e 'keycode 44 = Down'
	xmodmap -e 'keycode 45 = Up'
	xmodmap -e 'keycode 46 = Right'
	# echo "hjkl mapped to arrow keys."
else
	# 恢复 hjkl 功能
	xmodmap -e 'keycode 43 = h'
	xmodmap -e 'keycode 44 = j'
	xmodmap -e 'keycode 45 = k'
	xmodmap -e 'keycode 46 = l'
	# echo "hjkl restored."
fi
