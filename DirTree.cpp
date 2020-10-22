#include "DirTree.h"
#include <iostream>

void DirTree::setChildListInfo(DirTree* pNode, std::wstring path)
{
	childList.nodeList.push_back(pNode);
	childList.pathList.push_back(path);
}

void DirTree::raversalDir(DirTree* dir) 
{
	std::wcout << "==========================================" << dir  << std::endl;
	DirInfoPtr pInfo = dir->pChildList;

	int len = 0;
	if (pInfo->nodeList.size() == pInfo->pathList.size()) {
		len = pInfo->nodeList.size();
	}

	std::wcout << "len: " << len << ", depth: " << dir->depth << std::endl;
	for (size_t i = 0; i < len; i++) {
		if (pInfo->nodeList.at(i) != NULL) {
			std::wcout << "<DIR>\t" << pInfo->pathList.at(i) <<std::endl;
			raversalDir(pInfo->nodeList.at(i));
		}
		else {
			std::wcout << "<FILE>\t" << pInfo->pathList.at(i) << std::endl;
		}
	}
}

void DirTree::raversalDirTree()
{
	raversalDir(pDirTree);
}

//ÓÐÎÊÌâ
//void DirTree::releaseDir(DirTree* dir)
//{
//	DirInfoPtr pInfo = dir->pChildList;
//
//	int len = 0;
//	if (pInfo->nodeList.size() == pInfo->pathList.size()) {
//		len = pInfo->nodeList.size();
//	}
//	for (size_t i = 0; i < len; i++){
//		if (pInfo->nodeList.at(i) != NULL) {
//			releaseDir(pInfo->nodeList.at(i));
//			delete(pInfo->nodeList.at(i));
//		}
//	}
//}
//
//void DirTree::releaseDirTree()
//{
//	releaseDir(pDirTree);
//}