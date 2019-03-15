#include "stdafx.h"
#include "Ready.h"
#include "resource.h"
using namespace DuiLib;
using namespace std;

DuiLib::CDuiString Ready::GetSkinFile()
{
	TCHAR szBuf[MAX_PATH] = { 0 };
	_stprintf_s(szBuf, MAX_PATH - 1, _T("%d"), IDR_XMLREADY);
	return szBuf;
}

DuiLib::UILIB_RESOURCETYPE Ready::GetResourceType() const
{
	return UILIB_RESOURCE;
}

void Ready::Notify(DuiLib::TNotifyUI & msg)
{
	if (msg.sType == TEXT("click"))
	{
		if (msg.pSender->GetName() == TEXT("ready_ok"))
		{
			CloseAllowed = true;
			this->Close();
		}
		else if (msg.pSender->GetName() == TEXT("closebtn"))
		{
			exit(0);
			return;
		}
	}
	__super::Notify(msg);
}

LRESULT Ready::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_CLOSE) {
		if (!CloseAllowed) {
			exit(0);
		}
	}
	return __super::HandleMessage(uMsg, wParam, lParam);
}

void Ready::InitWindow()
{
	SetLayeredWindowAttributes(m_hWnd, 0, 245, LWA_ALPHA);
}

