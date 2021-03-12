
// ��� �஢���� ����稥 䠩�� ���

// File_name - ��� 䠩��.
BYTE Files_FileExists (PCHAR File_name)
{
  // �஡㥬 ������� �����-���� ᢥ����� � 䠩��.
  FILESTATUS3 Attributes = {0};
  if (DosQueryPathInfo (File_name, FIL_STANDARD, &Attributes, sizeof (Attributes)) == NO_ERROR)
   return 1;

  // ������.
  return 0;
}

// ��� �����頥� ⥪�騩 ��⠫�� ��� ����஥� ���

// Current_directory - ��६����� ��� ���.
VOID Files_GetCurrentPath (PCHAR Current_directory)
{
  // �롨ࠥ� ����.
  ULONG Current_drive = 0; ULONG Drive_map = 0; ULONG Length = SIZE_OF_PATH - 3;

  DosQueryCurrentDisk (&Current_drive, &Drive_map);
  Current_directory[0] = (CHAR) Current_drive + 64;
  Current_directory[1] = ':'; Current_directory[2] = '\\';
  DosQueryCurrentDir (0, &Current_directory[3], &Length);

  // ������.
  return;
}

// ��� ���뢠�� 䠩� ����஥� ��� ᮧ���� ��� ���

// Application - ������ �ਫ������, File_name - ��� 䠩�� ����஥�.
HINI Files_OpenIniProfile (HAB Application, PCHAR File_name)
{
  // �᫨ 䠩�� ����஥� ��� - ᮧ���� ���.
  HFILE File = NULLHANDLE; ULONG Report = 0; ULONG New_size = 0; PEAOP2 EAs = NULL;

  ULONG Action = OPEN_ACTION_FAIL_IF_EXISTS | OPEN_ACTION_CREATE_IF_NEW;
  ULONG Mode = OPEN_FLAGS_FAIL_ON_ERROR | OPEN_SHARE_DENYWRITE | OPEN_ACCESS_WRITEONLY;

  DosOpen (File_name, &File, &Report, New_size, FILE_COMMON_ATTRIBUTES, Action, Mode, EAs);

  // �᫨ 䠩� �� ᮧ��� - �����뢠�� � ���� ���祭�� �� 㬮�砭��.
  if (Report == FILE_CREATED)
  {
    INT Length = 20; BYTE Empty_ini[20] = { 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0, 0x14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    DosWrite (File, Empty_ini, Length, &Report);
  }

  // ����뢠�� 䠩�.
  DosClose (File); File = NULLHANDLE;

  // ����뢠�� ��� 䠩�� ᢮��⢮ "���쪮 ��� �⥭��".
  {
    FILESTATUS3 File_status = {0};
    DosSetPathInfo (File_name, FIL_STANDARD, &File_status, sizeof (File_status), DSPI_WRTTHRU);
  }

  // ���뢠�� 䠩� ����஥� � �����頥� ���.
  return PrfOpenProfile (Application, File_name);
}

// ��� ������ ���� ��᪠ ���

// Drive_name - ��� ��᪠, Drive_label - ��६����� ��� ��⪨.
VOID Files_QueryDriveLabel (PCHAR Drive_name, PCHAR Drive_label)
{
  // ������ ����.
  ULONG DriveNumber = Drive_name[0] - 64;

  BYTE FSInfoBuf[255]; ULONG FSInfoBufSize = 255;
  bzero (FSInfoBuf, FSInfoBufSize);

  DosQueryFSInfo (DriveNumber, FSIL_VOLSER, FSInfoBuf, FSInfoBufSize);

  // ���������� ��.
  strcpy (Drive_label, &FSInfoBuf[5]);

  // ������.
  return;
}

// ��� �஢���� ���� ��᪠ ��

// Label - ��⪠ ��᪠.
BYTE Files_DriveLabelHasSpecialChars (PCHAR Label)
{
  INT Length = strlen (Label); INT Count;

  for (Count = 0; Count < Length; Count ++)
   if (Label[Count] < 'A' || Label[Count] > 'Z')
    if (Label[Count] < 'a' || Label[Count] > 'z')
     if (Label[Count] < '0' || Label[Count] > '9')
      if (Label[Count] != '_')
       if (Label[Count] != '-')
        return 1;

  // ������.
  return 0;
}

// ��� ������ ⨯ � �������� 䠩����� ��⥬� ���

// Drive_name - ��� ��᪠, FS_name - ��ப� ��� ��������, FS_type - �᫮ ��� ⨯�.
VOID Files_QueryFSNameType (PCHAR Drive_name, PCHAR FS_name, PULONG FS_type = NULL)
{
  // ���頥��� � 䠩����� ��⥬�.
  PFSQBUFFER2 Data = NULL; ULONG Data_length = 1024;

  if (DosAllocMem ((PPVOID) &Data, Data_length, PAG_ALLOCATE) == NO_ERROR)
  {
    CHAR Drive[3] = { Drive_name[0], Drive_name[1], 0 };

    if (DosQueryFSAttach (Drive, 0, FSAIL_QUERYNAME, Data, &Data_length) == NO_ERROR)
    {
      PCHAR Reported_Drive_name = (PCHAR) Data->szName;
      PCHAR Reported_FS_name = "*";

      PBYTE Delimeter_byte = (PBYTE) &Data->szName + Data->cbName;
      if (*Delimeter_byte == 0) Reported_FS_name = (PCHAR) &Data->szName + Data->cbName + 1;

      if (FS_name != NULL) strncpy (FS_name, Reported_FS_name, sizeof (Reported_FS_name));
      if (FS_type != NULL) *FS_type = Data->iType;
    }

    DosFreeMem (Data); Data = NULL;
  }

  // ������.
  return;
}

// ��� �஢���� ����㯭���� ��᪠ ���

// Drive_name - ��� ��᪠.
BYTE Files_DriveIsAvailable (PCHAR Drive_name)
{
  // ������ ��� � �������� 䠩����� ��⥬�.
  ULONG Type = 0; CHAR FileSystem_name[25] = "";
  Files_QueryFSNameType (Drive_name, FileSystem_name, &Type);

  // �᫨ ��� 㧭��� �� 㤠���� - ��� ������㯥�.
  if (FileSystem_name[0] == 0) return 0;

  // ��⥢� ��᪨ ��� �� �㦭� (���ன�⢠ RAMFS ��।������� ��� �⥢�, �� ���뢠�� ��).
  if (Type != FSAT_LOCALDRV) if (!strstr ("RAM", FileSystem_name)) return 0;

  // ���ਣ���� ��� ���᪠ - ⮦�.
  if (strstr ("CDFS", FileSystem_name)) return 0;
  if (strstr ("UDF", FileSystem_name)) return 0;

  if (strstr ("FAT", FileSystem_name)) return 0;
  if (strstr ("NTFS", FileSystem_name)) return 0;

  if (strstr ("HFS", FileSystem_name)) return 0;
  if (strstr ("EXT", FileSystem_name)) return 0;

  if (strstr ("FTP", FileSystem_name)) return 0;
  if (strstr ("NET", FileSystem_name)) return 0;

  {
    CHAR Label[SIZE_OF_NAME] = ""; Files_QueryDriveLabel (Drive_name, Label);
    if (Files_DriveLabelHasSpecialChars (Label)) return 0;
  }

  // ������.
  return 1;
}

// ��� �����頥� ��� RAM-��᪠, �᫨ �� ���� ���

// Drive_name - ��� ��᪠.
VOID Files_FindRAMDrive (PCHAR Memory_drive)
{
  // �����뢠�� �� ������ ��६����� �ਧ��� ���� ��ப�
  Memory_drive[0] = 0;

  // ��ॡ�ࠥ� ��᪨.
  INT Letter = 0;

  for (Letter = 'C'; Letter <= 'Z'; Letter ++)
  {
    // ������ �������� 䠩����� ��⥬�.
    CHAR Drive_name[3] = { Letter, ':', 0 };

    CHAR FileSystem_name[25] = "";
    Files_QueryFSNameType (Drive_name, FileSystem_name);

    // �஢��塞 ���.
    if (FileSystem_name[0] != 0)
     if (strstr ("RAM", FileSystem_name))
     {
       Memory_drive[0] = Letter;
       Memory_drive[1] = ':';
       Memory_drive[2] = 0;

       break;
     }
  }

  // ������.
  return;
}

// ��� �����頥� ���浪��� ����� ���ன�⢠ ���

// Path - ������ ����.
INT Files_DriveNumberFromPath (PCHAR Path)
{
  // �᫨ ���ன�⢮ ������:
  if (strlen (Path) > 2)
   if (Path[1] == ':')
    if (Path[2] == '\\' || Path[2] == '/')
    {
      // �롨ࠥ� ����� �㪢� � �����頥� ����� ���ன�⢠.
      CHAR Drive[2] = { Path[0], 0 }; UpperCase (Drive);
      return Drive[0] - 64;
    }

  // ������.
  return -1;
}

// ��� ��室�� ��� � ��� ���

// Path - ������ ��� ���⪨� ����.
PCHAR Files_FindNameInPath (PCHAR Path)
{
  // ��室�� ��᫥���� ࠧ����⥫�.
  INT Count = 0; INT Length = strlen (Path);

  for (Count = Length - 1; Count > 0; Count --)
   if (Path[Count - 1] == '\\' || Path[Count - 1] == '/')
    return &Path[Count];

  // ������.
  return &Path[0];
}

// ��� ������ ��� �� ��� ���

// Path - ������ ��� ���⪨� ����.
VOID Files_CutNameInPath (PCHAR Path)
{
  // ��室�� ��᫥���� ࠧ����⥫�.
  PCHAR Name = Files_FindNameInPath (Path);

  // �⠢�� �㤠 �ਧ��� ���� ��ப�.
  if (Name != &Path[0]) *(Name - 1) = 0;

  // �᫨ ��⠫��� ⮫쪮 ��� ��᪠ - ������塞 ࠧ����⥫�.
  if (strlen (Path) == 2) if (Path[1] == ':') strcat (Path, "\\");

  // ������.
  return;
}

// ��� ������ ࠧ����⥫� � ���� ��� ���

// Path - ������ ��� ���⪨� ����.
VOID Files_CutLastSlash (PCHAR Path)
{
  // ����塞 ࠧ����⥫�, �᫨ �� ����.
  INT Length = strlen (Path);

  while (Path[Length - 1] == '\\' || Path[Length - 1] == '/')
  {
    Path[Length - 1] = 0; Length --; if (Length == 0) break;
  }

  // ������.
  return;
}

// ��� ��뢠�� �ਫ������ ���

// App_name - ���� � �ਫ������, Title - ��������� ����, App_params - ��ࠬ���� ��� ����.
// �᫨ ���祭�� Placement ࠢ�� "SWP_MINIMIZE", �ਫ������ �㤥� 㬥��襭� � ���箪.
HAPP Files_Execute (PCHAR App_name, PCHAR App_params = NULL, PCHAR Title = NULL, ULONG Placement = 0)
{
  // ����塞 �஡��� � ���� �����.
  INT Length = strlen (App_name); INT End = Length - 1;
  while (App_name[End] == ' ') { App_name[End] = 0; End --; }

  // ��������, �ॡ���� �믮����� Exe-�ਫ������ ��� �ਯ� �� Rexx.
  BYTE OS2Warp_Exe = 0; if (stric (".exe", &App_name[End - 3])) OS2Warp_Exe = 1;
  BYTE Rexx_script = 0; if (stric (".cmd", &App_name[End - 3])) Rexx_script = 1;

  CHAR App_path[SIZE_OF_PATH] = "C:\\";
  if (strstr (":\\", App_name)) { strcpy (App_path, App_name); Files_CutNameInPath (App_path); }

  // �᫨ �� ��몭������� �ਫ������:
  if (OS2Warp_Exe)
  {
    // �᫨ �� ������ ���������/�ᯮ������� ����:
    if (!Title && !Placement)
    {
      // ������ ��ࠬ���� ��� ����᪠ �ਫ������.
      CHAR Parameters[SIZE_OF_PATH] = "";
      strcpy (Parameters, App_name);
      strcat (Parameters, "|");

      if (App_params != NULL) strcat (Parameters, App_params);

      strchg (Parameters, '|', 0x00);

      // ����뢠�� �� ��⮪� �����-�뢮��.
      DosResetBuffer (-1);

      // ��뢠�� �ਫ������.
      CHAR Current_directory[SIZE_OF_PATH] = ""; Files_GetCurrentPath (Current_directory);

      DosSetDefaultDisk (Files_DriveNumberFromPath (App_path)); DosSetCurrentDir (App_path);
      CHAR Error_string[1]; RESULTCODES Return_codes; DosExecPgm (Error_string, sizeof (Error_string), EXEC_ASYNC, Parameters, NULL, &Return_codes, App_name);
      DosSetDefaultDisk (Files_DriveNumberFromPath (Current_directory)); DosSetCurrentDir (Current_directory);

      // ������.
      return 1;
    }
    // � �᫨ ����� ��������� ��� ������ �ᯮ�������:
    else
    {
      // ������ ��ࠬ���� ��� ����᪠ �ਫ������.
      PROGDETAILS Details; bzero (&Details, sizeof (PROGDETAILS)); Details.Length = sizeof (PROGDETAILS);

      Details.pszExecutable = App_name;
      Details.pszStartupDir = App_path;

      Details.pszEnvironment = "\0\0";
      Details.pszParameters = NULL;

      // ������ ��������� ����.
      if (Title != NULL) Details.pszTitle = Title;

      // ������ �ᯮ������� ����.
      if (Placement != SWP_MINIMIZE)
      {
        Details.swpInitial.fl = SWP_SHOW | SWP_ACTIVATE | SWP_ZORDER;
        Details.swpInitial.hwndInsertBehind = HWND_TOP;
      }
      else
      {
        Details.swpInitial.fl = SWP_MINIMIZE;
      }

      // ����뢠�� �� ��⮪� �����-�뢮��.
      DosResetBuffer (-1);

      // ��뢠�� �ਫ������.
      CHAR Current_directory[SIZE_OF_PATH] = ""; Files_GetCurrentPath (Current_directory);

      DosSetDefaultDisk (Files_DriveNumberFromPath (App_path)); DosSetCurrentDir (App_path);
      HAPP PM_Handle = WinStartApp (NULLHANDLE, &Details, NULL, NULL, 0);
      DosSetDefaultDisk (Files_DriveNumberFromPath (Current_directory)); DosSetCurrentDir (Current_directory);

      // ������.
      return PM_Handle;
    }
  }

  // �᫨ �� Rexx-�ਯ�:
  if (Rexx_script)
  {
    // ������ ��ࠬ���� ��� ����᪠ "Cmd.exe".
    CHAR Cmd_exe[SIZE_OF_PATH] = "";
    strcpy (Cmd_exe, "Cmd.exe");

    CHAR Parameters[SIZE_OF_PATH] = "";
    strcpy (Parameters, Cmd_exe);
    strcat (Parameters, "|");

    strcat (Parameters, "/C Start ");

    strcat (Parameters, "\"");
    if (Title != NULL) strcat (Parameters, Title);
    else strcat (Parameters, Files_FindNameInPath (App_name));
    strcat (Parameters, "\"");

    strcat (Parameters, "/I /C ");

    if (Placement != SWP_MINIMIZE) strcat (Parameters, "/F ");
    else strcat (Parameters, "/MIN ");

    strcat (Parameters, App_name);
    if (App_params != NULL) { strcat (Parameters, " "); strcat (Parameters, App_params); }

    strchg (Parameters, '|', 0x00);

    // ����뢠�� �� ��⮪� �����-�뢮��.
    DosResetBuffer (-1);

    // ��뢠�� "Cmd.exe".
    CHAR Current_directory[SIZE_OF_PATH] = ""; Files_GetCurrentPath (Current_directory);

    DosSetDefaultDisk (Files_DriveNumberFromPath (App_path)); DosSetCurrentDir (App_path);
    CHAR Error_string[1]; RESULTCODES Return_codes; DosExecPgm (Error_string, sizeof (Error_string), EXEC_SYNC, Parameters, NULL, &Return_codes, Cmd_exe);
    DosSetDefaultDisk (Files_DriveNumberFromPath (Current_directory)); DosSetCurrentDir (Current_directory);

    // ������.
    return 1;
  }

  // ������.
  return 0;
}

