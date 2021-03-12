
// ─── Сообщает, как должен работать поток для выравнивания окон ───

BYTE Rooms_SynchronizeArrangerAndRooms (VOID)
{
  // Проверяем настройки.
  if (Rooms.Settings.Synchronize_arranger_and_rooms) return 1;

  // Возврат.
  return 0;
}
