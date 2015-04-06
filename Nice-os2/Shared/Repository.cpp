// Методы для работы со списком приложений и распознавания окон.
#define rp_next                     Repository_rp_next
#define rp_clear                    Repository_rp_clear
#define ReadRepository              Repository_ReadRepository

#define QueryWPSObject              Repository_QueryWPSObject
#define WPSObjectIsExists           Repository_WPSObjectIsExists

#define FindApplicationInRepository Repository_FindApplicationInRepository
#define ApplicationIsExists         Repository_ApplicationIsExists
#define ShowCommandCanBeUsed        Repository_ShowCommandCanBeUsed
#define FindExeNameInRepository     Repository_FindExeNameInRepository
#define FindDescriptionInRepository Repository_FindDescriptionInRepository

#define IsDesktopWindow             Repository_IsDesktopWindow
#define IsFrameWindow               Repository_IsFrameWindow
#define IsFolderWindow              Repository_IsFolderWindow

#define QueryFrameWindow            Repository_QueryFrameWindow
#define QueryMainWindow             Repository_QueryMainWindow

#define QueryWindowRealProcessID    Repository_QueryWindowRealProcessID
#define WindowIsCreatedBy           Repository_WindowIsCreatedBy
#define WindowIsUsedTo              Repository_WindowIsUsedTo
#define CommandForWindowIs          Repository_CommandForWindowIs

#define QueryProcessInfo            Repository_QueryProcessInfo
#define QueryExeName                Repository_QueryExeName

#define IsMenuWindow                Repository_IsMenuWindow
#define IsTitleBarWindow            Repository_IsTitleBarWindow
#define IsScrollBarWindow           Repository_IsScrollBarWindow
#define IsInputFieldWindow          Repository_IsInputFieldWindow
#define IsEntryFieldWindow          Repository_IsEntryFieldWindow
#define IsIconViewWindow            Repository_IsIconViewWindow
#define IsDetailViewWindow          Repository_IsDetailViewWindow
#define IsComboBoxWindow            Repository_IsComboBoxWindow
#define IsListBoxWindow             Repository_IsListBoxWindow
#define IsSpinButtonWindow          Repository_IsSpinButtonWindow
#define IsCheckBoxButtonWindow      Repository_IsCheckBoxButtonWindow
#define IsRadioButtonWindow         Repository_IsRadioButtonWindow
#define IsButtonWindow              Repository_IsButtonWindow
#define IsSliderWindow              Repository_IsSliderWindow
#define IsCircularSliderWindow      Repository_IsCircularSliderWindow

#define IsNotebookWindow            Repository_IsNotebookWindow
#define IsNotebookPageWindow        Repository_IsNotebookPageWindow
#define IsStaticWindow              Repository_IsStaticWindow
#define IsLabelWindow               Repository_IsLabelWindow

#define IsInputFieldContainerWindow Repository_IsInputFieldContainerWindow

#define IsFileBarWindow             Repository_IsFileBarWindow
#define IsMDeskWindow               Repository_IsMDeskWindow
#define IsWinListWindow             Repository_IsWinListWindow

#define IsPMShellAuxiliaryWindow    Repository_IsPMShellAuxiliaryWindow
#define IsWorkplaceShellWindow      Repository_IsWorkplaceShellWindow
#define IsCommandExecutorWindow     Repository_IsCommandExecutorWindow
#define IsAltTabSwitcherWindow      Repository_IsAltTabSwitcherWindow
#define IslSwitcherWindow           Repository_IslSwitcherWindow
#define IsSysMsgWindow              Repository_IsSysMsgWindow

#define IsWarpCenterWindow          Repository_IsWarpCenterWindow
#define IsWarpCenterMenuWindow      Repository_IsWarpCenterMenuWindow
#define IsSysTrayWindow             Repository_IsSysTrayWindow
#define IsSysTrayMenuWindow         Repository_IsSysTrayMenuWindow
#define IsECenterWindow             Repository_IsECenterWindow
#define IsECenterMenuWindow         Repository_IsECenterMenuWindow
#define IsEPagerWindow              Repository_IsEPagerWindow
#define IsXWPDaemonWindow           Repository_IsXWPDaemonWindow

#define IsWindowsWindow             Repository_IsWindowsWindow
#define IsVIOWindow                 Repository_IsVIOWindow

// ─── Метод для подключения класса ───

VOID Repository_Start( VOID )
{
 // Заполняем переменные перед началом работы. 
 // Сбрасывать с помощью bzero() их не нужно - память очищается при заполнении.
 Repository_SetRepository();

 // Возврат.
 return;
}
