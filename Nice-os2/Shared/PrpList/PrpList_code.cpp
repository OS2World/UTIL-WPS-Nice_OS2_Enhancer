
// ��� �����頥� "����� ᯨ᪠ - 1" ��� ��� ��宦����� � ��砫� ���

// Descendant - ᢥ����� � ᯨ᪥.
INT PrpList_GetTopItemPosition (PPRPLISTDESC Descendant)
{
  // ����� ᯨ᪠ ����� ���� ࠢ�� ��� ��� ���� �।��쭮�.
  if (Descendant->Top_position == 0 || Descendant->Top_position == Descendant->Length - 1)
   return Descendant->Top_position;
  else
   return Descendant->Top_position - 1;
}

// ��� ��ॡ�ࠥ� ᯨ᮪ ���

// Descendant - ᢥ����� � ᯨ᪥, Key - ���祭�� ��� ���᪠.
// �����頥��� ���祭�� - �ᯮ������� ������ � ᯨ᪥ ��� -1.
INT PrpList_LookupList (PPRPLISTDESC Descendant, LISTKEY Key)
{
  // �饬 ���祭�� � ᯨ᪥.
  PRPLISTISITEMEQUALSPROCEDURE IsEqualsTo = Descendant->IsItemEqualsTo;

  for (INT Count = PrpList_GetTopItemPosition (Descendant); Count >= 0; Count --)
   if (IsEqualsTo (Count, Key)) return Count;

  // ������.
  return -1;
}

// ��� ��室�� ���祭�� � ᯨ᪥ ���

// Descendant - ᢥ����� � ᯨ᪥, Key - ���祭�� ��� ���᪠, Property - ᢮��⢮, Data - �����.
VOID PrpList_FindProperty (PPRPLISTDESC Descendant, LISTKEY Key, LISTPRP Property, PVOID Data)
{
  // �饬 ���祭�� � ᯨ᪥.
  INT Position = PrpList_LookupList (Descendant, Key);

  // �᫨ ���祭�� ������� - �롨ࠥ� ᢮��⢮.
  if (Position != -1)
  {
    PRPLISTGETPOINTERPROCEDURE SelectPointer = Descendant->GetPointerForData;
    PRPLISTGETSIZERPROCEDURE GetItemSize = Descendant->GetSizeOfData;

    memcpy (Data, SelectPointer (Position, Property), GetItemSize (Property));
  }

  // ������.
  return;
}

// ��� �������� ᢮��⢠ � ᯨ᮪ ��� ������� �� ���

// Descendant - ᢥ����� � ᯨ᪥, Key - ���祭�� ��� ���᪠, Property - ᢮��⢮, Data - �����.
VOID PrpList_SetProperty (PPRPLISTDESC Descendant, LISTKEY Key, LISTPRP Property, PVOID Data)
{
  // �饬 ���祭�� � ᯨ᪥.
  INT Position = PrpList_LookupList (Descendant, Key);

  // �᫨ ��� ��� � ᯨ᪥ - ���� ��� ��������.
  if (Position == -1)
  {
    // ���祭�� ����������� ���� �� ��㣨�.
    Position = Descendant->Input_position;

    // �᫨ ᯨ᮪ 㦥 �ᯮ������ - � ��� ����� ���� ᢮������ ���� ��� ����������.
    BYTE Hole_is_found = 0;

    if (Descendant->Top_position != 0)
    {
      PRPLISTISEMPTYPROCEDURE PlaceIsEmpty = Descendant->IsItemEmpty;

      for (INT Count = PrpList_GetTopItemPosition (Descendant); Count >= 0; Count --)
       if (PlaceIsEmpty (Count))
       {
         Hole_is_found = 1; Position = Count;
         break;
       }
    }

    // �᫨ ���祭�� ���������� �� �� ᢮������ ����:
    if (!Hole_is_found)
    {
      // ������ �ᯮ������� ��� ᫥���饣� ���祭��.
      // ����� ᯨ᮪ ����������, ���室�� � ��� ��砫� - ⮣�� �������� ���� ���祭�� ��⠫�������� �� ����.
      if (Descendant->Input_position != Descendant->Length - 1)
       Descendant->Input_position ++;
      else
       Descendant->Input_position = 0;

      // �����稢��� ����� ᯨ᪠, �᫨ �� ��������.
      if (Descendant->Top_position != Descendant->Length - 1)
       Descendant->Top_position ++;

      // �᢮������� ���� ��� ������ ���祭��.
      PRPLISTDISCARDPROCEDURE DiscardProperties = Descendant->DiscardItem;
      DiscardProperties (Position);
    }

    // ������塞 ���祭�� � ᯨ᮪.
    PRPLISTCREATENEWPROCEDURE CreateItem = Descendant->CreateNewItem;
    CreateItem (Position, Key);
  }

  // ��⠭�������� ᢮��⢮.
  PRPLISTGETPOINTERPROCEDURE SelectPointer = Descendant->GetPointerForData;
  PRPLISTGETSIZERPROCEDURE GetItemSize = Descendant->GetSizeOfData;

  memcpy (SelectPointer (Position, Property), Data, GetItemSize (Property));

  // ������.
  return;
}

// ��� ��祣� �� ������ ���

ULONG PrpList_Void (VOID) 
{
  // ��祣� �� ������ � ��祣� �� �����頥�.
  // �� �� �� ��稫���, � ���設� �⥪� �㤥� ��� �㫥��� ���祭��.
  return 0;
}

// ��� �����⠢������ ᯨ᮪ ���

// Descendant - ᢥ����� � ᯨ᪥.
VOID PrpList_PrepareList (PPRPLISTDESC Descendant)
{
  // ����뢠�� �� ��६����. ��뢠�� bzero () ����� ����易⥫쭮 - �� 㢥���� ��室 �����.
  Descendant->Top_position = Descendant->Input_position = 0;

  // ����뢠�� �� 㪠��⥫� �� ��⮤�.
  // �� �������, ���ਬ��, �� ����஥��� 㤫��塞��� ᯨ᪠, � ��⥬, �� ��� �᭮�� - 
  // ����ﭭ���, � ���஬ "��⮤ ��� 㤫������ ᯨ᪠" ���� ��祣� �� �㤥� ������.
  Descendant->IsItemEqualsTo    = (PRPLISTISITEMEQUALSPROCEDURE) PrpList_Void;
  Descendant->IsItemEmpty       = (PRPLISTISEMPTYPROCEDURE)      PrpList_Void;
  Descendant->CreateNewItem     = (PRPLISTCREATENEWPROCEDURE)    PrpList_Void;
  Descendant->DiscardItem       = (PRPLISTDISCARDPROCEDURE)      PrpList_Void;
  Descendant->GetPointerForData = (PRPLISTGETPOINTERPROCEDURE)   PrpList_Void;
  Descendant->GetSizeOfData     = (PRPLISTGETSIZERPROCEDURE)     PrpList_Void;

  // ������.
  return;
}
