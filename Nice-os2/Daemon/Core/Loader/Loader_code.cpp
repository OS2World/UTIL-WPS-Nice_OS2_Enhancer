
// ─── Вызывается при завершении приложения ───

VOID APIENTRY Loader_ExitListHook (ULONG Termination_code)
{
  // Вызываем Nice-os2.dll с сообщением о завершении приложения.
  if (Loader.Dll_calls.ApplicationIsKilled) Loader.Dll_calls.ApplicationIsKilled ();

  // Выход.
  DosExit (EXIT_PROCESS, 0);
}

// ─── Создает потоки, устанавливает обработчики событий ───

// Application определяет приложение. Возвращает 1 или 0.
BYTE Loader_NiceLoadEnhancer (HAB Application, BYTE Nice_is_visible, HWND Launcher_window)
{
  // Узнаем каталог, в котором работает приложение.
  CHAR Path_to_module[SIZE_OF_PATH] = ""; GetCurrentPath (Path_to_module);

  // Добавляем его в список каталогов "LIBPATH".
  DosSetExtLIBPATH (Path_to_module, BEGIN_LIBPATH);

  // Задаем полный путь к Nice-os2.dll.
  if (strlen (Path_to_module) > 3) strcat (Path_to_module, "\\");
  strcat (Path_to_module, "Nice-os2.dll");

  // Загружаем Nice-os2.dll и подключаем вызовы.
  if (DosLoadModule (NULL, 0, Path_to_module, &Loader.Dll_calls.Module) != NO_ERROR) return 0;

  DosQueryProcAddr (Loader.Dll_calls.Module, 0, "Krnl_StartKernel", (PFN*) &Loader.Dll_calls.StartKernel);
  DosQueryProcAddr (Loader.Dll_calls.Module, 0, "Krnl_HeyHoLetsGo", (PFN*) &Loader.Dll_calls.HeyHoLetsGo);
  DosQueryProcAddr (Loader.Dll_calls.Module, 0, "Krnl_ShutdownKernel", (PFN*) &Loader.Dll_calls.ShutdownKernel);
  DosQueryProcAddr (Loader.Dll_calls.Module, 0, "Krnl_ApplicationIsKilled", (PFN*) &Loader.Dll_calls.ApplicationIsKilled);

  DosQueryProcAddr (Loader.Dll_calls.Module, 0, "Krnl_ReadSettings", (PFN*) &Loader.Dll_calls.ReadSettings);
  DosQueryProcAddr (Loader.Dll_calls.Module, 0, "Krnl_ReadRepository", (PFN*) &Loader.Dll_calls.ReadRepository);

  DosQueryProcAddr (Loader.Dll_calls.Module, 0, "Hook_InputHook", (PFN*) &Loader.Dll_calls.InputHook);
  DosQueryProcAddr (Loader.Dll_calls.Module, 0, "Hook_KbdInputHook", (PFN*) &Loader.Dll_calls.KbdInputHook);
  DosQueryProcAddr (Loader.Dll_calls.Module, 0, "Hook_SendMsgHook", (PFN*) &Loader.Dll_calls.SendMsgHook);
  DosQueryProcAddr (Loader.Dll_calls.Module, 0, "Hook_LockupHook", (PFN*) &Loader.Dll_calls.LockupHook);

  DosQueryProcAddr (Loader.Dll_calls.Module, 0, "Applier_ScanMessageDialog", (PFN*) &Loader.Dll_calls.ScanMessageDialog);
  DosQueryProcAddr (Loader.Dll_calls.Module, 0, "Applier_ScanIncompleteDialog", (PFN*) &Loader.Dll_calls.ScanIncompleteDialog);
  DosQueryProcAddr (Loader.Dll_calls.Module, 0, "Applier_ScanLogonDialog", (PFN*) &Loader.Dll_calls.ScanLogonDialog);

  // Если не все методы для запуска расширителя были загружены - возврат.
  if (!Loader.Dll_calls.StartKernel || !Loader.Dll_calls.HeyHoLetsGo) return 0;

  // Включаем расширитель.
  Loader.Dll_calls.StartKernel (Application, Loader.Dll_calls.Module, Nice_is_visible, Launcher_window);
  Loader.Dll_calls.StartKernel = NULL;

  // Устанавливаем обработчики событий. Они будут действовать для всех очередей сообщений,
  // и для всех окон. Также можно ставить свой обработчик для каждой очереди, и если вдруг
  // в OS/2 будет устроена какая-нибудь "защита" как в Windows NT, то можно так и поступить.
  if (Loader.Dll_calls.InputHook)
  {
    Loader.Hooks.InputHook_type = HK_INPUT;
    WinSetHook (Application, ALL_QUEUES, Loader.Hooks.InputHook_type, (PFN) Loader.Dll_calls.InputHook, Loader.Dll_calls.Module);
  }

  if (Loader.Dll_calls.KbdInputHook)
  {
    Loader.Hooks.KbdInputHook_type = HK_PREACCEL;
    WinSetHook (Application, ALL_QUEUES, Loader.Hooks.KbdInputHook_type, (PFN) Loader.Dll_calls.KbdInputHook, Loader.Dll_calls.Module);
  }

  if (Loader.Dll_calls.SendMsgHook)
  {
    Loader.Hooks.SendMsgHook_type = HK_SENDMSG;
    WinSetHook (Application, ALL_QUEUES, Loader.Hooks.SendMsgHook_type, (PFN) Loader.Dll_calls.SendMsgHook, Loader.Dll_calls.Module);
  }

  if (Loader.Dll_calls.LockupHook)
  {
    Loader.Hooks.LockupHook_type = HK_LOCKUP;
    WinSetHook (Application, ALL_QUEUES, Loader.Hooks.LockupHook_type, (PFN) Loader.Dll_calls.LockupHook, Loader.Dll_calls.Module);
  }

  // Устанавливаем обработчик исключений, который должен вызываться в случае,
  // если расширитель прибивают в WatchCat или с помощью внешней команды "Kill".
  DosExitList (EXLST_ADD, Loader_ExitListHook);

  // Возврат.
  return 1;
}


