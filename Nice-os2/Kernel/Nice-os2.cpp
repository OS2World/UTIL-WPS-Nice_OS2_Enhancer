// Постоянные величины.
#include "..\\Shared\\General.h"
#include "..\\Shared\\AbstractClass\\AbstractClass_code.cpp"

// Вызовы C/C++.
#include "..\\Shared\\StdLib\\StdLib_code.cpp"
#include "..\\Shared\\StdLib.cpp"

// Работа со строками.
#include "..\\Shared\\Strings.h"
#include "..\\Shared\\Strings\\Strings_data.cpp"
#include "..\\Shared\\Strings\\Strings_code.cpp"
#include "..\\Shared\\Strings.cpp"

// Дополнительные вызовы OS/2.
#include "..\\Shared\\SysState.h"

// Список известных расширителю окон и приложений.
#include "..\\Shared\\Repository.h"

// Внешние сообщения.
#include "..\\Shared\\Messages4Daemon.h"

// Ответы от потоков приложения.
#include "Core\\ThreadResponds.h"

// Работа с файлами и PIPE-соединениями.
#include "..\\Shared\\Pipes\\Pipes_code.cpp"
#include "..\\Shared\\Pipes.cpp"

#include "..\\Shared\\Files\\Files_code.cpp"
#include "..\\Shared\\Files.cpp"

// Отладка приложения.
#include "Core\\Debug\\Debug_code.cpp"
#include "Core\\Debug.cpp"

// Приложение и список его составляющих.
typedef VOID ( MODPROC_STARTTHREAD ) ( VOID );
typedef VOID ( MODPROC_POSTQUITMSG ) ( VOID );
typedef VOID ( MODPROC_SHUTDOWNALL ) ( VOID );

typedef VOID ( MODPROC_TUNEMODULE    ) ( HINI );
typedef VOID ( MODPROC_JUMPBEFOREGO  ) ( VOID );

typedef VOID ( MODPROC_COLORSREPORTER ) ( PVOID );
typedef VOID ( MODPROC_VALUESREPORTER ) ( PVOID );

typedef struct _MODULE
 {
  // Длина структуры.
  ULONG cb;

  // Поток.
  TID Thread; LONG Priority;
  // Этот поток действительно нужен.
  BYTE Required;
  // Очередь сообщений потока.
  HMQ Message_queue;

  // Указатели на вызовы.
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
  // Уже подключенные составляющие. Каждый указатель будет указывать на одну
  // запись массива ModList, эти значения проставляются при вызове "StartKernel".
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

  // Составляющие "на будущее". Для них указатели тоже задаются.
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
  // Приложение.
  HAB Application; HMODULE Module;

  // Слежение за сообщениями включено.
  BYTE Hooks_are_enabled;

  // Составляющие приложения.
  MODULE ModList[ MODLIST_LENGTH ]; MODULE_POINTERS Modules;
 }
ENHANCER; ENHANCER Enhancer;

// Перебор составляющих приложения.
#include "Core\\ModList\\ModList_code.cpp"
#include "Core\\ModList.cpp"

// Переменные и свойства окружения.
#include "..\\Shared\\Environment\\Environment_data.cpp"
#include "..\\Shared\\Environment\\Environment_code.cpp"
#include "..\\Shared\\Environment.cpp"

#include "..\\Shared\\EnhancerProperties\\EnhancerProperties_code.cpp"
#include "..\\Shared\\EnhancerProperties.cpp"

// Размер стека для потоков.
#define THREAD_STACK_SIZE 32768

// Настройки.
#include "..\\Shared\\Settings.h"

// Значки и изображения.
#include "Resources\\Resources_data.cpp"
#include "Resources\\Resources_stop.cpp"

// Сообщения для потоков.
#include "Modules\\Messages.h"

// Распознавание окон и приложений.
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

// Распознавание предопределенных свойств окон
#include "Core\\PMMetrics\\PMMetrics_code.cpp"
#include "Core\\PMMetrics.cpp"

#include "Core\\Workplace\\Workplace_data.cpp"
#include "Core\\Workplace\\Workplace_code.cpp"
#include "Core\\Workplace.cpp"

// Переменные и свойства окружения.
#include "Core\\Environment\\Environment_data.cpp"
#include "Core\\Environment\\Environment_hook.cpp"
#include "Core\\Environment\\Environment_code.cpp"
#include "Core\\Environment.cpp"

// Поиск окон.
#include "..\\Shared\\Searcher.h"
#include "..\\Shared\\Searcher\\Searcher_code.cpp"
#include "..\\Shared\\Searcher.cpp"

// Проверка списка известных приложений и значков для них.
#include "Core\\RepositoryChecker\\RepositoryChecker_code.cpp"
#include "Core\\RepositoryChecker.cpp"

