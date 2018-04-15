#include "stdafx.h"
#include <map>
#include "PasswordData.h"

using namespace std;

extern const map<const tstring, const PasswordData> LicenceCodeList{
	{TEXT("964312"),PasswordData(TEXT(" 赵晨没有品"))},
	{TEXT("541632"),PasswordData(TEXT(" 朱刚没有品"))},
	{TEXT("493789"),PasswordData(TEXT("       品"),750)},
	{TEXT("392849"),PasswordData(TEXT("      无品"))},
	{TEXT("938498"),PasswordData(TEXT("     ZCNP"))},
	{TEXT("409148"),PasswordData(TEXT("     JGNP")) }
};

tstring LicenceCode;