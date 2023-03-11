#pragma once
#include"plant.h"
#include"zombie.h"
#include"overall.h"
#include<list>
using namespace std;
class Grid {
	friend class Game;
	friend class Lawn;
	friend class Plant;
	friend class Store;
	friend class Peashooter;
	friend class Sunflower;
	friend class Cherry_bomb;
	friend class Wall_nut;
	friend class Snow_pea;
	friend class Squash;
	friend class Repeater;
	friend class Tall_nut;
	friend class Pumpkin;
	friend class Garlic;
	friend class Spikeweed;
	friend class Jalapeno;
	friend class Potato_mine;
	friend class Chomper;
	friend class Zombie;
	friend class Ordinary;
	friend class Flag;
	friend class Conehead;
	friend class Pole_vaulting;
	friend class Bucket;
	friend class Newspaper;
	friend class Dancing;
	friend class Back_up;
	friend class Jack_in_the_box;
	friend class Catapult;
private:
	int x;
	int y;//绝对位置
	int sta_x;
	int sta_y;//相对位置
	Plant* plant;//该格子上的植物
	Pumpkin* pumpkin;//该格子上的南瓜头
	list<Zombie*>zombie_list;//该格子上的僵尸
	bool in_refresh;//内部是否需要重新绘制
	bool out_refresh;//外部是否需要重新绘制
	int color;//当前颜色（受游戏状态及光标位置影响）

	int bombing;//爆炸时间段
	int squashing;//窝瓜时间段
	int flashing;//舞王灯光时间段
public:
	//初始化
	void init( int x , int y );
	//添加植物
	void add_plant( Plant* x);
	//清空内部
	void clear();
	//打印植物，僵尸
	void print( Game& game );
	//打印生命值
	void print_defence( int x , int y , int z,int w);
	//打印名称
	void print_name( string x , int y,int z , int w );
	//植物行动
	void plant_action( Game& game );
	//僵尸减血
	void zombie_minus( Zombie* zombie, int x , Game& game );
	//植物减血
	void plant_minus( Plant*plant,int x );
	//打印边框
	void print_circle(Game&game);
	//更新
	void refresh(Game&game);
	//清除死亡的僵尸
	void clear_zombie();
};
class Lawn {
	friend class Game;
	friend class Plant;
	friend class Grid;
	friend class Peashooter;
	friend class Sunflower;
	friend class Cherry_bomb;
	friend class Wall_nut;
	friend class Snow_pea;
	friend class Squash;
	friend class Repeater;
	friend class Jalapeno;
	friend class Tall_nut;
	friend class Pumpkin;
	friend class Garlic;
	friend class Spikeweed;
	friend class Potato_mine;
	friend class Chomper;
	friend class Zombie;
	friend class Ordinary;
	friend class Flag;
	friend class Conehead;
	friend class Pole_vaulting;
	friend class Bucket;
	friend class Newspaper;
	friend class Dancing;
	friend class Back_up;
	friend class Jack_in_the_box;
	friend class Catapult;
private:
	int zombie_cooling;//生产单个僵尸的进度
	int zombie_circle [ 21 ] [ 2 ];//僵尸产生的时间间隔与数目
	int whole_wave;//完整的一轮包含的时间间隔数目
	Grid grid_list [ whole_length ] [ whole_width ];
	bool flag;//是否已出现摇旗僵尸
public:
	Lawn();
	//更新
	void refresh( Game& game );
	//产生僵尸
	void make_zombie(Game&game);
	//僵尸行动
	void zombie_action( Game& game );
};