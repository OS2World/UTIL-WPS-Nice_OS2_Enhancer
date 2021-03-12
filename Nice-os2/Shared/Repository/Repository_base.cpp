#ifdef INCLUDED_BY_SHELL
VOID Repository_QueryExeName (HWND, PCHAR);
#endif

// ─── Проверяет, является ли окно "окном рабочего стола" ───

// Window - окно для проверки.
BYTE Repository_IsDesktopWindow (HWND Window)
{
  // Узнаем имя, под которым определено окно.
  CHAR Window_name[SIZE_OF_NAME] = ""; WinQueryClassName (Window, SIZE_OF_NAME, Window_name);

  // Проверяем его.
  if (strc (Window_name, "#32766")) return 1;

  // Возврат.
  return 0;
}

// ─── Проверяет, является ли окно рамкой OS/2 ───

// Window - окно для проверки.
BYTE Repository_IsFrameWindow (HWND Window)
{
  // Узнаем имя, под которым определено окно.
  CHAR Window_name[SIZE_OF_NAME] = ""; WinQueryClassName (Window, SIZE_OF_NAME, Window_name);

  // Проверяем его.
  {
    // Проверяем имя, под которым определено окно.
    BYTE Window_can_be_frame = 0;

    if (strc (Window_name, "#1")) Window_can_be_frame = 1;
    if (strc (Window_name, "EFrame")) Window_can_be_frame = 1;
    if (strc (Window_name, "wpFolder window")) Window_can_be_frame = 1;
    if (strc (Window_name, "Win32FrameClass")) Window_can_be_frame = 1;

    #ifndef INCLUDED_BY_SHELL

    // Рамки часто используются для рисования прямоугольников.
    // Если у окна нет заголовка и оно расположено не в окне рабочего стола - это уже не рамка.
    if (Window_can_be_frame)
     if (WinWindowFromID (Window, FID_TITLEBAR) == NULLHANDLE)
      if (WinQueryWindow (Window, QW_PARENT) != QueryDesktopWindow ())
       return 0;

    #endif

    // Если проверка пройдена - это рамка.
    if (Window_can_be_frame) return 1;
  }

  // Возврат.
  return 0;
}

// ─── Проверяет, является ли окно рамкой WPS ───

// Frame_window - окно для проверки.
BYTE Repository_IsFolderWindow (HWND Frame_window)
{
  // Узнаем имя, под которым определено окно.
  CHAR Window_name[SIZE_OF_NAME] = ""; WinQueryClassName (Frame_window, SIZE_OF_NAME, Window_name);

  // Проверяем его.
  if (strc (Window_name, "wpFolder window")) return 1;

  // Возврат.
  return 0;
}

// ─── Проверяет, меню ли данное окно ───

// Window - окно для проверки.
BYTE Repository_IsMenuWindow (HWND Window)
{
  // Узнаем имя, под которым определено окно.
  CHAR Window_name[SIZE_OF_NAME] = ""; WinQueryClassName (Window, SIZE_OF_NAME, Window_name);

  // Проверяем его.
  if (strc (Window_name, "#4")) return 1;

  // Возврат.
  return 0;
}

// ─── Проверяет, является ли окно заголовком ───

// Window - окно для проверки.
BYTE Repository_IsTitleBarWindow (HWND Window)
{
  // Узнаем имя, под которым определено окно.
  CHAR Window_name[SIZE_OF_NAME] = ""; WinQueryClassName (Window, SIZE_OF_NAME, Window_name);

  // Проверяем его.
  if (strc (Window_name, "#9")) return 1;

  // Возврат.
  return 0;
}

// ─── Проверяет, является ли окно полоской просмотра ───

// Window - окно для проверки.
BYTE Repository_IsScrollBarWindow (HWND Window)
{
  // Узнаем имя, под которым определено окно.
  CHAR Window_name[SIZE_OF_NAME] = ""; WinQueryClassName (Window, SIZE_OF_NAME, Window_name);

  // Проверяем его.
  if (strc (Window_name, "#8")) return 1;

  // Возврат.
  return 0;
}

// ─── Проверяет, является ли окно полем ввода ───

