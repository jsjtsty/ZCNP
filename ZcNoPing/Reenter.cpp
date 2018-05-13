#include "stdafx.h"
#include "Reenter.h"
#include "resource.h"
#include <map>
#include "PasswordData.h"
#include "MessageBoxOK.h"
#include "PasswordManager.h"
#define PM PasswordManager::getInstance()
using namespace DuiLib;
using namespace std;

extern const map<const tstring, const PasswordData> LicenceCodeList;

DuiLib::CDuiString Reenter::GetSkinFile()
{
	TCHAR szBuf[MAX_PATH] = { 0 };
	_stprintf_s(szBuf, MAX_PATH - 1, _T("%d"), IDR_XMLREENTER);
	return szBuf;
}

DuiLib::UILIB_RESOURCETYPE Reenter::GetResourceType() const
{
	return UILIB_RESOURCE;
}

void Reenter::Notify(DuiLib::TNotifyUI & msg)
{
	if (msg.sType == TEXT("click"))
	{
		if (msg.pSender->GetName() == TEXT("rep_submit"))
		{
			tstring code = LicenceCode->GetText();
			if (PM->setKey(code)) {
				::SendMessage(Main, WM_UPDATETEXT, 0, 0);
				this->Close();
			}
			else {
				MessageBoxOK::Show(GetHWND(), TEXT("ZCNP - Wrong Code"), TEXT("Please enter a vaild licence code."));
			}
		}
		else if (msg.pSender->GetName() == TEXT("closebtn"))
		{
			this->Close();
			return;
		}
	}
	__super::Notify(msg);
}

LRESULT Reenter::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return __super::HandleMessage(uMsg, wParam, lParam);
}

void Reenter::InitWindow()
{
	LicenceCode = static_cast<CEditUI*>(m_PaintManager.FindControl(TEXT("rep_licence")));
	SetLayeredWindowAttributes(m_hWnd, 0, 245, LWA_ALPHA);
}

Reenter::Reenter(HWND Main)
{
	this->Main = Main;
}

