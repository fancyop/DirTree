#pragma once
#include <vector>
#include <string>

class DirTree;
typedef struct {
	std::vector<DirTree*> nodeList;
	std::vector<std::wstring> pathList;
}DirInfo, *DirInfoPtr;

class DirTree
{
public:
	DirTree(int value = 0) {
		pChildList = &childList;
		depth = value;
	}
	int depth;
	DirInfo childList;
	DirInfoPtr pChildList;

	DirTree* pDirTree = this;

	void setChildListInfo(DirTree* pNode, std::wstring path);

	//void setChildList(std::wstring path, DirTree* pNode);

	void raversalDir(DirTree* dir);
	void raversalDirTree();

	//void releaseDir(DirTree* dir);
	//void releaseDirTree();
};