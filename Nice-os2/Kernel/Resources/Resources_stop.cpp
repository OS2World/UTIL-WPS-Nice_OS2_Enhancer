
// ��� �����襭�� ࠡ��� ���

VOID Resources_Stop (VOID)
{
  // ����뢠�� �� ����ࠦ����, ����㦥��� � ������.
  if (Resources.Pointer_for_dragging != NULLHANDLE) WinDestroyPointer (Resources.Pointer_for_dragging);
  if (Resources.Pointer_for_CopyPaste != NULLHANDLE) WinDestroyPointer (Resources.Pointer_for_CopyPaste);

  for (INT Count = 0; Count < RC_ICONS_QUANTITY; Count ++)
   if (Resources.Default_icons[Count] != NULLHANDLE) WinDestroyPointer (Resources.Default_icons[Count]);

  // ������.
  return;
}

