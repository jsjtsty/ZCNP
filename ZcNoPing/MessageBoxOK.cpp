#include "stdafx.h"
#include "MessageBoxOK.h"
#include "resource.h"
using namespace DuiLib;
using namespace std;

MessageBoxOK::MessageBoxOK(tstring Title, tstring Message, int width, int height)
{
	this->Title = Title;
	this->Message = Message;
	this->height = height;
	this->width = width;
}

DuiLib::CDuiString MessageBoxOK::GetSkinFile()
{
	TCHAR szBuf[MAX_PATH] = { 0 };
	_stprintf_s(szBuf, MAX_PATH - 1, _T("%d"), IDR_XMLMSGBOXOK);
	return szBuf;
}

void MessageBoxOK::Notify(DuiLib::TNotifyUI & msg)
{
	if (msg.sType == TEXT("click"))
	{
		if (msg.pSender->GetName() == TEXT("ok"))
		{
			Close();
		}
	}
	__super::Notify(msg);
}

void MessageBoxOK::InitWindow()
{
	TextTitle = dynamic_cast<CTextUI*>(m_PaintManager.FindControl(TEXT("titletext")));
	TextMessage = dynamic_cast<CTextUI*>(m_PaintManager.FindControl(TEXT("Message")));
	if (width != 350 || height != 180)
	{
		MoveWindow(m_hWnd, CW_USEDEFAULT, CW_USEDEFAULT, width, height, true);
		this->CenterWindow();
	}
	TextTitle->SetText(Title.c_str());
	TextMessage->SetText(Message.c_str());
	SetLayeredWindowAttributes(m_hWnd, 0, 245, LWA_ALPHA);
}

void MessageBoxOK::Show(HWND parent, std::tstring Title, std::tstring Message, int width, int height)
{
	MessageBoxOK msgbox(Title, Message, width, height);
	msgbox.Create(parent, Title.c_str(), UI_WNDSTYLE_DIALOG, WS_EX_LAYERED);
	msgbox.CenterWindow();
	msgbox.ShowModal();
}

DuiLib::UILIB_RESOURCETYPE MessageBoxOK::GetResourceType() const
{
	return UILIB_RESOURCE;
}
