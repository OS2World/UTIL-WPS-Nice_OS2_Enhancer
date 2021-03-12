
// ─── Располагает окно определителя в середине окна рамки ───

VOID Detector_MoveToCenter (HWND Detector_window)
{
  // Передвигаем окно так, чтобы оно располагалось в середине окна рамки.
  RECT Frame_window_rectangle  = {0}; WinQueryWindowRect (Enhancer.Frame_window, &Frame_window_rectangle);
  RECT Dialog_window_rectangle = {0}; WinQueryWindowRect (Detector_window, &Dialog_window_rectangle);

  Dialog_window_rectangle.xLeft   += (Frame_window_rectangle.xRight - Dialog_window_rectangle.xRight) / 2;
  Dialog_window_rectangle.yBottom += (Frame_window_rectangle.yTop - Dialog_window_rectangle.yTop) / 2;

  WinSetWindowPos (Detector_window, HWND_TOP, Dialog_window_rectangle.xLeft, Dialog_window_rectangle.yBottom, 0, 0, SWP_ZORDER | SWP_MOVE | SWP_NOADJUST);

  // Возврат.
  return;
}
