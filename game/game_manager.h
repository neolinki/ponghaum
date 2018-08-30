#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#define MAX_POINTS 5

#include "../khroma.h"

/** Game phases enumeration **/
enum GameState {
	GameState_WAIT_PLAYERS, // Wait for players
	GameState_PLAY, // Actual game
	GameState_SCORE_DISPLAY, // Display score
};

/** Game communication messages **/
enum GameCommMsg {
	GameCommMsg_INIT4,
};

/** Generic game screen **/
class GameScreen {
	public:
		virtual void init() {}
		virtual void onReceived(GameCommMsg, char[4]) {};
		virtual void animate() = 0;
};

/** Players enumeraction **/
enum GamePlayer {
	PLAYER1,
	PLAYER2
};

/** Game Modes Enumeration **/

enum GameMode {
	NORMAL,
	CONQUER
};

/** Game persistent data **/
struct GameData {
	GamePlayer last_winner; /// Last winner player
	int p1score; /// Score of player 1
	int p2score; /// Score of player 2
	int p3score; /// Score of player 3 (score of other LED strip player 1)
	int p4score; /// Score of player 4 (score of other LED strip player 2)
	int direction; /// last direction of the ball
	int old_p1score; /// Old score of player 1
	int old_p2score; /// Old score of player 2
	bool playing4_enabled; /// Two ponghaum/4players enabled
	bool playing4_master; /// This pinghaum is master in the 4 players game
};


/** Class that manages the game **/
class GameManager {
	private:
		/** Power-on detector helper **/
		bool was_powered;

	public:
		/** Constructor **/
		GameManager();

		/** Initialize game **/
		void init();

		/** Animate outputs and treat inputs **/
		void animate();

		/** Entry point for communication mechanism **/
		void communicate(char type, char msg[4]);

		/** Restart a game **/
		void restart_game();

		/** Play again **/
		void play();

		/** Launch init screen **/
		void initscreen();

		/** Launch rainbow screen **/
		void rainbow();

		/** Show scores **/
		void show_scores();

		/** HardwareTest screen **/
		void test_hardware();

		GameData data;
		GameMode mode;

	private:
		GameState state; /// Current game phase
		LinearAnimator sleeptimer; /// Autoshutdown timer
};

extern GameManager game;

#endif
