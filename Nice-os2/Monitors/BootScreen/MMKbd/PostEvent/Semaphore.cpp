// ��� ����頥� ���譥�� �ਫ������ � ����⨨ ������ ���

VOID PostEventSemaphore (ULONG Known_key_number)
{
  // �⮡� ᮮ���� � ����⨨ ������, ����� ������� ᮡ�⨩�� ᥬ���,
  // ����� ������ ���� ᮧ��� ���譨� �ਫ������� (���ਬ��, � ����� ��
  // ��⮪�� Nice). ������ �������� ᥬ���.
  CHAR Semaphore_name[256] = "";

  switch (Known_key_number)
  {
    case MMK_POWER:           strcpy (Semaphore_name, MMK_POWER_SEMAPHORE_NAME           ); break;
    case MMK_SLEEP:           strcpy (Semaphore_name, MMK_SLEEP_SEMAPHORE_NAME           ); break;
    case MMK_MAIL_READER:     strcpy (Semaphore_name, MMK_MAIL_READER_SEMAPHORE_NAME     ); break;
    case MMK_MEDIA_PLAYER:    strcpy (Semaphore_name, MMK_MEDIA_PLAYER_SEMAPHORE_NAME    ); break;
    case MMK_PAGE_LEFT:       strcpy (Semaphore_name, MMK_PAGE_LEFT_SEMAPHORE_NAME       ); break;
    case MMK_PAGE_RIGHT:      strcpy (Semaphore_name, MMK_PAGE_RIGHT_SEMAPHORE_NAME      ); break;

    default: return;
  }

  // ����砥� ᥬ���.
  if (Semaphore_name[0] != 0)
  {
    HEV Semaphore = NULLHANDLE; ULONG Post_count = 0;

    if (DosOpenEventSem (Semaphore_name, &Semaphore) == NO_ERROR &&
        DosQueryEventSem (Semaphore, &Post_count) == NO_ERROR)
    {
      APIRET RC = DosPostEventSem (Semaphore);
    }

    if (Semaphore != NULLHANDLE) DosClose (Semaphore);
  }

  // ������.
  return;
}
