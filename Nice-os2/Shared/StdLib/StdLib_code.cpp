// ��� �����頥� ��砩��� �᫮ � �������� �।���� ���

INT StdLib_Rnd (INT Max)
{
  // �᫨ �᫮ ����� �����⨬��� ���祭�� - ������.
  if (Max > RAND_MAX - 1) return -1;

  // ����砥� ��砩��� �᫮ �� 0 �� 1.
  INT Integer_value = rand ();

  // ��᫮ ������ ���� �� 0 �� Max.
  INT Divisor = RAND_MAX / (Max + 1);

  // ����砥� �᫮.
  INT Result = Integer_value / Divisor;
  if (Result > Max) Result = Max;

  // �����頥� �᫮.
  return Result;
}

// ��� �����頥� ������⥫쭮� 楫�� �᫮ ���

INT StdLib_Unsigned (INT Number)
{
  // �������� �᫮ �� -1 �᫨ ��� ����� ���.
  if (Number < 0) Number *= (-1);

  // �����頥� �᫮.
  return Number;
}

// ��� �����頥� �������襥 楫�� �᫮ �� ��᪮�쪨� �ᥫ ���

INT StdLib_Min (INT V1, INT V2, INT V3 = INT_MAX, INT V4 = INT_MAX)
{
  // �믮��塞 �ࠢ�����.
  INT Min_value = V1;
  if (V2 < Min_value) Min_value = V2;
  if (V3 < Min_value) Min_value = V3;
  if (V4 < Min_value) Min_value = V4;

  // �����頥� �᫮.
  return Min_value;
}

// ��� �����頥� �������襥 楫�� �᫮ �� ��᪮�쪨� �ᥫ ���

INT StdLib_Max (INT V1, INT V2, INT V3 = INT_MIN, INT V4 = INT_MIN)
{
  // �믮��塞 �ࠢ�����.
  INT Max_value = V1;
  if (V2 > Max_value) Max_value = V2;
  if (V3 > Max_value) Max_value = V3;
  if (V4 > Max_value) Max_value = V4;

  // �����頥� �᫮.
  return Max_value;
}

// ��� �믮���� ������� � 㬭������� � �����頥� 楫�� �᫮ ���

INT StdLib_DivideMultiply (INT DD, INT D, INT L)
{
  // �� ���� �� �����, �� �����頥� ����.
  if (DD == 0 || D == 0 || L == 0) return 0;

  // �᫨ �᫠ ������� ��楫� ��� ���⪠ - �믮��塞 ���� ��� ���� �筮��.
  // ���� �믮��塞 ������� � �窮�, ��⥬ �믮��塞 㬭������ � ��塞 �筮���.
  if (DD % D == 0) return (DD / D) * L;
  else return ((FLOAT) DD / D) * L;
}

// ��� �믮���� ������� ������� � �����頥� 楫�� �᫮ ���

INT StdLib_DivideDivideLR (INT DD, INT D, INT L)
{
  // �� ���� �� �����, �� �����頥� ����.
  if (DD == 0 || D == 0 || L == 0) return 0;

  // �᫨ �᫠ ������� ��楫� ��� ���⪠ - �믮��塞 ���� ��� ���� �筮��.
  // ���� �믮��塞 ������� � �窮�, ��⥬ �믮��塞 ��� ������� � ��塞 �筮���.
  if (DD % D == 0) return (DD / D) / L;
  else return ((FLOAT) DD / D) / L;
}

// ��� �믮���� ������� ������� � �����頥� 楫�� �᫮ ���

INT StdLib_DivideDivideRL (INT DD, INT D, INT L)
{
  // �� ���� �� �����, �� �����頥� ����.
  if (DD == 0 || D == 0 || L == 0) return 0;

  // �᫨ �᫠ ������� ��楫� ��� ���⪠ - �믮��塞 ���� ��� ���� �筮��.
  // ���� �믮��塞 ������� � �窮�, ��⥬ �믮��塞 ��� ������� � ��塞 �筮���.
  if (DD % D == 0) return L / (DD / D);
  else return L / ((FLOAT) DD / D);
}

// ��� �믮���� ����প� ����� ��⮪� ���

VOID StdLib_Retard (VOID)
{
  // ���� �����஥ �६�.
  #ifdef I386_ARCHITECTURE
   DosSleep (50);
  #else
   DosSleep (10);
  #endif

  // ������.
  return;
}

