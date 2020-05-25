#include "MainWindow.h"
#include "Game.h"
#include "Objects.h"
#include <random>
using namespace std;

Game::Game(MainWindow& wnd):wnd(wnd), gfx(wnd){
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> xSpeed(-5, 5);
	std::uniform_int_distribution<int> ySpeed(-5, 5);
	std::uniform_int_distribution<int> bSize(100, 300);
	Color bColor[ 3 ] = {Colors::Cyan,Colors::Yellow, Colors::Magenta};
	int iColorCount = 0;

	for (int i = 0; i < numBoxes; i++){
		boxes[ i ].Size = bSize(rng);
		int xMaxPos = (gfx.ScreenWidth - boxes[ i ].Size); // make box not width going past edge of screen
		std::uniform_int_distribution<int> xPos(5, xMaxPos - 5); // set 5 pixel buffer for start
		boxes[ i ].X = xPos(rng);
		int yMaxPos = (gfx.ScreenHeight - boxes[ i ].Size); //same a X
		std::uniform_int_distribution<int> yPos(5, yMaxPos - 5); // same as X
		boxes[ i ].Y = yPos(rng);
		boxes[ i ].velocityX = xSpeed(rng);
		boxes[ i ].velocityY = ySpeed(rng);
		if (iColorCount >= 3){ iColorCount = 0; }
		boxes[ i ].c = bColor[ iColorCount++ ];
	}
}

void Game::Go(){
	gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel(){
	for (int i = 0; i < numBoxes; ++i){
		boxes[ i ].X = boxes[ i ].X + boxes[ i ].velocityX;
		boxes[ i ].Y = boxes[ i ].Y + boxes[ i ].velocityY;
		const int Xold = boxes[ i ].X;
		const int Yold = boxes[ i ].Y;
		boxes[ i ].X = XBound(boxes[ i ].X, boxes[ i ].Size);
		boxes[ i ].Y = YBound(boxes[ i ].Y, boxes[ i ].Size);
		if (boxes[ i ].X != Xold) boxes[ i ].velocityX = -boxes[ i ].velocityX;
		if (boxes[ i ].Y != Yold) boxes[ i ].velocityY = -boxes[ i ].velocityY;
		boxes[ i ].left = boxes[ i ].X;
		boxes[ i ].right = boxes[ i ].X + boxes[ i ].Size;
		boxes[ i ].top = boxes[ i ].Y;
		boxes[ i ].bottom = boxes[ i ].Y + boxes[ i ].Size;
	}
}

int Game::XBound(int x, int Width){
	if (x < 0) return 0;
	else if (x + Width >= gfx.ScreenWidth) return (gfx.ScreenWidth) - Width;
	else return x;
}

int Game::YBound(int y, int Height){
	if (y < 0) return 0;
	else if (y + Height >= gfx.ScreenHeight) return (gfx.ScreenHeight) - Height;
	else return y;
}

void Game::ComposeFrame(){
	for (int i = 0; i < numBoxes; ++i){
		gfx.DrawBox((boxes[ i ].X), boxes[ i ].Y, boxes[ i ].Size, boxes[ i ].c);
		for (int j = 0; j < i; j++){ // compare to all other boxes up to teh last one just drawn in order of layers
			if (j == i)continue; //skip overlaping self check
			// Overlap check, then draw overlap
			if (boxes[ i ].left < boxes[ j ].right &&
				boxes[ i ].right > boxes[ j ].left &&
				boxes[ i ].top < boxes[ j ].bottom &&
				boxes[ i ].bottom > boxes[ j ].top){
				int overlapX1; int overlapX2; int overlapY1; int overlapY2; Color c1 = boxes[ i ].c; Color c2 = boxes[ j ].c; Color c3;
				overlapX1 = std::max(boxes[ i ].left, boxes[ j ].left);
				overlapY1 = std::max(boxes[ i ].top, boxes[ j ].top);
				overlapX2 = std::min(boxes[ i ].right, boxes[ j ].right);
				overlapY2 = std::min(boxes[ i ].bottom, boxes[ j ].bottom);
				c3 = c1.dword & c2.dword;
				gfx.DrawBox(overlapX1, overlapY1, overlapX2, overlapY2, c3);
			}
		}
	}
}
