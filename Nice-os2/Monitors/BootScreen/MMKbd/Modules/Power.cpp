// ─── Распознает клавиши управления питанием ───

ULONG DetectPowerKeys( PBYTE bSeq )
{
 // Распознаем клавишу "Power".
 if( bSeq[ 0 ] == 0xE0 &&
     bSeq[ 1 ] == 0x5E ) { PostEventSemaphore( MMK_POWER ); return 1; }

 // Распознаем клавишу "Sleep".
 if( bSeq[ 0 ] == 0xE0 &&
     bSeq[ 1 ] == 0x5F ) { PostEventSemaphore( MMK_SLEEP ); return 1; }

 // Распознаем клавишу "WakeUp". Такие же коды присылает клавиша "Fn" на клавиатуре ThinkPad.
 if( bSeq[ 0 ] == 0xE0 &&
     bSeq[ 1 ] == 0x63 ) { PostEventSemaphore( MMK_WAKEUP ); return 1; }

 // Возврат.
 return 0;
}
