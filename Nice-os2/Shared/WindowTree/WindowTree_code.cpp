
// ��� ��ॡ�ࠥ� ���� �� ����� �஢�� ��ॢ� � �������� ���譨� ���ᨢ ���

// Parent_window - ����, ��� ���� ��ᬮ���� ����, Array - ���ᨢ ��� ����������,
// Length - ����� ���ᨢ�, Quantity - �᫮ ��������� ���� � ���祭�� � ���ᨢ�.
VOID WindowTree_EnumerateWindows (HWND Parent_window, PHWND Array, INT Length, PINT Quantity)
{
  // �᫨ ���ᨢ �������� �� �⪠�� - ������.
  if (*Quantity >= Length) return;

   // ��ॡ�ࠥ� ���� � 㪠������ ����.
   HENUM Enumeration = WinBeginEnumWindows (Parent_window); HWND Window = NULLHANDLE;
   while ((Window = WinGetNextWindow (Enumeration)) != NULLHANDLE)
   {
     // ���������� ����.
     INT Current_position = (*Quantity - 1);
     INT Next_position = Current_position + 1; Array[Next_position] = Window;

     // �����稢��� ��६�����, ᮤ�ঠ��� �᫮ ���� � ���ᨢ�.
     // ������ � �ᯮ�짮������ "���� ���ᮢ" ��祬�-� �� �ࠡ�⠫� - ��࠭��...
     *Quantity = *Quantity + 1;

     // �᫨ ���ᨢ �������� �� �⪠�� - �४�頥� ����.
     if (*Quantity >= Length) break;

     // �஡㥬 ���� ���� ����� �⮣� ����.
     // �᫨ �� ⠬ ��� - ���祭�� ��६����� �� ���������.
     WindowTree_EnumerateWindows (Window, Array, Length, Quantity);
   }
   WinEndEnumWindows (Enumeration);

  // ������.
  return;
}

// ��� ��ᬠ�ਢ��� ��ॢ� ���� � �������� ���ᨢ ���祭�� ��� ��� ���

// Window - ����, � ���ண� ���� ����� ��ᬮ��, Array - ���ᨢ ��� ����������, Length - ����� ���ᨢ�.
VOID WindowTree_ExploreWindowTree (HWND Window, PHWND Array, PINT Length)
{
  // �஢��塞 ���祭��.
  if (Array == NULL || Length == NULL || *Length <= 0) return;

  // ��ᬠ�ਢ��� ��ॢ� ����.
  Array[0] = Window; INT Quantity = 1;
  WindowTree_EnumerateWindows (Window, Array, *Length, &Quantity);

  // ���������� �᫮ ��������� ����.
  *Length = Quantity;

  // ������.
  return;
}

// ��� ������ ��ॢ� ���� ���

// Window - ����, ��稭�� � ���ண� ���� 㤠���� �� ����, � ��६�����
// Include_root_window 㪠�뢠��, ���� �� ����� � ���� 㤠���� �� ����.
VOID WindowTree_DestroyWindowTree (HWND Window, BYTE Include_root_window = 1)
{
  // ��ᬠ�ਢ��� ��ॢ� ����.
  HWND Tree[WNDTREE_SIZE]; INT Length = WNDTREE_SIZE; WindowTree_ExploreWindowTree (Window, Tree, &Length);

  // �⪫�砥� �ᮢ���� �� ��� �����.
  for (INT Count = 0; Count < Length; Count ++) WinEnableWindowUpdate (Tree[Count], 0);

  // ����塞 �� ����, ��稭�� � ��᫥����� ����������.
  INT Limit = 0; if (!Include_root_window) Limit = 1;

  for (Count = Length - 1; Count >= Limit; Count --) WinDestroyWindow (Tree[Count]);

  // ����砥� �ᮢ���� � ����, �᫨ ��� 㤠���� �� ����.
  if (!Include_root_window) WinEnableWindowUpdate (Window, 1);

  // ������.
  return;
}

// ��� ����砥� ��� �⪫�砥� �ᮢ���� � ����� ���

// Window - ����, New_state - ����� ���ﭨ�, Include_root_window - ���� �� �������� � �� ����.
// � ��६����� Changed_windows �����뢠���� ����, ���ﭨ� ������ ����⢨⥫쭮 �뫮 ��������.
VOID WindowTree_EnableWindowTreeUpdate (HWND Window, BYTE New_state, PHWND Changed_windows = NULL, INT Changed_windows_length = WNDTREE_SIZE, BYTE Include_root_window = 1)
{
  // ��ᬠ�ਢ��� ��ॢ� ����.
  HWND Tree[WNDTREE_SIZE]; INT Length = WNDTREE_SIZE; WindowTree_ExploreWindowTree (Window, Tree, &Length);

  // ����砥� ��� �⪫�砥� �ᮢ���� �� ��� �����.
  // �������� ���� - �� �ண���, ��⮬� �� �� ����祭�� �ᮢ���� ��� �⠭�� �����묨.
  INT Limit = 0; if (!Include_root_window) Limit = 1;

  if (!New_state)
  {
    for (INT Count = Limit; Count < Length; Count ++) 
    {
      if (Changed_windows != NULL && Count < Changed_windows_length) Changed_windows[Count] = NULLHANDLE;

      if (WinIsWindowVisible (Tree[Count])) 
      {
        WinEnableWindowUpdate (Tree[Count], 0);

        if (Changed_windows != NULL && Count < Changed_windows_length) Changed_windows[Count] = Tree[Count];
      }
    }
  }
  else
  {
    for (INT Count = Length - 1; Count >= Limit; Count --) 
    {
      if (Changed_windows != NULL && Count < Changed_windows_length) 
       if (Changed_windows[Count] == NULLHANDLE || Changed_windows[Count] != Tree[Count]) continue;

      WinEnableWindowUpdate (Tree[Count], 1);
    }
  }

  // ������.
  return;
}

