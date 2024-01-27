#include "pch.h"
#include "WinMain.h"

#define ID_SCR 100

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
// �ܼ�â ����
	AllocConsole();

// �ܼ�â ���� ����
#ifdef _DEBUG
	SetConsoleTitle(TEXT("Debug Mode"));
#else
	SetConsoleTitle(TEXT("Release Mode"));
#endif

// stream �翬��
	freopen_s(&dummyOut, "CONOUT$", "wt", stdout);
	freopen_s(&dummyIn, "CONIN$", "r", stdin);

// wstream �ѱ� ����
	wcout.imbue(locale(".utf8"));					
	wcin.imbue(locale("kor"));

// CURL Html �ҽ� ��������
	GetHtml getHtml(_link);
	curlResult = getHtml.Load();

// nlohmann Json ����
	JsonParse jsonParse(curlResult, sentences, "cppguidelines");
	
	shuffleRandom.Init(sentences.size());

// sources dir ���� Ž��
	dirList.Init();
	dirList.Load();
	cppDirList = dirList.GetVec();

	//randNum = random.GetNumber(sentences.size());				// mt19937 ���� ���
	//randNum = shuffleRandom.GetRandomNum();
	//sentence = strToW.Convert(sentences[randNum]);

	if (FAILED(InitWindow(hInstance, nCmdShow)))
		return 0;

	MSG msg = {};

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}

HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = TITLE;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassExW(&wcex))
		return E_FAIL;

	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	g_hInst = hInstance;
	g_hwnd = CreateWindowW(TITLE, TITLE, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance, nullptr);

	if (!g_hwnd)
	{
		return E_FAIL;
	}

	ShowWindow(g_hwnd, nCmdShow);

	return S_OK;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	HFONT hFont, OldFont;
	PAINTSTRUCT ps;
	static HWND b1, b2, b3, hScroll;
	int senCount = shuffleRandom.GetCount(); // ���� ���� �� ī���� �ö����Ƿ� ���� �� ǥ��
	int senCountDigits = shuffleRandom.GetCountDigits();

	//wstring temp = strToW.Convert(sentences[randNum]);	// sentences���� wstring���� convert

	wstring source;

	ifstream file(cppDirList[0]);

	if (file.is_open())
	{
		string temp;
		int size = 0;

		file.seekg(0, std::ios::end);	// ��ġ �����ڸ� ���� ������
		size = file.tellg();		// ��ġ �����ڱ����� ũ�� ����
		temp.resize(size, ' ');		// drawtext���� \0 ���� ǥ�� ������ ' '�� �ʱ�ȭ
		file.seekg(0, std::ios::beg);
		file.read(&temp[0], size); // ������ �о �����ŭ ����
		source = strToW.Convert(temp); // utf-8 -> wstring?
	}

	LPCWSTR strDraw = source.c_str();

	RECT rtDraw = { 300,300,1000,1000 };

	switch (message)
	{
	case WM_CREATE:
		b1 = CreateWindow(L"button", L"CppGuide", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			20, 20, 100, 25, hWnd, (HMENU)0, g_hInst, NULL);
		b2 = CreateWindow(L"button", L"GetTopic", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			150, 20, 100, 25, hWnd, (HMENU)1, g_hInst, NULL);
		b3 = CreateWindow(L"button", L"ShowTopic", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			280, 20, 100, 25, hWnd, (HMENU)2, g_hInst, NULL);
		hScroll = CreateWindow(L"scrollbar", NULL, WS_CHILD | WS_VISIBLE | SBS_VERT, 100, 300, 20, 900,
			hWnd, (HMENU)ID_SCR, g_hInst, NULL);		
		SetScrollRange(hScroll, SB_CTL, 0, 255, true);
		SetScrollPos(hScroll, SB_CTL, TempPos, TRUE);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		hFont = CreateFont(23, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("�ü�")); // ��Ʈ ����
		OldFont = (HFONT)SelectObject(hdc, hFont);
		DrawText(hdc, strDraw, source.size(), &rtDraw, DT_WORDBREAK | DT_EXPANDTABS); // DT_EXPANDTABS �� ���� ǥ��
		TextOut(hdc, 50, 50, to_wstring(senCount).c_str(), senCountDigits); // ���� ���̵���� ���� ��ȣ
		TextOut(hdc, 20, 100, sentence.c_str(), sentence.size()); // ���̵���� ���� ����
		TextOut(hdc, 20, 150, oneTopic.c_str(), oneTopic.size()); // �ǽð� �˻��� ����
		EndPaint(hWnd, &ps);
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case 0:												// ���̵���� �����ϰ� �̾Ƽ� �Ѹ���
			//randNum = random.GetNumber(sentences.size());
			randNum = shuffleRandom.GetRandomNum();
			sentence = strToW.Convert(sentences[randNum]);

			InvalidateRect(hWnd, NULL, TRUE); // ȭ�� ��ȿȭ
			UpdateWindow(hWnd); // WM_PAINT ȣ��
			SetFocus(hWnd);
			break;
		case 1:												// ���̽����� �ǰ� JSON���� ����
			topicNow.PyLoad();
			break;
		case 2:												// �ǰ� JSON �����ͼ� �Ѹ���
			oneTopic = strToW.Convert("");
			topicResult = topicNow.GetString();

			JsonParse topicParse(topicResult, topicVector, "topic");

			for (std::vector<string>::size_type i = 0; i < topicVector.size(); ++i)
			{
				oneTopic += strToW.Convert(topicVector[i]);
				oneTopic += strToW.Convert(" ");
			}

			InvalidateRect(hWnd, NULL, TRUE); // ȭ�� ��ȿȭ
			UpdateWindow(hWnd); // WM_PAINT ȣ��
			SetFocus(hWnd);
			break;
		}
		return 0;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_RETURN:
		case VK_SPACE:
			SendMessage(b1, BM_CLICK, 0, 0);
			break;
		}
		return 0;
	case WM_VSCROLL:
		switch (LOWORD(wParam))
		{
		case SB_LINEUP:
			TempPos = max(0, TempPos - 1);
			break;
		case SB_LINEDOWN:
			TempPos = min(255, TempPos + 1);
			break;
		case SB_PAGEUP:
			TempPos = max(0, TempPos - 10);
			break;
		case SB_PAGEDOWN:
			TempPos = min(255, TempPos + 10);
			break;
		case SB_THUMBTRACK:						// ��ũ�ѹ� �巡��
			TempPos = HIWORD(wParam); // y �� ����
			break;			
		}
		SetScrollPos((HWND)lParam, SB_CTL, TempPos, TRUE);
		InvalidateRect(hWnd, NULL, FALSE);
		return 0;
	case WM_DESTROY:
		FreeConsole();
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}