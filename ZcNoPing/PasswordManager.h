#pragma once
#include <unordered_map>
#include <string>
#include "PasswordData.h"
#include <memory>

class PasswordManager
{
public:
	static PasswordManager* getInstance();
	bool checkKey(std::tstring key);
	PasswordData getDataByKey(std::tstring key);
private:
	PasswordManager();
	std::unordered_map<std::string, PasswordData> LicenceCodeList;
	std::unique_ptr<unsigned char> stringToByte(std::tstring str);
	std::string Encrypt(const unsigned char* data);
};

