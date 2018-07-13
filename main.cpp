#include <windows.h>
#include<tchar.h>
#include "triangle.h"
#include "globals.h"

HINSTANCE g_hInstance = 0;
HANDLE g_hOutput = 0;

int screen_width=600;
int screen_height=600;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); //���ں���˵��

int WINAPI WinMain(HINSTANCE hInstance, //WinMain����˵��
	HINSTANCE hPrevInst,
	LPSTR lpszCmdLine,
	int nCmdShow)
{
	HWND hwnd;
	MSG Msg;
	WNDCLASS wndclass;
	TCHAR lpszClassName[] = _T("window"); //��������
	TCHAR lpszTitle[] = _T("demo"); //���ڱ�����
										  //������Ķ���
	wndclass.style = 0; //��������Ϊȱʡ����
	wndclass.lpfnWndProc = WndProc; //���ڴ�����ΪWndProc
	wndclass.cbClsExtra = 0; //����������չ
	wndclass.cbWndExtra = 0; //����ʵ������չ
	wndclass.hInstance = hInstance; //��ǰʵ�����
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);				//���ڵ���С��ͼ��Ϊȱʡͼ��
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);					//���ڲ��ü�ͷ���
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);	//���ڱ���Ϊ��ɫ
	wndclass.lpszMenuName = NULL;									//�������޲˵�
	wndclass.lpszClassName = lpszClassName;							//��������Ϊ"����ʾ��"




	//����һ������̨����

//	AllocConsole();
//	g_hOutput = GetStdHandle(STD_OUTPUT_HANDLE);//���ÿ���̨���ڵ�����
//	CHAR title[] = "Output Debug Window";
//	SetConsoleTitle((LPCTSTR)title);
//	SetConsoleTextAttribute((HANDLE)g_hOutput, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);//| FOREGROUND_BLUE );
//	hwnd = NULL;
//	while (NULL == hwnd) hwnd = ::FindWindow(NULL, (LPCTSTR)title);
////���ε�����̨���ڵĹرհ�ť���Է����ڱ���ɾ��
//	HMENU hmenu = ::GetSystemMenu(hwnd, FALSE);
//	DeleteMenu(hmenu, SC_CLOSE, MF_BYCOMMAND);





	if (!RegisterClass(&wndclass)) //���ע��ʧ���򷢳���������
	{
		//MessageBeep(0);
		return FALSE;
	}
	//��������
	hwnd = CreateWindow(lpszClassName, //��������
		lpszTitle, //����ʵ���ı�����
		WS_OVERLAPPEDWINDOW, //���ڵķ��
		CW_USEDEFAULT,
		CW_USEDEFAULT, //�������Ͻ�����Ϊȱʡֵ
		600,
		600, //���ڵĸߺͿ�Ϊȱʡֵ
		NULL, //�˴����޸�����
		NULL, //�˴��������˵�
		hInstance, //�����˴��ڵ�Ӧ�ó���ĵ�ǰ���
		NULL); //��ʹ�ø�ֵ
			   //��ʾ����
	ShowWindow(hwnd, nCmdShow);
	//�����û���
	UpdateWindow(hwnd);
	//��Ϣѭ��
	while (GetMessage(&Msg, NULL, 0, 0))
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam; //��Ϣѭ��������������ֹʱ����Ϣ����ϵͳ
}

//���ں���
LRESULT CALLBACK WndProc(HWND hwnd,
						UINT message,
						WPARAM wParam,
						LPARAM lParam)
{
	HDC hdc; // ����ָ���豸�ľ��
	HPEN hPen; // ����ָ�򻭱ʵľ��
	PAINTSTRUCT PtStr; //����ָ�������ͼ��Ϣ�Ľṹ�����
	vector<triangle> showT;
	vector<triangle>::iterator it;
	int i, j;
	color current_c;
	//vector<double> zBuffer;
	


	switch (message) {
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &PtStr);
		hPen = (HPEN)GetStockObject(WHITE_PEN); // ��ɫ����
		SelectObject(hdc, hPen); // ѡ�񻭱�
		//InvalidateRect��������WM_PAINT��Ϣ
		//paint();


		readfile();
		InitCamera();
		World2View();
		View2Screen();//�Ѿ�ת������Ļ����ϵ
		
		
		init_z();//���
		init_c();//��ɫ


		it = trangles.begin();
		for (i = 0; i < 600; i++) {
			for (j = 0; j < 600; j++) {
				//j�Ǻ����꣬i�Ǻ�����
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
		EndPaint(hwnd, &PtStr); // ������ͼ
		break;
	case WM_DESTROY:
		PostQuitMessage(0); //����PostQuitMessage����WM_QUIT��Ϣ
		break;
	default: //ȱʡʱ����ϵͳ��Ϣȱʡ����
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return (0);
}

