// ─── Проверяет список приложений ───

VOID RepositoryChecker_CheckRepositoryEntries( VOID )
{
 // Просматриваем список.
 for( INT Count = 0; Count < Repository.Length; Count ++ )
  {
   // Проверяем, есть ли приложение.
   if( Repository.Items[ Count ].Object[ 0 ] != 0 || Repository.Items[ Count ].Path[ 0 ] != 0 )
    {
     if( !ApplicationIsExists( Repository.Items[ Count ].Application ) )
      {
       bzero( Repository.Items[ Count ].Object, SIZE_OF_NAME );
       bzero( Repository.Items[ Count ].Path, SIZE_OF_PATH );
      }
    }

   // Проверяем, есть ли значок для него.
   if( ShellIsWPS() )
    if( Repository.Items[ Count ].Object[ 0 ] != 0 )
     {
      if( QueryWPSObject( Repository.Items[ Count ].Object ) == NULLHANDLE )
       {
        bzero( Repository.Items[ Count ].Object, SIZE_OF_NAME );
       }
     }
  }

 // Возврат.
 return;
}
