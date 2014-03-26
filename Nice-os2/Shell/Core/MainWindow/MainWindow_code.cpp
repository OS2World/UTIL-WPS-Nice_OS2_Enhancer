
// ─── Окно приложения ───

MRESULT EXPENTRY Enhancer_MainWindowProc( HWND Window, ULONG Message, MPARAM First_parameter, MPARAM Second_parameter )
{
 // Смотрим на пришедшее сообщение и выполняем действие.
 switch( Message )
  {
   // Создание окна:
   case WM_CREATE:
    {
     // Сообщаем окну о том, какие действия надо еще выполнить.
     WinPostMsg( Window, SM_ADD_SWITCH_ENTRY, 0, 0 );
     WinPostMsg( Window, SM_CREATE_LAYOUT, 0, 0 );

     WinPostMsg( Window, SM_SET_FRAME_ICON, 0, 0 );

    }
   return 0;

   // Установка значка в левом верхнем углу окна рамки:
   case SM_SET_FRAME_ICON:
    {
     // Задаем путь к значку, чтобы загрузить его из файла.
     CHAR Icon_file[ SIZE_OF_PATH ] = "";
     GetCurrentPath( Icon_file );
     CutNameInPath( Icon_file );

     switch( Enhancer.Settings_to_show )
      {
       case SET_SCROLLING:    strcat( Icon_file, "\\Install\\Scr_page.ico" ); break;
       case SET_DRAWING:      strcat( Icon_file, "\\Install\\Drw_page.ico" ); break;
       case SET_ROOMS:        strcat( Icon_file, "\\Install\\Rms_page.ico" ); break;
       case SET_KEYBOARD:     strcat( Icon_file, "\\Install\\Kbd_page.ico" ); break;
       case SET_MOUSE:        strcat( Icon_file, "\\Install\\Mse_page.ico" ); break;
       case SET_PLACEMENT:    strcat( Icon_file, "\\Install\\Wnd_page.ico" ); break;
       case SET_DIALOG_BOXES: strcat( Icon_file, "\\Install\\Dlg_page.ico" ); break;
       case SET_FILE_WINDOWS: strcat( Icon_file, "\\Install\\Itm_page.ico" ); break;
       case SET_PRIORITY:     strcat( Icon_file, "\\Install\\Pty_page.ico" ); break;
       case SET_WINLIST:      strcat( Icon_file, "\\Install\\Lst_page.ico" ); break;
       case SET_VIO_WINDOWS:  strcat( Icon_file, "\\Install\\Vio_page.ico" ); break;
       case SET_SYS_PATCHES:  strcat( Icon_file, "\\Install\\Dsk_page.ico" ); break;
       default:               strcat( Icon_file, "\\Install\\Nice-os2.ico" ); break;
      }

     if( !FileExists( Icon_file ) ) Icon_file[ 0 ] = 0;

     // Пробуем загрузить значок из файла или из приложения.
     HPOINTER Icon = NULLHANDLE;

     if( Icon_file[ 0 ] != 0 ) Icon = WinLoadFileIcon( Icon_file, 1 );
     if( !Icon ) Icon = WinLoadPointer( QueryDesktopWindow(), NULLHANDLE, 1 );

     // Задаем значок окна.
     WinSendMsg( Enhancer.Frame_window, WM_SETICON, (MPARAM) Icon, 0 );
    }
   return 0;

   // Добавление окна в список окон:
   case SM_ADD_SWITCH_ENTRY:
    {
     // Узнаем окно рабочего стола.
     HWND Desktop = QueryDesktopWindow();

     // Задаем заголовок окна.
     CHAR NCC_Title[ SIZE_OF_TITLE ] = ""; GetEnhancerWindowTitle( NCC_Title );
     WinSetWindowText( WinWindowFromID( Enhancer.Frame_window, FID_TITLEBAR ), NCC_Title );

     // Добавляем его в список окон.
     SWCNTRL Task; bzero( &Task, sizeof( SWCNTRL ) );

     Task.hwnd = Enhancer.Frame_window;
     Task.hwndIcon = (HPOINTER) WinSendMsg( Enhancer.Frame_window, WM_QUERYICON, 0, 0 );
     WinQueryWindowProcess( Enhancer.Frame_window, &Task.idProcess, NULL );

     strcpy( Task.szSwtitle, NCC_Title );

     Task.uchVisibility = SWL_VISIBLE;
     Task.fbJump = SWL_JUMPABLE;

     WinAddSwitchEntry( &Task );
    }
   return 0;

   // Создание полей ввода:
   case SM_CREATE_LAYOUT:
    {
     // Создаем окно с закладками. Оно добавит на свои страницы все остальные окна.
     LitCreateLayout( &Enhancer.Client_layout, Window );
     CreateNotebookWindow( Window, &Enhancer.Client_layout );

     {
      LTBRICK Window_brick; LitPrepareBrick( &Window_brick ); Window_brick.hwnd = Window;
      Window_brick.prpWidthInParent = 640 + 64;
      Window_brick.prpHeightInParent = 480 + 48;
      Window_brick.prpMargin = LTM_TOP_FRAME_MARGIN;
      LitJoinBrick( &Enhancer.Client_layout, &Window_brick );
     }

     // Показываем окно.
     if( Enhancer.Nice_is_minimized ) WinPostMsg( Enhancer.Frame_window, WM_SYSCOMMAND, (MPARAM) SC_MINIMIZE, MPFROM2SHORT( CMDSRC_MENU, 0 ) );
     else LitShowFrameWindow( &Enhancer.Client_layout );
    }
   return 0;

   // Расположение полей ввода:
   case SM_APPLY_LAYOUT:
    {
     // Пересчитываем расположение всех полей ввода.
     LitApplyLayout( &Enhancer.Client_layout );

     RECT Rectangle = {0}; WinQueryWindowRect( Enhancer.Notebook_window, &Rectangle );
     WinSendMsg( Enhancer.Notebook_window, BKM_CALCPAGERECT, (MPARAM) &Rectangle, (MPARAM) 1 );

     for( INT Page_count = 0; Page_count < PAGELIST_LENGTH; Page_count ++ )
      {
       PPAGE Page = GetPageListEntry( Page_count );

       if( Page != NULL ) if( Page->Present )
        {
         WinSetWindowPos( Page->Window, NULLHANDLE, Rectangle.xLeft, Rectangle.yBottom, Rectangle.xRight - Rectangle.xLeft, Rectangle.yTop - Rectangle.yBottom, SWP_MOVE | SWP_SIZE | SWP_NOADJUST );
         LitApplyLayout( &( Page->Layout ) );
        }
      }
    }
   return 0;

   // Рисование окна:
   case WM_PAINT:
    {
     // Закрашиваем пространство окна.
     RECT Rectangle = {0};
     HPS Presentation_space = WinBeginPaint( Window, 0, &Rectangle );
     WinFillRect( Presentation_space, &Rectangle, CLR_PALEGRAY );
     WinEndPaint( Presentation_space );
    }
   return 0;

   // Изменение размера окна:
   case WM_SIZE:
    {
     // Пересчитываем расположение всех полей ввода.
     WinPostMsg( Window, SM_APPLY_LAYOUT, 0, 0 );
    }
   return 0;

   // Разрушение окна:
   case WM_DESTROY:
    {
     // Удаляем поля ввода.
     for( INT Page_count = 0; Page_count < PAGELIST_LENGTH; Page_count ++ )
      {
       PPAGE Page = GetPageListEntry( Page_count );
       if( Page != NULL ) if( Page->Present ) LitDeleteLayout( &( Page->Layout ) );
      }

     LitDeleteLayout( &Enhancer.Client_layout );
     DestroyWindowTree( Window, 0 );

     // Закрываем окна справочника.
     CloseExistingHelpPage();

     // Убираем окно расширителя из списка окон.
     WinRemoveSwitchEntry( WinQuerySwitchHandle( Enhancer.Frame_window, 0 ) );
    }
   return 0;
  }

 // Возврат.
 return WinDefWindowProc( Window, Message, First_parameter, Second_parameter );
}