// Значения для потоков.
#include "Modules\\Constants.h"

// Список свойств окон.
#include "..\\Shared\\AbstractPrpList\\AbstractPrpList_data.cpp"
#include "..\\Shared\\AbstractPrpList\\AbstractPrpList_code.cpp"

#include "Core\\WinPrpList.h"
#include "Core\\WinPrpList\\WinPrpList_data.cpp"
#include "Core\\WinPrpList\\WinPrpList_code.cpp"
#include "Core\\WinPrpList.cpp"

// Работа с клавиатурой и мышью.
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

// Рисование.
#include "..\\Shared\\GpiExt\\GpiExt_code.cpp"
#include "..\\Shared\\GpiExt.cpp"

// Работа с изображениями.
#include "..\\Shared\\Images\\Images_code.cpp"
#include "..\\Shared\\Images.cpp"

// Работа со списком окон.
#include "..\\Shared\\WindowList\\WindowList_code.cpp"
#include "..\\Shared\\WindowList.cpp"

#include "Core\\WindowList\\WindowList_code.cpp"
#include "Core\\WindowList.cpp"

// Методы для проверки отслеживаемых сообщений.
#include "Core\\HookEvents\\HookEvents_code.cpp"
#include "Core\\HookEvents.cpp"

// Работа с меню.
#include "..\\Shared\\MenuItems\\MenuItems_data.cpp"
#include "..\\Shared\\MenuItems\\MenuItems_code.cpp"
#include "..\\Shared\\MenuItems.cpp"

// Работа с окнами.
#include "..\\Shared\\WindowManagement\\WindowManagement_code.cpp"
#include "..\\Shared\\WindowManagement.cpp"

#include "Core\\WinPrpListAndRepository\\WinPrpListAndRepository_base.cpp"
#include "Core\\WinPrpListAndRepository\\WinPrpListAndRepository_hook.cpp"
#include "Core\\WinPrpListAndRepository\\WinPrpListAndRepository_code.cpp"
#include "Core\\WinPrpListAndRepository.cpp"

#include "Core\\WinPrpListAndPainter\\WinPrpListAndPainter_code.cpp"
#include "Core\\WinPrpListAndPainter.cpp"

// Работа с окнами для открытия и сохранения файлов.
#include "Core\\FileDialogs\\FileDialogs_code.cpp"
#include "Core\\FileDialogs.cpp"

// Работа с окнами диалогов.
#include "..\\Shared\\DlgBoxes.h"
#include "Core\\DlgBox.h"
#include "Core\\DlgBox\\DlgBox_data.cpp"
#include "Core\\DlgBox\\DlgBox_code.cpp"
#include "Core\\DlgBox.cpp"

// Работа с окном обмена.
#include "..\\Shared\\Clipboard\\Clipboard_code.cpp"
#include "..\\Shared\\Clipboard.cpp"

// Методы для отслеживания комнат.
#include "Modules\\RoomsTracker\\RoomsTracker_data.cpp"
#include "Modules\\RoomsTracker\\RoomsTracker_code.cpp"
#include "Modules\\RoomsTracker.cpp"

// Окно-занавеска, которое ничего не рисует.
#include "Core\\Curtain\\Curtain_data.cpp"
#include "Core\\Curtain\\Curtain_code.cpp"
#include "Core\\Curtain\\Curtain_link.cpp"
#include "Core\\Curtain.cpp"

// Обновление окон.
#include "Core\\Repaint\\Repaint_code.cpp"
#include "Core\\Repaint.cpp"

// Сообщения, которые расширитель посылает приложениям.
#include "Hooks\\HookMessages.h"

// Подстановка состояния клавиатуры на уровне V-Keys.
#include "Core\\KbdState\\KbdState_data.cpp"
#include "Core\\KbdState\\KbdState_base.cpp"
#include "Core\\KbdState\\KbdState_hook.cpp"
#include "Core\\KbdState.cpp"

// Задание приоритетов приложений.
#include "Core\\Priority\\Priority_hook.cpp"
#include "Core\\Priority\\Priority_code.cpp"
#include "Core\\Priority.cpp"

// Прерывание приложений с использованием возможностей оболочки OS/2.
#include "Core\\TerminateProcess\\TerminateProcess_hook.cpp"
#include "Core\\TerminateProcess\\TerminateProcess_code.cpp"
#include "Core\\TerminateProcess.cpp"

// Изменение настроек и цветов оболочки OS/2.
#include "Core\\SysValues\\SysValues_data.cpp"
#include "Core\\SysValues\\SysValues_code.cpp"
#include "Core\\SysValues.cpp"

// Составляющие расширителя.
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

// Обработчики событий.
#include "Hooks\\HookMethods.cpp"

