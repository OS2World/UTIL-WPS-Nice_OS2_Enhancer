
// ��� �����頥� "����� ᯨ᪠ - 1" ��� ��� ��宦����� � ��砫� ���

// Descendant - ᢥ����� � ᯨ᪥.
INT AbstractPrpList_GetTopItemPosition( PPRPLISTDESC Descendant )
{
 // ����� ᯨ᪠ ����� ���� ࠢ�� ��� ��� ���� �।��쭮�.
 if( Descendant->Top_position == 0 || Descendant->Top_position == Descendant->Length - 1 )
  return Descendant->Top_position;
 else
  return Descendant->Top_position - 1;
}

// ��� ��ॡ�ࠥ� ᯨ᮪ ���

// Descendant - ᢥ����� � ᯨ᪥, Key - ���祭�� ��� ���᪠.
// �����頥��� ���祭�� - �ᯮ������� ������ � ᯨ᪥ ��� -1.
INT AbstractPrpList_LookupList( PPRPLISTDESC Descendant, LISTKEY Key )
{
 // �饬 ���祭�� � ᯨ᪥.
 PRPLISTISITEMEQUALSPROCEDURE ItemsAreEqually = Descendant->IsItemEqualsTo;

 for( INT Count = AbstractPrpList_GetTopItemPosition( Descendant ); Count >= 0; Count -- )
  if( ItemsAreEqually( Count, Key ) ) return Count;

 // ������.
 return -1;
}

// ��� ��室�� ���祭�� � ᯨ᪥ ���

// Descendant - ᢥ����� � ᯨ᪥, Key - ���祭�� ��� ���᪠, Property - ᢮��⢮, Data - �����.
VOID AbstractPrpList_FindProperty( PPRPLISTDESC Descendant, LISTKEY Key, LISTPRP Property, PVOID Data )
{
 // �饬 ���祭�� � ᯨ᪥.
 INT Position = AbstractPrpList_LookupList( Descendant, Key );

 // �᫨ ���祭�� ������� - �롨ࠥ� ᢮��⢮.
 if( Position != -1 )
  {
   PRPLISTGETPOINTERPROCEDURE SelectPointer = Descendant->GetPointerForData;
   PRPLISTGETSIZERPROCEDURE GetItemSize = Descendant->GetSizeOfData;

   memcpy( Data, SelectPointer( Position, Property ), GetItemSize( Property ) );
  }

 // ������.
 return;
}

// ��� �������� ᢮��⢠ � ᯨ᮪ ��� ������� �� ���

// Descendant - ᢥ����� � ᯨ᪥, Key - ���祭�� ��� ���᪠, Property - ᢮��⢮, Data - �����.
VOID AbstractPrpList_SetProperty( PPRPLISTDESC Descendant, LISTKEY Key, LISTPRP Property, PVOID Data )
{
 // �饬 ���祭�� � ᯨ᪥.
 INT Position = AbstractPrpList_LookupList( Descendant, Key );

 // �᫨ ��� ��� � ᯨ᪥ - ���� ��� ��������.
 if( Position == -1 )
  {
   // ���祭�� ����������� ���� �� ��㣨�.
   Position = Descendant->Input_position;

   // �᫨ ᯨ᮪ 㦥 �ᯮ������ - � ��� ����� ���� ᢮������ ���� ��� ����������.
   BYTE Hole_is_found = 0;

   if( Descendant->Top_position != 0 )
    {
     PRPLISTISEMPTYPROCEDURE PlaceIsEmpty = Descendant->IsItemEmpty;

     for( INT Count = AbstractPrpList_GetTopItemPosition( Descendant ); Count >= 0; Count -- )
      if( PlaceIsEmpty( Count ) )
       {
        Hole_is_found = 1; Position = Count;
        break;
       }
    }

   // �᫨ ���祭�� ���������� �� �� ᢮������ ����:
   if( !Hole_is_found )
    {
     // ������ �ᯮ������� ��� ᫥���饣� ���祭��.
     // ����� ᯨ᮪ ����������, ���室�� � ��� ��砫� - ⮣�� �������� ���� ���祭�� ��⠫�������� �� ����.
     if( Descendant->Input_position != Descendant->Length - 1 )
      Descendant->Input_position ++;
     else
      Descendant->Input_position = 0;

     // �����稢��� ����� ᯨ᪠, �᫨ �� ��������.
     if( Descendant->Top_position != Descendant->Length - 1 )
      Descendant->Top_position ++;

     // �᢮������� ���� ��� ������ ���祭��.
     PRPLISTDISCARDPROCEDURE DiscardProperties = Descendant->DiscardItem;
     DiscardProperties( Position );
    }

   // ������塞 ���祭�� � ᯨ᮪.
   PRPLISTCREATENEWPROCEDURE CreateItem = Descendant->CreateNewItem;
   CreateItem( Position, Key );
  }

 // ��⠭�������� ᢮��⢮.
 PRPLISTGETPOINTERPROCEDURE SelectPointer = Descendant->GetPointerForData;
 PRPLISTGETSIZERPROCEDURE GetItemSize = Descendant->GetSizeOfData;

 memcpy( SelectPointer( Position, Property ), Data, GetItemSize( Property ) );

 // ������.
 return;
}

// ��� �����⠢������ ᯨ᮪ ���

// Descendant - ᢥ����� � ᯨ᪥.
VOID AbstractPrpList_PrepareList( PPRPLISTDESC Descendant )
{
 // ����뢠�� �� ��६����. ��뢠�� bzero() ����� ����易⥫쭮 - �� 㢥���� ��室 �����.
 Descendant->Top_position = Descendant->Input_position = 0;

 // ����뢠�� �� 㪠��⥫� �� ��⮤�.
 // �� �������, ���ਬ��, �� ����஥��� 㤫��塞��� ᯨ᪠, � ��⥬, �� ��� �᭮�� - 
 // ����ﭭ���, � ���஬ "��⮤ ��� 㤫������ ᯨ᪠" ���� ��祣� �� �㤥� ������.
 Descendant->IsItemEqualsTo    = (PRPLISTISITEMEQUALSPROCEDURE) AbstractClass_Void;
 Descendant->IsItemEmpty       = (PRPLISTISEMPTYPROCEDURE)      AbstractClass_Void;
 Descendant->CreateNewItem     = (PRPLISTCREATENEWPROCEDURE)    AbstractClass_Void;
 Descendant->DiscardItem       = (PRPLISTDISCARDPROCEDURE)      AbstractClass_Void;
 Descendant->GetPointerForData = (PRPLISTGETPOINTERPROCEDURE)   AbstractClass_Void;
 Descendant->GetSizeOfData     = (PRPLISTGETSIZERPROCEDURE)     AbstractClass_Void;

 // ������.
 return;
}
