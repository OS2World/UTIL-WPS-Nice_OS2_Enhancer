#define INCL_KBD
#define INCL_DOS
#define INCL_DOSMISC
#define INCL_DOSPROCESS
#define INCL_DOSERRORS

#include <OS2.h>
#include "..\Tools\PS2Test\DosMon.h"

#include "..\\..\\..\\..\\Nice-os2\\Shared\\General.h"

#include "..\\..\\..\\..\\Nice-os2\\Shared\\Strings.h"
#include "..\\..\\..\\..\\Nice-os2\\Shared\\Strings\\Strings_data.cpp"
#include "..\\..\\..\\..\\Nice-os2\\Shared\\Strings\\Strings_code.cpp"
#include "..\\..\\..\\..\\Nice-os2\\Shared\\Strings.cpp"

#include "..\\..\\..\\..\\Nice-os2\\Shared\\MMKeys.h"
#include "PostEvent\Semaphore.cpp"

#include "Modules\Power.cpp"
#include "Modules\Cherry.cpp"
#include "Modules\ThinkPad.cpp"
#include "Modules\USBCherry.cpp"

#ifdef DEBUG_VERSION
#include <stdio.h>
#include "Debug\\Log.cpp"
#include "..\\..\\..\\..\\Nice-os2\\Kernel\\Core\\Debug\\Debug_code.cpp"
#include "..\\..\\..\\..\\Nice-os2\\Kernel\\Core\\Debug.cpp"
#endif

VOID main( VOID )
{
 // Если приложение уже есть - выход.
 {
  CHAR Semaphore_name[] = "\\SEM32\\MMKbd";
  HMTX hmtxAlreadyRunning = NULLHANDLE;

  if( DosOpenMutexSem( Semaphore_name, &hmtxAlreadyRunning ) == NO_ERROR )
   DosExit( EXIT_PROCESS, 0 );
  else
   DosCreateMutexSem( Semaphore_name, &hmtxAlreadyRunning, DC_SEM_SHARED, 1 );
 }

 // Ждем появления оконной оболочки.
 while( 1 )
  {
   ULONG ulSessionId = 0;
   DosQuerySysInfo( QSV_FOREGROUND_FS_SESSION, QSV_FOREGROUND_FS_SESSION, &ulSessionId, sizeof( ulSessionId ) );

   if( ulSessionId == MONITOR_SESSION_PM ) break;
   else DosSleep( 1000 );
  }

 // Присоединяемся к драйверу клавиатуры.
 HMONITOR hmonKbd = NULLHANDLE;

 MONIN monInBuf;   memset( &monInBuf, 0, sizeof( MONIN ) );   monInBuf.cb = sizeof( MONIN );
 MONOUT monOutBuf; memset( &monOutBuf, 0, sizeof( MONOUT ) ); monOutBuf.cb = sizeof( MONOUT );

 APIRET RC = DosMonOpen( "KBD$", &hmonKbd );

 if( RC == NO_ERROR )
  {
   // Включаем слежение за оконной оболочкой.
   ULONG ulSessionId = MONITOR_SESSION_PM;

   for( INT iStep = 0; iStep < 12 * 60; iStep ++ )
    {
     RC = DosMonReg( hmonKbd, (PBYTE) &monInBuf, (PBYTE) &monOutBuf, MONITOR_BEGIN, ulSessionId );
     if( RC == NO_ERROR ) break;

     DosSleep( 1000 );
    }

   if( RC == NO_ERROR )
    {
     // Распознаем клавиши.
     BYTE bSequence[ 4 ] = {0};
     INT iSeqCount = 0;

     while( 1 )
      {
       USHORT usCount = sizeof( KEYPACKET );
       KEYPACKET kbdKeyBuf; memset( &kbdKeyBuf, 0, sizeof( KEYPACKET ) );

       RC = DosMonRead( (PBYTE) &monInBuf, MONITOR_WAIT, (PBYTE) &kbdKeyBuf, &usCount );
       if( RC != NO_ERROR ) break;

       BYTE bWriteKeyPacket = 1;

       {
        BYTE bScanCode = kbdKeyBuf.mnflags >> 8;

        BYTE bExt_1 = 0; if( bScanCode == 0xE0 ) bExt_1 = 1;
        BYTE bExt_2 = 0; if( bScanCode == 0xE1 ) bExt_2 = 1;
        BYTE bRelease = 0;  if( !bExt_1 && !bExt_2 && ( bScanCode & 0x80 ) ) bRelease = 1;

        bSequence[ iSeqCount ] = bScanCode; iSeqCount ++;
        if( bRelease || iSeqCount == 4 ) iSeqCount = 0;

        if( iSeqCount == 0 ) bSequence[ 0 ] = bSequence[ 1 ] = bSequence[ 2 ] = bSequence[ 3 ] = 0;
       }

       if( iSeqCount == 2 && bSequence[ 0 ] == 0xE0 )
        {
         #ifdef DEBUG_VERSION
         CHAR String[ 255 ] = "";
         sprintf( String, "-> %02x\n", bSequence[ 1 ] ); Log( String ); Bzz();
         #endif

         ULONG bSuccess = 0;

         if( !bSuccess ) bSuccess = DetectPowerKeys( bSequence );
         if( !bSuccess ) bSuccess = DetectCherryKeys( bSequence );
         if( !bSuccess ) bSuccess = DetectThinkPadKeys( bSequence );
         if( !bSuccess ) bSuccess = DetectUSBCherryKeys( bSequence );

         if( bSuccess ) bWriteKeyPacket = 0;
        }

       if( bWriteKeyPacket )
        {
         RC = DosMonWrite( (PBYTE) &monOutBuf, (PBYTE) &kbdKeyBuf, usCount );
         if( RC != NO_ERROR ) break;
        }
      }
    }

   // Отключаемся от драйвера.
   DosMonClose( hmonKbd ); hmonKbd = NULLHANDLE;
  }

 // Выход.
 DosExit( EXIT_PROCESS, 0 );
}
