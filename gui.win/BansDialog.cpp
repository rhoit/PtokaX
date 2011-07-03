/*
 * PtokaX - hub server for Direct Connect peer to peer network.

 * Copyright (C) 2002-2005  Ptaczek, Ptaczek at PtokaX dot org
 * Copyright (C) 2004-2011  Petr Kozelka, PPK at PtokaX dot org

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
#include "BansDialog.h"
//---------------------------------------------------------------------------
#include "../core/hashBanManager.h"
#include "../core/LanguageManager.h"
#include "../core/utility.h"
//---------------------------------------------------------------------------
#include "GuiUtil.h"
//---------------------------------------------------------------------------
#ifdef _WIN32
	#pragma hdrstop
#endif
//---------------------------------------------------------------------------
#include "BanDialog.h"
//---------------------------------------------------------------------------
BansDialog * pBansDialog = NULL;
//---------------------------------------------------------------------------
#define IDC_CHANGE_BAN      1000
#define IDC_REMOVE_BANS     1001
//---------------------------------------------------------------------------
static ATOM atomBansDialog = 0;
//---------------------------------------------------------------------------

BansDialog::BansDialog() {
    memset(&hWndWindowItems, 0, (sizeof(hWndWindowItems) / sizeof(hWndWindowItems[0])) * sizeof(HWND));

    iFilterColumn = iSortColumn = 0;

    bSortAscending = true;
}
//---------------------------------------------------------------------------

BansDialog::~BansDialog() {
    pBansDialog = NULL;
}
//---------------------------------------------------------------------------

LRESULT CALLBACK BansDialog::StaticBansDialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    BansDialog * pBansDialog = (BansDialog *)::GetWindowLongPtr(hWnd, GWLP_USERDATA);

    if(pBansDialog == NULL) {
        return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
    }

	return pBansDialog->BansDialogProc(uMsg, wParam, lParam);
}
//------------------------------------------------------------------------------

LRESULT BansDialog::BansDialogProc(UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch(uMsg) {
        case WM_WINDOWPOSCHANGED: {
            RECT rcParent;
            ::GetClientRect(hWndWindowItems[WINDOW_HANDLE], &rcParent);

            ::SetWindowPos(hWndWindowItems[BTN_CLEAR_PERM_BANS], NULL, (rcParent.right / 2) + 1, rcParent.bottom - iEditHeight - 2,
                rcParent.right - (rcParent.right / 2) - 3, iEditHeight, SWP_NOZORDER);
            ::SetWindowPos(hWndWindowItems[BTN_CLEAR_TEMP_BANS], NULL, 2, rcParent.bottom - iEditHeight - 2, (rcParent.right / 2) - 2, iEditHeight, SWP_NOZORDER);
            ::SetWindowPos(hWndWindowItems[CB_FILTER], NULL, (rcParent.right / 2) + 3, (rcParent.bottom - iEditHeight - iOneLineGB - 6) + iGroupBoxMargin,
                rcParent.right - (rcParent.right / 2) - 14, iEditHeight, SWP_NOZORDER);
            ::SetWindowPos(hWndWindowItems[EDT_FILTER], NULL, 11, (rcParent.bottom - iEditHeight - iOneLineGB - 6) + iGroupBoxMargin, (rcParent.right / 2) - 14, iEditHeight, SWP_NOZORDER);
            ::SetWindowPos(hWndWindowItems[GB_FILTER], NULL, 3, rcParent.bottom - iEditHeight - iOneLineGB - 6, rcParent.right - 6, iOneLineGB, SWP_NOZORDER);
            ::SetWindowPos(hWndWindowItems[LV_BANS], NULL, 0, 0, rcParent.right - 6, rcParent.bottom - iOneLineGB - (2 * iEditHeight) - 14, SWP_NOMOVE | SWP_NOZORDER);
            ::SetWindowPos(hWndWindowItems[BTN_ADD_BAN], NULL, 0, 0, rcParent.right - 4, iEditHeight, SWP_NOMOVE | SWP_NOZORDER);

            return 0;
        }
        case WM_COMMAND:
            switch(LOWORD(wParam)) {
                case (BTN_ADD_BAN+100): {
                    pBanDialog = new BanDialog();
                    pBanDialog->DoModal(hWndWindowItems[WINDOW_HANDLE]);

                    return 0;
                }
                case IDC_CHANGE_BAN: {
                    ChangeBan();
                    return 0;
                }
                case IDC_REMOVE_BANS:
                    RemoveBans();
                    return 0;
                case CB_FILTER:
                    if(HIWORD(wParam) == CBN_SELCHANGE) {
                        if(::GetWindowTextLength(hWndWindowItems[EDT_FILTER]) != 0) {
                            FilterBans();
                        }
                    }

                    break;
                case BTN_CLEAR_TEMP_BANS:
                    if(::MessageBox(hWndWindowItems[WINDOW_HANDLE], (string(LanguageManager->sTexts[LAN_ARE_YOU_SURE], (size_t)LanguageManager->ui16TextsLens[LAN_ARE_YOU_SURE])+" ?").c_str(),
                        sTitle.c_str(), MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) == IDNO) {
                        return 0;
                    }

                    hashBanManager->ClearTemp();
                    AddAllBans();

                    return 0;
                case BTN_CLEAR_PERM_BANS:
                    if(::MessageBox(hWndWindowItems[WINDOW_HANDLE], (string(LanguageManager->sTexts[LAN_ARE_YOU_SURE], (size_t)LanguageManager->ui16TextsLens[LAN_ARE_YOU_SURE])+" ?").c_str(), sTitle.c_str(),
                        MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) == IDNO) {
                        return 0;
                    }

                    hashBanManager->ClearPerm();
                    AddAllBans();

                    return 0;
                case IDOK: { // NM_RETURN
                    HWND hWndFocus = ::GetFocus();

                    if(hWndFocus == hWndWindowItems[LV_BANS]) {
                        ChangeBan();
                        return 0;
                    } else if(hWndFocus == hWndWindowItems[EDT_FILTER]) {
                        FilterBans();
                        return 0;
                    }

                    break;
                }
                case IDCANCEL:
                    ::PostMessage(hWndWindowItems[WINDOW_HANDLE], WM_CLOSE, 0, 0);
					return 0;
            }

            break;
        case WM_CONTEXTMENU:
            OnContextMenu((HWND)wParam, lParam);
            break;
        case WM_NOTIFY:
            if(((LPNMHDR)lParam)->hwndFrom == hWndWindowItems[LV_BANS]) {
                if(((LPNMHDR)lParam)->code == LVN_COLUMNCLICK) {
                    OnColumnClick((LPNMLISTVIEW)lParam);
                } else if(((LPNMHDR)lParam)->code == NM_DBLCLK) {
                    if(((LPNMITEMACTIVATE)lParam)->iItem == -1) {
                        break;
                    }

                    BanItem * pBan = (BanItem *)ListViewGetItem(hWndWindowItems[LV_BANS], ((LPNMITEMACTIVATE)lParam)->iItem);

                    pBanDialog = new BanDialog();
                    pBanDialog->DoModal(hWndWindowItems[WINDOW_HANDLE], pBan);

                    return 0;
                } else if(((LPNMHDR)lParam)->code == NM_RETURN) {
                    ChangeBan();
                    return 0;
                }
            }

            break;
        case WM_GETMINMAXINFO: {
            MINMAXINFO *mminfo = (MINMAXINFO*)lParam;
            mminfo->ptMinTrackSize.x = ScaleGui(443);
            mminfo->ptMinTrackSize.y = ScaleGui(454);

            return 0;
        }
        case WM_CLOSE:
            ::EnableWindow(::GetParent(hWndWindowItems[WINDOW_HANDLE]), TRUE);
            g_hWndActiveDialog = NULL;
            break;
        case WM_NCDESTROY:
            delete this;
            return ::DefWindowProc(hWndWindowItems[WINDOW_HANDLE], uMsg, wParam, lParam);
        case WM_SETFOCUS:
            if((UINT)::SendMessage(hWndWindowItems[LV_BANS], LVM_GETSELECTEDCOUNT, 0, 0) != 0) {
                ::SetFocus(hWndWindowItems[LV_BANS]);
            } else {
                ::SetFocus(hWndWindowItems[EDT_FILTER]);
            }

            return 0;
        case WM_ACTIVATE:
            if(LOWORD(wParam) != WA_INACTIVE) {
                g_hWndActiveDialog = hWndWindowItems[WINDOW_HANDLE];
            }

            break;
    }

	return ::DefWindowProc(hWndWindowItems[WINDOW_HANDLE], uMsg, wParam, lParam);
}
//------------------------------------------------------------------------------

void BansDialog::DoModal(HWND hWndParent) {
    if(atomBansDialog == 0) {
        WNDCLASSEX m_wc;
        memset(&m_wc, 0, sizeof(WNDCLASSEX));
        m_wc.cbSize = sizeof(WNDCLASSEX);
        m_wc.lpfnWndProc = ::DefWindowProc;
        m_wc.hbrBackground = (HBRUSH)(COLOR_3DFACE + 1);
        m_wc.lpszClassName = "PtokaX_BansDialog";
        m_wc.hInstance = g_hInstance;
        m_wc.hCursor = ::LoadCursor(m_wc.hInstance, IDC_ARROW);
        m_wc.style = CS_HREDRAW | CS_VREDRAW;

        atomBansDialog = ::RegisterClassEx(&m_wc);
    }

    RECT rcParent;
    ::GetWindowRect(hWndParent, &rcParent);

    int iX = (rcParent.left + (((rcParent.right-rcParent.left))/2)) - (ScaleGui(443) / 2);
    int iY = (rcParent.top + ((rcParent.bottom-rcParent.top)/2)) - (ScaleGui(454) / 2);

    hWndWindowItems[WINDOW_HANDLE] = ::CreateWindowEx(WS_EX_DLGMODALFRAME | WS_EX_WINDOWEDGE, MAKEINTATOM(atomBansDialog), LanguageManager->sTexts[LAN_BANS],
        WS_POPUP | WS_CAPTION | WS_MAXIMIZEBOX | WS_SYSMENU | WS_SIZEBOX | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, iX >= 5 ? iX : 5, iY >= 5 ? iY : 5, ScaleGui(443), ScaleGui(454),
        hWndParent, NULL, g_hInstance, NULL);

    if(hWndWindowItems[WINDOW_HANDLE] == NULL) {
        return;
    }

    g_hWndActiveDialog = hWndWindowItems[WINDOW_HANDLE];

    ::SetWindowLongPtr(hWndWindowItems[WINDOW_HANDLE], GWLP_USERDATA, (LONG_PTR)this);
    ::SetWindowLongPtr(hWndWindowItems[WINDOW_HANDLE], GWLP_WNDPROC, (LONG_PTR)StaticBansDialogProc);

    ::GetClientRect(hWndWindowItems[WINDOW_HANDLE], &rcParent);

    hWndWindowItems[BTN_ADD_BAN] = ::CreateWindowEx(0, WC_BUTTON, LanguageManager->sTexts[LAN_ADD_NEW_BAN], WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON,
        2, 2, (rcParent.right / 3) - 2, iEditHeight, hWndWindowItems[WINDOW_HANDLE], (HMENU)(BTN_ADD_BAN+100), g_hInstance, NULL);

    hWndWindowItems[LV_BANS] = ::CreateWindowEx(WS_EX_CLIENTEDGE, WC_LISTVIEW, "", WS_CHILD | WS_VISIBLE | WS_TABSTOP | LVS_REPORT | LVS_SHOWSELALWAYS,
        3, iEditHeight + 6, rcParent.right - 6, rcParent.bottom - iOneLineGB - (2 * iEditHeight) - 14, hWndWindowItems[WINDOW_HANDLE], NULL, g_hInstance, NULL);
    ::SendMessage(hWndWindowItems[LV_BANS], LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_DOUBLEBUFFER | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);

    hWndWindowItems[GB_FILTER] = ::CreateWindowEx(WS_EX_TRANSPARENT, WC_BUTTON, LanguageManager->sTexts[LAN_FILTER_BANS], WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
        3, rcParent.bottom - iEditHeight - iOneLineGB - 6, rcParent.right - 6, iOneLineGB, hWndWindowItems[WINDOW_HANDLE], NULL, g_hInstance, NULL);

    hWndWindowItems[EDT_FILTER] = ::CreateWindowEx(WS_EX_CLIENTEDGE, WC_EDIT, "", WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_AUTOHSCROLL,
        11, (rcParent.bottom - iEditHeight - iOneLineGB - 6) + iGroupBoxMargin, (rcParent.right / 2) - 14, iEditHeight, hWndWindowItems[WINDOW_HANDLE], (HMENU)EDT_FILTER, g_hInstance, NULL);
    ::SendMessage(hWndWindowItems[EDT_FILTER], EM_SETLIMITTEXT, 64, 0);

    hWndWindowItems[CB_FILTER] = ::CreateWindowEx(0, WC_COMBOBOX, "", WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_TABSTOP | CBS_DROPDOWNLIST,
        (rcParent.right / 2) + 3, (rcParent.bottom - iEditHeight - iOneLineGB - 6) + iGroupBoxMargin, rcParent.right - (rcParent.right / 2) - 14, iEditHeight,
        hWndWindowItems[WINDOW_HANDLE], (HMENU)CB_FILTER, g_hInstance, NULL);

    hWndWindowItems[BTN_CLEAR_TEMP_BANS] = ::CreateWindowEx(0, WC_BUTTON, LanguageManager->sTexts[LAN_CLEAR_TEMP_BANS], WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON,
        2, rcParent.bottom - iEditHeight - 2, (rcParent.right / 2) - 2, iEditHeight, hWndWindowItems[WINDOW_HANDLE], (HMENU)BTN_CLEAR_TEMP_BANS, g_hInstance, NULL);

    hWndWindowItems[BTN_CLEAR_PERM_BANS] = ::CreateWindowEx(0, WC_BUTTON, LanguageManager->sTexts[LAN_CLEAR_PERM_BANS], WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON,
        (rcParent.right / 2) + 1, rcParent.bottom - iEditHeight - 2, rcParent.right - (rcParent.right / 2) - 3, iEditHeight,
        hWndWindowItems[WINDOW_HANDLE], (HMENU)BTN_CLEAR_PERM_BANS, g_hInstance, NULL);

    for(uint8_t ui8i = 0; ui8i < (sizeof(hWndWindowItems) / sizeof(hWndWindowItems[0])); ui8i++) {
        if(hWndWindowItems[ui8i] == NULL) {
            return;
        }

        ::SendMessage(hWndWindowItems[ui8i], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
    }

	RECT rcBans;
	::GetClientRect(hWndWindowItems[LV_BANS], &rcBans);

    LVCOLUMN lvColumn = { 0 };
    lvColumn.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
    lvColumn.fmt = LVCFMT_LEFT;
    lvColumn.cx = 100;

    const int iBansStrings[] = { LAN_NICK, LAN_IP, LAN_REASON, LAN_EXPIRE, LAN_BANNED_BY };

    for(uint8_t ui8i = 0; ui8i < 5; ui8i++) {
        lvColumn.pszText = LanguageManager->sTexts[iBansStrings[ui8i]];
        lvColumn.iSubItem = ui8i;

        ::SendMessage(hWndWindowItems[LV_BANS], LVM_INSERTCOLUMN, ui8i, (LPARAM)&lvColumn);

        ::SendMessage(hWndWindowItems[CB_FILTER], CB_ADDSTRING, 0, (LPARAM)LanguageManager->sTexts[iBansStrings[ui8i]]);
    }

    ListViewUpdateArrow(hWndWindowItems[LV_BANS], bSortAscending, iSortColumn);

    ::SendMessage(hWndWindowItems[CB_FILTER], CB_SETCURSEL, 0, 0);

    AddAllBans();

    const int iBansWidths[] = { 200, 160, 125, 125, 100 };

    for(uint8_t ui8i = 0; ui8i < 5; ui8i++) {
        ::SendMessage(hWndWindowItems[LV_BANS], LVM_SETCOLUMNWIDTH, ui8i, LVSCW_AUTOSIZE);

        int iWidth = (int)::SendMessage(hWndWindowItems[LV_BANS], LVM_GETCOLUMNWIDTH, ui8i, 0);

        if(iWidth < iBansWidths[ui8i]) {
            ::SendMessage(hWndWindowItems[LV_BANS], LVM_SETCOLUMNWIDTH, ui8i, iBansWidths[ui8i]);
        }
    }

    ::EnableWindow(hWndParent, FALSE);

    ::ShowWindow(hWndWindowItems[WINDOW_HANDLE], SW_SHOW);
}
//------------------------------------------------------------------------------

void BansDialog::AddAllBans() {
    ::SendMessage(hWndWindowItems[LV_BANS], WM_SETREDRAW, (WPARAM)FALSE, 0);

    ::SendMessage(hWndWindowItems[LV_BANS], LVM_DELETEALLITEMS, 0, 0);

    time_t acc_time; time(&acc_time);

    BanItem * nextBan = hashBanManager->TempBanListS,
        * curBan = NULL;

    while(nextBan != NULL) {
		curBan = nextBan;
    	nextBan = curBan->next;

        if(acc_time > curBan->tempbanexpire) {
			hashBanManager->Rem(curBan);
            delete curBan;

            continue;
        }

        AddBan(curBan);
    }

    nextBan = hashBanManager->PermBanListS;

    while(nextBan != NULL) {
        curBan = nextBan;
    	nextBan = curBan->next;

        AddBan(curBan);
    }

    ListViewSelectFirstItem(hWndWindowItems[LV_BANS]);

    ::SendMessage(hWndWindowItems[LV_BANS], WM_SETREDRAW, (WPARAM)TRUE, 0);
}
//------------------------------------------------------------------------------

void BansDialog::AddBan(const BanItem * pBan) {
    LVITEM lvItem = { 0 };
    lvItem.mask = LVIF_PARAM | LVIF_TEXT;
    lvItem.iItem = ListViewGetInsertPosition(hWndWindowItems[LV_BANS], pBan, bSortAscending, CompareBans);

    string sTxt = (pBan->sNick == NULL ? "" : pBan->sNick);
    if((pBan->ui8Bits & hashBanMan::NICK) == hashBanMan::NICK) {
        sTxt += " (";
        sTxt += LanguageManager->sTexts[LAN_BANNED];
        sTxt += ")";
    }
    lvItem.pszText = sTxt.c_str();
    lvItem.lParam = (LPARAM)pBan;

    int i = (int)::SendMessage(hWndWindowItems[LV_BANS], LVM_INSERTITEM, 0, (LPARAM)&lvItem);

    if(i == -1) {
        return;
    }

    lvItem.mask = LVIF_TEXT;
    lvItem.iItem = i;
    lvItem.iSubItem = 1;

    sTxt = (pBan->sIp[0] == '\0' ? "" : pBan->sIp);
    if((pBan->ui8Bits & hashBanMan::IP) == hashBanMan::IP) {
        sTxt += " (";
        if((pBan->ui8Bits & hashBanMan::FULL) == hashBanMan::FULL) {
            sTxt += LanguageManager->sTexts[LAN_FULL_BANNED];
        } else {
            sTxt += LanguageManager->sTexts[LAN_BANNED];
        }
        sTxt += ")";
    }
    lvItem.pszText = sTxt.c_str();

    ::SendMessage(hWndWindowItems[LV_BANS], LVM_SETITEM, 0, (LPARAM)&lvItem);

    lvItem.iSubItem = 2;
    lvItem.pszText = (pBan->sReason == NULL ? "" : pBan->sReason);

    ::SendMessage(hWndWindowItems[LV_BANS], LVM_SETITEM, 0, (LPARAM)&lvItem);

    if((pBan->ui8Bits & hashBanMan::TEMP) == hashBanMan::TEMP) {
        char msg[256];
        struct tm *tm = localtime(&pBan->tempbanexpire);
        strftime(msg, 256, "%c", tm);

        lvItem.iSubItem = 3;
        lvItem.pszText = msg;

        ::SendMessage(hWndWindowItems[LV_BANS], LVM_SETITEM, 0, (LPARAM)&lvItem);
    }

    lvItem.iSubItem = 4;
    lvItem.pszText = (pBan->sBy == NULL ? "" : pBan->sBy);

    ::SendMessage(hWndWindowItems[LV_BANS], LVM_SETITEM, 0, (LPARAM)&lvItem);
}
//------------------------------------------------------------------------------

int BansDialog::CompareBans(const void * pItem, const void * pOtherItem) {
    BanItem * pFirstBan = (BanItem *)pItem;
    BanItem * pSecondBan = (BanItem *)pOtherItem;

    switch(pBansDialog->iSortColumn) {
        case 0:
            return _stricmp(pFirstBan->sNick == NULL ? "" : pFirstBan->sNick, pSecondBan->sNick == NULL ? "" : pSecondBan->sNick);
        case 1:
            return (pFirstBan->ui32IpHash > pSecondBan->ui32IpHash) ? 1 : ((pFirstBan->ui32IpHash == pSecondBan->ui32IpHash) ? 0 : -1);
        case 2:
            return _stricmp(pFirstBan->sReason == NULL ? "" : pFirstBan->sReason, pSecondBan->sReason == NULL ? "" : pSecondBan->sReason);
        case 3:
            if((pFirstBan->ui8Bits & hashBanMan::TEMP) == hashBanMan::TEMP) {
                if((pSecondBan->ui8Bits & hashBanMan::TEMP) == hashBanMan::TEMP) {
                    return 0;
                } else {
                    return -1;
                }
            } else if((pSecondBan->ui8Bits & hashBanMan::TEMP) == hashBanMan::TEMP) {
                return 1;
            } else {
                return (pFirstBan->tempbanexpire > pSecondBan->tempbanexpire) ? 1 : ((pFirstBan->tempbanexpire == pSecondBan->tempbanexpire) ? 0 : -1);
            }
        case 4:
            return _stricmp(pFirstBan->sBy == NULL ? "" : pFirstBan->sBy, pSecondBan->sBy == NULL ? "" : pSecondBan->sBy);
        default:
            return 0; // never happen, but we need to make compiler/complainer happy ;o)
    }
}
//------------------------------------------------------------------------------

void BansDialog::OnColumnClick(const LPNMLISTVIEW &pListView) {
    if(pListView->iSubItem != iSortColumn) {
        bSortAscending = true;
        iSortColumn = pListView->iSubItem;
    } else {
        bSortAscending = !bSortAscending;
    }

    ListViewUpdateArrow(hWndWindowItems[LV_BANS], bSortAscending, iSortColumn);

    ::SendMessage(hWndWindowItems[LV_BANS], LVM_SORTITEMS, 0, (LPARAM)&SortCompareBans);
}
//------------------------------------------------------------------------------

int CALLBACK BansDialog::SortCompareBans(LPARAM lParam1, LPARAM lParam2, LPARAM /*lParamSort*/) {
    int iResult = pBansDialog->CompareBans((void *)lParam1, (void *)lParam2);

    return (pBansDialog->bSortAscending == true ? iResult : -iResult);
}
//------------------------------------------------------------------------------

