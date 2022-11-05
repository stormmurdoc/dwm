/* See LICENSE file for copyright and license details. */

/* Constants */
#define TERMINAL "st"
#define TERMCLASS "St"
#define BROWSER "brave"

/* appearance */
static unsigned int borderpx  = 3;        /* border pixel of windows */
static unsigned int snap      = 32;       /* snap pixel */
static unsigned int gappih    = 20;       /* horiz inner gap between windows */
static unsigned int gappiv    = 10;       /* vert inner gap between windows */
static unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static unsigned int gappov    = 30;       /* vert outer gap between windows and screen edge */
static int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static int showbar            = 1;        /* 0 means no bar */
static int topbar             = 1;        /* 0 means bottom bar */
static char *fonts[]          = {
   "Droid Sans:size=9:antialias=true:autohint=true",
   "Droid Sans Mono Dotted for Powerline:size=9:antialias=true:autohint=true",
   "monospace:size=9",
   "JoyPixels:pixelsize=9:antialias=true:autohint=true"  };
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#770000";
static char selbgcolor[]            = "#222222";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {TERMINAL, "-n", "spterm", "-g", "120x34", NULL };
const char *spcmd2[] = {TERMINAL, "-n", "spcalc", "-f", "monospace:size=16", "-g", "50x20", "-e", "bc", "-lq", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
	{"spcalc",      spcmd2},
};

/* tagging */
static const char *tags[] = { "1:Web ", "2:Term ", "3:Files ", "4:VDI ", "5:IRC ", "6:Email ", "7:Discord ", "8", "9" }      ;

