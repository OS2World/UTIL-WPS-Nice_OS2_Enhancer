
// ��� ����頥�, �뫮 �� �⪫�祭� ��ࠢ������� ���� ���

BYTE Performer_ArrangerMustBeDisabled( VOID )
{
 // �᫨ ��ࠢ������� ���� �뫮 �⪫�祭� - ᮮ�頥� �� �⮬.
 if( Performer.RTSettings.Performer_disables_arranger ) return 1;

 // ������.
 return 0;
}
