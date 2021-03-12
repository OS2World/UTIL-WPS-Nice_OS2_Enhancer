
// ─── Проверяет наличие файла ───

// File_name - имя файла.
BYTE Files_FileExists (PCHAR File_name)
{
  // Пробуем получить какие-либо сведения о файле.
  FILESTATUS3 Attributes = {0};
  if (DosQueryPathInfo (File_name, FIL_STANDARD, &Attributes, sizeof (Attributes)) == NO_ERROR)
   return 1;

  // Возврат.
  return 0;
}

// ─── Возвращает текущий каталог для настроек ───

// Current_directory - переменная для пути.
VOID Files_GetCurrentPath (PCHAR Current_directory)
{
  // Выбираем путь.
  ULONG Current_drive = 0; ULONG Drive_map = 0; ULONG Length = SIZE_OF_PATH - 3;

  DosQueryCurrentDisk (&Current_drive, &Drive_map);
  Current_directory[0] = (CHAR) Current_drive + 64;
  Current_directory[1] = ':'; Current_directory[2] = '\\';
  DosQueryCurrentDir (0, &Current_directory[3], &Length);

  // Возврат.
  return;
}

// ─── Открывает файл настроек или создает его ───

// Application - данное приложение, File_name - имя файла настроек.
HINI Files_OpenIniProfile (HAB Application, PCHAR File_name)
{
  // Если файла настроек нет - создаем его.
  HFILE File = NULLHANDLE; ULONG Report = 0; ULONG New_size = 0; PEAOP2 EAs = NULL;

  ULONG Action = OPEN_ACTION_FAIL_IF_EXISTS | OPEN_ACTION_CREATE_IF_NEW;
  ULONG Mode = OPEN_FLAGS_FAIL_ON_ERROR | OPEN_SHARE_DENYWRITE | OPEN_ACCESS_WRITEONLY;

  DosOpen (File_name, &File, &Report, New_size, FILE_COMMON_ATTRIBUTES, Action, Mode, EAs);

  // Если файл был создан - записываем в него значение по умолчанию.
  if (Report == FILE_CREATED)
  {
    INT Length = 20; BYTE Empty_ini[20] = { 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0, 0x14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    DosWrite (File, Empty_ini, Length, &Report);
  }

  // Закрываем файл.
  DosClose (File); File = NULLHANDLE;

  // Сбрасываем для файла свойство "Только для чтения".
  {
    FILESTATUS3 File_status = {0};
    DosSetPathInfo (File_name, FIL_STANDARD, &File_status, sizeof (File_status), DSPI_WRTTHRU);
  }

  // Открываем файл настроек и возвращаем его.
  return PrfOpenProfile (Application, File_name);
}

// ─── Узнает метку диска ───

// Drive_name - имя диска, Drive_label - переменная для метки.
VOID Files_QueryDriveLabel (PCHAR Drive_name, PCHAR Drive_label)
{
  // Узнаем метку.
  ULONG DriveNumber = Drive_name[0] - 64;

  BYTE FSInfoBuf[255]; ULONG FSInfoBufSize = 255;
  bzero (FSInfoBuf, FSInfoBufSize);

  DosQueryFSInfo (DriveNumber, FSIL_VOLSER, FSInfoBuf, FSInfoBufSize);

  // Запоминаем ее.
  strcpy (Drive_label, &FSInfoBuf[5]);

  // Возврат.
  return;
}

// ─── Проверяет метку диска ──

// Label - метка диска.
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

  // Возврат.
  return 0;
}

// ─── Узнает тип и название файловой системы ───

// Drive_name - имя диска, FS_name - строка для названия, FS_type - число для типа.
VOID Files_QueryFSNameType (PCHAR Drive_name, PCHAR FS_name, PULONG FS_type = NULL)
{
  // Обращаемся к файловой системе.
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

  // Возврат.
  return;
}

// ─── Проверяет доступность диска ───

