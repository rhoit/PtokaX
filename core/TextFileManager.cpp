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
#include "stdinc.h"
//---------------------------------------------------------------------------
#include "TextFileManager.h"
//---------------------------------------------------------------------------
#include "ServerManager.h"
#include "SettingManager.h"
#include "User.h"
#include "utility.h"
//---------------------------------------------------------------------------
#ifdef _WIN32
	#pragma hdrstop
#endif
//---------------------------------------------------------------------------
clsTextFilesManager * clsTextFilesManager::mPtr = NULL;
//---------------------------------------------------------------------------

clsTextFilesManager::TextFile::TextFile() : pPrev(NULL), pNext(NULL), sCommand(NULL), sText(NULL) {
    // ...
}
//---------------------------------------------------------------------------

clsTextFilesManager::TextFile::~TextFile() {
#ifdef _WIN32
    if(sCommand != NULL) {
        if(HeapFree(clsServerManager::hPtokaXHeap, HEAP_NO_SERIALIZE, (void *)sCommand) == 0) {
			AppendDebugLog("%s - [MEM] Cannot deallocate sCommand in clsTextFilesManager::TextFile::~TextFile\n");
        }
    }
#else
	free(sCommand);
#endif

#ifdef _WIN32
    if(sText != NULL) {
        if(HeapFree(clsServerManager::hPtokaXHeap, HEAP_NO_SERIALIZE, (void *)sText) == 0) {
			AppendDebugLog("%s - [MEM] Cannot deallocate sText in clsTextFilesManager::TextFile::~TextFile\n");
        }
    }
#else
	free(sText);
#endif
}
//---------------------------------------------------------------------------

clsTextFilesManager::clsTextFilesManager() : pTextFiles(NULL) {
    // ...
}
//---------------------------------------------------------------------------
	
clsTextFilesManager::~clsTextFilesManager() {
    TextFile * cur = NULL,
        * next = pTextFiles;

    while(next != NULL) {
        cur = next;
        next = cur->pNext;

    	delete cur;
    }
}
//---------------------------------------------------------------------------

bool clsTextFilesManager::ProcessTextFilesCmd(User * u, char * cmd, bool fromPM/* = false*/) const {
    TextFile * cur = NULL,
        * next = pTextFiles;

    while(next != NULL) {
        cur = next;
        next = cur->pNext;

		if(strcasecmp(cur->sCommand, cmd) == 0) {
            bool bInPM = (clsSettingManager::mPtr->bBools[SETBOOL_SEND_TEXT_FILES_AS_PM] == true || fromPM);
            size_t szHubSecLen = (size_t)clsSettingManager::mPtr->ui16PreTextsLens[clsSettingManager::SETPRETXT_HUB_SEC];
            size_t szChatLen = 0;

            // PPK ... to chat or to PM ???
            if(bInPM == true) {
                szChatLen = 18+u->ui8NickLen+(2*szHubSecLen)+strlen(cur->sText);
            } else {
                szChatLen = 4+szHubSecLen+strlen(cur->sText);
            }

#ifdef _WIN32
            char * sMSG = (char *)HeapAlloc(clsServerManager::hPtokaXHeap, HEAP_NO_SERIALIZE, szChatLen);
#else
			char * sMSG = (char *)malloc(szChatLen);
#endif
            if(sMSG == NULL) {
        		AppendDebugLogFormat("[MEM] Cannot allocate %" PRIu64 " bytes for sMsg in clsTextFilesManager::ProcessTextFilesCmd\n", (uint64_t)szChatLen);

                return true;
            }

            if(bInPM == true) {
                int iret = sprintf(sMSG, "$To: %s From: %s $<%s> %s", u->sNick, clsSettingManager::mPtr->sPreTexts[clsSettingManager::SETPRETXT_HUB_SEC], clsSettingManager::mPtr->sPreTexts[clsSettingManager::SETPRETXT_HUB_SEC], cur->sText);
                if(CheckSprintf(iret, szChatLen, "clsTextFilesManager::ProcessTextFilesCmd1") == false) {
                    free(sMSG);
                    return true;
                }
            } else {
                int iret = sprintf(sMSG,"<%s> %s", clsSettingManager::mPtr->sPreTexts[clsSettingManager::SETPRETXT_HUB_SEC], cur->sText);
                if(CheckSprintf(iret, szChatLen, "clsTextFilesManager::ProcessTextFilesCmd2") == false) {
                    free(sMSG);
                    return true;
                }
            }

            u->SendCharDelayed(sMSG, szChatLen-1);

#ifdef _WIN32
            if(HeapFree(clsServerManager::hPtokaXHeap, HEAP_NO_SERIALIZE, (void *)sMSG) == 0) {
        		AppendDebugLog("%s - [MEM] Cannot deallocate sMSG in clsTextFilesManager::ProcessTextFilesCmd\n");
            }
#else
			free(sMSG);
#endif

        	return true;
        }
    }

    return false;
}
//---------------------------------------------------------------------------

