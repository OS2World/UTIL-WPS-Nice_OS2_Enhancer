// Распознанное окружение.
typedef struct _KRNL_ENVIRONMENT
{
  // Внутренние переменные.
  typedef struct _RTSTS
  {
    // Оболочка системы.
    BYTE Shell_is_WPS;
    BYTE Shell_is_FileBar;

    // Вызвана заставка. 0 - нет, 1 - да.
    BYTE System_is_locked; HWND Lockup_frame;

    // Хранитель экрана может быть закрыт.
    BYTE Screen_Saver_can_be_closed;
  }
  RTSTS;

  RTSTS RTSettings;
} 
KRNL_ENVIRONMENT;

KRNL_ENVIRONMENT Krnl_Environment;

