#include <windows.h>
#include<tchar.h>
#include "triangle.h"
#include "globals.h"

HINSTANCE g_hInstance = 0;
HANDLE g_hOutput = 0;

int screen_width=600;
int screen_height=600;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); //窗口函数说明

int WINAPI WinMain(HINSTANCE hInstance, //WinMain函数说明
	HINSTANCE hPrevInst,
	LPSTR lpszCmdLine,
	int nCmdShow)
{
	HWND hwnd;
	MSG Msg;
	WNDCLASS wndclass;
	TCHAR lpszClassName[] = _T("window"); //窗口类名
	TCHAR lpszTitle[] = _T("demo"); //窗口标题名
										  //窗口类的定义
	wndclass.style = 0; //窗口类型为缺省类型
	wndclass.lpfnWndProc = WndProc; //窗口处理函数为WndProc
	wndclass.cbClsExtra = 0; //窗口类无扩展
	wndclass.cbWndExtra = 0; //窗口实例无扩展
	wndclass.hInstance = hInstance; //当前实例句柄
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);				//窗口的最小化图标为缺省图标
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);					//窗口采用箭头光标
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);	//窗口背景为白色
	wndclass.lpszMenuName = NULL;									//窗口中无菜单
	wndclass.lpszClassName = lpszClassName;							//窗口类名为"窗口示例"




	//创建一个控制台窗口

//	AllocConsole();
//	g_hOutput = GetStdHandle(STD_OUTPUT_HANDLE);//设置控制台窗口的属性
//	CHAR title[] = "Output Debug Window";
//	SetConsoleTitle((LPCTSTR)title);
//	SetConsoleTextAttribute((HANDLE)g_hOutput, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);//| FOREGROUND_BLUE );
//	hwnd = NULL;
//	while (NULL == hwnd) hwnd = ::FindWindow(NULL, (LPCTSTR)title);
////屏蔽掉控制台窗口的关闭按钮，以防窗口被误删除
//	HMENU hmenu = ::GetSystemMenu(hwnd, FALSE);
//	DeleteMenu(hmenu, SC_CLOSE, MF_BYCOMMAND);





	if (!RegisterClass(&wndclass)) //如果注册失败则发出警告声音
	{
		//MessageBeep(0);
		return FALSE;
	}
	//创建窗口
	hwnd = CreateWindow(lpszClassName, //窗口类名
		lpszTitle, //窗口实例的标题名
		WS_OVERLAPPEDWINDOW, //窗口的风格
		CW_USEDEFAULT,
		CW_USEDEFAULT, //窗口左上角坐标为缺省值
		600,
		600, //窗口的高和宽为缺省值
		NULL, //此窗口无父窗口
		NULL, //此窗口无主菜单
		hInstance, //创建此窗口的应用程序的当前句柄
		NULL); //不使用该值
			   //显示窗口
	ShowWindow(hwnd, nCmdShow);
	//绘制用户区
	UpdateWindow(hwnd);
	//消息循环
	while (GetMessage(&Msg, NULL, 0, 0))
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam; //消息循环结束即程序终止时将信息返回系统
}

//窗口函数
LRESULT CALLBACK WndProc(HWND hwnd,
						UINT message,
						WPARAM wParam,
						LPARAM lParam)
{
	HDC hdc; // 定义指向设备的句柄
	HPEN hPen; // 定义指向画笔的句柄
	PAINTSTRUCT PtStr; //定义指向包含绘图信息的结构体变量
	vector<triangle> showT;
	vector<triangle>::iterator it;
	int i, j;
	color current_c;
	//vector<double> zBuffer;
	


	switch (message) {
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &PtStr);
		hPen = (HPEN)GetStockObject(WHITE_PEN); // 黑色画笔
		SelectObject(hdc, hPen); // 选择画笔
		//InvalidateRect函数触发WM_PAINT消息
		//paint();


		readfile();
		InitCamera();
		World2View();
		View2Screen();//已经转化到屏幕坐标系
		
		
		init_z();//深度
		init_c();//颜色


		it = trangles.begin();
		for (i = 0; i < 600; i++) {
			for (j = 0; j < 600; j++) {
				//j是横坐标，i是横坐标
				z_buffer(j,i);
				//SetPixel(hdc, i, j, RGB(current_c.R, current_c.G, current_c.B));
				//SetPixel(hdc,j, i, RGB(0, 255, 0));
			}
		}
		for (i = 0; i < 600; i++) {
			for (j = 0; j < 600; j++) {
				//SetPixel(hdc, i, j, RGB(255*current_c.R, 255*current_c.G, 255*current_c.B));
				SetPixel(hdc,j , i, RGB(255*(screen_c[i][j].R), 255*(screen_c[i][j].G), 255*(screen_c[i][j].B)));
			}
		}
		/*for (; it != trangles.end(); it++) {
			SetPixel(hdc, (int)(it->A.v.x), (int)(it->A.v.y), RGB(0, 255, 0));
			SetPixel(hdc, (int)(it->B.v.x), (int)(it->B.v.y), RGB(0, 255, 0));
			SetPixel(hdc, (int)(it->C.v.x), (int)(it->C.v.y), RGB(0, 255, 0));
		}*/
		EndPaint(hwnd, &PtStr); // 结束绘图
		break;
	case WM_DESTROY:
		PostQuitMessage(0); //调用PostQuitMessage发出WM_QUIT消息
		break;
	default: //缺省时采用系统消息缺省处理函
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return (0);
}

