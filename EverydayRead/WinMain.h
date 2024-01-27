#pragma once

#include "GetHtml.h"
#include "JsonParse.h"
#include "StrToW.h"
#include "ShuffleRandom.h"
#include "TopicNow.h"
#include "DirList.h"
//#include "Random.h"

//CONSOLE
FILE* dummyOut;
FILE* dummyIn;

//CURL
string curlResult;
const char* _link = "https://raw.githubusercontent.com/rihyungame/EverydayRead/master/EverydayRead/guideline.json";

//DIR
DirList dirList;
std::vector<string> cppDirList;

//Sentences
std::vector<string> sentences;
std::wstring sentence;

//TOPIC
TopicNow topicNow;

std::string topicResult;
std::vector<string> topicVector;
std::wstring oneTopic;

//Wstring Convert
StrToW strToW;

//mt19937 Random
//Random random;

//ShuffleRandom
ShuffleRandom shuffleRandom;
int randNum;

//WINDOW
#define TITLE L"EverydayRead"

//#define WIDTH 1980
//#define HEIGHT 1080

#define WIDTH GetSystemMetrics(SM_CXSCREEN)		// 전체화면
#define HEIGHT GetSystemMetrics(SM_CYSCREEN)

HINSTANCE g_hInst;
HWND g_hwnd;

RECT rc = { 0, 0, WIDTH, HEIGHT };

HRESULT			 InitWindow(HINSTANCE hInstance, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int TempPos = 0; // 스크롤 위치
