#pragma once
#include "Graphics.h"
#include "Objects.h"

class Game{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	int XBound(int x, int Size);
	int YBound(int y, int Size);
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	static constexpr int numBoxes = 3;
	Objects::Box boxes[ numBoxes ];
	/********************************/
};