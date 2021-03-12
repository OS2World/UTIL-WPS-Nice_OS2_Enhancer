
// ─── Проверяет число процессоров в системе ───

BYTE Environment_SMPSystem (VOID)
{
  // Узнаем число процессоров.
  INT Processors = 1; DosQuerySysInfo (QSV_NUMPROCESSORS, QSV_NUMPROCESSORS, (PULONG) &Processors, sizeof (Processors));

  // Проверяем, сколько их доступно сейчас.
  if (Processors > 1) return 1;

  // Возврат.
  return 0;
}

// ─── Узнает приложение, окно которого выбрано ───

HAB Environment_ActiveApplication (VOID)
{
  // Окно рабочего стола неизвестно.
  HWND Desktop = HWND_DESKTOP;

  // Узнаем окно, которое сейчас выбрано.
  HWND Active_window = WinQueryActiveWindow (Desktop);

  // Если такого окна нет - узнаем окно, которое расположено в середине экрана.
  if (Active_window == NULLHANDLE)
  {
    // Узнаем размер экрана.
    INT X_Screen = WinQuerySysValue (Desktop, SV_CXSCREEN);
    INT Y_Screen = WinQuerySysValue (Desktop, SV_CYSCREEN);

    // Узнаем окно рамки, которое расположено в середине экрана.
    POINT Center_of_screen = { X_Screen / 2, Y_Screen / 2 };
    Active_window = WinWindowFromPoint (Desktop, &Center_of_screen, 0);
  }

  #ifndef INCLUDED_BY_SHELL

  // Если и такого окна нет - возвращаем свое собственное приложение.
  if (Active_window == NULLHANDLE) return Enhancer.Application;

  #else

  // Если и такого окна нет - возвращаем PMSHell.
  if (Active_window == NULLHANDLE) return WinQueryAnchorBlock (HWND_DESKTOP);

  #endif

  // Возвращаем приложение, в котором создано окно.
  return WinQueryAnchorBlock (Active_window);
}

// ─── Узнает окно рабочего стола ───

HWND Environment_QueryDesktopWindow (VOID)
{
  #ifndef INCLUDED_BY_SHELL

  // Если окно рабочего стола неизвестно - узнаем его.
  if (!Environment.RTSettings.Detected_Desktop_window)
  {
    Environment.RTSettings.Detected_Desktop_window = WinQueryDesktopWindow (Environment_ActiveApplication (), NULLHANDLE);
  }

  // Возвращаем окно рабочего стола.
  return Environment.RTSettings.Detected_Desktop_window;

  #else

  // Возвращаем окно рабочего стола.
  return HWND_DESKTOP;

  #endif
}

// ─── Узнает страну, которая установлена в OS/2 ───

ULONG Environment_QuerySystemCodePage (VOID)
{
  // Узнаем страну.
  ULONG Code_page = 0; ULONG Size_of_list = 0;
  DosQueryCp (sizeof (Code_page), &Code_page, &Size_of_list);

  // Возврат.
  return Code_page;
}

// ─── Узнает, установлена ли в системе поддержка DBCS ───

BYTE Environment_DBCSSupportIsEnabled (VOID)
{
  // Проверяем страну, в которой работает приложение.
  CHAR DBCS_line[12] = ""; COUNTRYCODE Country = {0};
  DosQueryDBCSEnv (12, &Country, DBCS_line);

  if (DBCS_line[0] != 0) return 1;

  // Возврат.
  return 0;
}

// ─── Узнает временный каталог ───

VOID Environment_QueryTempDirectory (PCHAR Temp_directory)
{
  // Записываем во внешнюю переменную признак конца строки.
  Temp_directory[0] = 0;

  // Проверяем переменные среды.
  for (INT Count = 0; Count < 4; Count ++)
  {
    PCHAR Environment_variable = "";
    if (Count == 0) Environment_variable = "TEMP";
    if (Count == 1) Environment_variable = "TMP";
    if (Count == 2) Environment_variable = "TEMPDIR";
    if (Count == 3) Environment_variable = "TMPDIR";

    PCHAR TempDir_ptr = NULL; DosScanEnv (Environment_variable, (PPCSZ) &TempDir_ptr);
    if (TempDir_ptr) { strcpy (Temp_directory, TempDir_ptr); break; }
  }

  // Возврат.
  return;
}
