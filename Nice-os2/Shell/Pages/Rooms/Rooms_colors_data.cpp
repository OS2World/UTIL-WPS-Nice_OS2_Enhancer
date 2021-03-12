// ���� ����஥�.
typedef struct _RMSCLRSPAGE
{
  // ����ன��.
  typedef struct _INRSTS
  {
    // ���� ����� � ����.
    ULONG Container_ID;
    ULONG Wallpaper_filebox_ID;
    ULONG Wallpaper_label_ID;
    ULONG Wallpaper_name_ID;
    ULONG Wallpaper_button_ID;

    ULONG Selected_room_cmbox_ID;
    ULONG Create_rooms_button_ID;

    ULONG NeonPalette_Container_ID;
    ULONG NeonPalette_Palette_ID;
    ULONG NeonPalette_Inactive_1_ID;
    ULONG NeonPalette_Inactive_2_ID;
    ULONG NeonPalette_Inactive_3_ID;
    ULONG NeonPalette_Active_1_ID;
    ULONG NeonPalette_Active_2_ID;
    ULONG NeonPalette_Active_3_ID;
    ULONG NeonPalette_FillTB_ID;

    ULONG WinTitles_Container_ID;
    ULONG WinTitles_Palette_ID;
    ULONG WinTitles_Inactive_ID;
    ULONG WinTitles_Active_ID;
    ULONG WinTitles_Button_ID;
    ULONG WinTitles_DrawText_ID;
  }
  INRSTS; INRSTS Settings;

  // ����७��� ��६����.
  typedef struct _RTSTS
  {
    // ��࠭��� ������.
    ULONG Selected_room;
    // ��᫥���� ��࠭�� ��⠫��.
    CHAR FileDlg_path[SIZE_OF_PATH];
  }
  RTSETTINGS; RTSETTINGS RTSettings;
}
RMSCLRSPAGE;

RMSCLRSPAGE Rooms_Colors;
