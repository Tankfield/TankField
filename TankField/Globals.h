//window size
#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 600


//tank1 positon constatns
#define TANK1_WEAPON_POS_X 2
#define TANK1_WEAPON_POS_Y 42
#define TANK1_POS_Y 455
#define TANK1_POS_X 0

//tank2 position constatnts
#define TANK2_WEAPON_POS_X -15
#define TANK2_WEAPON_POS_Y 42
#define TANK2_POS_Y 455
#define TANK2_POS_X 1100

//weapons degrees for both tanks
#define TANK1_WEAPON_DEGREES 75
#define TANK2_WEAPON_DEGREES -75


//buttons position constants
//create game
#define CREATE_GAME_BUTTON_POS_X 390
#define CREATE_GAME_BUTTON_POS_Y 190

//join game
#define JOIN_GAME_BUTTON_POS_X 450
#define JOIN_GAME_BUTTON_POS_Y 270

//versus 
#define VERSUS_BUTTON_POS_X 470
#define VERSUS_BUTTON_POS_Y 350

//botgame
#define BOTGAME_BUTTON_POS_X 435
#define BOTGAME_BUTTON_POS_Y 430

//exit
#define EXIT_BUTTON_POS_X 530
#define EXIT_BUTTON_POS_Y 510

//ok
#define OK_BUTTON_POS_X
#define OK_BUTTON_POS_Y


#define WIND_DELAY 5
#define MISSILE_DELAY 10

#define MISSILE_FIRE_POWER 1100
#define GRAVITY 1100
#define WIND_POWER 150


#define HOST_IP "localhost"
//46.253.13.147
//78.90.125.149

//packet sent through TCP
#define PACKET_SIZE 8



extern float wind;
//player turns
extern bool toChangeTurn;
extern bool firedMissile;
extern bool player1Turn;
extern bool player2Turn;
//gamemode 
extern bool isClient;
extern bool isServer;
extern bool isVersus;
extern bool isBotGame;

extern bool inGame;