// �� ��।����� PMWin.h.
#define ALL_QUEUES NULLHANDLE

// ��।������ ��� 㪠��⥫�� �� �맮�� Nice-os2.dll.
typedef VOID  ( EXPENTRY VOIDPROCEDURE    ) ( VOID );

typedef VOID  ( EXPENTRY STARTKERNEL      ) ( HAB, HMODULE, BYTE, HWND );
typedef VOID  ( EXPENTRY SHUTDOWNKERNEL   ) ( BYTE );

typedef VOID  ( EXPENTRY READSETTINGS     ) ( BYTE );
typedef VOID  ( EXPENTRY SCANDIALOGWINDOW ) ( HWND );

typedef ULONG ( EXPENTRY INPUTHOOK        ) ( HAB, PQMSG, ULONG );
typedef ULONG ( EXPENTRY KBDINPUTHOOK     ) ( HAB, PQMSG, ULONG );
typedef VOID  ( EXPENTRY SENDMSGHOOK      ) ( HAB, PSMHSTRUCT, ULONG );
typedef ULONG ( EXPENTRY LOCKUPHOOK       ) ( HAB, HWND );

// �����稪.
typedef struct _LOADER
 {
  // ��६���� ��� ࠡ��� � Nice-os2.dll, 㪠��⥫� �� �맮��.
  typedef struct _INSTALLED_HOOKS
   {
    LONG InputHook_type;
    LONG KbdInputHook_type;
    LONG SendMsgHook_type;
    LONG LockupHook_type;
   }
  INSTALLED_HOOKS; INSTALLED_HOOKS Hooks;

  typedef struct _DLL_CALLS
   {
    // �����⥫� �� Nice-os2.dll.
    HMODULE Module;

    // �����⥫� �� �맮��.
    STARTKERNEL* StartKernel;
    VOIDPROCEDURE* HeyHoLetsGo;
    SHUTDOWNKERNEL* ShutdownKernel;
    VOIDPROCEDURE* ApplicationIsKilled;

    READSETTINGS* ReadSettings;
    VOIDPROCEDURE* ReadRepository;

    INPUTHOOK* InputHook;
    KBDINPUTHOOK* KbdInputHook;
    SENDMSGHOOK* SendMsgHook;
    LOCKUPHOOK* LockupHook;

    SCANDIALOGWINDOW* ScanLogonDialog;
    SCANDIALOGWINDOW* ScanIncompleteDialog;
    SCANDIALOGWINDOW* ScanMessageDialog;
   }
  DLL_CALLS; DLL_CALLS Dll_calls;
 }
LOADER; LOADER Loader;
