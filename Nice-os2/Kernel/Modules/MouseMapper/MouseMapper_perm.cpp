
// ─── Проверяет, можно ли переключать ввод от клавиатуры в окне ───

// Frame_window - окно рамки, в котором надо осуществить переключение ввода от клавиатуры.
BYTE MouseMapper_PermissionForInputFocusMoving (HWND Frame_window)
{
  // В некоторых окнах переключать ввод не надо.
  if (WindowIsCreatedBy (APP_PMDIFF, Frame_window)) return 0;

  // Возврат.
  return 1;
}