// Окна сообщений.
#include "Core\\MessageBox\\MessageBox_code.cpp"
#include "Core\\MessageBox.cpp"

// Настройки приложения.
typedef struct _ENHANCER_KRNL
 {
  // Внутренние переменные.
  typedef struct _RTSTS
   {
    // Видно ли окно расширителя.
    BYTE Nice_is_visible;
    // Окно загрузчика.
    HWND Launcher_window;
   }
  RTSTS; RTSTS RTSettings;
 }
ENHANCER_KRNL;

ENHANCER_KRNL Krnl;

// ─── Отключает все настройки ───

VOID Krnl_DisableKernelSettings( VOID )
{
 // Сбрасываем все переменные, отключаем слежение за сообщениями.
 // Окна VIO продолжают использовать Nice-os2.dll, поэтому и очереди потоков надо сделать равными NULLHANDLE.
 bzero( &Enhancer, sizeof( ENHANCER ) );
 bzero( &Krnl, sizeof( ENHANCER_KRNL ) );

 // Возврат.
 return;
}

// ─── Читает список приложений ───

VOID EXPENTRY Krnl_ReadRepository( VOID )
{
 // Открываем файл настроек.
 CHAR Settings_file_name[ SIZE_OF_PATH ] = ""; GetSettingsFileName( Settings_file_name );
 HINI Ini_file = OpenIniProfile( Enhancer.Application, Settings_file_name );

 // Читаем список приложений.
 ReadRepository( Ini_file );

 // Закрываем файл настроек.
 PrfCloseProfile( Ini_file );

 // Возврат.
 return;
}

// ─── Настраиваем расширитель перед созданием потоков ───

// Все переменные - внешние.
VOID EXPENTRY Krnl_StartKernel( HAB Application, HMODULE Module, BYTE Nice_is_visible, HWND Launcher_window )
{
 // Подключаем служебные методы.
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

 // Сбрасываем все настройки, если они могли остаться от предыдущих запусков.
 Krnl_DisableKernelSettings();

 // Запоминаем приложение.
 Enhancer.Application = Application;
 Enhancer.Module = Module;

 // Запоминаем, видно ли окно расширителя.
 Krnl.RTSettings.Nice_is_visible = Nice_is_visible;

 // Запоминаем окно загрузчика.
 Krnl.RTSettings.Launcher_window = Launcher_window;

 // Устанавливаем указатели в списке составляющих расширителя.
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

 // Отключаем сообщения об ошибках.
 DosError( FERR_DISABLEHARDERR | FERR_DISABLEEXCEPTION );
 DosSuppressPopUps( SUPPRESS_POPUPS, 0 );
 DosDumpProcess( 0, 0, 0 );

 // Узнаем окно рабочего стола.
 HWND Desktop = QueryDesktopWindow();

 // Задаем настройки оконной оболочки.
 WinSetSysValue( Desktop, SV_CXBYTEALIGN, 0 );
 WinSetSysValue( Desktop, SV_CYBYTEALIGN, 0 );
 WinSetSysValue( Desktop, SV_CXALIGN, 0 );
 WinSetSysValue( Desktop, SV_CYALIGN, 0 );

 // Включаем правильную обработку сообщений.
 WinSetSysValue( Desktop, SV_ASYNCFOCUSCHANGE, 1 );
 WinSetSysValue( Desktop, SV_FOCUSCHANGESENS, 5 );

 // Переключаем хранитель экрана в режим "Screen Saver mode".
 ULONG Screen_saver_mode = 1; PrfWriteProfileData( HINI_USERPROFILE, "PM_Lockup", "LockupScreenSaverMode", &Screen_saver_mode, sizeof( ULONG ) );

 // Если оболочка WPS отсутствует - проверяем, был ли Nice вызван в Startup.cmd.
 if( !ShellIsWPS() ) if( StartupCmdIsPresent() )
  {
   // Ждем некоторое время.
   for( INT Count = 0; Count < 100; Count ++ )
    {
     // Выполняем задержку в 1/10 секунды.
     DosSleep( 100 );

     // Если оболочка загружена - прекращаем ожидание.
     if( ShellIsWPS() ) break;

     // Если окно Startup.cmd исчезло - ждем еще 1 секунду и прекращаем ожидание.
     if( !StartupCmdIsPresent() ) { DosSleep( 1000 ); break; }
    }
  }

 // Читаем список приложений.
 Krnl_ReadRepository();

 // Загружаем составляющие расширителя.
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

 // Возврат.
 return;
}

// ─── Читает настройки ───

