// Окно настроек.
typedef struct _SPTBKGNDPAGE
 {
  // Настройки.
  typedef struct _INRSTS
   {
    // Поля ввода в окне.
    ULONG Wallpaper_filebox_ID;
    ULONG Wallpaper_label_ID;
    ULONG Wallpaper_name_ID;
    ULONG Wallpaper_button_ID;

    ULONG Example_ID;
    ULONG Comment_ID;

    // Изображение для окон оболочки.
    CHAR Folder_background_name[ SIZE_OF_PATH ];
    HBITMAP Folder_background;
    INT Folder_background_width;
    INT Folder_background_height;
   }
  INRSTS; INRSTS Settings;
 }
SPTBKGNDPAGE;

SPTBKGNDPAGE SysPatches_Background;
