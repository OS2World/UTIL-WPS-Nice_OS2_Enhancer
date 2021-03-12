// Методы для отправки сообщений расширителю.
#define NiceReadSettings           Connector_NiceReadSettings
#define NiceReadRepository         Connector_NiceReadRepository

#define NiceScanLogonDialog        Connector_NiceScanLogonDialog
#define NiceScanIncompleteDialog   Connector_NiceScanIncompleteDialog
#define NiceScanMessageDialog      Connector_NiceScanMessageDialog

// ─── Метод для подключения класса ───

VOID Connector_Start (VOID)
{
  #ifdef Connector
  bzero (&Connector, sizeof (Connector));
  #endif

  // Возврат.
  return;
}
