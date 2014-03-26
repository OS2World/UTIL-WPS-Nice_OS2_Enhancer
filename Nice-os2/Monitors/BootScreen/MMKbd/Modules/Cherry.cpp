// ─── Распознает клавиши Cherry CyMotion ───

ULONG DetectCherryKeys( PBYTE bSeq )
{
 // Распознаем клавишу "Mail".
 if( bSeq[ 0 ] == 0xE0 &&
     bSeq[ 1 ] == 0x6C ) { PostEventSemaphore( MMK_MAIL_READER ); return 1; }

 // Возврат.
 return 0;
}
