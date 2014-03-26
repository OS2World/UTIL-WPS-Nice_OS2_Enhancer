
// ─── Добавляет имя и путь в список свойств ───

// Frame_window - окно рамки.
VOID WinPrpListAndRepository_RememberExeNameAndPath( HWND Frame_window )
{
 // Узнаем путь к приложению, создавшему окно.
 PROCESSINFO Process_info = {0}; QueryProcessInfo( Frame_window, &Process_info, 0 );

 PCHAR Name = Process_info.Exe_name;
 PCHAR Path = Process_info.Exe_path;

 // Если его не удалось определить - возврат.
 if( Path[ 0 ] == 0 ) return;

 // Если это исполнитель команд или одна из его вспомогательных программ - возврат.
 if( IsCommandExecutorWindow( Process_info.Exe_name ) ) return;

 // Устанавливаем свойства.
 SetProperty( Frame_window, PRP_EXENAME, Name );
 SetProperty( Frame_window, PRP_EXEPATH, Path );

 // Если список приложений был прочтен:
 if( Krnl_Repository.RTSettings.Repository_is_ready )
  {
   // Проверяем, есть ли это приложение в списке известных приложений.
   INT Position = FindExeNameInRepository( Name );

   // Если оно есть:
   if( Position != -1 )
    {
     // Если путь к приложению изменился - запоминаем новый путь.
     if( Repository.Items[ Position ].Path_INI_setting_name[ 0 ] != 0 )
      if( strcmp( Repository.Items[ Position ].Path, Path ) != EQUALLY )
       strcpy( Repository.Items[ Position ].Path, Path );
    }
  }

 // Возврат.
 return;
}
