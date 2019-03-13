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
	{ "cbf58ae107f1490995be98cab8116181",PasswordData(TEXT("  ZC 没有品")) },
	{ "492a726b76c27117eb07c3e5f3649620",PasswordData(TEXT("  JG 没有品")) },
	{ "ea96dcda7eb994afef087fdf77cf9d66",PasswordData(TEXT("       品"),750) },
	{ "896763d1fbfd58f44f15f4d32ee69695",PasswordData(TEXT("      无品")) },
	{ "b31a470fa23ffc490c7c1d7834c3ec13",PasswordData(TEXT("     ZCNP")) },
	{ "ea31ff6fb0e92a95915c4768b982394d",PasswordData(TEXT("     JGNP")) }
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
