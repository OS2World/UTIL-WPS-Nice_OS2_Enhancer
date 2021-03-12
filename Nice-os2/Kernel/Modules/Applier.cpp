// Методы для выполнения действия с окнами диалогов.
#define MakeLogonWindowTitle   Applier_MakeLogonWindowTitle

// ─── Метод для подключения класса ───

VOID Applier_Start (VOID)
{
  #ifdef Applier
  bzero (&Applier, sizeof (Applier));
  #endif

  // Задаем указатели в списке составляющих расширителя.
  MODULE Item; PresetModuleItem (&Item);

  Item.StartThread  = Applier_StartThread;
  Item.PostQuitMsg  = Applier_PostQuitMsg;
  Item.TuneModule   = Applier_Tune;
  Item.JumpBeforeGo = Applier_Jump;

  RememberModuleItem (Enhancer.Modules.Applier, &Item);

  // Возврат.
  return;
}