void BansDialog::RemoveBans() {
    if(::MessageBox(hWndWindowItems[WINDOW_HANDLE], (string(LanguageManager->sTexts[LAN_ARE_YOU_SURE], (size_t)LanguageManager->ui16TextsLens[LAN_ARE_YOU_SURE])+" ?").c_str(), sTitle.c_str(),
        MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) == IDNO) {
        return;
    }

    ::SendMessage(hWndWindowItems[LV_BANS], WM_SETREDRAW, (WPARAM)FALSE, 0);

    int iSel = -1;
    while((iSel = (int)::SendMessage(hWndWindowItems[LV_BANS], LVM_GETNEXTITEM, (WPARAM)-1, LVNI_SELECTED)) != -1) {
        BanItem * pBan = (BanItem *)ListViewGetItem(hWndWindowItems[LV_BANS], iSel);

        hashBanManager->Rem(pBan, true);

        ::SendMessage(hWndWindowItems[LV_BANS], LVM_DELETEITEM, iSel, 0);
    }

    ::SendMessage(hWndWindowItems[LV_BANS], WM_SETREDRAW, (WPARAM)TRUE, 0);
}
//------------------------------------------------------------------------------

void BansDialog::FilterBans() {
    int iTextLength = ::GetWindowTextLength(hWndWindowItems[EDT_FILTER]);

    if(iTextLength == 0) {
        sFilterString.clear();

    	AddAllBans();
    } else {
        iFilterColumn = (int)::SendMessage(hWndWindowItems[CB_FILTER], CB_GETCURSEL, 0, 0);

        char buf[65];

        int iLen = ::GetWindowText(hWndWindowItems[EDT_FILTER], buf, 65);

        for(int i = 0; i < iLen; i++) {
            buf[i] = (char)tolower(buf[i]);
        }

        sFilterString = buf;

        ::SendMessage(hWndWindowItems[LV_BANS], WM_SETREDRAW, (WPARAM)FALSE, 0);

        ::SendMessage(hWndWindowItems[LV_BANS], LVM_DELETEALLITEMS, 0, 0);

        time_t acc_time; time(&acc_time);

        BanItem * nextBan = hashBanManager->TempBanListS,
            * curBan = NULL;

        while(nextBan != NULL) {
		  curBan = nextBan;
    	   nextBan = curBan->next;

            if(acc_time > curBan->tempbanexpire) {
                hashBanManager->Rem(curBan);
                delete curBan;

                continue;
            }

            if(FilterBan(curBan) == false) {
                AddBan(curBan);
            }
        }

        nextBan = hashBanManager->PermBanListS;

        while(nextBan != NULL) {
            curBan = nextBan;
            nextBan = curBan->next;

            if(FilterBan(curBan) == false) {
                AddBan(curBan);
            }
        }

        ListViewSelectFirstItem(hWndWindowItems[LV_BANS]);

        ::SendMessage(hWndWindowItems[LV_BANS], WM_SETREDRAW, (WPARAM)TRUE, 0);
    }
}
//------------------------------------------------------------------------------

