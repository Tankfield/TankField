#include "Globals.h"

float wind = 0.0f;
bool toChangeTurn = false;
bool firedMissile = false;
bool player1Turn = true;
bool player2Turn = false;
#ifdef _DEBUG
bool isClient = false;
bool isServer = true;
bool singlePlayer = false;
#else
bool isClient = true;
bool isServer = false;
bool singlePlayer = false;
#endif