#include "pch.h"
#include "WinMain.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
// 새 콘솔창 생성
	AllocConsole();
	SetConsoleTitle(TEXT("stdout"));

	freopen_s(&dummyOut, "CONOUT$", "wt", stdout);
	freopen_s(&dummyIn, "CONIN$", "r", stdin);
//

	GetHtml getHtml(_link);
	curlResult = getHtml.Load();

	JsonParse jsonParse(curlResult, sentences, "cppguidelines");

	shuffleRandom.Init(sentences.size());

	//randNum = random.GetNumber(sentences.size());				// mt19937 랜덤 사용
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
	PAINTSTRUCT ps;
	static HWND b1, b2, b3;
	int senCount = shuffleRandom.GetCount(); // 내부 연산 후 카운터 올라갔으므로 차감 후 표시
	int senCountDigits = shuffleRandom.GetCountDigits();

	//string temp;
	//temp.assign(sentence.begin(), sentence.end());

	switch (message)
	{
	case WM_CREATE:
		b1 = CreateWindow(L"button", L"CppGuide", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			20, 20, 100, 25, hWnd, (HMENU)0, g_hInst, NULL);
		b2 = CreateWindow(L"button", L"GetTopic", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			150, 20, 100, 25, hWnd, (HMENU)1, g_hInst, NULL);
		b3 = CreateWindow(L"button", L"ShowTopic", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			280, 20, 100, 25, hWnd, (HMENU)2, g_hInst, NULL);
		return 0;
	case WM_PAINT:
		//LPCSTR str_cpp = &sentence, str_rank;
		hdc = BeginPaint(hWnd, &ps);
		//DrawText(hdc, )
		TextOut(hdc, 50, 50, to_wstring(senCount).c_str(), senCountDigits); // 현재 가이드라인 문장 번호
		TextOut(hdc, 20, 100, sentence.c_str(), sentence.size()); // 가이드라인 랜덤 문장
		TextOut(hdc, 20, 150, oneTopic.c_str(), oneTopic.size()); // 실시간 검색어 문장
		EndPaint(hWnd, &ps);
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case 0:												// 가이드라인 랜덤하게 뽑아서 뿌리기
			//randNum = random.GetNumber(sentences.size());
			randNum = shuffleRandom.GetRandomNum();
			sentence = strToW.Convert(sentences[randNum]);

			InvalidateRect(hWnd, NULL, TRUE); // 화면 무효화
			UpdateWindow(hWnd); // WM_PAINT 호출
			SetFocus(hWnd);
			return 0;
		case 1:												// 파이썬으로 실검 JSON으로 저장
			topicNow.PyLoad();
			return 0;
		case 2:												// 실검 JSON 가져와서 뿌리기
			oneTopic = strToW.Convert("");
			topicResult = topicNow.GetString();

			JsonParse topicParse(topicResult, topicVector, "topic");

			for (std::vector<string>::size_type i = 0; i < topicVector.size(); ++i)
			{
				oneTopic += strToW.Convert(topicVector[i]);
				oneTopic += strToW.Convert(" ");
			}

			InvalidateRect(hWnd, NULL, TRUE); // 화면 무효화
			UpdateWindow(hWnd); // WM_PAINT 호출
			SetFocus(hWnd);
			return 0;
		}
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_RETURN:
		case VK_SPACE:
			SendMessage(b1, BM_CLICK, 0, 0);
			return 0;
		default:
			return 0;
		}
	case WM_DESTROY:
		FreeConsole();
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}