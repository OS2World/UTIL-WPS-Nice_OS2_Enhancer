
// ─── Запускает расширитель ───

VOID LauncherThread( VOID )
{
 // Определяем поток в системе.
 HAB Thread = WinInitialize( 0 );
 Threads.Launcher_anchor = Thread;

 // Если это сделать не удалось - выход.
 if( Thread == NULLHANDLE ) return;

 // Создаем очередь сообщений - она должна быть в каждом потоке.
 {
  HMQ Messages_queue = WinCreateMsgQueue( Thread, 0 );
  Threads.Launcher_queue = Messages_queue;

  // Если очередь создать не удалось - выход.
  if( Messages_queue == NULLHANDLE )
   {
    WinTerminate( Thread );
    return;
   }
 }

 // Вызываем расширитель и ждем его завершения.
 {
  ULONG True = 1;
  while( True )
   {
    // Вызываем расширитель.
    ULONG Process_ID = NULLHANDLE;

    CHAR Parameters[ 255 ]; Parameters[ 0 ] = 0;
    strcpy( &Parameters[ 0 ], "Nice-os2.exe" ); Parameters[ 12 ] = 0;

    if( Enhancer.Launcher_mode == 1 ) { strcpy( &Parameters[ 13 ], "Enhancer" ); Parameters[ 21 ] = 0; }
    else { strcpy( &Parameters[ 13 ], "Icon" ); Parameters[ 17 ] = 0; }

    {
     CHAR Error_string[ 1 ]; RESULTCODES Return_codes;
     DosResetBuffer( -1 ); DosExecPgm( Error_string, sizeof( Error_string ), EXEC_ASYNC, Parameters, NULL, &Return_codes, "Nice-os2.exe" );
     Process_ID = Return_codes.codeTerminate;
    }

    // Снижаем приоритет потока.
    DosSetPriority( PRTYS_THREAD, PRTYC_IDLETIME, 0, 0 );

    // Ждем завершения расширителя.
    while( DosVerifyPidTid( Process_ID, 1 ) == NO_ERROR ) DosSleep( 7500 );

    // Восстанавливаем приоритет.
    DosSetPriority( PRTYS_THREAD, PRTYC_REGULAR, 0, 0 );

    // Если загруженный расширитель не сообщил, что все в порядке - значит, он упал или его прибили.
    if( !Enhancer.Enhancer_is_terminated_normally )
     {
      // Узнаем окно рабочего стола.
      HWND Desktop = WinQueryDesktopWindow( Enhancer.Application, NULLHANDLE );

      // Восстанавливаем окно оболочки.
      {
       HENUM Enumeration = NULLHANDLE; HWND Window = NULLHANDLE;

       // Перебираем окна в окне рабочего стола.
       Enumeration = WinBeginEnumWindows( Desktop );
       while( ( Window = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
        {
         // Если окно не скрыто:
         if( WinIsWindowVisible( Window ) )
          {
           // Узнаем имя, под которым определено окно.
           CHAR Window_name[ SIZE_OF_NAME ] = ""; WinQueryClassName( Window, SIZE_OF_NAME, Window_name );

           // Если это окно WPS:
           if( strc( Window_name, "wpFolder window" ) )
            {
             // Узнаем размер экрана.
             INT X_Screen = WinQuerySysValue( Desktop, SV_CXSCREEN );
             INT Y_Screen = WinQuerySysValue( Desktop, SV_CYSCREEN );

             // Узнаем расположение окна.
             SWP Window_placement = {0}; WinQueryWindowPos( Window, &Window_placement );

             // Если окно спрятано - возвращаем его обратно.
             if( Window_placement.x == X_Screen * (-10) )
              {
               RECT Rectangle = { 0, 0, X_Screen, Y_Screen }; WinCalcFrameRect( Window, &Rectangle, 0 );

               WinSetWindowPos( Window, NULLHANDLE, Rectangle.xLeft, Rectangle.yBottom, Rectangle.xRight - Rectangle.xLeft, Rectangle.yTop - Rectangle.yBottom, SWP_MOVE | SWP_SIZE | SWP_NOADJUST );
              }
            }
          }
        }
       WinEndEnumWindows( Enumeration );
      }

      // Если пользователь не хочет продолжать использовать расширитель - завершаем выполнение.
      {
       INT Reply = MBID_YES; CHAR Title[ SIZE_OF_TITLE ] = ""; GetEnhancerWindowTitle( Title );

       if( QuerySystemCodePage() == RUSSIAN )
        Reply = WinMessageBox( HWND_DESKTOP, HWND_DESKTOP, StrConst_RU_Enhancer_was_terminated, Title, NULLHANDLE, MB_YESNO );
       else
        Reply = WinMessageBox( HWND_DESKTOP, HWND_DESKTOP, StrConst_EN_Enhancer_was_terminated, Title, NULLHANDLE, MB_YESNO );

       if( Reply != MBID_YES ) break;
      }
     }
    // Если расширитель сообщил, что все в порядке - завершаем выполнение.
    else
     {
      break;
     }
   }
 }

 // Закрываем окно приложения.
 WinPostMsg( Enhancer.Frame_window, WM_SYSCOMMAND, (MPARAM) SC_CLOSE, MPFROM2SHORT( CMDSRC_MENU, 0 ) );

 // Завершаем поток.
 WinDestroyMsgQueue( Threads.Launcher_queue );
 WinTerminate( Threads.Launcher_anchor );
 Threads.Launcher = NULLHANDLE;
 DosExit( EXIT_THREAD, 0 );

 // Возврат.
 return;
}
