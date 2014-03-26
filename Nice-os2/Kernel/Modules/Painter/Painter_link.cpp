
// ─── Сообщает, включено ли рисование рамок ───

BYTE Painter_DrawFramesSettingIsON( VOID )
{
 // Проверяем настройки.
 if( Painter.Settings.Draw_frames ) return 1;

 // Возврат.
 return 0;
}

// ─── Сообщает, включено ли рисование значков в заголовках ───

BYTE Painter_DrawSystemMenusSettingIsON( VOID )
{
 // Проверяем настройки.
 if( Painter.Settings.Draw_system_menus ) return 1;

 // Возврат.
 return 0;
}

// ─── Сообщает, включено ли рисование кнопок в заголовках ───

BYTE Painter_DrawButtonsSettingIsON( VOID )
{
 // Проверяем настройки.
 if( Painter.Settings.Draw_buttons ) return 1;

 // Возврат.
 return 0;
}

// ─── Отключает рисование рамок ───

VOID Painter_DisableFrameDrawing( VOID )
{
 // Отключаем настройки для рисования.
 Painter.Settings.Draw_frames = 0;

 // Возврат.
 return;
}