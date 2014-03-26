// Методы для расположение полей ввода в окнах.
#define LitCreateLayout      Layout_LitCreateLayout
#define LitDeleteLayout      Layout_LitDeleteLayout

#define LitPrepareBrick      Layout_LitPrepareBrick
#define LitJoinBrick         Layout_LitJoinBrick
#define LitCompleteRow       Layout_LitCompleteRow

#define LitApplyLayout       Layout_LitApplyLayout
#define LitShowFrameWindow   Layout_LitShowFrameWindow

// ─── Метод для подключения класса ───

VOID Layout_Start( VOID )
{
 #ifdef Layout
 bzero( &Layout, sizeof( Layout ) );
 #endif

 // Возврат.
 return;
}
