// Методы для определения разновидности окон. Они используются в Repository, поэтому их надо объявить еще и таким образом.

LONG WindowTypes_FrameType (HWND W);
LONG             FrameType (HWND W)    { return WindowTypes_FrameType (W); }

// Виды рамок.
#include "Core\\WindowTypes.h"
