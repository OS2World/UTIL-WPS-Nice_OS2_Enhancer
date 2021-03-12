
// ─── Завершение работы ───

VOID Painter_ShutdownAll (VOID)
{
  // Сбрасываем изображения для заполнения заголовка.
  Painter_DeleteTitleBarImages (); Painter_DeleteTitleBarPattern ();

  // Возврат.
  return;
}
