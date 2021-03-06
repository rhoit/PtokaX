/*
 * PtokaX - hub server for Direct Connect peer to peer network.

 * Copyright (C) 2004-2015  Petr Kozelka, PPK at PtokaX dot org

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3
 * as published by the Free Software Foundation.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

//---------------------------------------------------------------------------
#include "../core/stdinc.h"
//---------------------------------------------------------------------------
#include "LineDialog.h"
//---------------------------------------------------------------------------
#include "../core/LanguageManager.h"
#include "../core/ServerManager.h"
//---------------------------------------------------------------------------
#include "GuiSettingManager.h"
#include "GuiUtil.h"
//---------------------------------------------------------------------------
#pragma hdrstop
//---------------------------------------------------------------------------
#include "Resources.h"
//---------------------------------------------------------------------------
static ATOM atomLineDialog = 0;
//---------------------------------------------------------------------------
void (*pOnOk)(char * Line, const int &iLen) = NULL;
//---------------------------------------------------------------------------

LineDialog::LineDialog(void (*pOnOkFunction)(char * Line, const int &iLen)) {
    memset(&hWndWindowItems, 0, sizeof(hWndWindowItems));

	pOnOk = pOnOkFunction;
}
//---------------------------------------------------------------------------

LineDialog::~LineDialog() {
    pOnOk = NULL;
}
//---------------------------------------------------------------------------

LRESULT CALLBACK LineDialog::StaticLineDialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	LineDialog * pLineDialog = (LineDialog *)::GetWindowLongPtr(hWnd, GWLP_USERDATA);

	if(pLineDialog == NULL) {
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	return pLineDialog->LineDialogProc(uMsg, wParam, lParam);
}
//------------------------------------------------------------------------------

LRESULT LineDialog::LineDialogProc(UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch(uMsg) {
        case WM_SETFOCUS:
            ::SetFocus(hWndWindowItems[EDT_LINE]);

            return 0;
        case WM_COMMAND:
           switch(LOWORD(wParam)) {
                case IDOK: {
                    int iLen = ::GetWindowTextLength(hWndWindowItems[EDT_LINE]);
                    if(iLen != 0) {
                        char * sBuf = new (std::nothrow) char[iLen + 1];

                        if(sBuf != NULL) {
                            ::GetWindowText(hWndWindowItems[EDT_LINE], sBuf, iLen + 1);
                            (*pOnOk)(sBuf, iLen);
                        }

                        delete [] sBuf;
                    }
                }
                case IDCANCEL:
                    ::PostMessage(hWndWindowItems[WINDOW_HANDLE], WM_CLOSE, 0, 0);
					return 0;
            }

            break;
        case WM_CLOSE:
            ::EnableWindow(::GetParent(hWndWindowItems[WINDOW_HANDLE]), TRUE);
            clsServerManager::hWndActiveDialog = NULL;
            break;
        case WM_NCDESTROY: {
            HWND hWnd = hWndWindowItems[WINDOW_HANDLE];
            delete this;
            return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
        }
    }

	return ::DefWindowProc(hWndWindowItems[WINDOW_HANDLE], uMsg, wParam, lParam);
}
//------------------------------------------------------------------------------

void LineDialog::DoModal(HWND hWndParent, char * Caption, char * Line) {
    if(atomLineDialog == 0) {
        WNDCLASSEX m_wc;
        memset(&m_wc, 0, sizeof(WNDCLASSEX));
        m_wc.cbSize = sizeof(WNDCLASSEX);
        m_wc.lpfnWndProc = ::DefWindowProc;
        m_wc.hbrBackground = (HBRUSH)(COLOR_3DFACE + 1);
        m_wc.lpszClassName = "PtokaX_LineDialog";
        m_wc.hInstance = clsServerManager::hInstance;
        m_wc.hCursor = ::LoadCursor(m_wc.hInstance, IDC_ARROW);
        m_wc.style = CS_HREDRAW | CS_VREDRAW;

        atomLineDialog = ::RegisterClassEx(&m_wc);
    }

    RECT rcParent;
    ::GetWindowRect(hWndParent, &rcParent);

    int iX = (rcParent.left + (((rcParent.right-rcParent.left))/2)) - (ScaleGui(306) / 2);
    int iY = (rcParent.top + ((rcParent.bottom-rcParent.top)/2)) - (ScaleGui(105) / 2);

    hWndWindowItems[WINDOW_HANDLE] = ::CreateWindowEx(WS_EX_DLGMODALFRAME | WS_EX_WINDOWEDGE, MAKEINTATOM(atomLineDialog), (string(Caption) + ":").c_str(),
        WS_POPUP | WS_CAPTION | WS_SYSMENU | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, iX, iY, ScaleGui(306), ScaleGui(105), hWndParent, NULL, clsServerManager::hInstance, NULL);

    if(hWndWindowItems[WINDOW_HANDLE] == NULL) {
        return;
    }

    clsServerManager::hWndActiveDialog = hWndWindowItems[WINDOW_HANDLE];

    ::SetWindowLongPtr(hWndWindowItems[WINDOW_HANDLE], GWLP_USERDATA, (LONG_PTR)this);
    ::SetWindowLongPtr(hWndWindowItems[WINDOW_HANDLE], GWLP_WNDPROC, (LONG_PTR)StaticLineDialogProc);

    {
        ::GetClientRect(hWndWindowItems[WINDOW_HANDLE], &rcParent);

        int iHeight = clsGuiSettingManager::iOneLineGB + clsGuiSettingManager::iEditHeight + 6;

        int iDiff = rcParent.bottom - iHeight;

        if(iDiff != 0) {
            ::GetWindowRect(hWndParent, &rcParent);

            iY = (rcParent.top + ((rcParent.bottom-rcParent.top)/2)) - ((ScaleGui(100) - iDiff) / 2);

            ::GetWindowRect(hWndWindowItems[WINDOW_HANDLE], &rcParent);

            ::SetWindowPos(hWndWindowItems[WINDOW_HANDLE], NULL, iX, iY, (rcParent.right-rcParent.left), (rcParent.bottom-rcParent.top) - iDiff, SWP_NOZORDER);
        }
    }

    ::GetClientRect(hWndWindowItems[WINDOW_HANDLE], &rcParent);

    hWndWindowItems[GB_LINE] = ::CreateWindowEx(WS_EX_TRANSPARENT, WC_BUTTON, "", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 5, 0, rcParent.right - 10, clsGuiSettingManager::iOneLineGB,
        hWndWindowItems[WINDOW_HANDLE], NULL, clsServerManager::hInstance, NULL);

    hWndWindowItems[EDT_LINE] = ::CreateWindowEx(WS_EX_CLIENTEDGE, WC_EDIT, Line, WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_AUTOHSCROLL,
        13, clsGuiSettingManager::iGroupBoxMargin, rcParent.right - 26, clsGuiSettingManager::iEditHeight, hWndWindowItems[WINDOW_HANDLE], NULL, clsServerManager::hInstance, NULL);
    ::SendMessage(hWndWindowItems[EDT_LINE], EM_SETSEL, 0, -1);

    hWndWindowItems[BTN_OK] = ::CreateWindowEx(0, WC_BUTTON, clsLanguageManager::mPtr->sTexts[LAN_ACCEPT], WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON,
        4, clsGuiSettingManager::iOneLineGB + 4, (rcParent.right / 2) - 5, clsGuiSettingManager::iEditHeight, hWndWindowItems[WINDOW_HANDLE], (HMENU)IDOK, clsServerManager::hInstance, NULL);

    hWndWindowItems[BTN_CANCEL] = ::CreateWindowEx(0, WC_BUTTON, clsLanguageManager::mPtr->sTexts[LAN_DISCARD], WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON,
        rcParent.right - ((rcParent.right / 2) - 1), clsGuiSettingManager::iOneLineGB + 4, (rcParent.right / 2) - 5, clsGuiSettingManager::iEditHeight, hWndWindowItems[WINDOW_HANDLE], (HMENU)IDCANCEL, clsServerManager::hInstance, NULL);

    for(uint8_t ui8i = 0; ui8i < (sizeof(hWndWindowItems) / sizeof(hWndWindowItems[0])); ui8i++) {
        ::SendMessage(hWndWindowItems[ui8i], WM_SETFONT, (WPARAM)clsGuiSettingManager::hFont, MAKELPARAM(TRUE, 0));
    }

    ::EnableWindow(hWndParent, FALSE);

    ::ShowWindow(hWndWindowItems[WINDOW_HANDLE], SW_SHOW);
}
//---------------------------------------------------------------------------
