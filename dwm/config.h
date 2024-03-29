#include <X11/XF86keysym.h>

/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 1;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const Bool viewontag         = True;     /* Switch view on tag switch */

static const char *fonts[]          = {
                    "FuraMono Nerd Font:pixelsize=24:type=Regular:antialias=true:autohint=true"
                    };
static const char dmenufont[]       = "SauceCodePro Nerd Font Mono:size=20";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#ffffff";
static const char col_cyan[]        = "#37474F";
static const char col_border[]        = "#663399";
static const unsigned int baralpha = 0xd0;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_border  },
	[SchemeHid]  = { col_cyan,  col_gray1, col_border  },
};
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Firefox",   NULL,       NULL,       1 << 8,       0,           -1 },
	{ "Edge Dev",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "T",      tile },    /* first entry is default */
	{ "F",      NULL },    /* no layout function means floating behavior */
	{ "M",      monocle },
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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };

static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "82x24", NULL };
static const char *screenshotcmd[] = { "flameshot", "gui", NULL };
static const char *browsercmd[] = { "edge", NULL };
static const char *rangercmd[] = { "st", "ranger", NULL };

/* customize commads */
static const char *wpcmd[]  = { "/home/nofoot/App/suckless/dwm/scripts/wp-change.sh", NULL };
static const char *suspendcmd[]  = { "/home/nofoot/App/suckless/dwm/scripts/suspend.sh", NULL };
static const char *sleepcmd[]  = { "/home/nofoot/App/suckless/dwm/scripts/sleep.sh", NULL };
static const char *toggle_hjkl[]  = { "/home/nofoot/App/suckless/dwm/scripts/toggle_hjkl.sh", NULL };

