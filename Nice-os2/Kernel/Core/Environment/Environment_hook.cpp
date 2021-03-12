
// ─── Обработчик событий, вызывается оболочкой WPS при включении заставки ───

// Application определяет приложение, Lockup_frame - окно заставки.
ULONG EXPENTRY Hook_LockupHook (HAB Application, HWND Lockup_frame)
{
  // Запоминаем, что вызвана заставка.
  Krnl_Environment.RTSettings.System_is_locked = 1;
  Krnl_Environment.RTSettings.Lockup_frame = Lockup_frame;
  Krnl_Environment.RTSettings.Screen_Saver_can_be_closed = 1;

  // Возврат.
  return 0;
}

// ─── Следит за состоянием оболочки OS/2 ───

// Message - сообщение, которое передается окну рабочего стола.
VOID LockupSendMsgHook (PSMHSTRUCT Message)
{
  // Если вызвана заставка и происходит переключение в другое окно:
  if (Krnl_Environment.RTSettings.System_is_locked)
   if (Message->msg == WM_ACTIVATE) if (Message->mp1 == (MPARAM) 1)
   {
     // Если окна заставки нет или оно скрыто - заставка не вызвана.
     if (!WinIsWindow (WinQueryAnchorBlock (Krnl_Environment.RTSettings.Lockup_frame), Krnl_Environment.RTSettings.Lockup_frame) ||
         !WinIsWindowVisible (Krnl_Environment.RTSettings.Lockup_frame))
     {
       Krnl_Environment.RTSettings.System_is_locked = 0;
     }
     // Иначе - если было вызвано окно справки по F1, хранитель экрана закрывать нельзя.
     else
     {
       // Проверяем окно.
       if (FrameType (Message->hwnd) == FT_FLAT) Krnl_Environment.RTSettings.Screen_Saver_can_be_closed = 0;
     }
   }

  // Возврат.
  return;
}
