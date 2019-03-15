#include "stdafx.h"
#include "Licence.h"
#include "resource.h"
#include <map>
#include "PasswordData.h"
#include "PasswordManager.h"
using namespace DuiLib;
using namespace std;

#define AM_FLIKERSTART     1
#define AM_FLIKERHIDE      2
#define AM_FLIKERSHOWSTART 3
#define AM_FLIKERSHOW      4
#define AM_FADE            5

namespace {
	int FlikerShowCount = 0;
	int FadeCount = 0;
	bool IsAnimating = false;
	DWORD FadeRGB = DUIRGB(255, 0, 0);
}

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
			if (PasswordManager::getInstance()->setKey(code)) {
				CloseAllowed = true;
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
					ChancesLeft->SetText((tstring(TEXT(" You have ")) + chanceStr + tstring(TEXT(" chances left."))).c_str());
					ChancesLeft->SetTextColor(DUIRGB(255, 0, 0));
					if (!IsAnimating) {
						IsAnimating = true;
						SetTimer(GetHWND(), AM_FLIKERSHOWSTART, 150, NULL);
						SetTimer(GetHWND(), AM_FLIKERHIDE, 300, NULL);
					}
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
	if (uMsg == WM_TIMER) {
		switch (wParam) {
		case AM_FLIKERSHOWSTART:
			KillTimer(GetHWND(), AM_FLIKERSHOWSTART);
			SetTimer(GetHWND(), AM_FLIKERSHOW, 300, NULL);
			break;
		case AM_FLIKERHIDE:
			ChancesLeft->SetVisible(false);
			break;
		case AM_FLIKERSHOW:
			ChancesLeft->SetVisible(true);
			++FlikerShowCount;
			if (FlikerShowCount >= 2) {
				KillTimer(GetHWND(), AM_FLIKERHIDE);
				KillTimer(GetHWND(), AM_FLIKERSHOW);
				SetTimer(GetHWND(), AM_FADE, 50, NULL);
				FlikerShowCount = 0;
			}
			break;
		case AM_FADE:
			++FadeCount;
			if (FadeCount * 15 >= 255) {
				ChancesLeft->SetTextColor(DUIRGB(255, 255, 255));
				KillTimer(GetHWND(), AM_FADE);
				FadeCount = 0;
				IsAnimating = false;
				break;
			}
			ChancesLeft->SetTextColor(DUIRGB(255, FadeCount * 15, FadeCount * 15));
			break;
		}
	}
	else if (uMsg == WM_CLOSE) {
		if (!CloseAllowed) {
			exit(0);
		}
	}
	return __super::HandleMessage(uMsg, wParam, lParam);
}

void Licence::InitWindow()
{
	LicenceCode = static_cast<CEditUI*>(m_PaintManager.FindControl(TEXT("password")));
	ChancesLeft = static_cast<CTextUI*>(m_PaintManager.FindControl(TEXT("pwd_chances")));
	SetLayeredWindowAttributes(m_hWnd, 0, 245, LWA_ALPHA);
}

