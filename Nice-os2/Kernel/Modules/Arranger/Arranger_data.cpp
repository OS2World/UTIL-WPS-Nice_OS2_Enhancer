// Задержка при выравнивании текстовых окон.
#define ARRANGER_DELAY_VIO        7500

// Выравнивание окон.
typedef struct _ARRANGER
 {
  // Настройки.
  typedef struct _INRSTS
   {
    // Выравнивать текстовые окна? 0 - нет, 1 - да.
    BYTE Arrange_VIO_windows; BYTE Arrange_FC2_windows;
    // Выравнивать список окон? 0 - нет, 1 - да.
    BYTE Arrange_WindowList;
    // Выравнивать окна WPS? 0 - нет, 1 - да.
    BYTE Arrange_WPS_windows;
   }
  INRSTS; INRSTS Settings;
 }
ARRANGER;

ARRANGER Arranger;