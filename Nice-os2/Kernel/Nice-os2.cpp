// ����ﭭ� ����稭�.
#include "..\\Shared\\General.h"
#include "..\\Shared\\AbstractClass\\AbstractClass_code.cpp"

// �맮�� C/C++.
#include "..\\Shared\\StdLib\\StdLib_code.cpp"
#include "..\\Shared\\StdLib.cpp"

// ����� � ��ப���.
#include "..\\Shared\\Strings.h"
#include "..\\Shared\\Strings\\Strings_data.cpp"
#include "..\\Shared\\Strings\\Strings_code.cpp"
#include "..\\Shared\\Strings.cpp"

// �������⥫�� �맮�� OS/2.
#include "..\\Shared\\SysState.h"

// ���᮪ �������� ����⥫� ���� � �ਫ������.
#include "..\\Shared\\Repository.h"

// ���譨� ᮮ�饭��.
#include "..\\Shared\\Messages4Daemon.h"

// �⢥�� �� ��⮪�� �ਫ������.
#include "Core\\ThreadResponds.h"

// ����� � 䠩���� � PIPE-ᮥ������ﬨ.
#include "..\\Shared\\Pipes\\Pipes_code.cpp"
#include "..\\Shared\\Pipes.cpp"

#include "..\\Shared\\Files\\Files_code.cpp"
#include "..\\Shared\\Files.cpp"

// �⫠��� �ਫ������.
#include "Core\\Debug\\Debug_code.cpp"
#include "Core\\Debug.cpp"

// �ਫ������ � ᯨ᮪ ��� ��⠢�����.
typedef VOID ( MODPROC_STARTTHREAD ) ( VOID );
typedef VOID ( MODPROC_POSTQUITMSG ) ( VOID );
typedef VOID ( MODPROC_SHUTDOWNALL ) ( VOID );

typedef VOID ( MODPROC_TUNEMODULE    ) ( HINI );
typedef VOID ( MODPROC_JUMPBEFOREGO  ) ( VOID );

typedef VOID ( MODPROC_COLORSREPORTER ) ( PVOID );
typedef VOID ( MODPROC_VALUESREPORTER ) ( PVOID );

typedef struct _MODULE
 {
  // ����� ��������.
  ULONG cb;

  // ��⮪.
  TID Thread; LONG Priority;
  // ��� ��⮪ ����⢨⥫쭮 �㦥�.
  BYTE Required;
  // ��।� ᮮ�饭�� ��⮪�.
  HMQ Message_queue;

  // �����⥫� �� �맮��.
  MODPROC_STARTTHREAD* StartThread;
  MODPROC_POSTQUITMSG* PostQuitMsg;
  MODPROC_SHUTDOWNALL* ShutdownAll;

  MODPROC_TUNEMODULE* TuneModule;
  MODPROC_JUMPBEFOREGO* JumpBeforeGo;

  MODPROC_COLORSREPORTER* SysColorsChangeReporter;
  MODPROC_VALUESREPORTER* SysValuesChangeReporter;
 }
MODULE; typedef MODULE* PMODULE;

#define MODLIST_LENGTH 48

typedef struct _MODULE_POINTERS
 {
  // ��� ������祭�� ��⠢���騥. ����� 㪠��⥫� �㤥� 㪠�뢠�� �� ����
  // ������ ���ᨢ� ModList, �� ���祭�� ���⠢������ �� �맮�� "StartKernel".
  PMODULE Inspector;
  PMODULE MouseMapper;
  PMODULE VIOFontManager;
  PMODULE VIOMenuManager;
  PMODULE Scroller;
  PMODULE Roller;
  PMODULE Painter;
  PMODULE Diver;
  PMODULE Performer;
  PMODULE Remover;
  PMODULE PriorityManager;
  PMODULE Launcher;
  PMODULE Patcher;
  PMODULE RoomsTracker;
  PMODULE Rooms;
  PMODULE WindowManager;
  PMODULE VIOMonitor;
  PMODULE Controller;
  PMODULE Definer;
  PMODULE MMKbdListener;
  PMODULE Clipper;
  PMODULE KeyMapper;
  PMODULE Clicker;
  PMODULE Arranger;
  PMODULE Changer;
  PMODULE Applier;
  PMODULE Waiter;

  // ���⠢���騥 "�� ���饥". ��� ��� 㪠��⥫� ⮦� ��������.
  PMODULE AnotherModule_27;
  PMODULE AnotherModule_28;
  PMODULE AnotherModule_29;
  PMODULE AnotherModule_30;
  PMODULE AnotherModule_31;
  PMODULE AnotherModule_32;

  PMODULE Module_pointer_at_ModListLength;
 }
MODULE_POINTERS;

typedef struct _ENHANCER
 {
  // �ਫ������.
  HAB Application; HMODULE Module;

  // �������� �� ᮮ�饭�ﬨ ����祭�.
  BYTE Hooks_are_enabled;

  // ���⠢���騥 �ਫ������.
  MODULE ModList[ MODLIST_LENGTH ]; MODULE_POINTERS Modules;
 }
ENHANCER; ENHANCER Enhancer;

