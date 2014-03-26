
// ─── Находит окно в списке диалогов ───

// Frame_window - окно, Check_title - надо ли проверять заголовок окна, Dialog - указатель на список диалогов.
VOID Applier_FindWindowInMessageDialogList( HWND Frame_window, BYTE Check_title, PPMSGDLGBOX Dialog )
{
 // Узнаем имя приложения, создавшего окно.
 CHAR Exe_name[ SIZE_OF_NAME ] = ""; GetDetectedExeName( Frame_window, Exe_name );

 // Если его удалось определить:
 if( Exe_name[ 0 ] != 0 )
  {
   // Узнаем, как выглядит рамка окна.
   LONG Frame_type = FrameType( Frame_window );

   // Если надо проверять заголовок окна - узнаем его. Если он неизвестен - используем пустую строку.
   CHAR Title[ SIZE_OF_TITLE ] = "";

   if( Check_title )
    {
     GetDetectedWindowTitle( Frame_window, Title );
     if( Title[ 0 ] == 0 ) strcpy( Title, "-" );
    }

   // Составляем список известных расширителю диалоговых окон.
   PMSGDLGBOX DlgList[ 8 ] = {
                                &Applier.Settings.Dialogs.Message_dialog_1, &Applier.Settings.Dialogs.Message_dialog_2,
                                &Applier.Settings.Dialogs.Message_dialog_3, &Applier.Settings.Dialogs.Message_dialog_4,
                                &Applier.Settings.Dialogs.Message_dialog_5, &Applier.Settings.Dialogs.Message_dialog_6,
                                &Applier.Settings.Dialogs.Message_dialog_7, &Applier.Settings.Dialogs.Message_dialog_8 };

   // Если такое окно уже есть в списке - возврат.
   for( INT Count = 0; Count < 8; Count ++ )
    {
     // Если список просмотрен - завершаем перебор.
     if( DlgList[ Count ]->Frame_type == 0 ) break;

     // Если окно имеет другой вид рамки - продолжаем перебор.
     if( Frame_type != DlgList[ Count ]->Frame_type )
      continue;

     // Если окно создано другим приложением - продолжаем перебор.
     if( DlgList[ Count ]->Exe_name[ 0 ] != 0 )
      if( strcmp( Exe_name, DlgList[ Count ]->Exe_name ) != EQUALLY )
       continue;

     // Если надо проверять заголовок окна:
     if( Title[ 0 ] != 0 )
      {
       // Если у окна другой заголовок - продолжаем перебор.
       if( DlgList[ Count ]->Window_title[ 0 ] != 0 )
        if( strcmp( Title, DlgList[ Count ]->Window_title ) != EQUALLY )
         continue;
      }

     // Запоминаем окно.
     *Dialog = DlgList[ Count ]; break;
    }
  }

 // Возврат.
 return;
}

// ─── Проверяет, есть ли окно в списке диалогов ───

// Frame_window - окно, Check_title - надо ли проверять заголовок окна.
BYTE Applier_WindowIsPresentInMessageDialogList( HWND Frame_window, BYTE Check_title )
{
 // Пробуем найти окно в одном из списков.
 PMSGDLGBOX Message_dialog = NULL; Applier_FindWindowInMessageDialogList( Frame_window, Check_title, &Message_dialog );
 if( Message_dialog != NULL ) return 1;

 // Возврат.
 return 0;
}

// ─── Находит окно в списке диалогов ───

// Frame_window - окно, Check_title - надо ли проверять заголовок окна, Dialog - указатель на список диалогов.
VOID Applier_FindWindowInIncompleteDialogList( HWND Frame_window, BYTE Check_title, PPDLGBOX Dialog )
{
 // Узнаем имя приложения, создавшего окно.
 CHAR Exe_name[ SIZE_OF_NAME ] = ""; GetDetectedExeName( Frame_window, Exe_name );

 // Если его удалось определить:
 if( Exe_name[ 0 ] != 0 )
  {
   // Узнаем, как выглядит рамка окна.
   LONG Frame_type = FrameType( Frame_window );

   // Если надо проверять заголовок окна - узнаем его. Если он неизвестен - используем пустую строку.
   CHAR Title[ SIZE_OF_TITLE ] = "";

   if( Check_title )
    {
     GetDetectedWindowTitle( Frame_window, Title );
     if( Title[ 0 ] == 0 ) strcpy( Title, "-" );
    }

   // Составляем список известных расширителю диалоговых окон.
   PDLGBOX DlgList[ 8 ] = {
                                &Applier.Settings.Dialogs.Incomplete_dialog_1, &Applier.Settings.Dialogs.Incomplete_dialog_2,
                                &Applier.Settings.Dialogs.Incomplete_dialog_3, &Applier.Settings.Dialogs.Incomplete_dialog_4,
                                &Applier.Settings.Dialogs.Incomplete_dialog_5, &Applier.Settings.Dialogs.Incomplete_dialog_6,
                                &Applier.Settings.Dialogs.Incomplete_dialog_7, &Applier.Settings.Dialogs.Incomplete_dialog_8 };

   // Если такое окно уже есть в списке - возврат.
   for( INT Count = 0; Count < 8; Count ++ )
    {
     // Если список просмотрен - завершаем перебор.
     if( DlgList[ Count ]->Frame_type == 0 ) break;

     // Если окно имеет другой вид рамки - продолжаем перебор.
     if( Frame_type != DlgList[ Count ]->Frame_type )
      continue;

     // Если окно создано другим приложением - продолжаем перебор.
     if( DlgList[ Count ]->Exe_name[ 0 ] != 0 )
      if( strcmp( Exe_name, DlgList[ Count ]->Exe_name ) != EQUALLY )
       continue;

     // Если надо проверять заголовок окна:
     if( Title[ 0 ] != 0 )
      {
       // Если у окна другой заголовок - продолжаем перебор.
       if( DlgList[ Count ]->Window_title[ 0 ] != 0 )
        if( strcmp( Title, DlgList[ Count ]->Window_title ) != EQUALLY )
         continue;
      }

     // Запоминаем окно.
     *Dialog = DlgList[ Count ]; break;
    }
  }

 // Возврат.
 return;
}

