// Окно настроек.
typedef struct _MSECLIPBRDPAGE
{
  // Настройки.
  typedef struct _INRSTS
  {
    // Поля ввода в окне.
    ULONG Mouse_cmbox_ID;
    ULONG Use_MB_ID;
  }
  INRSTS; INRSTS Settings;
}
MSECLIPBRDPAGE;

MSECLIPBRDPAGE Mouse_Clipboard;
