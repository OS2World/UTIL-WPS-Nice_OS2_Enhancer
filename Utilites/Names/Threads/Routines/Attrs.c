
// ��� ����뢠�� ���७�� ��ਡ�� ��� 䠩��. ���

// �����頥��� ���祭�� - ��ࠡ�⠭ �� 䠩�, 1 ��� 0.
VOID DiscardEA( PCHAR File_name, PCHAR EA_Name )
{
 // ������ �᫮ � �������� ��ਡ�⮢.
 PGEA2LIST Descriptions = NULL; ULONG Descriptions_size = 4096;

 if( DosAllocMem( (PPVOID) &Descriptions, Descriptions_size, PAG_ALLOCATE ) == NO_ERROR )
  {
   ULONG Quantity = DEA_GET_ATTRS;

   bzero( Descriptions, Descriptions_size );
   DosEnumAttribute( ENUMEA_REFTYPE_PATH, File_name, 1, Descriptions, Descriptions_size, &Quantity, ENUMEA_LEVEL_NO_VALUE );

   if( !Quantity )
    {
     DosFreeMem( Descriptions ); Descriptions = NULL;
    }
   else
    {
     INT Name_length = strlen( EA_Name );

     // �������� ����� ࠧ��� �����, ���⮬� �믮��塞 ���� ��ப�.
     BYTE Success = 0; PBYTE One_byte = (PBYTE) Descriptions; INT Count;
     for( Count = 0; Count < Descriptions_size - strlen( EA_Name ) - 1; Count ++ )
      if( strcmp( &One_byte[ Count ], EA_Name ) == EQUALLY ) { Success = 1; break; }

     DosFreeMem( Descriptions ); Descriptions = NULL;

     // �᫨ �������� �������:
     if( Success )
      {
       PGEA2LIST InputData = NULL; PFEA2LIST OutputData = NULL; LONG Data_size = 16384;

       // ������ ���祭��.
       if( DosAllocMem( (PPVOID) &InputData, Data_size, PAG_ALLOCATE ) == NO_ERROR &&
           DosAllocMem( (PPVOID) &OutputData, Data_size, PAG_ALLOCATE ) == NO_ERROR )
        {
         // �ॡ����� ᢥ����� �� ����� ��ਡ��.
         bzero( InputData, Data_size );
         strcpy( InputData->list[0].szName, EA_Name );
         InputData->list[0].cbName = (BYTE) Name_length;
         InputData->cbList = sizeof( GEA2LIST ) + Name_length + 1;

         bzero( OutputData, Data_size );
         OutputData->cbList = Data_size;

         // ����砥� ���祭��.
         {
          EAOP2 Reference = { InputData, OutputData, 0 };
          DosQueryPathInfo( File_name, FIL_QUERYEASFROMLIST, &Reference, sizeof( Reference ) );
         }

         // �᫨ ��� ����祭�:
         if( OutputData->cbList )
          {
           // ������ ����� ���祭�� ࠢ��� ���.
           OutputData->list[0].cbValue = 0;

           // ���࠭塞 ��ਡ��.
           {
            EAOP2 Reference = { InputData, OutputData, 0 };
            DosSetPathInfo( File_name, FIL_QUERYEASIZE, &Reference, sizeof( Reference ), 0 );
           }
          }

         DosFreeMem( InputData ); InputData = NULL;
         DosFreeMem( OutputData ); OutputData = NULL;
        }
      }
    }
  }

 // ������.
 return;
}
