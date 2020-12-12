#include "Framework.h"
#include "JsonDemo.h"

void JsonDemo::Init()
{
	/*Json::Value root;

	Json::Value student;
	int value1 = 10;
	float value2 = 20.0f;
	Vector3 value3 = Vector3(10, 20, 30);
	Json::SetValue(student, "Value1", value1);
	Json::SetValue(student, "Value2", value2);
	Json::SetValue(student, "Value3", value3);

	Json::Value uvData;
	Vector2 uv0 = Vector2(0, 1);
	Vector2 uv1 = Vector2(0, 0);
	Vector2 uv2 = Vector2(1, 1);
	Vector2 uv3 = Vector2(1, 0);
	Json::SetValue(uvData, "uv0", uv0);
	Json::SetValue(uvData, "uv1", uv1);
	Json::SetValue(uvData, "uv2", uv2);
	Json::SetValue(uvData, "uv3", uv3);

	root["Student"] = student;
	root["uvData"] = uvData;
 

	Json::WriteData(JsonPath + L"Test.json", &root);*/

	Json::Value root;
	Json::ReadData(JsonPath + L"test.json", &root);

	Json::Value student = root["Student"];
	int value1;
	float value2;
	Vector3 value3;
	Json::GetValue(student, "Value1", value1);
	Json::GetValue(student, "Value2", value2);
	Json::GetValue(student, "Value3", value3);
	int a = 1;
}

void JsonDemo::Destroy()
{
}

void JsonDemo::Update()
{
}

void JsonDemo::PreRender()
{
}

void JsonDemo::Render()
{
}

void JsonDemo::GUI()
{
}
