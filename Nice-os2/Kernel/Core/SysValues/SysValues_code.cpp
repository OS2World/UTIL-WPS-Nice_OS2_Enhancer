
// ��� ����⠭�������� 梥� ���

// Desktop - ���� ࠡ�祣� �⮫�.
VOID SysValues_RestoreSystemColors (HWND Desktop)
{
  // �᫨ �뫨 ������ ���� 梥� - ����⠭�������� ���� ���祭��.
  BYTE Colors_were_changed = 0;

  for (INT Count = 0; Count < SYSVALUES_SYSCLRS_TO_CHANGE; Count ++)
  {
    if (SysValues.Old_colors[Count].index != 0)
    {
      Colors_were_changed = 1;
      break;
    }
  }

  if (Colors_were_changed)
  {
    // �����⠢������ ᯨ᮪. ��᫮ ���祭�� ������ ���� ��� � ��� �� ������ ���� ������.
    ULONG Empty_index = SYSCLR_TITLEBOTTOM;
    ULONG Empty_color = WinQuerySysColor (Desktop, Empty_index, 0);

    for (Count = 0; Count < SYSVALUES_SYSCLRS_TO_CHANGE; Count ++)
    {
      if (SysValues.Old_colors[Count].index == 0)
      {
        SysValues.Old_colors[Count].index = Empty_index;
        SysValues.Old_colors[Count].color = Empty_color;
      }
    }

    // ���塞 梥�.
    WinSetSysColors (Desktop, 0, LCOLF_INDRGB, 0, SYSVALUES_SYSCLRS_TO_CHANGE, (PLONG) SysValues.Old_colors);

    // ��頥� ᯨ᮪, �⮡� �� ����୮� �맮�� � ��� �� ��⠫��� �।���� ���祭��.
    for (Count = 0; Count < SYSVALUES_SYSCLRS_TO_CHANGE; Count ++)
    {
      SysValues.Old_colors[Count].index = SysValues.Old_colors[Count].color = 0;
    }
  }

  // ������.
  return;
}

// ��� ������ 梥�, ���室�騥 ��� ����஥� ����⥫� ���

