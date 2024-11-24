#include "GameManager.h"
#include "ctime"

int main() {
	srand(time(NULL));
	GameManager* gameManager = new GameManager();
	gameManager->Code();
	return 0;
} 