// Window - окно для проверки.
BYTE Repository_IsInputFieldWindow (HWND Window)
{
  // Узнаем имя, под которым определено окно.
  CHAR Window_name[SIZE_OF_NAME] = ""; WinQueryClassName (Window, SIZE_OF_NAME, Window_name);

  // Проверяем его.
  if (strc (Window_name, "#10") ||
      strstr ("MultiLineEntryField", Window_name)) return 1;

  // Возврат.
  return 0;
}

// ─── Проверяет, является ли окно однострочным полем ввода ───

// Window - окно для проверки.
BYTE Repository_IsEntryFieldWindow (HWND Window)
{
  // Узнаем имя, под которым определено окно.
  CHAR Window_name[SIZE_OF_NAME] = ""; WinQueryClassName (Window, SIZE_OF_NAME, Window_name);

  // Проверяем его.
  if (strc (Window_name, "#6") ||
      strstr ("EntryField", Window_name)) return 1;

  // Возврат.
  return 0;
}

// ─── Проверяет, является ли окно списком со значками ───

// Window - окно для проверки.
BYTE Repository_IsIconViewWindow (HWND Window)
{
  // Узнаем имя, под которым определено окно.
  CHAR Window_name[SIZE_OF_NAME] = ""; WinQueryClassName (Window, SIZE_OF_NAME, Window_name);

  // Проверяем его.
  if (strc (Window_name, "#37")) return 1;

  // Возврат.
  return 0;
}

// ─── Проверяет, является ли окно списком со значками ───

// Window - окно для проверки.
BYTE Repository_IsDetailViewWindow (HWND Window)
{
  // Узнаем имя, под которым определено окно.
  CHAR Window_name[SIZE_OF_NAME] = ""; WinQueryClassName (Window, SIZE_OF_NAME, Window_name);

  // Проверяем его.
  if (strc (Window_name, "#50")) return 1;
  if (strc (Window_name, "#51")) return 1;

  // Возврат.
  return 0;
}

// ─── Проверяет, является ли окно списком с выпадающим меню ───

// Window - окно для проверки.
BYTE Repository_IsComboBoxWindow (HWND Window)
{
  // Узнаем имя, под которым определено окно.
  CHAR Window_name[SIZE_OF_NAME] = ""; WinQueryClassName (Window, SIZE_OF_NAME, Window_name);

  // Проверяем его.
  if (strc (Window_name, "#2") ||
      strstr ("Combo", Window_name) ||
      strstr ("DropDown", Window_name)) return 1;

  // Возврат.
  return 0;
}

// ─── Проверяет, является ли окно списком ───

// Window - окно для проверки.
BYTE Repository_IsListBoxWindow (HWND Window)
{
  // Узнаем имя, под которым определено окно.
  CHAR Window_name[SIZE_OF_NAME] = ""; WinQueryClassName (Window, SIZE_OF_NAME, Window_name);

  // Проверяем его.
  if (strc (Window_name, "#7") ||
      strstr ("ListBox", Window_name)) return 1;

  // Возврат.
  return 0;
}

// ─── Проверяет, является ли окно однострочным списком ───

// Window - окно для проверки.
BYTE Repository_IsSpinButtonWindow (HWND Window)
{
  // Узнаем имя, под которым определено окно.
  CHAR Window_name[SIZE_OF_NAME] = ""; WinQueryClassName (Window, SIZE_OF_NAME, Window_name);

  // Проверяем его.
  if (strc (Window_name, "#32") ||
      strstr ("SpinButton", Window_name)) return 1;

  // Возврат.
  return 0;
}

// ─── Проверяет, является ли окно отмечаемой кнопкой ───

// Window - окно для проверки.
BYTE Repository_IsCheckBoxButtonWindow (HWND Window)
{
  // Узнаем имя, под которым определено окно.
  CHAR Window_name[SIZE_OF_NAME] = ""; WinQueryClassName (Window, SIZE_OF_NAME, Window_name);

  // Проверяем его.
  if (strc (Window_name, "#3") ||
      strstr ("CheckBox", Window_name))
  {
    QMSG Report = {0};
    LONG Style = (LONG) WinSendMsg (Window, WM_QUERYDLGCODE, &Report, 0);
    if (Style & DLGC_CHECKBOX) return 1;
  }

  // Возврат.
  return 0;
}

// ─── Проверяет, является ли окно выбираемой кнопкой ───

