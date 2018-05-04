#include "stdafx.h"
#include "CloseDialog.h"
#include "resource.h"
#include "MessageBoxOK.h"

using namespace DuiLib;
using namespace std;


DuiLib::CDuiString CloseDialog::GetSkinFile()
{
	TCHAR szBuf[MAX_PATH] = { 0 };
	_stprintf_s(szBuf, MAX_PATH - 1, _T("%d"), IDR_XMLCLOSE);
	return szBuf;
}

DuiLib::UILIB_RESOURCETYPE CloseDialog::GetResourceType() const
{
	return UILIB_RESOURCE;
}

void CloseDialog::Notify(DuiLib::TNotifyUI & msg)
{
	if (msg.sType == TEXT("click"))
	{
		if (msg.pSender->GetName() == TEXT("closebtn")|| msg.pSender->GetName() == TEXT("close_cancel"))
		{
			this->Close();
			return;
		}
		else if (msg.pSender->GetName() == TEXT("close_ok"))
		{
			if (Licence->GetText() == TEXT("9643"))
			{
				exit(0);
			}
			else
			{
				MessageBoxOK::Show(this->GetHWND(), TEXT("ZCNP 1.1.2"), TEXT("Wrong Licence Code."));
			}
		}
	}
	__super::Notify(msg);
}

LRESULT CloseDialog::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return __super::HandleMessage(uMsg, wParam, lParam);
}

void CloseDialog::InitWindow()
{
	SetLayeredWindowAttributes(m_hWnd, 0, 245, LWA_ALPHA);
	Licence = static_cast<CEditUI*>(m_PaintManager.FindControl(TEXT("lc_exit")));
}

