
// ─── Выполняет действия после чтения настроек и создания потока ───

VOID Applier_Jump (VOID)
{
  // Находим диалоговые окна, известные расширителю.
  WinPostQueueMsg (Enhancer.Modules.Applier->Message_queue, SM_FIND_DIALOG_WINDOWS, 0, 0);

  // Возврат.
  return;
}