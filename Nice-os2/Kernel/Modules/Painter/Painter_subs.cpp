
// ��� ��⠭�������� ����� ��ࠡ��稪 ᮮ�饭�� ��� ���� ���

// Frame_window - ���� ࠬ��, Window - ����, ��ࠡ��稪 ��� ���ண� �� �������, Window_type - ����� �� ����.
VOID Painter_DetachWindow (HWND Frame_window, HWND Window, LONG Window_type)
{
  // ��室�� � ᯨ᪥ ᢮��� ���� �।��騩 ��ࠡ��稪.
  LONG Property = PRP_TITLEBAR_PERF;
  if (Window_type == WT_MINMAX)   Property = PRP_MINMAX_PERF;
  if (Window_type == WT_MENU)     Property = PRP_MENU_PERF;

  PFNWP Previous_performer = NULL; FindProperty (Frame_window, Property, &Previous_performer);

  // �᫨ �� �� �������:
  if (Previous_performer != NULL )
  {
    // �����頥� ��� ���⭮.
    WinSubclassWindow (Window, Previous_performer);

    // ����ᨬ � ᯨ᮪ ���⮥ ���祭��.
    PFNWP Empty_value = NULL; SetProperty (Frame_window, Property, &Empty_value);
  }

  // ������.
  return;
}

// ��� ��뢠�� ����� ��ࠡ��稪 ᮮ�饭�� ���

// �� ��६���� - ���譨�.
MRESULT EXPENTRY Painter_CallMessageProcessor (HWND Window, ULONG Message, MPARAM First_parameter, MPARAM Second_parameter, PFNWP Hook)
{
  // ��뢠�� ��ࠡ��稪 ᮮ�饭��.
  PFNWP Performer = (PFNWP) WinQueryWindowPtr (Window, QWP_PFNWP);

  if (Performer != Hook) return Performer (Window, Message, First_parameter, Second_parameter);

  // �᫨ �� ᤥ���� �� 㤠���� - ��뢠�� ��ࠡ��稪 �� 㬮�砭��.
  CHAR Window_name[SIZE_OF_NAME] = ""; WinQueryClassName (Window, SIZE_OF_NAME, Window_name);
  CLASSINFO Properties = {0}; WinQueryClassInfo (ActiveApplication (), Window_name, &Properties);

  return Properties.pfnWindowProc (Window, Message, First_parameter, Second_parameter);
}

// ��� ��ࠡ��稪 ᮮ�饭�� ��� ���� ����� ���� ࠬ�� ���

// �� ��६���� - ���譨�.
MRESULT EXPENTRY Painter_WindowHookMessageProcessing (HWND Window, ULONG Message, MPARAM First_parameter, MPARAM Second_parameter, LONG Window_type, PFNWP Hook)
{
  // ������ ���� ࠬ��.
  HWND Frame_window = QueryFrameWindow (Window);

  // ��⠭�������� ��� ���� �।��騩 ��ࠡ��稪 ᮮ�饭��.
  Painter_DetachWindow (Frame_window, Window, Window_type);

  // �᫨ ���� ������ ���� ����ᮢ���:
  if (Message == WM_PAINT)
  {
    // ������ �����頥��� ���祭��.
    MRESULT Report = 0;

    // �᫨ �� ���� ����:
    if (Window_type == WT_MENU)
    {
      // ��뢠�� ����� ��ࠡ��稪 ᮮ�饭��.
      Report = Painter_CallMessageProcessor (Window, Message, First_parameter, Second_parameter, Hook);
    }
    // � �᫨ �� ���� ��������� ��� ������:
    else
    {
      // ���� ��祣� �� ����.
      RECT Rectangle = {0};
      HPS Presentation_space = WinBeginPaint (Window, NULLHANDLE, &Rectangle);
      WinEndPaint (Presentation_space);
    }

    // ���뫠�� ᮮ�饭�� � ��⮪ �ᮢ����.
    if (Window_type != WT_MINMAX) WinPostQueueMsg (Enhancer.Modules.Painter->Message_queue, SM_DRAW_FRAME, (MPARAM) Frame_window, (MPARAM) Window_type);

    // ������.
    return Report;
  }

  // �᫨ ���� ��������� �⠭������ ��࠭��:
  if (Window_type == WT_TITLEBAR && Message == TBM_SETHILITE)
  {
    // ���뫠�� ᮮ�饭�� � ��⮪ �ᮢ����.
    WinPostQueueMsg (Enhancer.Modules.Painter->Message_queue, SM_DRAW_FRAME, (MPARAM) Frame_window, (MPARAM) WT_TITLEBAR);

    // ������.
    return (MRESULT) 1;
  }

  // ��뢠�� ����� ��ࠡ��稪 ᮮ�饭��.
  return Painter_CallMessageProcessor (Window, Message, First_parameter, Second_parameter, Hook);
}

