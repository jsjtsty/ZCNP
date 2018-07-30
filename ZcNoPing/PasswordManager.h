#pragma once
#include <unordered_map>
#include <string>
#include "PasswordData.h"
#include <memory>

class PasswordManager
{
public:
	static PasswordManager* getInstance();
	bool setKey(std::tstring key);
	PasswordData getData();
	struct ByteData {
		std::shared_ptr<unsigned char> ptr;
		int byteLength;
	};
	ByteData stringToByte(std::tstring str);
	std::string Encrypt(const unsigned char* data, int byteLength);
private:
	PasswordManager();
	std::unordered_map<std::string, PasswordData> LicenceCodeList;
	std::string encryptedKey;
};

