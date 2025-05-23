/* See LICENSE file for copyright and license details. */

#define TERMINAL "st"
#define TERMCLASS "St"
#define BROWSER "librewolf"
#define EMAIL "proton-mail"
#define YOUTUBE "freetube"
#define STATUSBAR "dwmblocks"

#define SPTAG(i) ((1 << LENGTH(tags)) << (i))

/* appearance */
static unsigned int borderpx  = 5;        /* border pixel of windows */
static unsigned int snap      = 32;       /* snap pixel */
static int showbar            = 1;        /* 0 means no bar */
static int topbar             = 1;        /* 0 means bottom bar */
static char font[]            = "AnonymicePro Nerd Font Mono:pixelsize=15";
static char dmenufont[]       = "AnonymicePro Nerd Font Mono:pixelsize=15";
static const char *fonts[]          = { font };
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
        /* xprop(1):
         *        WM_CLASS(STRING) = instance, class
         *        WM_NAME(STRING) = title
         */
        /* class      instance    title          tags mask     iscentered  isfloating   monitor  float x,y,w,h         floatborderpx  scratch key */
        { NULL,       NULL,       "spterm",      SPTAG(0),     1,          1,           -1,      -1,-1,-1,-1,          5,             's' },
        { NULL,       NULL,       "spcalc",      SPTAG(1),     1,          1,           -1,      -1,-1,-1,-1,          5,             'c' },
};