static Key keys[] = {
	/* modifier            key                      function        argument */

	/******************脚本逻辑******************/
	// 打开 dmenu
	{ MODKEY,              XK_s,                    spawn,          {.v = dmenucmd } },
	// 执行脚本，打开edge浏览器
	{ MODKEY|ShiftMask,    XK_s,                    spawn,          {.v = browsercmd } },
	// 执行脚本，打开range
	{ MODKEY|ShiftMask,    XK_r,                    spawn,          {.v = rangercmd } },
	// 执行脚本，打开st
	{ MODKEY,              XK_Return,               spawn,          {.v = termcmd } },
	// 执行脚本，打开st，浮窗模式
	{ MODKEY,              XK_apostrophe,           togglescratch,  {.v = scratchpadcmd } },
	// 执行脚本，更换壁纸
	{ MODKEY,              XK_p,                    spawn,          {.v = wpcmd } },
	// 执行脚本，打开flameshot，截图
	{ 0,                   XK_Print,                spawn,          {.v = screenshotcmd } },
	// 执行脚本，暂停系统
	{ MODKEY|ShiftMask,    XK_p,                    spawn,          {.v = suspendcmd } },
	// 执行脚本，休眠系统
	{ MODKEY|ControlMask|ShiftMask,  XK_p,          spawn,          {.v = sleepcmd } },
	// 执行脚本，将hjkl映射为上下左右
	{ MODKEY,              XK_semicolon,            spawn,          {.v = toggle_hjkl } },
	
	/******************桌面逻辑******************/
	// 向左切换桌面
	{ MODKEY,              XK_h,                    viewtoleft,     {0} },
	// 向右切换桌面
	{ MODKEY,              XK_l,                    viewtoright,    {0} },
	// 切换最近停留的桌面
	{ MODKEY,              XK_Tab,                  view,           {0} },
	// 是否显示状态栏
	{ MODKEY,              XK_b,                    togglebar,      {0} },
	// 数字按键映射
	TAGKEYS(               XK_1,                      0)
	TAGKEYS(               XK_2,                      1)
	TAGKEYS(               XK_3,                      2)
	TAGKEYS(               XK_4,                      3)
	TAGKEYS(               XK_5,                      4)
	TAGKEYS(               XK_6,                      5)
	TAGKEYS(               XK_7,                      6)
	TAGKEYS(               XK_8,                      7)
	TAGKEYS(               XK_9,                      8)

	/******************窗口逻辑******************/
	// comma:逗号，调整主窗口大小
	{ MODKEY,              XK_comma,                setmfact,       {.f = -0.05} },
	// period:句号，调整主窗口大小
	{ MODKEY,              XK_period,               setmfact,       {.f = +0.05} },
	// 切换窗口布局
	{ MODKEY|ShiftMask,    XK_comma,                incnmaster,     {.i = +1 } },
	// 切换窗口布局
	{ MODKEY|ShiftMask,    XK_period,               incnmaster,     {.i = -1 } },
	// 改变聚焦窗口
	{ MODKEY,              XK_j,                    focusstack,     {.i = +1 } },
	// 改变聚焦窗口
	{ MODKEY,              XK_k,                    focusstack,     {.i = -1 } },
	// 调整窗口顺序
	{ MODKEY|ShiftMask,    XK_j,                    rotatestack,    {.i = +1 } },
	// 调整窗口顺序
	{ MODKEY|ShiftMask,    XK_k,                    rotatestack,    {.i = -1 } },
	// 隐藏当前窗口
	{ MODKEY,              XK_i,                    hidewin,        {0} },
	// 隐藏当前窗口
	{ MODKEY|ShiftMask,    XK_i,                    restorewin,     {0} },
	// 将当前窗口设置为主窗口
	{ MODKEY|ShiftMask,    XK_Return,               zoom,           {0} },
	// 按顺序恢复显示窗口（栈顺序）
	{ MODKEY,              XK_o,                    hideotherwins,  {0}},
	// 恢复显示所有窗口
	{ MODKEY|ShiftMask,    XK_o,                    restoreotherwins, {0}},
	// 关闭当前窗口
	{ MODKEY|ShiftMask,    XK_q,                    killclient,     {0} },
	//slash:斜杠，循环切换窗口模式，堆叠模式-平铺模式
	{ MODKEY,              XK_slash,                cyclelayout,    { .i = 1 } },
	// 全屏
	{ MODKEY|ShiftMask,    XK_space,                fullscreen,     {0} },


	/******************窗口缩放逻辑******************/
	// 完全通过键盘实现窗口移动和放缩逻辑
	{ MODKEY,                       XK_Down,        moveresize,     {.v = "0x 25y 0w 0h" } },
	{ MODKEY,                       XK_Up,          moveresize,     {.v = "0x -25y 0w 0h" } },
	{ MODKEY,                       XK_Right,       moveresize,     {.v = "25x 0y 0w 0h" } },
	{ MODKEY,                       XK_Left,        moveresize,     {.v = "-25x 0y 0w 0h" } },
	{ MODKEY|ShiftMask,             XK_Down,        moveresize,     {.v = "0x 0y 0w 25h" } },
	{ MODKEY|ShiftMask,             XK_Up,          moveresize,     {.v = "0x 0y 0w -25h" } },
	{ MODKEY|ShiftMask,             XK_Right,       moveresize,     {.v = "0x 0y 25w 0h" } },
	{ MODKEY|ShiftMask,             XK_Left,        moveresize,     {.v = "0x 0y -25w 0h" } },
	{ MODKEY|ControlMask,           XK_Up,          moveresizeedge, {.v = "t"} },
	{ MODKEY|ControlMask,           XK_Down,        moveresizeedge, {.v = "b"} },
	{ MODKEY|ControlMask,           XK_Left,        moveresizeedge, {.v = "l"} },
	{ MODKEY|ControlMask,           XK_Right,       moveresizeedge, {.v = "r"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Up,          moveresizeedge, {.v = "T"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Down,        moveresizeedge, {.v = "B"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Left,        moveresizeedge, {.v = "L"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Right,       moveresizeedge, {.v = "R"} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button1,        togglewin,      {0} },
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

