#pragma once

#include "CurlDriver.h"

string curlResult;
const char *_link = "https://raw.githubusercontent.com/rihyungame/tetris/main/Main.cpp";

#define TITLE L"EverydayRead"
#define WIDTH 800
#define HEIGHT 600

HINSTANCE g_hInst;
HWND g_hwnd;

RECT rc = { 0, 0, WIDTH, HEIGHT };

HRESULT			 InitWindow(HINSTANCE hInstance, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


