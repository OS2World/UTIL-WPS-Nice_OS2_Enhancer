// Окно настроек.
typedef struct _DRWRSTRCTNSPAGE
 {
  // Настройки.
  typedef struct _INRSTS
   {
    // Поля ввода в окне.
    ULONG FixedColors_button_ID;
   }
  INRSTS; INRSTS Settings;
 }
DRWRSTRCTNSPAGE;

DRWRSTRCTNSPAGE Drawing_Restrictions;
