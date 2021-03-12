
// ─── Проверяет, нет ли в списке двух одновременно выбранных окон ───

// Frame_window - окно рамки.
VOID WinPrpListAndPainter_CheckActivityProperties (HWND Frame_window)
{
  // Просматриваем список.
  for (INT Count = PrpList_GetTopItemPosition (&WinPrpList.Descendant); Count >= 0; Count --)
  {
    // Если другое окно осталось выбранным - его рамка и заголовок должны быть перерисованы.
    HWND Window = WinPrpList.Properties_list[Count].Frame_window;

    if (Window != Frame_window)
     if (WinPrpList.Properties_list[Count].Activated)
      if (!WindowIsActive (Window))
      {
        WinPostQueueMsg (Enhancer.Modules.Painter->Message_queue, SM_DRAW_FRAME, (MPARAM) Window, (MPARAM) WT_TITLEBAR);
        WinPrpList.Properties_list[Count].Activated = 0;
      }
  }

  // Возврат.
  return;
}
