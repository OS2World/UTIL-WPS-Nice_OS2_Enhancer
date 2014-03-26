// Окно с сообщениями об ошибках.
typedef struct _LOGPAGE
 {
  // Настройки.
  typedef struct _INRSTS
   {
    // Окно для сообщений.
    LONG Field_ID;
   }
  INRSTS; INRSTS Settings;

  // Внутренние переменные.
  typedef struct _RTSTS
   {
    // Поле ввода изменено.
    BYTE Field_is_changed;
   }
  RTSETTINGS; RTSETTINGS RTSettings;
 }
LOGPAGE;

LOGPAGE Log;