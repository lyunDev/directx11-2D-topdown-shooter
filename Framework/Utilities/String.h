#pragma once

class String
{
public:
	// string 분리
	static void SplitString
	(vector<string>* result, string origin, string tok);

	static void SplitString
	(vector<wstring>* result, wstring origin, wstring tok);

	// 인자로받은 값이 첫 시작값과 동일한지 확인
	static bool StartWith(string str, string comp);
	static bool StartWith(wstring str, wstring comp);

	// 인자로받은 값이 문자열에 포함되어있는지 확인
	static bool Contain(string str, string comp);
	static bool Contain(wstring str, wstring comp);

	// 문자열 내용 변경
	static void Replace(string* str, string comp, string rep);
	static void Replace(wstring* str, wstring comp, wstring rep);

	// Convert to string
	static string ToString(D3DXVECTOR3 vec3, int precision = 5);
	static wstring ToWstring(D3DXVECTOR3 vec3, int precision = 5);

	// Convert to string
	static wstring ToWstring(string str);
	static string ToString(wstring str);

	//template<typename ... Args>
	//static std::string string_format(const std::string& format, Args ... args) {
	//	size_t size = snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0' 
	//	if (size <= 0)
	//	{
	//		throw std::runtime_error("Error during formatting.");
	//	} std::unique_ptr<char[]> buf(new char[size]);
	//	snprintf(buf.get(), size, format.c_str(), args ...);
	//	return std::string(buf.get(), buf.get() + size - 1);// We don't want the '\0' inside 
	//}
	template<typename ... Args>
	static std::string string_format(const std::string& format, Args ... args)
	{
		size_t size = snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
		if (size <= 0) { throw std::runtime_error("Error during formatting."); }
		std::unique_ptr<char[]> buf(new char[size]);
		snprintf(buf.get(), size, format.c_str(), args ...);
		return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
	}

};