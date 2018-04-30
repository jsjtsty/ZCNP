#pragma once
#include <UIlib.h>
class CloseDialog : public DuiLib::WindowImplBase
{
public:
	virtual LPCTSTR GetWindowClassName()const { return _T("ZCNP_Exit"); }
	virtual DuiLib::CDuiString GetSkinFile()override;
	virtual DuiLib::UILIB_RESOURCETYPE GetResourceType() const override;
	virtual DuiLib::CDuiString GetSkinFolder()override { return _T(""); }
	virtual void Notify(DuiLib::TNotifyUI& msg)override;
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)override;
	virtual void InitWindow()override;
private:
	DuiLib::CEditUI* Licence;
};

