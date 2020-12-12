#pragma once

struct DXDesc
{
	wstring AppName;
	HINSTANCE instance;
	HWND handle;
	UINT width;//윈도우 창의 가로 세로 크기
	UINT height;
};

class Window
{
public:
	Window(DXDesc desc);
	~Window();

	WPARAM Run(IObject* mainObj); //게임루프 함수




private:
	//함수호출 규약
	//stdcall
	//cdecl
	static LRESULT CALLBACK WndProc //메세지 처리함수
	(
		HWND handle,//어떤창인지 알아보는 창의 식별자
		UINT message,//어떤 메세지가 들어왔는지 알아보는것.
		WPARAM wParam,//키보드의 관련된정보 어떤키보드가 눌렸는지 알아보는것.
		LPARAM lParam //마우스의 좌표 클릭이 눌렸는지 마우스의 좌표를 알아보는것.
	);
	void MainRender();
	static DXDesc desc;
	IObject* mainObj = nullptr;
	//static class Program* program;
};