// Window - окно для проверки.
BYTE Repository_IsRadioButtonWindow (HWND Window)
{
  // Узнаем имя, под которым определено окно.
  CHAR Window_name[SIZE_OF_NAME] = ""; WinQueryClassName (Window, SIZE_OF_NAME, Window_name);

  // Проверяем его.
  if (strc (Window_name, "#3") ||
      strstr ("RadioButton", Window_name))
  {
    QMSG Report = {0};
    LONG Style = (LONG) WinSendMsg (Window, WM_QUERYDLGCODE, &Report, 0);
    if (Style & DLGC_RADIOBUTTON) return 1;
  }

  // Возврат.
  return 0;
}

// ─── Проверяет, является ли окно кнопкой ───

// Window - окно для проверки.
BYTE Repository_IsButtonWindow (HWND Window)
{
  // Узнаем имя, под которым определено окно.
  CHAR Window_name[SIZE_OF_NAME] = ""; WinQueryClassName (Window, SIZE_OF_NAME, Window_name);

  // Проверяем его.
  if (strc (Window_name, "#3") ||
      strstr ("PushButton", Window_name))
  {
    QMSG Report = {0};
    LONG Style = (LONG) WinSendMsg (Window, WM_QUERYDLGCODE, &Report, 0);
    if (Style & DLGC_PUSHBUTTON || Style & DLGC_DEFAULT) return 1;
  }

  // Возврат.
  return 0;
}

// ─── Проверяет, является ли окно движком ───

// Window - окно для проверки.
BYTE Repository_IsSliderWindow (HWND Window)
{
  // Узнаем имя, под которым определено окно.
  CHAR Window_name[SIZE_OF_NAME] = ""; WinQueryClassName (Window, SIZE_OF_NAME, Window_name);

  // Проверяем его.
  if (strc (Window_name, "#38")) return 1;

  // Возврат.
  return 0;
}

// ─── Проверяет, является ли окно круглым движком ───

// Window - окно для проверки.
BYTE Repository_IsCircularSliderWindow (HWND Window)
{
  // Узнаем имя, под которым определено окно.
  CHAR Window_name[SIZE_OF_NAME] = ""; WinQueryClassName (Window, SIZE_OF_NAME, Window_name);

  // Проверяем его.
  if (strc (Window_name, "#65")) return 1;

  // Возврат.
  return 0;
}

// ─── Проверяет, является ли окно набором закладок ───

// Window - окно для проверки.
BYTE Repository_IsNotebookWindow (HWND Window)
{
  // Узнаем имя, под которым определено окно.
  CHAR Window_name[SIZE_OF_NAME] = ""; WinQueryClassName (Window, SIZE_OF_NAME, Window_name);

  // Проверяем его.
  if (strc (Window_name, "#40")) return 1;

  // Возврат.
  return 0;
}

// ─── Проверяет, является ли окно закладкой ───

// Window - окно для проверки.
BYTE Repository_IsNotebookPageWindow (HWND Window)
{
  // Закладка - окно рамки без заголовка, расположенное в наборе закладок.
  if (Repository_IsFrameWindow (Window))
   if (WinWindowFromID (Window, FID_TITLEBAR) == NULLHANDLE)
    if (Repository_IsNotebookWindow (WinQueryWindow (Window, QW_PARENT)))
     return 1;

  // Возврат.
  return 0;
}

// ─── Проверяет, является ли окно невидимым прямоугольником ───

// Window - окно для проверки.
BYTE Repository_IsStaticWindow (HWND Window)
{
  // Узнаем имя, под которым определено окно.
  CHAR Window_name[SIZE_OF_NAME] = ""; WinQueryClassName (Window, SIZE_OF_NAME, Window_name);

  // Проверяем его.
  if (strc (Window_name, "#5"))
   if (WinQueryWindowTextLength (Window) == 0)
    return 1;

  // Возврат.
  return 0;
}

// ─── Проверяет, является ли окно надписью ───

// Window - окно для проверки.
BYTE Repository_IsLabelWindow (HWND Window)
{
  // Узнаем имя, под которым определено окно.
  CHAR Window_name[SIZE_OF_NAME] = ""; WinQueryClassName (Window, SIZE_OF_NAME, Window_name);

  // Проверяем его.
  if (strc (Window_name, "#5"))
   if (WinQueryWindowTextLength (Window) != 0)
    return 1;

  // Возврат.
  return 0;
}