bool BansDialog::FilterBan(const BanItem * pBan) {
    switch(iFilterColumn) {
        case 0:
            if(pBan->sNick != NULL && stristr2(pBan->sNick, sFilterString.c_str()) != NULL) {
                return false;
            }
            break;
        case 1:
            if(pBan->sIp[0] != '\0' && stristr2(pBan->sIp, sFilterString.c_str()) != NULL) {
                return false;
            }
            break;
        case 2:
            if(pBan->sReason != NULL && stristr2(pBan->sReason, sFilterString.c_str()) != NULL) {
                return false;
            }
            break;
        case 3:
            if((pBan->ui8Bits & hashBanMan::TEMP) == hashBanMan::TEMP) {
                char msg[256];
                struct tm *tm = localtime(&pBan->tempbanexpire);
                strftime(msg, 256, "%c", tm);

                if(stristr2(msg, sFilterString.c_str()) != NULL) {
                    return false;
                }
            }
            break;
        case 4:
            if(pBan->sBy != NULL && stristr2(pBan->sBy, sFilterString.c_str()) != NULL) {
                return false;
            }
            break;
    }

    return true;
}
//------------------------------------------------------------------------------

void BansDialog::RemoveBan(const BanItem * pBan) {
    int iPos = ListViewGetItemPosition(hWndWindowItems[LV_BANS], (void *)pBan);

    if(iPos != -1) {
        ::SendMessage(hWndWindowItems[LV_BANS], LVM_DELETEITEM, iPos, 0);
    }
}
//------------------------------------------------------------------------------

