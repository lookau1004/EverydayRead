#include "pch.h"
#include "WinMain.h"

#define ID_SCR 100
#define ID_EDIT 101

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	// 콘솔창 생성
	AllocConsole();

	// 콘솔창 제목 변경
#ifdef _DEBUG
	SetConsoleTitle(TEXT("Debug Mode"));
#else
	SetConsoleTitle(TEXT("Release Mode"));
#endif

	// stream 재연결
	freopen_s(&dummyOut, "CONOUT$", "wt", stdout);
	freopen_s(&dummyIn, "CONIN$", "r", stdin);

	// wstream 한글 설정
	wcout.imbue(locale(".utf8"));
	wcin.imbue(locale("kor"));

	// CURL Html 소스 가져오기
	GetHtml getHtml(_link);
	curlResult = getHtml.Load();

	// nlohmann Json으로 문장 파싱
	jsonParse.Init(curlResult, sentences, "cppguidelines");
	sentences = jsonParse.GetVector();

	// 문장 랜덤 함수 초기화
	sentencesRandom.Init(sentences.size());

	// sources 폴더 리스트 가져오기
	dirList.Init();
	dirList.Load();
	cppDirList = dirList.GetVec();

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
	WNDCLASSEXW wcex, wcex2;

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

	wcex2.cbSize = sizeof(WNDCLASSEX);

	wcex2.style = CS_HREDRAW | CS_VREDRAW;
	wcex2.lpfnWndProc = WndProc2;
	wcex2.cbClsExtra = 0;
	wcex2.cbWndExtra = 0;
	wcex2.hInstance = hInstance;
	wcex2.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex2.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex2.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex2.lpszMenuName = NULL;
	wcex2.lpszClassName = TITLE2;
	wcex2.hIconSm = LoadIcon(wcex2.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassExW(&wcex))
		return E_FAIL;

	if (!RegisterClassExW(&wcex2))
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
	int senCount = sentencesRandom.GetCount(); // 내부 연산 후 카운터 올라갔으므로 차감 후 표시
	int senCountSize = sentencesRandom.GetCountDigits();

	switch (message)
	{
	case WM_CREATE:
		b1 = CreateWindow(L"button", L"CppGuide", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			20, 20, 100, 25, hWnd, (HMENU)10, g_hInst, NULL);
		b2 = CreateWindow(L"button", L"GetTopic", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			150, 20, 100, 25, hWnd, (HMENU)11, g_hInst, NULL);
		b3 = CreateWindow(L"button", L"ShowTopic", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			280, 20, 100, 25, hWnd, (HMENU)12, g_hInst, NULL);
		b4 = CreateWindow(L"button", L"ShowCpp", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			410, 20, 100, 25, hWnd, (HMENU)13, g_hInst, NULL);
		b5 = CreateWindow(L"button", L"Calculate", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			540, 20, 100, 25, hWnd, (HMENU)14, g_hInst, NULL);
		hEdit = CreateWindow(L"edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | ES_READONLY | WS_VSCROLL,
			300, 300, 1000, 1000, hWnd, (HMENU)ID_EDIT, g_hInst, NULL);
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		hFont = CreateFont(23, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("궁서")); // 폰트 설정
		OldFont = (HFONT)SelectObject(hdc, hFont);
		SendMessage(hEdit, WM_SETFONT, WPARAM(hFont), TRUE);				// edit 컨트롤 폰트 설정
		SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)cppData.c_str());			// edit 컨트롤 text 설정
		TextOut(hdc, 50, 50, to_wstring(senCount).c_str(), senCountSize);	// 현재 가이드라인 문장 번호
		TextOut(hdc, 20, 100, sentence.c_str(), sentence.size());			// 가이드라인 랜덤 문장
		TextOut(hdc, 300, 270, fileAddress.c_str(), fileAddress.size());	// 파일 경로 표시
		EndPaint(hWnd, &ps);
		break;

	case WM_COMMAND:
		for (size_t i = 0; i < hStaticControls.size(); ++i)					// 매번 컨트롤이 눌러졌는지 검사
		{
			if (LOWORD(wParam) == i)
			{
				wstring topicLink = L"https://search.naver.com/search.naver?query=" +
					strToW.Convert(topicVector[i]);

				ShellExecute(NULL, L"open", topicLink.c_str(), NULL, NULL, SW_SHOWNORMAL);		// 인터넷 실행
				break;
			}
		}

		switch (LOWORD(wParam))
		{
		case 10:												// 가이드라인 랜덤하게 뽑아서 뿌리기
			//sentencesNum = random.GetNumber(sentences.size());
			sentencesNum = sentencesRandom.GetRandomNum();
			sentence = strToW.Convert(sentences[sentencesNum]);
			InvalidateRect(hWnd, NULL, TRUE);					// 화면 무효화
			UpdateWindow(hWnd);									// WM_PAINT 호출
			SetFocus(hWnd);
			break;

		case 11:												// 파이썬으로 실검 JSON으로 저장
			topicNow.PyLoad();
			break;

		case 12:												// 실검 JSON 가져와서 뿌리기
			topicResult = topicNow.GetString();

			topicParse.Init(topicResult, topicVector, "topic");
			topicVector = topicParse.GetVector();

			if (isLoadTopics == false)										// hStaticControls 채워지지 않았을때
			{
				for (size_t i = 0; i < topicVector.size(); ++i)
				{
					wstring controlText = std::to_wstring(i + 1) + L"위 ";	// 문장에 순위 추가
					controlText += strToW.Convert(topicVector[i]);
					HWND hStatic = CreateWindowEx(0, L"STATIC", controlText.c_str(),
						WS_CHILD | WS_VISIBLE | SS_NOTIFY, 20 + i * 220, 150, 200, 50, g_hwnd, (HMENU)i, g_hInst, NULL);

					hFont = CreateFont(23, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("궁서")); // 폰트 설정
					SendMessage(hStatic, WM_SETFONT, WPARAM(hFont), TRUE);	// 폰트 설정
					hStaticControls.push_back(hStatic);
				}

				isLoadTopics = true;
			}
			else															// Controls 채워져있고 버튼을 눌렀을때
			{
				for (size_t i = 0; i < topicVector.size(); ++i)
				{
					HWND hStatic = hStaticControls[i];
					wstring controlText = std::to_wstring(i + 1) + L"위 ";	// 문장에 순위 추가
					controlText += strToW.Convert(topicVector[i]);
					SetWindowText(hStatic, controlText.c_str());			// hwnd 컨트롤의 text 변경
				}
			}

			InvalidateRect(hWnd, NULL, TRUE);					// 화면 무효화
			UpdateWindow(hWnd);									// WM_PAINT 호출
			SetFocus(hWnd);
			break;

		case 13:												// CppFile 가져와서 보여주기
			cppFileRandom.Init(cppDirList.size());				// 랜덤 초기화
			cppFileNum = cppFileRandom.GetRandomNum();

			// 파일 경로 & 파일 내용 가져오기
			cppDir = cppDirList[cppFileNum];
			fileAddress.assign(cppDir.begin(), cppDir.end());	// 파일 경로 wstring 변환

			file.open(cppDir);

			if (file.is_open())
			{
				string temp;
				int size = 0;

				file.seekg(0, std::ios::end);	// 위치 지정자를 파일 끝으로
				size = file.tellg();			// 위치 지정자까지의 크기 저장
				temp.resize(size, ' ');			// drawtext에서 \0 문자 표시 때문에 ' '로 초기화
				file.seekg(0, std::ios::beg);
				file.read(&temp[0], size);		// 파일을 읽어서 사이즈만큼 저장

				temp = regex_replace(temp, std::regex("\n"), "\r\n");	// edit에서는 \n 대신 \r\n 사용
				cppData = strToW.Convert(temp);							// utf-8 -> wstring?
			}

			file.close();

			InvalidateRect(hWnd, NULL, TRUE); // 화면 무효화
			UpdateWindow(hWnd);				  // WM_PAINT 호출
			SetFocus(hWnd);
			break;
		case 14:							  // 자식창 생성
			if (!isNewWindowOpen)
			{
				newWindow = CreateWindowEx(0, TITLE2, TITLE2, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
					800, 600, g_hwnd, NULL, NULL, NULL);
				ShowWindow(newWindow, SW_SHOWNORMAL);
				isNewWindowOpen = true;
			}
			break;
		}
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_RETURN:
		case VK_SPACE:
			SendMessage(b1, BM_CLICK, 0, 0);
			break;
		}
		break;

	case WM_DESTROY:
		FreeConsole();
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

LRESULT CALLBACK WndProc2(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_CLOSE:
	case WM_DESTROY:
		DestroyWindow(hwnd);
		isNewWindowOpen = false;
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}

	return 0;
}
