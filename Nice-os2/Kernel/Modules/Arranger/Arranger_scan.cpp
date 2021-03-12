
// ��� ��ࠢ������ ������� ���� ���

// Desktop - ���� ࠡ�祣� �⮫�.
VOID ArrangeSomeWindows (HWND Desktop)
{
  // ��ॡ�ࠥ� ���� � ���� ࠡ�祣� �⮫�.
  HENUM Enumeration = WinBeginEnumWindows (Desktop); HWND Window = NULLHANDLE;
  while ((Window = WinGetNextWindow (Enumeration)) != NULLHANDLE)
  {
    // ������� ���� ���� ��ࠢ������ �� ����᪥ ����⥫�.
    if (Arranger.Settings.Arrange_Network_windows)
     if (IsSafeFireWindow (Window)) if (WindowIsCreatedBy (APP_SAFEFIRE, Window))
     {
       // ���뫠�� ᮮ�饭�� � ��⮪.
       WinPostQueueMsg (Enhancer.Modules.Arranger->Message_queue, SM_ARRANGE_NW_DIALER, (MPARAM) Window, 0);
     }

    if (Arranger.Settings.Arrange_XWP_windows)
     if (IsXWPPagerWindow (Window))
     {
       // ���뫠�� ᮮ�饭�� � ��⮪.
       WinPostQueueMsg (Enhancer.Modules.Arranger->Message_queue, SM_ARRANGE_XWP_PAGER, (MPARAM) Window, 0);
     }
  }
  WinEndEnumWindows (Enumeration);

  // ������.
  return;
}