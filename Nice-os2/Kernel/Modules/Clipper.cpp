// Методы для выделения строк в окнах.
#define PermissionForMarking               Clipper_PermissionForMarking
#define CopyPasteKeysCanBeUsedInVIOWindows Clipper_CopyPasteKeysCanBeUsedInVIOWindows

// ─── Метод для подключения класса ───

VOID Clipper_Start (VOID)
{
  #ifdef Clipper
  bzero (&Clipper, sizeof (Clipper));
  #endif

  // Задаем указатели в списке составляющих расширителя.
  MODULE Item; PresetModuleItem (&Item);

  Item.StartThread = Clipper_StartThread;
  Item.PostQuitMsg = Clipper_PostQuitMsg;
  Item.TuneModule  = Clipper_Tune;
  Item.SysValuesChangeReporter = Clipper_SysValuesChangeReporter;

  RememberModuleItem (Enhancer.Modules.Clipper, &Item);

  // Возврат.
  return;
}