// Desktop - ���� ࠡ�祣� �⮫�.
VOID SysValues_ChangeSystemColors (HWND Desktop)
{
  // ���ࠢ�塞 ������ �ᥬ ��⠢���騬 ����⥫�.
  // ��� ������� 㪠��⥫� �� ��६����� Request � �������� �� ᮤ�ন���.
  PREFERRED_SYSTEM_COLORS Request; bzero (&Request, sizeof (PREFERRED_SYSTEM_COLORS));
  Request.cb = sizeof (PREFERRED_SYSTEM_COLORS);

  for (INT Module_count = 0; Module_count < MODLIST_LENGTH; Module_count ++)
  {
    PMODULE Module = GetModListEntry (Module_count);
    if (Module != NULL) if (Module->SysColorsChangeReporter != NULL)
     Module->SysColorsChangeReporter (&Request);
  }

  // �஢��塞 梥� � �����塞 ��.
  for (INT Step = 0; Step < 2; Step ++)
  {
    // �᫨ 梥� ���� ��������, �� ��६���� 㪠��� �� �ந��襤訥 ���������.
    INT I = 0; BYTE No_reason_1 = 1; PLONG Previous_1 = &SysValues.Old_colors[I].index;

    // �᫨ ���� ������ ��� ���������� ��� ���� ᢥ⫮-��� 梥�:
    if (Request.Normalize_window_background)
    {
      // ���� ����� ���� ��������.
      No_reason_1 = 0;

      // ������ 梥� ��� ���� � �ࠢ�筨��.
      LONG New_color = WinQuerySysColor (Desktop, SYSCLR_DIALOGBACKGROUND, 0);

      INT Index = SYSCLR_WINDOW; LONG Old_color = WinQuerySysColor (Desktop, Index, 0);

      if (Old_color != New_color)
      {
        SysValues.New_colors[I].index = Index;
        SysValues.New_colors[I].color = New_color;

        if (Step == 1) if (SysValues.Old_colors[I].index == 0)
        {
          SysValues.Old_colors[I].index = Index;
          SysValues.Old_colors[I].color = Old_color;
        }
      }

      I ++; Index = SYSCLR_APPWORKSPACE; Old_color = WinQuerySysColor (Desktop, Index, 0);

      if (Old_color != New_color)
      {
        SysValues.New_colors[I].index = Index;
        SysValues.New_colors[I].color = New_color;

        if (Step == 1) if (SysValues.Old_colors[I].index == 0)
        {
          SysValues.Old_colors[I].index = Index;
          SysValues.Old_colors[I].color = Old_color;
        }
      }

      I ++; Index = SYSCLR_PAGEBACKGROUND; Old_color = WinQuerySysColor (Desktop, Index, 0);

      if (Old_color != New_color)
      {
        SysValues.New_colors[I].index = Index;
        SysValues.New_colors[I].color = New_color;

        if (Step == 1) if (SysValues.Old_colors[I].index == 0)
        {
          SysValues.Old_colors[I].index = Index;
          SysValues.Old_colors[I].color = Old_color;
        }
      }

      I ++; Index = SYSCLR_HELPBACKGROUND; Old_color = WinQuerySysColor (Desktop, Index, 0);

      if (Old_color != New_color)
      {
        SysValues.New_colors[I].index = Index;
        SysValues.New_colors[I].color = New_color;

        if (Step == 1) if (SysValues.Old_colors[I].index == 0)
        {
          SysValues.Old_colors[I].index = Index;
          SysValues.Old_colors[I].color = Old_color;
        }
      }

      I ++; Index = SYSCLR_MENU; Old_color = WinQuerySysColor (Desktop, Index, 0);

      if (Old_color != New_color)
      {
        SysValues.New_colors[I].index = Index;
        SysValues.New_colors[I].color = New_color;

        if (Step == 1) if (SysValues.Old_colors[I].index == 0)
        {
          SysValues.Old_colors[I].index = Index;
          SysValues.Old_colors[I].color = Old_color;
        }
      }
    }

    // �᫨ 梥� ���� ��������, �� ��६���� 㪠��� �� �ந��襤訥 ���������.
    I = 5; BYTE No_reason_2 = 1; PLONG Previous_2 = &SysValues.Old_colors[I].index;

    // �᫨ ���� ����� ��������� ����:
    if (Request.Hide_real_window_title.For_neon_theme)
    {
      // ���� ����� ���� ��������.
      No_reason_2 = 0;

      // ������ ⠪�� 梥�, �⮡� �����騩 ��������� �� �� �����.
      LONG New_color = WinQuerySysColor (Desktop, SYSCLR_DIALOGBACKGROUND, 0);

      INT Index = SYSCLR_ACTIVETITLE; LONG Old_color = WinQuerySysColor (Desktop, Index, 0);

      if (Old_color != New_color)
      {
        SysValues.New_colors[I].index = Index;
        SysValues.New_colors[I].color = New_color;

        if (Step == 1) if (SysValues.Old_colors[I].index == 0)
        {
          SysValues.Old_colors[I].index = Index;
          SysValues.Old_colors[I].color = Old_color;
        }
      }

      I ++; Index = SYSCLR_INACTIVETITLE; Old_color = WinQuerySysColor (Desktop, Index, 0);

      if (Old_color != New_color)
      {
        SysValues.New_colors[I].index = Index;
        SysValues.New_colors[I].color = New_color;

        if (Step == 1) if (SysValues.Old_colors[I].index == 0)
        {
          SysValues.Old_colors[I].index = Index;
          SysValues.Old_colors[I].color = Old_color;
        }
      }

      I ++; Index = SYSCLR_ACTIVETITLETEXTBGND; Old_color = WinQuerySysColor (Desktop, Index, 0);

      if (Old_color != New_color)
      {
        SysValues.New_colors[I].index = Index;
        SysValues.New_colors[I].color = New_color;

        if (Step == 1) if (SysValues.Old_colors[I].index == 0)
        {
          SysValues.Old_colors[I].index = Index;
          SysValues.Old_colors[I].color = Old_color;
        }
      }

      I ++; Index = SYSCLR_INACTIVETITLETEXTBGND; Old_color = WinQuerySysColor (Desktop, Index, 0);

      if (Old_color != New_color)
      {
        SysValues.New_colors[I].index = Index;
        SysValues.New_colors[I].color = New_color;

        if (Step == 1) if (SysValues.Old_colors[I].index == 0)
        {
          SysValues.Old_colors[I].index = Index;
          SysValues.Old_colors[I].color = Old_color;
        }
      }

      I ++; Index = SYSCLR_ACTIVETITLETEXT; Old_color = WinQuerySysColor (Desktop, Index, 0);

      if (Old_color != New_color)
      {
        SysValues.New_colors[I].index = Index;
        SysValues.New_colors[I].color = New_color;

        if (Step == 1) if (SysValues.Old_colors[I].index == 0)
        {
          SysValues.Old_colors[I].index = Index;
          SysValues.Old_colors[I].color = Old_color;
        }
      }

      I ++; Index = SYSCLR_INACTIVETITLETEXT; Old_color = WinQuerySysColor (Desktop, Index, 0);

      if (Old_color != New_color)
      {
        SysValues.New_colors[I].index = Index;
        SysValues.New_colors[I].color = New_color;

        if (Step == 1) if (SysValues.Old_colors[I].index == 0)
        {
          SysValues.Old_colors[I].index = Index;
          SysValues.Old_colors[I].color = Old_color;
        }
      }
    }

    // �᫨ 梥� ���� ��������, �� ��६���� 㪠��� �� �ந��襤訥 ���������.
    I = 11; BYTE No_reason_3 = 1; PLONG Previous_3 = &SysValues.Old_colors[I].index;

    // �᫨ ���� ����� ��������� ����:
    if (Request.Hide_real_window_title.For_grayed_theme)
    {
      // ���� ����� ���� ��������.
      No_reason_3 = 0;

      // ������ ⠪�� 梥�, �⮡� �����騩 ��������� �� �� �����.
      LONG New_color = WinQuerySysColor (Desktop, SYSCLR_ACTIVETITLE, 0);

      INT Index = SYSCLR_ACTIVETITLETEXT; LONG Old_color = WinQuerySysColor (Desktop, Index, 0);

      if (Old_color != New_color)
      {
        SysValues.New_colors[I].index = Index;
        SysValues.New_colors[I].color = New_color;

        if (Step == 1) if (SysValues.Old_colors[I].index == 0)
        {
          SysValues.Old_colors[I].index = Index;
          SysValues.Old_colors[I].color = Old_color;
        }
      }

      I ++; Index = SYSCLR_ACTIVETITLETEXTBGND; Old_color = WinQuerySysColor (Desktop, Index, 0);

      if (Old_color != New_color)
      {
        SysValues.New_colors[I].index = Index;
        SysValues.New_colors[I].color = New_color;

        if (Step == 1) if (SysValues.Old_colors[I].index == 0)
        {
          SysValues.Old_colors[I].index = Index;
          SysValues.Old_colors[I].color = Old_color;
        }
      }

      New_color = WinQuerySysColor (Desktop, SYSCLR_INACTIVETITLE, 0);

      I ++; Index = SYSCLR_INACTIVETITLETEXT; Old_color = WinQuerySysColor (Desktop, Index, 0);

      if (Old_color != New_color)
      {
        SysValues.New_colors[I].index = Index;
        SysValues.New_colors[I].color = New_color;

        if (Step == 1) if (SysValues.Old_colors[I].index == 0)
        {
          SysValues.Old_colors[I].index = Index;
          SysValues.Old_colors[I].color = Old_color;
        }
      }

      I ++; Index = SYSCLR_INACTIVETITLETEXTBGND; Old_color = WinQuerySysColor (Desktop, Index, 0);

      if (Old_color != New_color)
      {
        SysValues.New_colors[I].index = Index;
        SysValues.New_colors[I].color = New_color;

        if (Step == 1) if (SysValues.Old_colors[I].index == 0)
        {
          SysValues.Old_colors[I].index = Index;
          SysValues.Old_colors[I].color = Old_color;
        }
      }
    }

    // �᫨ 梥� ���� ��������, �� ��६���� 㪠��� �� �ந��襤訥 ���������.
    I = 15; BYTE No_reason_4 = 1; PLONG Previous_4 = &SysValues.Old_colors[I].index;

    // �᫨ ���� ��⠭����� ��� ���� ࠡ�祣� �⮫� ��� 梥�:
    if (Request.Set_black_desktop_background)
    {
      // ���� ����� ���� ��������.
      No_reason_4 = 0;

      // ������ 梥� ��� ���� ࠡ�祣� �⮫�.
      LONG New_color = MAKERGB (1, 1, 1);

      INT Index = SYSCLR_BACKGROUND; LONG Old_color = WinQuerySysColor (Desktop, Index, 0);

      if (Old_color != New_color)
      {
        SysValues.New_colors[I].index = Index;
        SysValues.New_colors[I].color = New_color;

        if (Step == 1) if (SysValues.Old_colors[I].index == 0)
        {
          SysValues.Old_colors[I].index = Index;
          SysValues.Old_colors[I].color = Old_color;
        }
      }
    }

    // �᫨ 梥� �뫨 ������ - ����⠭�������� ���� 梥� � ������ ����.
    BYTE Colors_must_be_changed = 0;

    for (INT Count = 0; Count < SYSVALUES_SYSCLRS_TO_CHANGE; Count ++)
     if (SysValues.New_colors[Count].index != 0)
     {
       Colors_must_be_changed = 1;
       break;
     }

    if (Colors_must_be_changed)
    {
      // �� ��ࢮ� 蠣� ���� ����⠭����� �।��騥 梥�.
      if (Step == 0) { SysValues_RestoreSystemColors (Desktop); continue; }

      // �� ��஬ 蠣� ���� ������ ���� 梥�.
      if (Step == 1)
      {
        // �����⠢������ ᯨ᮪. ��᫮ ���祭�� ������ ���� ��� � ��� �� ������ ���� ������.
        ULONG Empty_index = SYSCLR_TITLEBOTTOM;
        ULONG Empty_color = WinQuerySysColor (Desktop, Empty_index, 0);

        for (Count = 0; Count < SYSVALUES_SYSCLRS_TO_CHANGE; Count ++)
         if (SysValues.New_colors[Count].index == 0)
         {
           SysValues.New_colors[Count].index = Empty_index;
           SysValues.New_colors[Count].color = Empty_color;
         }

        // ���塞 梥�.
        WinSetSysColors (Desktop, 0, LCOLF_INDRGB, 0, SYSVALUES_SYSCLRS_TO_CHANGE, (PLONG) SysValues.New_colors);

        // ��頥� ᯨ᮪, �⮡� �� ����୮� �맮�� � ��� �� ��⠫��� �।���� ���祭��.
        for (Count = 0; Count < SYSVALUES_SYSCLRS_TO_CHANGE; Count ++)
         SysValues.New_colors[Count].index = SysValues.New_colors[Count].color = 0;
      }
    }
    // � �᫨ 梥� ������ �� ����:
    else
    {
      // �᫨ 梥� �� ������ ��������, �� ��� �뫨 ������ ࠭�� - ����⠭�������� ��.
      if (Step == 0)
      {
        if ((No_reason_1 && *Previous_1) ||
            (No_reason_2 && *Previous_2) ||
            (No_reason_3 && *Previous_3) ||
            (No_reason_4 && *Previous_4))
        {
          SysValues_RestoreSystemColors (Desktop);
        }
      }
    }
  }

  // ������.
  return;
}

