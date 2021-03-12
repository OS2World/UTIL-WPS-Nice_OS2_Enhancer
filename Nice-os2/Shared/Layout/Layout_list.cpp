
// ��� ������� ᯨ᮪ ���� � ����� ����� ���

// Layout - ᯨ᮪ ����� �����, Window - ���� � ���ﬨ �����,
// � Length - �������襥 ��������� �᫮ ����� ����� � ᯨ᪥.
VOID Layout_LitCreateLayout (PLTWALL Layout, HWND Window, INT Length = 100)
{
  // �᫨ ᯨ᮪ �� ����� ��� �᫮ ����� ����� ����� ������� - ������.
  if (Layout == NULL || Length < 1) return;

  // �᫨ ���� �� 㪠���� - ������.
  if (Window == NULLHANDLE) return;

  // �᫨ ⠪��� ���� ��� - ������.
  if (!WinIsWindow (WinQueryAnchorBlock (Window), Window)) return;

  // �⢮��� ������ ��� ᯨ᪠ � ���������� ��� ᢮��⢠.
  if (DosAllocMem ((PPVOID) &Layout->pList, sizeof (LTBRICK) * Length, PAG_ALLOCATE) == NO_ERROR)
  {
    Layout->ulLength = Length;
  }
  // ��� ���뢠�� ��६����� ��� ���� � ��砥 ��㤠�.
  else
  {
    bzero (Layout, sizeof (LTWALL));
  }

  // ���������� ����.
  Layout->hwnd = Window;

  // ������.
  return;
}

// ��� �����頥� 㪠��⥫� �� ���� ����� � ᯨ᪥ ���

// Layout - ᯨ᮪ ����� �����, Position - �ᯮ�������, ��� ���ண� ���� ������� 㪠��⥫�.
PLTBRICK Layout_GetBrickPointer (PLTWALL Layout, INT Position)
{
  // �஢��塞 ���祭�� ��६����� ��� ���᫥��� �ᯮ�������.
  // ��� ��⠥��� �� ��� � �� ����� ���� ࠢ�� ����� ᯨ᪠.
  if (Position < 0 || Position >= Layout->ulLength) return NULL;

  // ������뢠�� �ᯮ�������.
  PBYTE Exact_pointer = (PBYTE) Layout->pList + Position * sizeof (LTBRICK);

  return (PLTBRICK) Exact_pointer;
}

// ��� �஢���� ��६����� ��� ᯨ᪠ ���

// Layout - ᯨ᮪ ����� �����. �����頥��� ���祭�� - 1 ��� 0.
BYTE Layout_ListIsCorrect (PLTWALL Layout)
{
  // �஢��塞 ᯨ᮪.
  if (Layout == NULL || Layout->pList == NULL ||
      Layout->ulLength < 1 || Layout->ulQuantity < 0) return 0;

  // �஡㥬 ������� 㪠��⥫� ��� ��᫥���� ��ப� ᯨ᪠.
  if (Layout->ulQuantity != 0)
   if (!Layout_GetBrickPointer (Layout, Layout->ulQuantity - 1))
    return 0;

  // ������.
  return 1;
}

// ��� ������ ᯨ᮪ ���� � ����� �����, ᮧ����� ࠭�� ���

// Layout - ᯨ᮪ ����� �����.
VOID Layout_LitDeleteLayout (PLTWALL Layout)
{
  // �᫨ ᯨ᮪ ����� ����୮ - ������.
  if (!Layout_ListIsCorrect (Layout)) return;

  // �᢮������� ������.
  DosFreeMem (Layout->pList);

  // ����뢠�� ��६����� ��� ᯨ᪠.
  bzero (Layout, sizeof (LTWALL));

  // ������.
  return;
}

// ��� �஢���� ��६����� ��� ᯨ᪠ ���

// Layout - ᯨ᮪ ����� �����. �����頥��� ���祭�� - 1 ��� 0.
BYTE Layout_ListIsFull (PLTWALL Layout)
{
  // �஢��塞, �������� �� ᯨ᮪.
  if (Layout->ulQuantity == Layout->ulLength) return 1;

  // ������.
  return 0;
}

// ��� �஢���� ��६����� ��� ���� ����� ���

// Brick - ���� �����. �����頥��� ���祭�� - 1 ��� 0.
BYTE Layout_BrickIsCorrect (PLTBRICK Brick)
{
  // �஢��塞 ��६����� ��� ���� �����.
  if (Brick->cb != sizeof (LTBRICK)) return 0;
  if (Brick->hwnd == NULLHANDLE) return 0;

  // ������.
  return 1;
}

// ��� �����⠢������ ��६����� ��� ���� ����� ���

// Brick - ���� �����.
VOID Layout_LitPrepareBrick (PLTBRICK Brick)
{
  // ������塞 ��६����� ��ﬨ.
  bzero (Brick, sizeof (LTBRICK));

  // ���������� ����� ��������.
  Brick->cb = sizeof (LTBRICK);

  // ������.
  return;
}