// ��� ��ࠡ��稪 ᮮ�饭�� ��� ���� ��������� ���

// ��⮪ �ਫ������ ��뢠�� TitleBar_performer ��直� ࠧ, ����� ��� ���� ���� ᮮ�饭��.

// Window - ����, Message - ᮮ�饭��, *_parameter - �����, ����� ��।����� ����� � ᮮ�饭���.
MRESULT EXPENTRY Painter_TitleBarWindowHook (HWND Window, ULONG Message, MPARAM First_parameter, MPARAM Second_parameter)
{
  // ��ࠡ��뢠�� ᮮ�饭��.
  return Painter_WindowHookMessageProcessing (Window, Message, First_parameter, Second_parameter, WT_TITLEBAR, (PFNWP) Painter_TitleBarWindowHook);
}

// ��� ��ࠡ��稪 ᮮ�饭�� ��� ���� ������ ������ ���

// ��⮪ �ਫ������ ��뢠�� MinMax_performer ��直� ࠧ, ����� ��� ���� ���� ᮮ�饭��.

// Window ����, Message - ᮮ�饭��, *_parameter - �����, ����� ��।����� ����� � ᮮ�饭���.
MRESULT EXPENTRY Painter_MinMaxWindowHook (HWND Window, ULONG Message, MPARAM First_parameter, MPARAM Second_parameter)
{
  // ��ࠡ��뢠�� ᮮ�饭��.
  return Painter_WindowHookMessageProcessing (Window, Message, First_parameter, Second_parameter, WT_MINMAX, (PFNWP) Painter_MinMaxWindowHook);
}

// ��� ��ࠡ��稪 ᮮ�饭�� ��� ���� ���� ���

// ��⮪ �ਫ������ ��뢠�� Menu_performer ��直� ࠧ, ����� ��� ���� ���� ᮮ�饭��.

// Window - ����, Message - ᮮ�饭��, *_parameter - �����, ����� ��।����� ����� � ᮮ�饭���.
MRESULT EXPENTRY Painter_MenuWindowHook (HWND Window, ULONG Message, MPARAM First_parameter, MPARAM Second_parameter)
{
  // ��ࠡ��뢠�� ᮮ�饭��.
  return Painter_WindowHookMessageProcessing (Window, Message, First_parameter, Second_parameter, WT_MENU, (PFNWP) Painter_MenuWindowHook);
}

// ��� ������ ��� ���� ���� ��ࠡ��稪 ᮮ�饭�� ���

// Frame_window - ���� ࠬ��, Window - ����, ��� ���ண� ���� �������� ��ࠡ��稪 ᮮ�饭��, Target - ����� �� ����.
VOID Painter_SubClassWindow (HWND Frame_window, HWND Window, ULONG Target)
{
  // �롨ࠥ� ��ࠡ��稪 ᮮ�饭��.
  PFNWP New_performer = NULL; LONG Property = 0;

  if (Target == WT_TITLEBAR) { New_performer = (PFNWP) Painter_TitleBarWindowHook; Property = PRP_TITLEBAR_PERF; }
  if (Target == WT_MINMAX)   { New_performer = (PFNWP) Painter_MinMaxWindowHook;   Property = PRP_MINMAX_PERF;   }
  if (Target == WT_MENU)     { New_performer = (PFNWP) Painter_MenuWindowHook;     Property = PRP_MENU_PERF;     }

  // ������ ���� ��ࠡ��稪. ������ �� �㤥� ������� ᮮ�饭��, ��室�騥 ����.
  PFNWP Current_performer = WinSubclassWindow (Window, New_performer);

  // ���������� �।��騩 ��ࠡ��稪 � ᯨ᪥ ᢮��� ����.
  if (Current_performer != NULL) SetProperty (Frame_window, Property, &Current_performer);

  // ������.
  return;
}

