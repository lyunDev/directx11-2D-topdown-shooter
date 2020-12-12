#include "Framework.h"
#include "FileStreamDemo.h"
#include "Utilities/FileStream.h"


void FileStreamDemo::Init()
{
	FileStream * f = new FileStream("./binary.txt", FILE_STREAM_WRITE );
	
	//f->Write(10);
	//f->Write(12.1231243f);
	//f->Write(Vector3(10, 20, 10));

	f->Write(string("Hello world"));
	SAFE_DELETE(f);

	FileStream * r = new FileStream("./binary.txt",  FILE_STREAM_READ);

	string temp = r->Read<string>();

	/*int a = r->Read<int>();
	float b = r->Read<float>();
	Vector3 c = r->Read<Vector3>();*/

//	SAFE_DELETE(f);
	SAFE_DELETE(r);

}

void FileStreamDemo::Destroy()
{
}

void FileStreamDemo::Update()
{
}

void FileStreamDemo::PreRender()
{
}

void FileStreamDemo::Render()
{
}

void FileStreamDemo::GUI()
{
}
