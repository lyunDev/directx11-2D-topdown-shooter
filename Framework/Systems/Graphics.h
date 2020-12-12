#pragma once

/*
DirectX 11
DirectX June 2010 SDK

SoftWare developmentkit

*/

/*
DX11의 자원 종류
ID3D11Buffer : 거처가는 공간. 저장하고 보내는 역할, 자료들의 기차역 혹은 버스정류장같은 역할. CPU의 데이터, Rem의 데이터를 임시로 버퍼에 넣고 VRem으로 보내는 역할

ID3D11Texture : 사용 용도가 정해져 있지않은 객체.
				Texture란 픽셀(1pixel당 4byte)들의 집합.

Texture와 관련된 세부 정보
ID3D11RenderTargetView : 픽셀들이 렌더타겟뷰에 그려짐. 도화지의 느낌. 쓰여진다.

ID3D11ShaderResourceView : 쉐이더는 그래픽 카드에서 어떻게 제어할지 연산하는 도구.
						   쉐이더에서 쓰는 자원.
						   그래픽 자제가 나오려면 쉐이더를 작성해서 넣어줘야 구동이 된다.
						   HLSL (High Level Shader Language) : 고수준 단계의 쉐이더 언어

ID3D11DepthStencilView : 고무판, 판화, 3D에서 사용된다.

ID3D11UnorderedAccessView : 순서없는 접근 뷰.
							자잘한 간단연산을 많이 해야될 경우 그것들을 동시에 처리하는 것.

CPU는  복잡한 계산을 처리하는데 동시에 처리하기 힘듬.
그래픽 카드는 간단 연산을 여럿이 달려들어 처리하는데 머릿수가 많아 동시 처리가 된다.
그래픽 카드의 코어는 1000개 단위이다.
*/

/*
deviceContext : 그리는  모든것들이 연관되어있고 시작되는 것.

Rendering Pipeline)
최종적으로 화면에 나오기 까지의 그리는 단계
순서)
IA - VS - RS - PS - OM

IA : Input Assembler - 기초 단계들을 받아줌  primitive 정보를 바인딩한다.
	Vertex Buffer
	IndexBuffer
	Topology - 연결성 정보
	InputLayout

VS : vertex Shader 정점 계산을 하는 단계
	정점의 위치를 계산
	공간변환
		Local - World - View - Porjection - Viewport
		World - View - Projection 정도만 VS단계에서 처리

RS : Rasterizer state
viewport 연산 (NDC좌표계를 화면 좌표계로 변환해준다)
rastrization (픽셀화)
culling : 후면추리기 (앞면인지 뒷면인지 체크)
Scissor Test :화면안인지 밖인지 구분

PS : Pixel Shader
 -> 픽셀 연산 

OM : Output Merger


정점 (vertex)
정점은 꼭짓점들이지만 DX에서는 위치 그자체 이상의 의미와 정보를 가진다.




*/
// 09/04
/*
Rendering pipeline : 이미지 공정 과정
2D의 경우
1. IA(Input Assembler) : 입력 조립. 뭔가를 그리기 위한 기초 정보(값)를 입력한다.
						 
 : 점 그리는 것, IndexBuffer, Topology(연결성 정보) : 점과 점을 이어주는 거, InputLayout
	정점(vertex) : 면을 이루는데 필요한 꼭짓점
				   정점에는 좌표값(position) 이외에도 다른 값을 더 넣을 수 있다.
				   예를 들어서 색상(color)등을 추가 할 수 있다.
				   캐릭터를 그릴 때도 무수히 많은 정점이 사용된다.
2. VS(VertexShader) : 정점의 위치를 계산해주는 것
3. RS(Rasterizer State) : 그려야할 영역을 픽셀로 채워주는 것.
	Backface culling : 3D에서 보이지 않는 뒷면을  그리지 않는 것.
	NDC(Nomalized Device Coordinate) 좌표계 : (-1 ~ 1). 좌표의 viewport 변환. 멀티샘플링, fill mode의 변환도 여기서 일어난다.
4. PS(Pixel Shader) : 픽셀들을 어떻게 조작을 할지 정하는 것. 색상의 톱업 다운, 이미지의 프리미티브(삼각형)를 붙여준다.
5. OM(Output Merger) :

실질적으로 코딩이 가능한 공간은 VS와 PS 단계뿐이다. 나머지는 값만 넣어준다.

2D에서 하는 것 : 공간변환

공간 변환
1.Local : 지역 공간. 지정 물체의 각 꼭짓점의 좌표. 물체 기준 좌표
2.World : 맵 공간. 맵 상의 좌표
3.View : 카메라 공간(위치). 절두체 공간 안에 상을 비춘다. 카메라의 위치가 원점이다.
4.Projection : 투영 공간. 원근감. 거리에 따라서 비율이 작아지게 하는 것.
	FOV(Filed Of View) : 줌인. 줌아웃
5.Viewport : 화면 작업 공간. 윈도우창 영역에 대한 공간. Rasterizer 단계에서 계산됨.

행렬 공부할 것 곱하기까지 알면 더욱 좋고

Description과 Context의 차이점
Description : 자원을 어떻게 만들어달라는 요구. 견적서
Context : 파이프라인 안에 들어가는 세팅값
/

/
IDXGI : DirectX Graphics Infrastructure.
		제조사가 다른 그래픽 카드(하드웨어)를 구애받지 않고 편하게 사용하게 해주는 것.
SwapChain : 더블 버퍼링을 위한 DXGI의 한 종류.
D3DXCOLOR : RGBA 구조체.
			Red,    Green,  Blue,   Alpha
			float,  float,  float,  float
			0 ~ 1까지 정규화된 값을 사용한다.
			1, 0, 0, 1
			80, 0, 0
			80 / 255, 0, 0, 1


			ID3D11Device* device = nullptr; //Interface 서로 다른 두 개를 연결하는 뜻의 통상의 인터페이스, DirectX 3D 사용, DX11 버전, Device는 자원 종류
	ID3D11DeviceContext* deviceContext = nullptr; //그리는데 필요한 모든 정보가 들어있다.
	IDXGISwapChain* swapChain = nullptr;
	ID3D11RenderTargetView* rtv = nullptr;
	D3D11_VIEWPORT viewport;
	D3DXCOLOR clearColor = 0xff555566; //초기화할 색상. OM단계에 넣어줄 값
*/

