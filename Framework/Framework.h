#pragma once

#ifdef _DEBUG
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

//미리 컴파일된 헤더
//pch

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <Windows.h>
#include <vector>
#include <unordered_map>
#include <assert.h>
#include <functional>
#include <fstream>
#include <set>
#include <random>

using namespace std;

//DirectX
#include <d3dcompiler.h>
#include <d3d11.h>
#include <D3DX10math.h>
#include <D3DX11async.h>

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")
#pragma comment(lib, "d3dcompiler.lib")

///////////////////////////////////////////////////

// ImGui
#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"
#pragma comment(lib, "ImGui/ImGui.lib")
///////////////////////////////////////////////////
// DirectXTex
#include "DirectTex/DirectXTex.h"
#pragma comment(lib, "DirectTex/DirectXTex.lib")

////////////////////////////////////////////////
// jsoncpp
#include <json/json.h>
#pragma comment(lib, "json/jsoncpp.lib")

//////////////////////////////////////////////
// mysql
#include <mysql.h>
#pragma comment(lib, "libmysql.lib")



typedef D3DXVECTOR3 Vector3;
typedef D3DXVECTOR2 Vector2;
typedef D3DXMATRIX  Matrix;
typedef D3DXCOLOR   Color;
typedef UINT		uint;

#define DEVICE Graphics::Get()->GetDevice()
#define DC	   Graphics::Get()->GetDC()

#define CHECK(p) assert(SUCCEEDED(p))
#define ZERO(p) ZeroMemory(&p, sizeof(p))

#define SAFE_DELETE(p) { if(p) { delete(p); (p) = nullptr; }}
#define SAFE_DELETE_ARRAY(p){ if(p) { delete[](p); (p) = nullptr; }}
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p) = nullptr;}}

#define WinMaxWidth 1280
#define WinMaxHeight 720

#undef max
#undef min

const wstring ShaderPath = L"../_Shaders/";
const wstring TexturePath = L"../_Resources/_Textures/";
const string TilePath = "../_Resources/_TileDatas/";
const wstring JsonPath = L"../_Resources/_JsonData/";

extern HWND handle;



#include "Interfaces/IObject.h"

#include "Utilities/SingletonBase.h"
#include "Systems/Graphics.h"
#include "Systems/Keyboard.h"
#include "Systems/Mouse.h"
#include "Systems/Time.h"

#include "Utilities/Gui.h"
#include "Utilities/FileStream.h"

#include "Renders/Resources/VertexTypes.h"
#include "Renders/Resources/ShaderBuffer.h"
#include "Renders/Resources/GlobalBuffer.h"
#include "Renders/Resources/Texture2D.h"

#include "Renders/IA/VertexBuffer.h"
#include "Renders/IA/IndexBuffer.h"
#include "Renders/IA/InputLayout.h"

#include "Renders/Shaders/VertexShader.h"
#include "Renders/Shaders/PixelShader.h"
#include "Renders/States.h"


#include "Utilities/DirectHelpers.h"
#include "Utilities/Path.h"
#include "Utilities/String.h"
#include "Utilities/BoundingBox.h"
#include "Utilities/Json.h"
#include "Utilities/cpplinq.hpp"


#include "Systems/Camera.h"

