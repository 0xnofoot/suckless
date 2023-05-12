#!/bin/bash

if [[ -n "$1" ]]; then
	echo -n "$1" | xclip -selection clipboard
else
	echo -n "$1" | xclip -selection clipboard
	echo -n "$1" | xclip -selection primary
fi
