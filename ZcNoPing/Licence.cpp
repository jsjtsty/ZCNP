#include "stdafx.h"
#include "Licence.h"
#include "resource.h"
#include <map>
#include "PasswordData.h"
using namespace DuiLib;
using namespace std;

extern const map<const tstring, const PasswordData> LicenceCodeList;

DuiLib::CDuiString Licence::GetSkinFile()
{
	TCHAR szBuf[MAX_PATH] = { 0 };
	_stprintf_s(szBuf, MAX_PATH - 1, _T("%d"), IDR_XMLLICENCE);
	return szBuf;
}

DuiLib::UILIB_RESOURCETYPE Licence::GetResourceType() const
{
	return UILIB_RESOURCE;
}

void Licence::Notify(DuiLib::TNotifyUI & msg)
{
	if (msg.sType == TEXT("click"))
	{
		if (msg.pSender->GetName() == TEXT("licence_submit"))
		{
			tstring code = LicenceCode->GetText();
			if (LicenceCodeList.count(code) == 1) {
				extern tstring LicenceCode;
				LicenceCode = code;
				this->Close();
			}
			else {
				Chance--;
				if (Chance <= 0 || Chance > 3) {
					exit(0);
				}
				else {
					TCHAR chanceStr[2];
					_stprintf(chanceStr, TEXT("%d"), Chance);
					ChancesLeft->SetText((tstring(TEXT("Please enter the licence code. You have ")) + chanceStr + tstring(TEXT(" chances left."))).c_str());
				}
			}
		}
		else if (msg.pSender->GetName() == TEXT("closebtn"))
		{
			exit(0);
			return;
		}
	}
	__super::Notify(msg);
}

LRESULT Licence::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return __super::HandleMessage(uMsg, wParam, lParam);
}

void Licence::InitWindow()
{
	LicenceCode = static_cast<CEditUI*>(m_PaintManager.FindControl(TEXT("password")));
	ChancesLeft = static_cast<CTextUI*>(m_PaintManager.FindControl(TEXT("pwdchancesleft")));
	SetLayeredWindowAttributes(m_hWnd, 0, 245, LWA_ALPHA);
}

