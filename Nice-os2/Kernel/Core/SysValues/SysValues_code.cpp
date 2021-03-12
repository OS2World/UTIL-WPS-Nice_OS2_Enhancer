
// ─── Восстанавливает цвета ───

// Desktop - окно рабочего стола.
VOID SysValues_RestoreSystemColors (HWND Desktop)
{
  // Если были заданы новые цвета - восстанавливаем старые значения.
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
    // Подготавливаем список. Число значений должно быть четным и они все должны быть заданы.
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

    // Меняем цвета.
    WinSetSysColors (Desktop, 0, LCOLF_INDRGB, 0, SYSVALUES_SYSCLRS_TO_CHANGE, (PLONG) SysValues.Old_colors);

    // Очищаем список, чтобы при повторном вызове в нем не осталось предыдущих значений.
    for (Count = 0; Count < SYSVALUES_SYSCLRS_TO_CHANGE; Count ++)
    {
      SysValues.Old_colors[Count].index = SysValues.Old_colors[Count].color = 0;
    }
  }

  // Возврат.
  return;
}

// ─── Задает цвета, подходящие для настроек расширителя ───

// Desktop - окно рабочего стола.
VOID SysValues_ChangeSystemColors (HWND Desktop)
{
  // Направляем запросы всем составляющим расширителя.
  // Они получают указатель на переменную Request и изменяют ее содержимое.
  PREFERRED_SYSTEM_COLORS Request; bzero (&Request, sizeof (PREFERRED_SYSTEM_COLORS));
  Request.cb = sizeof (PREFERRED_SYSTEM_COLORS);

  for (INT Module_count = 0; Module_count < MODLIST_LENGTH; Module_count ++)
  {
    PMODULE Module = GetModListEntry (Module_count);
    if (Module != NULL) if (Module->SysColorsChangeReporter != NULL)
     Module->SysColorsChangeReporter (&Request);
  }

  // Проверяем цвета и заменяем их.
  for (INT Step = 0; Step < 2; Step ++)
  {
    // Если цвета будут изменены, эти переменные укажут на произошедшие изменения.
    INT I = 0; BYTE No_reason_1 = 1; PLONG Previous_1 = &SysValues.Old_colors[I].index;

    // Если надо задать для заполнения всех окон светло-серый цвет:
    if (Request.Normalize_window_background)
    {
      // Цвета могут быть изменены.
      No_reason_1 = 0;

      // Задаем цвета для окон и справочника.
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

    // Если цвета будут изменены, эти переменные укажут на произошедшие изменения.
    I = 5; BYTE No_reason_2 = 1; PLONG Previous_2 = &SysValues.Old_colors[I].index;

    // Если надо скрыть заголовки окон:
    if (Request.Hide_real_window_title.For_neon_theme)
    {
      // Цвета могут быть изменены.
      No_reason_2 = 0;

      // Задаем такие цвета, чтобы настоящий заголовок не был виден.
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

    // Если цвета будут изменены, эти переменные укажут на произошедшие изменения.
    I = 11; BYTE No_reason_3 = 1; PLONG Previous_3 = &SysValues.Old_colors[I].index;

    // Если надо скрыть заголовки окон:
    if (Request.Hide_real_window_title.For_grayed_theme)
    {
      // Цвета могут быть изменены.
      No_reason_3 = 0;

      // Задаем такие цвета, чтобы настоящий заголовок не был виден.
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

    // Если цвета будут изменены, эти переменные укажут на произошедшие изменения.
    I = 15; BYTE No_reason_4 = 1; PLONG Previous_4 = &SysValues.Old_colors[I].index;

    // Если надо установить для окна рабочего стола черный цвет:
    if (Request.Set_black_desktop_background)
    {
      // Цвета могут быть изменены.
      No_reason_4 = 0;

      // Задаем цвет для окна рабочего стола.
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

    // Если цвета были заданы - восстанавливаем старые цвета и задаем новые.
    BYTE Colors_must_be_changed = 0;

    for (INT Count = 0; Count < SYSVALUES_SYSCLRS_TO_CHANGE; Count ++)
     if (SysValues.New_colors[Count].index != 0)
     {
       Colors_must_be_changed = 1;
       break;
     }

    if (Colors_must_be_changed)
    {
      // На первом шаге надо восстановить предыдущие цвета.
      if (Step == 0) { SysValues_RestoreSystemColors (Desktop); continue; }

      // На втором шаге надо задать новые цвета.
      if (Step == 1)
      {
        // Подготавливаем список. Число значений должно быть четным и они все должны быть заданы.
        ULONG Empty_index = SYSCLR_TITLEBOTTOM;
        ULONG Empty_color = WinQuerySysColor (Desktop, Empty_index, 0);

        for (Count = 0; Count < SYSVALUES_SYSCLRS_TO_CHANGE; Count ++)
         if (SysValues.New_colors[Count].index == 0)
         {
           SysValues.New_colors[Count].index = Empty_index;
           SysValues.New_colors[Count].color = Empty_color;
         }

        // Меняем цвета.
        WinSetSysColors (Desktop, 0, LCOLF_INDRGB, 0, SYSVALUES_SYSCLRS_TO_CHANGE, (PLONG) SysValues.New_colors);

        // Очищаем список, чтобы при повторном вызове в нем не осталось предыдущих значений.
        for (Count = 0; Count < SYSVALUES_SYSCLRS_TO_CHANGE; Count ++)
         SysValues.New_colors[Count].index = SysValues.New_colors[Count].color = 0;
      }
    }
    // А если цвета менять не надо:
    else
    {
      // Если цвета не должны меняться, но они были заданы раньше - восстанавливаем их.
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

  // Возврат.
  return;
}

// ─── Восстанавливает настройки OS/2 ───

// Desktop - окно рабочего стола.
VOID SysValues_RestoreSystemValues (HWND Desktop)
{
  // Если были заданы новые настройки - восстанавливаем старые значения.
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
    // Меняем настройки.
    for (Count = 0; Count < SYSVALUES_SYSVALS_TO_CHANGE; Count ++)
     if (SysValues.Old_values[Count].index != 0)
      WinSetSysValue (Desktop, SysValues.Old_values[Count].index, SysValues.Old_values[Count].value);

    // Очищаем список, чтобы при повторном вызове в нем не осталось предыдущих значений.
    for (Count = 0; Count < SYSVALUES_SYSVALS_TO_CHANGE; Count ++)
     SysValues.Old_values[Count].index = SysValues.Old_values[Count].value = 0;
  }

  // Возврат.
  return;
}

// ─── Задает настройки OS/2, подходящие для настроек расширителя ───

// Desktop - окно рабочего стола.
VOID SysValues_ChangeSystemValues (HWND Desktop, PBYTE Update_windows)
{
  // Направляем запросы всем составляющим расширителя.
  // Они получают указатель на переменную Request и изменяют ее содержимое.
  PREFERRED_SYSTEM_VALUES Request; bzero (&Request, sizeof (PREFERRED_SYSTEM_VALUES));
  Request.cb = sizeof (PREFERRED_SYSTEM_VALUES);

  for (INT Module_count = 0; Module_count < MODLIST_LENGTH; Module_count ++)
  {
    PMODULE Module = GetModListEntry (Module_count);
    if (Module != NULL) if (Module->SysValuesChangeReporter != NULL)
     Module->SysValuesChangeReporter (&Request);
  }

  // Проверяем настройки и заменяем их.
  for (INT Step = 0; Step < 2; Step ++)
  {
    // Если настройки будут изменены, эти переменные укажут на произошедшие изменения.
    INT I = 0; BYTE No_reason_1 = 1; PLONG Previous_1 = &SysValues.Old_values[I].index;

    // Если надо сменить значение для ширины рамки окна:
    if (Request.Change_border_width && Request.New_border_width)
    {
      // Настройки могут быть изменены.
      No_reason_1 = 0;

      // Задаем подходяшую ширину рамки.
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

    // Если настройки будут изменены, эти переменные укажут на произошедшие изменения.
    I = 2; BYTE No_reason_2 = 1; PLONG Previous_2 = &SysValues.Old_values[I].index;

    // Если надо отключить действие PrintScreen:
    if (Request.Disable_PrintScreen)
    {
      // Настройки могут быть изменены.
      No_reason_2 = 0;

      // Отключаем печать экрана.
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

    // Если настройки будут изменены, эти переменные укажут на произошедшие изменения.
    I = 3; BYTE No_reason_3 = 1; PLONG Previous_3 = &SysValues.Old_values[I].index;

    // Если надо отключить действия мышью в окнах VIO:
    if (Request.Disable_VIO_mouse_actions)
    {
      // Настройки могут быть изменены.
      No_reason_3 = 0;

      // Отключаем действия для мыши.
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

    // Если настройки были заданы - восстанавливаем старые значения и задаем новые.
    BYTE Values_must_be_changed = 0;

    for (INT Count = 0; Count < SYSVALUES_SYSVALS_TO_CHANGE; Count ++)
     if (SysValues.New_values[Count].index != 0)
     {
       Values_must_be_changed = 1;
       break;
     }

    if (Values_must_be_changed)
    {
      // На первом шаге надо восстановить предыдущие настройки.
      if (Step == 0)
      {
        SysValues_RestoreSystemValues (Desktop);
        continue;
      }

      // На втором шаге надо задать новые настройки.
      if (Step == 1)
      {
        // Меняем настройки.
        for (Count = 0; Count < SYSVALUES_SYSVALS_TO_CHANGE; Count ++)
         if (SysValues.New_values[Count].index != 0)
          WinSetSysValue (Desktop, SysValues.New_values[Count].index, SysValues.New_values[Count].value);

        // Очищаем список, чтобы при повторном вызове в нем не осталось предыдущих значений.
        for (Count = 0; Count < SYSVALUES_SYSVALS_TO_CHANGE; Count ++)
         SysValues.New_values[Count].index = SysValues.New_values[Count].value = 0;
      }
    }
    // Если настройки менять не надо:
    else
    {
      // Если настройки не должны меняться, но они были заданы раньше - восстанавливаем их.
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

  // Возврат.
  return;
}

