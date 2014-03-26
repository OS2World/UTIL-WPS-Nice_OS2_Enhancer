
// ��� ��⠥� ����ன�� ���

// Ini_file - 䠩� ����஥�.
VOID MouseMapper_Tune( HINI Ini_file )
{
 // ��⠥� ����ன��.
 MouseMapper_SetPreDefinedSettings( SET_ALL_SETTINGS );
 MouseMapper_ReadSettings( Ini_file );

 // �஢��塞 ����ன��.
 if( MouseMapper.Settings.Use_middle_button_for_CopyPaste )
  if( WinQuerySysValue( QueryDesktopWindow(), SV_CMOUSEBUTTONS ) != 3 )
   MouseMapper.Settings.Use_middle_button_for_CopyPaste = 0;

 // ����㦠�� 㪠��⥫�.
 if( Resources.Pointer_for_CopyPaste != NULLHANDLE ) WinDestroyPointer( Resources.Pointer_for_CopyPaste );
 Resources.Pointer_for_CopyPaste = WinLoadPointer( QueryDesktopWindow(), Enhancer.Module, PTR_CLIPBOARD );

 // ����������, ����� ��⮪� �� ������ ���� ᮧ����.
 if( MouseMapper.Settings.Invert_mouse_buttons_with_Caps_Lock ) Enhancer.Modules.Controller->Required = 1;
 if( MouseMapper.Settings.Use_middle_button_for_CopyPaste ) Enhancer.Modules.Clipper->Required = 1;

 // ������.
 return;
}
