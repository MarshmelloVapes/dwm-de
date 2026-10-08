//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/	/*Command*/		/*Update Interval*/	/*Update Signal*/
	/* {"⌨", "sb-kbselect", 0, 30}, */
	{ "",     "~/.scripts/sb-powerprofiles", 0, 13 },
    {"^c#ebdbb2^ | ^d^", NULL, 0, 0},

    {"^c#8ec07c^", "~/.scripts/sb-weather", 3600, 5},
    {"^c#ebdbb2^ | ^d^", NULL, 0, 0},

    {"^c#fabd2f^RAM ", "free -m | awk '/Mem:/ {printf \"%d%%\", $3*100/$2 }'", 5, 6},
    {"^c#ebdbb2^ | ^d^", NULL, 0, 0},

    {"^c#83a598^VOL ", "~/.scripts/volume.sh", 0, 10},
    {"^c#ebdbb2^ | ^d^", NULL, 0, 0},

    {"^c#83a321^SCR ", "~/.scripts/brightness.sh", 0, 20},
    {"^c#ebdbb2^ | ^d^", NULL, 0, 0},

    { "^c#fb4934^",     "~/.scripts/battery", 30, 7 },
    {"^c#ebdbb2^ | ^d^", NULL, 0, 0},

    {"^c#d3869b^", "date '+%d %b %H:%M '", 60, 1},
};

//Sets delimiter between status commands. NULL character ('\0') means no delimiter.
static char *delim = "\0";

// Have dwmblocks automatically recompile and run when you edit this file in
// vim with the following line in your vimrc/init.vim:

// autocmd BufWritePost ~/.local/src/dwmblocks/config.h !cd ~/.local/src/dwmblocks/; sudo make install && { killall -q dwmblocks;setsid dwmblocks & }
