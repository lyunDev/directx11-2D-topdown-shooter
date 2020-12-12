#pragma once

class Path
{
public:
	// 인자로 받은 경로에 파일이 존재하는지 확인
	static bool ExistFile(string path);
	static bool ExistFile(wstring path);

	// 인자로 받은 경로가 존자하는지 확인
	static bool ExistDirectory(string path);
	static bool ExistDirectory(wstring path);

	// 인자 합침
	static string Combine(string path1, string path2);
	static wstring Combine(wstring path1, wstring path2);

	// vector를 받아서 combine기능 수행
	static string Combine(vector<string> paths);
	static wstring Combine(vector<wstring> paths);

	// 인자로 받은 경로의 마지막 폴더 이름을 반환한다.
	static string GetDirectoryName(string path);
	static wstring GetDirectoryName(wstring path);

	// 인자로 받은 경로의 파일 확장자를 반환한다.
	static string GetExtension(string path);
	static wstring GetExtension(wstring path);

	// 인자로 받은 경로의 파일이름을 반환한다. 확장자 포함
	static string GetFileName(string path);
	static wstring GetFileName(wstring path);

	// 확장자 없이 파일 이름 반환
	static string GetFileNameWithoutExtension(string path);
	static wstring GetFileNameWithoutExtension(wstring path);

	const static WCHAR* ImageFilter;
	const static WCHAR* ShaderFilter;
	const static WCHAR* TextFilter;
	const static WCHAR* TileFilter;
	const static WCHAR* TMapFilter;
	const static WCHAR* TDSDFilter;

	// 파일을 연다.
	static void OpenFileDialog(wstring file, const WCHAR* filter, wstring folder, function<void(wstring)> func, HWND hwnd = NULL);
	// 파일을 저장한다.
	static void SaveFileDialog(wstring file, const WCHAR* filter, wstring folder, function<void(wstring)> func, HWND hwnd = NULL);

	// 원하는 경로의 파일 경로를 모두 받는다.
	static void GetFiles(vector<string>* files, string path, string filter, bool bFindSubFolder);
	static void GetFiles(vector<wstring>* files, wstring path, wstring filter, bool bFindSubFolder);

	// 폴더를 만든다.
	static void CreateFolder(string path);
	static void CreateFolder(wstring path);

	static void CreateFolders(string path);
	static void CreateFolders(wstring path);
};