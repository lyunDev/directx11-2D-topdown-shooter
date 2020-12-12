#include "Framework.h"
#include "FileStream.h"

FileStream::FileStream(string path, uint flags)
	: flags(flags)
{
	int iosFlags = ios::binary;
	iosFlags |= flags & FILE_STREAM_WRITE ? ios::out : 0;
	iosFlags |= flags & FILE_STREAM_READ ? ios::in : 0;
	
	if (flags & FILE_STREAM_WRITE)
	{
		out.open(path, iosFlags);
		if (out.fail())
		{ 
			// 여기서 에러나면 경로문제 
			out.flush();
			out.close();
			assert(false);
		}
	}
	else if (flags & FILE_STREAM_READ)
	{
		in.open(path, iosFlags);
		if (in.fail())
		{
			in.clear();
			in.close();
			assert(false);
		}
	}

}
void FileStream::WriteString(string value)
{
	Write(value.length());
	out.write((const char *)value.c_str(), value.length());
}

string FileStream::ReadString()
{
	uint length = Read<uint>();
	string temp;
	temp.resize(length);
	in.read((char *)&temp[0], length);

	return temp;
}

FileStream::~FileStream()
{
	if (flags & FILE_STREAM_WRITE)
	{
		out.flush();
		out.close();
	}
	else if (flags & FILE_STREAM_READ)
	{
		in.clear();
		in.close();
	}
}
