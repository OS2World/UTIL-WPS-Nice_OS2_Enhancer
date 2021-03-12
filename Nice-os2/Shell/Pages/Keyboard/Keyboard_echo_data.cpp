// Окно настроек.
typedef struct _KBDECHOPAGE
{
  // Настройки.
  typedef struct _INRSTS
  {
    // Поля ввода в окне.
    ULONG Play_sound;
    ULONG For_IRC;
    ULONG For_ICQ;

    ULONG Use_RAMFS;
  }
  INRSTS; INRSTS Settings;
}
KBDECHOPAGE;

KBDECHOPAGE Keyboard_Echo;
