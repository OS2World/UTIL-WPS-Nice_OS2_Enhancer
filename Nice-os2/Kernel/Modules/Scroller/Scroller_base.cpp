
// ��� �������� � ᯨ᮪ ���, ��� ����� ��।����� ���� ���

// Window - ����, ���஥ ���� �������� � ᯨ᮪.
// �����頥��� ���祭�� - ����� � ᯨ᪥ (��� ����� �㤥� �ᯮ�짮���� ��� ��������� ���祭��).
INT Scroller_AddWindowToList (HWND Window)
{
  // ������ ���, ��� ����� ��।����� ����.
  CHAR Window_name[SIZE_OF_NAME] = ""; WinQueryClassName (Window, SIZE_OF_NAME, Window_name);

  // ���࠭塞 �஡�� � ���� ᫮��.
  if (Window_name[SIZE_OF_NAME - 2] == ' ') Window_name[SIZE_OF_NAME - 2] = '_';

  // �᫨ ��� ���� � ᯨ᪥ - ������.
  for (INT Count = 0; Count < SCROLLER_SCRLIST_SIZE; Count ++)
   if (strc (Window_name, Scroller.Scrolling_list[Count].Name))
    return Count;

  // �᫨ ��� �� �뫮 ������� - ��� ���� ��������.
  for (INT I = 0; I < SCROLLER_SCRLIST_SIZE; I ++)
   if (Scroller.Scrolling_list[I].Name[0] == 0)
   {
     // ����ᨬ ��� � ᯨ᮪.
     // �� �⮬ 蠣� ��⠥�, �� ᪮���� ��।������� ����ࠦ���� ࠢ�� "1 / 1", � ���� ��
     // ����ﭨ� � �窠� ࠢ�� ������ � ������ ����᪨ ��ᬮ�� ⮦� ��������� �� �������.
     strncpy (Scroller.Scrolling_list[I].Name, Window_name, SIZE_OF_NAME);
     Scroller.Scrolling_list[I].X_Velocity_DD = 1;
     Scroller.Scrolling_list[I].X_Velocity_D  = 1;
     Scroller.Scrolling_list[I].Y_Velocity_DD = 1;
     Scroller.Scrolling_list[I].Y_Velocity_D  = 1;
     Scroller.Scrolling_list[I].PreDefined    = 0;
     Scroller.Scrolling_list[I].Method        = SCROLLING_COMMON;

     // ���᮪ ���� �㤥� ��࠭���.
     WinPostQueueMsg (Enhancer.Modules.Scroller->Message_queue, SM_WRITE_SETTINGS, 0, 0);

     // �����頥� ����� � ᯨ᪥.
     return I;
   }

  // �����頥� �㫥��� ���祭��.
  return 0;
}

// ��� �������� � ᯨ᮪ ��� � ᪮���� ���

// Window_name - ���, XY_V_* - ᪮����, Method - ᯮᮡ �ப��⪨ (����� �⫨����� �� ��饯ਭ�⮣�).
VOID Scroller_AddPreDefinedWindowToList (PCHAR Window_name, INT X_V_DD, INT Y_V_DD, INT Method)
{
  // ������� � "蠣��" ����᪨ ��ᬮ�� �㤥� ࠢ�� ������.
  INT X_V_D = 1; INT Y_V_D = 1;

  // �᫨ ��� ���� � ᯨ᪥:
  for (INT Count = 0; Count < SCROLLER_SCRLIST_SIZE; Count ++)
   if (strc (Window_name, Scroller.Scrolling_list[Count].Name))
   {
     // � �� ��砥 ������ ᪮���� � ᯮᮡ ��।������� ����ࠦ����.
     // ������� ����� ���� ���ࠢ���� ᮮ�饭�� �१ ����᪨ ��ᬮ�� (���뫠� ����᪠� ᮮ�饭��
     // "WM_CHAR"), � ������� ���� ���� ᤢ����� ����ࠦ���� ���� �� ������⢨� ����᮪ ��ᬮ��.
     Scroller.Scrolling_list[Count].X_Velocity_DD = X_V_DD;
     Scroller.Scrolling_list[Count].X_Velocity_D  = X_V_D;
     Scroller.Scrolling_list[Count].Y_Velocity_DD = Y_V_DD;
     Scroller.Scrolling_list[Count].Y_Velocity_D  = Y_V_D;
     Scroller.Scrolling_list[Count].PreDefined    = 1;
     Scroller.Scrolling_list[Count].Method        = Method;

     // ������.
     return;
   }

  // �᫨ ��� �� �뫮 ������� - ��� ���� ��������.
  for (INT I = 0; I < SCROLLER_SCRLIST_SIZE; I ++)
   if (Scroller.Scrolling_list[I].Name[0] == 0)
   {
     // ����ᨬ ��� � ᯨ᮪.
     strncpy (Scroller.Scrolling_list[I].Name, Window_name, SIZE_OF_NAME);
     Scroller.Scrolling_list[I].X_Velocity_DD = X_V_DD;
     Scroller.Scrolling_list[I].X_Velocity_D  = X_V_D;
     Scroller.Scrolling_list[I].Y_Velocity_DD = Y_V_DD;
     Scroller.Scrolling_list[I].Y_Velocity_D  = Y_V_D;
     Scroller.Scrolling_list[I].PreDefined    = 1;
     Scroller.Scrolling_list[I].Method        = Method;

     // �४�頥� ����.
     break;
   }

  // ������.
  return;
}

