// �����⪨ ��� �����窨 OS/2.
typedef struct PATCHER
{
  // ����ﭭ� ����稭�.
  typedef struct _CONSTANTS
  {
    // ������� ���� WarpCenter.
    INT Big_WarpCenter;
    INT Big_WarpCenter_X1;
    INT Big_WarpCenter_X2;

    INT Small_WarpCenter;
    INT Small_WarpCenter_X1;
    INT Small_WarpCenter_X2;
  }
  CONSTANTS; CONSTANTS Constants;

  // ����ன��.
  typedef struct _INRSTS
  {
    // ����⠭�������� ���� ��। �����⨥�? 0 - ���, 1 - ��.
    BYTE Restore_windows_before_closing;
    // ��⠭����� ���⠢�� ⮫쪮 ��� ���� WPS? 0 - ���, 1 - ��.
    BYTE Limited_animation;
    // ��뢠�� � WarpCenter ����� ᯨ᮪ ����? 0 - ���, 1 - ��.
    BYTE Patch_WarpCenter;
  }
  INRSTS; INRSTS Settings;

  // ����७��� ��६����.
  typedef struct _RTSTS
  {
    // ����� ���� WarpCenter
    BYTE WinListMenu_is_pressed;
  }
  RTSTS; RTSTS RTSettings;
}
PATCHER;

PATCHER Patcher;
