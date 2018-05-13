#include "stdafx.h"
#include "PasswordManager.h"
#include <string>
#include <sstream>
#include <iomanip>
extern "C" {
#include <openssl/md5.h>
}
using namespace std;

static PasswordManager* pm = nullptr;

PasswordManager::PasswordManager()
{
	this->LicenceCodeList = {
	{ "7ef251c17dcb93537a1c9e7956fad649",PasswordData(TEXT(" 赵晨没有品")) },
	{ "1a08d7b1c63de131c7cc559d2539e2b7",PasswordData(TEXT(" 朱刚没有品")) },
	{ "bd39e5be3f9fa89a3437c72700ccaa4d",PasswordData(TEXT("       品"),750) },
	{ "2ec76b00d174fcdf23debe8ee8fc5a20",PasswordData(TEXT("      无品")) },
	{ "3108b6e15f1df2bc42f95c6acb151734",PasswordData(TEXT("     ZCNP")) },
	{ "1a7164018898c3a12af9a1cb084b6e63",PasswordData(TEXT("     JGNP")) }
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

bool PasswordManager::setKey(std::tstring key)
{
	ByteData bd = stringToByte(key);
	shared_ptr<unsigned char> bytes = bd.ptr;
	string md5 = Encrypt(bytes.get(), bd.byteLength);
	if (LicenceCodeList.find(md5) != LicenceCodeList.cend()) {
		this->encryptedKey = md5;
		return true;
	}
	return false;
}

PasswordData PasswordManager::getData()
{
	unordered_map<string, PasswordData>::const_iterator iter = LicenceCodeList.find(encryptedKey);
	if (iter == LicenceCodeList.cend()) {
		throw new exception("Invaild Key.");
		return NULL;
	}
	return iter->second;
}

PasswordManager::ByteData PasswordManager::stringToByte(std::tstring str)
{
#ifdef UNICODE
	int byteLength = str.length() * 2;
	shared_ptr<unsigned char> bytes(new unsigned char[byteLength]);
	unsigned char* sup = bytes.get();
	for (wchar_t ct : str) {
		*sup = ct >> 8;
		sup++;
		*sup = ct << 8 >> 8;
		sup++;
	}
	return { bytes,byteLength };
#else
	unique_ptr<unsigned char> bytes(new unsigned char[str.length()]);
	strcpy((char*)bytes.get(), str.c_str());
	return { bytes,str.length() };
#endif
}

std::string PasswordManager::Encrypt(const unsigned char * data, int byteLength)
{
	unsigned char output[16];
	memset(output, 0, sizeof(output));
	MD5(data, byteLength, output);
	stringstream stream;
	string target;
	for (int i = 0; i < 16;i++) {
		stream << setfill('0') << setw(2);
		stream << hex << (int)output[i];
	}
	stream >> target;
	return target;
}
