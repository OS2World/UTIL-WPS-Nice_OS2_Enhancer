// ���� ����஥�.
typedef struct _DRWTHEMESPAGE
 {
  // ����ன��.
  typedef struct _INRSTS
   {
    // ���� ����� � ����.
    ULONG Container_ID;
    ULONG Texture_filebox_ID;
    ULONG Texture_label_ID;
    ULONG Texture_name_ID;
    ULONG Texture_button_ID;
    ULONG Theme_list_ID;
    ULONG Theme_button_ID;

    // ���� ���������� ᯨ᪠ ⥬.
    BYTE Theme_list_is_locked;
   }
  INRSTS; INRSTS Settings;
 }
DRWTHEMESPAGE;

DRWTHEMESPAGE Drawing_Themes;
