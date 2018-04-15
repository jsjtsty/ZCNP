#pragma once
#include <UIlib.h>
class Warning : public DuiLib::WindowImplBase
{
public:
	virtual LPCTSTR    GetWindowClassName()const { return _T("ZCNP_Warning"); }
	virtual DuiLib::CDuiString GetSkinFile()override;
	virtual DuiLib::UILIB_RESOURCETYPE GetResourceType() const override;
	virtual DuiLib::CDuiString GetSkinFolder()override { return _T(""); }
	virtual void Notify(DuiLib::TNotifyUI& msg)override;
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)override;
	virtual void InitWindow()override;
private:
	DuiLib::CButtonUI *Yes, *No;
};
