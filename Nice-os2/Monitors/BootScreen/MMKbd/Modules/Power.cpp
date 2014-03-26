// ��� ��ᯮ����� ������ �ࠢ����� ��⠭��� ���

ULONG DetectPowerKeys( PBYTE bSeq )
{
 // ��ᯮ����� ������� "Power".
 if( bSeq[ 0 ] == 0xE0 &&
     bSeq[ 1 ] == 0x5E ) { PostEventSemaphore( MMK_POWER ); return 1; }

 // ��ᯮ����� ������� "Sleep".
 if( bSeq[ 0 ] == 0xE0 &&
     bSeq[ 1 ] == 0x5F ) { PostEventSemaphore( MMK_SLEEP ); return 1; }

 // ��ᯮ����� ������� "WakeUp". ����� �� ���� ���뫠�� ������ "Fn" �� ��������� ThinkPad.
 if( bSeq[ 0 ] == 0xE0 &&
     bSeq[ 1 ] == 0x63 ) { PostEventSemaphore( MMK_WAKEUP ); return 1; }

 // ������.
 return 0;
}
