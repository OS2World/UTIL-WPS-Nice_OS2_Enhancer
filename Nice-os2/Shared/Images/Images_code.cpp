// ��� ������� ����࠭�⢮ �⮡ࠦ���� ���

HPS Images_CreatePresentationSpace (HAB Application)
{
  // ������� ����࠭�⢮ �⮡ࠦ����.
  DEVOPENSTRUC Display = {0}; Display.pszDriverName = "Display";
  SIZEL Size = {0}; HDC Device = NULLHANDLE; HPS Space = NULLHANDLE;

  Device = DevOpenDC (Application, OD_MEMORY, "*", 0, (PDEVOPENDATA) &Display, NULLHANDLE);

  if (Device != NULLHANDLE)
  {
    Space = GpiCreatePS (Application, Device, &Size, PU_PELS | GPIA_ASSOC);
    DevCloseDC (Device); Device = NULLHANDLE;
  }

  // ������.
  return Space;
}

// ��� ������� ����ࠦ���� ���

// Presentation_space - ����࠭�⢮ �⮡ࠦ����, Width � Height - ࠧ��� ����ࠦ����.
HBITMAP Images_CreateBitmap (HPS Presentation_space, INT Width, INT Height)
{
  // ������ ����室��� ����� ��� ⮣�, �⮡� ᮧ���� ����ࠦ����.
  HBITMAP Bitmap = NULLHANDLE;

  BITMAPINFOHEADER2 Header; bzero (&Header, sizeof (BITMAPINFOHEADER2));

  Header.cbFix = (ULONG) sizeof (BITMAPINFOHEADER2);
  Header.cx = Width; Header.cy = Height;
  Header.ulCompression = BCA_UNCOMP;
  Header.usUnits = BRU_METRIC;
  Header.usRecording = BRA_BOTTOMUP;
  Header.usRendering = BRH_NOTHALFTONED;
  Header.ulColorEncoding = BCE_RGB;

  // ������� ����ࠦ����.
  Bitmap = GpiCreateBitmap (Presentation_space, &Header, 0, NULL, NULL);

  // ������.
  return Bitmap;
}

// ��� ����㦠�� ����ࠦ���� � ��᪠ ���

// �� ��६���� - ���譨�.
VOID Images_LoadBitmap (HAB Application, PCHAR File_name, PHBITMAP Bitmap, PINT Width, PINT Height)
{
  // ����塞 �।��饥 ����ࠦ����.
  if (*Bitmap != NULLHANDLE) { GpiDeleteBitmap (*Bitmap); *Bitmap = NULLHANDLE; }

  // �᫨ 䠩�� � ����ࠦ����� ��� - ������.
  if (!FileExists (File_name)) return;

  {
    // ����㦠�� ����ࠦ����.
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

    // �᫨ ��� �� �뫮 ����㦥�� - ������.
    if (Wallpaper.hbm == NULLHANDLE) return;

    // ������ ࠧ��� ����ࠦ����.
    {
      BITMAPINFOHEADER Bitmap_info; bzero (&Bitmap_info, sizeof (BITMAPINFOHEADER));
      GpiQueryBitmapParameters (Wallpaper.hbm, &Bitmap_info);
      *Width = Bitmap_info.cx; *Height = Bitmap_info.cy;
    }

    {
      // ������� ����࠭�⢮ �⮡ࠦ���� � �����.
      HPS Presentation_space = Images_CreatePresentationSpace (Application);

      // ������� � ����� �� ���� ����ࠦ����.
      *Bitmap = Images_CreateBitmap (Presentation_space, *Width, *Height);

      // ��७�ᨬ �� ���� ����ࠦ����, ����㦥���� � ��᪠.
      {
        POINT Point = {0};
        GpiSetBitmap (Presentation_space, *Bitmap);
        WinDrawBitmap (Presentation_space, Wallpaper.hbm, NULL, &Point, 0, 0, DBM_NORMAL);
        GpiSetBitmap (Presentation_space, NULLHANDLE);
      }

      // ����塞 ����࠭�⢮ �⮡ࠦ���� � �����.
      GpiDestroyPS (Presentation_space); Presentation_space = NULLHANDLE;
    }

    // �᢮������� �६���� ������� ������.
    Wallpaper.fl = SDT_DESTROY | SDT_NOBKGND;
    WinSetDesktopBkgnd (Desktop, &Wallpaper); Wallpaper.hbm = NULLHANDLE;

    // ������塞 ���� ࠡ�祣� �⮫�.
    WinInvalidateRect (Desktop, NULL, 0);
  }

  // ������.
  return;
}

