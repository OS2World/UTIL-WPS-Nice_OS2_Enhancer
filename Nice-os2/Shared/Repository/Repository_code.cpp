
// ��� �����稢��� ���稪 ᯨ᪠ ���

VOID Repository_next( PINT I )
{
 INT Value = *I;
 if( Value < MAX_RP_ENTRIES - 1 )
  {
   Value ++; *I = Value;
  }
 else
  {
   WinMessageBox( HWND_DESKTOP, HWND_DESKTOP, "[ MAX_RP_ENTRIES ]", "", NULLHANDLE, NULLHANDLE );
   DosExit( EXIT_PROCESS, 0 );
  }
}

// ��� ����뢠�� ������ ᯨ᪠ ���

VOID Repository_clear( PAPPLICATIONS Pointer )
{
 bzero( Pointer, sizeof( APPLICATIONS ) );
}

// ��� ������ ᯨ᮪ �������� ����⥫� �ਫ������ ���

VOID Repository_SetRepository( VOID )
{
 // ������ �ਫ������.
 INT I = -1;

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_NICE;
 Repository.Items[ I ].Purpose = DO_IMPROVE_WORKPLACE;
 strcpy( Repository.Items[ I ].Exe_name_1, "Nice-os2.exe" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_NICE_ECS;
 strcpy( Repository.Items[ I ].Exe_name_1, "Nice-ecs.exe" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_CMD;
 Repository.Items[ I ].Purpose = DO_EXECUTE_COMMANDS;
 strcpy( Repository.Items[ I ].Exe_name_1, "Cmd.exe" );
 strcpy( Repository.Items[ I ].Exe_name_2, "4os2.exe" );
 strcpy( Repository.Items[ I ].Exe_name_2, "YaOS.exe" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_COM;
 Repository.Items[ I ].Purpose = DO_EXECUTE_COMMANDS;
 strcpy( Repository.Items[ I ].Exe_name_1, "Mode.com" );
 strcpy( Repository.Items[ I ].Exe_name_2, "Keyb.com" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_JAVA_RUNTIME;
 Repository.Items[ I ].Purpose = DO_EXECUTE_APPLICATIONS;
 strcpy( Repository.Items[ I ].Exe_name_1, "Java.exe" );
 strcpy( Repository.Items[ I ].Exe_name_2, "JavaPM.exe" );
 strcpy( Repository.Items[ I ].Exe_name_3, "Jre.exe" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_APPLETVIEWER;
 Repository.Items[ I ].Purpose = DO_EXECUTE_APPLICATIONS;
 strcpy( Repository.Items[ I ].Exe_name_1, "Applet.exe" );
 strcpy( Repository.Items[ I ].Exe_name_2, "AppletViewer.exe" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_WATCHCAT;
 Repository.Items[ I ].Purpose = DO_MONITOR_SYSTEM;
 Repository.Items[ I ].Action = SHOW_TASK_MANAGER;
 Repository.Items[ I ].Desired = 1;
 strcpy( Repository.Items[ I ].Exe_name_1, "WatchCat.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "WatchCat object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "WatchCat path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_THESEUS;
 Repository.Items[ I ].Purpose = DO_MONITOR_SYSTEM;
 Repository.Items[ I ].Action = SHOW_TASK_MANAGER;
 strcpy( Repository.Items[ I ].Exe_name_1, "Theseus3.exe" );
 strcpy( Repository.Items[ I ].Exe_name_2, "Theseus4.exe" );
 strcpy( Repository.Items[ I ].Exe_name_3, "Theseus5.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "Theseus object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "Theseus path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_KTASKMAN;
 Repository.Items[ I ].Purpose = DO_MONITOR_SYSTEM;
 Repository.Items[ I ].Action = SHOW_TASK_MANAGER;
 strcpy( Repository.Items[ I ].Exe_name_1, "kTaskMgr.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "kTaskManager object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "kTaskManager path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_MPCPUMON;
 Repository.Items[ I ].Purpose = DO_MONITOR_SYSTEM;
 Repository.Items[ I ].Action = SHOW_PULSE;
 strcpy( Repository.Items[ I ].WPS_name_A, "<WP_PULSE>" );
 strcpy( Repository.Items[ I ].Exe_name_1, "MPCPUMon.exe" );
 strcpy( Repository.Items[ I ].Exe_name_1, "Pulse.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "MPCPUMonitor object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "MPCPUMonitor path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_SYSTEMLOAD;
 Repository.Items[ I ].Purpose = DO_MONITOR_SYSTEM;
 Repository.Items[ I ].Action = SHOW_PULSE;
 strcpy( Repository.Items[ I ].WPS_name_A, "<SYSTEMLOAD>" );
 strcpy( Repository.Items[ I ].Exe_name_1, "SL.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "SystemLoad object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "SystemLoad path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_NPSWPS;
 Repository.Items[ I ].Purpose = DO_IMPROVE_WORKPLACE;
 strcpy( Repository.Items[ I ].Exe_name_1, "NpsWps.exe" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_SYSBAR;
 Repository.Items[ I ].Purpose = DO_IMPROVE_WORKPLACE;
 Repository.Items[ I ].Action = SHOW_SYSBAR;
 strcpy( Repository.Items[ I ].Exe_name_1, "Sb2_tswt.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "SysBar object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "SysBar path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_ESPS;
 Repository.Items[ I ].Purpose = DO_IMPROVE_WORKPLACE;
 strcpy( Repository.Items[ I ].Exe_name_1, "Esps.exe" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_PMFORMAT;
 Repository.Items[ I ].Purpose = DO_PREPARE_DRIVES;
 strcpy( Repository.Items[ I ].Exe_name_1, "PMFormat.exe" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_PMCHKDSK;
 Repository.Items[ I ].Purpose = DO_PREPARE_DRIVES;
 strcpy( Repository.Items[ I ].Exe_name_1, "PMChkDsk.exe" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_CDRECORD;
 Repository.Items[ I ].Purpose = DO_PREPARE_DRIVES;
 strcpy( Repository.Items[ I ].Exe_name_1, "CDRecord.exe" );
 strcpy( Repository.Items[ I ].Exe_name_2, "CDRDao.exe" );
 strcpy( Repository.Items[ I ].Exe_name_3, "CDRDao2.exe" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_CDREC_PM;
 Repository.Items[ I ].Purpose = DO_PREPARE_DRIVES;
 strcpy( Repository.Items[ I ].Exe_name_1, "CDWriter.exe" );
 strcpy( Repository.Items[ I ].Exe_name_2, "PMCDRec.exe" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_DVDRECORD;
 Repository.Items[ I ].Purpose = DO_PREPARE_DRIVES;
 strcpy( Repository.Items[ I ].Exe_name_1, "DVDDao.exe" );
 strcpy( Repository.Items[ I ].Exe_name_2, "MkISOFS.exe" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_NETDRIVE;
 Repository.Items[ I ].Purpose = DO_CONNECT_DRIVES;
 Repository.Items[ I ].Action = SHOW_NETWORK;
 strcpy( Repository.Items[ I ].WPS_name_A, "<NDFS_CONTROLPANEL>" );
 strcpy( Repository.Items[ I ].Exe_name_1, "Ndpm.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "NetDrive object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "NetDrive path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_DISCON;
 Repository.Items[ I ].Purpose = DO_CONNECT_DRIVES;
 Repository.Items[ I ].Action = SHOW_NETWORK;
 strcpy( Repository.Items[ I ].WPS_name_A, "<FF_DISCON>" );
 strcpy( Repository.Items[ I ].Exe_name_1, "Connect.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "DisCon object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "DisCon path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_NETUSE;
 Repository.Items[ I ].Purpose = DO_CONNECT_DRIVES;
 Repository.Items[ I ].Action = SHOW_NETWORK;
 strcpy( Repository.Items[ I ].Exe_name_1, "Netuse.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "NetUse object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "NetUse path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_SAFEFIRE;
 Repository.Items[ I ].Purpose = DO_CONNECT_INTERNET;
 Repository.Items[ I ].Action = SHOW_DIALER;
 strcpy( Repository.Items[ I ].Exe_name_1, "sfgui.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "SafeFire object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "SafeFire path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_INJOY;
 Repository.Items[ I ].Purpose = DO_CONNECT_INTERNET;
 Repository.Items[ I ].Action = SHOW_DIALER;
 strcpy( Repository.Items[ I ].Exe_name_1, "In-joy.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "In-joy object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "In-joy path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_ISDNPM;
 Repository.Items[ I ].Purpose = DO_CONNECT_INTERNET;
 Repository.Items[ I ].Action = SHOW_DIALER;
 strcpy( Repository.Items[ I ].Exe_name_1, "ISDNPM.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "ISDNPM object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "ISDNPM path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_ECSCONET;
 Repository.Items[ I ].Purpose = DO_CONNECT_INTERNET;
 Repository.Items[ I ].Action = SHOW_DIALER;
 strcpy( Repository.Items[ I ].WPS_name_A, "<ECSCONET_EXEC>" );
 strcpy( Repository.Items[ I ].Exe_name_1, "eCSCoNet.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "eCSCoNet object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "eCSCoNet path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_FC;
 Repository.Items[ I ].Purpose = DO_MANAGE_FILES;
 Repository.Items[ I ].Action = SHOW_VIO_COMMANDER;
 Repository.Items[ I ].Desired = 1;
 strcpy( Repository.Items[ I ].Exe_name_1, "Fc.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "FC/2 object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "FC/2 path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_DN;
 Repository.Items[ I ].Purpose = DO_MANAGE_FILES;
 Repository.Items[ I ].Action = SHOW_VIO_COMMANDER;
 strcpy( Repository.Items[ I ].Exe_name_1, "Dn.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "DN/2 object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "DN/2 path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_XC;
 Repository.Items[ I ].Purpose = DO_MANAGE_FILES;
 Repository.Items[ I ].Action = SHOW_VIO_COMMANDER;
 strcpy( Repository.Items[ I ].Exe_name_1, "XCom2.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "X-Commander object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "X-Commander path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_LCMD;
 Repository.Items[ I ].Purpose = DO_MANAGE_FILES;
 Repository.Items[ I ].Action = SHOW_PM_COMMANDER;
 strcpy( Repository.Items[ I ].WPS_name_A, "<LarsenCommanderProg>" );
 strcpy( Repository.Items[ I ].Exe_name_1, "Lcmd.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "LCmd object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "LCmd path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_EFCOMM;
 Repository.Items[ I ].Purpose = DO_MANAGE_FILES;
 Repository.Items[ I ].Action = SHOW_PM_COMMANDER;
 strcpy( Repository.Items[ I ].Exe_name_1, "Comm.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "EFComm object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "EFComm path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_FM2;
 Repository.Items[ I ].Purpose = DO_MANAGE_FILES;
 Repository.Items[ I ].Action = SHOW_PM_COMMANDER;
 strcpy( Repository.Items[ I ].WPS_name_A, "<FM/2>" );
 strcpy( Repository.Items[ I ].Exe_name_1, "FM2.exe" );
 strcpy( Repository.Items[ I ].Exe_name_2, "FM3.exe" );
 strcpy( Repository.Items[ I ].Exe_name_3, "FM4.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "FM/2 object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "FM/2 path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_FBROWSER;
 Repository.Items[ I ].Purpose = DO_MANAGE_FILES;
 Repository.Items[ I ].Action = SHOW_PM_COMMANDER;
 strcpy( Repository.Items[ I ].WPS_name_A, "<FB_BROWSER>" );
 strcpy( Repository.Items[ I ].Exe_name_1, "FBrowser.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "FileBrowser object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "FileBrowser path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_FFREEDOM;
 Repository.Items[ I ].Purpose = DO_MANAGE_FILES;
 Repository.Items[ I ].Action = SHOW_PM_COMMANDER;
 strcpy( Repository.Items[ I ].WPS_name_A, "<FF_FILEMANAGER>" );
 strcpy( Repository.Items[ I ].Exe_name_1, "FileFrdm.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "FileFreedom object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "FileFreedom path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_FOTOGET;
 Repository.Items[ I ].Purpose = DO_MANAGE_FILES;
 Repository.Items[ I ].Action = SHOW_DIGITAL_CAMERA;
 Repository.Items[ I ].Desired = 1;
 strcpy( Repository.Items[ I ].WPS_name_A, "<FotoGet_2>" );
 strcpy( Repository.Items[ I ].Exe_name_1, "FotoGet.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "FotoGet object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "FotoGet path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_DCAMERA;
 Repository.Items[ I ].Purpose = DO_MANAGE_FILES;
 Repository.Items[ I ].Action = SHOW_DIGITAL_CAMERA;
 strcpy( Repository.Items[ I ].Exe_name_1, "Camera.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "DigitalCamera object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "DigitalCamera path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_GTU_FILES;
 Repository.Items[ I ].Purpose = DO_SEARCH_FILES;
 Repository.Items[ I ].Action = SHOW_FINDER;
 strcpy( Repository.Items[ I ].Exe_name_1, "Files.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "GTU.Files object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "GTU.Files path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_FIREFOX;
 Repository.Items[ I ].Purpose = DO_BROWSE_WEB_PAGES;
 Repository.Items[ I ].Action = SHOW_WEB_BROWSER;
 Repository.Items[ I ].Desired = 1;
 strcpy( Repository.Items[ I ].WPS_name_A, "<FIREFOXEXE>" );
 strcpy( Repository.Items[ I ].Exe_name_1, "FireFox.exe" );
 strcpy( Repository.Items[ I ].Exe_name_2, "FireFox!K.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "FireFox object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "FireFox path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_MOZILLA;
 Repository.Items[ I ].Purpose = DO_BROWSE_WEB_PAGES;
 Repository.Items[ I ].Action = SHOW_WEB_BROWSER;
 strcpy( Repository.Items[ I ].WPS_name_A, "<MOZILLAEXE>" );
 strcpy( Repository.Items[ I ].Exe_name_1, "Mozilla.exe" );
 strcpy( Repository.Items[ I ].Exe_name_2, "SeaMonkey.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "Mozilla object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "Mozilla path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_ARORA;
 Repository.Items[ I ].Purpose = DO_BROWSE_WEB_PAGES;
 Repository.Items[ I ].Action = SHOW_WEB_BROWSER;
 strcpy( Repository.Items[ I ].WPS_name_A, "<AWB_ARORA_EXE>" );
 strcpy( Repository.Items[ I ].Exe_name_1, "Arora.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "Arora object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "Arora path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_QTWEB;
 Repository.Items[ I ].Purpose = DO_BROWSE_WEB_PAGES;
 Repository.Items[ I ].Action = SHOW_WEB_BROWSER;
 strcpy( Repository.Items[ I ].Exe_name_1, "QtWeb.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "QtWeb object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "QtWeb path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_SURFER;
 Repository.Items[ I ].Purpose = DO_BROWSE_WEB_PAGES;
 Repository.Items[ I ].Action = SHOW_WEB_BROWSER;
 strcpy( Repository.Items[ I ].Exe_name_1, "Surfer.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "Surfer object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "Surfer path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_QUPZILLA;
 Repository.Items[ I ].Purpose = DO_BROWSE_WEB_PAGES;
 Repository.Items[ I ].Action = SHOW_WEB_BROWSER;
 strcpy( Repository.Items[ I ].Exe_name_1, "QupZilla.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "QupZilla object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "QupZilla path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_DOOBLE;
 Repository.Items[ I ].Purpose = DO_BROWSE_WEB_PAGES;
 Repository.Items[ I ].Action = SHOW_WEB_BROWSER;
 strcpy( Repository.Items[ I ].Exe_name_1, "Dooble.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "Dooble object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "Dooble path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_LINKS;
 Repository.Items[ I ].Purpose = DO_BROWSE_WEB_PAGES;
 Repository.Items[ I ].Action = SHOW_WEB_BROWSER;
 strcpy( Repository.Items[ I ].Exe_name_1, "Links.exe" );
 strcpy( Repository.Items[ I ].WPS_keyword_1, "GLinks" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "Links object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "Links path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_THUNDERBIRD;
 Repository.Items[ I ].Purpose = DO_READ_MESSAGES;
 Repository.Items[ I ].Action = SHOW_MAIL_READER;
 strcpy( Repository.Items[ I ].Exe_name_1, "ThunderBird.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "ThunderBird object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "ThunderBird path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_PMMAIL;
 Repository.Items[ I ].Purpose = DO_READ_MESSAGES;
 Repository.Items[ I ].Action = SHOW_MAIL_READER;
 strcpy( Repository.Items[ I ].Exe_name_1, "PMMail.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "PMMail object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "PMMail path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_POLARBAR;
 Repository.Items[ I ].Purpose = DO_READ_MESSAGES;
 Repository.Items[ I ].Action = SHOW_MAIL_READER;
 strcpy( Repository.Items[ I ].WPS_keyword_1, "PolarBar" );
 strcpy( Repository.Items[ I ].Window_keyword_1, "PolarBar" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "PolarBar object" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_OPENCHAT;
 Repository.Items[ I ].Purpose = DO_INTERNET_CHAT;
 Repository.Items[ I ].Action = SHOW_INTERNET_CHAT;
 Repository.Items[ I ].Desired = 1;
 strcpy( Repository.Items[ I ].Exe_name_1, "OpenChat.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "OpenChat object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "OpenChat path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_QUASSEL;
 Repository.Items[ I ].Purpose = DO_INTERNET_CHAT;
 Repository.Items[ I ].Action = SHOW_INTERNET_CHAT;
 strcpy( Repository.Items[ I ].Exe_name_1, "Quassel.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "Quassel object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "Quassel path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_PMBITCHX;
 Repository.Items[ I ].Purpose = DO_INTERNET_CHAT;
 Repository.Items[ I ].Action = SHOW_INTERNET_CHAT;
 strcpy( Repository.Items[ I ].Exe_name_1, "PMBitchX.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "PMBitchX object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "PMBitchX path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_PWICQ;
 Repository.Items[ I ].Purpose = DO_CONTACT_PEOPLE;
 Repository.Items[ I ].Action = SHOW_ICQ_PAGER;
 strcpy( Repository.Items[ I ].Exe_name_1, "pwICQ.exe" );
 strcpy( Repository.Items[ I ].Exe_name_2, "pwICQ2.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "pwICQ object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "pwICQ path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_ICECQ;
 Repository.Items[ I ].Purpose = DO_CONTACT_PEOPLE;
 Repository.Items[ I ].Action = SHOW_ICQ_PAGER;
 strcpy( Repository.Items[ I ].WPS_name_A, "<MINITUN>" );
 strcpy( Repository.Items[ I ].Exe_name_1, "IceCQ.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "IceCQ object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "IceCQ path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_AICQ;
 Repository.Items[ I ].Purpose = DO_CONTACT_PEOPLE;
 Repository.Items[ I ].Action = SHOW_ICQ_PAGER;
 strcpy( Repository.Items[ I ].Exe_name_1, "AICQ.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "AICQ object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "AICQ path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_PSI;
 Repository.Items[ I ].Purpose = DO_CONTACT_PEOPLE;
 Repository.Items[ I ].Action = SHOW_ICQ_PAGER;
 strcpy( Repository.Items[ I ].Exe_name_1, "Psi.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "Psi object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "Psi path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_EYECU;
 Repository.Items[ I ].Purpose = DO_CONTACT_PEOPLE;
 Repository.Items[ I ].Action = SHOW_ICQ_PAGER;
 strcpy( Repository.Items[ I ].Exe_name_1, "EyeCU.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "EyeCU object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "EyeCU path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_NFTPPM;
 Repository.Items[ I ].Purpose = DO_BROWSE_FTP_SITES;
 Repository.Items[ I ].Action = SHOW_FTP_BROWSER;
 strcpy( Repository.Items[ I ].Exe_name_1, "Nftp.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "NFTP object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "NFTP path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_FTPBROWSER;
 Repository.Items[ I ].Purpose = DO_BROWSE_FTP_SITES;
 Repository.Items[ I ].Action = SHOW_FTP_BROWSER;
 strcpy( Repository.Items[ I ].WPS_name_A, "<FTPB>" );
 strcpy( Repository.Items[ I ].Exe_name_1, "FTPBAddr.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "FTPBrowser object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "FTPBrowser path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_FTPPM;
 Repository.Items[ I ].Purpose = DO_BROWSE_FTP_SITES;
 Repository.Items[ I ].Action = SHOW_FTP_BROWSER;
 strcpy( Repository.Items[ I ].Exe_name_1, "Ftppm.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "FTPPM object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "FTPPM path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_HANDYFTP;
 Repository.Items[ I ].Purpose = DO_BROWSE_FTP_SITES;
 Repository.Items[ I ].Action = SHOW_FTP_BROWSER;
 strcpy( Repository.Items[ I ].Exe_name_1, "HandyFTP.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "HandyFTP object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "HandyFTP path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_QFTP;
 Repository.Items[ I ].Purpose = DO_BROWSE_FTP_SITES;
 Repository.Items[ I ].Action = SHOW_FTP_BROWSER;
 strcpy( Repository.Items[ I ].Exe_name_1, "qFTP.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "qFTP object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "qFTP path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_SSH;
 Repository.Items[ I ].Purpose = DO_REMOTE_CONTROL;
 Repository.Items[ I ].Action = SHOW_VIO_SSH_TERMINAL;
 Repository.Items[ I ].Desired = 1;
 strcpy( Repository.Items[ I ].WPS_name_A, "<ECS_OPENSSHCLIENT>" );
 strcpy( Repository.Items[ I ].Exe_name_1, "Ssh.exe" );
 strcpy( Repository.Items[ I ].Exe_name_2, "Ssh2.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "SSH object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "SSH path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_QPUTTY;
 Repository.Items[ I ].Purpose = DO_REMOTE_CONTROL;
 Repository.Items[ I ].Action = SHOW_PM_SSH_TERMINAL;
 strcpy( Repository.Items[ I ].Exe_name_1, "qPutty.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "qPutty object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "qPutty path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_MINDTERM;
 Repository.Items[ I ].Purpose = DO_REMOTE_CONTROL;
 Repository.Items[ I ].Action = SHOW_PM_SSH_TERMINAL;
 strcpy( Repository.Items[ I ].WPS_keyword_1, "MindTerm" );
 strcpy( Repository.Items[ I ].Window_keyword_1, "MindTerm" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "MindTerm object" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_VNC;
 Repository.Items[ I ].Purpose = DO_REMOTE_CONTROL;
 Repository.Items[ I ].Action = SHOW_REMOTE_DESKTOP_VNC;
 Repository.Items[ I ].Desired = 1;
 strcpy( Repository.Items[ I ].WPS_name_A, "<PM_VNCVIEW>" );
 strcpy( Repository.Items[ I ].Exe_name_1, "VNCView.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "PMVNC object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "PMVNC path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_LIXIA;
 Repository.Items[ I ].Purpose = DO_REMOTE_CONTROL;
 Repository.Items[ I ].Action = SHOW_REMOTE_DESKTOP_RDP;
 strcpy( Repository.Items[ I ].WPS_name_A, "<JAVA_RDPVIEW>" );
 strcpy( Repository.Items[ I ].WPS_keyword_1, "Lixia" );
 strcpy( Repository.Items[ I ].Window_keyword_1, "Lixia" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "Lixia object" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_MED;
 Repository.Items[ I ].Purpose = DO_EDIT_TEXT;
 Repository.Items[ I ].Action = SHOW_TEXT_EDITOR;
 Repository.Items[ I ].Desired = 1;
 strcpy( Repository.Items[ I ].Exe_name_1, "Med.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "MED object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "MED path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_KON;
 Repository.Items[ I ].Purpose = DO_EDIT_TEXT;
 Repository.Items[ I ].Action = SHOW_TEXT_EDITOR;
 strcpy( Repository.Items[ I ].WPS_name_A, "<KON2>" );
 strcpy( Repository.Items[ I ].WPS_name_B, "<KON2 README>" );
 strcpy( Repository.Items[ I ].Exe_name_1, "KonOS2.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "KON object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "KON path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_QEDIT;
 Repository.Items[ I ].Purpose = DO_EDIT_TEXT;
 Repository.Items[ I ].Action = SHOW_TEXT_EDITOR;
 strcpy( Repository.Items[ I ].Exe_name_1, "qEdit.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "qEdit object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "qEdit path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_FTEPM;
 Repository.Items[ I ].Purpose = DO_EDIT_TEXT;
 Repository.Items[ I ].Action = SHOW_TEXT_EDITOR;
 strcpy( Repository.Items[ I ].Exe_name_1, "Ftepm.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "FTE object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "FTE path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_FWE;
 Repository.Items[ I ].Purpose = DO_EDIT_TEXT;
 Repository.Items[ I ].Action = SHOW_TEXT_EDITOR;
 strcpy( Repository.Items[ I ].WPS_name_A, "<WP_FutureWaveEditor>" );
 strcpy( Repository.Items[ I ].Exe_name_1, "Fwe.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "FWE object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "FWE path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_E;
 Repository.Items[ I ].Purpose = DO_EDIT_TEXT;
 Repository.Items[ I ].Action = SHOW_TEXT_EDITOR;
 strcpy( Repository.Items[ I ].WPS_name_A, "<WP_SYSED>" );
 strcpy( Repository.Items[ I ].Exe_name_1, "E.exe" );
 strcpy( Repository.Items[ I ].Exe_name_2, "AE.exe" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_EPM;
 Repository.Items[ I ].Purpose = DO_EDIT_TEXT;
 Repository.Items[ I ].Action = SHOW_TEXT_EDITOR;
 strcpy( Repository.Items[ I ].WPS_name_A, "<WP_EPM>" );
 strcpy( Repository.Items[ I ].Exe_name_1, "Epm.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "EPM object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "EPM path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_EDPLUS;
 Repository.Items[ I ].Purpose = DO_EDIT_TEXT;
 Repository.Items[ I ].Action = SHOW_TEXT_EDITOR;
 strcpy( Repository.Items[ I ].Exe_name_1, "Editor.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "Editor+ object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "Editor+ path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_ZED;
 Repository.Items[ I ].Purpose = DO_EDIT_TEXT;
 Repository.Items[ I ].Action = SHOW_TEXT_EDITOR;
 strcpy( Repository.Items[ I ].Exe_name_1, "Zed.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "Zed object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "Zed path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_EULER;
 Repository.Items[ I ].Purpose = DO_CALCULATION;
 Repository.Items[ I ].Action = SHOW_CALCULATOR;
 strcpy( Repository.Items[ I ].Exe_name_1, "Euler.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "Euler object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "Euler path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_SCALC;
 Repository.Items[ I ].Purpose = DO_CALCULATION;
 Repository.Items[ I ].Action = SHOW_CALCULATOR;
 strcpy( Repository.Items[ I ].Exe_name_1, "SCalc.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "SCalc object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "SCalc path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_SCALC;
 Repository.Items[ I ].Purpose = DO_CALCULATION;
 Repository.Items[ I ].Action = SHOW_CALCULATOR;
 strcpy( Repository.Items[ I ].WPS_name_A, "<DECalc_Prog>" );
 strcpy( Repository.Items[ I ].Exe_name_1, "DECalc.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "DECalc object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "DECalc path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_ECALC;
 Repository.Items[ I ].Purpose = DO_CALCULATION;
 Repository.Items[ I ].Action = SHOW_CALCULATOR;
 strcpy( Repository.Items[ I ].WPS_name_A, "<ECS_CALC>" );
 strcpy( Repository.Items[ I ].Exe_name_1, "eCSCalc.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "eCalc object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "eCalc path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_WORDPRO;
 Repository.Items[ I ].Purpose = DO_EDIT_TEXT;
 strcpy( Repository.Items[ I ].Exe_name_1, "WordPro.exe" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_LOTUS123;
 Repository.Items[ I ].Purpose = DO_EDIT_DATA;
 strcpy( Repository.Items[ I ].Exe_name_1, "123w.exe" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_MESA;
 Repository.Items[ I ].Purpose = DO_EDIT_DATA;
 strcpy( Repository.Items[ I ].Exe_name_1, "Mesa2.exe" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_APPROACH;
 Repository.Items[ I ].Purpose = DO_EDIT_DATA;
 strcpy( Repository.Items[ I ].Exe_name_1, "Approach.exe" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_DBEXPERT;
 Repository.Items[ I ].Purpose = DO_EDIT_DATA;
 strcpy( Repository.Items[ I ].Exe_name_1, "DBExpert.exe" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_LATEX;
 Repository.Items[ I ].Purpose = DO_BROWSE_TEX_TEXT;
 strcpy( Repository.Items[ I ].Exe_name_1, "LaTeX.exe" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_VIEWDOC;
 Repository.Items[ I ].Purpose = DO_BROWSE_IPF_HELP;
 strcpy( Repository.Items[ I ].Exe_name_1, "View.exe" );
 strcpy( Repository.Items[ I ].Exe_name_2, "ViewDoc.exe" );
 strcpy( Repository.Items[ I ].Exe_name_3, "IBMView.exe" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_NEWVIEW;
 Repository.Items[ I ].Purpose = DO_BROWSE_IPF_HELP;
 strcpy( Repository.Items[ I ].Exe_name_1, "NewView.exe" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "NewView path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_PMVIEW;
 Repository.Items[ I ].Purpose = DO_BROWSE_IMAGES;
 Repository.Items[ I ].Action = SHOW_IMAGE_VIEWER;
 Repository.Items[ I ].Desired = 1;
 strcpy( Repository.Items[ I ].WPS_name_A, "<PMVIEW20>" );
 strcpy( Repository.Items[ I ].WPS_name_B, "<PMVIEW30>" );
 strcpy( Repository.Items[ I ].WPS_name_C, "<PMVIEW40>" );
 strcpy( Repository.Items[ I ].Exe_name_1, "PMView.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "PMView object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "PMView path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_EMBELLISH;
 Repository.Items[ I ].Purpose = DO_CREATE_IMAGES;
 strcpy( Repository.Items[ I ].Exe_name_1, "Emb.exe" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_PM123;
 Repository.Items[ I ].Purpose = DO_ENTERTAINMENT;
 Repository.Items[ I ].Action = SHOW_MUSIC_PLAYER;
 Repository.Items[ I ].Desired = 1;
 strcpy( Repository.Items[ I ].WPS_name_A, "<PM123>" );
 strcpy( Repository.Items[ I ].Exe_name_1, "Pm123.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "PM123 object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "PM123 path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_WARPVISION;
 Repository.Items[ I ].Purpose = DO_ENTERTAINMENT;
 Repository.Items[ I ].Action = SHOW_VIDEO_PLAYER;
 strcpy( Repository.Items[ I ].Exe_name_1, "Video2.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "WarpVision object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "WarpVision path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_VLC;
 Repository.Items[ I ].Purpose = DO_ENTERTAINMENT;
 Repository.Items[ I ].Action = SHOW_VIDEO_PLAYER;
 strcpy( Repository.Items[ I ].Exe_name_1, "VLC.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "VLC object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "VLC path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_MPLAYER;
 Repository.Items[ I ].Purpose = DO_ENTERTAINMENT;
 Repository.Items[ I ].Action = SHOW_MUSIC_PLAYER;
 strcpy( Repository.Items[ I ].Exe_name_1, "MPlayer.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "MPlayer object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "MPlayer path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_MOOSICK;
 Repository.Items[ I ].Purpose = DO_ENTERTAINMENT;
 Repository.Items[ I ].Action = SHOW_MUSIC_PLAYER;
 strcpy( Repository.Items[ I ].Exe_name_1, "MooSick.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "MooSick object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "MooSick path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_ZMP3;
 Repository.Items[ I ].Purpose = DO_ENTERTAINMENT;
 Repository.Items[ I ].Action = SHOW_MUSIC_PLAYER;
 strcpy( Repository.Items[ I ].Exe_name_1, "Z.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "ZMP3 object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "ZMP3 path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_MIKMOD;
 Repository.Items[ I ].Purpose = DO_ENTERTAINMENT;
 Repository.Items[ I ].Action = SHOW_MOD_PLAYER;
 strcpy( Repository.Items[ I ].Exe_name_1, "MikModPM.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "MikMod object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "MikMod path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_TIMIDITY;
 Repository.Items[ I ].Purpose = DO_ENTERTAINMENT;
 strcpy( Repository.Items[ I ].Exe_name_1, "Timidity.exe" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_COOLFM;
 Repository.Items[ I ].Purpose = DO_ENTERTAINMENT;
 Repository.Items[ I ].Action = SHOW_FM_TUNER;
 strcpy( Repository.Items[ I ].Exe_name_1, "CoolFM.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "CoolFM object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "CoolFM path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_ZMP3;
 Repository.Items[ I ].Purpose = DO_ENTERTAINMENT;
 Repository.Items[ I ].Action = SHOW_MUSIC_PLAYER;
 strcpy( Repository.Items[ I ].Exe_name_1, "Z.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "ZMP3 object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "ZMP3 path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_MMOS2_VOLUME;
 Repository.Items[ I ].Purpose = DO_ENTERTAINMENT;
 Repository.Items[ I ].Action = SHOW_MMOS2_VOLUME;
 Repository.Items[ I ].Desired = 1;
 strcpy( Repository.Items[ I ].WPS_name_A, "<MMPM2_MMVOLUME>" );
 strcpy( Repository.Items[ I ].Exe_name_1, "Volume.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "MM/V object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "MM/V path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_UNIAUDIO_MIXER;
 Repository.Items[ I ].Purpose = DO_ENTERTAINMENT;
 Repository.Items[ I ].Action = SHOW_UNIAUDIO_MIXER;
 strcpy( Repository.Items[ I ].WPS_name_A, "<UNIAUD_MIXER>" );
 strcpy( Repository.Items[ I ].Exe_name_1, "UniMixPM.exe" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "UniMix object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "UniMix path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_VACPP;
 Repository.Items[ I ].Purpose = DO_DEVELOP_PROGRAMS;
 strcpy( Repository.Items[ I ].Exe_name_1, "Vacide.exe" );
 strcpy( Repository.Items[ I ].Exe_name_2, "Imui.exe" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_PMDIFF;
 Repository.Items[ I ].Purpose = DO_DEVELOP_PROGRAMS;
 strcpy( Repository.Items[ I ].Exe_name_1, "PMDiff.exe" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_VIRTUALPC;
 Repository.Items[ I ].Purpose = DO_EMULATION;
 strcpy( Repository.Items[ I ].Exe_name_1, "Vpc.exe" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_MSQL;
 Repository.Items[ I ].Purpose = DO_DATABASE;
 strcpy( Repository.Items[ I ].Exe_name_1, "MSQL.exe" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_MYSQL;
 Repository.Items[ I ].Purpose = DO_DATABASE;
 strcpy( Repository.Items[ I ].Exe_name_1, "MySQL.exe" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_WEB2;
 Repository.Items[ I ].Purpose = DO_WEB_SERVER;
 strcpy( Repository.Items[ I ].Exe_name_1, "Web.exe" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_HTTPD;
 Repository.Items[ I ].Purpose = DO_WEB_SERVER;
 strcpy( Repository.Items[ I ].Exe_name_1, "HTTPD.exe" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_FTPD;
 Repository.Items[ I ].Purpose = DO_FTP_SERVER;
 strcpy( Repository.Items[ I ].Exe_name_1, "FTPD.exe" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_SSHD;
 Repository.Items[ I ].Purpose = DO_SSH_SERVER;
 strcpy( Repository.Items[ I ].Exe_name_1, "SSHD.exe" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_USER_TOOL_1;
 Repository.Items[ I ].Purpose = DO_ANYTHING;
 Repository.Items[ I ].Action = SHOW_USER_TOOL_1;
 strcpy( Repository.Items[ I ].Exe_name_1, "*" );
 strcpy( Repository.Items[ I ].Exe_INI_setting_name, "UserTool 1 name" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "UserTool 1 object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "UserTool 1 path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_USER_TOOL_2;
 Repository.Items[ I ].Purpose = DO_ANYTHING;
 Repository.Items[ I ].Action = SHOW_USER_TOOL_2;
 strcpy( Repository.Items[ I ].Exe_name_1, "*" );
 strcpy( Repository.Items[ I ].Exe_INI_setting_name, "UserTool 2 name" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "UserTool 2 object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "UserTool 2 path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_USER_TOOL_3;
 Repository.Items[ I ].Purpose = DO_ANYTHING;
 Repository.Items[ I ].Action = SHOW_USER_TOOL_3;
 strcpy( Repository.Items[ I ].Exe_name_1, "*" );
 strcpy( Repository.Items[ I ].Exe_INI_setting_name, "UserTool 3 name" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "UserTool 3 object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "UserTool 3 path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_USER_TOOL_4;
 Repository.Items[ I ].Purpose = DO_ANYTHING;
 Repository.Items[ I ].Action = SHOW_USER_TOOL_4;
 strcpy( Repository.Items[ I ].Exe_name_1, "*" );
 strcpy( Repository.Items[ I ].Exe_INI_setting_name, "UserTool 4 name" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "UserTool 4 object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "UserTool 4 path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_USER_TOOL_5;
 Repository.Items[ I ].Purpose = DO_ANYTHING;
 Repository.Items[ I ].Action = SHOW_USER_TOOL_5;
 strcpy( Repository.Items[ I ].Exe_name_1, "*" );
 strcpy( Repository.Items[ I ].Exe_INI_setting_name, "UserTool 5 name" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "UserTool 5 object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "UserTool 5 path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_USER_TOOL_6;
 Repository.Items[ I ].Purpose = DO_ANYTHING;
 Repository.Items[ I ].Action = SHOW_USER_TOOL_6;
 strcpy( Repository.Items[ I ].Exe_name_1, "*" );
 strcpy( Repository.Items[ I ].Exe_INI_setting_name, "UserTool 6 name" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "UserTool 6 object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "UserTool 6 path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_USER_TOOL_7;
 Repository.Items[ I ].Purpose = DO_ANYTHING;
 Repository.Items[ I ].Action = SHOW_USER_TOOL_7;
 strcpy( Repository.Items[ I ].Exe_name_1, "*" );
 strcpy( Repository.Items[ I ].Exe_INI_setting_name, "UserTool 7 name" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "UserTool 7 object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "UserTool 7 path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_USER_TOOL_8;
 Repository.Items[ I ].Purpose = DO_ANYTHING;
 Repository.Items[ I ].Action = SHOW_USER_TOOL_8;
 strcpy( Repository.Items[ I ].Exe_name_1, "*" );
 strcpy( Repository.Items[ I ].Exe_INI_setting_name, "UserTool 8 name" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "UserTool 8 object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "UserTool 8 path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_USER_TOOL_9;
 Repository.Items[ I ].Purpose = DO_ANYTHING;
 Repository.Items[ I ].Action = SHOW_USER_TOOL_9;
 strcpy( Repository.Items[ I ].Exe_name_1, "*" );
 strcpy( Repository.Items[ I ].Exe_INI_setting_name, "UserTool 9 name" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "UserTool 9 object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "UserTool 9 path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_USER_TOOL_A;
 Repository.Items[ I ].Purpose = DO_ANYTHING;
 Repository.Items[ I ].Action = SHOW_USER_TOOL_A;
 strcpy( Repository.Items[ I ].Exe_name_1, "*" );
 strcpy( Repository.Items[ I ].Exe_INI_setting_name, "UserTool A name" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "UserTool A object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "UserTool A path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_USER_TOOL_B;
 Repository.Items[ I ].Purpose = DO_ANYTHING;
 Repository.Items[ I ].Action = SHOW_USER_TOOL_B;
 strcpy( Repository.Items[ I ].Exe_name_1, "*" );
 strcpy( Repository.Items[ I ].Exe_INI_setting_name, "UserTool B name" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "UserTool B object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "UserTool B path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_USER_TOOL_C;
 Repository.Items[ I ].Purpose = DO_ANYTHING;
 Repository.Items[ I ].Action = SHOW_USER_TOOL_C;
 strcpy( Repository.Items[ I ].Exe_name_1, "*" );
 strcpy( Repository.Items[ I ].Exe_INI_setting_name, "UserTool C name" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "UserTool C object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "UserTool C path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_USER_TOOL_D;
 Repository.Items[ I ].Purpose = DO_ANYTHING;
 Repository.Items[ I ].Action = SHOW_USER_TOOL_D;
 strcpy( Repository.Items[ I ].Exe_name_1, "*" );
 strcpy( Repository.Items[ I ].Exe_INI_setting_name, "UserTool D name" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "UserTool D object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "UserTool D path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_USER_TOOL_E;
 Repository.Items[ I ].Purpose = DO_ANYTHING;
 Repository.Items[ I ].Action = SHOW_USER_TOOL_E;
 strcpy( Repository.Items[ I ].Exe_name_1, "*" );
 strcpy( Repository.Items[ I ].Exe_INI_setting_name, "UserTool E name" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "UserTool E object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "UserTool E path" );

 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );
 Repository.Items[ I ].Application = APP_USER_TOOL_F;
 Repository.Items[ I ].Purpose = DO_ANYTHING;
 Repository.Items[ I ].Action = SHOW_USER_TOOL_F;
 strcpy( Repository.Items[ I ].Exe_name_1, "*" );
 strcpy( Repository.Items[ I ].Exe_INI_setting_name, "UserTool F name" );
 strcpy( Repository.Items[ I ].Object_INI_setting_name, "UserTool F object" );
 strcpy( Repository.Items[ I ].Path_INI_setting_name, "UserTool F path" );

 // ���������� �᫮ ��ப � ᯨ᪥.
 Repository.Length = I + 1;

 // ��頥� �� ���� ��ப� ᯨ᪠.
 // �᫨ ���稪 ���⨣ �।��쭮�� ���祭��, � �� 㦥 �� 㢥������ � �� �⠭�� ����⭮.
 Repository_next( &I ); Repository_clear( &Repository.Items[ I ] );

 // ������.
 return;
}

// ��� ��⠥� ᯨ᮪ �ਫ������ ���

// Ini_file - 䠩� ����஥� �ਫ������.
VOID Repository_ReadRepository( HINI Ini_file )
{
 // ��⠥� ᯨ᮪ �ਫ������.
 INT Count = 0;

 for( Count = 0; Count < Repository.Length; Count ++ )
  {
   // ��⠥� ����� �ᯮ��塞�� 䠩���.
   if( Repository.Items[ Count ].Exe_INI_setting_name[ 0 ] != 0 )
    {
     PCHAR Target = NULL;

     if( Repository.Items[ Count ].Exe_name_4[ 0 ] == 0 || Repository.Items[ Count ].Exe_name_4[ 0 ] == '*' ) Target = Repository.Items[ Count ].Exe_name_4;
     if( Repository.Items[ Count ].Exe_name_3[ 0 ] == 0 || Repository.Items[ Count ].Exe_name_3[ 0 ] == '*' ) Target = Repository.Items[ Count ].Exe_name_3;
     if( Repository.Items[ Count ].Exe_name_2[ 0 ] == 0 || Repository.Items[ Count ].Exe_name_2[ 0 ] == '*' ) Target = Repository.Items[ Count ].Exe_name_2;
     if( Repository.Items[ Count ].Exe_name_1[ 0 ] == 0 || Repository.Items[ Count ].Exe_name_1[ 0 ] == '*' ) Target = Repository.Items[ Count ].Exe_name_1;

     if( Target != NULL )
      {
       ULONG Name = SIZE_OF_NAME; PrfQueryProfileData( Ini_file, "Applications", Repository.Items[ Count ].Exe_INI_setting_name, Target, &Name );
      }
    }

   // ��⠥� ����� ���窮� �� ࠡ�祬 �⮫�.
   if( Repository.Items[ Count ].Object_INI_setting_name[ 0 ] != 0 )
    {
     PCHAR Target = NULL;

     if( Repository.Items[ Count ].WPS_name_D[ 0 ] == 0 ) Target = Repository.Items[ Count ].WPS_name_D;
     if( Repository.Items[ Count ].WPS_name_C[ 0 ] == 0 ) Target = Repository.Items[ Count ].WPS_name_C;
     if( Repository.Items[ Count ].WPS_name_B[ 0 ] == 0 ) Target = Repository.Items[ Count ].WPS_name_B;
     if( Repository.Items[ Count ].WPS_name_A[ 0 ] == 0 ) Target = Repository.Items[ Count ].WPS_name_A;

     ULONG Name = SIZE_OF_NAME; PrfQueryProfileData( Ini_file, "Applications", Repository.Items[ Count ].Object_INI_setting_name, Target, &Name );
    }

   // ��⠥� ���� � ��⠫��� �ਫ������.
   #ifdef INCLUDED_BY_SHELL
   if( Repository.Items[ Count ].Path_INI_setting_name[ 0 ] != 0 )
    {
     ULONG Path = SIZE_OF_PATH; PrfQueryProfileData( Ini_file, "Applications", Repository.Items[ Count ].Path_INI_setting_name, Repository.Items[ Count ].Path_to_Exe_file, &Path );
    }
   #endif
  }

 // ������.
 return;
}

// ��� ������ ���箪 �� ࠡ�祬 �⮫�, �ᯮ������ ����� �� WPTools.dll ���

// Name - ��� ���窠, �����饭��� WPTools.dll
HOBJECT Repository_QueryWPSObject( PCHAR Name )
{
 // �᫨ � ��砫� ����� �⮨� "#" - ࠧ��ࠥ� ���, ��� 16-�筮� ���祭��.
 if( Name[ 0 ] == '#' )
  {
   return (HOBJECT) atoi( &Name[ 1 ] );
  }
 // ���� - ��뢠�� ����� ��⮤ WPS.
 else
  {
   return WinQueryObject( Name );
  }

 // ������.
 return NULLHANDLE;
}

// ��� ��室�� �ਫ������ � ᯨ᪥ ���

// Application, Action, Filter - ���祭�� ��� ���᪠, Position - � ������ ���� �த������ ����.
#ifndef INCLUDED_BY_SHELL
INT Repository_FindApplicationInRepository( INT Application, INT Action = 0, BYTE Filter = FLT_ALL, INT Position = 0 )
#else
INT Repository_FindApplicationInRepository( INT Application, BYTE Filter = FLT_ALL )
#endif
{
 // �᫨ �।��騩 ���� ��祣� �� ��� - ������.
 #ifndef INCLUDED_BY_SHELL
 if( Position == -1 ) return 0;
 #endif

 // �믮��塞 ����.
 #ifndef INCLUDED_BY_SHELL
 INT Count = Position;
 #else
 INT Count = 0;
 #endif

 while( Count < Repository.Length )
  {
   BYTE Success = 0;

   #ifndef INCLUDED_BY_SHELL
   if( Application != 0 && Repository.Items[ Count ].Application == Application )
    {
     if( Filter == FLT_ALL ) Success = 1;
     if( Filter == FLT_DESIRED  && Repository.Items[ Count ].Desired == 1 ) Success = 1;
     if( Filter == FLT_SUITABLE && Repository.Items[ Count ].Desired == 0 ) Success = 1;
    }

   if( Action != 0 && Repository.Items[ Count ].Action == Action )
    {
     if( Filter == FLT_ALL ) Success = 1;
     if( Filter == FLT_DESIRED  && Repository.Items[ Count ].Desired == 1 ) Success = 1;
     if( Filter == FLT_SUITABLE && Repository.Items[ Count ].Desired == 0 ) Success = 1;
    }
   #else
   if( Repository.Items[ Count ].Application == Application )
    {
     if( Filter == FLT_ALL ) Success = 1;
     if( Filter == FLT_DESIRED  && Repository.Items[ Count ].Desired == 1 ) Success = 1;
     if( Filter == FLT_SUITABLE && Repository.Items[ Count ].Desired == 0 ) Success = 1;
    }
   #endif

   if( Success ) return Count;
   else Count ++;
  }

 // ������.
 return -1;
}

// ��� ��室�� ��� � ᯨ᪥ ���

// Name - ��� �ਫ������ ��� ����, Filter - �᫮��� �⡮�.
INT Repository_FindExeNameInRepository( PCHAR Name, BYTE Filter = FLT_ALL )
{
 // �믮��塞 ����.
 INT Count = 0;

 while( Count < Repository.Length )
  {
   BYTE Success = 0;

   if( stric( Name, Repository.Items[ Count ].Exe_name_1 ) ||
       stric( Name, Repository.Items[ Count ].Exe_name_2 ) ||
       stric( Name, Repository.Items[ Count ].Exe_name_3 ) ||
       stric( Name, Repository.Items[ Count ].Exe_name_4 ) )
    {
     if( Filter == FLT_ALL ) Success = 1;
     if( Filter == FLT_DESIRED  && Repository.Items[ Count ].Desired == 1 ) Success = 1;
     if( Filter == FLT_SUITABLE && Repository.Items[ Count ].Desired == 0 ) Success = 1;
    }

   if( Success ) return Count;
   else Count ++;
  }

 // ������.
 return -1;
}

// ��� �஢���� ����⢮����� �ਫ������ ���

// Application - �ਫ������ ��� �஢�ન, Filter - �᫮��� �⡮�.
BYTE Repository_ApplicationIsExists( INT Application, BYTE Filter = FLT_ALL )
{
 // ��室�� �ਫ������ � ᯨ᪥.
 INT Position = Repository_FindApplicationInRepository( Application, Filter );

 // �᫨ ��� �� ������� - ������.
 if( Position == -1 ) return 0;

 // �஢��塞, ���� �� ���箪 ��� �ਫ������.
 if( Repository.Items[ Position ].WPS_name_A[ 0 ] != 0 ) if( Repository_QueryWPSObject( Repository.Items[ Position ].WPS_name_A ) != NULLHANDLE ) return 1;
 if( Repository.Items[ Position ].WPS_name_B[ 0 ] != 0 ) if( Repository_QueryWPSObject( Repository.Items[ Position ].WPS_name_B ) != NULLHANDLE ) return 1;
 if( Repository.Items[ Position ].WPS_name_C[ 0 ] != 0 ) if( Repository_QueryWPSObject( Repository.Items[ Position ].WPS_name_C ) != NULLHANDLE ) return 1;
 if( Repository.Items[ Position ].WPS_name_D[ 0 ] != 0 ) if( Repository_QueryWPSObject( Repository.Items[ Position ].WPS_name_D ) != NULLHANDLE ) return 1;

 // ������.
 return 0;
}

// ��� �஢���� ����⢮����� �ਫ������, ����� ����� �맢��� �� �������� ������� ���

// Action - ����⢨� ��� �맮�� �ਫ������, Filter - �᫮��� �⡮�.
BYTE Repository_ShowCommandCanBeUsed( INT Action, BYTE Filter = FLT_ALL )
{
 // ����⢨�, ��� ������ �� ������ �ਫ������, �ਬ����� �ᥣ��.
 if( ( Action >= SHOW_PMSHELL_FIRST && Action <= SHOW_PMSHELL_LAST ) ||
     ( Action >= SHOW_OBJECT_FIRST && Action <= SHOW_OBJECT_LAST ) )
  return 1;

 // ��� ��㣨� ����⢨� �㦭� �஢�ઠ.
 {
  INT Count = 0;

  for( Count; Count < Repository.Length; Count ++ )
   if( Repository.Items[ Count ].Action == Action )
    if( Repository_ApplicationIsExists( Repository.Items[ Count ].Application, Filter ) )
     return 1;
 }

 // ������.
 return 0;
}

// ��� �믮���� �ࠢ����� ����� �ਫ������ � ���祭�� � ᯨ᪥ ���

// Position - ���� ��� �ࠢ�����, Name - ��� ��� �ࠢ�����.
BYTE Repository_NamesAreEqually( INT Position, PCHAR Name )
{
 // �᫨ ���� ��� �ࠢ����� �� ������ - ������.
 if( Position == -1 ) return 0;

 // �஢��塞 �����.
 if( stric( Repository.Items[ Position ].Exe_name_1, Name ) ||
     stric( Repository.Items[ Position ].Exe_name_2, Name ) ||
     stric( Repository.Items[ Position ].Exe_name_3, Name ) ||
     stric( Repository.Items[ Position ].Exe_name_4, Name ) ) return 1;

 // ������.
 return 0;
}

// ��� ������ ���� ࠬ�� ���

// Window - ���� �� ���� �ਫ������.
HWND Repository_QueryFrameWindow( HWND Window )
{
 // �᫨ ���� �� 㪠���� - ������.
 if( Window == NULLHANDLE ) return NULLHANDLE;

 // ������ ���� ࠡ�祣� �⮫�.
 HWND Desktop = QueryDesktopWindow();

 // �᫨ 㪠���� ���� ࠡ�祣� �⮫� ��� ���� ࠬ�� - ������.
 if( Window == Desktop ) return NULLHANDLE;
 if( Repository_IsFrameWindow( Window ) ) return Window;

 // ������ த�⥫�᪮� ����.
 HWND Parent_window = WinQueryWindow( Window, QW_PARENT );

 // �᫨ �� ���� ࠬ�� - ������.
 if( Repository_IsFrameWindow( Parent_window ) ) return Parent_window;

 // ��ᬠ�ਢ��� �� த�⥫�᪨� ����.
 HWND Next_window = NULLHANDLE;

 while( Parent_window != Desktop && Parent_window != NULLHANDLE )
  {
   // ������ ᫥���饥 த�⥫�᪮� ����.
   Next_window = WinQueryWindow( Parent_window, QW_PARENT );

   // �᫨ �� �� ࠬ�� - �த������ ��ॡ�� ����.
   if( !Repository_IsFrameWindow( Next_window ) ) Parent_window = Next_window;
   // ���� - ������� ���� ࠬ��.
   else return Next_window;
  }

 // ������.
 return NULLHANDLE;
}

// ��� ������ ������� ���� �ਫ������ ���

// Window - ���� �� ���� �ਫ������, Find_frame_window - �᪠�� ⮫쪮 ���� ࠬ��.
HWND Repository_QueryMainWindow( HWND Window, BYTE Find_frame_window = 1 )
{
 // �᫨ ���� �� 㪠���� - ������.
 if( Window == NULLHANDLE ) return NULLHANDLE;

 // ������ ���� ࠡ�祣� �⮫�.
 HWND Desktop = QueryDesktopWindow();

 // �᫨ ��࠭� ���� ࠡ�祣� �⮫� - ������.
 if( Window == Desktop ) return NULLHANDLE;

 // ������ த�⥫�᪮� ����.
 HWND Parent_window = WinQueryWindow( Window, QW_PARENT );

 // �᫨ த�⥫�᪮� ���� - ࠡ�稩 �⮫:
 if( Parent_window == Desktop )
  {
   // ��������� ���� ������ ���� ����� ࠬ��.
   if( Find_frame_window ) if( !Repository_IsFrameWindow( Window ) ) Window = NULLHANDLE;

   // �����頥� ����.
   return Window;
  }

 // ��ᬠ�ਢ��� �� த�⥫�᪨� ����.
 HWND Next_window = NULLHANDLE;

 while( Parent_window != Desktop && Parent_window != NULLHANDLE )
  {
   // ������ ᫥���饥 த�⥫�᪮� ����.
   Next_window = WinQueryWindow( Parent_window, QW_PARENT );

   // �᫨ �� �� ࠡ�稩 �⮫ - �த������ ��ॡ�� ����.
   if( Next_window != Desktop ) Parent_window = Next_window;
   // ���� - ������� ������� ����.
   else break;
  }

 // ��������� ���� ������ ���� ����� ࠬ��.
 if( Find_frame_window ) if( !Repository_IsFrameWindow( Parent_window ) ) Parent_window = NULLHANDLE;

 // �����頥� ����.
 return Parent_window;
}

// ��� ������ �ਫ������, ᮧ���襥 ���� ��� ࠡ���饥 � ���� VIO ���

// Frame_window - ���� ࠬ��
PID Repository_QueryWindowRealProcessID( HWND Frame_window )
{
 // �᫨ � ���� ����� ��४������� - ����� 㧭��� � �ਫ������, ᮧ���襥 ����.
 // ��� ���� VIO � ���� "idProcess" ����ᠭ� ���祭�� PID ࠡ����� � ��� �ਫ������.
 // �᫨ �� ����� ����訢��� PID ����, ����稬 PID ������� �����窨, ᮧ���襩 ���� VIO.
 if( Repository_IsVIOWindow( Frame_window ) )
  {
   HSWITCH Switch_handle = WinQuerySwitchHandle( Frame_window, NULLHANDLE );

   if( Switch_handle != NULLHANDLE )
    {
     SWCNTRL Task; WinQuerySwitchEntry( Switch_handle, &Task );
     if( Task.idProcess != 0 ) return Task.idProcess;
    }
  }
 // �᫨ �� �� ⥪�⮢�� ���� - �஡㥬 ������� PID ��몭������ ᯮᮡ��.
 else
  {
   PID Process_ID = 0; TID Thread_ID = 0;
   WinQueryWindowProcess( Frame_window, &Process_ID, &Thread_ID );

   #ifndef INCLUDED_BY_SHELL

   // ��� ����, ᮧ������ ᠬ�� OS/2 (ᯨ᮪ ����, ���� ࠡ�祣� �⮫�,
   // ᮮ�饭�� ��� �� �� ��⮢�� ⥪�⮢�� ����) ��祣� ������ �� ����.
   PID Desktop_process_ID = 0; TID Desktop_thread_ID = 0;
   WinQueryWindowProcess( QueryDesktopWindow(), &Desktop_process_ID, &Desktop_thread_ID );

   if( Desktop_process_ID != 0 && Process_ID == Desktop_process_ID ) return 0;

   #endif

   return Process_ID;
  }

 // ������.
 return 0;
}

// ��� ����砥� ᢮��⢠ �ਫ������, � ⮬ �᫥ ࠡ���饣� � ���� VIO ���

// Frame_window - ���� ࠬ��, Process_info - ᢮��⢠ �ਫ������.
// �᫨ ���� �� 㪠����, ���祭�� Process_ID ������ ���� ��⠭������ � Process_info.
// �� �६� ࠡ��� �������� ������ �맮�, �� �⮬ Recursive_calling != 0.
VOID Repository_QueryProcessInfo( HWND Frame_window, PPROCESSINFO Process_info, BYTE Recursive_calling )
{
 // ������ �ਫ������, ᮧ���襥 ����.
 PID Process_ID = Process_info->Process_ID; TID Thread_ID = 0;

 if( Process_ID == 0 ) Process_ID = Repository_QueryWindowRealProcessID( Frame_window );

 // �᫨ ��� �� 㤠���� ������� - ������.
 if( Process_ID == 0 ) return;

 {
  // �뤥�塞 ������.
  PVOID Info = NULL; INT Length = 1024; DosAllocMem( (PPVOID) &Info, Length, PAG_ALLOCATE );

  {
   // ������ ᢮��⢠ �ਫ������.
   APIRET Result = DosQuerySysState( QS_PROCESS, 0, Process_ID, Thread_ID, Info, Length );

   if( Result == NO_ERROR )
    {
     PQSPTRREC Top = (PQSPTRREC) Info; PQSPREC Process_record = Top->pProcRec;

     if( Process_record->RecType == QS_PROCESS ) if( Process_record->pid == Process_ID )
      {
       Process_info->Process_ID = Process_record->pid;
       Process_info->Parent_ID = Process_record->ppid;

       DosQueryModuleName( Process_record->hMte, SIZE_OF_PATH, Process_info->Exe_path );
       strcpy( Process_info->Exe_name, FindNameInPath( Process_info->Exe_path ) );
       CutNameInPath( Process_info->Exe_path );
      }
    }
  }

  // �᢮������� ������.
  DosFreeMem( Info ); Info = NULL;
 }

 // �᫨ �� �� ������ �맮�:
 if( !Recursive_calling )
  {
   // �᫨ ��� 㤠���� ��।�����:
   if( Process_info->Exe_name[ 0 ] != 0 )
    {
     // �᫨ �� �ᯮ���⥫� ������ - � ��� ����� ���� ����饭� ��㣮� �ਫ������.
     if( Repository_NamesAreEqually( Repository_FindApplicationInRepository( APP_CMD ), Process_info->Exe_name ) )
      {
       // ��ᬠ�ਢ��� ��᪮�쪮 �ਫ������ ��᫥ ����.
       INT Count = 0;

       for( Count = Process_info->Process_ID; Count < Process_info->Process_ID + 10; Count ++ )
        {
         // �᫨ ⠪�� �ਫ������ �������:
         if( DosVerifyPidTid( Count, 1 ) == NO_ERROR )
          {
           // ������ ��� ᢮��⢠.
           PROCESSINFO Descendant_info = { Count, 0, 0, 0 }; Repository_QueryProcessInfo( NULLHANDLE, &Descendant_info, RECURSIVE_CALLING );

           // �᫨ ��� ᮧ���� �⨬ �ਫ������� - ���������� ���.
           if( Descendant_info.Parent_ID == Process_info->Process_ID )
            memcpy( Process_info, &Descendant_info, sizeof( PROCESSINFO ) );
          }
        }
      }

     // �ਢ���� ��� �ਫ������ � �⠥���� ����.
     {
      PCHAR Name = Process_info->Exe_name;
      UpperCase( Name ); LowerCase( &Name[ 1 ] );
     }
    }
  }

 // ������.
 return;
}

#ifdef INCLUDED_BY_SHELL

// ��� ������ �������� �ਫ������, ᮧ���襣� ���� ���

// Frame_window - ���� ࠬ��, Name - ��ப� ��� ��������.
VOID Repository_QueryExeName( HWND Frame_window, PCHAR Name )
{
 // ������ ��� �ਫ������, ᮧ���襣� ����.
 PROCESSINFO Process_info = {0}; Repository_QueryProcessInfo( Frame_window, &Process_info, 0 );

 // ���������� ���.
 strcpy( Name, Process_info.Exe_name );

 // ������.
 return;
}

#endif

// ��� �஢���� ����, ������ ���� �ਫ������ � ᯨ᪥ ���

// Application - �ਫ������ ��� �ࠢ�����, Window - ���� �ਫ������, Filter - �᫮��� �⡮�.
BYTE Repository_WindowIsCreatedBy( INT Application, HWND Window, BYTE Filter = FLT_ALL )
{
 #ifndef INCLUDED_BY_SHELL

 // ������ ���� ࠬ��.
 HWND Frame_window = Repository_QueryFrameWindow( Window );

 // ������ ��� �ਫ������, ᮧ���襣� ����.
 CHAR Exe_name[ SIZE_OF_NAME ] = ""; GetDetectedExeName( Frame_window, Exe_name );

 // �᫨ ��� 㤠���� ��।�����:
 if( Exe_name[ 0 ] != 0 )
  {
   // �஢��塞 ���.
   if( Repository_NamesAreEqually( Repository_FindApplicationInRepository( Application, Filter ), Exe_name ) ) return 1;
  }

 // ������ ���� ࠡ�祩 ������.
 HWND Client_window = WinWindowFromID( Frame_window, FID_CLIENT );

 if( Client_window != NULLHANDLE )
  {
   // ������ ���, ��� ����� ��।����� ����.
   CHAR Client_name[ SIZE_OF_NAME ] = ""; WinQueryClassName( Client_window, SIZE_OF_NAME, Client_name );

   // �஢��塞 ���.
   if( Repository_NamesAreEqually( Repository_FindApplicationInRepository( Application, Filter ), Client_name ) ) return 1;
  }

 // �᫨ �஢������ �� ���� ࠬ��:
 if( Window != Frame_window )
  {
   // ������ ���, ��� ����� ��।����� ����.
   CHAR Window_name[ SIZE_OF_NAME ] = ""; WinQueryClassName( Window, SIZE_OF_NAME, Window_name );

   // �஢��塞 ���.
   if( Repository_NamesAreEqually( Repository_FindApplicationInRepository( Application, Filter ), Window_name ) ) return 1;
  }

 #else

 // ������ ��� �ਫ������, ᮧ���襣� ����.
 CHAR Exe_name[ SIZE_OF_NAME ] = ""; Repository_QueryExeName( Window, Exe_name );

 // �஢��塞 ���.
 if( Repository_NamesAreEqually( Repository_FindApplicationInRepository( Application, Filter ), Exe_name ) ) return 1;

 #endif

 // ������.
 return 0;
}

// ��� �஢����, ����� �� ������ ���� ���� ����� �ᯮ���⥫� ������ ���

// Exe_name - ��� �ਫ������, ᮧ���襣� ����.
BYTE Repository_IsCommandExecutorWindow( PCHAR Exe_name )
{
 // �஢��塞 ����.
 if( Repository_NamesAreEqually( Repository_FindApplicationInRepository( APP_CMD ), Exe_name ) ) return 1;
 if( Repository_NamesAreEqually( Repository_FindApplicationInRepository( APP_COM ), Exe_name ) ) return 1;

 // ������.
 return 0;
}

// ��� �஢����, �ᯮ������ �� ���� ��� �믮������ ����� ���

// Purpose - �����, Frame_window - ���� ࠬ��, Filter - �᫮��� �⡮�.
BYTE Repository_WindowIsUsedTo( INT Purpose, HWND Frame_window, BYTE Filter = FLT_ALL )
{
 // ������ ��� �ਫ������, ᮧ���襣� ����.
 CHAR Exe_name[ SIZE_OF_NAME ] = "";

 #ifndef INCLUDED_BY_SHELL
 GetDetectedExeName( Frame_window, Exe_name );
 #else
 Repository_QueryExeName( Frame_window, Exe_name );
 #endif

 // �᫨ ��� 㤠���� ��।�����:
 if( Exe_name[ 0 ] != 0 )
  {
   // �஢��塞, ���� �� �� �ਫ������ � ᯨ᪥.
   INT Position = Repository_FindExeNameInRepository( Exe_name, Filter );

   // �᫨ ��� ����:
   if( Position != -1 )
    {
     // �஢��塞 ����⢨�.
     if( Repository.Items[ Position ].Purpose == Purpose ) return 1;
    }
  }

 // ������.
 return 0;
}

// ��� �஢����, ���ਭ����� �� ���� �������� ������� ���

// Action - ����⢨�, Frame_window - ���� ࠬ��, Filter - �᫮��� �⡮�.
BYTE Repository_CommandForWindowIs( INT Action, HWND Frame_window, BYTE Filter = FLT_ALL )
{
 // ������ ��� �ਫ������, ᮧ���襣� ����.
 CHAR Exe_name[ SIZE_OF_NAME ] = "";

 #ifndef INCLUDED_BY_SHELL
 GetDetectedExeName( Frame_window, Exe_name );
 #else
 Repository_QueryExeName( Frame_window, Exe_name );
 #endif

 // �᫨ ��� 㤠���� ��।�����:
 if( Exe_name[ 0 ] != 0 )
  {
   // �஢��塞, ���� �� �� �ਫ������ � ᯨ᪥.
   INT Position = Repository_FindExeNameInRepository( Exe_name, Filter );

   // �᫨ ��� ����:
   if( Position != -1 )
    {
     // �஢��塞 ����⢨�.
     if( Repository.Items[ Position ].Action == Action ) return 1;
    }
  }

 // ������.
 return 0;
}