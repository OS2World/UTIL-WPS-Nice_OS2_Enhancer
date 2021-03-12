
  INT Quantity = 6;          
  SEMRECORD Semaphores[6] = {0};
  BYTE Scan_codes[6]      = {0};
  CHAR Char_codes[6]      = {0};

  INT Position = -1;

  {
    Position ++; HEV KSem_Power = NULLHANDLE;
    if (DosCreateEventSem (MMK_POWER_SEMAPHORE_NAME, &KSem_Power, DC_SEM_SHARED, 0) == NO_ERROR) 
    {
      Semaphores[Position].hsemCur = (HSEM) KSem_Power;
      Semaphores[Position].ulUser = Position;
      Scan_codes[Position] = SC_ACPI_POWER;
      Char_codes[Position] = 'P';
    }
  }

  {
    Position ++; HEV KSem_Sleep = NULLHANDLE;
    if (DosCreateEventSem (MMK_SLEEP_SEMAPHORE_NAME, &KSem_Sleep, DC_SEM_SHARED, 0) == NO_ERROR) 
    {
      Semaphores[Position].hsemCur = (HSEM) KSem_Sleep;
      Semaphores[Position].ulUser = Position;
      Scan_codes[Position] = SC_ACPI_SLEEP;
      Char_codes[Position] = 'S';
    }
  }

  {
    Position ++; HEV KSem_MailReader = NULLHANDLE;
    if (DosCreateEventSem (MMK_MAIL_READER_SEMAPHORE_NAME, &KSem_MailReader, DC_SEM_SHARED, 0) == NO_ERROR) 
    {
      Semaphores[Position].hsemCur = (HSEM) KSem_MailReader;
      Semaphores[Position].ulUser = Position;
      Scan_codes[Position] = SC_APP_MAIL_READER;
      Char_codes[Position] = 'M';
    }
  }

  {
    Position ++; HEV KSem_MediaPlayer = NULLHANDLE;
    if (DosCreateEventSem (MMK_MEDIA_PLAYER_SEMAPHORE_NAME, &KSem_MediaPlayer, DC_SEM_SHARED, 0) == NO_ERROR) 
    {
      Semaphores[Position].hsemCur = (HSEM) KSem_MediaPlayer;
      Semaphores[Position].ulUser = Position;
      Scan_codes[Position] = SC_MM_MEDIA;
      Char_codes[Position] = 'M';
    }
  }

  {
    Position ++; HEV KSem_USBPageLeft = NULLHANDLE;
    if (DosCreateEventSem (MMK_PAGE_LEFT_SEMAPHORE_NAME, &KSem_USBPageLeft, DC_SEM_SHARED, 0) == NO_ERROR) 
    {
      Semaphores[Position].hsemCur = (HSEM) KSem_USBPageLeft;
      Semaphores[Position].ulUser = Position;
      Scan_codes[Position] = SC_PAGE_LEFT;
      Char_codes[Position] = 'L';
    }
  }

  {
    Position ++; HEV KSem_USBPageRight = NULLHANDLE;
    if (DosCreateEventSem (MMK_PAGE_RIGHT_SEMAPHORE_NAME, &KSem_USBPageRight, DC_SEM_SHARED, 0) == NO_ERROR) 
    {
      Semaphores[Position].hsemCur = (HSEM) KSem_USBPageRight;
      Semaphores[Position].ulUser = Position;
      Scan_codes[Position] = SC_PAGE_RIGHT;
      Char_codes[Position] = 'R';
    }
  }
