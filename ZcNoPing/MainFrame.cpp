#include "stdafx.h"
#include "MainFrame.h"
#include "resource.h"
#include "AboutDialog.h"
#include <Windows.h>
#include <map>
#include "PasswordData.h"
#include "Reenter.h"
#include "CloseDialog.h"

using namespace std;
using namespace DuiLib;
COptionUI* SwitchSelected;
extern const map<const tstring, const PasswordData> LicenceCodeList;
extern tstring LicenceCode;

void MainFrame::Notify(DuiLib::TNotifyUI & msg)
{
	if (msg.sType == TEXT("selectchanged"))
	{
		tstring name = msg.pSender->GetName(), groupname;
		COptionUI* option = dynamic_cast<COptionUI*>(msg.pSender);
		if (option != nullptr)
			groupname = option->GetGroup();
		if (groupname == TEXT("switch"))
		{
			CTabLayoutUI* tab = dynamic_cast<CTabLayoutUI*>(m_PaintManager.FindControl(TEXT("switchgroup")));
			if (name == TEXT("OptionShow"))
			{
				
			}
			else if (name == TEXT("OptionAbout"))
			{
				COptionUI* show = static_cast<COptionUI*>(m_PaintManager.FindControl(TEXT("OptionShow")));
				show->Selected(true);
				AboutDialog gui3;
				gui3.Create(NULL, TEXT("ZCNP 1.1.2"), UI_WNDSTYLE_DIALOG, WS_EX_WINDOWEDGE);
				gui3.CenterWindow();
				gui3.ShowModal();
			}
			else if (name == TEXT("OptionSetting"))
			{
				COptionUI* show = static_cast<COptionUI*>(m_PaintManager.FindControl(TEXT("OptionShow")));
				show->Selected(true);
				Reenter re(GetHWND());
				re.Create(NULL, TEXT("ZCNP 1.1.2"), UI_WNDSTYLE_DIALOG, WS_EX_WINDOWEDGE);
				re.CenterWindow();
				re.ShowModal();
			}
		}
	}
	else if (msg.sType == TEXT("click"))
	{
		tstring name = msg.pSender->GetName();
		if (name == TEXT("closebtn"))
		{
			CloseDialog dialog;
			dialog.Create(NULL, TEXT("ZCNP 1.1.2"), UI_WNDSTYLE_DIALOG, WS_EX_WINDOWEDGE);
			dialog.CenterWindow();
			dialog.ShowModal();
			return;
		}
	}
	__super::Notify(msg);
}

LRESULT MainFrame::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_UPDATETEXT) {
		Text = static_cast<CTextUI*>(m_PaintManager.FindControl(TEXT("text_show")));
		if (LicenceCodeList.count(LicenceCode) == 1) {
			map<const tstring, const PasswordData>::const_iterator i = LicenceCodeList.find(LicenceCode);
			Text->SetText(i->second.GetData().c_str());
			SetWindowPos(GetHWND(), NULL, 0, 0, i->second.GetWidth(), i->second.GetHeight(), SWP_NOZORDER | SWP_NOMOVE);
		}
	}
	return __super::HandleMessage(uMsg, wParam, lParam);
}

DuiLib::CDuiString MainFrame::GetSkinFile()
{
	TCHAR szBuf[MAX_PATH] = { 0 };
	_stprintf_s(szBuf, MAX_PATH - 1, _T("%d"), IDR_XMLMAINFRAME);
	return szBuf;
}

void MainFrame::InitWindow()
{
	Text = static_cast<CTextUI*>(m_PaintManager.FindControl(TEXT("text_show")));
	if (LicenceCodeList.count(LicenceCode) == 1) {
		map<const tstring, const PasswordData>::const_iterator i = LicenceCodeList.find(LicenceCode);
		Text->SetText(i->second.GetData().c_str());
		SetWindowPos(GetHWND(), NULL, 0, 0, i->second.GetWidth(), i->second.GetHeight(), SWP_NOZORDER | SWP_NOMOVE);
	}
	else {
		exit(-1);
	}
	__super::InitWindow();
}

DuiLib::UILIB_RESOURCETYPE MainFrame::GetResourceType() const
{
	return UILIB_RESOURCE;
}

