// ─── Распознает клавиши ThinkPad ───

ULONG DetectThinkPadKeys (PBYTE Message)
{
  // Распознаем клавишу "PageLeft".
  if (Message[0] == 0xE0 &&
      Message[1] == 0x6A) { PostEventSemaphore (MMK_PAGE_LEFT); return 1; }

  // Распознаем клавишу "PageRight".
  if (Message[0] == 0xE0 &&
      Message[1] == 0x69) { PostEventSemaphore (MMK_PAGE_RIGHT); return 1; }

  // Возврат.
  return 0;
}
