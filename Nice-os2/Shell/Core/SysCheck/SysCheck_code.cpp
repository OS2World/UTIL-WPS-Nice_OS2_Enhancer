
// ��� �஢���� ����ன�� PM � ��⠢��� ������ � ���� "Log" ���

VOID SysCheck_CheckPMSettingsAndWriteLog (VOID)
{
  // �஢��塞 ����ன�� "Restart Objects" �����窨 WPS.
  BYTE RestartObjects_is_correct = 1;

  PCHAR RestartObjects_ptr = NULL; DosScanEnv ("RESTARTOBJECTS", (PPCSZ) &RestartObjects_ptr);
  if (RestartObjects_ptr == NULL) RestartObjects_is_correct = 0;
  else if (!strstr ("STARTUPFOLDERSONLY", RestartObjects_ptr)) RestartObjects_is_correct = 0;

  if (!RestartObjects_is_correct)
  {
    if (Enhancer.Code_page == RUSSIAN) PrintLogMessage (StrConst_RU_Pages_Log_RestartObjects);
    else PrintLogMessage (StrConst_EN_Pages_Log_RestartObjects);
  }

  // ������.
  return;
}

// ��� �஢���� ����ன�� ���������筮�� � ��⠢��� ������ � ���� "Log" ���

VOID SysCheck_CheckPrioritySettingsAndWriteLog (VOID)
{
  // �஢��塞 ����ன�� "PRIORITY=ABSOLUTE/DYNAMIC".
  ULONG Dynamic_priority = 0; DosQuerySysInfo (QSV_DYN_PRI_VARIATION, QSV_DYN_PRI_VARIATION, (PULONG) &Dynamic_priority, sizeof (Dynamic_priority));

  if (Dynamic_priority)
  {
    if (Enhancer.Code_page == RUSSIAN) PrintLogMessage (StrConst_RU_Pages_Log_DynamicPriority);
    else PrintLogMessage (StrConst_EN_Pages_Log_DynamicPriority);
  }

  // ������.
  return;
}

// ��� �������� � ���� "Log" �������饥 ᮮ�饭�� ���

VOID SysCheck_AddCompletiveLogMessage (VOID)
{
  // ������塞 ᮮ�饭�� � ⮬, �� �� ����易⥫�� �ॡ������.
  if (!LogIsEmpty ())
  {
    if (Enhancer.Code_page == RUSSIAN) PrintLogMessage (StrConst_RU_Pages_Log_Note);
    else PrintLogMessage (StrConst_RU_Pages_Log_Note);
  }

  // ������.
  return;
}
