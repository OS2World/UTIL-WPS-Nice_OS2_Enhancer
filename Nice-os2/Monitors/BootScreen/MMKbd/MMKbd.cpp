#define INCL_KBD
#define INCL_DOS
#define INCL_DOSMISC
#define INCL_DOSPROCESS
#define INCL_DOSERRORS

#include <OS2.h>
#include "..\\..\\Monitor.h"

#include "..\\..\\..\\..\\Nice-os2\\Shared\\General.h"
#pragma pack(4)

#include "..\\..\\..\\..\\Nice-os2\\Shared\\Strings.h"
#include "..\\..\\..\\..\\Nice-os2\\Shared\\Strings\\Strings_data.cpp"
#include "..\\..\\..\\..\\Nice-os2\\Shared\\Strings\\Strings_code.cpp"
#include "..\\..\\..\\..\\Nice-os2\\Shared\\Strings.cpp"

#include "..\\..\\..\\..\\Nice-os2\\Shared\\MMKeys.h"

#ifdef DEBUG_VERSION
#include <stdio.h>
#include "Debug\\Log.cpp"
#include "..\\..\\..\\..\\Nice-os2\\Kernel\\Core\\Debug\\Debug_code.cpp"
#include "..\\..\\..\\..\\Nice-os2\\Kernel\\Core\\Debug.cpp"
#endif

#include "PostEvent\Semaphore.cpp"

#include "Modules\Power.cpp"
#include "Modules\Cherry.cpp"
#include "Modules\ThinkPad.cpp"
#include "Modules\USBCherry.cpp"

#define THREAD_STACK_SIZE 16384
#define SCREEN_SESSIONS   16

typedef struct _threadrc
{
  HMONITOR Keyboard;
  ULONG Screen_session;
  ULONG Thread_ID;
} THREADRC; typedef _threadrc* PTHREADRC;

VOID APIENTRY ThreadProc (ULONG Thread_parameter)
{
  // Включаем слежение за клавиатурой.
  MONIN Monitor_input   = {0}; Monitor_input.cb  = sizeof (MONIN);
  MONOUT Monitor_output = {0}; Monitor_output.cb = sizeof (MONOUT);

  PTHREADRC Pointer = (PTHREADRC) Thread_parameter;

  APIRET RC = NO_ERROR;

  for (ULONG Step = 0; Step < 25; Step ++)
  {
    RC = DosMonReg (Pointer->Keyboard, (PBYTE) &Monitor_input, (PBYTE) &Monitor_output, MONITOR_BEGIN, Pointer->Screen_session);
    if (RC == NO_ERROR) break;

    DosSleep (1000);
  }

  if (RC == NO_ERROR)
  {
    // Распознаем клавиши.
    BYTE Message[4] = {0}; INT Byte_offset = 0;

    while (1)
    {
      KEYPACKET Keyboard_packet = {0};
      USHORT Packet_length = sizeof (KEYPACKET);

      RC = DosMonRead ((PBYTE) &Monitor_input, MONITOR_WAIT, (PBYTE) &Keyboard_packet, &Packet_length);
      if (RC != NO_ERROR) break;

      BYTE Write_back = 1;

      {
        BYTE Scan_code = Keyboard_packet.ScanCode;

        BYTE Ext_1 = 0;   if (Scan_code == 0xE0) Ext_1 = 1;
        BYTE Ext_2 = 0;   if (Scan_code == 0xE1) Ext_2 = 1;
        BYTE Release = 0; if (!Ext_1 && !Ext_2 && (Scan_code & 0x80)) Release = 1;

        Message[Byte_offset] = Scan_code; Byte_offset ++;
        if (Release || Byte_offset == 4) Byte_offset = 0;

        if (Byte_offset == 0) { Message[0] = 0; Message[1] = 0; Message[2] = 0; Message[3] = 0; }
      }

      if (Byte_offset == 2 && Message[0] == 0xE0)
      {
        #ifdef DEBUG_VERSION
        CHAR String[255] = "";
        sprintf (String, "-> %02x\n", Message[1]); /* Log (String); Bzz (); */
        #endif

        ULONG Success = 0;

        if (!Success) Success = DetectPowerKeys (Message);
        if (!Success) Success = DetectCherryKeys (Message);
        if (!Success) Success = DetectThinkPadKeys (Message);
        if (!Success) Success = DetectUSBCherryKeys (Message);

        if (Success) Write_back = 0;
      }

      if (Write_back)
      {
        RC = DosMonWrite ((PBYTE) &Monitor_output, (PBYTE) &Keyboard_packet, Packet_length);
        if (RC != NO_ERROR) break;
      }
    }
  }

  // Завершаем поток.
  DosExit (EXIT_THREAD, 0);
}

void main ()
{
  // Если приложение уже есть - выход.
  {
    CHAR Semaphore_name[] = "\\SEM32\\MMKbd";
    HMTX Already_running = NULLHANDLE;

    if (DosOpenMutexSem (Semaphore_name, &Already_running) == NO_ERROR)
     DosExit (EXIT_PROCESS, 0);
    else
     DosCreateMutexSem (Semaphore_name, &Already_running, DC_SEM_SHARED, 1);
  }

  // Ждем появления оконной оболочки.
  /* -
  ULONG Boot_screen_session = 0;
  DosQuerySysInfo (QSV_FOREGROUND_FS_SESSION, QSV_FOREGROUND_FS_SESSION, &Boot_screen_session, sizeof (Boot_screen_session));

  while (1)
   {
    ULONG Screen_session = 0;
    DosQuerySysInfo (QSV_FOREGROUND_FS_SESSION, QSV_FOREGROUND_FS_SESSION, &Screen_session, sizeof (Screen_session));

    if (Screen_session != Boot_screen_session) break;
    else DosSleep (1000);
   }
  - */

  // Присоединяемся к драйверу клавиатуры.
  HMONITOR Keyboard_monitor = NULLHANDLE; APIRET RC = DosMonOpen ("KBD$", &Keyboard_monitor);

  if (RC == NO_ERROR)
  {
    // Включаем слежение за клавиатурой.
    THREADRC Threads[SCREEN_SESSIONS] = {0};

    for (ULONG Screen_session_number = 0; Screen_session_number < SCREEN_SESSIONS; Screen_session_number ++)
    {
      Threads[Screen_session_number].Keyboard = Keyboard_monitor;
      Threads[Screen_session_number].Screen_session = Screen_session_number;

      DosCreateThread (&Threads[Screen_session_number].Thread_ID, (PFNTHREAD) ThreadProc, (ULONG) &Threads[Screen_session_number], 0, THREAD_STACK_SIZE);
    }

    // Останавливаем поток до тех пор, пока работают другие потоки.
    PPIB Process_IB = NULL; PTIB Thread_IB = NULL; DosGetInfoBlocks (&Thread_IB, &Process_IB);

    while (1)
    {
      ULONG Other_threads_exists = 0;

      for (ULONG Screen_session_number = 0; Screen_session_number < SCREEN_SESSIONS; Screen_session_number ++)
      {
        if (DosVerifyPidTid (Process_IB->pib_ulpid, Threads[Screen_session_number].Thread_ID) == NO_ERROR) { Other_threads_exists = 1; break; }
      }

      if (Other_threads_exists) DosSleep (1000);
      else break;
    }

    // Отключаемся от драйвера.
    DosMonClose (Keyboard_monitor); Keyboard_monitor = NULLHANDLE;
  }

  // Выход.
  DosExit (EXIT_PROCESS, 0);
}
