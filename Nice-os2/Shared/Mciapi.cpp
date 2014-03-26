// ************************************************************************************
// * Mciapi.cpp �������� �ᯮ�짮���� � �ਫ������� �맮�� MMOS2.                    *
// ************************************************************************************

// ************************************************************************************
// * MMOS2 �� ����� ���� �맢��� ��⮪��, �᫨ ��� �⥪ ����� 8 �����.               *
// * ��� �ᥣ� ��뢠�� MMOS2 �� ��ࠡ�⪥ ᮮ�饭��, ��室��� ����.             *
// ************************************************************************************

// ************************************************************************************
// * �⮡� �� �������� ����� �����, ��㪨 ������ ����㦠���� �� �ॡ������.          *
// * ��㪨 ���ந�������� MMOS2 �⤥�쭮 �� �ਫ������, � ��᫥ ⮣�, ��� ��� �㤥� *
// * ���ந������, ������ ���� �᢮�������.                                          *
// ************************************************************************************

#define INCL_DOSMODULEMGR


// ��।������ ��� 㪠��⥫�� �� �맮�� MMOS2.
typedef ULONG ( APIENTRY MCISENDCOMMAND ) ( USHORT, USHORT, ULONG, PVOID, USHORT );

// ��६���� ��� ࠡ��� � MMOS2, 㪠��⥫� �� �맮��.
struct MM_CALLS
 {
  // �����⥫� �� Mdm.dll.
  HMODULE Mdm_module;
  // �����⥫� �� �맮� mciSendCommand(), ����� �।��⠢��� Mdm.dll.
  MCISENDCOMMAND* mciSendCommand;
 };
MM_CALLS MM_Calls = {0};


// ������� MMOS2. ������ ���ᠭ�� ����� ���� � Mcios2.h
#define MCI_OPEN                        1
#define MCI_CLOSE                       2
#define MCI_PLAY                        4
#define MCI_REWIND                     46

// �������⥫�� ��ࠬ���� ��� �� �������.
#define MCI_NOTIFY             0x00000001L
#define MCI_WAIT               0x00000002L
#define MCI_OPEN_ELEMENT       0x00000100L
#define MCI_OPEN_SHAREABLE     0x00002000L
#define MCI_OPEN_READONLY      0x00008000L

// ���祭��, ����� �����頥� mciSendCommand().
#define MCIERR_SUCCESS                  0
#define MCIERR_CANNOT_LOAD_DRIVER    5010

// ����饭�� ���� � ⮬, �� ��� ���ந������.
#define MM_MCINOTIFY               0x0500

// ��।������ ��६�����
typedef USHORT HSOUND;

// ��ࠬ���� ������� ������ 䠩��.
struct MCI_OPEN_PARMS
 {
  HWND    hwndCallback;    /* PM window handle for MCI notify message */
  USHORT  usDeviceID;      /* Device ID returned to user              */
  USHORT  usReserved0;     /* Reserved                                */
  PSZ     pszDeviceType;   /* Device name                             */
  PSZ     pszElementName;  /* Typically a file name or NULL           */
  PSZ     pszAlias;        /* Optional device alias                   */
 };

// ��ࠬ���� ������� ���ந�������� ��㪠.
struct MCI_PLAY_PARMS
 {
  HWND    hwndCallback;    /* PM window handle for MCI notify message */
  ULONG   ulFrom;          /* Play from this position                 */
  ULONG   ulTo;            /* Play to this position                   */
 };

// ��ࠬ���� ������� ������� 䠩��.
struct MCI_GENERIC_PARMS
 {
  HWND   hwndCallback;     /* PM window handle for MCI notify message */
 };


// ������砥� � �ਫ������ �맮�� MMOS2.
INT LoadMMOS2( VOID );

// �⪫�砥� MMOS2.
VOID UnloadMMOS2( VOID );

// ��뢠�� mciSendCommand().
ULONG mciSendCommand( USHORT usDeviceID, USHORT usMessage, ULONG ulParam1, PVOID pParam2, USHORT usUserParm );

// ����㦠�� ��� � ������.
HSOUND LoadSound( PSZ File_name );

// ���ந������ ����㦥��� ࠭�� ���.
ULONG PlaySound( HSOUND Sound_ID, HWND Window = NULLHANDLE );

// �᢮������� ������.
VOID DeleteSound( HSOUND Sound_ID );

// ���ந������ ��㪮��� 䠩�.
ULONG PlayAudioFile( PSZ File_name );


// // // // // // // // // // // // // // // // // // // // // // // // // // // //
//                                                                               //
// ��� �ਬ�� �ᯮ�짮����� Mciapi.cpp ���                                      //
//                                                                               //
// VOID main( VOID )                                                             //
// {                                                                             //
//  // ������砥� MMOS2.                                                         //
//  LoadMMOS2();                                                                 //
//                                                                               //
//  // ��ࠥ� ���.                                                              //
//  PlayAudioFile( "C:\\Mmos2\\Sounds\\���-1.wav" );                            //
//                                                                               //
//  // �⪫�砥� MMOS2.                                                          //
//  UnloadMMOS2();                                                               //
//                                                                               //
//  // ������.                                                                  //
//  return;                                                                      //
// }                                                                             //
//                                                                               //
// // // // // // // // // // // // // // // // // // // // // // // // // // // //


