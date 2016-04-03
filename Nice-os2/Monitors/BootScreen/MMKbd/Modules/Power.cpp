// ─── Распознает клавиши управления питанием ───

ULONG DetectPowerKeys (PBYTE Message)
{
  // Распознаем клавишу "Power".
  if (Message[0] == 0xE0 &&
      Message[1] == 0x5E) { PostEventSemaphore (MMK_POWER); return 1; }

  // Распознаем клавишу "Sleep".
  if (Message[0] == 0xE0 &&
      Message[1] == 0x5F) { PostEventSemaphore (MMK_SLEEP); return 1; }

  // Возврат.
  return 0;
}
