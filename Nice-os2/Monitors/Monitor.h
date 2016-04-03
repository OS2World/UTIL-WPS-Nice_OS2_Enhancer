/* DOS API Monitor Support
 *
 * Portions Copyright (C) Andrei Los' (lSwitcher, 2004)
 * Portions Copyright (C) Dmitry A.Steklenev (Keyboard Layer/2, 1998)
 * Portions Copyright (C) Julius Goryavsky (Black Hackers KeybMon, 1994-1995) 
 */

typedef SHANDLE HMONITOR;
typedef HMONITOR* PHMONITOR;

#pragma pack(2)
typedef struct _keypacket
{
  UCHAR  MonFlags;
  UCHAR  ScanCode;
  UCHAR  XlatedChar;
  UCHAR  XlatedScan;
  UCHAR  DBCSStatus;
  UCHAR  DBCSShiftState;
  USHORT ShiftState;

  ULONG  Milliseconds;
  USHORT KbdDDFlagWord;
} KEYPACKET; typedef _keypacket* PKEYPACKET;

typedef struct _monin
{
  USHORT    cb;
  KEYPACKET Buffer;
  BYTE      Reserved[20];
} MONIN; typedef _monin* PMONIN;

typedef struct _monout
{
  USHORT    cb;
  KEYPACKET Buffer;
  BYTE      Reserved[20];
} MONOUT; typedef _monout* PMONOUT;

struct _mlnpacket
{
  USHORT MonFlags;
  USHORT IOCTL;
  USHORT CPId;
  USHORT CPIndex;

  ULONG  Reserved;
  USHORT KbdDDFlagWord;
} MLNPACKET; typedef _mlnpacket* PMLNPACKET;

#pragma seg16(KEYPACKET)
#pragma seg16(MONIN)
#pragma seg16(MONOUT)
#pragma seg16(MLNPACKET)

#define DosMonOpen  DOS16MONOPEN
#define DosMonReg   DOS16MONREG
#define DosMonClose DOS16MONCLOSE
#define DosMonRead  DOS16MONREAD
#define DosMonWrite DOS16MONWRITE

APIRET16 APIENTRY16 DosMonOpen (PSZ DevName, PHMONITOR Handle);
APIRET16 APIENTRY16 DosMonReg (HMONITOR Handle, PBYTE BufferI, PBYTE BufferO, USHORT Posflag, USHORT Index);
APIRET16 APIENTRY16 DosMonClose (HMONITOR Handle);
APIRET16 APIENTRY16 DosMonRead (PBYTE BufferI, USHORT WaitFlag, PBYTE DataBuffer, PUSHORT Bytecnt);
APIRET16 APIENTRY16 DosMonWrite (PBYTE BufferO, PBYTE DataBuffer, USHORT Bytecnt);

#define MONITOR_DEFAULT 0x00
#define MONITOR_BEGIN   0x01
#define MONITOR_END     0x02

#define MONITOR_WAIT    0
#define MONITOR_NOWAIT  1

/* MonFlags */

#define MF_OPEN            1  // "Open"
#define MF_CLOSE           2  // "Close"
#define MF_FLUSH           4  // "Is flush packet"

/* DBCSStatus */

#define SF_SHIFTS          1  // If set to 1, shift status returned without a character
#define SF_NOTCHAR         2  // 0 - Scan code is a character
                              // 1 - Scan code is not a character;
                              //     instead it is an extended key code from the keyboard.
#define SF_IMMEDIATE      32  // If set to 1, immediate conversion requested
#define SF_TYPEMASK      192  // Has the following values:
                              // 00 - Undefined
                              // 01 - Final character; interim character flag is turned off
                              // 10 - Interim character
                              // 11 - Final character; interim character flag is turned on.

/* ShiftState */

#define RS_SYSREG      32768  // Bit 15  SysReq key down
#define RS_CAPSLOCK    16384  // Bit 14  Caps Lock key down
#define RS_NUMLOCK      8192  // Bit 13  NumLock key down
#define RS_SCROLLLOCK   4096  // Bit 12  Scroll Lock key down
#define RS_RALT         2048  // Bit 11  Right Alt key down
#define RS_RCONTROL     1024  // Bit 10  Right Ctrl key down
#define RS_LALT          512  // Bit  9  Left Alt key down
#define RS_LCONTROL      256  // Bit  8  Left Ctrl key down
#define RS_INSERT        128  // Bit  7  Insert on
#define RS_CAPS           64  // Bit  6  Caps Lock on
#define RS_NUM            32  // Bit  5  NumLock on
#define RS_SCROLL         16  // Bit  4  Scroll Lock on
#define RS_ALT             8  // Bit  3  Either Alt key down
#define RS_CONTROL         4  // Bit  2  Either Ctrl key down
#define RS_LSHIFT          2  // Bit  1  Left Shift key down
#define RS_RSHIFT          1  // Bit  0  Right Shift key down

/* KbdDDFlagWord */

#define KF_NOTSQPACKET  1024  // Don't put this packet in SQ buffer
#define KF_ACCENTEDKEY   512  // Key was translated using previous accent.
#define KF_MULTIMAKE     256  // Key was repeated make of a toggle key.
#define KF_SECONDARYKEY  128  // Previous scan code was the E0 prefix code.
#define KF_KEYBREAK       64  // This is the break of the key.
#define KF_KEYTYPEMASK    63  // Isolates the Key Type field of DDFlags.
#define KF_UNDEFKEY       63  // Key packet is undefined
#define KF_SYSREQKEY      23  // This key packet is the SysReq key (4990)
#define KF_PRINTFLUSHKEY  22  // This packet is Ct-Alt-PrtScr
#define KF_PSPRINTECHOKEY 21  // This packet is Ctl-P
#define KF_PRINTECHOKEY   20  // This packet is Ctl-PrtScr
#define KF_PRTSCRKEY      19  // This packet is PrtScr
#define KF_PSBREAKKEY     18  // This packet is Ctl-C
#define KF_BREAKKEY       17  // This packet is Ctl-Break
#define KF_ACCENTKEY      16  // This packet is an accent key
#define KF_XRORPNOT       13  // This packet is a Read or Peek Notification Pct.
#define KF_MLNOTIFICATION 14  // packet is a Multi-Layer NLS packet
#define KF_HOTKEYPACKET   12  // This packet is the hot key.
#define KF_BADKEYCOMBO    11  // Accent/char combo undefined, beep only.
#define KF_WAKEUPKEY      10  // This packet is one following PAUSEKEY
#define KF_PSPAUSEKEY      9  // This packet is Ctl-S
#define KF_PAUSEKEY        8  // This packet is Ctl-Numlock or PAUSE
#define KF_SHIFTMASK       7  // Key is a shift Key
#define KF_DUMPKEY         6  // This packet is Ctl-Numlock-NumLock
#define KF_REBOOTKEY       5  // This packet is Ctl-Alt-Del
#define KF_RESENDCODE      4  // This packet is resend code from controller
#define KF_OVERRUNCODE     3  // This packet is overrun code from controller
#define KF_SECPREFIXCODE   2  // This packet is E0/E1 scan code
#define KF_ACKCODE         1  // This packet is ack code from keyboard

#pragma pack(4)

/* * */

#ifndef QSV_FOREGROUND_FS_SESSION
#define QSV_FOREGROUND_FS_SESSION 24
#endif
