
// ��� ����᪠�� ����⥫� ���

VOID LauncherThread( VOID )
{
 // ��।��塞 ��⮪ � ��⥬�.
 HAB Thread = WinInitialize( 0 );
 Threads.Launcher_anchor = Thread;

 // �᫨ �� ᤥ���� �� 㤠���� - ��室.
 if( Thread == NULLHANDLE ) return;

 // ������� ��।� ᮮ�饭�� - ��� ������ ���� � ������ ��⮪�.
 {
  HMQ Messages_queue = WinCreateMsgQueue( Thread, 0 );
  Threads.Launcher_queue = Messages_queue;

  // �᫨ ��।� ᮧ���� �� 㤠���� - ��室.
  if( Messages_queue == NULLHANDLE )
   {
    WinTerminate( Thread );
    return;
   }
 }

 // ��뢠�� ����⥫� � ���� ��� �����襭��.
 {
  ULONG True = 1;
  while( True )
   {
    // ��뢠�� ����⥫�.
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

    // ������� �ਮ��� ��⮪�.
    DosSetPriority( PRTYS_THREAD, PRTYC_IDLETIME, 0, 0 );

    // ���� �����襭�� ����⥫�.
    while( DosVerifyPidTid( Process_ID, 1 ) == NO_ERROR ) DosSleep( 7500 );

    // ����⠭�������� �ਮ���.
    DosSetPriority( PRTYS_THREAD, PRTYC_REGULAR, 0, 0 );

    // �᫨ ����㦥��� ����⥫� �� ᮮ�騫, �� �� � ���浪� - �����, �� 㯠� ��� ��� �ਡ���.
    if( !Enhancer.Enhancer_is_terminated_normally )
     {
      // ������ ���� ࠡ�祣� �⮫�.
      HWND Desktop = WinQueryDesktopWindow( Enhancer.Application, NULLHANDLE );

      // ����⠭�������� ���� �����窨.
      {
       HENUM Enumeration = NULLHANDLE; HWND Window = NULLHANDLE;

       // ��ॡ�ࠥ� ���� � ���� ࠡ�祣� �⮫�.
       Enumeration = WinBeginEnumWindows( Desktop );
       while( ( Window = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
        {
         // �᫨ ���� �� ����:
         if( WinIsWindowVisible( Window ) )
          {
           // ������ ���, ��� ����� ��।����� ����.
           CHAR Window_name[ SIZE_OF_NAME ] = ""; WinQueryClassName( Window, SIZE_OF_NAME, Window_name );

           // �᫨ �� ���� WPS:
           if( strc( Window_name, "wpFolder window" ) )
            {
             // ������ ࠧ��� �࠭�.
             INT X_Screen = WinQuerySysValue( Desktop, SV_CXSCREEN );
             INT Y_Screen = WinQuerySysValue( Desktop, SV_CYSCREEN );

             // ������ �ᯮ������� ����.
             SWP Window_placement = {0}; WinQueryWindowPos( Window, &Window_placement );

             // �᫨ ���� ���⠭� - �����頥� ��� ���⭮.
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

      // �᫨ ���짮��⥫� �� ��� �த������ �ᯮ�짮���� ����⥫� - �����蠥� �믮������.
      {
       INT Reply = MBID_YES; CHAR Title[ SIZE_OF_TITLE ] = ""; GetEnhancerWindowTitle( Title );

       if( QuerySystemCodePage() == RUSSIAN )
        Reply = WinMessageBox( HWND_DESKTOP, HWND_DESKTOP, StrConst_RU_Enhancer_was_terminated, Title, NULLHANDLE, MB_YESNO );
       else
        Reply = WinMessageBox( HWND_DESKTOP, HWND_DESKTOP, StrConst_EN_Enhancer_was_terminated, Title, NULLHANDLE, MB_YESNO );

       if( Reply != MBID_YES ) break;
      }
     }
    // �᫨ ����⥫� ᮮ�騫, �� �� � ���浪� - �����蠥� �믮������.
    else
     {
      break;
     }
   }
 }

 // ����뢠�� ���� �ਫ������.
 WinPostMsg( Enhancer.Frame_window, WM_SYSCOMMAND, (MPARAM) SC_CLOSE, MPFROM2SHORT( CMDSRC_MENU, 0 ) );

 // �����蠥� ��⮪.
 WinDestroyMsgQueue( Threads.Launcher_queue );
 WinTerminate( Threads.Launcher_anchor );
 Threads.Launcher = NULLHANDLE;
 DosExit( EXIT_THREAD, 0 );

 // ������.
 return;
}
