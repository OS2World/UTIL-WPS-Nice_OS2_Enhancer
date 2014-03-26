// ─── Проверяет, можно ли воспроизвести звук при нажатии на клавишу ───

// Message - сообщение.
// Возвращаемое значение: 1, если можно, 0, если нельзя.
BYTE Clicker_PermissionForClicking( PQMSG Message )
{
 // Смотрим, какая клавиша нажата.
 BYTE Scan_code = CHAR4FROMMP( Message->mp1 );
 SHORT State = SHORT1FROMMP( Message->mp1 );

 // Смотрим, как установлены биты в State.
 if( !( State & KC_KEYUP ) ) return 0;
 if( !( State & KC_LONEKEY ) ) return 0;

 // Проверяем приложение.
 BYTE Permission = 0;

 // Узнаем окно рамки.
 HWND Frame_window = QueryFrameWindow( Message->hwnd );

 // Узнаем имя приложения, создавшего окно.
 CHAR Exe_name[ SIZE_OF_NAME ] = ""; GetDetectedExeName( Frame_window, Exe_name );

 // Если его удалось определить:
 if( Exe_name[ 0 ] != 0 )
  {
   // Если это окно IRC - надо воспроизвести звук.
   if( Clicker.Settings.Keyboard_echo_for_IRC )
    if( WindowIsUsedTo( DO_INTERNET_CHAT, Frame_window ) )
     Permission = 1;

   // Если это окно ICQ - надо воспроизвести звук.
   if( Clicker.Settings.Keyboard_echo_for_ICQ )
    if( WindowIsUsedTo( DO_CONTACT_PEOPLE, Frame_window ) )
     Permission = 1;
  }

 // Возврат.
 return Permission;
}
