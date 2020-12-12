#pragma once


enum EFileSystem : uint
{
	FILE_STREAM_READ = 1U << 0,
	FILE_STREAM_WRITE = 1U << 1,
};
class Tile;
class FileStream
{
public :
	FileStream(string path, uint flags);
	~FileStream();

	/*void Write(int value)
	{
		out.write(reinterpret_cast<const char*>(&value), sizeof(int));

	}
	void Write(const char* value, int size)
	{
		out.write(reinterpret_cast<const char*>(value), size);
	}*/
	template<typename T, typename = typename enable_if<
		is_same<T, bool>::value || 
		is_same<T, char>::value || 
		is_same<T, int>::value || 
		is_same<T, float>::value || 
		is_same<T, uint>::value || 
		is_same<T, Vector3>::value || 
		is_same<T, Vector2>::value || 
		is_same<T, Matrix>::value || 
		is_same<T, Color>::value ||
		is_same<T, Tile>::value
	>::type>
	void Write(T value)
	{
		out.write(reinterpret_cast<const char*>(&value), sizeof(T));
	}

	template<typename T>
	T Read()
	{
		T value;
		in.read(reinterpret_cast<char*>(&value), sizeof(T));
		return value;
	}
	void WriteString(string value);
	string ReadString();

private :
	ofstream out; // 출력
	ifstream in; // 입력

	uint flags;
};