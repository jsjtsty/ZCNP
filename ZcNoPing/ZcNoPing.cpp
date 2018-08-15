// ZcNoPing.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "ZcNoPing.h"
#include "Licence.h"
#include "Ready.h"
#include "Warning.h"
#include "MainFrame.h"
#include "PasswordManager.h"

using namespace DuiLib;




int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	CPaintManagerUI::SetInstance(hInstance);
	Licence gui;
	gui.Create(NULL, TEXT("ZCNP"), UI_WNDSTYLE_DIALOG, WS_EX_WINDOWEDGE);
	gui.CenterWindow();
	gui.ShowModal();
	/*
	Warning gui2;
	gui2.Create(NULL, TEXT("ZCNP"), UI_WNDSTYLE_DIALOG, WS_EX_WINDOWEDGE);
	gui2.CenterWindow();
	gui2.ShowModal();
	*/
	Ready gui3;
	gui3.Create(NULL, TEXT("ZCNP"), UI_WNDSTYLE_DIALOG, WS_EX_WINDOWEDGE);
	gui3.CenterWindow();
	gui3.ShowModal();
	MainFrame mf;
	mf.Create(NULL, TEXT("ZCNP"), UI_WNDSTYLE_DIALOG, WS_EX_WINDOWEDGE);
	mf.CenterWindow();
	mf.ShowModal();
	return 0;
}
