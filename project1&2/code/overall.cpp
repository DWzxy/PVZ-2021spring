#include<stdio.h>
#include<stdlib.h>
#include<cstring>
#include<windows.h>
#include<conio.h>
#include<iostream>
#include"overall.h"
//设置窗口名称
void set_screen_title(TCHAR* x) {
	SetConsoleTitle(x);
}
//设置窗口大小和位置
void set_screen_size() {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(handle, &info);
	COORD now1 = { 120,40 };
	SetConsoleScreenBufferSize(handle, now1);
	SMALL_RECT now2 = { 0,0,120 - 1,40 - 1 };
	SetConsoleWindowInfo(handle, 1, &now2);
}
//设置颜色
void set_color(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
//带颜色输出
void print_in_color(const string& x, int color) {
	set_color(color);
	cout << x;
	set_color(default_color);
}
//设置光标位置
void set_cursor(int x, int y) {
	COORD now = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), now);
}
//隐藏光标
void hide_cursor() {
	CONSOLE_CURSOR_INFO cursor;
	cursor.dwSize = 1;
	cursor.bVisible = false;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}
