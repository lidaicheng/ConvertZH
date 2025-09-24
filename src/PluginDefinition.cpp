//this file is part of notepad++
//Copyright (C)2022 Don HO <don.h@free.fr>
//
//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU General Public License
//as published by the Free Software Foundation; either
//version 2 of the License, or (at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

#include "PluginDefinition.h"
#include "menuCmdID.h"
#include "utils.h"

//
// put the headers you need here
//
#include <stdlib.h>
#include <time.h>
#include <shlwapi.h>
#include "DockingFeature/GoToLineDlg.h"
#include <string>
#include <unordered_map>
#include <vector>
#include <windows.h>

const TCHAR sectionName[] = TEXT("Insert Extesion");
const TCHAR keyName[] = TEXT("doCloseTag");
const TCHAR configFileName[] = TEXT("pluginDemo.ini");

DemoDlg _goToLine;

#ifdef UNICODE 
	#define generic_itoa _itow
#else
	#define generic_itoa itoa
#endif

FuncItem funcItem[nbFunc];

//
// The data of Notepad++ that you can use in your plugin commands
//
NppData nppData;


TCHAR iniFilePath[MAX_PATH];
bool doCloseTag = false;

#define DOCKABLE_DEMO_INDEX 15

//
// Initialize your plugin data here
// It will be called while plugin loading   
void pluginInit(HANDLE hModule)
{
	// Initialize dockable demo dialog
	_goToLine.init((HINSTANCE)hModule, NULL);
	
	// Initialize OpenCC wrapper
	//OpenCCWrapper::Initialize();
}

//
// Here you can do the clean up, save the parameters (if any) for the next session
//
void pluginCleanUp()
{
	::WritePrivateProfileString(sectionName, keyName, doCloseTag?TEXT("1"):TEXT("0"), iniFilePath);
	
	// Cleanup OpenCC wrapper
	//OpenCCWrapper::Cleanup();
}

//
// Initialization of your plugin commands
// You should fill your plugins commands here
void commandMenuInit()
{
	//
	// Firstly we get the parameters from your plugin config file (if any)
	//

	// get path of plugin configuration
	::SendMessage(nppData._nppHandle, NPPM_GETPLUGINSCONFIGDIR, MAX_PATH, (LPARAM)iniFilePath);

	// if config path doesn't exist, we create it
	if (PathFileExists(iniFilePath) == FALSE)
	{
		::CreateDirectory(iniFilePath, NULL);
	}

	// make your plugin config file full file path name
	PathAppend(iniFilePath, configFileName);

	// get the parameter value from plugin config
	doCloseTag = (::GetPrivateProfileInt(sectionName, keyName, 0, iniFilePath) != 0);


    //--------------------------------------------//
    //-- STEP 3. CUSTOMIZE YOUR PLUGIN COMMANDS --//
    //--------------------------------------------//
    // with function :
    // setCommand(int index,                      // zero based number to indicate the order of command
    //            TCHAR *commandName,             // the command name that you want to see in plugin menu
    //            PFUNCPLUGINCMD functionPointer, // the symbol of function (function pointer) associated with this command. The body should be defined below. See Step 4.
    //            ShortcutKey *shortcut,          // optional. Define a shortcut to trigger this command
    //            bool check0nInit                // optional. Make this menu item be checked visually
    //            );
		ShortcutKey *shKey = new ShortcutKey;
	shKey->_isAlt = true;
	shKey->_isCtrl = false;
	shKey->_isShift = false;
	shKey->_key = 0x54; //VK_T
    setCommand(0, TEXT("简体转繁体"), SimplifiedToTraditional, shKey, false);

	ShortcutKey *pShKey = new ShortcutKey;
	pShKey->_isAlt = true;
	pShKey->_isCtrl = false;
	pShKey->_isShift = false;
	pShKey->_key = 0x53; //VK_S
    setCommand(1, TEXT("繁体转简体"), TraditionalToSimplified, pShKey, false);
	//setCommand(2, TEXT("What is Notepad++?"), WhatIsNpp, NULL, false);

	//// Here you insert a separator
	//setCommand(3, TEXT("---"), NULL, NULL, false);


}


//
// Here you can do the clean up (especially for the shortcut)
//
void commandMenuCleanUp()
{
	// Don't forget to deallocate your shortcut here
	delete funcItem[0]._pShKey;
	delete funcItem[1]._pShKey;
}

