// ���ந�������� ��㪠 �� ����⨨ �� �������.
typedef struct _CLICKER
{
  // ����ன��.
  typedef struct _INRSTS
  {
    // ��� �� ����⨨ �� �������? 0 - ���, 1 - ��.
    BYTE Keyboard_echo; 
    BYTE Keyboard_echo_for_IRC;
    BYTE Keyboard_echo_for_ICQ;

    // ��७���� 䠩� � ��㪮� �� ��� � �����? 0 - ���, 1 - ��.
    BYTE Cache_echo_file;
  }
  INRSTS; INRSTS Settings;

  // ����७��� ��६����.
  typedef struct _RTSTS 
  {
    // ��� �� ����⨨ �� �������.
    CHAR Keyboard_wav[SIZE_OF_PATH];
    CHAR Keyboard_exe[SIZE_OF_PATH];
  }
  RTSTS; RTSTS RTSettings;
}
CLICKER;

CLICKER Clicker;