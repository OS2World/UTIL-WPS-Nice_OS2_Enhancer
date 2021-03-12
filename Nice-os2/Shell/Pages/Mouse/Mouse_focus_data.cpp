// Окно настроек.
typedef struct _MSEFOCUSPAGE
{
  // Настройки.
  typedef struct _INRSTS
  {
    // Поля ввода в окне.
    ULONG Scrolling_ID;
  }
  INRSTS; INRSTS Settings;
}
MSEFOCUSPAGE;

MSEFOCUSPAGE Mouse_Focus;
