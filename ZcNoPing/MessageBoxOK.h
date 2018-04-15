#pragma once
#include <UIlib.h>

class MessageBoxOK : public DuiLib::WindowImplBase
{
public:
	virtual LPCTSTR    GetWindowClassName()const { return _T("ZCNP_MessageBoxOK"); }
	virtual DuiLib::CDuiString GetSkinFile()override;
	virtual DuiLib::CDuiString GetSkinFolder()override { return _T(""); }
	virtual void Notify(DuiLib::TNotifyUI& msg)override;
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)override { return __super::HandleMessage(uMsg, wParam, lParam); }
	virtual void InitWindow()override;
	static void Show(HWND parent, std::tstring Title, std::tstring Message, int width = 350, int height = 180);
	virtual DuiLib::UILIB_RESOURCETYPE GetResourceType() const override;
private:
	MessageBoxOK(std::tstring Title, std::tstring Message, int width = 350, int height = 180);
	std::tstring Title, Message;
	int width, height;
	DuiLib::CTextUI *TextTitle, *TextMessage;
};

