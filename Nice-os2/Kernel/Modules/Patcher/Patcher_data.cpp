// Заплатки для оболочки OS/2.
typedef struct PATCHER
{
  // Постоянные величины.
  typedef struct _CONSTANTS
  {
    // Размеры окна WarpCenter.
    INT Big_WarpCenter;
    INT Big_WarpCenter_X1;
    INT Big_WarpCenter_X2;

    INT Small_WarpCenter;
    INT Small_WarpCenter_X1;
    INT Small_WarpCenter_X2;
  }
  CONSTANTS; CONSTANTS Constants;

  // Настройки.
  typedef struct _INRSTS
  {
    // Восстанавливать окна перед закрытием? 0 - нет, 1 - да.
    BYTE Restore_windows_before_closing;
    // Установить заставки только для окон WPS? 0 - нет, 1 - да.
    BYTE Limited_animation;
    // Вызывать в WarpCenter обычный список окон? 0 - нет, 1 - да.
    BYTE Patch_WarpCenter;
  }
  INRSTS; INRSTS Settings;

  // Внутренние переменные.
  typedef struct _RTSTS
  {
    // Нажато меню WarpCenter
    BYTE WinListMenu_is_pressed;
  }
  RTSTS; RTSTS RTSettings;
}
PATCHER;

PATCHER Patcher;
