#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

#include <string>
class FileException
{					 // ���� ���� Ŭ����
	string filename; // ���� �̸�
	bool bRead;		 // ���� ���

public:
	FileException(string name, bool b) : filename(name), bRead(b) {}
};

#endif