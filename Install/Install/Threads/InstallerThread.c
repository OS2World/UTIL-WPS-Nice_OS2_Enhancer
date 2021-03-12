
// ����७��� ��६����.
typedef struct _INSTALLERTHRD
{
  // ��ࠡ�⪠ 䠩���.
  TID Installer;
  HMQ Installer_queue;
  HAB Installer_anchor;

  // �� ���� ᤥ����.
  BYTE Install_Enhancer;
  BYTE Uninstall_Enhancer;

  // ��⠫�� �ਫ������.
  CHAR Current_directory[SIZE_OF_PATH];

  // ��⮪ ࠡ�⠥�.
  BYTE Processing;
}
INSTALLERTHRD; INSTALLERTHRD Installer_Thread;

// ��� �ᯮ���� �ਫ������ �� Rexx ���

VOID Installer_ExecuteScript (VOID)
{
  // ������ �ਫ������ � ������� ��� ����.
  CHAR Rexx_script[SIZE_OF_PATH] = "";
  strcpy (Rexx_script, Installer_Thread.Current_directory);
  strcat (Rexx_script, "\\Install\\Script.cmd");

  // �஢��塞 ����⢮����� �ਫ������.
  if (!FileExists (Rexx_script)) return;

  // ����᪠�� �ਫ������.
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

  // ������.
  return;
}

// ��� ��⮪ ��� ��⠭���� ����⥫� ���

VOID Installer_InstallerThread (VOID)
{
  // ��।��塞 ��⮪ � ��⥬�.
  HAB Thread = WinInitialize (0);
  Installer_Thread.Installer_anchor = Thread;

  // �᫨ �� ᤥ���� �� 㤠���� - ��室.
  if (Thread == NULLHANDLE) return;

  // ������� ��।� ᮮ�饭�� - ��� ������ ���� � ������ ��⮪�.
  {
    HMQ Messages_queue = WinCreateMsgQueue (Thread, 0);
    Installer_Thread.Installer_queue = Messages_queue;

    // �᫨ ��।� ᮧ���� �� 㤠���� - ��室.
    if (Messages_queue == NULLHANDLE)
    {
      WinTerminate (Thread);
      return;
    }
  }

  // �⪫�砥� ������
  WinPostMsg (Installer.Client_window, MY_ENABLE_BUTTONS, 0, 0);

  // ��뢠�� �ਫ������ �� Rexx.
  Installer_ExecuteScript ();

  // ����砥� ������
  WinPostMsg (Installer.Client_window, MY_ENABLE_BUTTONS, (MPARAM) 1, 0);

  // ����뢠�� ����.
  WinPostMsg (Installer.Frame_window, WM_SYSCOMMAND, (MPARAM) SC_CLOSE, 0);

  // ��⮪ �����襭.
  Installer_Thread.Processing = 0;

  // �����蠥� ��⮪.
  WinDestroyMsgQueue (Installer_Thread.Installer_queue);
  WinTerminate (Installer_Thread.Installer_anchor);
  Installer_Thread.Installer = NULLHANDLE;
  DosExit (EXIT_THREAD, 0); return;
}

// ��� ����᪠�� ��⮪ ���

VOID StartInstallerThread (ULONG Action)
{
  // �᫨ ��⮪ 㦥 ࠡ�⠥� - ������.
  if (Installer_Thread.Processing) return;

  // ����������, �� ���� ᤥ����.
  bzero (&Installer_Thread, sizeof (Installer_Thread));

  if (Action == NIA_INSTALL)
  {
    Installer_Thread.Install_Enhancer = 1;
  }
  else
  {
    Installer_Thread.Uninstall_Enhancer = 1;
  }

  // ������ ࠡ�稩 ��⠫��.
  {
    ULONG Current_drive = 0; ULONG Drive_map = 0; ULONG Length = SIZE_OF_PATH - 3;
    DosQueryCurrentDisk (&Current_drive, &Drive_map);
    Installer_Thread.Current_directory[0] = (CHAR) Current_drive + 64;
    Installer_Thread.Current_directory[1] = ':';
    Installer_Thread.Current_directory[2] = '\\';
    DosQueryCurrentDir (0, &Installer_Thread.Current_directory[3], &Length);
  }

  // ������� ��⮪.
  DosCreateThread (&Installer_Thread.Installer, (PFNTHREAD) Installer_InstallerThread, 0, 0, 32768);

  // ����������, �� �� ࠡ�⠥�.
  Installer_Thread.Processing = 1;

  // ������.
  return;
}
