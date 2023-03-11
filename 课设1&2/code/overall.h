#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<cstring>
#include<windows.h>
#include<conio.h>
#include<string>
#include<list>
#include<ctime>
using namespace std;
//缓冲区大小
const int console_screen_size_x = 120;
const int console_screen_size_y = 56;
//窗口大小
const int screen_size_x = 120;
const int screen_size_y = 56;
//单个草块大小
const int single_length = 11;
const int single_width = 5;
//草块行列数
const int whole_length = 9;
const int whole_width = 5;
//草坪位置
const int grass_top = 0;
const int grass_left = single_length;
const int grass_bottom = ( single_width + 1 ) * whole_width;
const int grass_right = single_length + 1 + ( single_length + 1 ) * whole_length;

//颜色
const int default_color = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
const int grass_color = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
const int black = 0;
const int selected = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED |
BACKGROUND_INTENSITY | 0;

const int dark_red = FOREGROUND_RED;
const int light_red = FOREGROUND_RED | FOREGROUND_INTENSITY;
const int dark_green = FOREGROUND_GREEN;
const int light_green = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
const int dark_blue = FOREGROUND_BLUE;
const int light_blue = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
const int dark_yellow = FOREGROUND_RED | FOREGROUND_GREEN;
const int light_yellow = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
const int dark_cyan = FOREGROUND_GREEN | FOREGROUND_BLUE;
const int light_cyan = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
const int dark_purple = FOREGROUND_BLUE | FOREGROUND_RED;
const int light_purple = FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY;
const int grey = FOREGROUND_INTENSITY;

const int dark_red_back = BACKGROUND_RED;
const int light_red_back = BACKGROUND_RED | BACKGROUND_INTENSITY;
const int dark_green_back = BACKGROUND_GREEN;
const int light_green_back = BACKGROUND_GREEN | BACKGROUND_INTENSITY;
const int dark_blue_back = BACKGROUND_BLUE;
const int light_blue_back = BACKGROUND_BLUE | BACKGROUND_INTENSITY;
const int dark_yellow_back = BACKGROUND_RED | BACKGROUND_GREEN;
const int light_yellow_back = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
const int dark_cyan_back = BACKGROUND_GREEN | BACKGROUND_BLUE;
const int light_cyan_back = BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
const int dark_purple_back = BACKGROUND_BLUE | BACKGROUND_RED;
const int light_purple_back = BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY;
const int grey_back = BACKGROUND_INTENSITY;

//设置窗口标题
void set_screen_title( TCHAR* x );
//设置窗口大小
void set_screen_size();
//设置颜色
void set_color( int color );
//带颜色输出
void print_in_color( const string& x , int color = default_color );
//设置光标位置
void set_cursor( int x , int y );
//隐藏光标
void hide_cursor();

//单位时间（毫秒）
const int single_time = 100;

//帮助栏宽度
const int help_length = 20;
//阳光栏宽度
const int sun_length = 10;

enum Plant_type{
	peashooter , sunflower , cherry_bomb , wall_nut , potato_mine , snow_pea ,
	chomper , repeater , squash , threepeater , jalapeno , spikeweed ,
	torchwood , tall_nut , pumpkin , garlic
};
enum Zombie_type{
	ordinary , flag , conehead , pole_vaulting , bucket , newspaper ,
	dancing , back_up , jack_in_the_box , catapult
};
enum Bullet_type{ pea , snow , fire };
enum Grid_state{ shop , plant , wipe };