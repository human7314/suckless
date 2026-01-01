/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 20;       /* snap pixel */
static const unsigned int gappx     = 5;        /* gaps between windows */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 20;        /* 2 is the default spacing around the bar's font */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 3;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */

static const char *fonts[]          = { "JetBrainsMono Nerd Font:size=11", "Noto Color Emoji:size=11" };

#define ICONSIZE 16   /* icon size */
#define ICONSPACING 5 /* space between icon and title */

/* colours */

static char normfgcolor[]      = "#A6ADC8";
static char normbgcolor[]      = "#1E1E2E";
static char normbordercolor[]  = "#A6ADC8";

static char selfgcolor[]       = "#CDD6F4";
static char selbgcolor[]       = "#1E1E2E";
static char selbordercolor[]   = "#89B4FA";

static char statusfgcolor[]    = "#eed49f";
static char statusbgcolor[]    = "#1E1E2E";

static char tagsselcolor[]     = "#eed49f";
static char tagsnormcolor[]    = "#A6ADC8";
static char infofgcolor[]      = "#CDD6F4";
static char infonormcolor[]    = "#A6ADC8";

/* Colors array */
static char *colors[][3] = {
    [SchemeNorm]     = { normfgcolor, normbgcolor, normbordercolor },
    [SchemeSel]      = { selfgcolor,  selbgcolor,  selbordercolor  },
    [SchemeStatus]   = { statusfgcolor, statusbgcolor, "#000000"   },
    [SchemeTagsSel]  = { tagsselcolor, normbgcolor,   "#000000"    },
    [SchemeTagsNorm] = { tagsnormcolor, normbgcolor, "#000000"     },
    [SchemeInfoSel]  = { infofgcolor,  normbgcolor, "#000000"      },
    [SchemeInfoNorm] = { infonormcolor, normbgcolor, "#000000"     },
};

/* tagging */
/* static const char *tags[] = { "一", "二", "三", "四", "五", "六", "七", "八", "九" }; */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "" };

/* Rules */

#define RULE(...){ __VA_ARGS__ },

static const Rule rules[] = {
    
    /* Terminal */
	RULE(.class = "st-256color", .isterminal = 1, .tags = 1 << 0, .switchtotag = 1)
	
    /* Browser */
    RULE(.class = "firefox", .tags = 1 << 1, .switchtotag = 1)
   	RULE(.class = "Chromium", .tags = 1 << 1, .switchtotag = 1)
    RULE(.class = "Thorium-browser", .tags = 1 << 1, .switchtotag = 1)
	
    /* Nvidia */
    RULE(.class = "Nvidia-settings", .isfloating = 1)

    /* Volume control */
	RULE(.class = "pavucontrol", .isfloating = 1)
	RULE(.class = "Pavucontrol", .isfloating = 1)

    /* Explorer */
	RULE(.class = "Nemo", .tags = 1 << 2, .switchtotag = 1)
	RULE(.class = "Pcmanfm", .tags = 1 << 2, .switchtotag = 1)
    
    /* Telegram */
	RULE(.class = "TelegramDesktop", .tags = 1 << 4, .switchtotag = 1)
	RULE(.class = "materialgram", .tags = 1 << 4, .switchtotag = 1)

    /* Music */
    RULE(.class = "com.github.th_ch.youtube_music", .tags = 1 << 3, .switchtotag = 1)

    /* Wallpaper */
    RULE(.class = "Nitrogen", .isfloating = 1)

    /* VLC */
    RULE(.class = "Vlc", .isfloating = 1)
    RULE(.class = "mpv", .tags = 1 << 3, .switchtotag = 1)

    /* Calculator */
    RULE(.class = "Galculator", .isfloating = 1)

    /* Discord */
    RULE(.class = "discord", .tags = 1 << 5, .switchtotag = 1)
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "",      tile },    /* first entry is default */
	{ "",      NULL },    /* no layout function means floating behavior */
	{ "",      monocle },
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

#define STATUSBAR "dwmblocks"

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", NULL };
static const char *termcmd[]  = { "st", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,             		    XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_p,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,             		    XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY,                       XK_F5,     xrdb,           {.v = NULL } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
	{ ClkStatusText,        0,              Button4,        sigstatusbar,   {.i = 4} },
	{ ClkStatusText,        0,              Button5,        sigstatusbar,   {.i = 5} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