/* rulez */
static const Rule rules[] = {
    /* xprop(1):
     * xprop | awk '/^WM_CLASS/{sub(/.* =/, "instance:"); sub(/,/, "\nclass:"); print}/^WM_NAME/{sub(/.* =/, "title:"); print}'
     *  WM_CLASS(STRING) = instance, class
     *  WM_NAME(STRING) = title
    */
    /* class                        instance        title             tags mask     isfloating   isterminal  noswallow  monitor */
    { "St",                         NULL,           NULL,             0,            0,           1,          0,         -1 },
    { "Gimp",                       NULL,           NULL,             1 << 8,       0,           0,          0,         -1 },
    { "trayer",                     NULL,           NULL,             1 << 8,       1,           0,          0,         -1 },
    { "Evolution",                  NULL,           NULL,             1 << 5,       0,           0,          0,         -1 },
    { "Evolution-alarm-notify",     NULL,           NULL,             1 << 5,       1,           0,          0,         -1 },
    { "Microsoft Teams - Preview",  NULL,           NULL,             1 << 6,       0,           0,          0,         -1 },
    { "discord",                    NULL,           NULL,             1 << 6,       0,           0,          0,         -1 },
    { NULL,                         NULL,           "Microsoft Teams-Benachrichtigung",1 << 6,1, 0,          0,         -1 },
    { NULL,                         NULL,           "term1",          1 << 1,       0,           1,          0,         -1 },
    { NULL,                         NULL,           "termlf",         1 << 2,       0,           1,          0,         -1 },
    { "Vmware-view",                NULL,           NULL,             1 << 3,       0,           0,          0,         -1 },
    { NULL,                         NULL,           "termirc",        1 << 4,       0,           1,          0,         -1 },
    { NULL,                         NULL,           "Event Tester",   0,            0,           0,          1,         -1 },
    { NULL,                        "spterm",        NULL,             SPTAG(0),     1,           1,          0,         -1 },
    { NULL,                        "spcalc",        NULL,             SPTAG(1),     1,           1,          0,         -1 },
    { NULL,                        "splf",          NULL,             SPTAG(2),     1,           1,          0,         -1 },
    //{ "trayer",   NULL,       NULL,             1 << 8,       1,           0,         0,        -1 },
};
/* layout(s) */
static float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",	tile },			/* Default: Master on left, slaves on right */
	{ "TTT",	bstack },		/* Master on top, slaves on bottom */

	{ "[@]",	spiral },		/* Fibonacci spiral */
	{ "[\\]",	dwindle },		/* Decreasing in size right and leftward */

	{ "[D]",	deck },			/* Master on left, slaves in monocle-like mode on right */
	{ "[M]",	monocle },		/* All windows on top of eachother */

	{ "|M|",	centeredmaster },		/* Master in middle, slaves on sides */
	{ ">M>",	centeredfloatingmaster },	/* Same but master floats */

	{ "><>",	NULL },			/* no layout function means floating behavior */
	{ NULL,		NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
	{ MOD,	XK_j,	ACTION##stack,	{.i = INC(+1) } }, \
	{ MOD,	XK_k,	ACTION##stack,	{.i = INC(-1) } }, \
	{ MOD,  XK_v,   ACTION##stack,  {.i = 0 } }, \
	/* { MOD, XK_grave, ACTION##stack, {.i = PREVSEL } }, \ */
	/* { MOD, XK_a,     ACTION##stack, {.i = 1 } }, \ */
	/* { MOD, XK_z,     ACTION##stack, {.i = 2 } }, \ */
	/* { MOD, XK_x,     ACTION##stack, {.i = -1 } }, */

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *termcmd[]  = { TERMINAL, NULL };

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
		{ "color0",		STRING,	&normbordercolor },
		{ "color8",		STRING,	&selbordercolor },
		{ "color0",		STRING,	&normbgcolor },
		{ "color4",		STRING,	&normfgcolor },
		{ "color0",		STRING,	&selfgcolor },
		{ "color4",		STRING,	&selbgcolor },
		{ "borderpx",		INTEGER, &borderpx },
		{ "snap",		INTEGER, &snap },
		{ "showbar",		INTEGER, &showbar },
		{ "topbar",		INTEGER, &topbar },
		{ "nmaster",		INTEGER, &nmaster },
		{ "resizehints",	INTEGER, &resizehints },
		{ "mfact",		FLOAT,	&mfact },
		{ "gappih",		INTEGER, &gappih },
		{ "gappiv",		INTEGER, &gappiv },
		{ "gappoh",		INTEGER, &gappoh },
		{ "gappov",		INTEGER, &gappov },
		{ "swallowfloating",	INTEGER, &swallowfloating },
		{ "smartgaps",		INTEGER, &smartgaps },
};

#include <X11/XF86keysym.h>
#include "shiftview.c"

static Key keys[] = {

	STACKKEYS(MODKEY,                          focus)
	STACKKEYS(MODKEY|ShiftMask,                push)
    { MODKEY,           XK_grave,       spawn,      SHCMD("dmenuunicode") },
    TAGKEYS(            XK_1,           0)
    TAGKEYS(            XK_2,           1)
    TAGKEYS(            XK_3,           2)
    TAGKEYS(            XK_4,           3)
    TAGKEYS(            XK_5,           4)
    TAGKEYS(            XK_6,           5)
    TAGKEYS(            XK_7,           6)
    TAGKEYS(            XK_8,           7)
    TAGKEYS(            XK_9,           8)
    { MODKEY,           XK_0,           view,       {.ui = ~0 } },
    { MODKEY|ShiftMask, XK_0,           tag,        {.ui = ~0 } },
    { MODKEY,           XK_minus,       spawn,      SHCMD("pamixer --allow-boost -d 5; kill -44 $(pidof dwmblocks) && pa_notify.sh") },
    { MODKEY|ShiftMask, XK_minus,       spawn,      SHCMD("pamixer --allow-boost -d 15; kill -44 $(pidof dwmblocks) && pa_notify.sh") },
    { MODKEY,           XK_plus,        spawn,      SHCMD("pamixer --allow-boost -i 5; kill -44 $(pidof dwmblocks) && pa_notify.sh") },
    { MODKEY|ShiftMask, XK_plus,        spawn,      SHCMD("pamixer --allow-boost -i 15; kill -44 $(pidof dwmblocks) && pa_notify.sh") },
    { MODKEY,           XK_BackSpace,   spawn,      SHCMD("dwm_exit.sh") },
    { MODKEY|ShiftMask, XK_BackSpace,   spawn,      SHCMD("dwm_exit.sh") },
    { MODKEY,           XK_asciicircum, spawn,      SHCMD("dmenuunicode") },
    { MODKEY,           XK_Tab,         view,       {0} },
    { MODKEY,           XK_q,           killclient, {0} },
    { MODKEY|ShiftMask, XK_q,           spawn,      SHCMD("dwm_exit.sh") },
    { MODKEY,           XK_w,           spawn,      SHCMD("xdo activate -N $BROWSER || $BROWSER") },
    { MODKEY|ShiftMask, XK_w,           spawn,      SHCMD("st -e sudo nmtui") },
    { MODKEY,           XK_e,           spawn,      SHCMD("xdo activate -N Evolution || evolution") },
    { MODKEY,           XK_d,           spawn,      SHCMD("rofi -show-icons -show drun") },
    { MODKEY|ShiftMask, XK_l,           spawn,      SHCMD("betterlockscreen -l '/home/murdoc/ownCloud/Bilder (Kopie)/Hintergrundbilder/trevor-cole-393228.jpg'")},
    { MODKEY|ShiftMask, XK_e,           spawn,      SHCMD("st -e neomutt") },
    { MODKEY,           XK_r,           togglescratch,  {.ui = 2} },
    { MODKEY|ShiftMask, XK_r,           spawn,      SHCMD("st -e btop") },
    { MODKEY,           XK_t,           setlayout,  {.v = &layouts[0]} }, /* tile */
    { MODKEY|ShiftMask, XK_t,           setlayout,  {.v = &layouts[1]} }, /* bstack */
    { MODKEY,           XK_z,           setlayout,  {.v = &layouts[2]} }, /* spiral */
    { MODKEY|ShiftMask, XK_z,           setlayout,  {.v = &layouts[3]} }, /* dwindle */
    { MODKEY,           XK_u,           setlayout,  {.v = &layouts[4]} }, /* deck */
    { MODKEY|ShiftMask, XK_u,           setlayout,  {.v = &layouts[5]} }, /* monocle */
    { MODKEY,           XK_i,           setlayout,  {.v = &layouts[6]} }, /* centeredmaster */
    { MODKEY|ShiftMask, XK_i,           setlayout,  {.v = &layouts[7]} }, /* centeredfloatingmaster */
    { MODKEY,           XK_o,           incnmaster,     {.i = +1 } },
    { MODKEY|ShiftMask, XK_o,           incnmaster,     {.i = -1 } },
    { MODKEY,           XK_p,           spawn,      SHCMD("mpc toggle") },
    { MODKEY|ShiftMask, XK_p,           spawn,      SHCMD("passmenu") },
    { MODKEY,           XK_bracketleft, spawn,      SHCMD("mpc seek -10") },
    { MODKEY|ShiftMask, XK_bracketleft, spawn,      SHCMD("mpc seek -60") },
    { MODKEY,           XK_bracketright,spawn,      SHCMD("mpc seek +10") },
    { MODKEY|ShiftMask, XK_bracketright,spawn,      SHCMD("mpc seek +60") },
    { MODKEY,           XK_backslash,   view,           {0} },
    { MODKEY,           XK_a,           togglegaps,     {0} },
    { MODKEY|ShiftMask, XK_a,           defaultgaps,    {0} },
    { MODKEY,           XK_s,           togglesticky,   {0} },
    { MODKEY|ShiftMask, XK_s,           spawn,     SHCMD("fcmd.sh set EG.WZ.Sofa.Steckdose toggle") },
    { MODKEY,           XK_f,           togglefullscr,  {0} },
    { MODKEY|ShiftMask, XK_f,           setlayout,      {.v = &layouts[8]} },
    { MODKEY,           XK_g,           shiftview,      { .i = -1 } },
    { MODKEY|ShiftMask, XK_g,           shifttag,       { .i = -1 } },
    { MODKEY,           XK_h,           setmfact,       {.f = -0.05} },
    /* J and K are automatically bound above in STACKEYS */
    { MODKEY,           XK_l,           setmfact,       {.f = +0.05} },
    { MODKEY,           XK_semicolon,   shiftview,      { .i = 1 } },
    { MODKEY|ShiftMask, XK_semicolon,   shifttag,       { .i = 1 } },
	{ MODKEY|ShiftMask,	XK_apostrophe,	togglesmartgaps,	{0} },
    { MODKEY,           XK_c,           togglescratch,  {.ui = 1} },
    { MODKEY,           XK_Return,      spawn,          {.v = termcmd } },
    { MODKEY|ShiftMask, XK_Return,      togglescratch,  {.ui = 0} },
    { MODKEY,           XK_y,           incrgaps,       {.i = +3 } },
    { MODKEY|ShiftMask, XK_y,           incrgaps,       {.i = -3 } },
    /* V is automatically bound above in STACKKEYS */
    { MODKEY,           XK_b,           togglebar,      {0} },
    { MODKEY|ShiftMask, XK_b,           spawn,      SHCMD("airpods.sh t") },
    { MODKEY,           XK_n,           spawn,      SHCMD("st -e nvim -u /home/murdoc/.config/nvim/init.vim -c VimwikiIndex") },
    { MODKEY|ShiftMask, XK_n,           spawn,      SHCMD("st -e newsboat; pkill -RTMIN+6 dwmblocks") },
    { MODKEY,           XK_m,           spawn,      SHCMD("alacritty -e ncmpcpp") },
    { MODKEY|ShiftMask, XK_m,           spawn,      SHCMD("pamixer -t; kill -44 $(pidof dwmblocks) && pa_notify.sh") },
    { MODKEY,           XK_comma,       spawn,      SHCMD("mpc prev") },
    { MODKEY|ShiftMask, XK_comma,       spawn,      SHCMD("mpc seek 0%") },
    { MODKEY,           XK_period,      spawn,      SHCMD("mpc next") },
    { MODKEY|ShiftMask, XK_period,      spawn,      SHCMD("mpc repeat") },
    { MODKEY,           XK_Left,        focusmon,   {.i = -1 } },
    { MODKEY|ShiftMask, XK_Left,        tagmon,     {.i = -1 } },
    { MODKEY,           XK_Right,       focusmon,   {.i = +1 } },
    { MODKEY|ShiftMask, XK_Right,       tagmon,     {.i = +1 } },
    { MODKEY,           XK_Page_Up,     shiftview,  { .i = -1 } },
    { MODKEY|ShiftMask, XK_Page_Up,     shifttag,   { .i = -1 } },
    { MODKEY,           XK_Page_Down,   shiftview,  { .i = +1 } },
    { MODKEY|ShiftMask, XK_Page_Down,   shifttag,   { .i = +1 } },
    { MODKEY,           XK_Insert,      spawn,      SHCMD("notify-send \"📋 Clipboard contents:\" \"$(xclip -o -selection clipboard)\"") },
    { MODKEY,           XK_F1,          spawn,      SHCMD("pamixer -t; kill -44 $(pidof dwmblocks) && pa_notify.sh") },
    { MODKEY,           XK_F2,          spawn,      SHCMD("dmenuunicode") },
    { MODKEY,           XK_F3,          spawn,      SHCMD("st -e displayselect.sh") },
    { MODKEY,           XK_F4,          spawn,      SHCMD("st -e pulsemixer; kill -44 $(pidof dwmblocks)") },
    { MODKEY,           XK_F5,          xrdb,       {.v = NULL } },
    { MODKEY,           XK_F6,          spawn,      SHCMD("torwrap") },
    { MODKEY,           XK_F7,          spawn,      SHCMD("td-toggle") },
    { MODKEY,           XK_F8,          spawn,      SHCMD("mailsync") },
    { MODKEY,           XK_F9,          spawn,      SHCMD("dmenumount") },
    { MODKEY,           XK_F10,         spawn,      SHCMD("dmenuumount") },
    { MODKEY,           XK_F11,         spawn,      SHCMD("mpv --no-cache --no-osc --no-input-default-bindings --input-conf=/dev/null --title=webcam $(ls /dev/video[0,2,4,6,8] | tail -n 1)") },
    { MODKEY,           XK_F12,         xrdb,       {.v = NULL } },
    { MODKEY,           XK_space,       zoom,       {0} },
    { MODKEY|ShiftMask, XK_space,       togglefloating, {0} },
    { 0,                XK_Print,       spawn,      SHCMD("maim pic-full-$(date '+%y%m%d-%H%M-%S').png") },
    { ShiftMask,        XK_Print,       spawn,      SHCMD("maimpick") },
    { MODKEY,           XK_Print,       spawn,      SHCMD("dmenurecord.sh") },
    { MODKEY|ShiftMask, XK_Print,       spawn,      SHCMD("dmenurecord.sh kill") },
    { MODKEY,           XK_Delete,      spawn,      SHCMD("dmenurecord.sh kill") },
    { MODKEY,           XK_Scroll_Lock, spawn,      SHCMD("killall screenkey || screenkey &") },
    { 0, XF86XK_AudioMute,              spawn,      SHCMD("pamixer -t; kill -44 $(pidof dwmblocks) && pa_notify.sh") },
    { 0, XF86XK_AudioRaiseVolume,       spawn,      SHCMD("pamixer --allow-boost -i 3; kill -44 $(pidof dwmblocks) && pa_notify.sh") },
    { 0, XF86XK_AudioLowerVolume,       spawn,      SHCMD("pamixer --allow-boost -d 3; kill -44 $(pidof dwmblocks) && pa_notify.sh") },
    { 0, XF86XK_AudioPrev,              spawn,      SHCMD("mpc prev") },
    { 0, XF86XK_AudioNext,              spawn,      SHCMD("mpc next") },
    { 0, XF86XK_AudioPause,             spawn,      SHCMD("mpc pause") },
    { 0, XF86XK_AudioPlay,              spawn,      SHCMD("mpc play") },
    { 0, XF86XK_AudioStop,              spawn,      SHCMD("mpc stop") },
    { 0, XF86XK_AudioRewind,            spawn,      SHCMD("mpc seek -10") },
    { 0, XF86XK_AudioForward,           spawn,      SHCMD("mpc seek +10") },
    { 0, XF86XK_AudioMedia,             spawn,      SHCMD("st -e ncmpcpp") },
    { 0, XF86XK_PowerOff,               spawn,      SHCMD("dwm_exit.sh") },
    { 0, XF86XK_Calculator,             spawn,      SHCMD("st -e bc -l") },
    { 0, XF86XK_Sleep,                  spawn,      SHCMD("sudo -A zzz") },
    { 0, XF86XK_WWW,                    spawn,      SHCMD("$BROWSER") },
    { 0, XF86XK_DOS,                    spawn,      SHCMD("st") },
    { 0, XF86XK_ScreenSaver,            spawn,      SHCMD("slock & xset dpms force off; mpc pause; pauseallmpv") },
    { 0, XF86XK_TaskPane,               spawn,      SHCMD("st -e btop") },
    { 0, XF86XK_Mail,                   spawn,      SHCMD("evolution") },
    { 0, XF86XK_MyComputer,             spawn,      SHCMD("st -e lfrun /") },
    { 0, XF86XK_Launch1,                spawn,      SHCMD("xset dpms force off") },
    { 0, XF86XK_TouchpadToggle,         spawn,      SHCMD("(synclient | grep 'TouchpadOff.*1' && synclient TouchpadOff=0) || synclient TouchpadOff=1") },
    { 0, XF86XK_TouchpadOff,            spawn,      SHCMD("synclient TouchpadOff=1") },
    { 0, XF86XK_TouchpadOn,             spawn,      SHCMD("synclient TouchpadOff=0") },
    { 0, XF86XK_MonBrightnessUp,        spawn,      SHCMD("xbacklight -inc 15 && xbl_notify.sh") },
    { 0, XF86XK_MonBrightnessDown,      spawn,      SHCMD("xbacklight -dec 15 && xbl_notify.sh") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
#ifndef __OpenBSD__
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkStatusText,        0,              Button4,        sigdwmblocks,   {.i = 4} },
	{ ClkStatusText,        0,              Button5,        sigdwmblocks,   {.i = 5} },
	{ ClkStatusText,        ShiftMask,      Button1,        sigdwmblocks,   {.i = 6} },
#endif
	{ ClkStatusText,        ShiftMask,      Button3,        spawn,          SHCMD(TERMINAL " -e nvim ~/.local/src/dwmblocks/config.h") },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        defaultgaps,	{0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkClientWin,		MODKEY,		Button4,	incrgaps,	{.i = +1} },
	{ ClkClientWin,		MODKEY,		Button5,	incrgaps,	{.i = -1} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkTagBar,		0,		Button4,	shiftview,	{.i = -1} },
	{ ClkTagBar,		0,		Button5,	shiftview,	{.i = 1} },
	{ ClkRootWin,		0,		Button2,	togglebar,	{0} },
};