// ��ॡ�� ��⠢����� �ਫ������.
#include "Core\\ModList\\ModList_code.cpp"
#include "Core\\ModList.cpp"

// ��६���� � ᢮��⢠ ���㦥���.
#include "..\\Shared\\Environment\\Environment_data.cpp"
#include "..\\Shared\\Environment\\Environment_code.cpp"
#include "..\\Shared\\Environment.cpp"

#include "..\\Shared\\EnhancerProperties\\EnhancerProperties_code.cpp"
#include "..\\Shared\\EnhancerProperties.cpp"

// ������ �⥪� ��� ��⮪��.
#define THREAD_STACK_SIZE 32768

// ����ன��.
#include "..\\Shared\\Settings.h"

// ���窨 � ����ࠦ����.
#include "Resources\\Resources_data.cpp"
#include "Resources\\Resources_stop.cpp"

// ����饭�� ��� ��⮪��.
#include "Modules\\Messages.h"

// ��ᯮ�������� ���� � �ਫ������.
#include "Core\\WinPrpListAndRepository.h"
#include "Core\\WindowTypesAndRepository.h"

#include "..\\Shared\\Repository\\Repository_data.cpp"
#include "..\\Shared\\Repository\\Repository_code.cpp"
#include "..\\Shared\\Repository.cpp"

#include "Core\\WindowTypes.h"
#include "Core\\WindowTypes\\WindowTypes_code.cpp"
#include "Core\\WindowTypes.cpp"

#include "Core\\Repository\\Repository_data.cpp"
#include "Core\\Repository\\Repository_code.cpp"
#include "Core\\Repository\\Repository_init.cpp"
#include "Core\\Repository\\Repository_tune.cpp"
#include "Core\\Repository\\Repository_link.cpp"
#include "Core\\Repository.cpp"

// ��ᯮ�������� �।��।������� ᢮��� ����
#include "Core\\PMMetrics\\PMMetrics_code.cpp"
#include "Core\\PMMetrics.cpp"

#include "Core\\Workplace\\Workplace_data.cpp"
#include "Core\\Workplace\\Workplace_code.cpp"
#include "Core\\Workplace.cpp"

// ��६���� � ᢮��⢠ ���㦥���.
#include "Core\\Environment\\Environment_data.cpp"
#include "Core\\Environment\\Environment_hook.cpp"
#include "Core\\Environment\\Environment_code.cpp"
#include "Core\\Environment.cpp"

// ���� ����.
#include "..\\Shared\\Searcher.h"
#include "..\\Shared\\Searcher\\Searcher_code.cpp"
#include "..\\Shared\\Searcher.cpp"

// �஢�ઠ ᯨ᪠ �������� �ਫ������ � ���窮� ��� ���.
#include "Core\\RepositoryChecker\\RepositoryChecker_code.cpp"
#include "Core\\RepositoryChecker.cpp"

// ���祭�� ��� ��⮪��.
#include "Modules\\Constants.h"

// ���᮪ ᢮��� ����.
#include "..\\Shared\\AbstractPrpList\\AbstractPrpList_data.cpp"
#include "..\\Shared\\AbstractPrpList\\AbstractPrpList_code.cpp"

#include "Core\\WinPrpList.h"
#include "Core\\WinPrpList\\WinPrpList_data.cpp"
#include "Core\\WinPrpList\\WinPrpList_code.cpp"
#include "Core\\WinPrpList.cpp"

// ����� � ��������ன � �����.
#include "..\\Shared\\KbdMouse.h"
#include "..\\Shared\\KbdMouse\\KbdMouse_code.cpp"
#include "..\\Shared\\KbdMouse.cpp"

#include "..\\Shared\\Scan_codes.h"
#include "..\\Shared\\MMKeys.h"

#ifdef I386_ARCHITECTURE
  #include "Core\\KbdMouse_i386\\KbdMouse_i386_data.cpp"
  #include "Core\\KbdMouse_i386\\KbdMouse_i386_code.cpp"
  #include "Core\\KbdMouse_i386.cpp"
#endif

#include "Core\\KbdLocks\\KbdLocks_data.cpp"
#include "Core\\KbdLocks\\KbdLocks_code.cpp"
#include "Core\\KbdLocks.cpp"

// ��ᮢ����.
#include "..\\Shared\\GpiExt\\GpiExt_code.cpp"
#include "..\\Shared\\GpiExt.cpp"

// ����� � ����ࠦ���ﬨ.
#include "..\\Shared\\Images\\Images_code.cpp"
#include "..\\Shared\\Images.cpp"

// ����� � ᯨ᪮� ����.
#include "..\\Shared\\WindowList\\WindowList_code.cpp"
#include "..\\Shared\\WindowList.cpp"

#include "Core\\WindowList\\WindowList_code.cpp"
#include "Core\\WindowList.cpp"

// ��⮤� ��� �஢�ન ��᫥�������� ᮮ�饭��.
#include "Core\\HookEvents\\HookEvents_code.cpp"
#include "Core\\HookEvents.cpp"

