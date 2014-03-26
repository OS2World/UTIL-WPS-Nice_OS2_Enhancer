// Наибольшее число цветов, значения которых заменяются расширителем (всегда четное число).
#define SYSVALUES_SYSCLRS_TO_CHANGE     32
// Наибольшее число настроек, значения которых заменяются расширителем.
#define SYSVALUES_SYSVALS_TO_CHANGE     16

// Запросы для составляющих расширителя.
typedef struct _PREFERRED_SYSTEM_COLORS
 {
  // Длина структуры.
  ULONG cb;

  // Задать для заполнения всех окон светло-серый цвет?
  BYTE Normalize_window_background;
  // Скрыть заголовки окон?
  typedef struct _HRWT
   {
    BYTE For_neon_theme;
    BYTE For_grayed_theme;
   }
  HRWT; HRWT Hide_real_window_title;
  // Установить для окна рабочего стола черный цвет?
  BYTE Set_black_desktop_background;
 }
PREFERRED_SYSTEM_COLORS; typedef PREFERRED_SYSTEM_COLORS* PPREFERRED_SYSTEM_COLORS;

typedef struct _PREFERRED_SYSTEM_VALUES
 {
  // Длина структуры.
  ULONG cb;

  // Изменять ширину рамок?
  BYTE Change_border_width; INT New_border_width;
  // Отключить клавишу "PrintScreen"?
  BYTE Disable_PrintScreen;
  // Отключить "Действия мышью в окнах VIO"?
  BYTE Disable_VIO_mouse_actions;
 }
PREFERRED_SYSTEM_VALUES; typedef PREFERRED_SYSTEM_VALUES* PPREFERRED_SYSTEM_VALUES;

// Изменение настроек и цветов оболочки OS/2.
typedef struct _SYSVALUES
 {
  // Цвета и настройки OS/2 до и после запуска расширителя.
  SYSCLR_ENTRY Old_colors[ SYSVALUES_SYSCLRS_TO_CHANGE ];
  SYSCLR_ENTRY New_colors[ SYSVALUES_SYSCLRS_TO_CHANGE ];

  SYSVAL_ENTRY Old_values[ SYSVALUES_SYSVALS_TO_CHANGE ];
  SYSVAL_ENTRY New_values[ SYSVALUES_SYSVALS_TO_CHANGE ];
 }
SYSVALUES; SYSVALUES SysValues;