/*


*/




class D3DEnumAdapterInfo;
class D3DEnumOutputInfo;
class Graphics : public SingletonBase<Graphics>
{

public:
	friend class SingletonBase<Graphics>;

	

	//void Init();
	//void CreateBackbuffer();
	///////////////////////////////////
	

	ID3D11Device* GetDevice()
	{
		return device;
	}

	ID3D11DeviceContext* GetDC()
	{
		return deviceContext;
	}

	void Resize(const UINT& width, const UINT& height);
	void SetViewport(const UINT& width, const UINT& height);
	void InitViewport();

	void Begin();
	void End();

	void GUI();
private :
	void CreateSwapchain();
	void CreateRenderTargetView();
	void DeleteSurface();

 
private:
	Graphics();
	~Graphics();

private :
	void EnumerateAdapters();
	bool EnumerateAdapterOutput(D3DEnumAdapterInfo* adapterInfo);

private:
	ID3D11Device* device = nullptr; //DirectX11을 사용하는 객체들을 생성하는 역할
	ID3D11DeviceContext* deviceContext = nullptr; //그리는 것에 관련된 모든 정보들을 가지고 있는 객체
	IDXGISwapChain* swapChain = nullptr;
	ID3D11RenderTargetView* rtv = nullptr;
	D3D11_VIEWPORT viewport;
	D3DXCOLOR clearColor = 0xff555566;

	UINT numerator = 0;
	UINT denominator = 1;

	UINT gpuMemorySize;
	wstring gpuName;

	// VRAM이 제일 큰게 외장 그래픽
	vector<D3DEnumAdapterInfo*> adapterInfos;
	int selectedAdapterIndex = 0;

	// 수직 동기화
	bool bVsync = true;

	/*Rendering Pipeline
	*/
};

class D3DEnumAdapterInfo
{
public:
	~D3DEnumAdapterInfo();

	UINT adapterOrdinal = 0;
	IDXGIAdapter1* adapter = nullptr;
	DXGI_ADAPTER_DESC1 adapterDesc = { 0 };

	D3DEnumOutputInfo* outputInfo = nullptr;
};

class D3DEnumOutputInfo
{
public :
	~D3DEnumOutputInfo();

	IDXGIOutput *output = nullptr;
	DXGI_OUTPUT_DESC outputDesc = { 0 };

	// 수직 동기화
	UINT numerator = 0;
	UINT denominator = 1;
};

/*
COM Interface


*/
