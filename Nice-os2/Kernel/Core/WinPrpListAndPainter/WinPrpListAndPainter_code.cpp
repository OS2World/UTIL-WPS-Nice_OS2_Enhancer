
// ��� �஢����, ��� �� � ᯨ᪥ ���� �����६���� ��࠭��� ���� ���

// Frame_window - ���� ࠬ��.
VOID WinPrpListAndPainter_CheckActivityProperties (HWND Frame_window)
{
  // ��ᬠ�ਢ��� ᯨ᮪.
  for (INT Count = PrpList_GetTopItemPosition (&WinPrpList.Descendant); Count >= 0; Count --)
  {
    // �᫨ ��㣮� ���� ��⠫��� ��࠭�� - ��� ࠬ�� � ��������� ������ ���� ����ᮢ���.
    HWND Window = WinPrpList.Properties_list[Count].Frame_window;

    if (Window != Frame_window)
     if (WinPrpList.Properties_list[Count].Activated)
      if (!WindowIsActive (Window))
      {
        WinPostQueueMsg (Enhancer.Modules.Painter->Message_queue, SM_DRAW_FRAME, (MPARAM) Window, (MPARAM) WT_TITLEBAR);
        WinPrpList.Properties_list[Count].Activated = 0;
      }
  }

  // ������.
  return;
}
