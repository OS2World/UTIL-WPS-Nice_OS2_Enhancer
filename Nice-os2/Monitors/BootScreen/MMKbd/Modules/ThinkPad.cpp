// ��� ��ᯮ����� ������ ThinkPad ���

ULONG DetectThinkPadKeys( PBYTE bSeq )
{
 // ��ᯮ����� ������� "PageLeft".
 if( bSeq[ 0 ] == 0xE0 &&
     bSeq[ 1 ] == 0x6A ) { PostEventSemaphore( MMK_PAGE_LEFT ); return 1; }

 // ��ᯮ����� ������� "PageRight".
 if( bSeq[ 0 ] == 0xE0 &&
     bSeq[ 1 ] == 0x69 ) { PostEventSemaphore( MMK_PAGE_RIGHT ); return 1; }

 // ������.
 return 0;
}