// ��� ����⠭�������� ����ன�� OS/2 ���

// Desktop - ���� ࠡ�祣� �⮫�.
VOID SysValues_RestoreSystemValues (HWND Desktop)
{
  // �᫨ �뫨 ������ ���� ����ன�� - ����⠭�������� ���� ���祭��.
  BYTE Values_were_changed = 0;

  for (INT Count = 0; Count < SYSVALUES_SYSVALS_TO_CHANGE; Count ++)
  {
    if (SysValues.Old_values[Count].index != 0)
    {
      Values_were_changed = 1;
      break;
    }
  }

  if (Values_were_changed)
  {
    // ���塞 ����ன��.
    for (Count = 0; Count < SYSVALUES_SYSVALS_TO_CHANGE; Count ++)
     if (SysValues.Old_values[Count].index != 0)
      WinSetSysValue (Desktop, SysValues.Old_values[Count].index, SysValues.Old_values[Count].value);

    // ��頥� ᯨ᮪, �⮡� �� ����୮� �맮�� � ��� �� ��⠫��� �।���� ���祭��.
    for (Count = 0; Count < SYSVALUES_SYSVALS_TO_CHANGE; Count ++)
     SysValues.Old_values[Count].index = SysValues.Old_values[Count].value = 0;
  }

  // ������.
  return;
}

