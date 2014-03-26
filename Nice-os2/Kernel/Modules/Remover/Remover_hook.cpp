
// ─── Проверяет список окон для удаления ───

BYTE Remover_RemovingListIsEmpty( VOID )
{
 // Проверяем список.
 if( Remover.Settings.WinListNames.Remove_from_list_1_name[ 0 ] == 0 )
 if( Remover.Settings.WinListNames.Remove_from_list_2_name[ 0 ] == 0 )
 if( Remover.Settings.WinListNames.Remove_from_list_3_name[ 0 ] == 0 )
 if( Remover.Settings.WinListNames.Remove_from_list_4_name[ 0 ] == 0 )
 if( Remover.Settings.WinListNames.Remove_from_list_5_name[ 0 ] == 0 )
 if( Remover.Settings.WinListNames.Remove_from_list_6_name[ 0 ] == 0 )
 if( Remover.Settings.WinListNames.Remove_from_list_7_name[ 0 ] == 0 )
 if( Remover.Settings.WinListNames.Remove_from_list_8_name[ 0 ] == 0 ) return 1;

 // Возврат.
 return 0;
}

// ─── Слежение за сообщениями ───

// Все переменные - внешние.
VOID RemoverSendMsgHook( HAB Application, PSMHSTRUCT Message )
{
 // Скрываем строки в списке окон.
 // Это можно делать когда список окон становится выбранным.
 if( Remover.Settings.Remove_items_from_Window_list ) if( !RoomsChangeIsInProcess() )
  if( TopFrameWindowIsActivating( Message ) )
   if( Remover.Settings.Hide_known_applications || !Remover_RemovingListIsEmpty() )
    {
     // Узнаем окно рамки.
     HWND Frame_window = QueryFrameWindow( Message->hwnd );

     // Если это список окон:
     if( IsWinListWindow( Frame_window ) )
      {
       // Посылаем сообщение в поток.
       WinPostQueueMsg( Enhancer.Modules.Remover->Message_queue, SM_REMOVE_ITEMS, 0, 0 );
      }
    }

 // Возврат.
 return;
}
