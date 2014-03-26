
// ─── Выполняет действие ───

VOID DialogWindow_PathField( HWND Window, ULONG Message, MPARAM First_parameter, MPARAM Second_parameter, ULONG WM_Control_Window_ID = 0 )
{
 // Запоминаем, что настройки изменены.
 if( !Names.Settings.InputField_is_locked ) Names.Settings.Settings_are_changed = 1;

 // Возврат.
 return;
}

