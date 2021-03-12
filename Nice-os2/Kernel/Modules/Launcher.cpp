// Методы для выполнения различных действий.
#define HideShellToolbarMenu        Launcher_HideShellToolbarMenu

// ─── Метод для подключения класса ───

VOID Launcher_Start (VOID)
{
  #ifdef Launcher
  bzero (&Launcher, sizeof (Launcher));
  #endif

  // Задаем указатели в списке составляющих расширителя.
  MODULE Item; PresetModuleItem (&Item);

  Item.StartThread = Launcher_StartThread;
  Item.PostQuitMsg = Launcher_PostQuitMsg;
  Item.TuneModule  = Launcher_Tune;

  RememberModuleItem (Enhancer.Modules.Launcher, &Item);

  // Возврат.
  return;
}

