#include"FilesystemFacade.h"
int main() {
	Filesystem* f = Filesystem::getInstance();
	Folder * f1 = f->createFolder("Folder 1" o);
	f->createFile("Fajl 1", f1);


}