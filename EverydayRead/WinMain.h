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

//Json
JsonParse jsonParse;
JsonParse topicParse;

//DIR
DirList dirList;
std::vector<string> cppDirList;
string cppDir;
wstring cppData, fileAddress;

//Sentences
std::vector<string> sentences;
std::wstring sentence;

//TOPIC
TopicNow topicNow;
bool isLoadTopics;

std::string topicResult;
std::vector<string> topicVector;

//Wstring Convert
StrToW strToW;

//mt19937 Random
//Random random;

//ShuffleRandom
ShuffleRandom sentencesRandom;
ShuffleRandom cppFileRandom;
int sentencesNum;
int cppFileNum;

//WINDOW
#define TITLE L"EverydayRead"
#define TITLE2 L"Calculate"

//#define WIDTH 1980
//#define HEIGHT 1080

#define WIDTH GetSystemMetrics(SM_CXSCREEN)		// 전체화면
#define HEIGHT GetSystemMetrics(SM_CYSCREEN)

HINSTANCE g_hInst;
HWND g_hwnd;

RECT rc = { 0, 0, WIDTH, HEIGHT };

std::vector<HWND> hStaticControls;

HRESULT			 InitWindow(HINSTANCE hInstance, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProc2(HWND, UINT, WPARAM, LPARAM);

//WndProc
HDC hdc;
HFONT hFont, OldFont;
PAINTSTRUCT ps;
static HWND b1, b2, b3, b4, b5, hEdit, newWindow;
ifstream file;
bool isNewWindowOpen;