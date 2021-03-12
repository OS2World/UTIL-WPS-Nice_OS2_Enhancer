
// ��� ��⠥� ����ன�� ���

// Ini_file - 䠩� ����஥�.
VOID Scroller_Tune (HINI Ini_file)
{
  // ��⠥� ����ன��.
  Scroller_SetPreDefinedSettings (SET_ALL_SETTINGS);
  Scroller_ReadSettings (Ini_file);

  // �᫨ ����祭� ��।������� ����ࠦ����:
  if (Scroller.Settings.Key_scrolling || Scroller.Settings.Image_dragging)
  {
    // ��⠥� ����� ���� ��� ��।������� ����ࠦ����.
    Scroller_ReadScrList (Ini_file);
    Scroller_CompleteScrList ();

    // ����㦠�� 㪠��⥫�.
    if (Resources.Pointer_for_dragging != NULLHANDLE) 
    { 
      WinDestroyPointer (Resources.Pointer_for_dragging); Resources.Pointer_for_dragging = NULLHANDLE; 
    }

    if (Scroller.Settings.Number_of_pointer) 
    {
      Resources.Pointer_for_dragging = WinLoadPointer (QueryDesktopWindow (), Enhancer.Module, Scroller.Settings.Number_of_pointer);
    }
  }

  // ����������, �� ��⮪ ������ ���� ᮧ���.
  if (Scroller.Settings.Key_scrolling || Scroller.Settings.Image_dragging) Enhancer.Modules.Scroller->Required = 1;

  // ������.
  return;
}
