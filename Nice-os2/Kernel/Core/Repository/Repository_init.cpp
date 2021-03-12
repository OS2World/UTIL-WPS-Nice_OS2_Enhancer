
// ��� ������ ����� ���窮� �� ࠡ�祬 �⮫� ���

VOID Krnl_Repository_SetObjectNames (VOID)
{
  // ������ ����� ���窮�.
  strcpy (Krnl_Repository.Settings.Objects.Drives_name, "<WP_DRIVES>");

  strcpy (Krnl_Repository.Settings.Objects.Printer_prtname, "<WPPO_");
  strcpy (Krnl_Repository.Settings.Objects.Printers_name, "<WP_PRINTERSFOLDER>");

  strcpy (Krnl_Repository.Settings.Objects.Viewer_name, "<WP_VIEWER>");
  strcpy (Krnl_Repository.Settings.Objects.Clock_name, "<WP_CLOCK>");
  strcpy (Krnl_Repository.Settings.Objects.Pulse_name, "<WP_PULSE>");
  strcpy (Krnl_Repository.Settings.Objects.PowerMgr_name, "<WP_POWER>");

  strcpy (Krnl_Repository.Settings.Objects.LaunchPad_name, "<WP_LAUNCHPAD>");
  strcpy (Krnl_Repository.Settings.Objects.WarpCenter_name, "<WP_WARPCENTER>");
  strcpy (Krnl_Repository.Settings.Objects.SysTray_name, "<WPSystray>");
  strcpy (Krnl_Repository.Settings.Objects.XWPTaskBar_name, "<XWP_XCENTER>");

  strcpy (Krnl_Repository.Settings.Objects.HiResPalette_name, "<WP_HIRESCLRPAL>");

  // ������.
  return;
}

// ��� ������ ����� PIPE-ᮥ������� � �ਫ�����ﬨ ���

VOID Krnl_Repository_SetPipeNames (VOID)
{
  // ������ ����� PIPE-ᮥ�������.
  strcpy (Krnl_Repository.Settings.Pipes.PM123_pipe, "\\Pipe\\Pm123");
  strcpy (Krnl_Repository.Settings.Pipes.WarpVision_pipe, "\\Pipe\\Wv");
  strcpy (Krnl_Repository.Settings.Pipes.ZMP3_pipe, "\\Pipe\\Zmp3");

  // ������.
  return;
}

// ��� ��⠭�������� ����ன�� �� 㬮�砭�� ���

// Division - ����� ����ன�� ���� ��⠭�����.
VOID Krnl_Repository_SetPreDefinedSettings (LONG Division)
{
  // ������.
  return;
}

// ��� ��⠥� ����ன�� ���

// Ini_file - 䠩� ����஥�.
VOID Krnl_Repository_ReadSettings (HINI Ini_file)
{
  // ������.
  return;
}
