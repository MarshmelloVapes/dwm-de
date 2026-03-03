/* See LICENSE file for copyright and license details. */

#include "movestack.c"
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 10;       /* snap pixel */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int user_bh						= 4;				/* 2 is the default spacing around the bar*/
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "JetBrainsMono Nerd Font:size=11" };
static const char dmenufont[]       = "JetBrainsMono Nerd Font:size=11";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";

static const char col_fg[]    = "#f2e5bc"; /* background (bg0 soft) */
static const char col_bg[]    = "#3c3836"; /* foreground (fg0) */
static const char col_blk[]   = "#7c6f64"; /* neutral gray */
static const char col_red[]   = "#cc241d"; /* red */
static const char col_grn[]   = "#98971a"; /* green */
static const char col_ylw[]   = "#d79921"; /* yellow */
static const char col_blu[]   = "#458588"; /* blue */
static const char col_mag[]   = "#b16286"; /* purple */
static const char col_cyn[]   = "#689d6a"; /* aqua */
static const char col_brblk[] = "#928374"; /* light gray */

static const char *colors[][3] = {
    /*               fg       bg       border */
    [SchemeNorm] = { col_fg,  col_bg,   col_brblk },
    [SchemeSel]  = { col_cyn, col_bg,   col_mag   },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const int refreshrate = 120;  /* refresh rate (per second) for client move/resize */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "[\\]",     dwindle },
	{ "HHH",      grid },
	{ "|M|",      centeredmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "~/.config/rofi/launchers/type-2/launcher.sh", NULL };
static const char *termcmd[]  = { "alacritty", NULL };
static const char *firefox[] = { "firefox", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          SHCMD("~/.config/rofi/launchers/type-2/launcher.sh") },
	{ MODKEY,                       XK_f,      spawn,          {.v = firefox } },
	{ MODKEY|ShiftMask,             XK_s,      spawn,          SHCMD("shotgun -s ~/Photos/$(date +%Y-%m-%d_%H-%m-%S).png") },
	{ MODKEY,             					XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ControlMask,           XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY|ControlMask,           XK_p,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_u,      incrgaps,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_u,      incrgaps,       {.i = -1 } },
	{ MODKEY,              					XK_i,      incrigaps,      {.i = +1 } },
	{ MODKEY|ShiftMask,    					XK_i,      incrigaps,      {.i = -1 } },
	{ MODKEY,              					XK_o,      incrogaps,      {.i = +1 } },
	{ MODKEY|ShiftMask,    					XK_o,      incrogaps,      {.i = -1 } },
	{ MODKEY|Mod3Mask,              XK_0,      togglegaps,     {0} },
	{ MODKEY|Mod3Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,    					          XK_q,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_b,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,             XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_f,      fullscreen,     {0} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	// Cycle layout
	{ MODKEY,               XK_n,  cyclelayout, {.i = +1 } },
  { MODKEY|ShiftMask,     XK_n,  cyclelayout, {.i = -1 } },
	// Vol
	{ 0,                       			XF86XK_AudioMute,      spawn,         SHCMD("pactl set-sink-mute 0 toggle; kill -44 $(pidof dwmblocks)") },
	{ 0,                       			XF86XK_AudioRaiseVolume,      spawn,         SHCMD("pactl set-sink-volume 0 +5%; pkill -RTMIN+10 dwmblocks") },
	{ 0,                       			XF86XK_AudioLowerVolume,      spawn,         SHCMD("pactl set-sink-volume 0 -5%; pkill -RTMIN+10 dwmblocks") },
	{ 0,                       			XF86XK_AudioMicMute,      spawn,         SHCMD("pactl set-source-mute 0 toggle") },
	// Brightness
	{ 0,                       			XF86XK_MonBrightnessUp,      spawn,         SHCMD("brightnessctl set 5%+") },
	{ 0,                       			XF86XK_MonBrightnessDown,      spawn,         SHCMD("brightnessctl set 5%-") },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_p,      quit,           {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_q,      quit,           {1} }, 
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

