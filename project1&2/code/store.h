#pragma once
using namespace std;
#include"plant.h"
class Game;
//植物种类
class Store {
	friend class Game;
	friend class Plant;
	friend class Grid;
	friend class Peashooter;
	friend class Sunflower;
private:
	int page;//当前在第几页
	int sun_cooling;//目前生产单个阳光进度
	int sun_circle;//生产阳光的间隔
	int sun;//阳光总数
	int sun_flash;//阳光闪烁阶段
	int chat_circle;//提示信息显示时长
	int chat_cooling;//提示信息已显示时长
	int now_chat;//当前提示编号
	Plant plant_list [ 3 ] [ 8 ];//可购买的植物
	Plant_type now_plant;//当前要种植的植物
	int score;//分数
	bool score_refresh;//分数是否更新
	char* chat [ 101 ];
public:
	//初始化
	Store();
	//画框
	void print_frame();
	//打印植物栏
	void print_all_plant();
	//翻页
	void turn_page( int page );
	//打印单个植物
	void print_plant( int x , int y , int k,int page );
	//打印阳光
	void print_sun( int x );
	//打印分数
	void print_score();
	//打印铲子
	void print_shovel();
	//打印帮助信息
	void print_help();
	//植物冷却
	void refresh( Game& game );
	//设置提示信息
	void set_chat( int x );
	//更新提示信息
	void chat_refresh();
	//打印提示信息
	void print_chat( int x );
};