// ─── Включает слежение за сообщениями ───

VOID Loader_NiceRunEnhancer (VOID)
{
  // Включаем слежение за сообщениями.
  if (Loader.Dll_calls.HeyHoLetsGo)
  {
    Loader.Dll_calls.HeyHoLetsGo ();
    Loader.Dll_calls.HeyHoLetsGo = NULL;
  }

  // Возврат.
  return;
}

// ─── Читает настройки ───

// Вызывается при изменении настроек пользователем.
// Update_windows - надо ли обновить все окна.
VOID Loader_NiceReadSettings (BYTE Update_windows = 0, BYTE Arrange_windows = 0)
{
  // Читаем настройки, которые содержатся в Nice-OS2.ini.
  if (Loader.Dll_calls.ReadSettings) Loader.Dll_calls.ReadSettings (Update_windows, Arrange_windows);

  // Возврат.
  return;
}

// ─── Читает список приложений ───

// Вызывается при изменении списка приложений.
VOID Loader_NiceReadRepository (VOID)
{
  // Читаем настройки, которые содержатся в Nice-OS2.ini.
  if (Loader.Dll_calls.ReadRepository) Loader.Dll_calls.ReadRepository ();

  // Возврат.
  return;
}

// ─── Собирает сведения об окне ввода пароля ───

// Window - окно ввода пароля.
VOID Loader_NiceScanLogonDialog (HWND Window)
{
  // Узнаем сведения об окне.
  if (Loader.Dll_calls.ScanLogonDialog) Loader.Dll_calls.ScanLogonDialog (Window);

  // Возврат.
  return;
}

// ─── Собирает сведения об окне диалога ───

// Window - окно диалога.
VOID Loader_NiceScanIncompleteDialog (HWND Window)
{
  // Узнаем сведения об окне.
  if (Loader.Dll_calls.ScanIncompleteDialog) Loader.Dll_calls.ScanIncompleteDialog (Window);

  // Возврат.
  return;
}

// ─── Собирает сведения об окне сообщения ───

// Window - окно сообщения.
VOID Loader_NiceScanMessageDialog (HWND Window)
{
  // Узнаем сведения об окне.
  if (Loader.Dll_calls.ScanMessageDialog) Loader.Dll_calls.ScanMessageDialog (Window);

  // Возврат.
  return;
}

// ─── Отключает обработчики событий, завершает работу потоков ───

// Application определяет приложение, Nice_is_visible - доступно ли окно Nice пользователю.
VOID Loader_NiceReleaseEnhancer (HAB Application, BYTE Nice_is_visible)
{
  // Отключаем обработчик исключений.
  DosExitList (EXLST_REMOVE, Loader_ExitListHook);

  // Отключаем обработчики событий.
  if (Loader.Hooks.InputHook_type) WinReleaseHook (Application, ALL_QUEUES, Loader.Hooks.InputHook_type, (PFN) Loader.Dll_calls.KbdInputHook, Loader.Dll_calls.Module);
  if (Loader.Hooks.KbdInputHook_type) WinReleaseHook (Application, ALL_QUEUES, Loader.Hooks.KbdInputHook_type, (PFN) Loader.Dll_calls.InputHook, Loader.Dll_calls.Module);
  if (Loader.Hooks.SendMsgHook_type) WinReleaseHook (Application, ALL_QUEUES, Loader.Hooks.SendMsgHook_type, (PFN) Loader.Dll_calls.SendMsgHook, Loader.Dll_calls.Module);
  if (Loader.Hooks.LockupHook_type) WinReleaseHook (Application, ALL_QUEUES, Loader.Hooks.LockupHook_type, (PFN) Loader.Dll_calls.LockupHook, Loader.Dll_calls.Module);

  // Завершаем работу потоков внутри расширителя.
  if (Loader.Dll_calls.ShutdownKernel)
  {
    Loader.Dll_calls.ShutdownKernel (Nice_is_visible);
    Loader.Dll_calls.ShutdownKernel = NULL;
  }

  // Сбрасываем все внутренние переменные и указатели на вызовы.
  bzero (&Loader, sizeof (LOADER));

  // Здесь надо отключить Nice-os2.dll... но в некоторых случаях это вызывает ошибку.
  // Вероятно, DLL расширителя отключается самой оболочкой.
  /* DosFreeModule (Loader.Dll_calls.Module); */

  // Возврат.
  return;
}