// ����� � ����.
#include "..\\Shared\\MenuItems\\MenuItems_data.cpp"
#include "..\\Shared\\MenuItems\\MenuItems_code.cpp"
#include "..\\Shared\\MenuItems.cpp"

// ����� � ������.
#include "..\\Shared\\WindowManagement\\WindowManagement_code.cpp"
#include "..\\Shared\\WindowManagement.cpp"

#include "Core\\WinPrpListAndRepository\\WinPrpListAndRepository_base.cpp"
#include "Core\\WinPrpListAndRepository\\WinPrpListAndRepository_hook.cpp"
#include "Core\\WinPrpListAndRepository\\WinPrpListAndRepository_code.cpp"
#include "Core\\WinPrpListAndRepository.cpp"

#include "Core\\WinPrpListAndPainter\\WinPrpListAndPainter_code.cpp"
#include "Core\\WinPrpListAndPainter.cpp"

// ����� � ������ ��� ������ � ��࠭���� 䠩���.
#include "Core\\FileDialogs\\FileDialogs_code.cpp"
#include "Core\\FileDialogs.cpp"

// ����� � ������ ��������.
#include "..\\Shared\\DlgBoxes.h"
#include "Core\\DlgBox.h"
#include "Core\\DlgBox\\DlgBox_data.cpp"
#include "Core\\DlgBox\\DlgBox_code.cpp"
#include "Core\\DlgBox.cpp"

// ����� � ����� ������.
#include "..\\Shared\\Clipboard\\Clipboard_code.cpp"
#include "..\\Shared\\Clipboard.cpp"

// ��⮤� ��� ��᫥������� ������.
#include "Modules\\RoomsTracker\\RoomsTracker_data.cpp"
#include "Modules\\RoomsTracker\\RoomsTracker_code.cpp"
#include "Modules\\RoomsTracker.cpp"

// ����-������᪠, ���஥ ��祣� �� ����.
#include "Core\\Curtain\\Curtain_data.cpp"
#include "Core\\Curtain\\Curtain_code.cpp"
#include "Core\\Curtain\\Curtain_link.cpp"
#include "Core\\Curtain.cpp"

// ���������� ����.
#include "Core\\Repaint\\Repaint_code.cpp"
#include "Core\\Repaint.cpp"

// ����饭��, ����� ����⥫� ���뫠�� �ਫ������.
#include "Hooks\\HookMessages.h"

// ����⠭���� ���ﭨ� ���������� �� �஢�� V-Keys.
#include "Core\\KbdState\\KbdState_data.cpp"
#include "Core\\KbdState\\KbdState_base.cpp"
#include "Core\\KbdState\\KbdState_hook.cpp"
#include "Core\\KbdState.cpp"

// ������� �ਮ��⮢ �ਫ������.
#include "Core\\Priority\\Priority_hook.cpp"
#include "Core\\Priority\\Priority_code.cpp"
#include "Core\\Priority.cpp"

// ���뢠��� �ਫ������ � �ᯮ�짮������ ���������⥩ �����窨 OS/2.
#include "Core\\TerminateProcess\\TerminateProcess_hook.cpp"
#include "Core\\TerminateProcess\\TerminateProcess_code.cpp"
#include "Core\\TerminateProcess.cpp"

// ��������� ����஥� � 梥⮢ �����窨 OS/2.
#include "Core\\SysValues\\SysValues_data.cpp"
#include "Core\\SysValues\\SysValues_code.cpp"
#include "Core\\SysValues.cpp"

// ���⠢���騥 ����⥫�.
#include "Modules\\Inspector\\Inspector_data.cpp"
#include "Modules\\Inspector\\Inspector_code.cpp"
#include "Modules\\Inspector\\Inspector_init.cpp"
#include "Modules\\Inspector\\Inspector_tune.cpp"
#include "Modules\\Inspector\\Inspector_jump.cpp"
#include "Modules\\Inspector\\Inspector_work.cpp"
#include "Modules\\Inspector\\Inspector_link.cpp"
#include "Modules\\Inspector.cpp"

#include "Modules\\MouseMapper\\MouseMapper_data.cpp"
#include "Modules\\MouseMapper\\MouseMapper_perm.cpp"
#include "Modules\\MouseMapper\\MouseMapper_base.cpp"
#include "Modules\\MouseMapper\\MouseMapper_hook.cpp"
#include "Modules\\MouseMapper\\MouseMapper_init.cpp"
#include "Modules\\MouseMapper\\MouseMapper_tune.cpp"
#include "Modules\\MouseMapper\\MouseMapper_link.cpp"
#include "Modules\\MouseMapper.cpp"

#include "Modules\\VIOFontManager\\VIOFontManager_data.cpp"
#include "Modules\\VIOFontManager\\VIOFontManager_base.cpp"
#include "Modules\\VIOFontManager\\VIOFontManager_hook.cpp"
#include "Modules\\VIOFontManager\\VIOFontManager_code.cpp"
#include "Modules\\VIOFontManager\\VIOFontManager_init.cpp"
#include "Modules\\VIOFontManager\\VIOFontManager_tune.cpp"
#include "Modules\\VIOFontManager\\VIOFontManager_link.cpp"
#include "Modules\\VIOFontManager.cpp"

