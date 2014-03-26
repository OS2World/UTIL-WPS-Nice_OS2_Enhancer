
// ─── Читает настройки ───

// Ini_file - файл настроек.
VOID MouseMapper_Tune( HINI Ini_file )
{
 // Читаем настройки.
 MouseMapper_SetPreDefinedSettings( SET_ALL_SETTINGS );
 MouseMapper_ReadSettings( Ini_file );

 // Проверяем настройки.
 if( MouseMapper.Settings.Use_middle_button_for_CopyPaste )
  if( WinQuerySysValue( QueryDesktopWindow(), SV_CMOUSEBUTTONS ) != 3 )
   MouseMapper.Settings.Use_middle_button_for_CopyPaste = 0;

 // Загружаем указатели.
 if( Resources.Pointer_for_CopyPaste != NULLHANDLE ) WinDestroyPointer( Resources.Pointer_for_CopyPaste );
 Resources.Pointer_for_CopyPaste = WinLoadPointer( QueryDesktopWindow(), Enhancer.Module, PTR_CLIPBOARD );

 // Запоминаем, какие потоки еще должны быть созданы.
 if( MouseMapper.Settings.Invert_mouse_buttons_with_Caps_Lock ) Enhancer.Modules.Controller->Required = 1;
 if( MouseMapper.Settings.Use_middle_button_for_CopyPaste ) Enhancer.Modules.Clipper->Required = 1;

 // Возврат.
 return;
}
