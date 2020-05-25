#pragma once
#include <string>
#include "Colors.h"
using namespace std;
class Objects{
public:
	class Box{
	public:
		int X=0;
		int Y=0;
		int Size=0;
		int velocityX=0;
		int velocityY=0;
		int left = X;
		int top = Y;
		int right = X + Size;
		int bottom = Y + Size;
		Color c;
		std::string objType = "Box";
	private:
	};
protected:
private:
};
