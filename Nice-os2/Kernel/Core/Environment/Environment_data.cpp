// ��ᯮ������� ���㦥���.
typedef struct _KRNL_ENVIRONMENT
{
  // ����७��� ��६����.
  typedef struct _RTSTS
  {
    // �����窠 ��⥬�.
    BYTE Shell_is_WPS;
    BYTE Shell_is_FileBar;

    // �맢��� ���⠢��. 0 - ���, 1 - ��.
    BYTE System_is_locked; HWND Lockup_frame;

    // �࠭�⥫� �࠭� ����� ���� ������.
    BYTE Screen_Saver_can_be_closed;
  }
  RTSTS;

  RTSTS RTSettings;
} 
KRNL_ENVIRONMENT;

KRNL_ENVIRONMENT Krnl_Environment;