/* layout(s) */
static float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
        /* symbol     arrange function */
        { "[]=",      tile },    /* first entry is default */
        { "[M]",      monocle },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
        { "><>",      NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
        { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
        { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
		{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
		{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} }, \

#define MONKEYS(KEY,TAG) \
        { MODKEY,                       KEY,      focusnthmon,    {.i  = TAG } }, \
        { MODKEY|ShiftMask,             KEY,      tagnthmon,      {.i  = TAG } },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "st", NULL };

/*First arg only serves to match against key in rules*/
static const char *scratchpadcmd[] = {"s", "st", "-t", "spterm", "-g", "120x34", NULL}; 
static const char *calccmd[] = {"c", "st", "-t", "spcalc", "-g", "50x20", "-e", "bc" , "-lq", NULL}; 

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
                { "font",               STRING,  &font },
                { "dmenufont",          STRING,  &dmenufont },
                { "normbgcolor",        STRING,  &normbgcolor },
                { "normbordercolor",    STRING,  &normbordercolor },
                { "normfgcolor",        STRING,  &normfgcolor },
                { "selbgcolor",         STRING,  &selbgcolor },
                { "selbordercolor",     STRING,  &selbordercolor },
                { "selfgcolor",         STRING,  &selfgcolor },
                { "borderpx",           INTEGER, &borderpx },
                { "snap",               INTEGER, &snap },
                { "showbar",            INTEGER, &showbar },
                { "topbar",             INTEGER, &topbar },
                { "nmaster",            INTEGER, &nmaster },
                { "resizehints",        INTEGER, &resizehints },
                { "mfact",              FLOAT,   &mfact },
};


static const Key keys[] = {
        /*  modifier                      key          function                argument */
/*F1*/  MONKEYS(                          67,                                    0)
/*F2*/  MONKEYS(                          68,                                    1)
/*F3*/  MONKEYS(                          69,                                    2)
/*F4*/  MONKEYS(                          70,                                    3)
/*F5*/  MONKEYS(                          71,                                    4)
/*F6*/  MONKEYS(                          72,                                    5)
/*F7*/  MONKEYS(                          73,                                    6)
/*F8*/  MONKEYS(                          74,                                    7)
/*F9*/  MONKEYS(                          75,                                    8)
/*1*/   TAGKEYS(                          10,                                    0)
/*2*/   TAGKEYS(                          11,                                    1)
/*3*/   TAGKEYS(                          12,                                    2)
/*4*/   TAGKEYS(                          13,                                    3)
/*5*/   TAGKEYS(                          14,                                    4)
/*6*/   TAGKEYS(                          15,                                    5)
/*7*/   TAGKEYS(                          16,                                    6)
/*8*/   TAGKEYS(                          17,                                    7)
/*9*/   TAGKEYS(                          18,                                    8)
/*0*/      {MODKEY,                       19,          view,                   {.ui=~0}},
/*0*/   /* {MODKEY|ControlMask,           19,          noop,                   {}}, */
/*)*/   /* {MODKEY|ShiftMask,             19,          noop,                   {}}, */
/*)*/   /* {MODKEY|ControlMask|ShiftMask, 19,          noop,                   {}}, */
/*-*/      {MODKEY,                       20,          spawn,                  SHCMD("changevol 2%-; kill -44 $(pidof dwmblocks)")}, 
/*-*/   /* {MODKEY|ControlMask,           20,          noop,                   {}}, */
/*_*/      {MODKEY|ShiftMask,             20,          spawn,                  SHCMD("changevol 5%-; kill -44 $(pidof dwmblocks)")}, 
/*_*/   /* {MODKEY|ControlMask|ShiftMask, 20,          noop,                   {}}, */
/*=*/      {MODKEY,                       21,          spawn,                  SHCMD("changevol 2%+; kill -44 $(pidof dwmblocks)")},
/*=*/   /* {MODKEY,                       21,          noop,                   {}}, */
/*=*/   /* {MODKEY|ControlMask,           21,          noop,                   {}}, */
/*+*/      {MODKEY|ShiftMask,             21,          spawn,                   SHCMD("changevol 5%+; kill -44 $(pidof dwmblocks)")}, 
/*+*/   /* {MODKEY|ControlMask|ShiftMask, 21,          noop,                   {}}, */
/*BS*/     {MODKEY,                       22,          spawn,                  {.v = (const char*[]){"sysact", NULL}}},
/*BS*/  /* {MODKEY|ControlMask,           22,          noop,                   {}}, */
/*BS*/     {MODKEY|ShiftMask,             22,          spawn,                  {.v = (const char*[]){"sysact", NULL}}},
/*TAB*/ /* {MODKEY|ControlMask|ShiftMask, 22,          noop,                   {}}, */
/*TAB*/    {MODKEY,                       23,          view,                   {0} },
/*TAB*/ /* {MODKEY|ControlMask,           23,          noop,                   {}}, */
/*TAB*/ /* {MODKEY|ShiftMask,             23,          noop,                   {}}, */
/*BS*/  /* {MODKEY|ControlMask|ShiftMask, 22,          noop,                   {}}, */
/*q*/      {MODKEY,                       24,          killclient,             {0}},
/*q*/   /* {MODKEY|ControlMask,           24,          noop,                   {}}, */
/*Q*/      {MODKEY|ShiftMask,             24,          spawn,                  {.v = (const char*[]){"sysact", NULL}}},
/*Q*/   /* {MODKEY|ControlMask|ShiftMask, 24,          noop,                   {}}, */
/*w*/      {MODKEY,                       25,          spawn,                  {.v = (const char*[]){BROWSER, NULL}}},
/*w*/   /* {MODKEY|ControlMask,           25,          noop,                   {}}, */
/*W*/      {MODKEY|ShiftMask,             25,          spawn,                  {.v = (const char*[]){TERMINAL, "-e", "sudo", "nmtui", NULL}}},
/*W*/   /* {MODKEY|ControlMask|ShiftMask, 25,          noop,                   {}}, */
/*e*/      {MODKEY,                       26,          spawn,                  {.v = (const char*[]){EMAIL, NULL}}},
/*e*/   /* {MODKEY|ControlMask,           26,          noop,                   {}}, */
/*E*/   /* {MODKEY|ShiftMask,             26,          noop,                   {}}, */
/*E*/   /* {MODKEY|ControlMask|ShiftMask, 26,          noop,                   {}}, */
/*r*/   /* {MODKEY,                       27,          noop,                   {}}, */
/*r*/   /* {MODKEY|ControlMask,           27,          noop,                   {}}, */
/*R*/   /* {MODKEY|ShiftMask,             27,          noop,                   {}}, */
/*R*/   /* {MODKEY|ControlMask|ShiftMask, 27,          noop,                   {}}, */
/*t*/      {MODKEY,                       28,          setlayout,              {.v = &layouts[0]}}, /* tile */
/*t*/   /* {MODKEY|ControlMask,           28,          noop,                   {}}, */
/*T*/   /* {MODKEY|ShiftMask,             28,          noop,                   {}}, */
/*T*/   /* {MODKEY|ControlMask|ShiftMask, 28,          noop,                   {}}, */
/*y*/      {MODKEY,                       29,          setlayout,              {.v = &layouts[1]}}, /* monocle */
/*y*/   /* {MODKEY|ControlMask,           29,          noop,                   {}}, */
/*Y*/   /* {MODKEY|ShiftMask,             29,          noop,                   {}}, */
/*Y*/   /* {MODKEY|ControlMask|ShiftMask, 29,          noop,                   {}}, */
/*u*/      {MODKEY,                       30,          setlayout,              {.v = &layouts[2]}}, /* centeredmaster */
/*u*/   /* {MODKEY|ControlMask,           30,          noop,                   {}}, */
/*U*/      {MODKEY|ShiftMask,             30,          setlayout,              {.v = &layouts[3]}}, /* centeredfloatingmaster */
/*U*/   /* {MODKEY|ControlMask|ShiftMask, 30,          noop,                   {}}, */
/*i*/   /* {MODKEY,                       31,          noop,                   {}}, */
/*i*/   /* {MODKEY|ControlMask,           31,          noop,                   {}}, */
/*I*/   /* {MODKEY|ShiftMask,             31,          noop,                   {}}, */
/*I*/   /* {MODKEY|ControlMask|ShiftMask, 31,          noop,                   {}}, */
/*o*/      {MODKEY,                       32,          incnmaster,             {.i = +1}},
/*o*/      {MODKEY|ControlMask,           32,          setcfact,               {.f = 0.00}},
/*O*/      {MODKEY|ShiftMask,             32,          incnmaster,             {.i = -1}},
/*O*/   /* {MODKEY|ControlMask|ShiftMask, 32,          noop,                   {}}, */
/*p*/   /* {MODKEY,                       33,          noop,                   {}}, */
/*p*/   /* {MODKEY|ControlMask,           33,          noop,                   {}}, */
/*P*/   /* {MODKEY|ShiftMask,             33,          noop,                   {}}, */
/*P*/   /* {MODKEY|ControlMask|ShiftMask, 33,          noop,                   {}}, */
/*[*/   /* {MODKEY,                       34,          noop,                   {}}, */
/*[*/   /* {MODKEY|ControlMask,           34,          noop,                   {}}, */
/*{*/   /* {MODKEY|ShiftMask,             34,          noop,                   {}}, */
/*{*/   /* {MODKEY|ControlMask|ShiftMask, 34,          noop,                   {}}, */
/*]*/   /* {MODKEY,                       35,          noop,                   {}}, */
/*]*/   /* {MODKEY|ControlMask,           35,          noop,                   {}}, */
/*}*/   /* {MODKEY|ShiftMask,             35,          noop,                   {}}, */
/*}*/   /* {MODKEY|ControlMask|ShiftMask, 35,          noop,                   {}}, */
/*CR*/     {MODKEY,                       36,          spawn,                  {.v=termcmd}}, 
/*CR*/  /* {MODKEY|ControlMask,           36,          noop,                   {}}, */
/*CR*/     {MODKEY|ShiftMask,             36,          togglescratch,          {.v = scratchpadcmd}},
/*CR*/  /* {MODKEY|ControlMask|ShiftMask, 36,          noop,                   {}}, */
/*a*/   /* {MODKEY,                       38,          noop,                   {}}, */
/*a*/   /* {MODKEY|ControlMask,           38,          noop,                   {}}, */
/*A*/   /* {MODKEY|ShiftMask,             38,          noop,                   {}}, */
/*A*/   /* {MODKEY|ControlMask|ShiftMask, 38,          noop,                   {}}, */
/*s*/   /* {MODKEY,                       39,          noop,                   {}}, */ // TODO sticky
/*s*/   /* {MODKEY|ControlMask,           39,          noop,                   {}}, */
/*S*/   /* {MODKEY|ShiftMask,             39,          noop,                   {}}, */
/*S*/   /* {MODKEY|ControlMask|ShiftMask, 39,          noop,                   {}}, */
/*d*/      {MODKEY,                       40,          spawn,                  {.v = (const char*[]){"dmenu_run", NULL}}},   
/*d*/   /* {MODKEY|ControlMask,           40,          noop,                   {}}, */
/*D*/   /* {MODKEY|ShiftMask,             40,          noop,                   {}}, */
/*D*/   /* {MODKEY|ControlMask|ShiftMask, 40,          noop,                   {}}, */
/*f*/      {MODKEY,                       41,          togglefullscr,          {0}},
/*f*/   /* {MODKEY|ControlMask,           41,          noop,                   {}}, */
/*F*/      {MODKEY|ShiftMask,             41,          spawn,                  {.v = (const char*[]){YOUTUBE, NULL}}}, 
/*F*/   /* {MODKEY|ControlMask|ShiftMask, 41,          noop,                   {}}, */
/*g*/   /* {MODKEY,                       42,          noop,                   {}}, */
/*g*/   /* {MODKEY|ControlMask,           42,          noop,                   {}}, */
/*G*/   /* {MODKEY|ShiftMask,             42,          noop,                   {}}, */
/*G*/   /* {MODKEY|ControlMask|ShiftMask, 42,          noop,                   {}}, */
/*h*/      {MODKEY,                       43,          setmfact,               {.f = -0.01}},
/*h*/   /* {MODKEY|ControlMask,           43,          noop,                   {}}, */
/*H*/      {MODKEY|ShiftMask,             43,          setcfact,               {.f = -0.05}}, 
/*H*/   /* {MODKEY|ControlMask|ShiftMask, 43,          noop,                   {}}, */
/*j*/      {MODKEY,                       44,          focusstack,             {.i = +1}}, 
/*j*/   /* {MODKEY|ControlMask,           44,          noop,                   {}}, */
/*J*/   /* {MODKEY|ShiftMask,             44,          noop,                   {}}, */
/*J*/   /* {MODKEY|ControlMask|ShiftMask, 44,          noop,                   {}}, */
/*k*/      {MODKEY,                       45,          focusstack,             {.i = -1}},
/*k*/   /* {MODKEY|ControlMask,           45,          noop,                   {}}, */
/*K*/   /* {MODKEY|ShiftMask,             45,          noop,                   {}}, */
/*K*/   /* {MODKEY|ControlMask|ShiftMask, 45,          noop,                   {}}, */
/*l*/      {MODKEY,                       46,          setmfact,               {.f = +0.01}},
/*l*/   /* {MODKEY|ControlMask,           46,          noop,                   {}}, */
/*L*/      {MODKEY|ShiftMask,             46,          setcfact,               {.f = +0.05}}, 
/*L*/   /* {MODKEY|ControlMask|ShiftMask, 46,          noop,                   {}}, */
/*;*/   /* {MODKEY,                       47,          noop,                   {}}, */
/*;*/   /* {MODKEY|ControlMask,           47,          noop,                   {}}, */
/*:*/   /* {MODKEY|ShiftMask,             47,          noop,                   {}}, */
/*:*/   /* {MODKEY|ControlMask|ShiftMask, 47,          noop,                   {}}, */
/*'*/      {MODKEY,                       48,          togglescratch,          {.v = calccmd}},
/*'*/   /* {MODKEY|ControlMask,           48,          noop,                   {}}, */
/*"*/   /* {MODKEY|ShiftMask,             48,          noop,                   {}}, */
/*"*/   /* {MODKEY|ControlMask|ShiftMask, 48,          noop,                   {}}, */
/*`*/   /* {MODKEY,                       49,          noop,                   {}}, */
/*`*/   /* {MODKEY|ControlMask,           49,          noop,                   {}}, */
/*~*/   /* {MODKEY|ShiftMask,             49,          noop,                   {}}, */
/*~*/   /* {MODKEY|ControlMask|ShiftMask, 49,          noop,                   {}}, */
/*z*/   /* {MODKEY,                       52,          noop,                   {}}, */
/*z*/   /* {MODKEY|ControlMask,           52,          noop,                   {}}, */
/*Z*/   /* {MODKEY|ShiftMask,             52,          noop,                   {}}, */
/*Z*/   /* {MODKEY|ControlMask|ShiftMask, 52,          noop,                   {}}, */
/*x*/   /* {MODKEY,                       53,          noop,                   {}}, */
/*x*/   /* {MODKEY|ControlMask,           53,          noop,                   {}}, */
/*X*/   /* {MODKEY|ShiftMask,             53,          noop,                   {}}, */
/*X*/   /* {MODKEY|ControlMask|ShiftMask, 53,          noop,                   {}}, */
/*c*/   /* {MODKEY,                       54,          noop,                   {}}, */
/*c*/   /* {MODKEY|ControlMask,           54,          noop,                   {}}, */
/*C*/   /* {MODKEY|ShiftMask,             54,          noop,                   {}}, */
/*C*/   /* {MODKEY|ControlMask|ShiftMask, 54,          noop,                   {}}, */
/*v*/   /* {MODKEY,                       55,          noop,                   {}}, */
/*v*/   /* {MODKEY|ControlMask,           55,          noop,                   {}}, */
/*V*/   /* {MODKEY|ShiftMask,             55,          noop,                   {}}, */
/*V*/   /* {MODKEY|ControlMask|ShiftMask, 55,          noop,                   {}}, */
/*b*/      {MODKEY,                       56,          togglebar,              {0}},
/*b*/   /* {MODKEY|ControlMask,           56,          noop,                   {}}, */
/*B*/   /* {MODKEY|ShiftMask,             56,          noop,                   {}}, */
/*B*/   /* {MODKEY|ControlMask|ShiftMask, 56,          noop,                   {}}, */
/*n*/   /* {MODKEY,                       57,          noop,                   {}}, */
/*n*/   /* {MODKEY|ControlMask,           57,          noop,                   {}}, */
/*N*/   /* {MODKEY|ShiftMask,             57,          noop,                   {}}, */
/*N*/   /* {MODKEY|ControlMask|ShiftMask, 57,          noop,                   {}}, */
/*m*/   /* {MODKEY,                       58,          noop,                   {}}, */
/*m*/   /* {MODKEY|ControlMask,           58,          noop,                   {}}, */
/*M*/   /* {MODKEY|ShiftMask,             58,          noop,                   {}}, */
/*M*/   /* {MODKEY|ControlMask|ShiftMask, 58,          noop,                   {}}, */
/*,*/      {MODKEY,                       59,          spawn,                  {.v = (const char*[]){"mpc", "prev", NULL}}},
/*,*/   /* {MODKEY|ControlMask,           59,          noop,                   {}}, */
/*<*/      {MODKEY|ShiftMask,             59,          spawn,                  {.v = (const char*[]){"mpc", "seek", "0%", NULL}}},
/*<*/   /* {MODKEY|ControlMask|ShiftMask, 59,          noop,                   {}}, */
/*.*/      {MODKEY,                       60,          spawn,                  {.v = (const char*[]){"mpc", "next", NULL}}},
/*.*/   /* {MODKEY|ControlMask,           60,          noop,                   {}}, */
/*>*/      {MODKEY|ShiftMask,             60,          spawn,                  {.v = (const char*[]){"mpc", "repeat", NULL}}},
/*>*/   /* {MODKEY|ControlMask|ShiftMask, 60,          noop,                   {}}, */
/*/*/   /* {MODKEY,                       61,          noop,                   {}}, */
/*/*/   /* {MODKEY|ControlMask,           61,          noop,                   {}}, */
/*?*/   /* {MODKEY|ShiftMask,             61,          noop,                   {}}, */
/*?*/   /* {MODKEY|ControlMask|ShiftMask, 61,          noop,                   {}}, */
/* */      {MODKEY,                       65,          zoom,                   {0}},
/* */   /* {MODKEY|ControlMask,           65,          noop,                   {}}, */
/* */      {MODKEY|ShiftMask,             65,          togglefloating,         {0}},
/* */   /* {MODKEY|ControlMask|ShiftMask, 65,          noop,                   {}}, */
/*F1*/  /* {0,                            67,          noop,                   {}}, */
/*F1*/  /* {0|ControlMask,                67,          noop,                   {}}, */
/*F1*/  /* {0|ShiftMask,                  67,          noop,                   {}}, */
/*F1*/  /* {0|ControlMask|ShiftMask,      67,          noop,                   {}}, */
/*F2*/  /* {0,                            68,          noop,                   {}}, */
/*F2*/  /* {0|ControlMask,                68,          noop,                   {}}, */
/*F2*/  /* {0|ShiftMask,                  68,          noop,                   {}}, */
/*F2*/  /* {0|ControlMask|ShiftMask,      68,          noop,                   {}}, */
/*F3*/     {0,                            69,          spawn,                  {.v = (const char*[]){"displayselect", NULL}}},
/*F3*/  /* {0|ControlMask,                69,          noop,                   {}}, */
/*F3*/  /* {0|ShiftMask,                  69,          noop,                   {}}, */
/*F3*/  /* {0|ControlMask|ShiftMask,      69,          noop,                   {}}, */
/*PS*/     {0,                            107,         spawn,                  SHCMD("maim pic-full-$(date '+%y%m%d-%H%M-%S').png")},
/*PS*/     {ShiftMask,                    107,         spawn,                  {.v = (const char*[]){"maimpick", NULL}}},
/*PS*/     {MODKEY,                       107,         spawn,                  {.v = (const char*[]){"dmenurecord", NULL}}},
/*PS*/     {MODKEY|ShiftMask,             107,         spawn,                  {.v = (const char*[]){"dmenurecord", "kill", NULL}}},
/*->*/     {MODKEY,                       113,         focusmon,               {.i = -1}},
/*->*/  /* {MODKEY|ControlMask,           113,         noop,                   {}}, */
/*->*/     {MODKEY|ShiftMask,             113,         tagmon,                 {.i = -1}},
/*->*/  /* {MODKEY|ControlMask|ShiftMask, 113,         noop,                   {}}, */
/*<-*/     {MODKEY,                       114,         focusmon,               {.i = +1}},
/*<-*/  /* {MODKEY|ControlMask,           114,         noop,                   {}}, */
/*<-*/     {MODKEY|ShiftMask,             114,         tagmon,                 {.i = +1}},
/*<-*/  /* {MODKEY|ControlMask|ShiftMask, 114,         noop,                   {}}, */
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
        { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
        { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
        { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
        { ClkTagBar,            0,              Button1,        view,           {0} },
        { ClkTagBar,            0,              Button3,        toggleview,     {0} },
        { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
        { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