// ─── Проверяет, может ли окно быть оболочкой для полей ввода ───

// Window - окно для проверки.
BYTE Repository_IsInputFieldContainerWindow (HWND Window)
{
  // Поля ввода могут располагаться в прямоугольниках и в закладках.
  if (Repository_IsStaticWindow (Window) ||
      Repository_IsNotebookWindow (Window) ||
      Repository_IsNotebookPageWindow (Window)) return 1;

  // Возврат.
  return 0;
}

// ─── Проверяет, может ли данное окно быть окном FileBar ───

// Frame_window - окно для проверки.
BYTE Repository_IsFileBarWindow (HWND Frame_window)
{
  // Узнаем окно рабочей области.
  HWND Client_window = WinWindowFromID (Frame_window, FID_CLIENT);

  if (Client_window != NULLHANDLE)
  {
    // Узнаем имя, под которым определено окно.
    CHAR Client_name[SIZE_OF_NAME] = ""; WinQueryClassName (Client_window, SIZE_OF_NAME, Client_name);

    // Проверяем его.
    if (strc (Client_name, "FileBar")) return 1;
  }

  // Возврат.
  return 0;
}

// ─── Проверяет, является ли окно рамкой MDesk ───

// Frame_window - окно для проверки.
BYTE Repository_IsMDeskWindow (HWND Frame_window)
{
  // Узнаем окно рабочей области.
  HWND Client_window = WinWindowFromID (Frame_window, FID_CLIENT);

  if (Client_window != NULLHANDLE)
  {
    // Узнаем имя, под которым определено окно.
    CHAR Client_name[SIZE_OF_NAME] = ""; WinQueryClassName (Client_window, SIZE_OF_NAME, Client_name);

    // Проверяем его.
    if (strc (Client_name, "MDesk-Folder")) return 1;
  }

  // Возврат.
  return 0;
}

// ─── Проверяет, может ли данное окно быть окном WindowList ───

// Frame_window - окно, которое надо проверить.
BYTE Repository_IsWinListWindow (HWND Frame_window)
{
  // Узнаем окно рабочей области.
  HWND Client_window = WinWindowFromID (Frame_window, FID_CLIENT);

  if (Client_window != NULLHANDLE)
  {
    // Узнаем имя, под которым определено окно.
    CHAR Client_name[SIZE_OF_NAME] = ""; WinQueryClassName (Client_window, SIZE_OF_NAME, Client_name);

    // Проверяем его.
    if (strc (Client_name, "WindowList")) return 1;
  }

  // Возврат.
  return 0;
}

// ─── Проверяет, является ли окно рамкой VIO ───

// Frame_window - окно для проверки.
BYTE Repository_IsVIOWindow (HWND Frame_window)
{
  // Узнаем окно рабочей области.
  HWND Client_window = WinWindowFromID (Frame_window, FID_CLIENT);

  if (Client_window != NULLHANDLE)
  {
    // Узнаем имя, под которым определено окно.
    CHAR Client_name[SIZE_OF_NAME] = ""; WinQueryClassName (Client_window, SIZE_OF_NAME, Client_name);

    // Проверяем его.
    if (strc (Client_name, "Shield")) return 1;
  }

  // Возврат.
  return 0;
}

// ─── Проверяет, является ли окно рамкой Win-OS/2 или Odin ───

// Frame_window - окно рамки.
BYTE Repository_IsWindowsWindow (HWND Frame_window)
{
  // Узнаем окно рабочей области.
  HWND Client_window = WinWindowFromID (Frame_window, FID_CLIENT);

  if (Client_window != NULLHANDLE)
  {
    // Узнаем имя, под которым определено окно.
    CHAR Client_name[SIZE_OF_NAME] = ""; WinQueryClassName (Client_window, SIZE_OF_NAME, Client_name);

    // Проверяем его.
    if (strstr ("Win32WindowClass", Client_name)) return 1;
    if (strc (Client_name, "SeamlessClass")) return 1;
  }

  // Возврат.
  return 0;
}

// ─── Проверяет, создано ли окно оболочкой OS/2 (то есть PM, не WPS и не приложениями) ───

