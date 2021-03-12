
// ─── Выполняет действие ───

VOID DialogWindow_HelpButton (HWND Window, ULONG Message, MPARAM First_parameter, MPARAM Second_parameter, ULONG WM_Control_Window_ID = 0)
{
  // Делаем выбранной кнопку "Старт/Стоп".
  WinSetFocus (HWND_DESKTOP, WinWindowFromID (Window, ID_MAINWNDFORM_START_BUTTON));

  // Задаем название раздела.
  CHAR Topic_name[SIZE_OF_NAME] = "";

  if (Names.Settings.Code_page == RUSSIAN) strcpy (Topic_name, StrConst_RU_Help_caption);
  else strcpy (Topic_name, StrConst_EN_Help_caption);

  CHAR Chapter[SIZE_OF_PATH] = ""; GetCurrentPath (Chapter);
  strcat (Chapter, "\\Names.inf "); strcat (Chapter, Topic_name);

  // Вызываем справочник.
  Execute (Names.Help.Viewer, Chapter);

  // Возврат.
  return;
}

