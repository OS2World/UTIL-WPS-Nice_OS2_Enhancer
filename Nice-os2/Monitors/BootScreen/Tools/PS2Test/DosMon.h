typedef SHANDLE HMONITOR;
typedef HMONITOR *PHMONITOR;

#pragma pack(2)
typedef struct _MONIN {
        USHORT cb;
        BYTE abReserved[18];
        BYTE abBuffer[108];
} MONIN;
typedef MONIN *PMONIN;

#pragma pack(2)
typedef struct _MONOUT {
        USHORT cb;
        UCHAR buffer[18];
        BYTE abBuf[108];
} MONOUT;
typedef MONOUT *PMONOUT;

#pragma pack(2)
typedef struct _keypacket {
        USHORT     mnflags;
        KBDKEYINFO cp;
        USHORT     ddflags;
} KEYPACKET;

#pragma seg16(HKBD)
#pragma seg16(MONIN)
#pragma seg16(MONOUT)
#pragma seg16(KEYPACKET)

#define DosMonOpen    DOS16MONOPEN
#define DosMonReg     DOS16MONREG
#define DosMonClose   DOS16MONCLOSE
#define DosMonRead    DOS16MONREAD
#define DosMonWrite   DOS16MONWRITE

APIRET16 APIENTRY16 DosMonOpen(PSZ DevName,PHMONITOR Handle);
APIRET16 APIENTRY16 DosMonReg(HMONITOR Handle,PBYTE BufferI,PBYTE BufferO,USHORT Posflag,USHORT Index);
APIRET16 APIENTRY16 DosMonClose(HMONITOR Handle);
APIRET16 APIENTRY16 DosMonRead(PBYTE BufferI,USHORT WaitFlag,PBYTE DataBuffer,PUSHORT Bytecnt);
APIRET16 APIENTRY16 DosMonWrite(PBYTE BufferO,PBYTE DataBuffer,USHORT Bytecnt);

#define MONITOR_BEGIN   0x01
#define MONITOR_DEFAULT 0x00

#define MONITOR_WAIT      0
#define MONITOR_NOWAIT    1

#define MONITOR_SESSION_PM 1

#pragma pack()

/* * */

#ifndef QSV_FOREGROUND_FS_SESSION
#define QSV_FOREGROUND_FS_SESSION 24
#endif