#include "Modules\\VIOMenuManager\\VIOMenuManager_data.cpp"
#include "Modules\\VIOMenuManager\\VIOMenuManager_base.cpp"
#include "Modules\\VIOMenuManager\\VIOMenuManager_hook.cpp"
#include "Modules\\VIOMenuManager\\VIOMenuManager_code.cpp"
#include "Modules\\VIOMenuManager\\VIOMenuManager_init.cpp"
#include "Modules\\VIOMenuManager\\VIOMenuManager_tune.cpp"
#include "Modules\\VIOMenuManager\\VIOMenuManager_work.cpp"
#include "Modules\\VIOMenuManager.cpp"

#include "Modules\\Waiter.h"

#include "Modules\\Scroller\\Scroller_data.cpp"
#include "Modules\\Scroller\\Scroller_perm.cpp"
#include "Modules\\Scroller\\Scroller_base.cpp"
#include "Modules\\Scroller\\Scroller_bars.cpp"
#include "Modules\\Scroller\\Scroller_save.cpp"
#include "Modules\\Scroller\\Scroller_hook.cpp"
#include "Modules\\Scroller\\Scroller_post.cpp"
#include "Modules\\Scroller\\Scroller_code.cpp"
#include "Modules\\Scroller\\Scroller_init.cpp"
#include "Modules\\Scroller\\Scroller_list.cpp"
#include "Modules\\Scroller\\Scroller_tune.cpp"
#include "Modules\\Scroller\\Scroller_work.cpp"
#include "Modules\\Scroller.cpp"

#include "Modules\\Roller\\Roller_data.cpp"
#include "Modules\\Roller\\Roller_code.cpp"
#include "Modules\\Roller.cpp"

#include "Modules\\Painter\\Painter_data.cpp"
#include "Modules\\Painter\\Painter_perm.cpp"
#include "Modules\\Painter\\Painter_subs.cpp"
#include "Modules\\Painter\\Painter_base.cpp"
#include "Modules\\Painter\\Painter_bars.cpp"
#include "Modules\\Painter\\Painter_hook.cpp"
#include "Modules\\Painter\\Painter_prep.cpp"
#include "Modules\\Painter\\Painter_code.cpp"
#include "Modules\\Painter\\Painter_init.cpp"
#include "Modules\\Painter\\Painter_tune.cpp"
#include "Modules\\Painter\\Painter_work.cpp"
#include "Modules\\Painter\\Painter_stop.cpp"
#include "Modules\\Painter\\Painter_vals.cpp"
#include "Modules\\Painter\\Painter_link.cpp"
#include "Modules\\Painter.cpp"

#include "Modules\\Diver\\Diver_data.cpp"
#include "Modules\\Diver\\Diver_icon.cpp"
#include "Modules\\Diver\\Diver_code.cpp"
#include "Modules\\Diver\\Diver_work.cpp"
#include "Modules\\Diver.cpp"

#include "Modules\\Performer\\Performer_data.cpp"
#include "Modules\\Performer\\Performer_base.cpp"
#include "Modules\\Performer\\Performer_hook.cpp"
#include "Modules\\Performer\\Performer_code.cpp"
#include "Modules\\Performer\\Performer_link.cpp"
#include "Modules\\Performer.cpp"

#include "Modules\\Remover\\Remover_data.cpp"
#include "Modules\\Remover\\Remover_hook.cpp"
#include "Modules\\Remover\\Remover_code.cpp"
#include "Modules\\Remover\\Remover_init.cpp"
#include "Modules\\Remover\\Remover_tune.cpp"
#include "Modules\\Remover\\Remover_jump.cpp"
#include "Modules\\Remover\\Remover_work.cpp"
#include "Modules\\Remover\\Remover_stop.cpp"
#include "Modules\\Remover.cpp"

#include "Modules\\PriorityManager.h"
#include "Modules\\PriorityManager\\PriorityManager_data.cpp"
#include "Modules\\PriorityManager\\PriorityManager_perm.cpp"
#include "Modules\\PriorityManager\\PriorityManager_base.cpp"
#include "Modules\\PriorityManager\\PriorityManager_hook.cpp"
#include "Modules\\PriorityManager\\PriorityManager_init.cpp"
#include "Modules\\PriorityManager\\PriorityManager_tune.cpp"
#include "Modules\\PriorityManager.cpp"

#include "Modules\\Launcher\\Launcher_data.cpp"
#include "Modules\\Launcher\\Launcher_perm.cpp"
#include "Modules\\Launcher\\Launcher_hook.cpp"
#include "Modules\\Launcher\\Launcher_code.cpp"
#include "Modules\\Launcher\\Launcher_tune.cpp"
#include "Modules\\Launcher\\Launcher_work.cpp"
#include "Modules\\Launcher.cpp"

#include "Modules\\Patcher\\Patcher_data.cpp"
#include "Modules\\Patcher\\Patcher_hook.cpp"
#include "Modules\\Patcher\\Patcher_code.cpp"
#include "Modules\\Patcher\\Patcher_init.cpp"
#include "Modules\\Patcher\\Patcher_tune.cpp"
#include "Modules\\Patcher.cpp"

