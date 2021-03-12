
// ��� �஢���� �᫮ �����஢ � ��⥬� ���

BYTE Environment_SMPSystem (VOID)
{
  // ������ �᫮ �����஢.
  INT Processors = 1; DosQuerySysInfo (QSV_NUMPROCESSORS, QSV_NUMPROCESSORS, (PULONG) &Processors, sizeof (Processors));

  // �஢��塞, ᪮�쪮 �� ����㯭� ᥩ��.
  if (Processors > 1) return 1;

  // ������.
  return 0;
}

// ��� ������ �ਫ������, ���� ���ண� ��࠭� ���

HAB Environment_ActiveApplication (VOID)
{
  // ���� ࠡ�祣� �⮫� �������⭮.
  HWND Desktop = HWND_DESKTOP;

  // ������ ����, ���஥ ᥩ�� ��࠭�.
  HWND Active_window = WinQueryActiveWindow (Desktop);

  // �᫨ ⠪��� ���� ��� - 㧭��� ����, ���஥ �ᯮ������ � �।��� �࠭�.
  if (Active_window == NULLHANDLE)
  {
    // ������ ࠧ��� �࠭�.
    INT X_Screen = WinQuerySysValue (Desktop, SV_CXSCREEN);
    INT Y_Screen = WinQuerySysValue (Desktop, SV_CYSCREEN);

    // ������ ���� ࠬ��, ���஥ �ᯮ������ � �।��� �࠭�.
    POINT Center_of_screen = { X_Screen / 2, Y_Screen / 2 };
    Active_window = WinWindowFromPoint (Desktop, &Center_of_screen, 0);
  }

  #ifndef INCLUDED_BY_SHELL

  // �᫨ � ⠪��� ���� ��� - �����頥� ᢮� ᮡ�⢥���� �ਫ������.
  if (Active_window == NULLHANDLE) return Enhancer.Application;

  #else

  // �᫨ � ⠪��� ���� ��� - �����頥� PMSHell.
  if (Active_window == NULLHANDLE) return WinQueryAnchorBlock (HWND_DESKTOP);

  #endif

  // �����頥� �ਫ������, � ���஬ ᮧ���� ����.
  return WinQueryAnchorBlock (Active_window);
}

// ��� ������ ���� ࠡ�祣� �⮫� ���

HWND Environment_QueryDesktopWindow (VOID)
{
  #ifndef INCLUDED_BY_SHELL

  // �᫨ ���� ࠡ�祣� �⮫� �������⭮ - 㧭��� ���.
  if (!Environment.RTSettings.Detected_Desktop_window)
  {
    Environment.RTSettings.Detected_Desktop_window = WinQueryDesktopWindow (Environment_ActiveApplication (), NULLHANDLE);
  }

  // �����頥� ���� ࠡ�祣� �⮫�.
  return Environment.RTSettings.Detected_Desktop_window;

  #else

  // �����頥� ���� ࠡ�祣� �⮫�.
  return HWND_DESKTOP;

  #endif
}

// ��� ������ ��࠭�, ����� ��⠭������ � OS/2 ���

ULONG Environment_QuerySystemCodePage (VOID)
{
  // ������ ��࠭�.
  ULONG Code_page = 0; ULONG Size_of_list = 0;
  DosQueryCp (sizeof (Code_page), &Code_page, &Size_of_list);

  // ������.
  return Code_page;
}

// ��� ������, ��⠭������ �� � ��⥬� �����প� DBCS ���

BYTE Environment_DBCSSupportIsEnabled (VOID)
{
  // �஢��塞 ��࠭�, � ���ன ࠡ�⠥� �ਫ������.
  CHAR DBCS_line[12] = ""; COUNTRYCODE Country = {0};
  DosQueryDBCSEnv (12, &Country, DBCS_line);

  if (DBCS_line[0] != 0) return 1;

  // ������.
  return 0;
}

// ��� ������ �६���� ��⠫�� ���

VOID Environment_QueryTempDirectory (PCHAR Temp_directory)
{
  // �����뢠�� �� ������ ��६����� �ਧ��� ���� ��ப�.
  Temp_directory[0] = 0;

  // �஢��塞 ��६���� �।�.
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

  // ������.
  return;
}
