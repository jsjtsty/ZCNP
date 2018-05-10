#include "stdafx.h"
#include "PasswordManager.h"
#include <string>
#include <sstream>
extern "C" {
#include <openssl/md5.h>
}
using namespace std;

static PasswordManager* pm = nullptr;

PasswordManager::PasswordManager()
{
	this->LicenceCodeList = {
		{"",L"’‘≥ø√ª”–∆∑"}
	};
}

PasswordManager * PasswordManager::getInstance()
{
	if (pm == nullptr) {
		pm = new PasswordManager();
		return pm;
	}
	return pm;
}

std::unique_ptr<unsigned char> PasswordManager::stringToByte(std::tstring str)
{
#ifdef UNICODE
	int byteLength = str.length() * 2;
	unique_ptr<unsigned char> bytes(new unsigned char[byteLength]);
	unsigned char* sup = bytes.get();
	for (wchar_t ct : str) {
		*sup = ct >> 8;
		sup++;
		*sup = ct << 8 >> 8;
		sup++;
	}
	return bytes;
#else
	unique_ptr<unsigned char> bytes(new unsigned char[str.length()]);
	strcpy((char*)bytes.get(), str.c_str());
	return bytes;
#endif
}

std::string PasswordManager::Encrypt(const unsigned char * data)
{
	unsigned char output[32];
	MD5(data, strlen((const char*)data), output);
	stringstream stream;
	string target;
	for (unsigned char c : output) {
		stream << hex << (int)c;
	}
	stream >> target;
	return target;
}
