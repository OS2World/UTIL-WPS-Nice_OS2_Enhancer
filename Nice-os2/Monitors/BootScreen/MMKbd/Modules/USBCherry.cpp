// ��� ��ᯮ����� ������ Cherry CyMotion (USB) ���

ULONG DetectUSBCherryKeys( PBYTE bSeq )
{
 // ��ᯮ����� ������� "Media".
 if( bSeq[ 0 ] == 0xE0 &&
     bSeq[ 1 ] == 0x3D ) { PostEventSemaphore( MMK_USB_MEDIA ); return 1; }

 // ������.
 return 0;
}