#include "Modules\\Rooms\\Rooms_data.cpp"
#include "Modules\\Rooms\\Rooms_perm.cpp"
#include "Modules\\Rooms\\Rooms_base.cpp"
#include "Modules\\Rooms\\Rooms_hook.cpp"
#include "Modules\\Rooms\\Rooms_code.cpp"
#include "Modules\\Rooms\\Rooms_init.cpp"
#include "Modules\\Rooms\\Rooms_tune.cpp"
#include "Modules\\Rooms\\Rooms_work.cpp"
#include "Modules\\Rooms\\Rooms_stop.cpp"
#include "Modules\\Rooms\\Rooms_vals.cpp"
#include "Modules\\Rooms\\Rooms_link.cpp"
#include "Modules\\Rooms.cpp"

#include "Modules\\WindowManager\\WindowManager_code.cpp"
#include "Modules\\WindowManager\\WindowManager_tune.cpp"
#include "Modules\\WindowManager\\WindowManager_work.cpp"
#include "Modules\\WindowManager.cpp"

#include "Modules\\VIOMonitor\\VIOMonitor_data.cpp"
#include "Modules\\VIOMonitor\\VIOMonitor_code.cpp"
#include "Modules\\VIOMonitor\\VIOMonitor_tune.cpp"
#include "Modules\\VIOMonitor\\VIOMonitor_work.cpp"
#include "Modules\\VIOMonitor.cpp"

#include "Modules\\Controller\\Controller_data.cpp"
#include "Modules\\Controller\\Controller_base.cpp"
#include "Modules\\Controller\\Controller_hook.cpp"
#include "Modules\\Controller\\Controller_code.cpp"
#include "Modules\\Controller\\Controller_init.cpp"
#include "Modules\\Controller\\Controller_tune.cpp"
#include "Modules\\Controller\\Controller_jump.cpp"
#include "Modules\\Controller\\Controller_work.cpp"
#include "Modules\\Controller\\Controller_stop.cpp"
#include "Modules\\Controller.cpp"

#include "Modules\\Definer\\Definer_data.cpp"
#include "Modules\\Definer\\Definer_hook.cpp"
#include "Modules\\Definer\\Definer_init.cpp"
#include "Modules\\Definer\\Definer_tune.cpp"
#include "Modules\\Definer\\Definer_vals.cpp"
#include "Modules\\Definer.cpp"

#include "Modules\\MMKbdListener\\MMKbdListener_code.cpp"
#include "Modules\\MMKbdListener\\MMKbdListener_tune.cpp"
#include "Modules\\MMKbdListener\\MMKbdListener_work.cpp"
#include "Modules\\MMKbdListener.cpp"

#include "Modules\\Clipper.h"
#include "Modules\\Clipper\\Clipper_data.cpp"
#include "Modules\\Clipper\\Clipper_perm.cpp"
#include "Modules\\Clipper\\Clipper_base.cpp"
#include "Modules\\Clipper\\Clipper_hook.cpp"
#include "Modules\\Clipper\\Clipper_code.cpp"
#include "Modules\\Clipper\\Clipper_init.cpp"
#include "Modules\\Clipper\\Clipper_tune.cpp"
#include "Modules\\Clipper\\Clipper_work.cpp"
#include "Modules\\Clipper\\Clipper_vals.cpp"
#include "Modules\\Clipper\\Clipper_link.cpp"
#include "Modules\\Clipper.cpp"

#include "Modules\\KeyMapper\\KeyMapper_data.cpp"
#include "Modules\\KeyMapper\\KeyMapper_hook.cpp"
#include "Modules\\KeyMapper\\KeyMapper_init.cpp"
#include "Modules\\KeyMapper\\KeyMapper_tune.cpp"
#include "Modules\\KeyMapper.cpp"

#include "Modules\\Clicker\\Clicker_data.cpp"
#include "Modules\\Clicker\\Clicker_perm.cpp"
#include "Modules\\Clicker\\Clicker_hook.cpp"
#include "Modules\\Clicker\\Clicker_code.cpp"
#include "Modules\\Clicker\\Clicker_init.cpp"
#include "Modules\\Clicker\\Clicker_tune.cpp"
#include "Modules\\Clicker\\Clicker_work.cpp"
#include "Modules\\Clicker.cpp"

#include "Modules\\Arranger\\Arranger_data.cpp"
#include "Modules\\Arranger\\Arranger_hook.cpp"
#include "Modules\\Arranger\\Arranger_code.cpp"
#include "Modules\\Arranger\\Arranger_init.cpp"
#include "Modules\\Arranger\\Arranger_tune.cpp"
#include "Modules\\Arranger\\Arranger_work.cpp"
#include "Modules\\Arranger\\Arranger_link.cpp"
#include "Modules\\Arranger.cpp"

#include "Modules\\Changer\\Changer_code.cpp"
#include "Modules\\Changer\\Changer_tune.cpp"
#include "Modules\\Changer\\Changer_work.cpp"
#include "Modules\\Changer.cpp"

