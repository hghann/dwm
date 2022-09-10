/* See LICENSE file for copyright and license details. */

/* constant(s) */
#define TERMINAL "st"
#define TERMCLASS "St"
#define BROWSER "librewolf"

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 4;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]     = { "SauceCodePro Nerd Font Mono:weight=bold:size=11:antialias=true:hinting=true",
                                   "Mononoki:size=11:antialias=true:autohint=true",
                                   "Hack:size=10:antialias=true:autohint=true",
                                   "JoyPixels:size=12:antialias=true:autohint=true" };
static const char col_gray1[]       = "#282c34"; /* bar bg color */
static const char col_gray2[]       = "#282c34"; /* unfocosed window border*/
static const char col_gray3[]       = "#bbc2cf";
static const char col_gray4[]       = "#924441"; /* focosed window border and tags*/
static const char col_gray5[]       = "#8aadf4";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray3, col_gray4, col_gray2 },
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {"st", "-n", "spterm", "-g", "120x34", NULL };
const char *spcmd2[] = {"st", "-n", "spfm", "-g", "120x34", "-e", "lf", NULL };
const char *spcmd3[] = {"keepassxc", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
	{"spfm",        spcmd2},
	{"keepassxc",   spcmd3},
};

/* tagging */
static const char *tags[] = { "dev", "www", "sys", "doc", "vbox", "chat", "mus", "vid", "gfx" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class    instance    title    tags mask    isfloating    isterminal    noswallow   monitor */
	{ "Gimp",   NULL,       NULL,    1 << 8,      0,            0,            0,          -1 },
	{ BROWSER,  NULL,       NULL,    1 << 1,      0,            0,            0,          -1 },
	{ "libreoffice", NULL,  NULL,    1 << 3,      0,            0,            0,          -1 },
	{ TERMCLASS, NULL,      NULL,    0,           0,            1,            0,          -1 },
	{ NULL,     NULL,       "Event Tester", 0,    0,            0,            1,          -1 },
	{ NULL,     "spterm",   NULL,    SPTAG(0),    1,            1,            0,          -1 },
	{ NULL,     "spfm",     NULL,    SPTAG(1),    1,            1,            0,          -1 },
	{ NULL,     "keepassxc", NULL,   SPTAG(2),    1,            0,            0,          -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

#include "fibonacci.c"
#include "layouts.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "HHH",      grid },
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
static const char *dmenucmd[]    = { "dmenu_run", "-g", "10", "-l", "10", "-p", "Run: ", NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *tabtermcmd[]  = { "tabbed", "-r", "2", "st", "-w", "''", NULL };
static const char *mutecmd[] = { "change_volume.sh", "mute", NULL };
static const char *volupcmd[] = { "change_volume.sh", "up", NULL };
static const char *voldowncmd[] = { "change_volume.sh", "down", NULL };
static const char *brupcmd[] = { "screen_brightness.sh", "up", NULL };
static const char *brdowncmd[] = { "screen_brightness.sh", "down", NULL };
static const char *blupcmd[] = { "keyboard_backlight.sh", "up", NULL };
static const char *bldowncmd[] = { "keyboard_backlight.sh", "down", NULL };
static const char *screenshotcmd[] = { "flameshot", "gui", NULL };

#include "shiftview.c"
#include "movestack.c"
#include "selfrestart.c"
static Key keys[] = {
	/* modifier                     key                 function            argument */
	TAGKEYS(                        XK_1,                                   0)
	TAGKEYS(                        XK_2,                                   1)
	TAGKEYS(                        XK_3,                                   2)
	TAGKEYS(                        XK_4,                                   3)
	TAGKEYS(                        XK_5,                                   4)
	TAGKEYS(                        XK_6,                                   5)
	TAGKEYS(                        XK_7,                                   6)
	TAGKEYS(                        XK_8,                                   7)
	TAGKEYS(                        XK_9,                                   8)
	{ MODKEY,                       XK_d,               spawn,              {.v = dmenucmd } },
	{ MODKEY,                       XK_Return,          spawn,              {.v = termcmd } },
	{ Mod1Mask,                     XK_Return,          spawn,              {.v = tabtermcmd } },
	{ MODKEY,                       XK_w,               spawn,              SHCMD("$BROWSER") },
	{ MODKEY,                       XK_r,               spawn,              SHCMD(TERMINAL " -e /usr/local/bin/lfrun") },
	{ MODKEY,                       XK_e,               spawn,              SHCMD("~/.local/bin/dmenuunicode") },
	{ MODKEY|ShiftMask,             XK_r,               spawn,              SHCMD(TERMINAL " -g 120x34 -e htop") },
	{ MODKEY,                       XK_n,               spawn,              SHCMD(TERMINAL " -e nmtui") },
	{ MODKEY|ShiftMask,             XK_n,               spawn,              SHCMD(TERMINAL " -e newsboat") },
	{ MODKEY|ShiftMask,             XK_b,               togglebar,          {0} },
	{ MODKEY,                       XK_j,               focusstack,         {.i = +1 } },
	{ MODKEY,                       XK_k,               focusstack,         {.i = -1 } },
	{ MODKEY,                       XK_i,               incnmaster,         {.i = +1 } },
	{ MODKEY,                       XK_u,               incnmaster,         {.i = -1 } },
	{ MODKEY,                       XK_h,               setmfact,           {.f = -.05} },
	{ MODKEY,                       XK_l,               setmfact,           {.f = +.05} },
	{ MODKEY,                       XK_Return,          zoom,               {0} },
	{ MODKEY,                       XK_q,               killclient,         {0} },
	{ MODKEY,                       XK_t,               setlayout,          {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,               setlayout,          {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,               setlayout,          {.v = &layouts[2]} },
	{ MODKEY,                       XK_s,               setlayout,          {.v = &layouts[3]} },
	{ MODKEY,                       XK_u,               setlayout,          {.v = &layouts[4]} },
	{ MODKEY,                       XK_g,               setlayout,          {.v = &layouts[5]} },
	{ MODKEY,                       XK_space,           setlayout,          {0} },
	{ MODKEY|ShiftMask,             XK_space,           togglefloating,     {0} },
	{ MODKEY|ShiftMask,             XK_s,               togglesticky,       {0} },
	{ MODKEY|ShiftMask,             XK_f,               togglefullscr,      {0} },
	{ MODKEY|ShiftMask,             XK_Return,          togglescratch,      {.ui = 0 } },
	{ MODKEY|ShiftMask,             XK_apostrophe,      togglescratch,      {.ui = 1 } },
	{ MODKEY|ShiftMask,             XK_v,               togglescratch,      {.ui = 2 } },
	{ MODKEY,                       XK_0,               view,               {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,               tag,                {.ui = ~0 } },
	{ MODKEY,                       XK_comma,           focusmon,           {.i = -1 } },
	{ MODKEY,                       XK_period,          focusmon,           {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,           tagmon,             {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,          tagmon,             {.i = +1 } },
	{ MODKEY,                       XK_bracketleft,     shiftview,          {.i = -1 } },
	{ MODKEY,                       XK_bracketright,    shiftview,          {.i = +1 } },
	{ MODKEY,                       XK_backslash,       view,               {0} },
	{ MODKEY,                       XK_Tab,             view,               {0} },
	{ MODKEY|ShiftMask,             XK_k,               movestack,          {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,               movestack,          {.i = +1 } },
	{ MODKEY,                       XK_z,               setgaps,            {.i = -1 } },
	{ MODKEY,                       XK_x,               setgaps,            {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_a,               setgaps,            {.i = 0  } },
	{ Mod1Mask|ShiftMask,           XK_q,               quit,               {0} },
	{ MODKEY|ShiftMask,             XK_q,               self_restart,       {0} },
	{ Mod1Mask|ShiftMask,           XK_3,               spawn,              SHCMD("scrotFull") },
	{ Mod1Mask|ShiftMask,           XK_4,               spawn,              SHCMD("scrotSection") },
	{ Mod1Mask|ShiftMask,           XK_5,               spawn,              {.v = screenshotcmd} },
	{ 0, XF86XK_AudioMute,                              spawn,              {.v = mutecmd} },
	{ 0, XF86XK_AudioRaiseVolume,                       spawn,              {.v = volupcmd } },
	{ 0, XF86XK_AudioLowerVolume,                       spawn,              {.v = voldowncmd } },
	{ 0, XF86XK_MonBrightnessUp,                        spawn,              {.v = brupcmd} },
	{ 0, XF86XK_MonBrightnessDown,                      spawn,              {.v = brdowncmd} },
	{ 0, XF86XK_KbdBrightnessUp,                        spawn,              {.v = blupcmd} },
	{ 0, XF86XK_KbdBrightnessDown,                      spawn,              {.v = bldowncmd} },
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
	{ ClkStatusText,        ShiftMask,      Button3,        spawn,          SHCMD(TERMINAL " -e vim ~/.local/src/dwmblocks/config.h") },
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
