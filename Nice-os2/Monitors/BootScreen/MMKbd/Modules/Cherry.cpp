// ─── Распознает клавиши Cherry CyMotion ───

ULONG DetectCherryKeys (PBYTE Message)
{
  // Распознаем клавишу "Mail".
  if (Message[0] == 0xE0 &&
      Message[1] == 0x6C) { PostEventSemaphore (MMK_MAIL_READER); return 1; }

  // Возврат.
  return 0;
}