// Frame_window - окно, которое надо проверить.
BYTE Repository_IsPMShellAuxiliaryWindow (HWND Frame_window)
{
  // Окна VIO и Win-OS/2 не считаем окнами Presentation Manager: хоть они и
  // создаются оболочкой, но в них работают приложения, это не часть оболочки.
  if (Repository_IsVIOWindow (Frame_window) || Repository_IsWindowsWindow (Frame_window)) return 0;

  // Узнаем приложение, создавшее окно.
  PID Process_ID = 0; TID Thread_ID = 0; WinQueryWindowProcess (Frame_window, &Process_ID, &Thread_ID);

  // Если его не удалось узнать - считаем, что окно создано оболочкой Presentation Manager.
  // Как правило, это еще не готовое текстовое окно или окно диалога с текстовым сообщением.
  if (Process_ID == 0) return 1;

  // Узнаем приложение, создавшее окно рабочего стола.
  PID Desktop_process_ID = 0; TID Desktop_thread_ID = 0; WinQueryWindowProcess (QueryDesktopWindow (), &Desktop_process_ID, &Desktop_thread_ID);

  // Если значения совпадают - окно создано оболочкой Presentation Manager.
  if (Desktop_process_ID != 0 && Process_ID == Desktop_process_ID) return 1;

  // Возврат.
  return 0;
}

// ─── Проверяет, создано ли окно оболочкой рабочего стола (WPS, не PM) ───

// Frame_window - окно, которое надо проверить.
BYTE Repository_IsWorkplaceShellWindow (HWND Frame_window)
{
  // Если это окно VIO или Win-OS/2 - возврат.
  if (Repository_IsVIOWindow (Frame_window) || Repository_IsWindowsWindow (Frame_window)) return 0;

  // Если это окно создано самой оболочкой Presentation Manager - возврат.
  if (Repository_IsPMShellAuxiliaryWindow (Frame_window)) return 0;

  // Если это окно фолдера - то это окно оболочки WPS, и проверки не требуются.
  if (Repository_IsFolderWindow (Frame_window)) return 1;

  // Узнаем имя приложения, используемого в качестве оболочки.
  PCHAR Workplace = NULL; DosScanEnv ("RUNWORKPLACE", (PPCSZ) &Workplace);

  // Если оно неизвестно - нет ни одного окна, которое может быть им создано, возврат.
  if (Workplace == NULL) return 0;

  // Узнаем имя приложения, создавшего окно.
  CHAR Exe_name[SIZE_OF_NAME] = "";

  #ifndef INCLUDED_BY_SHELL
  GetDetectedExeName (Frame_window, Exe_name);
  #else
  Repository_QueryExeName (Frame_window, Exe_name);
  #endif

  // Если его удалось определить:
  if (Exe_name[0] != 0)
  {
    // Проверяем его.
    if (stristr (Exe_name, Workplace)) return 1;
  }
  // А если имя неизвестно:
  else
  {
    // Это может быть что угодно, но не одно из окон оболочки.
    return 0;
  }

  // Возврат.
  return 0;
}

// ─── Проверяет, может ли данное окно быть переключателем окон по "Alt + Tab" ───

// Frame_window - окно, которое надо проверить.
BYTE Repository_IsAltTabSwitcherWindow (HWND Frame_window)
{
  // Узнаем имя, под которым определено окно.
  CHAR Window_name[SIZE_OF_NAME] = ""; WinQueryClassName (Frame_window, SIZE_OF_NAME, Window_name);

  // Проверяем его.
  if (stric (Window_name, "AltTabSwitcher")) return 1;

  // Возврат.
  return 0;
}

// ─── Проверяет, может ли данное окно быть окном lSwitcher ───

// Frame_window - окно, которое надо проверить.
BYTE Repository_IslSwitcherWindow (HWND Frame_window)
{
  // Узнаем окно рабочей области.
  HWND Client_window = WinWindowFromID (Frame_window, FID_CLIENT);

  if (Client_window != NULLHANDLE)
  {
    // Узнаем имя, под которым определено окно.
    CHAR Client_name[SIZE_OF_NAME] = ""; WinQueryClassName (Client_window, SIZE_OF_NAME, Client_name);

    // Проверяем его. Начало имени, "lsw" может быть задано разными буквами.
    if (stric (Client_name, "lswPopupClass")) return 1;
    if (stric (Client_name, "lswTaskBarClass")) return 1;
  }

  // Возврат.
  return 0;
}

