#include"lawn.h"
#include"zombie.h"
#include"overall.h"
#include"game.h"
#include<ctime>
#include<cstdlib>
#include<iostream>
class Game;
//初始化
void Grid::init( int z , int w ) {
	x = z * ( single_length + 1 ) + grass_left;
	y = w * ( single_width + 1 );
	sta_x = z;
	sta_y = w;
	in_refresh = out_refresh = 0;
	plant = NULL;
	pumpkin = NULL;
	zombie_list.clear();
	color = grass_color;

	bombing = 0;
	squashing = 0;
	flashing = 0;
}
//添加植物
void Grid::add_plant( Plant* r ){
	plant = r;
	r->x = sta_x;
	r->y = sta_y;
}
void Grid::clear(){
	for ( int i = 0; i < single_width; i++ ){
		set_cursor( x + 1 , y + 1 + i );
		string u( 11 , ' ' );
		print_in_color( u , default_color );
	}//清空内部
}
//打印植物，僵尸
void Grid::print( Game& game ){
	clear();
	if ( plant != NULL || pumpkin != NULL ){
		if ( plant != NULL ){
			print_name( plant->name , x , y + 2 , plant->color );
			if ( pumpkin == NULL )
				print_defence( x + 3 , y + 3 , plant->defence , plant->blood );
		}
		if ( pumpkin != NULL ){
			set_cursor( x + 1 , y + 2 );
			print_in_color( "[" , pumpkin->color );
			set_cursor( x + 11 , y + 2 );
			print_in_color( "]" , pumpkin->color );
			print_defence( x + 3 , y + 3 , pumpkin->defence , pumpkin->blood );
		}
		if ( zombie_list.size() != 0 ){
			if ( zombie_list.size() > 1 ){
				set_cursor( x + 2 , y + 4 );
				print_in_color( "僵尸" , zombie_list.front()->color );
				print_in_color( "*" , zombie_list.front()->color );
				print_in_color( to_string( zombie_list.size() ) ,
					zombie_list.front()->color );
			}
			else print_name( zombie_list.front()->name , x , y + 4 ,
				zombie_list.front()->color );
		}
	}
	else if ( zombie_list.size() != 0 && plant == NULL && pumpkin == NULL ){
		if ( zombie_list.size() == 1 ){
			print_name( zombie_list.front()->name , x , y + 2 , zombie_list.front()->color );
			print_defence( x + 3 , y + 3 , zombie_list.front()->defence ,
				zombie_list.front()->blood );
		}
		else if ( zombie_list.size() > 5 ){
			set_cursor( x + 2 , y + 3 );
			print_in_color( "僵尸" , zombie_list.front()->color );
			print_in_color( "*" , zombie_list.front()->color );
			print_in_color( to_string( zombie_list.size() ) , zombie_list.front()->color );
		}
		else{
			list<Zombie*>::iterator k;
			int i = 1;
			for ( k = zombie_list.begin() , i = 1; k != zombie_list.end(); k++ , i++ ){
				if ( i == 1 ) print_name( ( *k )->name , x , y + 3 , ( *k )->color );
				if ( i == 2 ) print_name( ( *k )->name , x , y + 2 , ( *k )->color );
				if ( i == 3 ) print_name( ( *k )->name , x , y + 4 , ( *k )->color );
				if ( i == 4 ) print_name( ( *k )->name , x , y + 1 , ( *k )->color );
				if ( i == 5 ) print_name( ( *k )->name , x , y + 5 , ( *k )->color );
			}
		}

	}
}
//打印生命值
void Grid::print_defence( int x , int y , int z , int w ){
	int cnt = z * 100 / w;
	set_cursor( x , y );
	print_in_color( "HP: " , default_color );
	print_in_color( to_string( cnt ) , default_color );
	print_in_color( "%" , default_color );
}
//打印名称
void Grid::print_name( string name , int x , int y , int z ){
	if ( name.length() <= 8 ) set_cursor( x + 3 , y );
	else set_cursor( x + 1 , y );
	print_in_color( name , z );
}
//植物行动
void Grid::plant_action( Game& game ){
	plant->action( game );
}
//僵尸减血
void Grid::zombie_minus( Zombie* now , int z , Game& game ){
	now->defence -= z;
	if ( now->defence <= 0 ){
		if ( game.store.score < 99995 ) game.store.score += now->score;
		game.store.score_refresh = 1;
	}
	in_refresh = 1;
}
//植物减血
void Grid::plant_minus( Plant* y , int x ){
	y->defence -= x;
	if ( y->defence <= 0 ){
		if ( y->type == Plant_type::pumpkin ) pumpkin = NULL;
		else plant = NULL;
	}
	if ( y->eating == 0 ) y->eating = 4;
	in_refresh = 1;
}
//打印边框
void Grid::print_circle( Game& game ){
	int q = sta_x , w = sta_y;
	string u( 13 , '#' );
	set_cursor( x , y );
	if ( w == 0 || game.lawn.grid_list [ q ] [ w - 1 ].color == grass_color )
		print_in_color( u , color );
	set_cursor( x , y + single_width + 1 );
	if ( w == whole_width - 1 ||
		game.lawn.grid_list [ q ] [ w + 1 ].color == grass_color )
		print_in_color( u , color );
	u.assign( 1 , '#' );
	if ( q == 0 || game.lawn.grid_list [ q - 1 ] [ w ].color == grass_color )
		for ( int i = 1; i <= single_width; i++ ) {
			set_cursor( x , y + i );
			print_in_color( u , color );
		}
	if ( q == whole_length - 1 ||
		game.lawn.grid_list [ q + 1 ] [ w ].color == grass_color )
		for ( int i = 1; i <= single_width; i++ ) {
			set_cursor( x + single_length + 1 , y + i );
			print_in_color( u , color );
		}
}
//更新
void Grid::refresh( Game& game ){
	clear_zombie();
	if ( in_refresh ) print( game );
	if ( out_refresh ) print_circle( game );
	if ( squashing ){
		squashing--;
		if ( squashing == 0 ) color = grass_color , print_circle( game );
		else if ( squashing == 10 ) color = light_yellow , print_circle( game );
	}
	if ( bombing ){
		bombing--;
		if ( bombing == 0 ) color = grass_color , print_circle( game );
		else if ( bombing == 10 )color = dark_red , print_circle( game );
	}
	if ( flashing ){
		flashing--;
		if ( flashing % 3 == 1 )color = default_color , print_circle( game );
		else  color = grass_color , print_circle( game );
	}
	in_refresh = 0;
	out_refresh = 0;
}
//清除死亡的僵尸
void Grid::clear_zombie(){
	for ( list<Zombie*>::iterator k = zombie_list.begin(); k != zombie_list.end(); ){
		Zombie* now = *k;
		if ( now->defence <= 0 ){
			if ( now->type == back_up ){
				if ( ( (Back_up*) now )->direction == 0 )
					( (Back_up*) now )->dancing->left = NULL;
				else if ( ( (Back_up*) now )->direction == 1 )
					( (Back_up*) now )->dancing->right = NULL;
				else if ( ( (Back_up*) now )->direction == 2 )
					( (Back_up*) now )->dancing->top = NULL;
				else if ( ( (Back_up*) now )->direction == 3 )
					( (Back_up*) now )->dancing->bottom = NULL;
			}
			zombie_list.erase( k++ );
			in_refresh = 1;
		}
		else k++;
	}
}
Lawn::Lawn() {
	zombie_cooling = 0;//生产单个僵尸的进度
	whole_wave = 14;
	flag = 0;

	zombie_circle [ 0 ] [ 0 ] = 0;
	zombie_circle [ 1 ] [ 0 ] = 200;
	zombie_circle [ 2 ] [ 0 ] = 500;
	zombie_circle [ 3 ] [ 0 ] = 800;
	zombie_circle [ 4 ] [ 0 ] = 1100;
	zombie_circle [ 5 ] [ 0 ] = 1400;
	zombie_circle [ 6 ] [ 0 ] = 1700;
	zombie_circle [ 7 ] [ 0 ] = 2000;
	zombie_circle [ 8 ] [ 0 ] = 2300;
	zombie_circle [ 9 ] [ 0 ] = 2600;
	zombie_circle [ 10 ] [ 0 ] = 2900;
	zombie_circle [ 11 ] [ 0 ] = 3200;
	zombie_circle [ 12 ] [ 0 ] = 3500;
	zombie_circle [ 13 ] [ 0 ] = 3650;
	zombie_circle [ 14 ] [ 0 ] = 3800;

	zombie_circle [ 0 ] [ 1 ] = 1;
	zombie_circle [ 1 ] [ 1 ] = 1;
	zombie_circle [ 2 ] [ 1 ] = 1;
	zombie_circle [ 3 ] [ 1 ] = 1;
	zombie_circle [ 4 ] [ 1 ] = 2;
	zombie_circle [ 5 ] [ 1 ] = 2;
	zombie_circle [ 6 ] [ 1 ] = 3;
	zombie_circle [ 7 ] [ 1 ] = 3;
	zombie_circle [ 8 ] [ 1 ] = 3;
	zombie_circle [ 9 ] [ 1 ] = 4;
	zombie_circle [ 10 ] [ 1 ] = 4;
	zombie_circle [ 11 ] [ 1 ] = 4;
	zombie_circle [ 12 ] [ 1 ] = 6;
	zombie_circle [ 13 ] [ 1 ] = 6;
	zombie_circle [ 14 ] [ 1 ] = 9;

	for ( int i = 0; i <= whole_width; i++ ) {
		set_cursor( grass_left , i * ( single_width + 1 ) );
		string u( ( single_length + 1 ) * whole_length + 1 , '#' );
		print_in_color( u , grass_color );
	}
	for ( int i = 0; i <= whole_length; i++ ) {
		for ( int j = 0; j <= whole_width * ( single_width + 1 ); j++ ) {
			set_cursor( grass_left + i * ( single_length + 1 ) , j );
			print_in_color( "#" , grass_color );
		}
	}
	for ( int i = 0; i <= whole_width * ( single_width + 1 ); i++ ) {
		set_cursor( grass_left - 1 , i );
		print_in_color( "]" );
	}
	for ( int i = 0; i < whole_length; i++ ){
		for ( int j = 0; j < whole_width; j++ ) grid_list [ i ] [ j ].init( i , j );
	}
}
//更新
void Lawn::refresh( Game& game ){
	for ( int i = 0; i < whole_length; i++ ){
		for ( int j = 0; j < whole_width; j++ ) grid_list [ i ] [ j ].refresh( game );
	}
}
//产生僵尸
void Lawn::make_zombie( Game& game ){
	zombie_cooling++;
	int num = zombie_circle [ 0 ] [ 1 ];
	if ( zombie_cooling < zombie_circle [ num ] [ 0 ] ) return;
	srand( time( NULL ) );
	if ( num == whole_wave ){
		if ( !flag ){
			flag = 1;
			game.store.set_chat( 7 );
			int cnt = rand() % whole_width;
			Flag* now = new Flag();
			now->x = whole_length - 1;
			now->y = cnt;
			grid_list [ whole_length - 1 ] [ cnt ].zombie_list.push_back( now );
			grid_list [ whole_length - 1 ] [ cnt ].in_refresh = 1;
		}
		zombie_cooling = zombie_circle [ num - 3 ] [ 0 ];
		zombie_circle [ 0 ] [ 1 ] -= 3;
	}
	zombie_circle [ 0 ] [ 1 ]++;
	for ( int k = 0; k < zombie_circle [ num ] [ 1 ]; k++ ){
		while ( true ){
			int cnt = rand() % whole_width;
			if ( game.lawn.grid_list [ whole_length - 1 ] [ cnt ].zombie_list.size() > 2 )
				continue;
			Zombie* now = NULL;
			while ( now == NULL ){
				int type = rand() % 100;
				if ( type < 13 ) now = new Ordinary();
				else if ( type < 43 && num >= 4 ) now = new Conehead();
				else if ( type < 53 && num >= 6 ) now = new Pole_vaulting();
				else if ( type < 73 && num >= 7 )now = new Bucket();
				else if ( type < 83 && num >= 7 )now = new Newspaper();
				else if ( type < 90 && num >= 9 ) now = new Dancing();
				else if ( type < 95 && num >= 11 ) now = new Jack_in_the_box();
				else if ( type < 100 && num >= 12 ) now = new Catapult();
			}
			now->x = whole_length - 1;
			now->y = cnt;
			grid_list [ whole_length - 1 ] [ cnt ].zombie_list.push_back( now );
			grid_list [ whole_length - 1 ] [ cnt ].in_refresh = 1;
			break;
		}
	}
}
//僵尸行动
void Lawn::zombie_action( Game& game ){
	for ( int i = 0; i < whole_length; i++ ){
		for ( int j = 0; j < whole_width; j++ ){
			if ( grid_list [ i ] [ j ].zombie_list.empty() ) continue;
			for ( list<Zombie*>::iterator k =
				grid_list [ i ] [ j ].zombie_list.begin(); k !=
				grid_list [ i ] [ j ].zombie_list.end();k++ ){
				Zombie* now = *k;
				if ( now->type == back_up ) continue;
				now->action( game );
			}
		}
	}
	for ( int i = 0; i < whole_length; i++ ){
		for ( int j = 0; j < whole_width; j++ ){
			if ( grid_list[i][j].zombie_list.empty() ) continue;
			for ( list<Zombie*>::iterator k =
				grid_list[i][j].zombie_list.begin(); k !=
				grid_list[i][j].zombie_list.end(); ){
				Zombie* now = *k;
				if ( now->x != i ){
					if ( now->x < 0 ) game.game_over();
					else{
						grid_list[now->x][j].zombie_list.push_back( *k );
						grid_list[now->x][j].in_refresh = 1;
						grid_list[i][j].zombie_list.erase( k++ );
						grid_list[i][j].in_refresh = 1;
					}
				}
				else if ( now->y != j ){
					grid_list[i][now->y].zombie_list.push_back( *k );
					grid_list[i][now->y].in_refresh = 1;
					grid_list[i][j].zombie_list.erase( k++ );
					grid_list[i][j].in_refresh = 1;
				}
				else k++;
			}
		}
	}
}