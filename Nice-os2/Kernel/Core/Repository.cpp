// Методы для распознавания окон.
#define IsHobWindow                 Krnl_Repository_IsHobWindow
#define IsJavaWindow                Krnl_Repository_IsJavaWindow
#define IsSpeedPascalWindow         Krnl_Repository_IsSpeedPascalWindow
#define IsSibylInnerWindow          Krnl_Repository_IsSibylInnerWindow

#define WindowIsDialog              Krnl_Repository_WindowIsDialog
#define WindowIsAppDialog           Krnl_Repository_WindowIsAppDialog

#define IsPaletteWindow             Krnl_Repository_IsPaletteWindow
#define IsJobCnrWindow              Krnl_Repository_IsJobCnrWindow
#define IsSmartBarWindow            Krnl_Repository_IsSmartBarWindow

#define IsMozillaLiningWindow       Krnl_Repository_IsMozillaLiningWindow
#define IsMozillaFrameWindow        Krnl_Repository_IsMozillaFrameWindow
#define IsQtLiningWindow            Krnl_Repository_IsQtLiningWindow
#define IsQtFrameWindow             Krnl_Repository_IsQtFrameWindow
#define IsOdinLiningWindow          Krnl_Repository_IsOdinLiningWindow
#define IsOdinFrameWindow           Krnl_Repository_IsOdinFrameWindow
#define IsEPMEditorWindow           Krnl_Repository_IsEPMEditorWindow
#define IsVideoViewerWindow         Krnl_Repository_IsVideoViewerWindow
#define IsVideoPlayerWindow         Krnl_Repository_IsVideoPlayerWindow

#define FindFontListField           Krnl_Repository_FindFontListField
#define IsVIOFontMetricsDialog      Krnl_Repository_IsVIOFontMetricsDialog
#define IsLaunchPadWindow           Krnl_Repository_IsLaunchPadWindow

#define IsRZApiWindow               Krnl_Repository_IsRZApiWindow

#define IsGoldEdWindow              Krnl_Repository_IsGoldEdWindow
#define IsHotJavaBrowserWindow      Krnl_Repository_IsHotJavaBrowserWindow

#define FindRelatedFrameWindow      Krnl_Repository_FindRelatedFrameWindow

#define QueryPrinterName            Krnl_Repository_QueryPrinterName

#define GetKnownObjects             Krnl_Repository_GetKnownObjects
#define GetKnownPipes               Krnl_Repository_GetKnownPipes

// ─── Метод для подключения класса ───

VOID Krnl_Repository_Start (VOID)
{
  #ifdef Krnl_Repository
  bzero (&Krnl_Repository, sizeof (Krnl_Repository));
  #endif

  // Задаем имена значков рабочего стола.
  Krnl_Repository_SetObjectNames ();

  // Задаем соединения.
  Krnl_Repository_SetPipeNames ();

  // Возврат.
  return;
}