// Update_windows - надо ли обновить все окна.
VOID EXPENTRY Krnl_ReadSettings( BYTE Update_windows )
{
 // Открываем файл настроек.
 CHAR Settings_file_name[ SIZE_OF_PATH ] = ""; GetSettingsFileName( Settings_file_name );
 HINI Ini_file = OpenIniProfile( Enhancer.Application, Settings_file_name );

 // Читаем настройки для списка приложений.
 Krnl_Repository_Tune( Ini_file );

 // Читаем настройки составляющих расширителя.
 for( INT Module_count = 0; Module_count < MODLIST_LENGTH; Module_count ++ )
  {
   PMODULE Module = GetModListEntry( Module_count );
   if( Module != NULL ) if( Module->TuneModule != NULL ) Module->TuneModule( Ini_file );
  }

 // Удаляем настройки предыдущих версий.
 PrfWriteProfileData( Ini_file, "Exceptions", NULL, NULL, 0 );

 // Закрываем файл настроек.
 PrfCloseProfile( Ini_file );

 // Создаем потоки.
 for( Module_count = 0; Module_count < MODLIST_LENGTH; Module_count ++ )
  {
   PMODULE Module = GetModListEntry( Module_count );
   if( Module != NULL ) if( Module->Required )
    if( Module->StartThread != NULL ) Module->StartThread();
  }

 // Узнаем окно рабочего стола.
 HWND Desktop = QueryDesktopWindow();

 // Задаем цвета и настройки OS/2, подходящие для настроек расширителя.
 ChangeSystemColors( Desktop );
 ChangeSystemValues( Desktop, &Update_windows );

 // Перерисовываем рамки всех окон.
 if( Update_windows ) UpdateAllWindows( Desktop );

 // Выполняем дополнительные действия после создания потоков.
 for( Module_count = 0; Module_count < MODLIST_LENGTH; Module_count ++ )
  {
   PMODULE Module = GetModListEntry( Module_count );
   if( Module != NULL ) if( Module->Required )
    if( Module->JumpBeforeGo != NULL ) Module->JumpBeforeGo();
  }

 // Возврат.
 return;
}

// ─── Включает слежение за сообщениями ───

VOID EXPENTRY Krnl_HeyHoLetsGo( VOID )
{
 // Запоминаем, что слежение за сообщениями возможно.
 Enhancer.Hooks_are_enabled = 1;

 // Возврат.
 return;
}

// ─── Завершает работу расширителя ───

VOID EXPENTRY Krnl_ShutdownKernel( VOID )
{
 // Отключаем слежение за сообщениями.
 Enhancer.Hooks_are_enabled = 0;

 // Завершаем работу потоков и всех составляющих расширителя.
 for( INT Module_count = 0; Module_count < MODLIST_LENGTH; Module_count ++ )
  {
   PMODULE Module = GetModListEntry( Module_count );
   if( Module != NULL )
    {
     if( Module->PostQuitMsg != NULL ) Module->PostQuitMsg();
     if( Module->ShutdownAll != NULL ) Module->ShutdownAll();
    }
  }

 // Сбрасываем все изображения, загруженные в память.
 Resources_Stop();

 // Узнаем окно рабочего стола.
 HWND Desktop = QueryDesktopWindow();

 // Восстанавливаем цвета и настройки OS/2 по умолчанию.
 RestoreSystemColors( Desktop ); RestoreSystemValues( Desktop );

 // Обновляем все окна.
 DisableFrameDrawing(); UpdateAllWindows( Desktop, 1 );

 // Закрываем окно-занавеску.
 DestroyCurtain();

 // Сообщаем окну загрузчика что все в порядке.
 if( Krnl.RTSettings.Launcher_window != NULLHANDLE )
  if( WinIsWindow( WinQueryAnchorBlock( Krnl.RTSettings.Launcher_window ), Krnl.RTSettings.Launcher_window ) )
   WinPostMsg( Krnl.RTSettings.Launcher_window, LM_REPORT_ENHANCER_IS_TERMINATED, 0, 0 );

 // Окна VIO продолжают использовать Nice до тех пор, пока они не будут закрыты,
 // поэтому когда приложение завершает свою работу, все настройки надо отключить.
 Krnl_DisableKernelSettings();
}

// ─── Вызывается когда расширитель прибивается в WatchCat ───

VOID EXPENTRY Krnl_ApplicationIsKilled( VOID )
{
 // Отключаем слежение за сообщениями.
 Enhancer.Hooks_are_enabled = 0;

 // "Чирикаем" :-)
 DosBeep( 2000, 10 );
 DosBeep( 2500, 10 );

 // Включаем Ctrl + Alt + Del.
 SetCtrlAltDel( 1 );

 // Отключаем все настройки.
 Krnl_DisableKernelSettings();

 // Снижаем приоритет приложения - неизвестно, что будет дальше.
 DosSetPriority( PRTYS_PROCESS, PRTYC_REGULAR, PRTYD_MINIMUM, 0 );

 // Возврат.
 return;
}

