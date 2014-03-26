
// ��� �����뢠�� ���� ��।���⥫� ���

VOID Detector_OpenDETECTOR( VOID )
{
 // �᫨ ���� 㦥 �������� - ������.
 if( Enhancer.Detector_dialog.Detector_is_running ) return;

 // ����������, �� ���� ��������.
 Enhancer.Detector_dialog.Detector_is_running = 1;

 // ����㦠�� ������.
 // ���� �㤥� �ᯮ�������� � ���� ࠬ�� � ��४�뢠�� ���� ࠡ�祩 ������.
 HWND Detector_window = WinLoadDlg( Enhancer.Frame_window, Enhancer.Client_window, (PFNWP) Detector_DlgProc, NULLHANDLE, ID_DETECTORFORM, NULL );

 // ������ ����.
 SetCommonEnhancerFont( Detector_window );

 // ��।������ ���� � �।��� ���� ࠬ��.
 Detector_MoveToCenter( Detector_window );

 // ����᪠�� ���稪 �६���.
 WinStartTimer( Enhancer.Application, Detector_window, 1, Detector_Form.Constants.Delay_time_ms );

 // ��稭��� ������ � ���� ��� �����襭��.
 WinProcessDlg( Detector_window );

 // ��⠭�������� ���稪 �६���.
 WinStopTimer( Enhancer.Application, Detector_window, 1 );

 // ����뢠�� ���譨� � ����७��� ��६����. ����⠭�� �� �ண���.
 bzero( &Enhancer.Detector_dialog, sizeof( Enhancer.Detector_dialog ) );
 bzero( &Detector_Form.Settings, sizeof( Detector_Form.Settings ) );

 // ����塞 ����. ���� ����� ��� 㤠��� ᠬ����⥫쭮.
 WinDestroyWindow( Detector_window );

 // ������.
 return;
}


