#include<stdio.h>
#include<stdlib.h>
#include<cstring>
#include<windows.h>
#include<conio.h>
#include<iostream>
#include"store.h"
#include"lawn.h"
#include"overall.h"
#include"game.h"
using namespace std;
class Game;
//初始化
Store::Store():plant_list{
	Peashooter(),Wall_nut(),  Chomper() ,Threepeater(),
	Torchwood(),Garlic(),Plant(),Plant(),
	Sunflower(), Potato_mine(),Repeater(), Jalapeno(),
	Tall_nut(),Plant(),Plant(),Plant(),
	Cherry_bomb(),Snow_pea(),Squash(),Spikeweed(),
	Pumpkin(),Plant(),Plant(),Plant() } {
	page = 0;
	sun = 50;
	sun_cooling = 0;
	sun_circle = 55 + rand() % 40;//5.5-10.5秒掉落一个阳光
	sun_flash = 0;
	score = 0;
	score_refresh = 0;
	chat_cooling = 0;
	chat_circle = 40;
	now_chat = 0;
	chat [ 0 ] = (char*) "";
	chat [ 1 ] = (char*) "这块地已经种植了植物";
	chat [ 2 ] = (char*) "这块地没有种植植物";
	chat [ 3 ] = (char*) "阳光不足";
	chat [ 4 ] = (char*) "植物冷却中";
	chat [ 5 ] = (char*) "正在添加中……";
	chat [ 6 ] = (char*) "这块地已经种植了南瓜头";
	chat [ 7 ] = (char*) "一大波僵尸正在靠近";

	print_frame();//画框
	print_all_plant();//打印植物栏
	print_sun( light_yellow );//打印阳光
	print_score();//打印分数
	print_shovel();//打印铲子
	print_help();//打印帮助信息
}
//画框
void Store::print_frame(){
	set_cursor( 0 , grass_bottom + 1 );
	for ( int i = 0; i < screen_size_x; i++ ) print_in_color( "-" );
	for ( int i = grass_bottom + 2; i < 40; i++ ) {
		set_cursor( screen_size_x - help_length - 1 , i );
		print_in_color( "│" );
		set_cursor( help_length - 1 , i );
		print_in_color( "│" );
		set_cursor( screen_size_x - help_length - sun_length - 1 , i );
		print_in_color( "│" );
	}
	set_cursor( screen_size_x - help_length - 1 , grass_bottom + 1 );
	print_in_color( "┬" );
	set_cursor( help_length - 1 , grass_bottom + 1 );
	print_in_color( "┬" );
	set_cursor( screen_size_x - help_length - sun_length - 1 , grass_bottom + 1 );
	print_in_color( "┬" );
	for ( int k = 1; k < 4; k++ ) {
		set_cursor( help_length , grass_bottom + 1 + k * 2 );
		for ( int i = help_length; i < screen_size_x - help_length - sun_length; i++ )
			print_in_color( "-" );
	}
	set_cursor( screen_size_x - help_length - sun_length - 1 , grass_bottom + 1 + 3 * 2 );
	for ( int i = screen_size_x - help_length - sun_length - 1; i < screen_size_x - help_length; i++ )
		print_in_color( "-" );
	set_cursor( screen_size_x - help_length - 1 , grass_bottom + 1 + 3 * 2 );
	print_in_color( "┤" );
	set_cursor( screen_size_x - help_length - sun_length - 1 , grass_bottom + 1 + 2 );
	print_in_color( "┤" );
	set_cursor( screen_size_x - help_length - sun_length - 1 , grass_bottom + 1 + 2 * 2 );
	print_in_color( "┤" );
	set_cursor( screen_size_x - help_length - sun_length - 1 , grass_bottom + 1 + 3 * 2 );
	print_in_color( "┤" );
	set_cursor( screen_size_x / 2 , grass_bottom + 1 + 4 * 2 );
	print_in_color( "▼" );
}
//打印植物栏
void Store::print_all_plant(){
	for ( int i = 0; i < 3; i++ ) {
		for ( int j = 0; j < 4; j++ ) print_plant( i , j , default_color , page );
	}
}
//翻页
void Store::turn_page( int x ){
	page = x;
	print_all_plant();
	if ( page == 0 ){
		set_cursor( screen_size_x / 2 , grass_bottom + 1 + 4 * 2 );
		print_in_color( "▼" );
	}
	else if ( page == 1 ){
		set_cursor( screen_size_x / 2 , grass_bottom + 1 + 4 * 2 );
		print_in_color( "▲" );
	}
	else {
		set_cursor( screen_size_x / 2 , grass_bottom + 1 + 4 * 2 );
		print_in_color( "  " );
	}
}
//打印单个植物
void Store::print_plant( int i , int j , int k , int page ){
	j %= 4;
	int z = help_length + 1 + i * 22;
	int w = grass_bottom + 1 + 1 + j * 2;
	set_cursor( z , w );
	print_in_color( "                      " , default_color );
	set_cursor( z , w );
	print_in_color( plant_list [ i ] [ j + page * 4 ].name , k );
	print_in_color( " $" , k );
	print_in_color( to_string( plant_list [ i ] [ j + page * 4 ].cost_sun ) , k );
	print_in_color( " (" , k );
	print_in_color( to_string( plant_list [ i ] [ j + page * 4 ].cooling * 100 /
		plant_list [ i ] [ j + page * 4 ].cool_time ) , k );
	print_in_color( "%)" , k );
}
//打印阳光
void Store::print_sun( int x ) {
	set_cursor( screen_size_x - help_length - sun_length + 2 , grass_bottom + 1 + 1 );
	print_in_color( "阳光 " , x );
	set_cursor( screen_size_x - help_length - sun_length + 2 , grass_bottom + 1 + 2 );
	printf( "     " );
	set_cursor( screen_size_x - help_length - sun_length + 2 , grass_bottom + 1 + 2 );
	print_in_color( to_string( sun ) , x );
}
//打印分数
void Store::print_score(){
	set_cursor( screen_size_x - help_length - sun_length + 2 , grass_bottom + 1 + 4 );
	print_in_color( "分数 " , light_red );
	set_cursor( screen_size_x - help_length - sun_length + 2 , grass_bottom + 1 + 5 );
	printf( "     " );
	set_cursor( screen_size_x - help_length - sun_length + 2 , grass_bottom + 1 + 5 );
	print_in_color( to_string( score ) , light_red );
}
//打印铲子
void Store::print_shovel() {
	set_cursor( screen_size_x - help_length - sun_length + 1 , grass_bottom + 1 + 3 * 2 + 1 );
	print_in_color( "铲除植物" , light_cyan );
}
//打印帮助信息
void Store::print_help() {
	set_cursor( screen_size_x - help_length + 1 , grass_bottom + 1 + 2 );
	print_in_color( "按↑↓←→键控制\n" , light_blue );
	set_cursor( screen_size_x - help_length + 1 , grass_bottom + 1 + 2 * 2 );
	print_in_color( "空格键：确定\n" , light_blue );
	set_cursor( screen_size_x - help_length + 1 , grass_bottom + 1 + 3 * 2 );
	print_in_color( "Esc键：暂停\n" , light_blue );
}
//植物冷却，阳光产生，更新提示
void Store::refresh( Game& game ){
	for ( int i = 0; i < 3; i++ ){
		for ( int j = 0; j < 8; j++ ){
			if ( plant_list [ i ] [ j ].cooling < plant_list [ i ] [ j ].cool_time ){
				plant_list [ i ] [ j ].cooling++;
				if ( j<page * 4 || j> page * 4 + 3 ) continue;
				if ( plant_list [ i ] [ j ].cooling == plant_list [ i ] [ j ].cool_time ){
					if ( game.state == Game::State::Shopping && game.x == i && game.y == j%4 )
						print_plant( i , j , selected , page );
					else print_plant( i , j , default_color , page );
				}
				else{
					if ( game.state == Game::State::Shopping && game.x == i && game.y == j%4 )
						print_plant( i , j , grey_back , page );
					else print_plant( i , j , grey , page );
				}
			}
		}
	}
	sun_cooling++;
	if ( sun_cooling == sun_circle ){
		sun_cooling = 0;
		sun_circle = 55 + rand() % 40;
		if ( sun < 99975 ) sun += 25;
		sun_flash = 2;
	}
	if ( sun_flash ){
		if ( sun_flash <= 1 ) print_sun( light_yellow );
		else print_sun( selected );
		sun_flash--;
	}
	if ( score_refresh ) print_score();
	chat_refresh();
}
//设置提示信息
void Store::set_chat( int x ){
	now_chat = x;
	chat_cooling = 0;
}
//更新提示信息
void Store::chat_refresh(){
	if ( now_chat == 0 ){
		print_chat( 0 );
		return;
	}
	if ( chat_cooling <= 2 ) print_chat( selected );
	else if ( chat_cooling == 3 ) print_chat( default_color | dark_purple_back );
	if ( chat_cooling == chat_circle ) set_chat( 0 );
	else chat_cooling++;
}
//打印提示信息
void Store::print_chat( int x ){
	if ( !now_chat && chat_cooling ) return;
	//用chat_cooling=1来表示在无提示信息状况下的“已清空”
	for ( int i = 0; i < 4; i++ ){
		set_cursor( 2 , grass_bottom + i * 2 + 2 );
		print_in_color( "                " , default_color );
	}
	if ( !now_chat ){
		chat_cooling = 1;
		return;
	}
	set_color( x );
	if ( strlen( chat [ now_chat ] ) > 48 ){
		for ( int i = 0; i < strlen( chat [ now_chat ] ); i++ ) {
			if ( i % 16 == 0 ) set_cursor( 2 , grass_bottom + 2 + i / 8 );
			cout << chat [ now_chat ] [ i ];
		}
	}
	else{
		for ( int i = 0; i < strlen( chat [ now_chat ] ); i++ ) {
			if ( i % 16 == 0 ) set_cursor( 2 , grass_bottom + 4 + i / 8 );
			cout << chat [ now_chat ] [ i ];
		}
	}
	set_color( default_color );
}