// ��� ������砥� � �ਫ������ �맮�� MMOS2 ���

// �����頥� 1 ��� 0.
INT LoadMMOS2( VOID )
{
 // ������砥� Mdm.dll.
 APIRET Result = DosLoadModule( NULL, 0, "Mdm.dll", &MM_Calls.Mdm_module );

 // �᫨ �� ᤥ���� �� 㤠���� - ������.
 if( Result != 0 ) return 0;

 // ������砥� �맮� mciSendCommand(), ����� �।��⠢��� Mdm.dll.
 DosQueryProcAddr( MM_Calls.Mdm_module, 0, "mciSendCommand", (PFN*) &MM_Calls.mciSendCommand );

 // ������.
 return 1;
}

// ��� �⪫�砥� MMOS2 ���

VOID UnloadMMOS2( VOID )
{
 // �᢮������� Mdm.dll.
 if( MM_Calls.Mdm_module ) DosFreeModule( MM_Calls.Mdm_module ); MM_Calls.Mdm_module = NULLHANDLE;

 // ������.
 return;
}

// ��� �஢����, ����㦥�� �� MMOS2 ���

BYTE MMOS2IsLoaded( VOID )
{
 // �஢��塞, ����㦥�� �� Mdm.dll.
 if( MM_Calls.Mdm_module ) return 1;

 // ������.
 return 0;
}

// ��� ��뢠�� mciSendCommand() ���

// ���祭�� � ��, �� � � OS/2.
ULONG mciSendCommand( USHORT usDeviceID, USHORT usMessage, ULONG ulParam1, PVOID pParam2, USHORT usUserParm )
{
 // ��뢠�� mciSendCommand().
 if( MM_Calls.mciSendCommand ) return MM_Calls.mciSendCommand( usDeviceID, usMessage, ulParam1, pParam2, usUserParm );
 // ��� �����頥� �訡�� "�� �� ������祭 �ࠩ���".
 else return MCIERR_CANNOT_LOAD_DRIVER;
}

// ��� ����㦠�� ��� � ������ ���

// File_name - ��� 䠩�� ACM Wave.
// �����頥��� ���祭�� ��।���� ��� � �����.
HSOUND LoadSound( PSZ File_name )
{
 // ���뢠�� 䠩�.
 MCI_OPEN_PARMS Open_parameters;
 Open_parameters.hwndCallback = NULLHANDLE;
 Open_parameters.usDeviceID = NULLHANDLE;
 Open_parameters.pszDeviceType = NULL;
 Open_parameters.pszElementName = File_name;
 mciSendCommand( NULLHANDLE, MCI_OPEN, MCI_WAIT | MCI_OPEN_ELEMENT | MCI_OPEN_SHAREABLE | MCI_OPEN_READONLY, (PVOID) &Open_parameters, 0 );

 // �����頥� ���祭��, ��।����饥 ��� � �����.
 return Open_parameters.usDeviceID;
}

// ��� ���ந������ ����㦥��� ࠭�� ��� ���

// Sound_ID - ��� � �����, Window - ����, ���஬� ᮮ�頥��� � ⮬, �� ��� ���ந������.
// �᫨ ��� ���ந������, �����頥� 1, ���� 0.
ULONG PlaySound( HSOUND Sound_ID, HWND Window )
{
 // �᫨ ���� �� 㪠����, � ���� �����, ���� ��� �㤥� ���ந������.
 INT Parameter = 0; if( Window == NULLHANDLE ) Parameter = MCI_WAIT; else Parameter = MCI_NOTIFY;

 // ���ந������ ���. ��᫥ ⮣�, ��� ��� �㤥� ���ந������, � ���� Window �㤥�
 // ��᫠�� ᮮ�饭�� MM_MCINOTIFY. ��ࠡ��稪 �⮣� ᮮ�饭�� ������ �᢮������ ������.
 MCI_PLAY_PARMS Play_parameters;
 Play_parameters.hwndCallback = Window;
 Play_parameters.ulFrom = 0; Play_parameters.ulTo = 0;
 ULONG Result = mciSendCommand( Sound_ID, MCI_PLAY, Parameter, (PVOID) &Play_parameters, 0 );

 // ������.
 if( Result == MCIERR_SUCCESS ) return 1; else return 0;
}

// ��� �᢮������� ������ ���

// Sound_ID - ��� � �����.
VOID DeleteSound( HSOUND Sound_ID )
{
 // ����뢠�� 䠩�.
 MCI_GENERIC_PARMS Close_parameters;
 Close_parameters.hwndCallback = NULLHANDLE;
 mciSendCommand( Sound_ID, MCI_CLOSE, 0, (PVOID) &Close_parameters, 0 );

 // ������.
 return;
}

// ��� ���ந������ ��㪮��� 䠩� ���

// ��६����� File_name ������ ��� 䠩��.
// �᫨ ��� ���ந������, �����頥� 1, ���� 0.
ULONG PlayAudioFile( PSZ File_name )
{
 // ����㦠�� ��� � ������.
 HSOUND Sound = LoadSound( File_name );
 // ���ந������ ���.
 ULONG Result = PlaySound( Sound );
 // �᢮������� ������.
 DeleteSound( Sound );

 // ������.
 return Result;
}
