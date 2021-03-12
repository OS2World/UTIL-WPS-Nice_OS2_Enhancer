// Окно с сообщениями об ошибках.
#define LogWindow       Log_LogWindow
#define LogIsEmpty      Log_LogIsEmpty
#define PrintLogMessage Log_PrintLogMessage

// ─── Метод для подключения класса ───

VOID Log_Start (LONG Settings_division = SET_ALL_SETTINGS)
{
  #ifdef Log
  bzero (&Log, sizeof (Log));
  #endif

  // Узнаем страну, в которой работает приложение.
  LONG Code_page = Enhancer.Code_page;

  {
    // Задаем указатели в списке составляющих расширителя.
    {
      PAGE Item; PresetPageItem (&Item);

      if (Code_page == RUSSIAN) strcpy (Item.Name, StrConst_RU_Pages_Log_Name);
      else strcpy (Item.Name, StrConst_EN_Pages_Log_Name);

      strcpy (Item.Icon_name, "Log_page.ico");

      Item.CreatePage     = Log_CreatePage;
      Item.SetDefSettings = Log_DoNothing;
      Item.ReadSettings   = Log_DoNothing;

      RememberPageItem (Enhancer.Pages.Log, &Item);
    }

    // Задаем ID полей ввода.
    Log.Settings.Field_ID = 1000;
  }

  // Возврат.
  return;
}

