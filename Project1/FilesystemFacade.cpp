#include "FilesystemFacade.h"


File* Filesystem::createFile(Text * fName, Folder * destFolder)
{
	CreateFile cf(fName, destFolder);
	cf.execute();
	return cf.f;
}
//done!
Folder* Filesystem::createFolder(Text * fName, Folder * parentFolder)
{
	CreateFolder cf(fName, parentFolder);
	cf.execute();
	return cf.f;
}
//done!
FSObject * Filesystem::listFolder(Folder * folder)
{
	ListDirectory ld(folder);
	ld.execute();
	return ld.rez;
}
//done!
Byte* Filesystem::readFile(File * file)
{
	ReadFile rf(file);
	rf.execute();
	return rf.stanje;
}
//done!
void Filesystem::writeFile(Byte * content, File* f)
{
	WriteFile wf(content, f);
	wf.execute();
}
//done!
void Filesystem::grantAccess(FSObject * fObj, Text * opName)
{
	AccessDescriptor* a = fObj->getAccessDescriptor();
	if (a->checkAccess(opName)) {
		return;
	}
	else {
		a->add(opName);
	}
}
//done!
void Filesystem::revokeAccess(FSObject * fObj, Text * opName)
{
	AccessDescriptor* a = fObj->getAccessDescriptor();
	if (a->checkAccess(opName)) {
		a->remove(opName);
	}
	else {
		return;
	}
}
Folder * Filesystem::openFolder(Text * folderPath)
{
	std::vector<char*> putanja;
	Text* ime;
	for (int i = 0; i < sizeof(folderPath) / sizeof(folderPath[0]); i++) {
		if (folderPath[i] == '/'|| folderPath[i] == '\0') {
			ime = new Text(sizeof(ime) + sizeof(char));
			strcat(ime, "\0");
			putanja.push_back(ime);
			delete ime;
			continue;
		}
		else {
			ime = new Text(sizeof(ime) + sizeof(char));
			strcat(ime, &folderPath[i]);
		}
	}
	Folder* root = rootFolder;
	for (unsigned int i = 0; i < putanja.size(); i++){
		Text* key = putanja[i];
		SearchVisitor v(key);
		root->accept(&v);
		
		Folder* novi = v.folder;
		root = novi;
		}
	return root;
}
//done!
std::vector<FSObject*> Filesystem::search(Text * objName)
{
	Search s(objName, rootFolder);
	return s.found;
}
//done!
void Filesystem::copyPaste(FSObject * objToCopy, Folder * destFolder, Text * name)
{
	CopyPaste cp(objToCopy, destFolder, name);
	cp.execute();
}
//done!
void Filesystem::move(FSObject * objToMove, Folder * destFolder)
{
	Move m(objToMove, destFolder);
	m.execute();
}
//done!
bool Filesystem::deleteF(FSObject * objToDelete)
{
	DeleteObject del(objToDelete);
	del.execute();
	return del.check;
}
//done!
//long Filesystem::freeSpace()
//{
//	return 0;
//}