// ���� ����஥�.
typedef struct _RMSXCPTNSPAGE
 {
  // ����ன��.
  typedef struct _INRSTS
   {
    // ���� ����� � ����.
    ULONG Container_ID;
    ULONG List_ID;
    ULONG Add_button_ID;
    ULONG Remove_button_ID;

    ULONG NoKeys_button_ID;
    ULONG NoIcons_button_ID;
    ULONG NoWallpaper_button_ID;
   }
  INRSTS; INRSTS Settings;
 }
RMSXCPTNSPAGE;

RMSXCPTNSPAGE Rooms_Exceptions;
