
 INT Quantity = 8;          INT Position = 0;
 SEMRECORD Semaphores[ 8 ]; bzero( Semaphores, sizeof( Semaphores ) );
 BYTE Scan_codes[ 8 ];      bzero( Scan_codes, sizeof( Scan_codes ) );
 CHAR Char_codes[ 8 ];      bzero( Char_codes, sizeof( Char_codes ) ); 

 {
  Position = 0; HEV KSem_Power = NULLHANDLE;
  if( DosCreateEventSem( MMK_POWER_SEMAPHORE_NAME, &KSem_Power, DC_SEM_SHARED, 0 ) == NO_ERROR ) 
   {
    Semaphores[ Position ].hsemCur = (HSEM) KSem_Power;
    Semaphores[ Position ].ulUser = Position + 1;
    Scan_codes[ Position ] = SC_ACPI_POWER;
    Char_codes[ Position ] = 'P';
   }
 }

 {
  Position = 1; HEV KSem_Sleep = NULLHANDLE;
  if( DosCreateEventSem( MMK_SLEEP_SEMAPHORE_NAME, &KSem_Sleep, DC_SEM_SHARED, 0 ) == NO_ERROR ) 
   {
    Semaphores[ Position ].hsemCur = (HSEM) KSem_Sleep;
    Semaphores[ Position ].ulUser = Position + 1;
    Scan_codes[ Position ] = SC_ACPI_SLEEP;
    Char_codes[ Position ] = 'S';
   }
 }

 {
  Position = 2; HEV KSem_WakeUp = NULLHANDLE;
  if( DosCreateEventSem( MMK_WAKEUP_SEMAPHORE_NAME, &KSem_WakeUp, DC_SEM_SHARED, 0 ) == NO_ERROR ) 
   {
    Semaphores[ Position ].hsemCur = (HSEM) KSem_WakeUp;
    Semaphores[ Position ].ulUser = Position + 1;
    Scan_codes[ Position ] = SC_ACPI_WAKE_UP;
    Char_codes[ Position ] = 'W';
   }
 }

 {
  Position = 3; HEV KSem_MailReader = NULLHANDLE;
  if( DosCreateEventSem( MMK_MAIL_READER_SEMAPHORE_NAME, &KSem_MailReader, DC_SEM_SHARED, 0 ) == NO_ERROR ) 
   {
    Semaphores[ Position ].hsemCur = (HSEM) KSem_MailReader;
    Semaphores[ Position ].ulUser = Position + 1;
    Scan_codes[ Position ] = SC_APP_MAIL_READER;
    Char_codes[ Position ] = 'M';
   }
 }

 {
  Position = 4; HEV KSem_USBMedia = NULLHANDLE;
  if( DosCreateEventSem( MMK_USB_MEDIA_SEMAPHORE_NAME, &KSem_USBMedia, DC_SEM_SHARED, 0 ) == NO_ERROR ) 
   {
    Semaphores[ Position ].hsemCur = (HSEM) KSem_USBMedia;
    Semaphores[ Position ].ulUser = Position + 1;
    Scan_codes[ Position ] = SC_MM_MEDIA;
    Char_codes[ Position ] = 'M';
   }
 }

 {
  Position = 5; HEV KSem_USBMailReader = NULLHANDLE;
  if( DosCreateEventSem( MMK_USB_MAIL_READER_SEMAPHORE_NAME, &KSem_USBMailReader, DC_SEM_SHARED, 0 ) == NO_ERROR ) 
   {
    Semaphores[ Position ].hsemCur = (HSEM) KSem_USBMailReader;
    Semaphores[ Position ].ulUser = Position + 1;
    Scan_codes[ Position ] = SC_APP_MAIL_READER;
    Char_codes[ Position ] = 'M';
   }
 }

 {
  Position = 6; HEV KSem_USBPageLeft = NULLHANDLE;
  if( DosCreateEventSem( MMK_PAGE_LEFT_SEMAPHORE_NAME, &KSem_USBPageLeft, DC_SEM_SHARED, 0 ) == NO_ERROR ) 
   {
    Semaphores[ Position ].hsemCur = (HSEM) KSem_USBPageLeft;
    Semaphores[ Position ].ulUser = Position + 1;
    Scan_codes[ Position ] = SC_PAGE_LEFT;
    Char_codes[ Position ] = 'L';
   }
 }

 {
  Position = 7; HEV KSem_USBPageRight = NULLHANDLE;
  if( DosCreateEventSem( MMK_PAGE_RIGHT_SEMAPHORE_NAME, &KSem_USBPageRight, DC_SEM_SHARED, 0 ) == NO_ERROR ) 
   {
    Semaphores[ Position ].hsemCur = (HSEM) KSem_USBPageRight;
    Semaphores[ Position ].ulUser = Position + 1;
    Scan_codes[ Position ] = SC_PAGE_RIGHT;
    Char_codes[ Position ] = 'R';
   }
 }
