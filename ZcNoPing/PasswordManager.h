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
private:
	struct ByteData {
		std::shared_ptr<unsigned char> ptr;
		int byteLength;
	};
	PasswordManager();
	std::unordered_map<std::string, PasswordData> LicenceCodeList;
	ByteData stringToByte(std::tstring str);
	std::string Encrypt(const unsigned char* data, int byteLength);
	std::string encryptedKey;
};

