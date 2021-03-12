
// Внутренние переменные.
typedef struct _INSTALLERTHRD
{
  // Обработка файлов.
  TID Installer;
  HMQ Installer_queue;
  HAB Installer_anchor;

  // Что надо сделать.
  BYTE Install_Enhancer;
  BYTE Uninstall_Enhancer;

  // Каталог приложения.
  CHAR Current_directory[SIZE_OF_PATH];

  // Поток работает.
  BYTE Processing;
}
INSTALLERTHRD; INSTALLERTHRD Installer_Thread;

// ─── Исполняет приложение на Rexx ───

VOID Installer_ExecuteScript (VOID)
{
  // Задаем приложение и команду для него.
  CHAR Rexx_script[SIZE_OF_PATH] = "";
  strcpy (Rexx_script, Installer_Thread.Current_directory);
  strcat (Rexx_script, "\\Install\\Script.cmd");

  // Проверяем существование приложения.
  if (!FileExists (Rexx_script)) return;

  // Запускаем приложение.
  {
    CHAR Rexx_parameters[SIZE_OF_PATH] = "";

    if (Installer_Thread.Install_Enhancer) strcat (Rexx_parameters, " --action=install");
    if (Installer_Thread.Uninstall_Enhancer) strcat (Rexx_parameters, " --action=uninstall");
    if (Installer.Code_page == RUSSIAN) strcat (Rexx_parameters, " --language=russian");

    {
      CHAR Rexx_launcher[] = "Cmd.exe";
      CHAR Launcher_parameters[SIZE_OF_PATH] = "";

      strcpy (Launcher_parameters, Rexx_launcher);   strcat (Launcher_parameters, "|");
      strcat (Launcher_parameters, "/C");            strcat (Launcher_parameters, " \"");
      strcat (Launcher_parameters, Rexx_script);     strcat (Launcher_parameters, " ");
      strcat (Launcher_parameters, Rexx_parameters); strcat (Launcher_parameters, "\"");
      strchg (Launcher_parameters, '|', 0x00);

      CHAR Error_string[1] = ""; RESULTCODES Return_codes;
      CHAR Path[SIZE_OF_PATH] = "";
      strcpy (Path, Installer_Thread.Current_directory);
      strcat (Path, "\\Install");

      DosSetCurrentDir (Path);
      DosResetBuffer (-1); DosExecPgm (Error_string, sizeof (Error_string), EXEC_SYNC, Launcher_parameters, NULL, &Return_codes, Rexx_launcher);
      DosSetCurrentDir (Installer_Thread.Current_directory);
    }
  }

  // Возврат.
  return;
}

// ─── Поток для установки расширителя ───

VOID Installer_InstallerThread (VOID)
{
  // Определяем поток в системе.
  HAB Thread = WinInitialize (0);
  Installer_Thread.Installer_anchor = Thread;

  // Если это сделать не удалось - выход.
  if (Thread == NULLHANDLE) return;

  // Создаем очередь сообщений - она должна быть в каждом потоке.
  {
    HMQ Messages_queue = WinCreateMsgQueue (Thread, 0);
    Installer_Thread.Installer_queue = Messages_queue;

    // Если очередь создать не удалось - выход.
    if (Messages_queue == NULLHANDLE)
    {
      WinTerminate (Thread);
      return;
    }
  }

  // Отключаем кнопки
  WinPostMsg (Installer.Client_window, MY_ENABLE_BUTTONS, 0, 0);

  // Вызываем приложение на Rexx.
  Installer_ExecuteScript ();

  // Включаем кнопки
  WinPostMsg (Installer.Client_window, MY_ENABLE_BUTTONS, (MPARAM) 1, 0);

  // Закрываем окно.
  WinPostMsg (Installer.Frame_window, WM_SYSCOMMAND, (MPARAM) SC_CLOSE, 0);

  // Поток завершен.
  Installer_Thread.Processing = 0;

  // Завершаем поток.
  WinDestroyMsgQueue (Installer_Thread.Installer_queue);
  WinTerminate (Installer_Thread.Installer_anchor);
  Installer_Thread.Installer = NULLHANDLE;
  DosExit (EXIT_THREAD, 0); return;
}

// ─── Запускает поток ───

VOID StartInstallerThread (ULONG Action)
{
  // Если поток уже работает - возврат.
  if (Installer_Thread.Processing) return;

  // Запоминаем, что надо сделать.
  bzero (&Installer_Thread, sizeof (Installer_Thread));

  if (Action == NIA_INSTALL)
  {
    Installer_Thread.Install_Enhancer = 1;
  }
  else
  {
    Installer_Thread.Uninstall_Enhancer = 1;
  }

  // Узнаем рабочий каталог.
  {
    ULONG Current_drive = 0; ULONG Drive_map = 0; ULONG Length = SIZE_OF_PATH - 3;
    DosQueryCurrentDisk (&Current_drive, &Drive_map);
    Installer_Thread.Current_directory[0] = (CHAR) Current_drive + 64;
    Installer_Thread.Current_directory[1] = ':';
    Installer_Thread.Current_directory[2] = '\\';
    DosQueryCurrentDir (0, &Installer_Thread.Current_directory[3], &Length);
  }

  // Создаем поток.
  DosCreateThread (&Installer_Thread.Installer, (PFNTHREAD) Installer_InstallerThread, 0, 0, 32768);

  // Запоминаем, что он работает.
  Installer_Thread.Processing = 1;

  // Возврат.
  return;
}