#include "Modules\\Applier\\Applier_data.cpp"
#include "Modules\\Applier\\Applier_base.cpp"
#include "Modules\\Applier\\Applier_hook.cpp"
#include "Modules\\Applier\\Applier_code.cpp"
#include "Modules\\Applier\\Applier_list.cpp"
#include "Modules\\Applier\\Applier_init.cpp"
#include "Modules\\Applier\\Applier_tune.cpp"
#include "Modules\\Applier\\Applier_jump.cpp"
#include "Modules\\Applier\\Applier_work.cpp"
#include "Modules\\Applier\\Applier_scan.cpp"
#include "Modules\\Applier.cpp"

#include "Modules\\Waiter\\Waiter_data.cpp"
#include "Modules\\Waiter\\Waiter_code.cpp"
#include "Modules\\Waiter.cpp"

// ��ࠡ��稪� ᮡ�⨩.
#include "Hooks\\HookMethods.cpp"

// ���� ᮮ�饭��.
#include "Core\\MessageBox\\MessageBox_code.cpp"
#include "Core\\MessageBox.cpp"

// ����ன�� �ਫ������.
typedef struct _ENHANCER_KRNL
 {
  // ����७��� ��६����.
  typedef struct _RTSTS
   {
    // ����� �� ���� ����⥫�.
    BYTE Nice_is_visible;
    // ���� �����稪�.
    HWND Launcher_window;
   }
  RTSTS; RTSTS RTSettings;
 }
ENHANCER_KRNL;

ENHANCER_KRNL Krnl;

// ��� �⪫�砥� �� ����ன�� ���

VOID Krnl_DisableKernelSettings( VOID )
{
 // ����뢠�� �� ��६����, �⪫�砥� ᫥����� �� ᮮ�饭�ﬨ.
 // ���� VIO �த������ �ᯮ�짮���� Nice-os2.dll, ���⮬� � ��।� ��⮪�� ���� ᤥ���� ࠢ�묨 NULLHANDLE.
 bzero( &Enhancer, sizeof( ENHANCER ) );
 bzero( &Krnl, sizeof( ENHANCER_KRNL ) );

 // ������.
 return;
}

// ��� ��⠥� ᯨ᮪ �ਫ������ ���

VOID EXPENTRY Krnl_ReadRepository( VOID )
{
 // ���뢠�� 䠩� ����஥�.
 CHAR Settings_file_name[ SIZE_OF_PATH ] = ""; GetSettingsFileName( Settings_file_name );
 HINI Ini_file = OpenIniProfile( Enhancer.Application, Settings_file_name );

 // ��⠥� ᯨ᮪ �ਫ������.
 ReadRepository( Ini_file );

 // ����뢠�� 䠩� ����஥�.
 PrfCloseProfile( Ini_file );

 // ������.
 return;
}

// ��� ����ࠨ���� ����⥫� ��। ᮧ������ ��⮪�� ���

