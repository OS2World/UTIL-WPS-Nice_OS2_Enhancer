// ��� ��ᯮ����� ������ Cherry CyMotion ���

ULONG DetectCherryKeys (PBYTE Message)
{
  // ��ᯮ����� ������� "Mail".
  if (Message[0] == 0xE0 &&
      Message[1] == 0x6C) { PostEventSemaphore (MMK_MAIL_READER); return 1; }

  // ������.
  return 0;
}
