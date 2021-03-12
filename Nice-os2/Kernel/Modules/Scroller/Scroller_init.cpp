
// ─── Устанавливает настройки по умолчанию ───

// Division - какие настройки надо установить.
VOID Scroller_SetPreDefinedSettings (LONG Division)
{
  // Задаем настройки.
  if (Division == SET_ALL_SETTINGS)
  {
    bzero (&Scroller.Settings.Exceptions, sizeof (SCROLLER_EXCEPTIONS));
  }

  if (Division == SET_ALL_SETTINGS || Division == SET_SCROLLING)
  {
    Scroller.Settings.Key_scrolling = 1;
    Scroller.Settings.Smooth_scrolling = 1;
    Scroller.Settings.Image_dragging = SCROLLER_USE_SHIFT;
    Scroller.Settings.Number_of_pointer = SCROLLER_CAT_POINTER;
  }

  // Возврат.
  return;
}

// ─── Читает настройки ───

// Ini_file - файл настроек.
VOID Scroller_ReadSettings (HINI Ini_file)
{
  // Читаем настройки.
  ULONG Byte = 0; ULONG Int = 0; ULONG Name = 0; ULONG Byte_data = 0; ULONG Int_data = 0;

  Byte = sizeof (BYTE); if (PrfQueryProfileData (Ini_file, "Settings", "Key scrolling", &Byte_data, &Byte)) Scroller.Settings.Key_scrolling = Byte_data;
  Byte = sizeof (BYTE); if (PrfQueryProfileData (Ini_file, "Settings", "Smooth scrolling", &Byte_data, &Byte)) Scroller.Settings.Smooth_scrolling = Byte_data;
  Byte = sizeof (BYTE); if (PrfQueryProfileData (Ini_file, "Settings", "Image dragging", &Byte_data, &Byte)) Scroller.Settings.Image_dragging = Byte_data;
  Int  = sizeof (INT);  if (PrfQueryProfileData (Ini_file, "Settings", "Number of pointer", &Int_data, &Int)) Scroller.Settings.Number_of_pointer = Int_data;

  // Читаем список исключений.
  {
    CHAR Item[SIZE_OF_NAME] = "";

    Name = SIZE_OF_NAME; PrfQueryProfileData (Ini_file, "ExceptionList", "Scrolling 1", Item, &Name); strcpy (Scroller.Settings.Exceptions.Scrolling_1, Item); Item[0] = 0;
    Name = SIZE_OF_NAME; PrfQueryProfileData (Ini_file, "ExceptionList", "Scrolling 2", Item, &Name); strcpy (Scroller.Settings.Exceptions.Scrolling_2, Item); Item[0] = 0;
    Name = SIZE_OF_NAME; PrfQueryProfileData (Ini_file, "ExceptionList", "Scrolling 3", Item, &Name); strcpy (Scroller.Settings.Exceptions.Scrolling_3, Item); Item[0] = 0;
    Name = SIZE_OF_NAME; PrfQueryProfileData (Ini_file, "ExceptionList", "Scrolling 4", Item, &Name); strcpy (Scroller.Settings.Exceptions.Scrolling_4, Item); Item[0] = 0;
    Name = SIZE_OF_NAME; PrfQueryProfileData (Ini_file, "ExceptionList", "Scrolling 5", Item, &Name); strcpy (Scroller.Settings.Exceptions.Scrolling_5, Item); Item[0] = 0;
    Name = SIZE_OF_NAME; PrfQueryProfileData (Ini_file, "ExceptionList", "Scrolling 6", Item, &Name); strcpy (Scroller.Settings.Exceptions.Scrolling_6, Item); Item[0] = 0;
    Name = SIZE_OF_NAME; PrfQueryProfileData (Ini_file, "ExceptionList", "Scrolling 7", Item, &Name); strcpy (Scroller.Settings.Exceptions.Scrolling_7, Item); Item[0] = 0;
    Name = SIZE_OF_NAME; PrfQueryProfileData (Ini_file, "ExceptionList", "Scrolling 8", Item, &Name); strcpy (Scroller.Settings.Exceptions.Scrolling_8, Item); Item[0] = 0;

    Name = SIZE_OF_NAME; PrfQueryProfileData (Ini_file, "ExceptionList", "KeyScrolling 1", Item, &Name); strcpy (Scroller.Settings.Exceptions.KeyScrolling_1, Item); Item[0] = 0;
    Name = SIZE_OF_NAME; PrfQueryProfileData (Ini_file, "ExceptionList", "KeyScrolling 2", Item, &Name); strcpy (Scroller.Settings.Exceptions.KeyScrolling_2, Item); Item[0] = 0;
    Name = SIZE_OF_NAME; PrfQueryProfileData (Ini_file, "ExceptionList", "KeyScrolling 3", Item, &Name); strcpy (Scroller.Settings.Exceptions.KeyScrolling_3, Item); Item[0] = 0;
    Name = SIZE_OF_NAME; PrfQueryProfileData (Ini_file, "ExceptionList", "KeyScrolling 4", Item, &Name); strcpy (Scroller.Settings.Exceptions.KeyScrolling_4, Item); Item[0] = 0;
    Name = SIZE_OF_NAME; PrfQueryProfileData (Ini_file, "ExceptionList", "KeyScrolling 5", Item, &Name); strcpy (Scroller.Settings.Exceptions.KeyScrolling_5, Item); Item[0] = 0;
    Name = SIZE_OF_NAME; PrfQueryProfileData (Ini_file, "ExceptionList", "KeyScrolling 6", Item, &Name); strcpy (Scroller.Settings.Exceptions.KeyScrolling_6, Item); Item[0] = 0;
    Name = SIZE_OF_NAME; PrfQueryProfileData (Ini_file, "ExceptionList", "KeyScrolling 7", Item, &Name); strcpy (Scroller.Settings.Exceptions.KeyScrolling_7, Item); Item[0] = 0;
    Name = SIZE_OF_NAME; PrfQueryProfileData (Ini_file, "ExceptionList", "KeyScrolling 8", Item, &Name); strcpy (Scroller.Settings.Exceptions.KeyScrolling_8, Item); Item[0] = 0;
  }

  // Возврат.
  return;
}

