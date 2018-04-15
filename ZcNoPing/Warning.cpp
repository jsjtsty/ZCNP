#include "stdafx.h"
#include "Warning.h"
#include "resource.h"
using namespace DuiLib;
using namespace std;

DuiLib::CDuiString Warning::GetSkinFile()
{
	TCHAR szBuf[MAX_PATH] = { 0 };
	_stprintf_s(szBuf, MAX_PATH - 1, _T("%d"), IDR_XMLWARNING);
	return szBuf;
}

DuiLib::UILIB_RESOURCETYPE Warning::GetResourceType() const
{
	return UILIB_RESOURCE;
}

void Warning::Notify(DuiLib::TNotifyUI & msg)
{
	if (msg.sType == TEXT("click"))
	{
		if (msg.pSender->GetName() == TEXT("warning_yes"))
		{
			this->Close();
		}
		else if (msg.pSender->GetName() == TEXT("warning_no"))
		{
			exit(0);
			return;
		}
		else if (msg.pSender->GetName() == TEXT("closebtn"))
		{
			exit(0);
			return;
		}
	}
	__super::Notify(msg);
}

LRESULT Warning::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return __super::HandleMessage(uMsg, wParam, lParam);
}

void Warning::InitWindow()
{
	Yes = static_cast<CButtonUI*>(m_PaintManager.FindControl(TEXT("warning_yes")));
	No = static_cast<CButtonUI*>(m_PaintManager.FindControl(TEXT("warning_no")));
	SetLayeredWindowAttributes(m_hWnd, 0, 245, LWA_ALPHA);
}

