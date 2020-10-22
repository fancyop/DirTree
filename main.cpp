#include <iostream>
#include <Windows.h>
#include "DirTree.h"

#pragma comment (lib, "User32.lib")

std::vector<bool> lastPathRecoder;

using namespace std;

#define midSymbol (L"├");
#define lineSymbol (L"│");
#define angleSymbol (L"└");
#define spaceSymbol (L" ");

/*
├ aclocal.m4
├ advio
│   ├ daytimetcpcli.c
│   ├ daytimeudpcli3.c
│   ├ Makefile
│   ├ old
│   │   ├ dgechoaddr.c
│   │   ├ recvfromflags.c
│   │   └ test01.c
│   ├ recvfromflags.c
*/

/* 函数声明 */
DWORD ListAllFileInDirectory(LPWSTR szPath, DirTree* dir);

/* 全局变量 */
// 记录所有的文件和目录
DWORD dwTotalFileNum = 0;

/*********************************************************
* DWORD ListAllFileInDirectory(LPSTR szPath)
* 功能：遍历目录及所有子目录，打印路径
* 参数：LPSTR szPath，为需遍历的目录
* 返回值：0代表执行完成，1代表发生错误
*********************************************************/
DWORD ListAllFileInDirectory(LPWSTR szPath, DirTree* dir)
{
    WCHAR szFilePath[MAX_PATH];
    WIN32_FIND_DATA FindFileData;
    HANDLE hListFile;
    WCHAR szFullPath[MAX_PATH];

    // 构造代表子目录和文件夹路径的字符串，使用通配符“*”
    lstrcpy(szFilePath, szPath);
    lstrcat(szFilePath, L"\\*");

    // 查找第一个文件目录，获得查找句柄
    hListFile = FindFirstFile(szFilePath, &FindFileData);
    if (hListFile == INVALID_HANDLE_VALUE)
    {
        printf("错误： %d", GetLastError());
        return 1;
    }
    else
    {
        do {
            // 过滤"."和".."，不需要遍历
            if (lstrcmp(FindFileData.cFileName, TEXT(".")) == 0 ||
                lstrcmp(FindFileData.cFileName, TEXT("..")) == 0)
            {
                continue;
            }

            // 构造成全路径
            //wsprintf(szFullPath, "%s\\%s", szPath, FindFileData.cFileName);
            lstrcpy(szFullPath, szPath);
            lstrcat(szFullPath, L"\\");
            lstrcat(szFullPath, FindFileData.cFileName);

            dwTotalFileNum++;

            // 如果是目录，则递归调用，列举下级目录
            wstring str(szFullPath);
            if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)       //目录
            {
                DirTree* node = new DirTree(dir->depth + 1);
                dir->setChildListInfo(node, str);
                wcout << endl << dwTotalFileNum << "\t<DIR>" << szFullPath << "\t";
                ListAllFileInDirectory(szFullPath,node);
            }
            else    //文件
            {
                dir->setChildListInfo(NULL, str);
                wcout << endl << dwTotalFileNum << "\t     " << szFullPath << "\t";
            }
        } while (FindNextFile(hListFile, &FindFileData));
    }
    return 0;
}

void raversalTree(DirTree* dir)
{
    wstring wStr;
    DirInfoPtr pInfo = dir->pChildList;
    int depth = dir->depth;

    int len = 0;
    if (pInfo->nodeList.size() == pInfo->pathList.size()) {
        len = pInfo->nodeList.size();
    }
    
    //wcout << "lastPathRecoder: " << lastPathRecoder.size() << endl;
    //wcout << "depth: " << depth << endl;

    for (int i = 0; i < len; i++) {
        wstring wsDisplay;

        for (int i = 0; i < depth; i++)
        {
            if (false == lastPathRecoder.at((size_t)i+1)) {
                wsDisplay += lineSymbol;
            }
            else{
                wsDisplay += spaceSymbol;
            }
            wsDisplay += spaceSymbol;
        }

        if (i == len - 1) {
            wsDisplay += angleSymbol;
        }
        else {
            wsDisplay += midSymbol;
        }
        wsDisplay += spaceSymbol;
        wsDisplay += spaceSymbol;
        wsDisplay += pInfo->pathList.at(i);
        wcout << wsDisplay << endl;

        if (pInfo->nodeList.at(i) != NULL) {
            if (i == len - 1) {
                lastPathRecoder.push_back(true);
            }
            else {
                lastPathRecoder.push_back(false);
            }
            raversalTree(pInfo->nodeList.at(i));
        }
        else {
            
        }
    }
    lastPathRecoder.pop_back();
}

void raversal(DirTree* dir)
{
    lastPathRecoder.push_back(true);
    wcout << endl << endl << "---------------------------------------------------" << endl ;
    raversalTree(dir);
}

int main()
{
    std::wcout.imbue(std::locale("chs"));
	wcout << "---------------------------------------------------" << endl;

	DirTree tree;

    WCHAR szCurrentPath[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, szCurrentPath);

    //wstring s(L"C:\\Users");
    //ListAllFileInDirectory(LPWSTR(s.c_str()), &tree);
    ListAllFileInDirectory(szCurrentPath, &tree);

    raversal(&tree);

    return 0;
}

