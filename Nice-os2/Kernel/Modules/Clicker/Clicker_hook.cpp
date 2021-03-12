
// ─── Слежение за сообщениями ───

// Все переменные - внешние.
VOID ClickerKbdInputHook (HAB Application, PQMSG Message, PBYTE Discarding)
{
  // Звук при нажатии на клавишу.
  BYTE Message_will_be_discarded = *Discarding;

  if (Clicker.Settings.Keyboard_echo) if (!Message_will_be_discarded)
   if (Message->msg == WM_CHAR) if (Clicker_PermissionForClicking (Message))
    WinPostQueueMsg (Enhancer.Modules.Clicker->Message_queue, SM_CLICK, 0, 0);

  // Возврат.
  return;
}
