// Не определены PMWin.h.
#define ALL_QUEUES NULLHANDLE

// Определения для указателей на вызовы Nice-os2.dll.
typedef VOID  ( EXPENTRY VOIDPROCEDURE    ) ( VOID );

typedef VOID  ( EXPENTRY STARTKERNEL      ) ( HAB, HMODULE, BYTE, HWND );
typedef VOID  ( EXPENTRY SHUTDOWNKERNEL   ) ( BYTE );

typedef VOID  ( EXPENTRY READSETTINGS     ) ( BYTE );
typedef VOID  ( EXPENTRY SCANDIALOGWINDOW ) ( HWND );

typedef ULONG ( EXPENTRY INPUTHOOK        ) ( HAB, PQMSG, ULONG );
typedef ULONG ( EXPENTRY KBDINPUTHOOK     ) ( HAB, PQMSG, ULONG );
typedef VOID  ( EXPENTRY SENDMSGHOOK      ) ( HAB, PSMHSTRUCT, ULONG );
typedef ULONG ( EXPENTRY LOCKUPHOOK       ) ( HAB, HWND );

// Загрузчик.
typedef struct _LOADER
 {
  // Переменные для работы с Nice-os2.dll, указатели на вызовы.
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
    // Указатель на Nice-os2.dll.
    HMODULE Module;

    // Указатели на вызовы.
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
