#pragma once
#include <UIlib.h>

class MainFrame : public DuiLib::WindowImplBase
{
public:
	virtual DuiLib::CDuiString GetSkinFolder()override { return _T(""); }
	virtual void Notify(DuiLib::TNotifyUI& msg)override;
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)override;
	virtual LPCTSTR    GetWindowClassName()const override { return _T("MainFrame"); }
	virtual DuiLib::CDuiString GetSkinFile()override;
	virtual void InitWindow()override;
	virtual DuiLib::UILIB_RESOURCETYPE GetResourceType() const override;
private:
	DuiLib::CTextUI *VersionText, *Text;
};
