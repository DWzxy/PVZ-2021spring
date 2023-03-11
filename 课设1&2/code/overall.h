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
//��������С
const int console_screen_size_x = 120;
const int console_screen_size_y = 56;
//���ڴ�С
const int screen_size_x = 120;
const int screen_size_y = 56;
//�����ݿ��С
const int single_length = 11;
const int single_width = 5;
//�ݿ�������
const int whole_length = 9;
const int whole_width = 5;
//��ƺλ��
const int grass_top = 0;
const int grass_left = single_length;
const int grass_bottom = ( single_width + 1 ) * whole_width;
const int grass_right = single_length + 1 + ( single_length + 1 ) * whole_length;

//��ɫ
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

//���ô��ڱ���
void set_screen_title( TCHAR* x );
//���ô��ڴ�С
void set_screen_size();
//������ɫ
void set_color( int color );
//����ɫ���
void print_in_color( const string& x , int color = default_color );
//���ù��λ��
void set_cursor( int x , int y );
//���ع��
void hide_cursor();

//��λʱ�䣨���룩
const int single_time = 100;

//���������
const int help_length = 20;
//���������
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