// ─── Проверяет, имеет ли окно расположение, похожее на WarpCenter ───

// Window - окно для проверки.
BYTE Repository_HasWarpCenterSize (HWND Window)
{
  // Узнаем размер окна.
  RECT Rectangle = {0}; WinQueryWindowRect (Window, &Rectangle);

  // Если ширина окна в несколько раз больше его высоты:
  if (Rectangle.xRight > Rectangle.yTop * 10)
  {
    // Узнаем окно рабочего стола.
    HWND Desktop = QueryDesktopWindow ();

    // Узнаем размер экрана.
    INT X_Screen = WinQuerySysValue (QueryDesktopWindow (), SV_CXSCREEN);

    // Если ширина окна больше размера экрана - это окно похоже на WarpCenter.
    if (Rectangle.xRight > X_Screen - 10) return 1;
  }

  // Возврат.
  return 0;
}

// ─── Проверяет, может ли данное окно быть окном WarpCenter ───

// Window - окно, которое надо проверить.
BYTE Repository_IsWarpCenterWindow (HWND Window)
{
  // Если окно создано не оболочкой - возврат.
  if (!Repository_IsWorkplaceShellWindow (Window)) return 0;

  // Если родительское окно не рабочий стол - возврат.
  if (WinQueryWindow (Window, QW_PARENT) != QueryDesktopWindow ()) return 0;

  // Узнаем имя, под которым определено окно.
  CHAR Window_name[SIZE_OF_NAME] = ""; WinQueryClassName (Window, SIZE_OF_NAME, Window_name);

  // Если это может быть WarpCenter:
  if (strc (Window_name, "#3"))
   if (Repository_HasWarpCenterSize (Window))
   {
     // Узнаем заголовок окна.
     Window_name[0] = NULL;
     WinQueryWindowText (Window, SIZE_OF_NAME, Window_name);

     // Если это WarpCenter - возвращаем 1.
     if (strc (Window_name, "SmartCenter")) return 1;
   }

  // Возврат.
  return 0;
}

// ─── Проверяет, может ли данное окно быть окном меню WarpCenter ───

// Window - окно, которое надо проверить.
BYTE Repository_IsWarpCenterMenuWindow (HWND Window)
{
  // Если окно создано не оболочкой - возврат.
  if (!Repository_IsWorkplaceShellWindow (Window)) return 0;

  // Если родительское окно не рабочий стол - возврат.
  if (WinQueryWindow (Window, QW_PARENT) != QueryDesktopWindow ()) return 0;

  // Узнаем имя, под которым определено окно.
  CHAR Window_name[SIZE_OF_NAME] = ""; WinQueryClassName (Window, SIZE_OF_NAME, Window_name);

  // Если это может быть WarpCenter:
  if (strc (Window_name, "#3"))
  {
    // Узнаем размер окна.
    RECT Rectangle = {0}; WinQueryWindowRect (Window, &Rectangle);

    // Если высота окна больше его ширины - это меню WarpCenter.
    if (Rectangle.yTop > Rectangle.xRight) return 1;
  }

  // Возврат.
  return 0;
}

// ─── Проверяет, может ли данное окно быть окном SysTray ───

// Window - окно, которое надо проверить.
BYTE Repository_IsSysTrayWindow (HWND Window)
{
  // Узнаем окно рабочей области.
  HWND Client_window = WinWindowFromID (Window, FID_CLIENT);

  if (Client_window != NULLHANDLE)
  {
    // Узнаем имя, под которым определено окно.
    CHAR Client_name[SIZE_OF_NAME] = ""; WinQueryClassName (Client_window, SIZE_OF_NAME, Client_name);

    // Если оно может быть окном SysTray:
    if (stristr ("SysTray", Client_name))
    {
      // Проверяем расположение окна.
      if (Repository_HasWarpCenterSize (Window)) return 1;
    }
  }

  // Возврат.
  return 0;
}

// ─── Проверяет, может ли данное окно быть окном меню SysTray ───

