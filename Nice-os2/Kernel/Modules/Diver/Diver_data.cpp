// Получение свойств окон.
typedef struct _DIVER
 {
  // Настройки.
  typedef struct _RTSTS
   {
    // Временная переменная для получения значения ширины рамки.
    POINT FB_size;
    // Значки из файловой системы.
    HPOINTER HDD_icon; HPOINTER EPM_icon;
   }
  RTSTS; RTSTS RTSettings;
 }
DIVER;

DIVER Diver;