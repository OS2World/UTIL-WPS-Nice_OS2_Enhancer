
// ─── Восстанавливает "свернутые" окна ───

// Message - сообщение, которое передается одному из окон.
VOID Performer_RolledWindowRestoreNode (PQMSG Message)
{
  // Если есть окно, которое убрано наверх:
  if (RolledWindow () != NULLHANDLE)
  {
    // Если окно, которое было убрано наверх, изменяет размер или закрывается:
    if (Message->hwnd == RolledWindow ())
     if ((Message->msg == WM_SYSCOMMAND && Message->mp1 == (MPARAM) SC_HIDE) ||
         (Message->msg == WM_SYSCOMMAND && Message->mp1 == (MPARAM) SC_RESTORE) ||
         (FrameWindowIsClosing (Message)))
     {
       // Возвращаем его в обычное состояние.
       Performer_UnrollWindow (Message->hwnd);
     }

    // Если нажата кнопка уменьшения - считаем, что ни одно окно не убрано наверх.
    if (Message->msg == WM_SYSCOMMAND && Message->mp1 == (MPARAM) SC_MINIMIZE)
     RememberRolledWindow (NULLHANDLE);
  }

  // Возврат.
  return;
}


// ─── Слежение за сообщениями ───

// Все переменные - внешние.
VOID PerformerInputHook (HAB Application, PQMSG Message, PBYTE Discarding)
{
  // Восстанавливаем окна при закрытии.
  Performer_RolledWindowRestoreNode (Message);

  // Возврат.
  return;
}


// ─── Слежение за сообщениями от клавиатуры ───

// Все переменные - внешние.
VOID PerformerKbdInputHook (HAB Application, PQMSG Message, PBYTE Discarding)
{
  // Восстанавливаем окна при закрытии.
  Performer_RolledWindowRestoreNode (Message);

  // Возврат.
  return;
}

