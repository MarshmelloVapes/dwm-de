//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/	/*Command*/		/*Update Interval*/	/*Update Signal*/
	/* {"⌨", "sb-kbselect", 0, 30}, */

	{"", "~/.scripts/sb-mail", 120, 12},
    	{"", "~/.scripts/sb-weather", 1800, 5},
	{ "",     "~/.scripts/sb-powerprofiles", 0, 13 },
    	{"RAM ", "free -m | awk '/Mem:/ {printf \"%d%%\", $3*100/$2 }'", 5, 6},
    	{"VOL ", "~/.scripts/volume.sh", 0, 10},
    	{"SCR ", "~/.scripts/brightness.sh", 0, 20},
    	{"",     "~/.scripts/battery", 30, 7 },
    	{"", "date '+%d %b %H:%M '", 60, 1},
};

//Sets delimiter between status commands. NULL character ('\0') means no delimiter.
static char *delim = " | ";

// Have dwmblocks automatically recompile and run when you edit this file in
// vim with the following line in your vimrc/init.vim:

// autocmd BufWritePost ~/.local/src/dwmblocks/config.h !cd ~/.local/src/dwmblocks/; sudo make install && { killall -q dwmblocks;setsid dwmblocks & }
