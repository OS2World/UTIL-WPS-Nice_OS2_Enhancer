#define INCL_KBD
#define INCL_DOSMISC
#define INCL_DOSPROCESS
#define INCL_DOSERRORS

#include <OS2.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "DosMon.h"

VOID main( VOID )
{
 HMONITOR hmonKbd = NULLHANDLE;

 MONIN monInBuf;   memset( &monInBuf, 0, sizeof( MONIN ) );   monInBuf.cb = sizeof( MONIN );
 MONOUT monOutBuf; memset( &monOutBuf, 0, sizeof( MONOUT ) ); monOutBuf.cb = sizeof( MONOUT );

 APIRET RC = DosMonOpen( "KBD$", &hmonKbd );

 if( RC == NO_ERROR )
  {
   ULONG ulSessionId = 0;
   DosQuerySysInfo( QSV_FOREGROUND_FS_SESSION, QSV_FOREGROUND_FS_SESSION, &ulSessionId, sizeof( ulSessionId ) );
   printf( "FFSS %d\n\n", ulSessionId );

   RC = DosMonReg( hmonKbd, (PBYTE) &monInBuf, (PBYTE) &monOutBuf, MONITOR_BEGIN, ulSessionId );

   if( RC == NO_ERROR )
    {
     while( 1 )
      {
       USHORT usCount = sizeof( KEYPACKET );
       KEYPACKET kbdKeyBuf; memset( &kbdKeyBuf, 0, sizeof( KEYPACKET ) );

       RC = DosMonRead( (PBYTE) &monInBuf, MONITOR_WAIT, (PBYTE) &kbdKeyBuf, &usCount );
       if( RC != NO_ERROR ) { printf( "[3] Error %d\n", RC ); break; }

       BYTE bWriteKeyPacket = 1;

       {
        BYTE bScanCode = kbdKeyBuf.mnflags >> 8;
        printf( "[ %02x ]", bScanCode );

        BYTE aData[ 256 ];
        memset( aData, 0, sizeof( aData ) );
        memcpy( aData, &kbdKeyBuf, sizeof( kbdKeyBuf ) );
        for( INT i = 0; i < sizeof( kbdKeyBuf ); i++ ) { printf( " %02x", aData[ i ] ); }

        BYTE bExt_1 = 0; if( bScanCode == 0xE0 ) bExt_1 = 1;
        BYTE bExt_2 = 0; if( bScanCode == 0xE1 ) bExt_2 = 1;
        BYTE bRelease = 0;  if( !bExt_1 && !bExt_2 && ( bScanCode & 0x80 ) ) bRelease = 1;

        if( bRelease ) printf( "\n");
        printf( "\n");
       }

       if( bWriteKeyPacket )
        {
         RC = DosMonWrite( (PBYTE) &monOutBuf, (PBYTE) &kbdKeyBuf, usCount );
         if( RC != NO_ERROR ) break;
        }
      }
    }
   else
    {
     printf( "[2] Error %d\n", RC );
    }

   RC = DosMonClose( hmonKbd ); hmonKbd = NULLHANDLE;

   if( RC != NO_ERROR )
    {
     printf( "[5] Error %d\n", RC );
    }
  }
 else
  {
   printf( "[1] Error %d\n", RC );
  }

 DosExit( EXIT_PROCESS, 0 );
}