// ��� �������� ���� ����� � ᯨ᮪ ���

// Layout - ᯨ᮪ ����� �����, Brick - ���� ����� ��� ���������� � ᯨ᮪.
VOID Layout_LitJoinBrick (PLTWALL Layout, PLTBRICK Brick)
{
  // �᫨ ᯨ᮪ ����� ����୮ - ������.
  if (!Layout_ListIsCorrect (Layout)) return;

  // �᫨ ���� ����� �� ������ - ������.
  if (!Layout_BrickIsCorrect (Brick)) return;

  // �᫨ ᯨ᮪ �������� �� �⪠�� - ������.
  if (Layout_ListIsFull (Layout)) return;

  // ������ ��� ���� ����� ����� ���� ����� � �窠� (�᫮ > 1.00) ��� � %% ��
  // ࠧ��� த�⥫�᪮�� ���� (�᫮ <= 1.00), ��� �� 㬮�砭�� (�᫮ = 0.00),
  // � �᫨ ࠧ��� ���� ����� ����� ��� - ��⠥�, �� �� �� �� �����.
  if (Brick->prpWidthInParent < 0) Brick->prpWidthInParent = 0;
  if (Brick->prpHeightInParent < 0) Brick->prpHeightInParent = 0;

  // ������ �ਭ� � ����� �� 㬮�砭��.
  if (!Brick->prpWidthInParent || !Brick->prpHeightInParent)
  {
    Brick->prpWidthInParent = Brick->prpHeightInParent = 0;

    CHAR Window_name[SIZE_OF_NAME] = ""; WinQueryClassName (Brick->hwnd, SIZE_OF_NAME, Window_name);

    if (WinFindAtom (WinQuerySystemAtomTable (), Window_name) == SHORT1FROMLONG ((ULONG) WC_FRAME) ||
        WinFindAtom (WinQuerySystemAtomTable (), Window_name) == SHORT1FROMLONG ((ULONG) WC_NOTEBOOK))
    {
      Brick->prpWidthInParent = Brick->prpHeightInParent = 1.00;
    }
  }

  // ��� ��� � ���� ࠧ ����� ᯨ᪠ �뫠 㢥��祭� �� �������, ���祭��
  // ��६����� ��� ��� ᮮ⢥����� ᫥���饬� �ᯮ������� ��� ���� �����.
  INT Next_position = Layout->ulQuantity; PLTBRICK Pointer = Layout_GetBrickPointer (Layout, Next_position);

  if (Pointer != NULL)
  {
    // ������塞 ���� ����� � ᯨ᮪.
    memcpy (Pointer, Brick, sizeof (LTBRICK));

    // �����稢��� ����� ᯨ᪠.
    Layout->ulQuantity ++;
  }

  // ������ ���� ������.
  WinShowWindow (Brick->hwnd, 1);

  // ����ᮢ뢠�� ���� �� ����.
  WinValidateRect (Brick->hwnd, NULL, 1);

  // ����뢠�� ���祭�� ��� ���� �����, �⮡� ��砩�� �� �ᯮ�짮���� ��� ������.
  HWND Window_for_future_use = Brick->hwnd;
  bzero (Brick, sizeof (LTBRICK)); Brick->hwnd = Window_for_future_use;

  // ������.
  return;
}

// ��� �������� � ᯨ᮪ �ਧ��� ������ �鸞 ���

// Layout - ᯨ᮪ ����� �����.
VOID Layout_LitCompleteRow (PLTWALL Layout)
{
  // �᫨ ᯨ᮪ ����� ����୮ - ������.
  if (!Layout_ListIsCorrect (Layout)) return;

  // �᫨ ᯨ᮪ ���⮩ - ���� �� � ⠪ �㤥� ����, ������.
  if (!Layout->ulQuantity) return;

  // �᫨ �ਧ��� ������ �鸞 ⮫쪮 �� �� �������� - ������.
  INT Current_position = Layout->ulQuantity - 1; PLTBRICK Pointer = Layout_GetBrickPointer (Layout, Current_position);

  if (Pointer != NULL) if (Pointer->hwnd == (HWND) LTM_NEXT_ROW_MARK) return;

  // ������ �ᯮ������� ��� �ਧ���� ������ �鸞.
  INT Next_position = Layout->ulQuantity; Pointer = Layout_GetBrickPointer (Layout, Next_position);

  if (Pointer != NULL)
  {
    // ������塞 � ᯨ᮪ �ਧ��� ������ �鸞.
    LTBRICK Mark_brick; Layout_LitPrepareBrick (&Mark_brick);

    Mark_brick.hwnd = (HWND) LTM_NEXT_ROW_MARK;

    memcpy (Pointer, &Mark_brick, sizeof (LTBRICK));

    // �����稢��� ����� ᯨ᪠.
    Layout->ulQuantity ++;
  }

  // ������.
  return;
}

