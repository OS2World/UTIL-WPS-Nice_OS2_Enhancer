// ��� ����頥� ���譥�� �ਫ������ � ����⨨ ������ ���

VOID PostEventSemaphore( ULONG ulKnownKeyNumber )
{
 // �⮡� ᮮ���� � ����⨨ ������, ����� ������� ᮡ�⨩�� ᥬ���,
 // ����� ������ ���� ᮧ��� ���譨� �ਫ������� (���ਬ��, � ����� ��
 // ��⮪�� Nice). ������ �������� ᥬ���.
 CHAR strSemaphoreName[ 256 ] = "";

 switch( ulKnownKeyNumber )
  {
   case MMK_POWER:           strcpy( strSemaphoreName, MMK_POWER_SEMAPHORE_NAME           ); break;
   case MMK_SLEEP:           strcpy( strSemaphoreName, MMK_SLEEP_SEMAPHORE_NAME           ); break;
   case MMK_WAKEUP:          strcpy( strSemaphoreName, MMK_WAKEUP_SEMAPHORE_NAME          ); break;
   case MMK_MAIL_READER:     strcpy( strSemaphoreName, MMK_MAIL_READER_SEMAPHORE_NAME     ); break;
   case MMK_USB_MEDIA:       strcpy( strSemaphoreName, MMK_USB_MEDIA_SEMAPHORE_NAME       ); break;
   case MMK_USB_MAIL_READER: strcpy( strSemaphoreName, MMK_USB_MAIL_READER_SEMAPHORE_NAME ); break;
   case MMK_PAGE_LEFT:       strcpy( strSemaphoreName, MMK_PAGE_LEFT_SEMAPHORE_NAME       ); break;
   case MMK_PAGE_RIGHT:      strcpy( strSemaphoreName, MMK_PAGE_RIGHT_SEMAPHORE_NAME      ); break;

   default: return;
  }

 // ����砥� ᥬ���.
 if( strSemaphoreName[ 0 ] != 0 )
  {
   HEV hSemaphore = NULLHANDLE; ULONG ulPostCount = 0;

   if( DosOpenEventSem( strSemaphoreName, &hSemaphore ) == NO_ERROR &&
       DosQueryEventSem( hSemaphore, &ulPostCount) == NO_ERROR) 
    {
     DosPostEventSem( hSemaphore );
    }

   if( hSemaphore != NULLHANDLE ) DosClose( hSemaphore );
  }

 // ������.
 return;
}
