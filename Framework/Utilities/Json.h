#pragma once

namespace Json
{
	void GetValue(Json::Value& parent, string name, bool& vec);
	void SetValue(Json::Value& parent, string name, bool& vec);

	void GetValue(Json::Value& parent, string name, float& vec);
	void SetValue(Json::Value& parent, string name, float& vec);

	void GetValue(Json::Value& parent, string name, int& vec);
	void SetValue(Json::Value& parent, string name, int& vec);

	void GetValue(Json::Value& parent, string name, D3DXVECTOR2& vec);
	void SetValue(Json::Value& parent, string name, D3DXVECTOR2& vec);

	void GetValue(Json::Value& parent, string name, D3DXVECTOR3& vec);
	void SetValue(Json::Value& parent, string name, D3DXVECTOR3& vec);

	void GetValue(Json::Value& parent, string name, D3DXCOLOR& vec);
	void SetValue(Json::Value& parent, string name, D3DXCOLOR& vec);

	void GetValue(Json::Value& parent, string name, string& value);
	void SetValue(Json::Value& parent, string name, string& value);

	void ReadData(wstring file, Json::Value* root);
	void WriteData(wstring file, Json::Value* root);
}