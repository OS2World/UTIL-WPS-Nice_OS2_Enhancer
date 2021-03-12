
// ─── Выполняет действия после чтения настроек и создания потока ───

VOID Remover_Jump (VOID)
{
  // Скрываем или показываем строки в списке окон.
  if (Remover.Settings.Remove_items_from_Window_list) Remover_ShowAllItemsInSwitchList (0, Remover.Settings.Hide_known_applications);
  else Remover_ShowAllItemsInSwitchList (1);

  // Возврат.
  return;
}