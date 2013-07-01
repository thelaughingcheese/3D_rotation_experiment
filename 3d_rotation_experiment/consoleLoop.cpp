#include "common.h"

void consoleLoop(void *arg){
	for(;;){
		/*char face[64];
		std::cin >> face;
		printf(face);*/

		/*InvalidateRect(*g_hwnd, NULL, false);
		Sleep(16);*/
		std::cout << "x: " << std::endl;
		std::cin >> cubeAxisx;
		std::cout << "y: " << std::endl;
		std::cin >> cubeAxisy;
		std::cout << "z: " << std::endl;
		std::cin >> cubeAxisz;
	}
}