// �� ��६���� - ���譨�.
VOID EXPENTRY Krnl_StartKernel( HAB Application, HMODULE Module, BYTE Nice_is_visible, HWND Launcher_window )
{
 // ������砥� �㦥��� ��⮤�.
 StdLib_Start( Application );
 Strings_Start();
 Pipes_Start();
 Files_Start();
 Environment_Start(); Krnl_Environment_Start();
 EnhancerProperties_Start();
 Repository_Start();
 WindowTypes_Start();
 Krnl_Repository_Start();
 PMMetrics_Start();
 Workplace_Start();
 Krnl_Environment_Start();
 Searcher_Start();
 RepositoryChecker_Start();
 WinPrpList_Start();
 KbdMouse_Start(); Krnl_KbdMouse_i386_Start();
 KbdLocks_Start();
 GpiExt_Start();
 Images_Start();
 WindowList_Start(); Krnl_WindowList_Start();
 HookEvents_Start();
 WindowManagement_Start();
 WinPrpListAndRepository_Start();
 WinPrpListAndPainter_Start();
 FileDialogs_Start();
 MenuItems_Start();
 Clipboard_Start();
 Krnl_DlgBox_Start();
 Curtain_Start();
 Repaint_Start();
 KbdState_Start();
 Priority_Start();
 TerminateProcess_Start();
 SysValues_Start();

 // ����뢠�� �� ����ன��, �᫨ ��� ����� ������� �� �।���� ����᪮�.
 Krnl_DisableKernelSettings();

 // ���������� �ਫ������.
 Enhancer.Application = Application;
 Enhancer.Module = Module;

 // ����������, ����� �� ���� ����⥫�.
 Krnl.RTSettings.Nice_is_visible = Nice_is_visible;

 // ���������� ���� �����稪�.
 Krnl.RTSettings.Launcher_window = Launcher_window;

 // ��⠭�������� 㪠��⥫� � ᯨ᪥ ��⠢����� ����⥫�.
 {
  MODULE_POINTERS Module_pointers =
   {
    &Enhancer.ModList[  0 ],
    &Enhancer.ModList[  1 ],
    &Enhancer.ModList[  2 ],
    &Enhancer.ModList[  3 ],
    &Enhancer.ModList[  4 ],
    &Enhancer.ModList[  5 ],
    &Enhancer.ModList[  6 ],
    &Enhancer.ModList[  7 ],
    &Enhancer.ModList[  8 ],
    &Enhancer.ModList[  9 ],
    &Enhancer.ModList[ 10 ],
    &Enhancer.ModList[ 11 ],
    &Enhancer.ModList[ 12 ],
    &Enhancer.ModList[ 13 ],
    &Enhancer.ModList[ 14 ],
    &Enhancer.ModList[ 15 ],
    &Enhancer.ModList[ 16 ],
    &Enhancer.ModList[ 17 ],
    &Enhancer.ModList[ 18 ],
    &Enhancer.ModList[ 19 ],
    &Enhancer.ModList[ 20 ],
    &Enhancer.ModList[ 21 ],
    &Enhancer.ModList[ 22 ],
    &Enhancer.ModList[ 23 ],
    &Enhancer.ModList[ 24 ],
    &Enhancer.ModList[ 25 ],
    &Enhancer.ModList[ 26 ],
    &Enhancer.ModList[ 27 ],
    &Enhancer.ModList[ 28 ],

    &Enhancer.ModList[ 29 ],
    &Enhancer.ModList[ 30 ],

    &Enhancer.ModList[ 31 ]
   };

  memcpy( &Enhancer.Modules, &Module_pointers, sizeof( MODULE_POINTERS ) );
 }

 // �⪫�砥� ᮮ�饭�� �� �訡���.
 DosError( FERR_DISABLEHARDERR | FERR_DISABLEEXCEPTION );
 DosSuppressPopUps( SUPPRESS_POPUPS, 0 );
 DosDumpProcess( 0, 0, 0 );

 // ������ ���� ࠡ�祣� �⮫�.
 HWND Desktop = QueryDesktopWindow();

 // ������ ����ன�� ������� �����窨.
 WinSetSysValue( Desktop, SV_CXBYTEALIGN, 0 );
 WinSetSysValue( Desktop, SV_CYBYTEALIGN, 0 );
 WinSetSysValue( Desktop, SV_CXALIGN, 0 );
 WinSetSysValue( Desktop, SV_CYALIGN, 0 );

 // ����砥� �ࠢ����� ��ࠡ��� ᮮ�饭��.
 WinSetSysValue( Desktop, SV_ASYNCFOCUSCHANGE, 1 );
 WinSetSysValue( Desktop, SV_FOCUSCHANGESENS, 5 );

 // ��४��砥� �࠭�⥫� �࠭� � ०�� "Screen Saver mode".
 ULONG Screen_saver_mode = 1; PrfWriteProfileData( HINI_USERPROFILE, "PM_Lockup", "LockupScreenSaverMode", &Screen_saver_mode, sizeof( ULONG ) );

 // �᫨ �����窠 WPS ��������� - �஢��塞, �� �� Nice �맢�� � Startup.cmd.
 if( !ShellIsWPS() ) if( StartupCmdIsPresent() )
  {
   // ���� �����஥ �६�.
   for( INT Count = 0; Count < 100; Count ++ )
    {
     // �믮��塞 ����প� � 1/10 ᥪ㭤�.
     DosSleep( 100 );

     // �᫨ �����窠 ����㦥�� - �४�頥� ��������.
     if( ShellIsWPS() ) break;

     // �᫨ ���� Startup.cmd ��祧�� - ���� �� 1 ᥪ㭤� � �४�頥� ��������.
     if( !StartupCmdIsPresent() ) { DosSleep( 1000 ); break; }
    }
  }

 // ��⠥� ᯨ᮪ �ਫ������.
 Krnl_ReadRepository();

 // ����㦠�� ��⠢���騥 ����⥫�.
 Krnl_MessageBox_Start();

 #ifdef DEBUG_VERSION
 Krnl_Debug_Start();
 #endif

 Inspector_Start();
 MouseMapper_Start();
 VIOFontManager_Start();
 VIOMenuManager_Start();
 Scroller_Start();
 Roller_Start();
 Painter_Start();
 Diver_Start();
 Performer_Start();
 Remover_Start();
 PriorityManager_Start();
 Launcher_Start();
 Patcher_Start();
 RoomsTracker_Start(); Rooms_Start();
 WindowManager_Start();
 VIOMonitor_Start();
 Controller_Start();
 Definer_Start();
 MMKbdListener_Start();
 Clipper_Start();
 KeyMapper_Start();
 Clicker_Start();
 Arranger_Start();
 Changer_Start();
 Applier_Start();
 Waiter_Start();

 // ������.
 return;
}

// ��� ��⠥� ����ன�� ���

