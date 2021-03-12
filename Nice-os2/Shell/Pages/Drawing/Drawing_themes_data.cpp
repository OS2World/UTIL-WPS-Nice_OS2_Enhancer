// Окно настроек.
typedef struct _DRWTHEMESPAGE
{
  // Настройки.
  typedef struct _INRSTS
  {
    // Поля ввода в окне.
    ULONG Container_ID;
    ULONG Texture_filebox_ID;
    ULONG Texture_label_ID;
    ULONG Texture_name_ID;
    ULONG Texture_button_ID;
    ULONG Theme_list_ID;
    ULONG Theme_button_ID;

    // Идет заполнение списка тем.
    BYTE Theme_list_is_locked;
  }
  INRSTS; INRSTS Settings;

  // Внутренние переменные.
  typedef struct _RTSTS
  {
    // Последний выбранный каталог.
    CHAR FileDlg_path[SIZE_OF_PATH];
  }
  RTSETTINGS; RTSETTINGS RTSettings;
}
DRWTHEMESPAGE;

DRWTHEMESPAGE Drawing_Themes;
