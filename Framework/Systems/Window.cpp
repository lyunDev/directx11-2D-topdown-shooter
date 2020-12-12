#include "Framework.h"//상대적인경로 ../ : 기준폴더에 어디까지인지
#include "Window.h"
#include "Graphics.h"
#include "Utilities/UpdateDispatcher.h"
#include "MySQL/LogManager.h"
//#include "Program.h"
//절대경로 : c://program 같은 전체경로
//상대경로 : ./ 현재폴더 , ../ 상위폴더

DXDesc Window::desc;

//Program* Window::program = nullptr;
HINSTANCE instance;

Window::Window(DXDesc desc)
{
	WNDCLASSEX wndClass;

	wndClass.cbClsExtra = 0;//예비영역 이지만 잘쓰지않음.
	wndClass.cbWndExtra = 0;//이것도 잘쓰지않음.
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//배경색 설정 메모리에 올라간걸 복사해오는식.
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);//커서모양 화살표모양의 커서를 가져온다.
	wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);//윈도우 로고
	wndClass.hIconSm = wndClass.hIcon;
	wndClass.hInstance = desc.instance;//생성자에서 받아주는것 어떤프로그램인지 확인하는거
	wndClass.lpfnWndProc = (WNDPROC)WndProc;//메세지처리함수의 주소가 들어감.함수포인터가 들어가는것
	wndClass.lpszClassName = desc.AppName.c_str();//클래스 이름정해주기
	wndClass.lpszMenuName = NULL;//메뉴이름인데 안쓰기때문에 널을 써넣어놓음.
	wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;//윈도우 창의 스타일
	wndClass.cbSize = sizeof(WNDCLASSEX);//어떤윈도우를 사용해서 만드는지.

	WORD wHr = RegisterClassEx(&wndClass);
	assert(wHr != 0);//릴리즈로 실행하면 이건 무시되서 에러가 표시되지않음. / 디버깅용 기능

	desc.handle = CreateWindowEx
	(
		WS_EX_APPWINDOW,//스타일 확장된 옵션
		desc.AppName.c_str(),//클래스 네임
		desc.AppName.c_str(),//윈도우 창의 이름
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW,//스타일
		CW_USEDEFAULT,//윈도우 창의 좌표,기본값 원래는 X 좌표가 들어간다
		CW_USEDEFAULT,//윈도우 창의 좌표,기본값 원래는 Y 좌표가 들어간다
		CW_USEDEFAULT,//윈도우 창의 가로 크기,기본값 나중에추가
		CW_USEDEFAULT,//윈도우 창의 세로 크기,기본값 나중에추가
		NULL,//부모창의 핸들
		(HMENU)NULL,//메뉴의 식별자이지만 쓰지않아서 널 을썻음
		desc.instance,//어떤 윈도우 프로그램인지 식별자
		NULL//안씀 그냥둠
	);

	RECT rect = { 0, 0, (LONG)desc.width, (LONG)desc.height };

	UINT centerX = (GetSystemMetrics(SM_CXSCREEN) - (UINT)desc.width) / 2;
	UINT centerY = (GetSystemMetrics(SM_CYSCREEN) - (UINT)desc.height) / 2;

	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	MoveWindow
	(
		desc.handle
		, centerX, centerY
		, rect.right - rect.left, rect.bottom - rect.top
		, true
	);

	ShowWindow(desc.handle, SW_SHOWNORMAL);//윈도우창을 보이게해주는것
	SetForegroundWindow(desc.handle);//실행시켰을때 제일위로 올라오게하는것
	SetFocus(desc.handle);//포커스 , 키보드나 마우스를 눌렀을때 조작이되는창.

	ShowCursor(true);//불형
	Window::desc = desc;

	::instance = desc.instance;

}

Window::~Window()
{
	DestroyWindow(desc.handle);
	UnregisterClass(desc.AppName.c_str(), desc.instance);
}

WPARAM Window::Run(IObject* mainObj)//메세지처리함수로 넘겨주는역활 / 나중에 조금 건드림
{
	MSG msg = { 0 };
	
	this->mainObj = mainObj;

	Graphics::Create();
	Keyboard::Create();
	Mouse::Create();
	Time::Create();
	Gui::Create();
	LogManager::Create();

	this->mainObj->Init();

	Time::Get()->Start();

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))//메세지 큐 / 대기열 먼저들어온 메세지부터 처리한다. / PM_REMOVE 는 메세지를 읽고 지워주는 역활. / GetMessage 다른메세지가 들어올때까지 대기 / PeekMessage 메세지가 안들어와도 다른작업을 계속 수행함.
		{
			if (msg.message == WM_QUIT)
				break;
		
			TranslateMessage(&msg);//키보드 메세지처리를 도와주는함수.
			DispatchMessage(&msg);//메세지함수에 메세지를 던져주는역활.
		}
		else
		{
			MainRender();
		//	Keyboard::Get()->Update();
		////	program->Update();
		//	Graphics::Get()->Begin();
		//	{
		//	//	program->Render();
		//	}
		//	Graphics::Get()->End();
		}
	}
	this->mainObj->Destroy();
	
	//SAFE_DELETE(program);
	LogManager::Delete();
	Gui::Delete();
	Time::Delete();
	Mouse::Delete();
	Keyboard::Delete();
	Graphics::Delete();




	return msg.wParam;
}


HWND handle;
LRESULT Window::WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)//메세지 처리함수 / api 하는동안에만 건드림
{
	Mouse::Get()->InputProc(message, wParam, lParam);
	Gui::Get()->MsgProc(handle, message, wParam, lParam);

	if (message == WM_CREATE)
	::handle = handle;


	if (message == WM_CLOSE || message == WM_DESTROY)
	{
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(handle, message, wParam, lParam);
}

void Window::MainRender()
{

	if (ImGui::GetIO().WantCaptureMouse == false)
	{
		Mouse::Get()->Update();
		Keyboard::Get()->Update();
	}

	Time::Get()->Update();
	Gui::Get()->Update();
	mainObj->Update();
	UpdateDispatcher::Update();

	mainObj->PreRender();
	//	program->Update();
	Graphics::Get()->Begin();
	{
		//	program->Render();
		mainObj->Render();
		
		mainObj->GUI();
		Gui::Get()->Render();
	}
	Graphics::Get()->End();
}