// ��� ������ ����ன�� OS/2, ���室�騥 ��� ����஥� ����⥫� ���

// Desktop - ���� ࠡ�祣� �⮫�.
VOID SysValues_ChangeSystemValues (HWND Desktop, PBYTE Update_windows)
{
  // ���ࠢ�塞 ������ �ᥬ ��⠢���騬 ����⥫�.
  // ��� ������� 㪠��⥫� �� ��६����� Request � �������� �� ᮤ�ন���.
  PREFERRED_SYSTEM_VALUES Request; bzero (&Request, sizeof (PREFERRED_SYSTEM_VALUES));
  Request.cb = sizeof (PREFERRED_SYSTEM_VALUES);

  for (INT Module_count = 0; Module_count < MODLIST_LENGTH; Module_count ++)
  {
    PMODULE Module = GetModListEntry (Module_count);
    if (Module != NULL) if (Module->SysValuesChangeReporter != NULL)
     Module->SysValuesChangeReporter (&Request);
  }

  // �஢��塞 ����ன�� � �����塞 ��.
  for (INT Step = 0; Step < 2; Step ++)
  {
    // �᫨ ����ன�� ���� ��������, �� ��६���� 㪠��� �� �ந��襤訥 ���������.
    INT I = 0; BYTE No_reason_1 = 1; PLONG Previous_1 = &SysValues.Old_values[I].index;

    // �᫨ ���� ᬥ���� ���祭�� ��� �ਭ� ࠬ�� ����:
    if (Request.Change_border_width && Request.New_border_width)
    {
      // ����ன�� ����� ���� ��������.
      No_reason_1 = 0;

      // ������ ���室���� �ਭ� ࠬ��.
      LONG New_value = Request.New_border_width;

      INT Index = SV_CXSIZEBORDER; LONG Old_value = WinQuerySysValue (Desktop, Index);

      if (Old_value != New_value)
      {
        SysValues.New_values[I].index = Index;
        SysValues.New_values[I].value = New_value;

        if (Step == 1) if (SysValues.Old_values[I].index == 0)
        {
          SysValues.Old_values[I].index = Index;
          SysValues.Old_values[I].value = Old_value;
        }

        if (Step == 1) { *Update_windows = 1; }
      }

      I ++; Index = SV_CYSIZEBORDER; Old_value = WinQuerySysValue (Desktop, Index);

      if (Old_value != New_value)
      {
        SysValues.New_values[I].index = Index;
        SysValues.New_values[I].value = New_value;

        if (Step == 1) if (SysValues.Old_values[I].index == 0)
        {
          SysValues.Old_values[I].index = Index;
          SysValues.Old_values[I].value = Old_value;
        }

        if (Step == 1) { *Update_windows = 1; }
      }
    }

    // �᫨ ����ன�� ���� ��������, �� ��६���� 㪠��� �� �ந��襤訥 ���������.
    I = 2; BYTE No_reason_2 = 1; PLONG Previous_2 = &SysValues.Old_values[I].index;

    // �᫨ ���� �⪫���� ����⢨� PrintScreen:
    if (Request.Disable_PrintScreen)
    {
      // ����ன�� ����� ���� ��������.
      No_reason_2 = 0;

      // �⪫�砥� ����� �࠭�.
      LONG New_value = 0;

      INT Index = SV_PRINTSCREEN; LONG Old_value = WinQuerySysValue (Desktop, Index);

      if (Old_value != New_value)
      {
        SysValues.New_values[I].index = Index;
        SysValues.New_values[I].value = New_value;

        if (Step == 1) if (SysValues.Old_values[I].index == 0)
        {
          SysValues.Old_values[I].index = Index;
          SysValues.Old_values[I].value = Old_value;
        }
      }
    }

    // �᫨ ����ன�� ���� ��������, �� ��६���� 㪠��� �� �ந��襤訥 ���������.
    I = 3; BYTE No_reason_3 = 1; PLONG Previous_3 = &SysValues.Old_values[I].index;

    // �᫨ ���� �⪫���� ����⢨� ����� � ����� VIO:
    if (Request.Disable_VIO_mouse_actions)
    {
      // ����ன�� ����� ���� ��������.
      No_reason_3 = 0;

      // �⪫�砥� ����⢨� ��� ���.
      LONG New_value = 0;

      INT Index = SV_VIOMOUSEACTIONS; LONG Old_value = WinQuerySysValue (Desktop, Index);

      if (Old_value != New_value)
      {
        SysValues.New_values[I].index = Index;
        SysValues.New_values[I].value = New_value;

        if (Step == 1) if (SysValues.Old_values[I].index == 0)
        {
          SysValues.Old_values[I].index = Index;
          SysValues.Old_values[I].value = Old_value;
        }
      }
    }

    // �᫨ ����ன�� �뫨 ������ - ����⠭�������� ���� ���祭�� � ������ ����.
    BYTE Values_must_be_changed = 0;

    for (INT Count = 0; Count < SYSVALUES_SYSVALS_TO_CHANGE; Count ++)
     if (SysValues.New_values[Count].index != 0)
     {
       Values_must_be_changed = 1;
       break;
     }

    if (Values_must_be_changed)
    {
      // �� ��ࢮ� 蠣� ���� ����⠭����� �।��騥 ����ன��.
      if (Step == 0)
      {
        SysValues_RestoreSystemValues (Desktop);
        continue;
      }

      // �� ��஬ 蠣� ���� ������ ���� ����ன��.
      if (Step == 1)
      {
        // ���塞 ����ன��.
        for (Count = 0; Count < SYSVALUES_SYSVALS_TO_CHANGE; Count ++)
         if (SysValues.New_values[Count].index != 0)
          WinSetSysValue (Desktop, SysValues.New_values[Count].index, SysValues.New_values[Count].value);

        // ��頥� ᯨ᮪, �⮡� �� ����୮� �맮�� � ��� �� ��⠫��� �।���� ���祭��.
        for (Count = 0; Count < SYSVALUES_SYSVALS_TO_CHANGE; Count ++)
         SysValues.New_values[Count].index = SysValues.New_values[Count].value = 0;
      }
    }
    // �᫨ ����ன�� ������ �� ����:
    else
    {
      // �᫨ ����ன�� �� ������ ��������, �� ��� �뫨 ������ ࠭�� - ����⠭�������� ��.
      if (Step == 0)
      {
        if ((No_reason_1 && *Previous_1) ||
            (No_reason_2 && *Previous_2) ||
            (No_reason_3 && *Previous_3))
        {
          SysValues_RestoreSystemValues (Desktop);
        }
      }
    }
  }

  // ������.
  return;
}

