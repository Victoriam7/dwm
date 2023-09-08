/* See LICENSE file for copyright and license details. */

#define TERMINAL "st"
#define TERMCLASS "St"
#define BROWSER "librewolf"

/* appearance */
static unsigned int borderpx  = 1;        /* border pixel of windows */
static unsigned int snap      = 32;       /* snap pixel */
static int showbar            = 1;        /* 0 means no bar */
static int topbar             = 1;        /* 0 means bottom bar */
static char font[]            = "monospace:size=10";
static char dmenufont[]       = "monospace:size=10";
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
        /* class      instance    title       tags mask     isfloating   monitor */
        { "Gimp",     NULL,       NULL,       0,            1,           -1 },
        { "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
        /* symbol     arrange function */
        { "[]=",      tile },    /* first entry is default */
        { "><>",      NULL },    /* no layout function means floating behavior */
        { "[M]",      monocle },
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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "st", NULL };

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
#if 0
	/* modifier                        key              function                argument */
	/* { MODKEY,                       XK_a,            noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_a,            noop,                   {} }, */
	/* { MODKEY,                       XK_A,            noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_A,            noop,                   {} }, */
	/* { MODKEY,                       XK_b,            noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_b,            noop,                   {} }, */
	/* { MODKEY,                       XK_B,            noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_B,            noop,                   {} }, */
	/* { MODKEY,                       XK_c,            noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_c,            noop,                   {} }, */
	/* { MODKEY,                       XK_C,            noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_C,            noop,                   {} }, */
	/* { MODKEY,                       XK_d,            noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_d,            noop,                   {} }, */
	/* { MODKEY,                       XK_D,            noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_D,            noop,                   {} }, */
	/* { MODKEY,                       XK_e,            noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_e,            noop,                   {} }, */
	/* { MODKEY,                       XK_E,            noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_E,            noop,                   {} }, */
	/* { MODKEY,                       XK_g,            noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_g,            noop,                   {} }, */
	/* { MODKEY,                       XK_G,            noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_G,            noop,                   {} }, */
	/* { MODKEY,                       XK_h,            noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_h,            noop,                   {} }, */
	/* { MODKEY,                       XK_H,            noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_H,            noop,                   {} }, */
	/* { MODKEY,                       XK_i,            noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_i,            noop,                   {} }, */
	/* { MODKEY,                       XK_I,            noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_I,            noop,                   {} }, */
	   { MODKEY,                       XK_j,            focusstack,             {.i = INC(+1)} }, 
	/* { MODKEY|ControlMask,           XK_j,            noop,                   {} }, */
	   { MODKEY,                       XK_J,            pushstack,              {.i = INC(+1)} },
	/* { MODKEY|ControlMask,           XK_J,            noop,                   {} }, */
	   { MODKEY,                       XK_k,            focusstack,             {.i = INC(-1)} },
	/* { MODKEY|ControlMask,           XK_k,            noop,                   {} }, */
	   { MODKEY,                       XK_K,            pushstack,              {.i = INC(-1)} },
	/* { MODKEY|ControlMask,           XK_K,            noop,                   {} }, */
	/* { MODKEY,                       XK_l,            noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_l,            noop,                   {} }, */
	/* { MODKEY,                       XK_L,            noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_L,            noop,                   {} }, */
	/* { MODKEY,                       XK_m,            noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_m,            noop,                   {} }, */
	/* { MODKEY,                       XK_M,            noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_M,            noop,                   {} }, */
	/* { MODKEY,                       XK_n,            noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_n,            noop,                   {} }, */
	/* { MODKEY,                       XK_N,            noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_N,            noop,                   {} }, */
	/* { MODKEY,                       XK_o,            noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_o,            noop,                   {} }, */
	/* { MODKEY,                       XK_O,            noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_O,            noop,                   {} }, */
	/* { MODKEY,                       XK_p,            noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_p,            noop,                   {} }, */
	/* { MODKEY,                       XK_P,            noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_P,            noop,                   {} }, */
	/* { MODKEY,                       XK_q,            noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_q,            noop,                   {} }, */
	/* { MODKEY,                       XK_Q,            noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_Q,            noop,                   {} }, */
	/* { MODKEY,                       XK_r,            noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_r,            noop,                   {} }, */
	/* { MODKEY,                       XK_R,            noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_R,            noop,                   {} }, */
	/* { MODKEY,                       XK_s,            noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_s,            noop,                   {} }, */
	/* { MODKEY,                       XK_S,            noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_S,            noop,                   {} }, */
	/* { MODKEY,                       XK_t,            noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_t,            noop,                   {} }, */
	/* { MODKEY,                       XK_T,            noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_T,            noop,                   {} }, */
	/* { MODKEY,                       XK_u,            noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_u,            noop,                   {} }, */
	/* { MODKEY,                       XK_U,            noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_U,            noop,                   {} }, */
	/* { MODKEY,                       XK_v,            noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_v,            noop,                   {} }, */
	/* { MODKEY,                       XK_V,            noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_V,            noop,                   {} }, */
	/* { MODKEY,                       XK_w,            noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_w,            noop,                   {} }, */
	/* { MODKEY,                       XK_W,            noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_W,            noop,                   {} }, */
	/* { MODKEY,                       XK_x,            noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_x,            noop,                   {} }, */
	/* { MODKEY,                       XK_X,            noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_X,            noop,                   {} }, */
	/* { MODKEY,                       XK_y,            noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_y,            noop,                   {} }, */
	/* { MODKEY,                       XK_Y,            noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_Y,            noop,                   {} }, */
	/* { MODKEY,                       XK_z,            noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_z,            noop,                   {} }, */
	/* { MODKEY,                       XK_Z,            noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_Z,            noop,                   {} }, */
	/* { MODKEY,                       XK_BackSpace,    noop,                   {} }, */
	/* { MODKEY|ShiftMask,             XK_BackSpace,    noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_BackSpace,    noop,                   {} }, */
	/* { MODKEY|ControlMask|ShiftMask, XK_BackSpace,    noop,                   {} }, */
	/* { MODKEY,                       XK_Tab,          noop,                   {} }, */
	/* { MODKEY|ShiftMask,             XK_Tab,          noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_Tab,          noop,                   {} }, */
	/* { MODKEY|ControlMask|ShiftMask, XK_Tab,          noop,                   {} }, */
	   { MODKEY,                       XK_Return,       spawn,                  {.v=termcmd} }, 
	   { MODKEY|ShiftMask,             XK_Return,       togglescratch,          {.ui=0} }, 
	/* { MODKEY|ControlMask,           XK_Return,       noop,                   {} }, */
	/* { MODKEY|ControlMask|ShiftMask, XK_Return,       noop,                   {} }, */
	/* { MODKEY,                       XK_Delete,       noop,                   {} }, */
	/* { MODKEY|ShiftMask,             XK_Delete,       noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_Delete,       noop,                   {} }, */
	/* { MODKEY|ControlMask|ShiftMask, XK_Delete,       noop,                   {} }, */
	   { MODKEY,                       XK_Left,         focusmon,               {.i = -1} },
	   { MODKEY|ShiftMask,             XK_Left,         tagmon,                 {.i = -1} },
	/* { MODKEY|ControlMask,           XK_Left,         noop,                   {} }, */
	/* { MODKEY|ControlMask|ShiftMask, XK_Left,         noop,                   {} }, */
	/* { MODKEY,                       XK_Up,           noop,                   {} }, */
	/* { MODKEY|ShiftMask,             XK_Up,           noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_Up,           noop,                   {} }, */
	/* { MODKEY|ControlMask|ShiftMask, XK_Up,           noop,                   {} }, */
	   { MODKEY,                       XK_Right,        focusmon,               {.i = +1} },
	   { MODKEY|ShiftMask,             XK_Right,        tagmon,                 {.i = +1} },
	/* { MODKEY|ControlMask,           XK_Right,        noop,                   {} }, */
	/* { MODKEY|ControlMask|ShiftMask, XK_Right,        noop,                   {} }, */
	/* { MODKEY,                       XK_Down,         noop,                   {} }, */
	/* { MODKEY|ShiftMask,             XK_Down,         noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_Down,         noop,                   {} }, */
	/* { MODKEY|ControlMask|ShiftMask, XK_Down,         noop,                   {} }, */
	   { MODKEY,                       XK_space,        zoom,                   {0} },
	   { MODKEY|ShiftMask,             XK_space,        togglefloating,         {0} },
	/* { MODKEY|ControlMask,           XK_space,        noop,                   {} }, */
	/* { MODKEY|ControlMask|ShiftMask, XK_space,        noop,                   {} }, */
	/* { MODKEY,                       XK_semicolon,    noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_semicolon,    noop,                   {} }, */
	/* { MODKEY,                       XK_colon,        noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_colon,        noop,                   {} }, */
	/* { MODKEY,                       XK_comma,        noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_comma,        noop,                   {} }, */
	/* { MODKEY,                       XK_less,         noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_less          noop,                   {} }, */
	/* { MODKEY,                       XK_period,       noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_period,       noop,                   {} }, */
	/* { MODKEY,                       XK_greater,      noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_greater,      noop,                   {} }, */
	/* { MODKEY,                       XK_slash,        noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_slash,        noop,                   {} }, */
	/* { MODKEY,                       XK_question,     noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_question,     noop,                   {} }, */
	/* { MODKEY,                       XK_at,           noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_at,           noop,                   {} }, */
	/* { MODKEY,                       XK_asciicircum,  noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_asciicircum,  noop,                   {} }, */
	/* { MODKEY,                       XK_backslash,    noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_backslash,    noop,                   {} }, */
	/* { MODKEY,                       XK_bar,          noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_bar,          noop,                   {} }, */
	   { MODKEY,                       XK_minus,        spawn,                  SHCMD("changevol -2%; kill -44 $(pidof dwmblocks)") }, 
	/* { MODKEY|ControlMask,           XK_minus,        noop,                   {} }, */
	/* { MODKEY,                       XK_underscore,   noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_underscore,   noop,                   {} }, */
	/* { MODKEY,                       XK_apostrophe,   noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_apostrophe,   noop,                   {} }, */
	   { MODKEY,                       XK_quotedbl,     togglescratch,          {.ui=1} },
	/* { MODKEY|ControlMask,           XK_quotedbl,     noop,                   {} }, */
	/* { MODKEY,                       XK_dollar,       noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_dollar,       noop,                   {} }, */
	/* { MODKEY,                       XK_asciitilde,   noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_asciitilde,   noop,                   {} }, */
	/* { MODKEY,                       XK_ampersand,    noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_ampersand,    noop,                   {} }, */
	/* { MODKEY,                       XK_percent,      noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_percent,      noop,                   {} }, */
	/* { MODKEY,                       XK_bracketleft,  noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_bracketleft,  noop,                   {} }, */
	/* { MODKEY,                       XK_braceleft,    noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_braceleft,    noop,                   {} }, */
	/* { MODKEY,                       XK_braceright,   noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_braceright,   noop,                   {} }, */
	/* { MODKEY,                       XK_parenleft,    noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_parenleft,    noop,                   {} }, */
	/* { MODKEY,                       XK_equal,        noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_equal,        noop,                   {} }, */
	/* { MODKEY,                       XK_astrisk,      noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_astrisk,      noop,                   {} }, */
	/* { MODKEY,                       XK_parenright,   noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_parenright,   noop,                   {} }, */
	   { MODKEY,                       XK_plus,         spawn,                  SHCMD("changevol +2%; kill -44 $(pidof dwmblocks)") },
        /* { MODKEY|ControlMask,           XK_plus,         noop,                   {} }, */
	/* { MODKEY,                       XK_bracketright, noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_bracketright, noop,                   {} }, */
	/* { MODKEY,                       XK_exclam,       noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_exclam,       noop,                   {} }, */
	/* { MODKEY,                       XK_numbersign,   noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_numbersign,   noop,                   {} }, */
	   { MODKEY,                       XK_grave,        spawn,                  {.v=(const char*[]){"dmenuunicode", NULL}} },
	/* { MODKEY|ControlMask,           XK_grave,        noop,                   {} }, */
	/* { MODKEY,                       XK_F1,           noop,                   {} }, */
	/* { MODKEY|ShiftMask,             XK_F1,           noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_F1,           noop,                   {} }, */
	/* { MODKEY|ControlMask|ShiftMask, XK_F1,           noop,                   {} }, */
	/* { MODKEY,                       XK_F2,           noop,                   {} }, */
	/* { MODKEY|ShiftMask,             XK_F2,           noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_F2,           noop,                   {} }, */
	/* { MODKEY|ControlMask|ShiftMask, XK_F2,           noop,                   {} }, */
	/* { MODKEY,                       XK_F3,           noop,                   {} }, */
	/* { MODKEY|ShiftMask,             XK_F3,           noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_F3,           noop,                   {} }, */
	/* { MODKEY|ControlMask|ShiftMask, XK_F3,           noop,                   {} }, */
	/* { MODKEY,                       XK_F4,           noop,                   {} }, */
	/* { MODKEY|ShiftMask,             XK_F4,           noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_F4,           noop,                   {} }, */
	/* { MODKEY|ControlMask|ShiftMask, XK_F4,           noop,                   {} }, */
	/* { MODKEY,                       XK_F5,           noop,                   {} }, */
	/* { MODKEY|ShiftMask,             XK_F5,           noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_F5,           noop,                   {} }, */
	/* { MODKEY|ControlMask|ShiftMask, XK_F5,           noop,                   {} }, */
	/* { MODKEY,                       XK_F6,           noop,                   {} }, */
	/* { MODKEY|ShiftMask,             XK_F6,           noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_F6,           noop,                   {} }, */
	/* { MODKEY|ControlMask|ShiftMask, XK_F6,           noop,                   {} }, */
	/* { MODKEY,                       XK_F7,           noop,                   {} }, */
	/* { MODKEY|ShiftMask,             XK_F7,           noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_F7,           noop,                   {} }, */
	/* { MODKEY|ControlMask|ShiftMask, XK_F7,           noop,                   {} }, */
	/* { MODKEY,                       XK_F8,           noop,                   {} }, */
	/* { MODKEY|ShiftMask,             XK_F8,           noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_F8,           noop,                   {} }, */
	/* { MODKEY|ControlMask|ShiftMask, XK_F8,           noop,                   {} }, */
	/* { MODKEY,                       XK_F9,           noop,                   {} }, */
	/* { MODKEY|ShiftMask,             XK_F9,           noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_F9,           noop,                   {} }, */
	/* { MODKEY|ControlMask|ShiftMask, XK_F9,           noop,                   {} }, */
	/* { MODKEY,                       XK_F10,          noop,                   {} }, */
	/* { MODKEY|ShiftMask,             XK_F10,          noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_F10,          noop,                   {} }, */
	/* { MODKEY|ControlMask|ShiftMask, XK_F10,          noop,                   {} }, */
	/* { MODKEY,                       XK_F12,          noop,                   {} }, */
	/* { MODKEY|ShiftMask,             XK_F12,          noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_F12,          noop,                   {} }, */
	/* { MODKEY|ControlMask|ShiftMask, XK_F12,          noop,                   {} }, */
	/* { MODKEY,                       XK_F12,          noop,                   {} }, */
	/* { MODKEY|ShiftMask,             XK_F12,          noop,                   {} }, */
	/* { MODKEY|ControlMask,           XK_F12,          noop,                   {} }, */
	/* { MODKEY|ControlMask|ShiftMask, XK_F12,          noop,                   {} }, */
	   { MODKEY,                       XK_0,            view,                   {.ui=~0} },
	   { MODKEY|ShiftMask,             XK_0,            tag,                    {.ui=~0} },
             TAGKEYS(                      XK_1,                                    0)
             TAGKEYS(                      XK_2,                                    1)
             TAGKEYS(                      XK_3,                                    2)
             TAGKEYS(                      XK_4,                                    3)
             TAGKEYS(                      XK_5,                                    4)
             TAGKEYS(                      XK_6,                                    5)
             TAGKEYS(                      XK_7,                                    6)
             TAGKEYS(                      XK_8,                                    7)
             TAGKEYS(                      XK_9,                                    8)
#endif 
        /* modifier                     key        function        argument */
        { MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
        { MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
        { MODKEY,                       XK_b,      togglebar,      {0} },
        { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
        { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
        { MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
        { MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
        { MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
        { MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
        { MODKEY,                       XK_Return, zoom,           {0} },
        { MODKEY,                       XK_Tab,    view,           {0} },
        { MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
        { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
        { MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
        { MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
        { MODKEY,                       XK_space,  setlayout,      {0} },
        { MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
        { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
        { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
        { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
        { MODKEY,                       XK_period, focusmon,       {.i = +1 } },
        { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
        { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
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
	{ MODKEY|ControlMask|ShiftMask, XK_q,      quit,           {1} }, 
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
        /* click                event mask      button          function        argument */
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

