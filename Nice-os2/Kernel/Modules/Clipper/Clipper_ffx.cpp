
  BYTE Dash_in_Unicode[] = { 0x20, 0x14 };

  BYTE Common_primary_quote_1_in_Unicode[]   = { 0x00, 0xAB }; PBYTE Primary_quote_1_in_Unicode = Common_primary_quote_1_in_Unicode;
  BYTE Common_primary_quote_2_in_Unicode[]   = { 0x00, 0xBB }; PBYTE Primary_quote_2_in_Unicode = Common_primary_quote_2_in_Unicode;
  BYTE Common_secondary_quote_1_in_Unicode[] = { 0x20, 0x1E }; PBYTE Secondary_quote_1_in_Unicode = Common_secondary_quote_1_in_Unicode;
  BYTE Common_secondary_quote_2_in_Unicode[] = { 0x20, 0x1C }; PBYTE Secondary_quote_2_in_Unicode = Common_secondary_quote_2_in_Unicode;

  CHAR Lang[] = "xx"; CHAR Language[] = "xx_XX";

  {
    PCHAR Lng_ptr = NULL; DosScanEnv ("LANG", (PPCSZ) &Lng_ptr);
    if (Lng_ptr != NULL && strlen (Lng_ptr) == strlen (Language))
    {
      strcpy (Language, Lng_ptr);
      Lang[0] = Lng_ptr[0]; Lang[1] = Lng_ptr[1];
    }
  }

  BYTE Afrikaans_primary_quote_1_in_Unicode[]   = { 0x20, 0x1E };
  BYTE Afrikaans_primary_quote_2_in_Unicode[]   = { 0x20, 0x1D };
  BYTE Afrikaans_secondary_quote_1_in_Unicode[] = { 0x20, 0x1A };
  BYTE Afrikaans_secondary_quote_2_in_Unicode[] = { 0x20, 0x19 };
  if (strc (Lang, "af"))
  {
    Primary_quote_1_in_Unicode = Afrikaans_primary_quote_1_in_Unicode;
    Primary_quote_2_in_Unicode = Afrikaans_primary_quote_2_in_Unicode;
    Secondary_quote_1_in_Unicode = Afrikaans_secondary_quote_1_in_Unicode;
    Secondary_quote_2_in_Unicode = Afrikaans_secondary_quote_2_in_Unicode;
  }

  BYTE Albanian_primary_quote_1_in_Unicode[]   = { 0x00, 0xAB };
  BYTE Albanian_primary_quote_2_in_Unicode[]   = { 0x00, 0xBB };
  BYTE Albanian_secondary_quote_1_in_Unicode[] = { 0x20, 0x39 };
  BYTE Albanian_secondary_quote_2_in_Unicode[] = { 0x20, 0x3A };
  if (strc (Lang, "sq"))
  {
    Primary_quote_1_in_Unicode = Albanian_primary_quote_1_in_Unicode;
    Primary_quote_2_in_Unicode = Albanian_primary_quote_2_in_Unicode;
    Secondary_quote_1_in_Unicode = Albanian_secondary_quote_1_in_Unicode;
    Secondary_quote_2_in_Unicode = Albanian_secondary_quote_2_in_Unicode;
  }

  BYTE Belarusian_primary_quote_1_in_Unicode[]   = { 0x00, 0xAB };
  BYTE Belarusian_primary_quote_2_in_Unicode[]   = { 0x00, 0xBB };
  BYTE Belarusian_secondary_quote_1_in_Unicode[] = { 0x20, 0x1E };
  BYTE Belarusian_secondary_quote_2_in_Unicode[] = { 0x20, 0x1C };
  if (strc (Lang, "be"))
  {
    Primary_quote_1_in_Unicode = Belarusian_primary_quote_1_in_Unicode;
    Primary_quote_2_in_Unicode = Belarusian_primary_quote_2_in_Unicode;
    Secondary_quote_1_in_Unicode = Belarusian_secondary_quote_1_in_Unicode;
    Secondary_quote_2_in_Unicode = Belarusian_secondary_quote_2_in_Unicode;
  }

  BYTE Bulgarian_primary_quote_1_in_Unicode[]   = { 0x20, 0x1E };
  BYTE Bulgarian_primary_quote_2_in_Unicode[]   = { 0x20, 0x1C };
  BYTE Bulgarian_secondary_quote_1_in_Unicode[] = { 0x00, 0xAB };
  BYTE Bulgarian_secondary_quote_2_in_Unicode[] = { 0x00, 0xBB };
  if (strc (Lang, "bg"))
  {
    Primary_quote_1_in_Unicode = Bulgarian_primary_quote_1_in_Unicode;
    Primary_quote_2_in_Unicode = Bulgarian_primary_quote_2_in_Unicode;
    Secondary_quote_1_in_Unicode = Bulgarian_secondary_quote_1_in_Unicode;
    Secondary_quote_2_in_Unicode = Bulgarian_secondary_quote_2_in_Unicode;
  }

  BYTE Chinese_primary_quote_1_in_Unicode[]   = { 0x20, 0x1C };
  BYTE Chinese_primary_quote_2_in_Unicode[]   = { 0x20, 0x1D };
  BYTE Chinese_secondary_quote_1_in_Unicode[] = { 0x20, 0x18 };
  BYTE Chinese_secondary_quote_2_in_Unicode[] = { 0x20, 0x19 };
  if (strc (Lang, "zh"))
  {
    Primary_quote_1_in_Unicode = Chinese_primary_quote_1_in_Unicode;
    Primary_quote_2_in_Unicode = Chinese_primary_quote_2_in_Unicode;
    Secondary_quote_1_in_Unicode = Chinese_secondary_quote_1_in_Unicode;
    Secondary_quote_2_in_Unicode = Chinese_secondary_quote_2_in_Unicode;
  }

  BYTE Croatian_primary_quote_1_in_Unicode[]   = { 0x00, 0xBB };
  BYTE Croatian_primary_quote_2_in_Unicode[]   = { 0x00, 0xAB };
  BYTE Croatian_secondary_quote_1_in_Unicode[] = { 0x20, 0x18 };
  BYTE Croatian_secondary_quote_2_in_Unicode[] = { 0x20, 0x19 };
  if (strc (Lang, "hr"))
  {
    Primary_quote_1_in_Unicode = Croatian_primary_quote_1_in_Unicode;
    Primary_quote_2_in_Unicode = Croatian_primary_quote_2_in_Unicode;
    Secondary_quote_1_in_Unicode = Croatian_secondary_quote_1_in_Unicode;
    Secondary_quote_2_in_Unicode = Croatian_secondary_quote_2_in_Unicode;
  }

  BYTE Czech_primary_quote_1_in_Unicode[]   = { 0x20, 0x1E };
  BYTE Czech_primary_quote_2_in_Unicode[]   = { 0x20, 0x1C };
  BYTE Czech_secondary_quote_1_in_Unicode[] = { 0x20, 0x1A };
  BYTE Czech_secondary_quote_2_in_Unicode[] = { 0x20, 0x18 };
  if (strc (Lang, "cs"))
  {
    Primary_quote_1_in_Unicode = Czech_primary_quote_1_in_Unicode;
    Primary_quote_2_in_Unicode = Czech_primary_quote_2_in_Unicode;
    Secondary_quote_1_in_Unicode = Czech_secondary_quote_1_in_Unicode;
    Secondary_quote_2_in_Unicode = Czech_secondary_quote_2_in_Unicode;
  }

  BYTE Danish_primary_quote_1_in_Unicode[]   = { 0x00, 0xBB };
  BYTE Danish_primary_quote_2_in_Unicode[]   = { 0x00, 0xAB };
  BYTE Danish_secondary_quote_1_in_Unicode[] = { 0x20, 0x3A };
  BYTE Danish_secondary_quote_2_in_Unicode[] = { 0x20, 0x39 };
  if (strc (Lang, "da"))
  {
    Primary_quote_1_in_Unicode = Danish_primary_quote_1_in_Unicode;
    Primary_quote_2_in_Unicode = Danish_primary_quote_2_in_Unicode;
    Secondary_quote_1_in_Unicode = Danish_secondary_quote_1_in_Unicode;
    Secondary_quote_2_in_Unicode = Danish_secondary_quote_2_in_Unicode;
  }

  BYTE Dutch_primary_quote_1_in_Unicode[]   = { 0x20, 0x1E };
  BYTE Dutch_primary_quote_2_in_Unicode[]   = { 0x20, 0x1D };
  BYTE Dutch_secondary_quote_1_in_Unicode[] = { 0x20, 0x1A };
  BYTE Dutch_secondary_quote_2_in_Unicode[] = { 0x20, 0x19 };
  if (strc (Lang, "nl"))
  {
    Primary_quote_1_in_Unicode = Dutch_primary_quote_1_in_Unicode;
    Primary_quote_2_in_Unicode = Dutch_primary_quote_2_in_Unicode;
    Secondary_quote_1_in_Unicode = Dutch_secondary_quote_1_in_Unicode;
    Secondary_quote_2_in_Unicode = Dutch_secondary_quote_2_in_Unicode;
  }

  BYTE English_UK_primary_quote_1_in_Unicode[]   = { 0x20, 0x18 };
  BYTE English_UK_primary_quote_2_in_Unicode[]   = { 0x20, 0x19 };
  BYTE English_UK_secondary_quote_1_in_Unicode[] = { 0x20, 0x1C };
  BYTE English_UK_secondary_quote_2_in_Unicode[] = { 0x20, 0x1D };
  if (strc (Language, "en_GB"))
  {
    Primary_quote_1_in_Unicode = English_UK_primary_quote_1_in_Unicode;
    Primary_quote_2_in_Unicode = English_UK_primary_quote_2_in_Unicode;
    Secondary_quote_1_in_Unicode = English_UK_secondary_quote_1_in_Unicode;
    Secondary_quote_2_in_Unicode = English_UK_secondary_quote_2_in_Unicode;
  }

  BYTE English_US_primary_quote_1_in_Unicode[]   = { 0x20, 0x1C };
  BYTE English_US_primary_quote_2_in_Unicode[]   = { 0x20, 0x1D };
  BYTE English_US_secondary_quote_1_in_Unicode[] = { 0x20, 0x18 };
  BYTE English_US_secondary_quote_2_in_Unicode[] = { 0x20, 0x19 };
  if (strc (Language, "en_US"))
  {
    Primary_quote_1_in_Unicode = English_US_primary_quote_1_in_Unicode;
    Primary_quote_2_in_Unicode = English_US_primary_quote_2_in_Unicode;
    Secondary_quote_1_in_Unicode = English_US_secondary_quote_1_in_Unicode;
    Secondary_quote_2_in_Unicode = English_US_secondary_quote_2_in_Unicode;
  }

  BYTE Estonian_primary_quote_1_in_Unicode[]   = { 0x20, 0x1E };
  BYTE Estonian_primary_quote_2_in_Unicode[]   = { 0x20, 0x1C };
  BYTE Estonian_secondary_quote_1_in_Unicode[] = { 0x00, 0xAB };
  BYTE Estonian_secondary_quote_2_in_Unicode[] = { 0x00, 0xBB };
  if (strc (Lang, "et"))
  {
    Primary_quote_1_in_Unicode = Estonian_primary_quote_1_in_Unicode;
    Primary_quote_2_in_Unicode = Estonian_primary_quote_2_in_Unicode;
    Secondary_quote_1_in_Unicode = Estonian_secondary_quote_1_in_Unicode;
    Secondary_quote_2_in_Unicode = Estonian_secondary_quote_2_in_Unicode;
  }

  BYTE Finnish_primary_quote_1_in_Unicode[]   = { 0x20, 0x1D };
  BYTE Finnish_primary_quote_2_in_Unicode[]   = { 0x20, 0x1D };
  BYTE Finnish_secondary_quote_1_in_Unicode[] = { 0x20, 0x19 };
  BYTE Finnish_secondary_quote_2_in_Unicode[] = { 0x20, 0x19 };
  if (strc (Lang, "fi"))
  {
    Primary_quote_1_in_Unicode = Finnish_primary_quote_1_in_Unicode;
    Primary_quote_2_in_Unicode = Finnish_primary_quote_2_in_Unicode;
    Secondary_quote_1_in_Unicode = Finnish_secondary_quote_1_in_Unicode;
    Secondary_quote_2_in_Unicode = Finnish_secondary_quote_2_in_Unicode;
  }

  BYTE French_primary_quote_1_in_Unicode[]   = { 0x00, 0xAB };
  BYTE French_primary_quote_2_in_Unicode[]   = { 0x00, 0xBB };
  BYTE French_secondary_quote_1_in_Unicode[] = { 0x20, 0x39 };
  BYTE French_secondary_quote_2_in_Unicode[] = { 0x20, 0x3A };
  if (strc (Lang, "fr"))
  {
    Primary_quote_1_in_Unicode = French_primary_quote_1_in_Unicode;
    Primary_quote_2_in_Unicode = French_primary_quote_2_in_Unicode;
    Secondary_quote_1_in_Unicode = French_secondary_quote_1_in_Unicode;
    Secondary_quote_2_in_Unicode = French_secondary_quote_2_in_Unicode;
  }

  BYTE German_primary_quote_1_in_Unicode[]   = { 0x20, 0x1E };
  BYTE German_primary_quote_2_in_Unicode[]   = { 0x20, 0x1C };
  BYTE German_secondary_quote_1_in_Unicode[] = { 0x20, 0x1A };
  BYTE German_secondary_quote_2_in_Unicode[] = { 0x20, 0x18 };
  if (strc (Lang, "de"))
  {
    Primary_quote_1_in_Unicode = German_primary_quote_1_in_Unicode;
    Primary_quote_2_in_Unicode = German_primary_quote_2_in_Unicode;
    Secondary_quote_1_in_Unicode = German_secondary_quote_1_in_Unicode;
    Secondary_quote_2_in_Unicode = German_secondary_quote_2_in_Unicode;
  }

  BYTE Greek_primary_quote_1_in_Unicode[]   = { 0x00, 0xAB };
  BYTE Greek_primary_quote_2_in_Unicode[]   = { 0x00, 0xBB };
  BYTE Greek_secondary_quote_1_in_Unicode[] = { 0x20, 0x39 };
  BYTE Greek_secondary_quote_2_in_Unicode[] = { 0x20, 0x3A };
  if (strc (Lang, "el"))
  {
    Primary_quote_1_in_Unicode = Greek_primary_quote_1_in_Unicode;
    Primary_quote_2_in_Unicode = Greek_primary_quote_2_in_Unicode;
    Secondary_quote_1_in_Unicode = Greek_secondary_quote_1_in_Unicode;
    Secondary_quote_2_in_Unicode = Greek_secondary_quote_2_in_Unicode;
  }

  BYTE Hungarian_primary_quote_1_in_Unicode[]   = { 0x20, 0x1E };
  BYTE Hungarian_primary_quote_2_in_Unicode[]   = { 0x20, 0x1D };
  BYTE Hungarian_secondary_quote_1_in_Unicode[] = { 0x00, 0xBB };
  BYTE Hungarian_secondary_quote_2_in_Unicode[] = { 0x00, 0xAB };
  if (strc (Lang, "hu"))
  {
    Primary_quote_1_in_Unicode = Hungarian_primary_quote_1_in_Unicode;
    Primary_quote_2_in_Unicode = Hungarian_primary_quote_2_in_Unicode;
    Secondary_quote_1_in_Unicode = Hungarian_secondary_quote_1_in_Unicode;
    Secondary_quote_2_in_Unicode = Hungarian_secondary_quote_2_in_Unicode;
  }

  BYTE Hebrew_primary_quote_1_in_Unicode[]   = { 0x20, 0x1C };
  BYTE Hebrew_primary_quote_2_in_Unicode[]   = { 0x20, 0x1D };
  BYTE Hebrew_secondary_quote_1_in_Unicode[] = { 0x00, 0xAB };
  BYTE Hebrew_secondary_quote_2_in_Unicode[] = { 0x00, 0xBB };
  if (strc (Lang, "he"))
  {
    Primary_quote_1_in_Unicode = Hebrew_primary_quote_1_in_Unicode;
    Primary_quote_2_in_Unicode = Hebrew_primary_quote_2_in_Unicode;
    Secondary_quote_1_in_Unicode = Hebrew_secondary_quote_1_in_Unicode;
    Secondary_quote_2_in_Unicode = Hebrew_secondary_quote_2_in_Unicode;
  }

  BYTE Icelandic_primary_quote_1_in_Unicode[]   = { 0x20, 0x1E };
  BYTE Icelandic_primary_quote_2_in_Unicode[]   = { 0x20, 0x1C };
  BYTE Icelandic_secondary_quote_1_in_Unicode[] = { 0x20, 0x1A };
  BYTE Icelandic_secondary_quote_2_in_Unicode[] = { 0x20, 0x18 };
  if (strc (Lang, "is"))
  {
    Primary_quote_1_in_Unicode = Icelandic_primary_quote_1_in_Unicode;
    Primary_quote_2_in_Unicode = Icelandic_primary_quote_2_in_Unicode;
    Secondary_quote_1_in_Unicode = Icelandic_secondary_quote_1_in_Unicode;
    Secondary_quote_2_in_Unicode = Icelandic_secondary_quote_2_in_Unicode;
  }

  BYTE Irish_primary_quote_1_in_Unicode[]   = { 0x20, 0x1C };
  BYTE Irish_primary_quote_2_in_Unicode[]   = { 0x20, 0x1D };
  BYTE Irish_secondary_quote_1_in_Unicode[] = { 0x20, 0x18 };
  BYTE Irish_secondary_quote_2_in_Unicode[] = { 0x20, 0x19 };
  if (strc (Lang, "ga"))
  {
    Primary_quote_1_in_Unicode = Irish_primary_quote_1_in_Unicode;
    Primary_quote_2_in_Unicode = Irish_primary_quote_2_in_Unicode;
    Secondary_quote_1_in_Unicode = Irish_secondary_quote_1_in_Unicode;
    Secondary_quote_2_in_Unicode = Irish_secondary_quote_2_in_Unicode;
  }

  BYTE Italian_primary_quote_1_in_Unicode[]   = { 0x00, 0xAB };
  BYTE Italian_primary_quote_2_in_Unicode[]   = { 0x00, 0xBB };
  BYTE Italian_secondary_quote_1_in_Unicode[] = { 0x20, 0x1C };
  BYTE Italian_secondary_quote_2_in_Unicode[] = { 0x20, 0x1D };
  if (strc (Lang, "it"))
  {
    Primary_quote_1_in_Unicode = Italian_primary_quote_1_in_Unicode;
    Primary_quote_2_in_Unicode = Italian_primary_quote_2_in_Unicode;
    Secondary_quote_1_in_Unicode = Italian_secondary_quote_1_in_Unicode;
    Secondary_quote_2_in_Unicode = Italian_secondary_quote_2_in_Unicode;
  }

  BYTE Japanese_primary_quote_1_in_Unicode[]   = { 0x30, 0x0C };
  BYTE Japanese_primary_quote_2_in_Unicode[]   = { 0x30, 0x0D };
  BYTE Japanese_secondary_quote_1_in_Unicode[] = { 0x30, 0x0E };
  BYTE Japanese_secondary_quote_2_in_Unicode[] = { 0x30, 0x0F };
  if (strc (Lang, "ja"))
  {
    Primary_quote_1_in_Unicode = Japanese_primary_quote_1_in_Unicode;
    Primary_quote_2_in_Unicode = Japanese_primary_quote_2_in_Unicode;
    Secondary_quote_1_in_Unicode = Japanese_secondary_quote_1_in_Unicode;
    Secondary_quote_2_in_Unicode = Japanese_secondary_quote_2_in_Unicode;
  }

  BYTE Korean_N_primary_quote_1_in_Unicode[]   = { 0x00, 0xAB };
  BYTE Korean_N_primary_quote_2_in_Unicode[]   = { 0x00, 0xBB };
  BYTE Korean_N_secondary_quote_1_in_Unicode[] = { 0x20, 0x1E };
  BYTE Korean_N_secondary_quote_2_in_Unicode[] = { 0x20, 0x1C };
  if (strc (Language, "ko_KP"))
  {
    Primary_quote_1_in_Unicode = Korean_N_primary_quote_1_in_Unicode;
    Primary_quote_2_in_Unicode = Korean_N_primary_quote_2_in_Unicode;
    Secondary_quote_1_in_Unicode = Korean_N_secondary_quote_1_in_Unicode;
    Secondary_quote_2_in_Unicode = Korean_N_secondary_quote_2_in_Unicode;
  }

  BYTE Korean_S_primary_quote_1_in_Unicode[]   = { 0x20, 0x1C };
  BYTE Korean_S_primary_quote_2_in_Unicode[]   = { 0x20, 0x1D };
  BYTE Korean_S_secondary_quote_1_in_Unicode[] = { 0x20, 0x18 };
  BYTE Korean_S_secondary_quote_2_in_Unicode[] = { 0x20, 0x19 };
  if (strc (Language, "ko_KR"))
  {
    Primary_quote_1_in_Unicode = Korean_S_primary_quote_1_in_Unicode;
    Primary_quote_2_in_Unicode = Korean_S_primary_quote_2_in_Unicode;
    Secondary_quote_1_in_Unicode = Korean_S_secondary_quote_1_in_Unicode;
    Secondary_quote_2_in_Unicode = Korean_S_secondary_quote_2_in_Unicode;
  }

  BYTE Latvian_primary_quote_1_in_Unicode[]   = { 0x00, 0xAB };
  BYTE Latvian_primary_quote_2_in_Unicode[]   = { 0x00, 0xBB };
  BYTE Latvian_secondary_quote_1_in_Unicode[] = { 0x20, 0x1E };
  BYTE Latvian_secondary_quote_2_in_Unicode[] = { 0x20, 0x1D };
  if (strc (Lang, "lv"))
  {
    Primary_quote_1_in_Unicode = Latvian_primary_quote_1_in_Unicode;
    Primary_quote_2_in_Unicode = Latvian_primary_quote_2_in_Unicode;
    Secondary_quote_1_in_Unicode = Latvian_secondary_quote_1_in_Unicode;
    Secondary_quote_2_in_Unicode = Latvian_secondary_quote_2_in_Unicode;
  }

  BYTE Lithuanian_primary_quote_1_in_Unicode[]   = { 0x20, 0x1E };
  BYTE Lithuanian_primary_quote_2_in_Unicode[]   = { 0x20, 0x1C };
  BYTE Lithuanian_secondary_quote_1_in_Unicode[] = { 0x20, 0x1A };
  BYTE Lithuanian_secondary_quote_2_in_Unicode[] = { 0x20, 0x18 };
  if (strc (Lang, "lt"))
  {
    Primary_quote_1_in_Unicode = Lithuanian_primary_quote_1_in_Unicode;
    Primary_quote_2_in_Unicode = Lithuanian_primary_quote_2_in_Unicode;
    Secondary_quote_1_in_Unicode = Lithuanian_secondary_quote_1_in_Unicode;
    Secondary_quote_2_in_Unicode = Lithuanian_secondary_quote_2_in_Unicode;
  }

  BYTE Norwegian_primary_quote_1_in_Unicode[]   = { 0x00, 0xAB };
  BYTE Norwegian_primary_quote_2_in_Unicode[]   = { 0x00, 0xBB };
  BYTE Norwegian_secondary_quote_1_in_Unicode[] = { 0x20, 0x18 };
  BYTE Norwegian_secondary_quote_2_in_Unicode[] = { 0x20, 0x19 };
  if (strc (Lang, "no") ||
      strc (Lang, "nb") ||
      strc (Lang, "nn"))
  {
    Primary_quote_1_in_Unicode = Norwegian_primary_quote_1_in_Unicode;
    Primary_quote_2_in_Unicode = Norwegian_primary_quote_2_in_Unicode;
    Secondary_quote_1_in_Unicode = Norwegian_secondary_quote_1_in_Unicode;
    Secondary_quote_2_in_Unicode = Norwegian_secondary_quote_2_in_Unicode;
  }

  BYTE Polish_primary_quote_1_in_Unicode[]   = { 0x20, 0x1E };
  BYTE Polish_primary_quote_2_in_Unicode[]   = { 0x20, 0x1D };
  BYTE Polish_secondary_quote_1_in_Unicode[] = { 0x20, 0x1A };
  BYTE Polish_secondary_quote_2_in_Unicode[] = { 0x20, 0x19 };
  if (strc (Lang, "pl"))
  {
    Primary_quote_1_in_Unicode = Polish_primary_quote_1_in_Unicode;
    Primary_quote_2_in_Unicode = Polish_primary_quote_2_in_Unicode;
    Secondary_quote_1_in_Unicode = Polish_secondary_quote_1_in_Unicode;
    Secondary_quote_2_in_Unicode = Polish_secondary_quote_2_in_Unicode;
  }

  BYTE Portuguese_primary_quote_1_in_Unicode[]   = { 0x20, 0x1C };
  BYTE Portuguese_primary_quote_2_in_Unicode[]   = { 0x20, 0x1D };
  BYTE Portuguese_secondary_quote_1_in_Unicode[] = { 0x20, 0x18 };
  BYTE Portuguese_secondary_quote_2_in_Unicode[] = { 0x20, 0x19 };
  if (strc (Lang, "pt"))
  {
    Primary_quote_1_in_Unicode = Portuguese_primary_quote_1_in_Unicode;
    Primary_quote_2_in_Unicode = Portuguese_primary_quote_2_in_Unicode;
    Secondary_quote_1_in_Unicode = Portuguese_secondary_quote_1_in_Unicode;
    Secondary_quote_2_in_Unicode = Portuguese_secondary_quote_2_in_Unicode;
  }

  BYTE Romanian_primary_quote_1_in_Unicode[]   = { 0x20, 0x1E };
  BYTE Romanian_primary_quote_2_in_Unicode[]   = { 0x20, 0x1D };
  BYTE Romanian_secondary_quote_1_in_Unicode[] = { 0x00, 0xAB };
  BYTE Romanian_secondary_quote_2_in_Unicode[] = { 0x00, 0xBB };
  if (strc (Lang, "ro"))
  {
    Primary_quote_1_in_Unicode = Romanian_primary_quote_1_in_Unicode;
    Primary_quote_2_in_Unicode = Romanian_primary_quote_2_in_Unicode;
    Secondary_quote_1_in_Unicode = Romanian_secondary_quote_1_in_Unicode;
    Secondary_quote_2_in_Unicode = Romanian_secondary_quote_2_in_Unicode;
  }

  BYTE Russian_primary_quote_1_in_Unicode[]   = { 0x00, 0xAB };
  BYTE Russian_primary_quote_2_in_Unicode[]   = { 0x00, 0xBB };
  BYTE Russian_secondary_quote_1_in_Unicode[] = { 0x20, 0x1E };
  BYTE Russian_secondary_quote_2_in_Unicode[] = { 0x20, 0x1C };
  if (strc (Lang, "ru"))
  {
    Primary_quote_1_in_Unicode = Russian_primary_quote_1_in_Unicode;
    Primary_quote_2_in_Unicode = Russian_primary_quote_2_in_Unicode;
    Secondary_quote_1_in_Unicode = Russian_secondary_quote_1_in_Unicode;
    Secondary_quote_2_in_Unicode = Russian_secondary_quote_2_in_Unicode;
  }

  BYTE Serbian_primary_quote_1_in_Unicode[]   = { 0x20, 0x1E };
  BYTE Serbian_primary_quote_2_in_Unicode[]   = { 0x20, 0x1C };
  BYTE Serbian_secondary_quote_1_in_Unicode[] = { 0x20, 0x1A };
  BYTE Serbian_secondary_quote_2_in_Unicode[] = { 0x20, 0x18 };
  if (strc (Lang, "sr"))
  {
    Primary_quote_1_in_Unicode = Serbian_primary_quote_1_in_Unicode;
    Primary_quote_2_in_Unicode = Serbian_primary_quote_2_in_Unicode;
    Secondary_quote_1_in_Unicode = Serbian_secondary_quote_1_in_Unicode;
    Secondary_quote_2_in_Unicode = Serbian_secondary_quote_2_in_Unicode;
  }

  BYTE Slovak_primary_quote_1_in_Unicode[]   = { 0x20, 0x1E };
  BYTE Slovak_primary_quote_2_in_Unicode[]   = { 0x20, 0x1C };
  BYTE Slovak_secondary_quote_1_in_Unicode[] = { 0x20, 0x1A };
  BYTE Slovak_secondary_quote_2_in_Unicode[] = { 0x20, 0x18 };
  if (strc (Lang, "sk"))
  {
    Primary_quote_1_in_Unicode = Slovak_primary_quote_1_in_Unicode;
    Primary_quote_2_in_Unicode = Slovak_primary_quote_2_in_Unicode;
    Secondary_quote_1_in_Unicode = Slovak_secondary_quote_1_in_Unicode;
    Secondary_quote_2_in_Unicode = Slovak_secondary_quote_2_in_Unicode;
  }

  BYTE Slovene_primary_quote_1_in_Unicode[]   = { 0x20, 0x1E };
  BYTE Slovene_primary_quote_2_in_Unicode[]   = { 0x20, 0x1C };
  BYTE Slovene_secondary_quote_1_in_Unicode[] = { 0x20, 0x1A };
  BYTE Slovene_secondary_quote_2_in_Unicode[] = { 0x20, 0x18 };
  if (strc (Lang, "sl"))
  {
    Primary_quote_1_in_Unicode = Slovene_primary_quote_1_in_Unicode;
    Primary_quote_2_in_Unicode = Slovene_primary_quote_2_in_Unicode;
    Secondary_quote_1_in_Unicode = Slovene_secondary_quote_1_in_Unicode;
    Secondary_quote_2_in_Unicode = Slovene_secondary_quote_2_in_Unicode;
  }

  BYTE Spanish_primary_quote_1_in_Unicode[]   = { 0x00, 0xAB };
  BYTE Spanish_primary_quote_2_in_Unicode[]   = { 0x00, 0xBB };
  BYTE Spanish_secondary_quote_1_in_Unicode[] = { 0x20, 0x1C };
  BYTE Spanish_secondary_quote_2_in_Unicode[] = { 0x20, 0x1D };
  if (strc (Lang, "es"))
  {
    Primary_quote_1_in_Unicode = Spanish_primary_quote_1_in_Unicode;
    Primary_quote_2_in_Unicode = Spanish_primary_quote_2_in_Unicode;
    Secondary_quote_1_in_Unicode = Spanish_secondary_quote_1_in_Unicode;
    Secondary_quote_2_in_Unicode = Spanish_secondary_quote_2_in_Unicode;
  }

  BYTE Swedish_primary_quote_1_in_Unicode[]   = { 0x20, 0x1D };
  BYTE Swedish_primary_quote_2_in_Unicode[]   = { 0x20, 0x1D };
  BYTE Swedish_secondary_quote_1_in_Unicode[] = { 0x20, 0x19 };
  BYTE Swedish_secondary_quote_2_in_Unicode[] = { 0x20, 0x19 };
  if (strc (Lang, "sv"))
  {
    Primary_quote_1_in_Unicode = Swedish_primary_quote_1_in_Unicode;
    Primary_quote_2_in_Unicode = Swedish_primary_quote_2_in_Unicode;
    Secondary_quote_1_in_Unicode = Swedish_secondary_quote_1_in_Unicode;
    Secondary_quote_2_in_Unicode = Swedish_secondary_quote_2_in_Unicode;
  }

  BYTE Turkish_primary_quote_1_in_Unicode[]   = { 0x00, 0xAB };
  BYTE Turkish_primary_quote_2_in_Unicode[]   = { 0x00, 0xBB };
  BYTE Turkish_secondary_quote_1_in_Unicode[] = { 0x20, 0x39 };
  BYTE Turkish_secondary_quote_2_in_Unicode[] = { 0x20, 0x3A };
  if (strc (Lang, "tr"))
  {
    Primary_quote_1_in_Unicode = Turkish_primary_quote_1_in_Unicode;
    Primary_quote_2_in_Unicode = Turkish_primary_quote_2_in_Unicode;
    Secondary_quote_1_in_Unicode = Turkish_secondary_quote_1_in_Unicode;
    Secondary_quote_2_in_Unicode = Turkish_secondary_quote_2_in_Unicode;
  }

  BYTE Ukrainian_primary_quote_1_in_Unicode[]   = { 0x00, 0xAB };
  BYTE Ukrainian_primary_quote_2_in_Unicode[]   = { 0x00, 0xBB };
  BYTE Ukrainian_secondary_quote_1_in_Unicode[] = { 0x20, 0x1E };
  BYTE Ukrainian_secondary_quote_2_in_Unicode[] = { 0x20, 0x1C };
  if (strc (Lang, "uk"))
  {
    Primary_quote_1_in_Unicode = Ukrainian_primary_quote_1_in_Unicode;
    Primary_quote_2_in_Unicode = Ukrainian_primary_quote_2_in_Unicode;
    Secondary_quote_1_in_Unicode = Ukrainian_secondary_quote_1_in_Unicode;
    Secondary_quote_2_in_Unicode = Ukrainian_secondary_quote_2_in_Unicode;
  }


