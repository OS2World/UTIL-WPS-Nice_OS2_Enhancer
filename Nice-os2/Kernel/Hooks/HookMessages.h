// Расширитель посылает эти сообщения в очереди приложений для того, чтобы знать,
// когда окно выполнит текущее действие и перейти к выполнению следующего. Обычно
// окна не обрабатывают эти сообщения, их наличие не вызывает никаких последствий.

// Эти сообщения могут быть использованы еще и для того, чтобы выполнить действие
// внутри определенного приложения, например, закрыть одно из его окон. Так как в
// оболочке OS/2 расширитель вызывают сами же приложения при получении сообщений,
// он может делать в InputHook все, что угодно.

// Сообщения, которые расширитель посылает приложениям.
#define WM_MARK                  WM_NULL

// Значения для них.
#define MRK_KBD_MODIFIERS        0xA0B0C0D0
#define MRK_MSE_MODIFIERS        0xD0C0B0A0

#define MRK_SET_POINTER          0xF0F0F0F0

#define MRK_DRAW_FRAME           0x0ABCDEF0
#define MRK_DRAW_SYSMENU         0x12341234
#define MRK_PRESS_SYSMENU        0x43214321

#define MRK_GO_TO_ROOM           0x00FACE00
#define MRK_FILL_DESKTOP         0x00FF00FF
#define MRK_CHECK_WINDOW         0x0FF00FF0

#define MRK_ADD_VIO_MENU_ITEMS   0x05050505
#define MRK_SHOW_VIO_MENU_ITEMS  0x50505050

#define MRK_POST_CTRL_V          0x40302010
#define MRK_RESTORE_CLIPBOARD    0x10203040

#define MRK_SELECT_ANYTHING      0xA0A0A0A0

#define MRK_ARRANGE_WINDOW       0x12345678
#define MRK_SHOW_AND_ARRANGE     0x30303030

#define MRK_LOGON_WINDOW         0x00770077
#define MRK_LOGON_VALUES         0x77007700
#define MRK_COMPLETE_DIALOG      0x70707070
#define MRK_SEND_YES             0x07070707

#define MRK_SET_PRIORITY         0x0A0B0C0D
#define MRK_SET_VIO_FONT         0x03030303

#define MRK_KILL_PROCESS         0x0D0E0A0D


