#include "stdafx.h"
#include "CloseDialog.h"
#include "resource.h"
#include "MessageBoxOK.h"
#include <openssl/md5.h>
#include "PasswordManager.h"

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
			tstring pass = Licence->GetText().GetData();
			PasswordManager::ByteData bd = PasswordManager::getInstance()->stringToByte(pass);
			string encPass = PasswordManager::getInstance()->Encrypt(bd.ptr.get(), bd.byteLength);
			if (encPass == "f78166dd4024b552911be1696cc7ae78")
			{
				exit(0);
			}
			else
			{
				MessageBoxOK::Show(this->GetHWND(), TEXT("ZCNP - Error"), TEXT("Wrong License Code."));
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

