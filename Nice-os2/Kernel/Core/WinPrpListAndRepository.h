// Методы для работы со списком свойств окон. Они используются в Repository, поэтому их надо объявить еще и таким образом.

VOID WinPrpListAndRepository_GetDetectedExeName( HWND W, PCHAR N );
VOID                         GetDetectedExeName( HWND W, PCHAR N )     { WinPrpListAndRepository_GetDetectedExeName( W, N );     }

VOID WinPrpListAndRepository_GetDetectedExePath( HWND W, PCHAR N );
VOID                         GetDetectedExePath( HWND W, PCHAR N )     { WinPrpListAndRepository_GetDetectedExePath( W, N );     }

VOID WinPrpListAndRepository_GetDetectedWindowTitle( HWND W, PCHAR N );
VOID                         GetDetectedWindowTitle( HWND W, PCHAR N ) { WinPrpListAndRepository_GetDetectedWindowTitle( W, N ); }
