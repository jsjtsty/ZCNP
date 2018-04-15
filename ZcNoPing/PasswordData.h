#pragma once
#include "stdafx.h"
class PasswordData
{
public:
	PasswordData(std::tstring data, int width = 800, int height = 500);
	std::tstring GetData()const;
	int GetWidth()const;
	int GetHeight()const;
private:
	std::tstring Data;
	int Width;
	int Height;
};

