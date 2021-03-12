// ���� � ᮮ�饭�ﬨ �� �訡���.
#define LogWindow       Log_LogWindow
#define LogIsEmpty      Log_LogIsEmpty
#define PrintLogMessage Log_PrintLogMessage

// ��� ��⮤ ��� ������祭�� ����� ���

VOID Log_Start (LONG Settings_division = SET_ALL_SETTINGS)
{
  #ifdef Log
  bzero (&Log, sizeof (Log));
  #endif

  // ������ ��࠭�, � ���ன ࠡ�⠥� �ਫ������.
  LONG Code_page = Enhancer.Code_page;

  {
    // ������ 㪠��⥫� � ᯨ᪥ ��⠢����� ����⥫�.
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

    // ������ ID ����� �����.
    Log.Settings.Field_ID = 1000;
  }

  // ������.
  return;
}

