#include "GameManager.h"
#include "ctime"

int main() {
	srand(time(NULL));
	GameManager* gameManager = new GameManager();
	gameManager->Decode();
	gameManager->PrintNewMap();
	gameManager->Start();
	while (true) {
		Timer::DelayExecute(15000, [gameManager]() {
			//gameManager->Code();
			});
		gameManager->Update();
	}
	return 0;
} 