// ─── Проверяет, есть ли окно в списке диалогов ───

// Frame_window - окно, Check_title - надо ли проверять заголовок окна.
BYTE Applier_WindowIsPresentInIncompleteDialogList( HWND Frame_window, BYTE Check_title )
{
 // Пробуем найти окно в одном из списков.
 PDLGBOX Incomplete_dialog = NULL; Applier_FindWindowInIncompleteDialogList( Frame_window, Check_title, &Incomplete_dialog );
 if( Incomplete_dialog != NULL ) return 1;

 // Возврат.
 return 0;
}

// ─── Находит окно в списке диалогов ───

// Frame_window - окно, Check_title - надо ли проверять заголовок окна, Dialog - указатель на список диалогов.
VOID Applier_FindWindowInLogonDialogList( HWND Frame_window, BYTE Check_title, PPLOGONDLGBOX Dialog )
{
 // Узнаем имя приложения, создавшего окно.
 CHAR Exe_name[ SIZE_OF_NAME ] = ""; GetDetectedExeName( Frame_window, Exe_name );

 // Если его удалось определить:
 if( Exe_name[ 0 ] != 0 )
  {
   // Узнаем, как выглядит рамка окна.
   LONG Frame_type = FrameType( Frame_window );

   // Если надо проверять заголовок окна - узнаем его. Если он неизвестен - используем пустую строку.
   CHAR Title[ SIZE_OF_TITLE ] = "";

   if( Check_title )
    {
     GetDetectedWindowTitle( Frame_window, Title );
     if( Title[ 0 ] == 0 ) strcpy( Title, "-" );
    }

   // Составляем список известных расширителю диалоговых окон.
   PLOGONDLGBOX DlgList[ 8 ] = {
                                &Applier.Settings.Dialogs.Logon_dialog_1, &Applier.Settings.Dialogs.Logon_dialog_2,
                                &Applier.Settings.Dialogs.Logon_dialog_3, &Applier.Settings.Dialogs.Logon_dialog_4,
                                &Applier.Settings.Dialogs.Logon_dialog_5, &Applier.Settings.Dialogs.Logon_dialog_6,
                                &Applier.Settings.Dialogs.Logon_dialog_7, &Applier.Settings.Dialogs.Logon_dialog_8 };

   // Если такое окно уже есть в списке - возврат.
   for( INT Count = 0; Count < 8; Count ++ )
    {
     // Если список просмотрен - завершаем перебор.
     if( DlgList[ Count ]->Frame_type == 0 ) break;

     // Если окно имеет другой вид рамки - продолжаем перебор.
     if( Frame_type != DlgList[ Count ]->Frame_type )
      continue;

     // Если окно создано другим приложением - продолжаем перебор.
     if( DlgList[ Count ]->Exe_name[ 0 ] != 0 )
      if( strcmp( Exe_name, DlgList[ Count ]->Exe_name ) != EQUALLY )
       continue;

     // Если надо проверять заголовок окна:
     if( Title[ 0 ] != 0 )
      {
       // Если у окна другой заголовок - продолжаем перебор.
       if( DlgList[ Count ]->Window_title[ 0 ] != 0 )
        if( strcmp( Title, DlgList[ Count ]->Window_title ) != EQUALLY )
         continue;
      }

     // Запоминаем окно.
     *Dialog = DlgList[ Count ]; break;
    }
  }

 // Возврат.
 return;
}

// ─── Проверяет, есть ли окно в списке диалогов ───

// Frame_window - окно, Check_title - надо ли проверять заголовок окна.
BYTE Applier_WindowIsPresentInLogonDialogList( HWND Frame_window, BYTE Check_title )
{
 // Пробуем найти окно в одном из списков.
 PLOGONDLGBOX Logon_dialog = NULL; Applier_FindWindowInLogonDialogList( Frame_window, Check_title, &Logon_dialog );
 if( Logon_dialog != NULL ) return 1;

 // Возврат.
 return 0;
}

