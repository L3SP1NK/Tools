#!/bin/bash

setScreenSaver() {
	while true
		do
			clear

			screensaver=$(find /usr/libexec/xscreensaver/|shuf|head -n1)
			coproc "${screensaver}" --root

			echo -e "${screensaver}\npress [enter] to view another screensaver"
			read

			kill "$(pidof ${screensaver})"
			setScreenSaver
	done
}

setScreenSaver
