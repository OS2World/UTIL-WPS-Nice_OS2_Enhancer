// ─── Создает пространство отображения ───

HPS Images_CreatePresentationSpace (HAB Application)
{
  // Создаем пространство отображения.
  DEVOPENSTRUC Display = {0}; Display.pszDriverName = "Display";
  SIZEL Size = {0}; HDC Device = NULLHANDLE; HPS Space = NULLHANDLE;

  Device = DevOpenDC (Application, OD_MEMORY, "*", 0, (PDEVOPENDATA) &Display, NULLHANDLE);

  if (Device != NULLHANDLE)
  {
    Space = GpiCreatePS (Application, Device, &Size, PU_PELS | GPIA_ASSOC);
    DevCloseDC (Device); Device = NULLHANDLE;
  }

  // Возврат.
  return Space;
}

// ─── Создает изображение ───

// Presentation_space - пространство отображения, Width и Height - размер изображения.
HBITMAP Images_CreateBitmap (HPS Presentation_space, INT Width, INT Height)
{
  // Задаем необходимые данные для того, чтобы создать изображение.
  HBITMAP Bitmap = NULLHANDLE;

  BITMAPINFOHEADER2 Header; bzero (&Header, sizeof (BITMAPINFOHEADER2));

  Header.cbFix = (ULONG) sizeof (BITMAPINFOHEADER2);
  Header.cx = Width; Header.cy = Height;
  Header.ulCompression = BCA_UNCOMP;
  Header.usUnits = BRU_METRIC;
  Header.usRecording = BRA_BOTTOMUP;
  Header.usRendering = BRH_NOTHALFTONED;
  Header.ulColorEncoding = BCE_RGB;

  // Создаем изображение.
  Bitmap = GpiCreateBitmap (Presentation_space, &Header, 0, NULL, NULL);

  // Возврат.
  return Bitmap;
}

// ─── Загружает изображение с диска ───

// Все переменные - внешние.
VOID Images_LoadBitmap (HAB Application, PCHAR File_name, PHBITMAP Bitmap, PINT Width, PINT Height)
{
  // Удаляем предыдущее изображение.
  if (*Bitmap != NULLHANDLE) { GpiDeleteBitmap (*Bitmap); *Bitmap = NULLHANDLE; }

  // Если файла с изображением нет - возврат.
  if (!FileExists (File_name)) return;

  {
    // Загружаем изображение.
    HWND Desktop = QueryDesktopWindow ();

    DESKTOP Wallpaper = { sizeof (DESKTOP), NULLHANDLE, 0, 0, SDT_LOADFILE | SDT_CENTER, 1, 0 };
    strcpy (Wallpaper.szFile, File_name);

    {
      INT Count;
      for (Count = 0; Count < 12; Count ++)
      {
        WinSetDesktopBkgnd (Desktop, &Wallpaper);

        {
          DESKTOP Current_wallpaper; bzero (&Current_wallpaper, sizeof (DESKTOP));
          WinQueryDesktopBkgnd (Desktop, &Current_wallpaper);
          if (Current_wallpaper.hbm != NULLHANDLE)
          {
            memcpy (&Wallpaper, &Current_wallpaper, sizeof (DESKTOP));
            break;
          }
        }

        #ifndef INCLUDED_BY_SHELL
        Retard ();
        #else
        DosSleep (250);
        #endif
      }
    }

    // Если оно не было загружено - возврат.
    if (Wallpaper.hbm == NULLHANDLE) return;

    // Узнаем размер изображения.
    {
      BITMAPINFOHEADER Bitmap_info; bzero (&Bitmap_info, sizeof (BITMAPINFOHEADER));
      GpiQueryBitmapParameters (Wallpaper.hbm, &Bitmap_info);
      *Width = Bitmap_info.cx; *Height = Bitmap_info.cy;
    }

    {
      // Создаем пространство отображения в памяти.
      HPS Presentation_space = Images_CreatePresentationSpace (Application);

      // Создаем в памяти еще одно изображение.
      *Bitmap = Images_CreateBitmap (Presentation_space, *Width, *Height);

      // Переносим на него изображение, загруженное с диска.
      {
        POINT Point = {0};
        GpiSetBitmap (Presentation_space, *Bitmap);
        WinDrawBitmap (Presentation_space, Wallpaper.hbm, NULL, &Point, 0, 0, DBM_NORMAL);
        GpiSetBitmap (Presentation_space, NULLHANDLE);
      }

      // Удаляем пространство отображения в памяти.
      GpiDestroyPS (Presentation_space); Presentation_space = NULLHANDLE;
    }

    // Освобождаем временно занятую память.
    Wallpaper.fl = SDT_DESTROY | SDT_NOBKGND;
    WinSetDesktopBkgnd (Desktop, &Wallpaper); Wallpaper.hbm = NULLHANDLE;

    // Обновляем окно рабочего стола.
    WinInvalidateRect (Desktop, NULL, 0);
  }

  // Возврат.
  return;
}

