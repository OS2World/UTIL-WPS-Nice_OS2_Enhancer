// ��� �஢���� ᯨ᮪ �ਫ������ ���

VOID RepositoryChecker_CheckRepositoryEntries( VOID )
{
 // ��ᬠ�ਢ��� ᯨ᮪.
 for( INT Count = 0; Count < Repository.Length; Count ++ )
  {
   // �஢��塞, ���� �� �ਫ������.
   if( Repository.Items[ Count ].Object[ 0 ] != 0 || Repository.Items[ Count ].Path[ 0 ] != 0 )
    {
     if( !ApplicationIsExists( Repository.Items[ Count ].Application ) )
      {
       bzero( Repository.Items[ Count ].Object, SIZE_OF_NAME );
       bzero( Repository.Items[ Count ].Path, SIZE_OF_PATH );
      }
    }

   // �஢��塞, ���� �� ���箪 ��� ����.
   if( ShellIsWPS() )
    if( Repository.Items[ Count ].Object[ 0 ] != 0 )
     {
      if( QueryWPSObject( Repository.Items[ Count ].Object ) == NULLHANDLE )
       {
        bzero( Repository.Items[ Count ].Object, SIZE_OF_NAME );
       }
     }
  }

 // ������.
 return;
}