// Drive_name - имя диска.
BYTE Files_DriveIsAvailable (PCHAR Drive_name)
{
  // Узнаем вид и название файловой системы.
  ULONG Type = 0; CHAR FileSystem_name[25] = "";
  Files_QueryFSNameType (Drive_name, FileSystem_name, &Type);

  // Если имя узнать не удалось - диск недоступен.
  if (FileSystem_name[0] == 0) return 0;

  // Сетевые диски нам не нужны (устройства RAMFS определяются как сетевые, не учитываем их).
  if (Type != FSAT_LOCALDRV) if (!strstr ("RAM", FileSystem_name)) return 0;

  // Непригодные для поиска - тоже.
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

  // Возврат.
  return 1;
}

// ─── Возвращает имя RAM-диска, если он есть ───

// Drive_name - имя диска.
VOID Files_FindRAMDrive (PCHAR Memory_drive)
{
  // Записываем во внешнюю переменную признак конца строки
  Memory_drive[0] = 0;

  // Перебираем диски.
  INT Letter = 0;

  for (Letter = 'C'; Letter <= 'Z'; Letter ++)
  {
    // Узнаем название файловой системы.
    CHAR Drive_name[3] = { Letter, ':', 0 };

    CHAR FileSystem_name[25] = "";
    Files_QueryFSNameType (Drive_name, FileSystem_name);

    // Проверяем его.
    if (FileSystem_name[0] != 0)
     if (strstr ("RAM", FileSystem_name))
     {
       Memory_drive[0] = Letter;
       Memory_drive[1] = ':';
       Memory_drive[2] = 0;

       break;
     }
  }

  // Возврат.
  return;
}

// ─── Возвращает порядковый номер устройства ───

// Path - длинный путь.
INT Files_DriveNumberFromPath (PCHAR Path)
{
  // Если устройство задано:
  if (strlen (Path) > 2)
   if (Path[1] == ':')
    if (Path[2] == '\\' || Path[2] == '/')
    {
      // Выбираем первую букву и возвращаем номер устройства.
      CHAR Drive[2] = { Path[0], 0 }; UpperCase (Drive);
      return Drive[0] - 64;
    }

  // Возврат.
  return -1;
}

// ─── Находит имя в пути ───

// Path - длинный или короткий путь.
PCHAR Files_FindNameInPath (PCHAR Path)
{
  // Находим последний разделитель.
  INT Count = 0; INT Length = strlen (Path);

  for (Count = Length - 1; Count > 0; Count --)
   if (Path[Count - 1] == '\\' || Path[Count - 1] == '/')
    return &Path[Count];

  // Возврат.
  return &Path[0];
}

// ─── Удаляет имя из пути ───

// Path - длинный или короткий путь.
VOID Files_CutNameInPath (PCHAR Path)
{
  // Находим последний разделитель.
  PCHAR Name = Files_FindNameInPath (Path);

  // Ставим туда признак конца строки.
  if (Name != &Path[0]) *(Name - 1) = 0;

  // Если осталось только имя диска - добавляем разделитель.
  if (strlen (Path) == 2) if (Path[1] == ':') strcat (Path, "\\");

  // Возврат.
  return;
}

// ─── Удаляет разделитель в конце пути ───

// Path - длинный или короткий путь.
VOID Files_CutLastSlash (PCHAR Path)
{
  // Удаляем разделитель, если он есть.
  INT Length = strlen (Path);

  while (Path[Length - 1] == '\\' || Path[Length - 1] == '/')
  {
    Path[Length - 1] = 0; Length --; if (Length == 0) break;
  }

  // Возврат.
  return;
}

// ─── Вызывает приложение ───

