
// ��� ��⠭�������� ����ன�� �� 㬮�砭�� ���

// Division - ����� ����ன�� ���� ��⠭�����.
VOID MouseMapper_SetPreDefinedSettings (LONG Division)
{
  // ������ ����ன��.
  if (Division == SET_ALL_SETTINGS || Division == SET_MOUSE)
  {
    MouseMapper.Settings.Suppress_double_click_in_sysmenu = 0;
    MouseMapper.Settings.Use_middle_button_for_CopyPaste = 1;
    MouseMapper.Settings.Move_input_focus_when_scrolling = 0;
    MouseMapper.Settings.Use_right_button_in_scrollbars = 1;
    MouseMapper.Settings.Invert_mouse_buttons_with_Caps_Lock = 0;
  }

  // ������.
  return;
}

// ��� ��⠥� ����ன�� ���

// Ini_file - 䠩� ����஥�.
VOID MouseMapper_ReadSettings (HINI Ini_file)
{
  // ��⠥� ����ன��.
  ULONG Byte = 0; ULONG Byte_data = 0;

  Byte = sizeof (BYTE); if (PrfQueryProfileData (Ini_file, "Settings", "Suppress double click in sysmenu", &Byte_data, &Byte))MouseMapper.Settings.Suppress_double_click_in_sysmenu = Byte_data;
  Byte = sizeof (BYTE); if (PrfQueryProfileData (Ini_file, "Settings", "Use middle button for CopyPaste", &Byte_data, &Byte))MouseMapper.Settings.Use_middle_button_for_CopyPaste = Byte_data;
  Byte = sizeof (BYTE); if (PrfQueryProfileData (Ini_file, "Settings", "Move input focus when scrolling", &Byte_data, &Byte))MouseMapper.Settings.Move_input_focus_when_scrolling = Byte_data;
  Byte = sizeof (BYTE); if (PrfQueryProfileData (Ini_file, "Settings", "Use right button in scrollbars", &Byte_data, &Byte))MouseMapper.Settings.Use_right_button_in_scrollbars = Byte_data;
  Byte = sizeof (BYTE); if (PrfQueryProfileData (Ini_file, "Settings", "Invert mouse buttons with Caps Lock", &Byte_data, &Byte))MouseMapper.Settings.Invert_mouse_buttons_with_Caps_Lock = Byte_data;

  // ������.
  return;
}