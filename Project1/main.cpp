#include"FilesystemFacade.h"
#include "FilesystemObject.h"
#include "FilesystemOperations.h"
int main() {

	try {
		Filesystem* f = Filesystem::getInstance();
		Folder * f1 = f->createFolder("Folder 1");
		File* fajl1 = f->createFile("Fajl 1", f1);
		Byte a = "rakoon je gej";
		fajl1->write(&a);
		f->deleteF(fajl1);


	}
	catch (AccessException) {}


}