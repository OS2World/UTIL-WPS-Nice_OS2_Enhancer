// ��� ��ᯮ����� ������ Cherry CyMotion (USB) ���

ULONG DetectUSBCherryKeys (PBYTE Message)
{
  // ��ᯮ����� ������� "Media".
  if (Message[0] == 0xE0 &&
      Message[1] == 0x3D) { PostEventSemaphore (MMK_MEDIA_PLAYER); return 1; }

  // ������.
  return 0;
}
