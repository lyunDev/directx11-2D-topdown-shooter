#pragma once
#include "Renders/Shaders/IShader.h"
#include <unordered_map>

class ShaderCreator
{
public : 
	template<typename TShaderType, typename = typename enable_if<
		is_same<TShaderType, PixelShader>::value ||
		is_same<TShaderType, VertexShader>::value 
		>::type>
	static void Create(IShader** shader, const wstring filePath, const string entryName)
	{
		wstring key = filePath + String::ToWstring(entryName);
		auto result = shaderMap.find(key);
		if (result == shaderMap.end()) // 없으면
		{
			*shader = new TShaderType();
			(*shader)->Create(filePath, entryName);
			shaderMap.insert(make_pair(key, *shader));
			return;
		}
		else
		{
			// 있으면
			*shader = (*result).second;
		}
	}

	static unordered_map<wstring, IShader*>  shaderMap;
};
