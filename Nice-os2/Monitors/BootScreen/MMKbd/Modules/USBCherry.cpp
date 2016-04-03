// ─── Распознает клавиши Cherry CyMotion (USB) ───

ULONG DetectUSBCherryKeys (PBYTE Message)
{
  // Распознаем клавишу "Media".
  if (Message[0] == 0xE0 &&
      Message[1] == 0x3D) { PostEventSemaphore (MMK_MEDIA_PLAYER); return 1; }

  // Возврат.
  return 0;
}
