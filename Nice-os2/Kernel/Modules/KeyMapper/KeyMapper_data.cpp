// ������ ������ � ������� �ਫ�������.
typedef struct _KEYMAPPER
 {
  // ����ன��.
  typedef struct _INRSTS
   {
    // ������� ������ ��� ⮣�, �⮡� ���������� � ��⠢���� ⥪��? 0 - ���, 1 - ��.
    BYTE Define_Ctrl_CV;
    // ��।����� ������� "|\"? 0 - ���, 1 - ��.
    BYTE Define_Dash;
    BYTE Define_Ctrl_Dash;
    // ��।����� ������� Enter ��� ����� ���祭�� �� ࠡ�祬 �⮫�? 0 - ���, 1 - ��.
    BYTE Define_Enter;
    // �⪫���� ������� F3, �᫨ ��� �ᯮ������ ��� "�᪮�⥫�"? 0 - ���, 1 - ��.
    BYTE Discard_F3;
    // ������� ������ "Alt + F4 / F9" � ⥪�⮢�� �����? 0 - ���, 1 - ��.
    BYTE Enable_WMKeys_in_VIO;
   }
  INRSTS; INRSTS Settings;
 }
KEYMAPPER;

KEYMAPPER KeyMapper;
