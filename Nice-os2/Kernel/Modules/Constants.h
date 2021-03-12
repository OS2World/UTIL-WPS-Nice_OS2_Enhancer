// Кнопки в заголовке и связанные с ними действия.
#define NO_ACTION        0

#define SYSMENU_ACTION   1

#define MAXIMIZE_ACTION  2
#define RESTORE_ACTION   4
#define MINIMIZE_ACTION  8
#define HIDE_ACTION      16
#define ROLLUP_ACTION    32
#define CLOSE_ACTION     64

#define ALL_ACTIONS     (CLOSE_ACTION | MAXIMIZE_ACTION | MINIMIZE_ACTION)