void BansDialog::OnContextMenu(HWND hWindow, LPARAM lParam) {
    if(hWindow != hWndWindowItems[LV_BANS]) {
        return;
    }

    UINT UISelectedCount = (UINT)::SendMessage(hWndWindowItems[LV_BANS], LVM_GETSELECTEDCOUNT, 0, 0);

    if(UISelectedCount == 0) {
        return;
    }

    HMENU hMenu = ::CreatePopupMenu();

    if(UISelectedCount == 1) {
        ::AppendMenu(hMenu, MF_STRING, IDC_CHANGE_BAN, LanguageManager->sTexts[LAN_CHANGE]);
        ::AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
    }

    ::AppendMenu(hMenu, MF_STRING, IDC_REMOVE_BANS, LanguageManager->sTexts[LAN_REMOVE]);

    int iX = GET_X_LPARAM(lParam);
    int iY = GET_Y_LPARAM(lParam);

    ListViewGetMenuPos(hWndWindowItems[LV_BANS], iX, iY);

    ::TrackPopupMenuEx(hMenu, TPM_LEFTALIGN | TPM_RIGHTBUTTON, iX, iY, hWndWindowItems[WINDOW_HANDLE], NULL);

    ::DestroyMenu(hMenu);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void BansDialog::ChangeBan() {
    int iSel = (int)::SendMessage(hWndWindowItems[LV_BANS], LVM_GETNEXTITEM, (WPARAM)-1, LVNI_SELECTED);

    if(iSel == -1) {
        return;
    }

    BanItem * pBan = (BanItem *)ListViewGetItem(hWndWindowItems[LV_BANS], iSel);

    pBanDialog = new BanDialog();
    pBanDialog->DoModal(hWndWindowItems[WINDOW_HANDLE], pBan);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------