// ─── Читает настройки для передвижения изображения ───

VOID Scroller_ReadScrList (HINI Ini_file)
{
  // Читаем настройки.
  for (INT Count = 0; Count < SCROLLER_SCRLIST_SIZE; Count ++)
  {
    CHAR Number[25] = ""; itoa (Count, Number, 10); CHAR Setting_name[50] = "";

    strcpy (Setting_name, Number); strcat (Setting_name, " N");
    ULONG Name = SIZE_OF_NAME; CHAR Item[SIZE_OF_NAME] = "";
    PrfQueryProfileData (Ini_file, "Scrolling", Setting_name, Item, &Name);

    if (Item[0] != 0)
    {
      strcpy (Scroller.Scrolling_list[Count].Name, Item);
      Scroller.Scrolling_list[Count].PreDefined = 0;
      Scroller.Scrolling_list[Count].Method = SCROLLING_COMMON;

      strcpy (Setting_name, Number); strcat (Setting_name, " X DD");
      ULONG Int = sizeof (INT); ULONG Int_data = 0;
      PrfQueryProfileData (Ini_file, "Scrolling", Setting_name, &Int_data, &Int);
      Scroller.Scrolling_list[Count].X_Velocity_DD = Int_data;

      strcpy (Setting_name, Number); strcat (Setting_name, " X D");
      Int = sizeof (INT); Int_data = 0;
      PrfQueryProfileData (Ini_file, "Scrolling", Setting_name, &Int_data, &Int);
      Scroller.Scrolling_list[Count].X_Velocity_D = Int_data;

      strcpy (Setting_name, Number); strcat (Setting_name, " Y DD");
      Int = sizeof (INT); Int_data = 0;
      PrfQueryProfileData (Ini_file, "Scrolling", Setting_name, &Int_data, &Int);
      Scroller.Scrolling_list[Count].Y_Velocity_DD = Int_data;

      strcpy (Setting_name, Number); strcat (Setting_name, " Y D");
      Int = sizeof (INT); Int_data = 0;
      PrfQueryProfileData (Ini_file, "Scrolling", Setting_name, &Int_data, &Int);
      Scroller.Scrolling_list[Count].Y_Velocity_D = Int_data;
    }
  }

  // Возврат.
  return;
}
