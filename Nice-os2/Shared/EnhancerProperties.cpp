// ��⮤� ��� ����祭�� ���� 䠩��� � ����ன����, ���������� ��� ���� � ��㣨� ᢮��� ����⥫�.
#define GetSettingsFileName            EnhancerProperties_GetSettingsFileName

#define GetEnhancerWindowTitle         EnhancerProperties_GetEnhancerWindowTitle
#define GetLoaderWindowTitle           EnhancerProperties_GetLoaderWindowTitle

#define SetCommonEnhancerFont          EnhancerProperties_SetCommonEnhancerFont
#define SetCommonEnhancerColors        EnhancerProperties_SetCommonEnhancerColors

// ��� ��⮤ ��� ������祭�� ����� ���

VOID EnhancerProperties_Start (VOID)
{
  #ifdef EnhancerProperties
  bzero (&EnhancerProperties, sizeof (EnhancerProperties));
  #endif

  // ������.
  return;
}

