// ��� ��ᯮ����� ������ ThinkPad ���

ULONG DetectThinkPadKeys (PBYTE Message)
{
  // ��ᯮ����� ������� "PageLeft".
  if (Message[0] == 0xE0 &&
      Message[1] == 0x6A) { PostEventSemaphore (MMK_PAGE_LEFT); return 1; }

  // ��ᯮ����� ������� "PageRight".
  if (Message[0] == 0xE0 &&
      Message[1] == 0x69) { PostEventSemaphore (MMK_PAGE_RIGHT); return 1; }

  // ������.
  return 0;
}
