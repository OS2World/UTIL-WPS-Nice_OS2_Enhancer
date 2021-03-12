// ��ࠢ����� ��४���⥫ﬨ �� ���������.
typedef struct _CONTROLLER
{
  // ����ன��.
  typedef struct _INRSTS
  {
    // ������� Num Lock? 0 - �� �ண���, 1 - �������, 2 - �몫����.
    BYTE Turn_Num_Lock;
    // ��।����� ��஢� ������ ��� 1..9? 0 - ���, 1 - ��.
    BYTE Define_Num_keys;

    // ����뢠�� ������ "Shift"? 0 - ���, 1 - ��.
    BYTE Reset_Shift_keys;

    // ��������� ����������? 0 - ���, 1 - ��.
    BYTE SpeedUp_keyboard; BYTE Keyboard_rate;

    // �⪫���� Ctrl + Alt + Del? 0 - ���, 1 - ��.
    BYTE Suppress_CtrlAltDel;
    // �⪫���� Ctrl + Break? 0 - ���, 1 - ��.
    BYTE Suppress_CtrlBreak;
  }
  INRSTS; INRSTS Settings;
}
CONTROLLER;

CONTROLLER Controller;