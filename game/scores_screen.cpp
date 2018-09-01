#include "scores_screen.h"

void ScoresScreen::init() {
	khroma.log("Scores : ");
	khroma.log(game.data.p1score);
	khroma.log(" - ");
	khroma.log(game.data.p2score);
	khroma.log("\n");

	score1.init();
	score1.reverse(true);
	if(!game.data.playing4_enabled){
		score1.set_score(game.data.p1score);
	}
	else{
		score1.set_score(3 - game.data.p1score);
	}
	score2.init();
	if(!game.data.playing4_enabled){
		score2.set_score(game.data.p2score);
	}
	else{
		score2.set_score(3 - game.data.p2score);
	}

	ack1 = false;
	ack2 = false;

	fct = 0;
}

void ScoresScreen::animate() {
	khroma.leds.clear();
	score1.animate();
	score2.animate();

	if (score1.fadeout_finished() && score2.fadeout_finished()) {
		if (khroma.btn1.spressed(true) || fct) {
			khroma.leds.set_rgb(-khroma.get_halfsize(), 0xAA, 0xAA, 0xAA);
		}
		if (khroma.btn2.spressed(true) || fct) {
			khroma.leds.set_rgb(+khroma.get_halfsize(), 0xAA, 0xAA, 0xAA);
		}
		if (khroma.btn1.dpressed(true)) {
			khroma.leds.set_rgb(-khroma.get_halfsize(), 0xAA, 0, 0);
		}
		if (khroma.btn2.dpressed(true)) {
			khroma.leds.set_rgb(+khroma.get_halfsize(), 0xAA, 0, 0);
		}
	}

	if (khroma.btn1.dpressed(true) && khroma.btn2.dpressed(true)) {
		fct = &GameManager::initscreen;
		score1.fadeout();
		score2.fadeout();
	}

	if (!ack1 && khroma.btn1.stouched(true)) {
		ack1 = true;
		score1.fadeout();
	}

	if (!ack2 && khroma.btn2.stouched(true)) {
		ack2 = true;
		score2.fadeout();
	}

	if (ack1 && ack2) { 
		if ( !game.data.playing4_enabled) {
			if ((game.mode == CONQUER && (game.data.p1score == game.data.max_points || game.data.p2score == game.data.max_points)) || (game.mode == NORMAL && (game.data.p1score + game.data.p2score == game.data.max_points))) {
			fct = &GameManager::rainbow;
			} else {
				fct = &GameManager::play;
			}
		} else {
			int nb_player_loose = 0;
			if ((3 - game.data.p1score) == 0) {
				nb_player_loose++;
			}
			if ((3-game.data.p2score) == 0) {
				nb_player_loose++;
			}
			if ((3-game.data.p3score) == 0) {
				nb_player_loose++;
			}
			if ((3-game.data.p4score) == 0) {
				nb_player_loose++;
			}

			if (nb_player_loose >= 3) {
				fct = &GameManager::rainbow;
			} else {
				fct = &GameManager::play;
			}
		}
	}

	if (khroma.btn1.released() && khroma.btn2.released() && fct && score1.fadeout_finished() && score2.fadeout_finished()) {
		(game.*fct)();
	}
}
