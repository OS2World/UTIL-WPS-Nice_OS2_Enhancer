// ��⮤� ��� ��������� ���⮢ � ⥪�⮢�� �����.
#define VIOFontMustBeChanged          VIOFontManager_VIOFontMustBeChanged

#define OpenVIOFontMetricsDialog      VIOFontManager_OpenVIOFontMetricsDialog
#define SubmitVIOFontMetricsDialog    VIOFontManager_SubmitVIOFontMetricsDialog

#define FontsCanBeChangedInVIOWindows VIOFontManager_FontsCanBeChangedInVIOWindows

// ��� ��⮤ ��� ������祭�� ����� ���

VOID VIOFontManager_Start( VOID )
{
 #ifdef VIOFontManager
 bzero( &VIOFontManager, sizeof( VIOFontManager ) );
 #endif

 // ������ 㪠��⥫� � ᯨ᪥ ��⠢����� ����⥫�.
 MODULE Item; PresetModuleItem( &Item );

 Item.TuneModule = VIOFontManager_Tune;

 RememberModuleItem( Enhancer.Modules.VIOFontManager, &Item );

 // ������.
 return;
}