// Update_windows - ���� �� �������� �� ����.
VOID EXPENTRY Krnl_ReadSettings( BYTE Update_windows )
{
 // ���뢠�� 䠩� ����஥�.
 CHAR Settings_file_name[ SIZE_OF_PATH ] = ""; GetSettingsFileName( Settings_file_name );
 HINI Ini_file = OpenIniProfile( Enhancer.Application, Settings_file_name );

 // ��⠥� ����ன�� ��� ᯨ᪠ �ਫ������.
 Krnl_Repository_Tune( Ini_file );

 // ��⠥� ����ன�� ��⠢����� ����⥫�.
 for( INT Module_count = 0; Module_count < MODLIST_LENGTH; Module_count ++ )
  {
   PMODULE Module = GetModListEntry( Module_count );
   if( Module != NULL ) if( Module->TuneModule != NULL ) Module->TuneModule( Ini_file );
  }

 // ����塞 ����ன�� �।���� ���ᨩ.
 PrfWriteProfileData( Ini_file, "Exceptions", NULL, NULL, 0 );

 // ����뢠�� 䠩� ����஥�.
 PrfCloseProfile( Ini_file );

 // ������� ��⮪�.
 for( Module_count = 0; Module_count < MODLIST_LENGTH; Module_count ++ )
  {
   PMODULE Module = GetModListEntry( Module_count );
   if( Module != NULL ) if( Module->Required )
    if( Module->StartThread != NULL ) Module->StartThread();
  }

 // ������ ���� ࠡ�祣� �⮫�.
 HWND Desktop = QueryDesktopWindow();

 // ������ 梥� � ����ன�� OS/2, ���室�騥 ��� ����஥� ����⥫�.
 ChangeSystemColors( Desktop );
 ChangeSystemValues( Desktop, &Update_windows );

 // ����ᮢ뢠�� ࠬ�� ��� ����.
 if( Update_windows ) UpdateAllWindows( Desktop );

 // �믮��塞 �������⥫�� ����⢨� ��᫥ ᮧ����� ��⮪��.
 for( Module_count = 0; Module_count < MODLIST_LENGTH; Module_count ++ )
  {
   PMODULE Module = GetModListEntry( Module_count );
   if( Module != NULL ) if( Module->Required )
    if( Module->JumpBeforeGo != NULL ) Module->JumpBeforeGo();
  }

 // ������.
 return;
}

// ��� ����砥� ᫥����� �� ᮮ�饭�ﬨ ���

VOID EXPENTRY Krnl_HeyHoLetsGo( VOID )
{
 // ����������, �� ᫥����� �� ᮮ�饭�ﬨ ��������.
 Enhancer.Hooks_are_enabled = 1;

 // ������.
 return;
}

// ��� �����蠥� ࠡ��� ����⥫� ���

VOID EXPENTRY Krnl_ShutdownKernel( VOID )
{
 // �⪫�砥� ᫥����� �� ᮮ�饭�ﬨ.
 Enhancer.Hooks_are_enabled = 0;

 // �����蠥� ࠡ��� ��⮪�� � ��� ��⠢����� ����⥫�.
 for( INT Module_count = 0; Module_count < MODLIST_LENGTH; Module_count ++ )
  {
   PMODULE Module = GetModListEntry( Module_count );
   if( Module != NULL )
    {
     if( Module->PostQuitMsg != NULL ) Module->PostQuitMsg();
     if( Module->ShutdownAll != NULL ) Module->ShutdownAll();
    }
  }

 // ����뢠�� �� ����ࠦ����, ����㦥��� � ������.
 Resources_Stop();

 // ������ ���� ࠡ�祣� �⮫�.
 HWND Desktop = QueryDesktopWindow();

 // ����⠭�������� 梥� � ����ன�� OS/2 �� 㬮�砭��.
 RestoreSystemColors( Desktop ); RestoreSystemValues( Desktop );

 // ������塞 �� ����.
 DisableFrameDrawing(); UpdateAllWindows( Desktop, 1 );

 // ����뢠�� ����-��������.
 DestroyCurtain();

 // ����頥� ���� �����稪� �� �� � ���浪�.
 if( Krnl.RTSettings.Launcher_window != NULLHANDLE )
  if( WinIsWindow( WinQueryAnchorBlock( Krnl.RTSettings.Launcher_window ), Krnl.RTSettings.Launcher_window ) )
   WinPostMsg( Krnl.RTSettings.Launcher_window, LM_REPORT_ENHANCER_IS_TERMINATED, 0, 0 );

 // ���� VIO �த������ �ᯮ�짮���� Nice �� �� ���, ���� ��� �� ���� �������,
 // ���⮬� ����� �ਫ������ �����蠥� ᢮� ࠡ���, �� ����ன�� ���� �⪫����.
 Krnl_DisableKernelSettings();
}

// ��� ��뢠���� ����� ����⥫� �ਡ������� � WatchCat ���

VOID EXPENTRY Krnl_ApplicationIsKilled( VOID )
{
 // �⪫�砥� ᫥����� �� ᮮ�饭�ﬨ.
 Enhancer.Hooks_are_enabled = 0;

 // "��ਪ���" :-)
 DosBeep( 2000, 10 );
 DosBeep( 2500, 10 );

 // ����砥� Ctrl + Alt + Del.
 SetCtrlAltDel( 1 );

 // �⪫�砥� �� ����ன��.
 Krnl_DisableKernelSettings();

 // ������� �ਮ��� �ਫ������ - �������⭮, �� �㤥� �����.
 DosSetPriority( PRTYS_PROCESS, PRTYC_REGULAR, PRTYD_MINIMUM, 0 );

 // ������.
 return;
}

