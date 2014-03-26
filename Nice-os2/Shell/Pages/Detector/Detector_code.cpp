
// ─── Показывает окно определителя ───

VOID Detector_OpenDETECTOR( VOID )
{
 // Если окно уже показано - возврат.
 if( Enhancer.Detector_dialog.Detector_is_running ) return;

 // Запоминаем, что окно показано.
 Enhancer.Detector_dialog.Detector_is_running = 1;

 // Загружаем диалог.
 // Окно будет располагаться в окне рамки и перекрывать окно рабочей области.
 HWND Detector_window = WinLoadDlg( Enhancer.Frame_window, Enhancer.Client_window, (PFNWP) Detector_DlgProc, NULLHANDLE, ID_DETECTORFORM, NULL );

 // Задаем шрифт.
 SetCommonEnhancerFont( Detector_window );

 // Передвигаем окно в середину окна рамки.
 Detector_MoveToCenter( Detector_window );

 // Запускаем счетчик времени.
 WinStartTimer( Enhancer.Application, Detector_window, 1, Detector_Form.Constants.Delay_time_ms );

 // Начинаем диалог и ждем его завершения.
 WinProcessDlg( Detector_window );

 // Останавливаем счетчик времени.
 WinStopTimer( Enhancer.Application, Detector_window, 1 );

 // Сбрасываем внешние и внутренние переменные. Константы не трогаем.
 bzero( &Enhancer.Detector_dialog, sizeof( Enhancer.Detector_dialog ) );
 bzero( &Detector_Form.Settings, sizeof( Detector_Form.Settings ) );

 // Удаляем окно. Поля ввода оно удалит самостоятельно.
 WinDestroyWindow( Detector_window );

 // Возврат.
 return;
}