// ��� �஢���� ���祭�� ��� �ᯮ������� ���� �����, �������� ���짮��⥫�� ���

// Layout - ᯨ᮪ ����� �����, Position - �ᯮ������� ���� ����� � ���.
BYTE Layout_PositionIsCorrect (PLTWALL Layout, INT Position)
{
  // �஢��塞 ���祭�� ��६����� ��� ���᫥��� �ᯮ�������.
  // ��� ��⠥��� �� ��� � �� �ॢ�蠥� �᫮ ���祭�� � ᯨ᪥.
  if (Position < 0 || Position >= Layout->ulQuantity) return 0;

  // ������.
  return 1;
}

// ��� ������ ���� ����� �� ᯨ᪠ ���

// Layout - ᯨ᮪ ����� �����, Position - �ᯮ������� ���� ����� � ���.
VOID Layout_DeleteInputField (PLTWALL Layout, INT Position)
{
  // �᫨ ᯨ᮪ ����� ����୮ - ������.
  if (!Layout_ListIsCorrect (Layout)) return;

  // �᫨ �ᯮ������� ������ ����୮ - ������.
  if (!Layout_PositionIsCorrect (Layout, Position)) return;

  // ����砥� 㪠��⥫� �� ���� ����� � ᯨ᪥.
  PLTBRICK Pointer = Layout_GetBrickPointer (Layout, Position);

  if (Pointer != NULL)
  {
    // ���ࠥ� ���祭�� ��� ���� �����.
    bzero (Pointer, sizeof (LTBRICK));

    // �᫨ �� ��᫥���� ���� ����� - 㬥��蠥� ����� ᯨ᪠.
    if (Position == Layout->ulQuantity - 1) Layout->ulQuantity --;
  }

  // ������.
  return;
}

// ��� ��室�� ���� ����� � ᯨ᪥ ���

// Layout - ᯨ᮪ ����� �����, Field - ���� �����.
// �����頥��� ���祭�� - 㪠��⥫� �� ���� ����� � ᯨ᪥.
PLTBRICK Layout_FindInputField (PLTWALL Layout, HWND Field)
{
  // �᫨ ᯨ᮪ ����� ����୮ - ������.
  if (!Layout_ListIsCorrect (Layout)) return NULL;

  // �᫨ ���� ����� �� ������ - ������.
  if (Field == NULLHANDLE) return NULL;

  // ��ᬠ�ਢ��� ᯨ᮪.
  for (INT Count = 0; Count < Layout->ulQuantity; Count ++)
  {
    // ����砥� 㪠��⥫� �� ���� ����� � ᯨ᪥.
    PLTBRICK Pointer = Layout_GetBrickPointer (Layout, Count);

    if (Pointer != NULL)
    {
      // �஢��塞 ���� �����.
      if (Pointer->hwnd == Field) return Pointer;
    }
  }

  // ������.
  return NULL;
}

// ��� ������ ᢮��⢠ ���� ����� ���

// Layout - ᯨ᮪ ����� �����, Field - ���� �����.
// Brick - ������ ��६�����, ����� �㤥� ���������, �᫨ ���� ����� �㤥� �������.
VOID Layout_GetInputField (PLTWALL Layout, HWND Field, PLTBRICK Brick)
{
  // �᫨ ������ ��६����� �� ������ - ������.
  if (Brick == NULL) return;

  // ��室�� ���� �����. �� �⮬ �믮������� �஢�ન ��� ��� ��⠫��� ���祭��.
  PLTBRICK Pointer = Layout_FindInputField (Layout, Field);

  // �����塞 ������ ��६����� ��� ���ࠥ� ��.
  if (Pointer != NULL) memcpy (Brick, Pointer, sizeof (LTBRICK));
  else bzero (Brick, sizeof (LTBRICK));

  // ������.
  return;
}

// ��� ������� ᢮��⢠ ���� ����� ���

// Layout - ᯨ᮪ ����� �����, Field - ���� �����.
// Brick - ������ ��६�����, ����� �㤥� �ᯮ�짮����, �᫨ ���� ����� �㤥� �������.
VOID Layout_SetInputField (PLTWALL Layout, HWND Field, PLTBRICK Brick)
{
  // �᫨ ������ ��६����� �� ������ - ������.
  if (Brick == NULL) return;

  // ��室�� ���� �����. �� �⮬ �믮������� �஢�ન ��� ��� ��⠫��� ���祭��.
  PLTBRICK Pointer = Layout_FindInputField (Layout, Field);

  // ��७�ᨬ ���祭�� �� ���譥� ��६�����.
  if (Pointer != NULL) memcpy (Pointer, Brick, sizeof (LTBRICK));

  // ������.
  return;
}

