#include <SDL.h>
#include <iostream>
#include <vector>
#include <time.h>

#include "Sprite.h"
#include "Input.h"
#include "Vec2.h"
#include "player.h"
#include "Bullet.h"
#include "Pickup.h"

#include "Pawn.h"
#include "Knight.h"
#include "Rogue.h"
#include "Bishop.h"
#include "Tank.h"
#include "Rook.h"

#include "Boss.h"
#include "BossA.h"

// made this because I got bored whilst waiting for Microsoft Visio to install
void ManageWindow(SDL_Window* window, int score)
{
	if (score >= 0 && score < 100)
	{
		SDL_SetWindowTitle(window, "Hyperspace Fighter");
	}
	else if (score >= 100 && score < 300)
	{
		SDL_SetWindowTitle(window, "Are you actually playing?");
	}
	else if (score >= 300 && score < 1000)
	{
		SDL_SetWindowTitle(window, "You seem to be doing alright");
	}
	else if (score >= 1000 && score < 2500)
	{
		SDL_SetWindowTitle(window, "Glad you made it this far, I hope you enjoyed it :)");
	}
	else
	{
		SDL_SetWindowTitle(window, "Are you cheating?");
	}
}

// the main loop and entire game, would have split game into seperate functions, but didn't see the point
int main(int argc, char *argv[])
{
	// initialise SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "Error" << std::endl;
		return -1;
	}

	// set the window position
	Vec2 winPos;
	winPos.x = 100;
	winPos.y = 100;

	// and window dimensions
	int winWidth = 392;
	int winHeight = 720;

	// more SDL stuff
	SDL_Window *window = SDL_CreateWindow("Hyperspace Fighter", (int)winPos.x, (int)winPos.y, winWidth, winHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);

	// create the input class
	Input input;

	// load in all sprites
	Sprite* playerSprite = new Sprite("PlayerShip.bmp", renderer);
	Sprite* blueBullet = new Sprite("BlueBullet.bmp", renderer);
	Sprite* redBullet = new Sprite("RedBullet.bmp", renderer);
	Sprite* redLaser = new Sprite("RedLaser.bmp", renderer);
		  
	Sprite* baseP = new Sprite("EnemyShip1.bmp", renderer);
	Sprite* baseK = new Sprite("EnemyShip2.bmp", renderer);
	Sprite* baseRG = new Sprite("EnemyShip3.bmp", renderer);
	Sprite* baseB = new Sprite("EnemyShip4.bmp", renderer);
	Sprite* baseT = new Sprite("EnemyShip5.bmp", renderer);
	Sprite* baseR = new Sprite("EnemyShip6.bmp", renderer);

	Sprite* boss1 = new Sprite("Boss1.bmp", renderer);

	Sprite* healthBar = new Sprite("HealthBar.bmp", renderer);
	Sprite* healthBlob = new Sprite("Health.bmp", renderer);
	Sprite* lives = new Sprite("PlayerLive.bmp", renderer);

	Sprite* healthUp = new Sprite("HealthUp.bmp", renderer);
	Sprite* powerUp = new Sprite("PowerUp.bmp", renderer);

	Sprite* numbers[10];
	numbers[0] = new Sprite("0.bmp", renderer);
	numbers[1] = new Sprite("1.bmp", renderer);
	numbers[2] = new Sprite("2.bmp", renderer);
	numbers[3] = new Sprite("3.bmp", renderer);
	numbers[4] = new Sprite("4.bmp", renderer);
	numbers[5] = new Sprite("5.bmp", renderer);
	numbers[6] = new Sprite("6.bmp", renderer);
	numbers[7] = new Sprite("7.bmp", renderer);
	numbers[8] = new Sprite("8.bmp", renderer);
	numbers[9] = new Sprite("9.bmp", renderer);

	Sprite* Menu = new Sprite("Menu.bmp", renderer);
	Sprite* Instructions = new Sprite("Instructions.bmp", renderer);
	Sprite* Dead = new Sprite("Dead.bmp", renderer);
	Sprite* Win = new Sprite("Win.bmp", renderer);

	// that's a lot of sprites o.O
	
	// create the player
	Player* player = new Player(Vec2(winWidth / 2, winHeight - 100), playerSprite->GetW(), playerSprite->GetH());
	player->Bind(Vec2(0, 0), Vec2(winWidth, winHeight));
	player->SetSpeed(3);
	player->SetFireRate(6);
	player->SetBullet(Bullet(blueBullet->GetW(), blueBullet->GetH(), player->Center(), Vec2(winWidth, winHeight), Vec2(0, -1), true, 1));
	
	// the 3 vectors we need for our game, probably could fit the boss into the enemy vector, but it was too much hassle
	std::vector<Bullet*> bullets;
	std::vector<Ship*> enemies;
	std::vector<Ship*> bosses;

	// Uint32 to keep track of the SDL_Ticks to help modulate framerate
	Uint32 ticks;

	// variables to manage gameplay
	float gTimer = -3000;
	float deathTime = 0;
	float lastSpawn = 0;
	bool levelUp = false;
	bool oneBoss = false;
	bool noLives = false;

	int wave = 0;
	bool play = true;
	bool menu = true;
	bool game = false;
	bool instructions = false;
	bool endless = false;
	
	int bulletsSize = 0;
	int enemiesSize = 0;
	int bossesSize = 0;

	int bossWave = 0;

	// THE game loop
	while (play)
	{
		// reset renderer
		SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
		SDL_RenderClear(renderer);

		// change window title based on score
		ManageWindow(window, player->GetScore());

		// update input
		input.Update();

		if (input.quit)
			SDL_Quit(), menu = false, game = false, menu = false, instructions = false, play = false;

		if (menu)
		{
			Menu->Draw(Vec2(0, 0), renderer);

			// because buttons aren't a class, add to-do list
			if (input.mouse)
			{
				// if mouse corresponds to certain positions when clicked, change values to navigate to seperate stages of the game
				if (input.mousePos.x > 90 && input.mousePos.x < 300
					&& input.mousePos.y > 320 && input.mousePos.y < 350)
				{
					menu = false, game = true;
				}
				else if (input.mousePos.x > 90 && input.mousePos.x < 300
					&& input.mousePos.y > 360 && input.mousePos.y < 400)
				{
					menu = false; instructions = true; 
				}
				else if (input.mousePos.x > 90 && input.mousePos.x < 300
					&& input.mousePos.y > 410 && input.mousePos.y < 440)
				{
					menu = false; play = false;
				}
				else if (input.mousePos.x > 90 && input.mousePos.x < 300
					&& input.mousePos.y > 630 && input.mousePos.y < 660)
				{
					menu = false; game = true; endless = true;
				}
			}

			// if the game was triggered in the menu, set all values to starting conditions
			if (game)
			{
				// in case game has been played in same session, go through all vectors and clear them
				int vectorSize = bullets.size();
				for (int i = 0; i < vectorSize;)
				{
					delete bullets[i];
					bullets.erase(bullets.begin() + i);
					vectorSize--;
				}

				vectorSize = enemies.size();
				for (int i = 0; i < vectorSize;)
				{
					delete enemies[i];
					enemies.erase(enemies.begin() + i);
					vectorSize--;
				}

				vectorSize = bosses.size();
				for (int i = 0; i < vectorSize;)
				{
					delete bosses[i];
					bosses.erase(bosses.begin() + i);
					vectorSize--;
				}

				// re-set all game control variables
				gTimer = -3000;
				deathTime = 0;
				lastSpawn = 0;
				levelUp = false;
				oneBoss = false;
				noLives = false;

				wave = 0;

				// re-set the player
				player->Respawn(Vec2(winWidth / 2, winHeight - 100));
				player->SetSpeed(3);
				player->SetFireRate(6);
				player->SetLives(3);
				player->AddScore(0 - player->GetScore());

				// depending on which gamemode was chosen, set the bosswave to a certain number
				if (!endless)
					bossWave = 6;
				else
					bossWave = 256;
			}
		}
		else if (instructions)
		{
			// draw instructions to screen
			Instructions->Draw(0, 0, renderer);

			if (input.esc)
				instructions = false, menu = true;
		}
		else if (game)
		{
			// update timer
			ticks = SDL_GetTicks();
			gTimer += (1000 / 60 - (SDL_GetTicks() - ticks));

			// keep tiner on a 20 second loop for math reasons, and spawn a power up ever half/wave
			if (gTimer > 20000 && !player->Dead())
				gTimer = 0, wave++, levelUp = false;
			else if (gTimer > 18000 && !levelUp)
				enemies.push_back(new Pickup(powerUp->GetW(), powerUp->GetH(), Vec2(40 + rand() % (winWidth - 80), -10), 8, winHeight)), levelUp = true;
			
			// main game control, currently random - based on various variabels, such as the player being dead, or what wave the game is currently on
			if ((int)gTimer % 150 < 5 && (int)gTimer > 0 && !player->Dead() && wave < bossWave)
			{
				// based on random numbers again, spawn certain enemy types randomly
				if (rand() % 15 < wave + 4)
					enemies.push_back(new Pawn(Vec2(40 + rand() % (winWidth - 80), -100), Vec2(baseP->GetW(), baseP->GetH()), 1, Vec2(winWidth, winHeight), 1 + (wave / 2)));
				if (rand() % 15 < wave + 2)
					enemies.push_back(new Knight(Vec2(40 + rand() % (winWidth - 80), -100), Vec2(baseK->GetW(), baseK->GetH()), 2, Vec2(winWidth, winHeight), 2 + (wave / 2), Vec2(redBullet->GetW(), redBullet->GetH())));
				if (rand() % 15 < wave + 4)
					enemies.push_back(new Rogue(Vec2(40 + rand() % (winWidth - 80), -100), Vec2(baseRG->GetW(), baseRG->GetH()), 3, Vec2(winWidth, winHeight), 1 + (wave / 2), Vec2(redBullet->GetW(), redBullet->GetH())));
				if (rand() % 15 < wave + 2)
					enemies.push_back(new Bishop(Vec2(40 + rand() % (winWidth - 80), -100), Vec2(baseB->GetW(), baseB->GetH()), 4, Vec2(winWidth, winHeight), 2 + (wave / 2), Vec2(redBullet->GetW(), redBullet->GetH())));
				if (rand() % 15 < wave - 2)
					enemies.push_back(new Tank(Vec2(40 + rand() % (winWidth - 80), -100), Vec2(baseT->GetW(), baseT->GetH()), 5, Vec2(winWidth, winHeight), 5 + (wave / 2), Vec2(redBullet->GetW(), redBullet->GetH())));
				if (rand() % 15 < wave - 1)
					enemies.push_back(new Rook(Vec2(40 + rand() % (winWidth - 80), -100), Vec2(baseR->GetW(), baseR->GetH()), 6, Vec2(winWidth, winHeight), 2 + (wave / 2), Vec2(redLaser->GetW(), redLaser->GetH())));
			}
			else if (wave >= bossWave && bosses.size() < 1)
			{
				// once the wave counter reaches the boss wave, check to see if a boss has spawned, and spawn one if not
				if (!oneBoss)
				{
					bosses.push_back(new BossA(Vec2((winWidth / 2) - boss1->GetW(), -100), Vec2(boss1->GetW(), boss1->GetH()), 9, Vec2(winWidth, winHeight), 5000, Vec2(redBullet->GetW(), redBullet->GetH())));
					oneBoss = true;
				}
				else
				{
					// if the boss has been spawned AND defeated, display win screen
					Win->Draw(Vec2((winWidth / 2) - (Win->GetW() / 2), (winHeight / 2) - Win->GetH()), renderer);
				}
			}
			
			// randomly spawn health pickups
			if (((int)gTimer % (rand() % 200 + 1)) * 2 < 16 + wave && wave < bossWave)
			{
				if (lastSpawn == 0)
					lastSpawn = gTimer;

				if (gTimer > lastSpawn + 2000)
				{
					lastSpawn = 0;
					enemies.push_back(new Pickup(healthUp->GetW(), healthUp->GetH(), Vec2(40 + rand() % (winWidth - 80), -10), 7, winHeight));
				}
			}
			
			// let the player quit out of the game
			if (input.esc)
				game = false, endless = false, menu = true;

			// update the players

			// if the player is dead
			if (player->Dead())
			{
				// check timer stuff for respawn
				if (deathTime == 0)
					deathTime = gTimer;

				if (gTimer > deathTime + 5000)
				{
					deathTime = 0;

					// if the player has lives left respawn him, otherwise display lose screen
					if (player->GetLives() > 0)
						player->Respawn(Vec2(winWidth / 2, winHeight - 200));
					else
						noLives = true;
				}
				if (noLives)
				{
					Dead->Draw(Vec2((winWidth / 2) - (Dead->GetW() / 2), (winHeight / 2) - Dead->GetH()), renderer);
				}
			}
			else
			{
				player->Update(&input, bullets);
			}
			
			// update all objects
			// local ints because calling bullets.size() for every loop wastes CPU time
			bulletsSize = bullets.size();
			enemiesSize = enemies.size();
			bossesSize = bosses.size();

			// for every bullet
			for (int i = 0; i < bulletsSize;)
			{
				// update
				bullets[i]->Update();

				// check to see who fired the bullet, and draw what bullet relates to the type of bullet
				switch (bullets[i]->isPlayer())
				{
				case true:
					switch (bullets[i]->GetType())
					{
					case 1:
						blueBullet->Draw(bullets[i]->GetPos() + Vec2(blueBullet->GetW() / 2, blueBullet->GetH() / 2), renderer);
						break;
					case 2:
						blueBullet->Draw(bullets[i]->GetPos() + Vec2(blueBullet->GetW() / 2, blueBullet->GetH() / 2), renderer);
						break;
					}
					break;
				case false:
					switch (bullets[i]->GetType())
					{
					case 1:
						redBullet->Draw(bullets[i]->GetPos() + Vec2(redBullet->GetW() / 2, -redBullet->GetH()), renderer);
						break;
					case 2:
						redLaser->Draw(bullets[i]->GetPos() + Vec2(redLaser->GetW() / 2, -redLaser->GetH()), renderer);
						break;
					case 3:
						redBullet->Draw(bullets[i]->GetPos() + Vec2(redBullet->GetW() / 2, -redBullet->GetH()), renderer);
						break;
					}
					break;
				}

				// outside of the drawing, because errors
				if (bullets[i]->isPlayer())
				{
					// test the bullet with every enemy for collision (optimise?)
					for (int i2 = 0; i2 < enemiesSize; i2++)
					{
						if (enemies[i2]->Collide(bullets[i]->GetPos()))
						{
							// becasue the 'ship' class is used for pickups, check to see if the type is below 7 (7 and above are for upgrades, which for now, can't be shot))
							if (enemies[i2]->GetType() < 7)
							{
								bullets[i]->Hit();
								enemies[i2]->Hit();
							}
						}
					}

					// test the bullet with every boss (only 1, but able to use later if more bosses are added)
					for (int i2 = 0; i2 < bossesSize; i2++)
					{
						if (bosses[i2]->Collide(bullets[i]->GetPos()))
						{
							bullets[i]->Hit();
							bosses[i2]->Hit();
						}
					}
				}
				else
				{
					// if the bullet was not shot by the player, test the player for collisions
					if (player->Collide(bullets[i]->GetPos()))
					{
						bullets[i]->Hit();
						player->Hit();
					}
				}

				// if the bullet has hit something or needs to be destroyed, destroy it and adjust the for loop accordingly
				if (bullets[i]->Destroy())
				{
					delete bullets[i], bullets.erase(bullets.begin() + i), bulletsSize--;
				}
				else
				{
					i++;
				}
			}

			// same as bullet, but with enemies
			for (int i = 0; i < enemiesSize;)
			{
				enemies[i]->Update(bullets);

				// if the ship is an enemy
				if (enemies[i]->GetType() < 7)
				{
					// test player collision with enemy
					if (player->Collide(enemies[i]->Center()))
					{
						enemies[i]->Kill();
						player->Kill();
					}
				}
				else // it is a pickup
				{
					if (player->Pickup(enemies[i]->Center()))
					{
						switch (enemies[i]->GetType())
						{
						case 7:			// depending on the type, add effects to the player
							enemies[i]->Kill();
							player->SetHealth(player->GetHealth() + 10);
							break;
						case 8:
							enemies[i]->Kill();
							player->SetFireRate(player->GetFireRate() + 1);
							break;
						case 9:
							enemies[i]->Kill();
							player->SetLives(player->GetLives() + 1);
							break;
						case 10:
							enemies[i]->Kill();
							break;
						}
					}
				}

				// whatever type the enemy is, draw it
				switch (enemies[i]->GetType())
				{
				case 1:
					baseP->Draw(enemies[i]->GetPos(), renderer);
					break;
				case 2:
					baseK->Draw(enemies[i]->GetPos(), renderer);
					break;
				case 3:
					baseRG->Draw(enemies[i]->GetPos(), renderer);
					break;
				case 4:
					baseB->Draw(enemies[i]->GetPos(), renderer);
					break;
				case 5:
					baseT->Draw(enemies[i]->GetPos(), renderer);
					break;
				case 6:
					baseR->Draw(enemies[i]->GetPos(), renderer);
					break;
				case 7:
					healthUp->Draw(enemies[i]->GetPos(), renderer);
					break;
				case 8:
					powerUp->Draw(enemies[i]->GetPos(), renderer);
					break;
				}

				// if enemy needs to be destroyed, destory it and adjust for loop
				if (enemies[i]->Destroy())
				{
					// if the enemy is an enemy type
					if (enemies[i]->GetType() < 7)
					{
						// add score
						if (!player->Dead())
							player->AddScore(enemies[i]->GetType());

						// and give a chance to drop a health kit
						if ((rand() % 200) * 2 < 3 + (1 + wave * 2))
							enemies.push_back(new Pickup(healthUp->GetW(), healthUp->GetH(), enemies[i]->GetPos(), 7, winHeight)), enemiesSize++;
					}

					delete enemies[i];
					enemies.erase(enemies.begin() + i);
					enemiesSize--;
				}
				else
				{
					i++;
				}
			}

			// for the boss(es)
			for (int i = 0; i < bossesSize;)
			{
				bosses[i]->Update(bullets);

				// if the player is alive
				if (player->Dead())
				{
					bosses[i]->DisableShot();
				}

				// if the boss collides with the player
				if (bosses[i]->Collide(player->Center()))
				{
					// kill the player
					player->Kill();
				}

				// draw the boss
				boss1->Draw(bosses[i]->GetPos(), renderer);

				// if the boss needs destroying, delete it
				if (bosses[i]->Destroy())
				{
					delete bosses[i], bosses.erase(bosses.begin() + i), bossesSize--;
				}
				else
				{
					i++;
				}
			}

			// if the player is alive, draw it
			if (!player->Dead())
				playerSprite->Draw(player->GetPos(), renderer);

			// draw UI

			// health bar
			healthBar->Draw(20, 20, renderer);

			// health %
			for (int i = 0; i < player->GetHealth(); i += healthBlob->GetW())
			{
				healthBlob->Draw(23 + i, 23, renderer);
			}

			// lives
			for (int i = 0; i < player->GetLives(); i++)
			{
				if (i < 5)
					lives->Draw(23 + (i * (lives->GetW() + 4)), 45 + lives->GetH(), renderer);
				else
					lives->Draw(23 + (i * (lives->GetW() + 4)), 45 + ((lives->GetH() + 1) * 2), renderer);
			}

			// draw score using bitmaps
			for (int i = 0; i < 5; i++)
			{
				if ((player->GetScore() > 99999))
					player->AddScore(99999 - player->GetScore());

				int index = -1;
				switch (i)
				{
					//using an array of bitmaps, find out which one to use and draw using math
				case 0:
					index = ((int)(player->GetScore() / 10000));
					numbers[index]->Draw(Vec2(280 + (i * 20), 23), renderer);
					break;
				case 1:
					index = ((int)(player->GetScore() / 1000)) - (((int)player->GetScore() / 10000) * 10);
					numbers[index]->Draw(Vec2(280 + (i * 20), 23), renderer);
					break;
				case 2:
					index = ((int)(player->GetScore() / 100)) - (((int)player->GetScore() / 1000) * 10);
					numbers[index]->Draw(Vec2(280 + (i * 20), 23), renderer);
					break;
				case 3:
					index = ((int)player->GetScore() / 10) - (((int)player->GetScore() / 100) * 10);
					numbers[index]->Draw(Vec2(280 + (i * 20), 23), renderer);
					break;
				case 4:
					index = ((int)player->GetScore()) - (((int)player->GetScore() / 10) * 10);
					numbers[index]->Draw(Vec2(280 + (i * 20), 23), renderer);
					break;
				}
			}
		}

		// renderer
		SDL_RenderPresent(renderer);

		// based on SDL stuff, delay the game to keep it at (or below sometimes, but very rarely) at 60fps
		if (1000 / 60 > SDL_GetTicks() - ticks)
			SDL_Delay(1000 / 60 - (SDL_GetTicks() - ticks));
	}
	
	//proceed to empty out all vectors
	int vectorSize = bullets.size();
	for (int i = 0; i < vectorSize;)
	{
		delete bullets[i];
		bullets.erase(bullets.begin() + i);
		vectorSize--;
	}

	vectorSize = enemies.size();
	for (int i = 0; i < vectorSize;)
	{
		delete enemies[i];
		enemies.erase(enemies.begin() + i);
		vectorSize--;
	}

	vectorSize = bosses.size();
	for (int i = 0; i < vectorSize;)
	{
		delete bosses[i];
		bosses.erase(bosses.begin() + i);
		vectorSize--;
	}

	// delete all sprites
	delete player;
	delete playerSprite;
	delete blueBullet;
	delete redBullet;
	delete redLaser;
	delete baseP;
	delete baseK;
	delete baseRG;
	delete baseB;
	delete baseT;
	delete baseR;
	delete boss1;
	delete healthBar;
	delete healthBlob;
	delete healthUp;
	delete lives;
	delete powerUp;
	delete Menu;
	delete Instructions;
	delete Dead;
	delete Win;

	for (int i = 0; i < 10; i++)
	{
		delete numbers[i];
	}

	// end SDL
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}