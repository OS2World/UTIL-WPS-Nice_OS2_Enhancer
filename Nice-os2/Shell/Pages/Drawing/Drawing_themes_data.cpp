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

  // ����७��� ��६����.
  typedef struct _RTSTS
  {
    // ��᫥���� ��࠭�� ��⠫��.
    CHAR FileDlg_path[SIZE_OF_PATH];
  }
  RTSETTINGS; RTSETTINGS RTSettings;
}
DRWTHEMESPAGE;

DRWTHEMESPAGE Drawing_Themes;
