// ����⢨� � �����.
typedef struct _MOUSEMAPPER
 {
  // ����ன��.
  typedef struct _INRSTS
   {
    // �⪫���� ������� ����⨥ ��� �� ���⨭�� � ����� ���孥� 㣫� ����? 0 - ���, 1 - ��.
    BYTE Suppress_double_click_in_sysmenu;
    // �ᯮ�짮���� �।��� ������ ��� ����������� � ��⠢�� ⥪��? 0 - ���, 1 � 2 - ��.
    BYTE Use_middle_button_for_CopyPaste;
    // ��७���� ���� �� ���������� ��� 㪠��⥫� ��� �� �ப��⪥? 0 - ���, 1 - ��.
    BYTE Move_input_focus_when_scrolling;
    // �ᯮ�짮���� �ࠢ�� ������ ��� ��� ����᮪ ��ᬮ��? 0 - ���, 1 - ��.
    BYTE Use_right_button_in_scrollbars;
    // ������ ������ ��� �᫨ ����祭 Caps Lock? 0 - ���, 1 - ��.
    BYTE Invert_mouse_buttons_with_Caps_Lock;
   }
  INRSTS; INRSTS Settings;

  // ����७��� ��६����.
  typedef struct _RTSTS
   {
    // ������ ��� ��������.
    BYTE Buttons_are_inverted;

    // ����ﭨ� ��� ��������.
    BYTE Mouse_state_is_changed;

    // �६� ��᫥����� ������ �।��� ������ ���.
    LONG WM_MB_Down_time;
   }
  RTSTS; RTSTS RTSettings;
 }
MOUSEMAPPER;

MOUSEMAPPER MouseMapper;