void clsTextFilesManager::RefreshTextFiles() {
	if(clsSettingManager::mPtr->bBools[SETBOOL_ENABLE_TEXT_FILES] == false)
        return;

    TextFile * cur = NULL,
        * next = pTextFiles;

    while(next != NULL) {
        cur = next;
        next = cur->pNext;

    	delete cur;
    }

    pTextFiles = NULL;

#ifdef _WIN32
    struct _finddata_t textfile;
    intptr_t hFile = _findfirst((clsServerManager::sPath+"\\texts\\*.txt").c_str(), &textfile);

	if(hFile != -1) {
		do {
			if((textfile.attrib & _A_SUBDIR) != 0 ||
				stricmp(textfile.name+(strlen(textfile.name)-4), ".txt") != 0) {
				continue;
			}

        	FILE *f = fopen((clsServerManager::sPath+"\\texts\\"+textfile.name).c_str(), "rb");
			if(f != NULL) {
				if(textfile.size != 0) {
					TextFile * pNewTxtFile = new (std::nothrow) TextFile();
					if(pNewTxtFile == NULL) {
						AppendDebugLog("%s - [MEM] Cannot allocate pNewTxtFile in clsTextFilesManager::RefreshTextFiles\n");

						fclose(f);
						_findclose(hFile);

                        return;
                    }

					pNewTxtFile->sText = (char *)HeapAlloc(clsServerManager::hPtokaXHeap, HEAP_NO_SERIALIZE, textfile.size+2);

					if(pNewTxtFile->sText == NULL) {
						AppendDebugLogFormat("[MEM] Cannot allocate %" PRIu64 " bytes for sText in clsTextFilesManager::RefreshTextFiles\n", (uint64_t)(textfile.size+2));

						fclose(f);
						_findclose(hFile);

                        delete pNewTxtFile;

						return;
 					}

					size_t size = fread(pNewTxtFile->sText, 1, textfile.size, f);

					pNewTxtFile->sText[size] = '|';
					pNewTxtFile->sText[size+1] = '\0';

					pNewTxtFile->sCommand = (char *)HeapAlloc(clsServerManager::hPtokaXHeap, HEAP_NO_SERIALIZE, strlen(textfile.name)-3);
					if(pNewTxtFile->sCommand == NULL) {
						AppendDebugLogFormat("[MEM] Cannot allocate %" PRIu64 " bytes for sCommand in clsTextFilesManager::RefreshTextFiles\n", (uint64_t)(strlen(textfile.name)-3));

						fclose(f);
						_findclose(hFile);

                        delete pNewTxtFile;

						return;
					}

					memcpy(pNewTxtFile->sCommand, textfile.name, strlen(textfile.name)-4);
					pNewTxtFile->sCommand[strlen(textfile.name)-4] = '\0';

					pNewTxtFile->pPrev = NULL;

					if(pTextFiles == NULL) {
						pNewTxtFile->pNext = NULL;
					} else {
						pTextFiles->pPrev = pNewTxtFile;
						pNewTxtFile->pNext = pTextFiles;
					}

					pTextFiles = pNewTxtFile;
				}

				fclose(f);
			}
	    } while(_findnext(hFile, &textfile) == 0);

		_findclose(hFile);
    }
#else
    string txtdir = clsServerManager::sPath + "/texts/";

    DIR * p_txtdir = opendir(txtdir.c_str());

    if(p_txtdir == NULL) {
        return;
    }

    struct dirent * p_dirent;
    struct stat s_buf;

    while((p_dirent = readdir(p_txtdir)) != NULL) {
        string txtfile = txtdir + p_dirent->d_name;

        if(stat(txtfile.c_str(), &s_buf) != 0 || 
            (s_buf.st_mode & S_IFDIR) != 0 || 
            strcasecmp(p_dirent->d_name + (strlen(p_dirent->d_name)-4), ".txt") != 0) {
            continue;
        }

        FILE *f = fopen(txtfile.c_str(), "rb");
		if(f != NULL) {
			if(s_buf.st_size != 0) {
                TextFile * pNewTxtFile = new (std::nothrow) TextFile();
				if(pNewTxtFile == NULL) {
					AppendDebugLog("%s - [MEM] Cannot allocate pNewTxtFile in clsTextFilesManager::RefreshTextFiles1\n");

					fclose(f);
					closedir(p_txtdir);

                    return;
                }

				pNewTxtFile->sText = (char *)malloc(s_buf.st_size+2);
				if(pNewTxtFile->sText == NULL) {
					AppendDebugLogFormat("[MEM] Cannot allocate %" PRIu64 " bytes for sText in clsTextFilesManager::RefreshTextFiles\n", (uint64_t)(s_buf.st_size+2));

					fclose(f);
					closedir(p_txtdir);

                    delete pNewTxtFile;

                    return;
                }
    	        size_t size = fread(pNewTxtFile->sText, 1, s_buf.st_size, f);
				pNewTxtFile->sText[size] = '|';
                pNewTxtFile->sText[size+1] = '\0';

				pNewTxtFile->sCommand = (char *)malloc(strlen(p_dirent->d_name)-3);
				if(pNewTxtFile->sCommand == NULL) {
					AppendDebugLogFormat("[MEM] Cannot allocate %" PRIu64 " bytes for sCommand in clsTextFilesManager::RefreshTextFiles\n", (uint64_t)(strlen(p_dirent->d_name)-3));

					fclose(f);
					closedir(p_txtdir);

                    delete pNewTxtFile;

                    return;
                }

                memcpy(pNewTxtFile->sCommand, p_dirent->d_name, strlen(p_dirent->d_name)-4);
                pNewTxtFile->sCommand[strlen(p_dirent->d_name)-4] = '\0';

                pNewTxtFile->pPrev = NULL;

                if(pTextFiles == NULL) {
                    pNewTxtFile->pNext = NULL;
                } else {
                    pTextFiles->pPrev = pNewTxtFile;
                    pNewTxtFile->pNext = pTextFiles;
                }

                pTextFiles = pNewTxtFile;
    	    }

            fclose(f);
    	}
    }

    closedir(p_txtdir);
#endif
}
//---------------------------------------------------------------------------
