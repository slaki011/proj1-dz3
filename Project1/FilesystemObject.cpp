#include"FilesystemObject.h"

Folder::Folder(Text* a, Folder* fn) :FSObject(a, fn) {
	accessDescriptor = new AccessDescriptor(this);
}
Text* FSObject::getName() {
	return name;
}
void FSObject::setName(Text * name)
{
	this->name = name;
}
FSObject::~FSObject() {
	delete name;
	parent = nullptr;
}
AccessDescriptor::AccessDescriptor(FSObject* f)
{
	allowedOperations = new Text*();
	protectedObject = f;
}
void AccessDescriptor::add(Text* operationName) {
	int a = sizeof(allowedOperations) / sizeof(allowedOperations[0]);
	if (allowedOperations == nullptr)a = 0;
	*(allowedOperations + a) = new Text(*operationName);
}
void AccessDescriptor::remove(Text* operationName) {
	int n = sizeof(allowedOperations) / sizeof(allowedOperations[0]);
	for (int i = 0; i < n; i++) {
		if (std::strcmp(allowedOperations[i], operationName)) {
			delete[] allowedOperations[i];
			return;
		}
	}
}
Text** AccessDescriptor::getAllowedOperations() {
	if (allowedOperations == nullptr) return nullptr;
	return allowedOperations;
}
bool AccessDescriptor::checkAccess(Text* operationName) {
	if (this->getAllowedOperations() == nullptr) return false;
	int n = sizeof(allowedOperations) / sizeof(allowedOperations[0]);
	for (int i = 0; i < n; i++) {
		if (std::strcmp(allowedOperations[i], operationName)) {
			return true;
		}
	}
	return false;
}
AccessDescriptor::~AccessDescriptor() {
	delete protectedObject;
	delete allowedOperations;
}
void Folder::accept(FilesystemVisitor* v) {
	v->visitFolder(this);
}
void Folder::add(FSObject* o) {
	containedObjects.push_back(o);
}

std::vector<FSObject*> Folder::getObjects() {
	return containedObjects;
}
void Folder::remove(FSObject* obj) {
	for (int i = 0; i < containedObjects.size(); i++) {
		if (containedObjects[i]->getName() == obj->getName()) {
			delete containedObjects[i];
			containedObjects.erase(containedObjects.begin() + i);
			return;
		}
	}
}
FSObject* Folder::copy() {

	if (containedObjects.size() == 0) {
		Folder *x = new Folder(this->getName(),this->parent);
		return x;
	}
	else {
		Folder *x = new Folder(this->getName(),this->parent);
		for (int i = 0; i < containedObjects.size(); i++)
		{

			x->add(containedObjects[i]->copy());
		}
		return x;
	}
}
Folder::~Folder() {
	for (int i = 0; i < containedObjects.size(); i++)
	{
		delete containedObjects[i];
	}

}
File::File(Text * a, Folder * fn) :FSObject(a, fn)
{
	content = nullptr;
	accessDescriptor = new AccessDescriptor(this);
}
void File::accept(FilesystemVisitor* v) {
	v->visitFile(this);
}
void File::write(Byte* content) {
		this->content = new Byte(*content);
}
FSObject* File::copy() {
	File* novi = new File(this->getName(), this->parent);
	novi->write(this->content);
	return novi;
}

long File::size()
{
	if(content!=nullptr)return sizeof(content);
}


Byte* File::read() {
	return this->content;
}
File::~File() {
	delete content;
}

SearchVisitor::SearchVisitor(Text* t) {
	filename = new Text(*t);
}
void SearchVisitor::visitFile(File * f)
{
	if (f->getName() == filename) 
		foundObjects.push_back(f);
}
void SearchVisitor::visitFolder(Folder * f)
{
	if (f->getName() == filename) {
		foundObjects.push_back(f);
		folder = f;
	}
	for (unsigned int i = 0; i < f->containedObjects.size(); i++) {
			f->containedObjects[i]->accept(this);
	}

}
CheckVisitor::CheckVisitor(Text * t)
{
	access = new Text(*t);
}
void CheckVisitor::visitFile(File * f)
{
	AccessDescriptor* a = f->getAccessDescriptor();
	if (a->checkAccess(access)) {
		check = true;
	}
	else
		check = false;
}
void CheckVisitor::visitFolder(Folder * f)
{
	AccessDescriptor* a = f->getAccessDescriptor();
	if (a->checkAccess(access)) {
		check = true;
	}
	else check = false;
	for (unsigned int i = 0; i < f->containedObjects.size(); i++) {
		f->containedObjects[i]->accept(this);
	}
}
