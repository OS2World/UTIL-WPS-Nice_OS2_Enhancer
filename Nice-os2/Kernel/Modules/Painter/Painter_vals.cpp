
// ��� ����頥� � ⮬, ����� ����ன�� � �����窥 OS/2 ������ ���� �������� ���

// Request_pointer - 㪠��⥫� �� ᯨ᮪ ����஥�, ����� ����⥫� 㬥�� ��������.
VOID Painter_SysValuesChangeReporter (PVOID Request_pointer)
{
  // �����ࠥ� 㪠��⥫�.
  PPREFERRED_SYSTEM_VALUES Request = (PPREFERRED_SYSTEM_VALUES) Request_pointer;

  // �஢��塞 ���.
  if (Request->cb != sizeof (PREFERRED_SYSTEM_VALUES)) return;

  // �᫨ ���� �ᮢ��� ����� ࠬ��:
  if (Painter.Settings.Draw_frames)
  {
    // ������ ��� ࠬ�� ����� �ਭ�.
    INT Border_width = 0;

    switch (Painter.Settings.Theme)
    {
      case PAINTER_THEME_CLASSIC_GRAY:
      case PAINTER_THEME_CLASSIC_RGB:
      {
        Border_width = 5;
      }
      break;

      case PAINTER_THEME_WHITE_SNOW:
      {
        Border_width = 4;
      }
      break;
    }

    // �����塞 ���譨� ᯨ᮪, �᫨ �� �ॡ����.
    if (Border_width)
    {
      Request->Change_border_width = 1;
      Request->New_border_width = Border_width;
    }
  }

  // ������.
  return;
}

// ��� ����頥� � ⮬, ����� 梥� � �����窥 OS/2 ������ ���� �������� ���

// Request_pointer - 㪠��⥫� �� ᯨ᮪ 梥⮢, ����� ����⥫� 㬥�� ��������.
VOID Painter_SysColorsChangeReporter (PVOID Request_pointer)
{
  // �����ࠥ� 㪠��⥫�.
  PPREFERRED_SYSTEM_COLORS Request = (PPREFERRED_SYSTEM_COLORS) Request_pointer;

  // �஢��塞 ���.
  if (Request->cb != sizeof (PREFERRED_SYSTEM_COLORS)) return;

  // ������ 梥�.
  if (Painter.Settings.Draw_frames && !Painter.Settings.Keep_frame_colors)
  {
    Request->Normalize_window_background = 1;
  }

  // ������.
  return;
}
