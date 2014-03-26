// ─── Устанавливает окно-занавеску поверх всех окон ───

// Desktop - окно рабочего стола.
VOID Curtain_ShowCurtainWindow( HWND Desktop )
{
 // Если окно не показано:
 if( !WinIsWindowVisible( Curtain.Curtain_window ) )
  {
   // Узнаем размер экрана.
   INT X_Screen = WinQuerySysValue( Desktop, SV_CXSCREEN );
   INT Y_Screen = WinQuerySysValue( Desktop, SV_CYSCREEN );

   // Устанавливаем окно-занавеску поверх всех окон. Оно закрывает экран, но ничего не рисует.
   WinSetWindowPos( Curtain.Curtain_window, HWND_TOP, 0, 0, X_Screen, Y_Screen, SWP_MOVE | SWP_SIZE | SWP_SHOW | SWP_ZORDER | SWP_NOADJUST );
   WinShowWindow( Curtain.Curtain_window, 1 );

   // Перенаправляем ввод от клавиатуры в это окно.
   WinSetFocus( Desktop, Curtain.Curtain_window );
  }

 // Возврат.
 return;
}

// ─── Прячет окно-занавеску, если оно было видимо ───

// Activate_window_in_center - надо выбрать окно в середине экрана.
VOID Curtain_HideCurtainWindow( BYTE Activate_window_in_center = 0 )
{
 // Если окно видимо - прячем его.
 if( WinIsWindowVisible( Curtain.Curtain_window ) )
  {
   // Прячем окно-занавеску.
   WinSetWindowPos( Curtain.Curtain_window, HWND_BOTTOM, 0, 0, 0, 0, SWP_MOVE | SWP_SIZE | SWP_SHOW | SWP_ZORDER | SWP_NOADJUST );
   WinShowWindow( Curtain.Curtain_window, 0 );

   // Делаем выбранным окно в середине экрана.
   if( Activate_window_in_center ) ActivateWindowInCenter();
  }

 // Возврат.
 return;
}

// ─── Окно-занавеска, которое закрывает экран и ничего не рисует ───

// Поток приложения вызывает WindowProc всякий раз, когда для окна есть сообщение.
// Window - окно, Message - сообщение, *_parameter - данные, которые передаются вместе с сообщением.
MRESULT EXPENTRY Curtain_WindowProc( HWND Window, ULONG Message, MPARAM First_parameter, MPARAM Second_parameter )
{
 // Если окно становится видимым:
 if( Message == WM_SHOW ) if( First_parameter == (MPARAM) 1 )
  {
   // Запускаем счетчик времени.
   WinStartTimer( Enhancer.Application, Window, 1, Curtain.Constants.Curtain_present_time );

   // Возврат.
   return 0;
  }

 // Если окно становится скрытым:
 if( Message == WM_SHOW ) if( First_parameter == (MPARAM) 0 )
  {
   // Останавливаем счетчик времени.
   WinStopTimer( Enhancer.Application, Window, 1 );

   // Возврат.
   return 0;
  }

 // Сообщение о том, что окно должно быть перерисовано:
 if( Message == WM_PAINT )
  {
   // Окно ничего не рисует.
   RECT Rectangle = {0}; 
   HPS Presentation_space = WinBeginPaint( Window, NULLHANDLE, &Rectangle );
   WinEndPaint( Presentation_space );

   // Возврат.
   return 0;
  }

 // Сообщение от счетчика времени:
 if( Message == WM_TIMER )
  {
   // Прячем окно.
   Curtain_HideCurtainWindow();

   // Возврат.
   return 0;
  }

 // Нажата кнопка мыши:
 if( Message == WM_BUTTON1DOWN || Message == WM_BUTTON1DBLCLK ||
     Message == WM_BUTTON2DOWN || Message == WM_BUTTON2DBLCLK ||
     Message == WM_BUTTON3DOWN || Message == WM_BUTTON3DBLCLK )
  {
   // Прячем окно.
   Curtain_HideCurtainWindow();

   // Возврат.
   return 0;
  }

 // Другое сообщение - не обрабатывается.
 return WinDefWindowProc( Window, Message, First_parameter, Second_parameter );
}

// ─── Создает окно-занавеску ───

VOID Curtain_CreateCurtain()
{
 // Определяем окно в системе.
 CHAR Curtain_class_name[] = "CurtainWndClass";

 WinRegisterClass( Enhancer.Application, Curtain_class_name, (PFNWP) Curtain_WindowProc, 0, 0 );

 // Узнаем размер экрана.
 HWND Desktop = QueryDesktopWindow();

 // Создаем окно.
 Curtain.Curtain_window = WinCreateWindow( Desktop, Curtain_class_name, NULL, 0, 0, 0, 0, 0, NULLHANDLE, HWND_BOTTOM, 0, NULL, NULL );
 WinShowWindow( Curtain.Curtain_window, 0 );

 // Возврат.
 return;
}

// ─── Закрывает окно-занавеску ───

VOID Curtain_DestroyCurtain( VOID )
{
 // Закрываем окно.
 WinDestroyWindow( Curtain.Curtain_window ); Curtain.Curtain_window = NULLHANDLE;

 // Возврат.
 return;
}

