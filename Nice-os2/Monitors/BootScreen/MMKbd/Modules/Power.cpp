// ��� ��ᯮ����� ������ �ࠢ����� ��⠭��� ���

ULONG DetectPowerKeys (PBYTE Message)
{
  // ��ᯮ����� ������� "Power".
  if (Message[0] == 0xE0 &&
      Message[1] == 0x5E) { PostEventSemaphore (MMK_POWER); return 1; }

  // ��ᯮ����� ������� "Sleep".
  if (Message[0] == 0xE0 &&
      Message[1] == 0x5F) { PostEventSemaphore (MMK_SLEEP); return 1; }

  // ������.
  return 0;
}
