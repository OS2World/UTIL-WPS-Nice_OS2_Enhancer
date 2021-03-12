// Методы для рисования рамок окон.
#define FrameDrawingIsRequired                  Painter_FrameDrawingIsRequired
#define DifferentTitleBarImagesAreRequired      Painter_DifferentTitleBarImagesAreRequired
#define NeonTitleBarIsRequired                  Painter_NeonTitleBarIsRequired
#define GlassTitleBarIsRequired                 Painter_GlassTitleBarIsRequired
#define TitleBarIsGrayed                        Painter_TitleBarIsGrayed

#define GetButtonPixelMargin                    Painter_GetButtonPixelMargin
#define GetTitleBarPixelMargin                  Painter_GetTitleBarPixelMargin
#define CalculateButtonRectangles               Painter_CalculateButtonRectangles

#define CreateTitleBarImages                    Painter_CreateTitleBarImages
#define DeleteTitleBarImages                    Painter_DeleteTitleBarImages
#define DeleteTitleBarPattern                   Painter_DeleteTitleBarPattern

#define PermissionForDrawing                    Painter_PermissionForDrawing
#define PermissionForCompleteDrawing            Painter_PermissionForCompleteDrawing
#define PermissionForButtonsDrawing             Painter_PermissionForButtonsDrawing
#define PermissionForRolling                    Painter_PermissionForRolling
#define PermissionForInnerFrameDrawing          Painter_PermissionForInnerFrameDrawing

#define QueryButtonsState                       Painter_QueryButtonsState

#define DrawFramesSettingIsON                   Painter_DrawFramesSettingIsON
#define DrawSystemMenusSettingIsON              Painter_DrawSystemMenusSettingIsON
#define DrawButtonsSettingIsON                  Painter_DrawButtonsSettingIsON
#define DisableFrameDrawing                     Painter_DisableFrameDrawing

#define SelectDesiredTexture                    Painter_SelectDesiredTexture

// ─── Метод для подключения класса ───

VOID Painter_Start (VOID)
{
  #ifdef Painter
  bzero (&Painter, sizeof (Painter));
  #endif

  // Задаем постоянные величины.
  Painter.Constants.Permanent_drawing = 250;
  Painter.Constants.Drawing_check_timeout = 750;

  // Задаем указатели в списке составляющих расширителя.
  MODULE Item; PresetModuleItem (&Item);

  Item.StartThread = Painter_StartThread;
  Item.PostQuitMsg = Painter_PostQuitMsg;
  Item.ShutdownAll = Painter_ShutdownAll;
  Item.TuneModule  = Painter_Tune;
  Item.SysColorsChangeReporter = Painter_SysColorsChangeReporter;
  Item.SysValuesChangeReporter = Painter_SysValuesChangeReporter;

  RememberModuleItem (Enhancer.Modules.Painter, &Item);

  // Возврат.
  return;
}