// ��� ��室�� ��� � ᯨ᪥ ���

// Window - ����, ���஥ ���� ����.
// �����頥��� ���祭�� - ����� � ᯨ᪥ (��� ����� �㤥� �ᯮ�짮���� ��� ��������� ���祭��).
// �᫨ ���� �� �ᯥ��, ���������� ��६����� �� 㪠��⥫� Record_from_list, ���� ��� �� ���������.
INT Scroller_FindWindowInList (HWND Window, PSCRLIST Record_from_list = NULL)
{
  // ������ ���, ��� ����� ��।����� ����.
  CHAR Window_name[SIZE_OF_NAME] = ""; WinQueryClassName (Window, SIZE_OF_NAME, Window_name);

  // ���࠭塞 �஡�� � ���� ᫮��.
  if (Window_name[SIZE_OF_NAME - 2] == ' ') Window_name[SIZE_OF_NAME - 2] = '_';

  // �᫨ ��� ���� � ᯨ᪥:
  for (INT Count = 0; Count < SCROLLER_SCRLIST_SIZE; Count ++)
   if (strc (Window_name, Scroller.Scrolling_list[Count].Name))
   {
     // ������塞 ��६�����, 㪠�뢠���� �� ������ �� ᯨ᪠. ��᫥ �� ����� �㤥� �ᯮ�짮����.
     if (Record_from_list != NULL)
     {
       Record_from_list->X_Velocity_DD = Scroller.Scrolling_list[Count].X_Velocity_DD;
       Record_from_list->X_Velocity_D  = Scroller.Scrolling_list[Count].X_Velocity_D;
       Record_from_list->Y_Velocity_DD = Scroller.Scrolling_list[Count].Y_Velocity_DD;
       Record_from_list->Y_Velocity_D  = Scroller.Scrolling_list[Count].Y_Velocity_D;
       Record_from_list->PreDefined    = Scroller.Scrolling_list[Count].PreDefined;
       Record_from_list->Method        = Scroller.Scrolling_list[Count].Method;
     }

     // �����頥� ����� � ᯨ᪥.
     return Count;
   }

  // �����頥� �㫥��� ���祭��.
  return 0;
}

// ��� ������ ᪮���� ��।������� ����ࠦ���� � ���� ���

// Window - ����, Record_from_list - ��६�����, ����� �㤥� ᮤ�ঠ�� ᪮����.
VOID Scroller_QueryScrollingVelocity (HWND Window, PSCRLIST Record_from_list)
{
  // ������ ᪮����.
  Scroller_FindWindowInList (Window, Record_from_list);

  // ������.
  return;
}

// ��� ������ ᯮᮡ ��।������� ����ࠦ���� � ���� ���

// Window - ����, � ���஬ ���� ��।������ ����ࠦ����.
INT Scroller_QueryScrollingMethod (HWND Window)
{
  // ��室�� ���� � ᯨ᪥.
  SCRLIST Record_from_list = {0};
  Scroller_FindWindowInList (Window, &Record_from_list);

  // �����頥� ᯮᮡ ��।�������.
  return Record_from_list.Method;
}

// ��� ������, �뫮 �� ���� ��������� � ᯨ᮪ � ���祭�ﬨ �� 㬮�砭�� ���

// Window - ����, � ���஬ ���� ��।������ ����ࠦ����.
BYTE Scroller_WindowHasPreDefinedSpeed (HWND Window)
{
  // ��室�� ���� � ᯨ᪥.
  SCRLIST Record_from_list = {0};
  Scroller_FindWindowInList (Window, &Record_from_list);

  // ������.
  return Record_from_list.PreDefined;
}
