#include "stdafx.h"
#include "PasswordData.h"
using namespace std;


PasswordData::PasswordData(tstring data, int width, int height)
{
	Data = data;
	Width = width;
	Height = height;
}

std::tstring PasswordData::GetData()const
{
	return Data;
}

int PasswordData::GetWidth()const
{
	return Width;
}

int PasswordData::GetHeight()const
{
	return Height;
}