//----------------------------------------------//
//-- STEP 4. DEFINE YOUR ASSOCIATED FUNCTIONS --//
//----------------------------------------------//



// 简体转繁体插件命令函数
void SimplifiedToTraditional() {
    // 获取当前选中的文本
    int start, end;
    start = (int)::SendMessage(nppData._scintillaMainHandle, SCI_GETSELECTIONSTART, 0, 0);
    end = (int)::SendMessage(nppData._scintillaMainHandle, SCI_GETSELECTIONEND, 0, 0);
    
    if (start == end) {
        // 没有选中文本，转换整个文档
        int docLength = (int)::SendMessage(nppData._scintillaMainHandle, SCI_GETLENGTH, 0, 0);
        start = 0;
        end = docLength;
    }
    
    // 检查是否有文本需要转换
    if (start >= end) {
        return; // 没有文本需要转换
    }
    
    // 获取选中文本
    Sci_TextRangeFull textRange;
    textRange.chrg.cpMin = start;
    textRange.chrg.cpMax = end;
    char* text = new char[end - start + 1];
    textRange.lpstrText = text;
    ::SendMessage(nppData._scintillaMainHandle, SCI_GETTEXTRANGEFULL, 0, (LPARAM)&textRange);
    text[end - start] = '\0'; // Null-terminate the string
    
    // 转换为宽字符
    // int wideLen = MultiByteToWideChar(CP_UTF8, 0, text, -1, NULL, 0);
    // wchar_t* wideText = new wchar_t[wideLen];
    // MultiByteToWideChar(CP_UTF8, 0, text, -1, wideText, wideLen);
    
    // 进行转换
    std::string inputStr(text);
    std::string outputStr = utils::SimplifiedToTrad(inputStr);
    
    // 替换选中文本
    ::SendMessage(nppData._scintillaMainHandle, SCI_REPLACESEL, 0, (LPARAM)outputStr.c_str());
    
    // 清理内存
    delete[] text;
}

// 繁体转简体插件命令函数
void TraditionalToSimplified() {
    // 获取当前选中的文本
    int start, end;
    start = (int)::SendMessage(nppData._scintillaMainHandle, SCI_GETSELECTIONSTART, 0, 0);
    end = (int)::SendMessage(nppData._scintillaMainHandle, SCI_GETSELECTIONEND, 0, 0);
    
    if (start == end) {
        // 没有选中文本，转换整个文档
        int docLength = (int)::SendMessage(nppData._scintillaMainHandle, SCI_GETLENGTH, 0, 0);
        start = 0;
        end = docLength;
    }
    
    // 检查是否有文本需要转换
    if (start >= end) {
        return; // 没有文本需要转换
    }
    
    // 获取选中文本
    Sci_TextRangeFull textRange;
    textRange.chrg.cpMin = start;
    textRange.chrg.cpMax = end;
    char* text = new char[end - start + 1];
    textRange.lpstrText = text;
    ::SendMessage(nppData._scintillaMainHandle, SCI_GETTEXTRANGEFULL, 0, (LPARAM)&textRange);
    text[end - start] = '\0'; // Null-terminate the string
    
    // 进行转换
    std::string inputStr(text);
    std::string outputStr = utils::TraditionalToSimp(inputStr);
    
    // 替换选中文本
    ::SendMessage(nppData._scintillaMainHandle, SCI_REPLACESEL, 0, (LPARAM)outputStr.c_str());
    
    // 清理内存
    delete[] text;
}




//
// This function help you to initialize your plugin commands
//
bool setCommand(size_t index, TCHAR *cmdName, PFUNCPLUGINCMD pFunc, ShortcutKey *sk, bool check0nInit) 
{
    if (index >= nbFunc)
        return false;

    if (!pFunc)
        return false;

    lstrcpy(funcItem[index]._itemName, cmdName);
    funcItem[index]._pFunc = pFunc;
    funcItem[index]._init2Check = check0nInit;
    funcItem[index]._pShKey = sk;

    return true;
}


// Dockable Dialog Demo
// 
// This demonstration shows you how to do a dockable dialog.
// You can create your own non dockable dialog - in this case you don't nedd this demonstration.
// You have to create your dialog by inherented DockingDlgInterface class in order to make your dialog dockable
// - please see DemoDlg.h and DemoDlg.cpp to have more informations.


