// ��⮤� ��� �ᯮ�������� ���㦥���.
#define SMPSystem                   Environment_SMPSystem

#define ActiveApplication           Environment_ActiveApplication
#define QueryDesktopWindow          Environment_QueryDesktopWindow

#define QuerySystemCodePage         Environment_QuerySystemCodePage
#define DBCSSupportIsEnabled        Environment_DBCSSupportIsEnabled

#define QueryTempDirectory          Environment_QueryTempDirectory

// ��� ��⮤ ��� ������祭�� ����� ���

VOID Environment_Start (VOID)
{
  #ifdef Environment
  bzero (&Environment, sizeof (Environment));
  #endif

  // ������.
  return;
}
