// ��⮤� ��� ��ࠢ�� ᮮ�饭�� ����⥫�.
#define NiceReadSettings           Connector_NiceReadSettings
#define NiceReadRepository         Connector_NiceReadRepository

#define NiceScanLogonDialog        Connector_NiceScanLogonDialog
#define NiceScanIncompleteDialog   Connector_NiceScanIncompleteDialog
#define NiceScanMessageDialog      Connector_NiceScanMessageDialog

// ��� ��⮤ ��� ������祭�� ����� ���

VOID Connector_Start (VOID)
{
  #ifdef Connector
  bzero (&Connector, sizeof (Connector));
  #endif

  // ������.
  return;
}
