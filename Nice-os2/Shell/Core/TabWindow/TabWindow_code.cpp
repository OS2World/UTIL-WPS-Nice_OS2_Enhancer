
// ��� �������� ��࠭��� � ���� ���

// Notebook_window - ���� ��������, Page - ��࠭��, Is_Log_page - �� ��࠭�� � ᮮ�饭�ﬨ �� �訡���.
VOID TabWindow_AddPage (HWND Notebook_window, PPAGE Page, BYTE Is_Log_page = 0)
{
  // �஢��塞 ��࠭���.
  if (Page == NULL) return;
  if (Page->Window == NULLHANDLE) return;

  if (!Page->Present) return;
  if (!Is_Log_page && Page->Window == Enhancer.Pages.Log->Window) return;

  if (!Is_Log_page && !Page->SetDefSettings) return;
  if (!Is_Log_page && !Page->Settings_to_show) return;

  // ������ ��� ��� ���������騥 ᢮��⢠.
  if (Page->Name[0] == 0) strcpy (Page->Name, "...");
  if (!Page->Style) Page->Style = BKA_MAJOR;

  // ������塞 ��.
  ULONG New_page = (ULONG) WinSendMsg (Notebook_window, BKM_INSERTPAGE, MPFROMLONG (0), MPFROM2SHORT (Page->Style | BKA_AUTOPAGESIZE, BKA_LAST));

  if (New_page)
  {
    WinSendMsg (Notebook_window, BKM_SETPAGEWINDOWHWND, MPFROMLONG (New_page), MPFROMHWND (Page->Window));
    WinSendMsg (Notebook_window, BKM_SETTABTEXT, MPFROMLONG (New_page), MPFROMP (Page->Name));
  }

  // ������ ����.
  SetCommonEnhancerFont (Page->Window);

  // ������ 梥�.
  SetCommonEnhancerColors (Page->Window);

  // �᫨ � ��࠭��� ���� �������� - ���뢠�� �� ᢮��⢮.
  // ���� ���� ����� ��४������ � ���ﭨ� "⮫쪮 ��� �⥭��".
  WinSetOwner (Page->Window, NULLHANDLE);

  // ������.
  return;
}

// ��� �������� �������� � ���� ���

// Notebook_window - ���� ��������.
VOID TabWindow_AddPages (HWND Notebook_window)
{
  // ������塞 ��࠭��� � ����ன����.
  for (INT Page_count = 0; Page_count < PAGELIST_LENGTH; Page_count ++)
  {
    PPAGE Page = GetPageListEntry (Page_count);
    if (Page != NULL) if (Page != Enhancer.Pages.Log) TabWindow_AddPage (Notebook_window, Page);
  }

  // ������塞 ��࠭��� � ᮮ�饭�ﬨ �� �訡���.
  TabWindow_AddPage (Notebook_window, Enhancer.Pages.Log, 1);

  // ������.
  return;
}

// ��� ������� ���� �������� ���

// Window - ���� ࠡ�祩 ������, Client_layout - �᪫���� ��� ����.
VOID TabWindow_CreateNotebookWindow (HWND Window, PLTWALL Client_layout)
{
  // ������� ����� ��������.
  {
    LTBRICK Notebook_brick; LitPrepareBrick (&Notebook_brick);
    INT Notebook_ID = 1000; ULONG Notebook_style = BKS_SPIRALBIND | BKS_MAJORTABRIGHT | BKS_ROUNDEDTABS | BKS_TABTEXTLEFT | BKS_STATUSTEXTLEFT;
    Enhancer.Notebook_window = Notebook_brick.hwnd = WinCreateWindow (Window, WC_NOTEBOOK, NULL, WS_VISIBLE | Notebook_style, LTM_X, LTM_Y, LTM_CX, LTM_CY, Window, HWND_TOP, Notebook_ID, NULL, NULL);
    Notebook_brick.prpWidthInParent = LTM_FULL_WIDTH; Notebook_brick.prpHeightInParent = LTM_FULL_HEIGHT;
    LitJoinBrick (Client_layout, &Notebook_brick);

    SetCommonEnhancerColors (Notebook_brick.hwnd);

    ULONG Gray_color = RGB_PALEGRAY;
    WinSetPresParam (Notebook_brick.hwnd, PP_NOTEBOOKBACKGROUNDCOLOR,         sizeof (Gray_color), (PVOID) &Gray_color);
    WinSetPresParam (Notebook_brick.hwnd, PP_NOTEBOOKMAJORTABBACKGROUNDCOLOR, sizeof (Gray_color), (PVOID) &Gray_color);
    WinSetPresParam (Notebook_brick.hwnd, PP_NOTEBOOKMINORTABBACKGROUNDCOLOR, sizeof (Gray_color), (PVOID) &Gray_color);
  }

  // ������ ����.
  SetCommonEnhancerFont (Enhancer.Notebook_window);

  // ������ ࠧ��� ��������.
  INT Tab_height = 25; INT Tab_width = 150;
  WinSendMsg (Enhancer.Notebook_window, BKM_SETDIMENSIONS, MPFROM2SHORT (Tab_width, Tab_height), MPFROMLONG (BKA_MAJORTAB));
  WinSendMsg (Enhancer.Notebook_window, BKM_SETDIMENSIONS, MPFROM2SHORT (Tab_width, Tab_height), MPFROMLONG (BKA_MINORTAB));

  // ������塞 ��࠭��� � ����.
  TabWindow_AddPages (Enhancer.Notebook_window);

  // ������.
  return;
}
