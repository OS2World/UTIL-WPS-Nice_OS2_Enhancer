// Исследование окон.
typedef struct _INSPECTOR
 {
  // Настройки.
  typedef struct _INRSTS
   {
    // Выполнять проверку списка приложений при запуске расширителя? 0 - нет, 1 - да.
    BYTE Check_Repository;
   }
  INRSTS; INRSTS Settings;
 }
INSPECTOR;

INSPECTOR Inspector;