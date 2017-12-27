#pragma once
#include"FilesystemOperations.h"

class Filesystem {
private:
	Filesystem();
	static Filesystem* instance;
	Folder* rootFolder;
	long size,used;
public:
	static Filesystem* getInstance();
	File* createFile(Text* fName, Folder* destFolder);
	Folder* createFolder(Text* fName, Folder* parentFolder);
	FSObject* listFolder(Folder* folder);
	Byte* readFile(File* file);
	void writeFile(Byte* content,File* f);
	void grantAccess(FSObject* fObj, Text* opName = nullptr);
	void revokeAccess(FSObject* fObj, Text* opName = nullptr);
	Folder* openFolder(Text* folderPath);
	std::vector<FSObject*> search(Text* objName);
	void copyPaste(FSObject* objToCopy, Folder* destFolder, Text* name);
	void move(FSObject* objToMove, Folder* destFolder);
	bool deleteF(FSObject* objToDelete);
	void setSize(long a);
	long freeSpace();
	~Filesystem() {
		delete rootFolder;
	}
};