// Window - окно, которое надо проверить.
BYTE Repository_IsSysTrayMenuWindow (HWND Window)
{
  // Если это окно меню:
  if (Repository_IsMenuWindow (Window))
  {
    // Узнаем окно владельца.
    HWND Owner_window = WinQueryWindow (Window, QW_OWNER);

    // Узнаем имя, под которым определено окно.
    CHAR Owner_name[SIZE_OF_NAME] = ""; WinQueryClassName (Owner_window, SIZE_OF_NAME, Owner_name);

    // Проверяем его.
    if (strc (Owner_name, "AgentCenterClass")) return 1;
    if (strc (Owner_name, "SPLG_WarpButton")) return 1;
  }

  // Возврат.
  return 0;
}

// ─── Проверяет, может ли данное окно быть окном XWP TaskBar ───

// Window - окно, которое надо проверить.
BYTE Repository_IsXWPTaskBarWindow (HWND Window)
{
  // Узнаем окно рабочей области.
  HWND Client_window = WinWindowFromID (Window, FID_CLIENT);

  if (Client_window != NULLHANDLE)
  {
    // Узнаем имя, под которым определено окно.
    CHAR Client_name[SIZE_OF_NAME] = ""; WinQueryClassName (Client_window, SIZE_OF_NAME, Client_name);

    // Если оно может быть окном XWP TaskBar:
    if (stristr ("XWPCenter", Client_name))
    {
      // Проверяем расположение окна.
      if (Repository_HasWarpCenterSize (Window)) return 1;
    }
  }

  // Возврат.
  return 0;
}

// ─── Проверяет, может ли данное окно быть окном меню XWP TaskBar ───

// Window - окно, которое надо проверить.
BYTE Repository_IsXWPTaskBarMenuWindow (HWND Window)
{
  // Если это окно меню:
  if (Repository_IsMenuWindow (Window))
  {
    // Узнаем окно владельца.
    HWND Owner_window = WinQueryWindow (Window, QW_OWNER);

    // Узнаем имя, под которым определено окно.
    CHAR Owner_name[SIZE_OF_NAME] = ""; WinQueryClassName (Owner_window, SIZE_OF_NAME, Owner_name);

    // Проверяем его.
    if (stristr ("XWPCenter", Owner_name)) return 1;
  }

  // Возврат.
  return 0;
}

// ─── Проверяет, может ли данное окно быть окном XWP Pager ───

// Window - окно, которое надо проверить.
BYTE Repository_IsXWPPagerWindow (HWND Frame_window)
{
  // Узнаем окно рабочей области.
  HWND Client_window = WinWindowFromID (Frame_window, FID_CLIENT);

  if (Client_window != NULLHANDLE)
  {
    // Узнаем имя, под которым определено окно.
    CHAR Client_name[SIZE_OF_NAME] = ""; WinQueryClassName (Client_window, SIZE_OF_NAME, Client_name);

    // Проверяем его.
    if (stristr ("XWPXPagerClient", Client_name)) return 1;
  }

  // Возврат.
  return 0;
}

// ─── Проверяет, может ли данное окно быть окном SafeFire ───

// Window - окно, которое надо проверить.
BYTE Repository_IsSafeFireWindow (HWND Frame_window)
{
  // Узнаем окно рабочей области.
  HWND Client_window = WinWindowFromID (Frame_window, FID_CLIENT);

  if (Client_window != NULLHANDLE)
  {
    // Узнаем имя, под которым определено окно.
    CHAR Client_name[SIZE_OF_NAME] = ""; WinQueryClassName (Client_window, SIZE_OF_NAME, Client_name);

    // Проверяем его.
    if (stristr ("Uni.Cell.Client", Client_name)) return 1;
  }

  // Возврат.
  return 0;
}

// ─── Проверяет, может ли данное окно быть окном системного сообщения ───

// Frame_window - окно, которое надо проверить.
BYTE Repository_IsSysMsgWindow (HWND Frame_window)
{
  // Узнаем окно рабочей области.
  HWND Client_window = WinWindowFromID (Frame_window, FID_CLIENT);

  if (Client_window != NULLHANDLE)
  {
    // Узнаем имя, под которым определено окно.
    CHAR Client_name[SIZE_OF_NAME] = ""; WinQueryClassName (Client_window, SIZE_OF_NAME, Client_name);

    // Проверяем его.
    if (strc (Client_name, "PM Hard Error")) return 1;
  }

  // Возврат.
  return 0;
}

