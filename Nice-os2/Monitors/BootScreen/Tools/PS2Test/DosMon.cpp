#define INCL_KBD
#define INCL_DOSMISC
#define INCL_DOSPROCESS
#define INCL_DOSERRORS

#include <OS2.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "..\\..\\..\\Monitor.h"

void main ()
{
  HMONITOR Keyboard = NULLHANDLE;

  MONIN Monitor_input   = {0}; Monitor_input.cb = sizeof (MONIN);
  MONOUT Monitor_output = {0}; Monitor_output.cb = sizeof (MONOUT);

  APIRET RC = DosMonOpen ("KBD$", &Keyboard);

  if (RC == NO_ERROR)
  {
    ULONG Screen_session = 0;
    DosQuerySysInfo (QSV_FOREGROUND_FS_SESSION, QSV_FOREGROUND_FS_SESSION, &Screen_session, sizeof (Screen_session));
    printf ("FFSS %d\n\n", Screen_session);

    RC = DosMonReg (Keyboard, (PBYTE) &Monitor_input, (PBYTE) &Monitor_output, MONITOR_BEGIN, Screen_session);

    if (RC == NO_ERROR)
    {
      while (1)
      {
        KEYPACKET Keyboard_packet = {0};
        USHORT Packet_length = sizeof (KEYPACKET);

        RC = DosMonRead ((PBYTE) &Monitor_input, MONITOR_WAIT, (PBYTE) &Keyboard_packet, &Packet_length);
        if (RC != NO_ERROR) { printf ("[3] Error %d\n", RC); break; }

        BYTE Write_back = 1;

        {
          BYTE Scan_code = Keyboard_packet.ScanCode;
          printf ("[%02x]", Scan_code);

          BYTE Message[256] = {0};
          memcpy (Message, &Keyboard_packet, sizeof (Keyboard_packet));
          for (INT Cntr = 0; Cntr < sizeof (Keyboard_packet); Cntr ++) { printf (" %02x", Message[Cntr]); }

          BYTE Ext_1 = 0;   if (Scan_code == 0xE0) Ext_1 = 1;
          BYTE Ext_2 = 0;   if (Scan_code == 0xE1) Ext_2 = 1;
          BYTE Release = 0; if (!Ext_1 && !Ext_2 && (Scan_code & 0x80)) Release = 1;

          if (Release) printf ("\n");
          printf ("\n");
        }

        if (Write_back)
        {
          RC = DosMonWrite ((PBYTE) &Monitor_output, (PBYTE) &Keyboard_packet, Packet_length);
          if (RC != NO_ERROR) break;
        }
      }
    }
    else
    {
      printf ("[2] Error %d\n", RC);
    }

    RC = DosMonClose (Keyboard); Keyboard = NULLHANDLE;

    if (RC != NO_ERROR)
    {
      printf ("[5] Error %d\n", RC);
    }
  }
  else
  {
    printf ("[1] Error %d\n", RC);
  }

  DosExit (EXIT_PROCESS, 0);
}
