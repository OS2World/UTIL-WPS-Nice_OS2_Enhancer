
// ─── Узнает ширину рамки окна ───

// Frame_window - окно рамки. Возвращаемое значение - ширина рамки.
INT PMMetrics_FrameWidth( HWND Frame_window )
{
 // Узнаем, как выглядит рамка окна.
 LONG Frame_type = FrameType( Frame_window );

 // Если окно имеет обычную рамку:
 if( Frame_type == FT_NORMAL )
  {
   // Узнаем окно рабочего стола.
   HWND Desktop = QueryDesktopWindow();

   // Узнаем ширину рамки по умолчанию.
   INT Normal_frame = Min( WinQuerySysValue( Desktop, SV_CXSIZEBORDER ), WinQuerySysValue( Desktop, SV_CYSIZEBORDER ) );

   // Возвращаем ширину рамки.
   return Normal_frame;
  }

 // Если окно имеет рамку постоянного размера или это плоское окно:
 if( Frame_type == FT_CONST || Frame_type == FT_FLAT )
  {
   // Узнаем окно рабочего стола.
   HWND Desktop = QueryDesktopWindow();

   // Узнаем ширину рамки окна.
   INT Const_frame = Min( WinQuerySysValue( Desktop, SV_CXDLGFRAME ), WinQuerySysValue( Desktop, SV_CYDLGFRAME ) );

   // Возвращаем ширину рамки.
   return Const_frame;
  }

 // А если окно имеет рамку в 1 точку:
 if( Frame_type == FT_POINT )
  {
   // Возвращаем ширину рамки.
   return 1;
  }

 // Если у окна нет рамки - возвращаем ноль.
 return 0;
}