// App_name - путь к приложению, Title - заголовок окна, App_params - параметры для него.
// Если значение Placement равно "SWP_MINIMIZE", приложение будет уменьшено в значок.
HAPP Files_Execute (PCHAR App_name, PCHAR App_params = NULL, PCHAR Title = NULL, ULONG Placement = 0)
{
  // Удаляем пробелы в конце имени.
  INT Length = strlen (App_name); INT End = Length - 1;
  while (App_name[End] == ' ') { App_name[End] = 0; End --; }

  // Возможно, требуется выполнить Exe-приложение или скрипт на Rexx.
  BYTE OS2Warp_Exe = 0; if (stric (".exe", &App_name[End - 3])) OS2Warp_Exe = 1;
  BYTE Rexx_script = 0; if (stric (".cmd", &App_name[End - 3])) Rexx_script = 1;

  CHAR App_path[SIZE_OF_PATH] = "C:\\";
  if (strstr (":\\", App_name)) { strcpy (App_path, App_name); Files_CutNameInPath (App_path); }

  // Если это обыкновенное приложение:
  if (OS2Warp_Exe)
  {
    // Если не заданы заголовок/расположение окна:
    if (!Title && !Placement)
    {
      // Задаем параметры для запуска приложения.
      CHAR Parameters[SIZE_OF_PATH] = "";
      strcpy (Parameters, App_name);
      strcat (Parameters, "|");

      if (App_params != NULL) strcat (Parameters, App_params);

      strchg (Parameters, '|', 0x00);

      // Сбрасываем все потоки ввода-вывода.
      DosResetBuffer (-1);

      // Вызываем приложение.
      CHAR Current_directory[SIZE_OF_PATH] = ""; Files_GetCurrentPath (Current_directory);

      DosSetDefaultDisk (Files_DriveNumberFromPath (App_path)); DosSetCurrentDir (App_path);
      CHAR Error_string[1]; RESULTCODES Return_codes; DosExecPgm (Error_string, sizeof (Error_string), EXEC_ASYNC, Parameters, NULL, &Return_codes, App_name);
      DosSetDefaultDisk (Files_DriveNumberFromPath (Current_directory)); DosSetCurrentDir (Current_directory);

      // Возврат.
      return 1;
    }
    // А если задан заголовок или задано расположение:
    else
    {
      // Задаем параметры для запуска приложения.
      PROGDETAILS Details; bzero (&Details, sizeof (PROGDETAILS)); Details.Length = sizeof (PROGDETAILS);

      Details.pszExecutable = App_name;
      Details.pszStartupDir = App_path;

      Details.pszEnvironment = "\0\0";
      Details.pszParameters = NULL;

      // Задаем заголовок окна.
      if (Title != NULL) Details.pszTitle = Title;

      // Задаем расположение окна.
      if (Placement != SWP_MINIMIZE)
      {
        Details.swpInitial.fl = SWP_SHOW | SWP_ACTIVATE | SWP_ZORDER;
        Details.swpInitial.hwndInsertBehind = HWND_TOP;
      }
      else
      {
        Details.swpInitial.fl = SWP_MINIMIZE;
      }

      // Сбрасываем все потоки ввода-вывода.
      DosResetBuffer (-1);

      // Вызываем приложение.
      CHAR Current_directory[SIZE_OF_PATH] = ""; Files_GetCurrentPath (Current_directory);

      DosSetDefaultDisk (Files_DriveNumberFromPath (App_path)); DosSetCurrentDir (App_path);
      HAPP PM_Handle = WinStartApp (NULLHANDLE, &Details, NULL, NULL, 0);
      DosSetDefaultDisk (Files_DriveNumberFromPath (Current_directory)); DosSetCurrentDir (Current_directory);

      // Возврат.
      return PM_Handle;
    }
  }

  // Если это Rexx-скрипт:
  if (Rexx_script)
  {
    // Задаем параметры для запуска "Cmd.exe".
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

    // Сбрасываем все потоки ввода-вывода.
    DosResetBuffer (-1);

    // Вызываем "Cmd.exe".
    CHAR Current_directory[SIZE_OF_PATH] = ""; Files_GetCurrentPath (Current_directory);

    DosSetDefaultDisk (Files_DriveNumberFromPath (App_path)); DosSetCurrentDir (App_path);
    CHAR Error_string[1]; RESULTCODES Return_codes; DosExecPgm (Error_string, sizeof (Error_string), EXEC_SYNC, Parameters, NULL, &Return_codes, Cmd_exe);
    DosSetDefaultDisk (Files_DriveNumberFromPath (Current_directory)); DosSetCurrentDir (Current_directory);

    // Возврат.
    return 1;
  }

  // Возврат.
  return 0;
}

