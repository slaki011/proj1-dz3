#pragma once
#include<string>
using namespace std;
class FSException:public exception{
public:
	FSException* causedBy;
	FSException(string& msg) :exception() {}
	FSException(string& msg, FSException& cause) :exception(cause){}
};

class AccessException :public FSException {
public:
	AccessException(string& msg) :FSException(msg) {}
	AccessException(string& msg, FSException& cause) :FSException(msg,cause) {}
};
class OperationFailedException :public FSException {
public:
	OperationFailedException(string& msg) :FSException(msg) {}
	OperationFailedException(string& msg,FSException& cause) :FSException(msg,cause) {}
};
class NameCollisionException :public OperationFailedException {
public:
	NameCollisionException(string& msg) :OperationFailedException(msg) {}
	NameCollisionException(string& msg,FSException& cause) :OperationFailedException(msg,cause) {}
};
class WriteFailedException :public OperationFailedException {
public:
	WriteFailedException(string& msg):OperationFailedException(msg){}
};