#pragma once
#include<string>
#include"overall.h"
using namespace std;
class Bullet {
	friend class Game;
	friend class Zombie;
protected:
	Bullet_type type;//�ӵ�����
	int color;//��ɫ
	int x;
	int y;//����λ��
	int attack;//������
	int speed;//�ٶ�
public:
	//��ʼ��
	Bullet( int x , int y );
};
class Pea_bullet:public Bullet{
public:
	Pea_bullet( int x , int y );
};
class Snow_bullet:public Bullet{
public:
	Snow_bullet( int x , int y );
};
class Fire_bullet:public Bullet{
public:
	Fire_bullet( int x , int y );
};
class Plant {
	friend class Bullet;
	friend class Store;
	friend class Game;
	friend class Grid;
	friend class Lawn;
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
protected:
	string name;//����
	Plant_type type;//����
	int color;//��ǰ��ɫ
	int origin_color;//ԭʼ��ɫ
	int high_light;//������ʱ����ɫ
	int blood;//������
	int defence;//��������ֵ
	int cost_sun;//�۸�
	int cooling;//��ǰ����ȴʱ��
	int cool_time;//��ȴʱ��
	int x;
	int y;//���λ��

	bool can_jump;//�ܷ�����
	int eating;//���Խ׶�
public:
	//��ʼ��
	Plant();
	virtual void action( Game& game );
	//�ж����ֹ�����Χ���Ƿ��н�ʬ
	bool shooter_can_attack( Lawn& lawn );
	//�Ƿ������
	bool can_be_jump();
	//���Ե���˸
	void shine(Lawn&lawn);
};
class Peashooter:public Plant{
	friend class Grid;
	friend class Lawn;
private:
	int attack_cooling;//��ǰ����ȴ�Ĺ���ʱ��
	int attack_time;//�������ʱ��
	//ʱ������λ��Ϊ0.1��
public:
	Peashooter();
	void action( Game& game );
};
class Sunflower:public Plant{
	friend class Grid;
	friend class Lawn;
private:
	int make_sun;//����������
	int start_sun_circle;//���տ���һ����������ʱ��
	bool if_start;//�Ƿ��ѽ��е�һ������
	int sun_circle;//����������
	int sun_cooling;//Ŀǰ������ȴʱ��
	int sun_shine_time;//��˸ʱ��
public:
	Sunflower();
	void action( Game& game );
	//��������ʱ����˸
	void sun_shine( Game& game );
};
class Cherry_bomb:public Plant{
	friend class Grid;
	friend class Lawn;
private:
	int life_time;//�����µ���ը��ʱ��
	int bomb_time;//��ը����ʱ��
	int attack;//������
public:
	Cherry_bomb();
	void action( Game& game );
};
class Wall_nut:public Plant{
	friend class Grid;
	friend class Lawn;
private:
public:
	Wall_nut();
	void action( Game& game );
};
class Potato_mine:public Plant{
	friend class Grid;
	friend class Lawn;
private:
	int rest_time;//׼��ʱ��
	int bomb_time;//��ըʱ��
	int attack;//������
public:
	Potato_mine();
	void action( Game& game );
};
class Snow_pea:public Plant{
	friend class Grid;
	friend class Lawn;
private:
	int attack_cooling;//��ǰ����ȴ�Ĺ���ʱ��
	int attack_time;//�������ʱ��
	//ʱ������λ��Ϊ0.1��
	int bullet_type;
	//�ӵ�����
public:
	Snow_pea();
	void action( Game& game );
};
class Chomper:public Plant{
	friend class Grid;
	friend class Lawn;
private:
	int rest_time;
	int attack;
public:
	Chomper();
	void action( Game& game );
};
class Repeater:public Plant{
	friend class Grid;
	friend class Lawn;
private:
	int attack_cooling;
	int first ;//��һ������һ�ŵ�ʱ��
	int second ;//�ڶ�������һ�ŵ�ʱ��
	int bullet_type;
public:
	Repeater();
	void action( Game& game );
};
class Squash:public Plant{
	friend class Grid;
	friend class Lawn;
private:
	int life_time;//�ӷ��ֽ�ʬ��������ʱ��
	int squash_time;//����Ч������ʱ��
	int attack;//������
public:
	Squash();
	void action( Game& game );
};
class Threepeater:public Plant{
private:
	int attack_cooling;
	int attack_time;
public:
	Threepeater();
	void action( Game& game );
	bool can_attack( Lawn& lawn );
};
class Jalapeno:public Plant{
private:
	int life_time;
	int bomb_time;
	int attack;
public:
	Jalapeno();
	void action( Game& game );
};
class Spikeweed:public Plant{
private:
	int attack;
	int attack_cooling;
	int attack_time;
public:
	Spikeweed();
	void action( Game& game );
};
class Torchwood:public Plant{
public:
	Torchwood();
	void action( Game& game );
};
class Tall_nut:public Plant{
	friend class Grid;
	friend class Lawn;
private:
public:
	Tall_nut();
	void action( Game& game );
};
class Pumpkin:public Plant{
	friend class Grid;
	friend class Lawn;
private:
public:
	Pumpkin();
	void action( Game& game );
};
class Garlic:public Plant{
	friend class Grid;
	friend class Lawn;
private:
public:
	Garlic();
	void action( Game& game );
};
