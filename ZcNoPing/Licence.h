#pragma once
#include <UIlib.h>
class Licence : public DuiLib::WindowImplBase
{
public:
	virtual LPCTSTR GetWindowClassName()const { return _T("ZCNP_Licence"); }
	virtual DuiLib::CDuiString GetSkinFile()override;
	virtual DuiLib::UILIB_RESOURCETYPE GetResourceType() const override;
	virtual DuiLib::CDuiString GetSkinFolder()override { return _T(""); }
	virtual void Notify(DuiLib::TNotifyUI& msg)override;
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)override;
	virtual void InitWindow()override;
private:
	DuiLib::CTextUI* ChancesLeft;
	DuiLib::CEditUI* LicenceCode;
	bool CloseAllowed = false;
	int Chance = 3;
};

