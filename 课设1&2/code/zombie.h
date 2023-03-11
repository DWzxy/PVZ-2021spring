#pragma once
#include<string>
using namespace std;
class Lawn;
class Back_up;
class Zombie {
	friend class Bullet;
	friend class Game;
	friend class Lawn;
	friend class Grid;
	friend class Cherry_bomb;
	friend class Wall_nut;
	friend class Snow_pea;
	friend class Squash;
	friend class Repeater;
	friend class Tall_nut;
	friend class Pumpkin;
	friend class Garlic;
	friend class Potato_mine;
	friend class Chomper;
	friend class Back_up;
protected:
	string name;//����
	Zombie_type type;
	int attack;//������
	int defence;//��ǰ����ֵ
	int blood;//������ֵ
	int speed;//�ٶȣ�ʵ����������һ����Ҫ��ʱ�䣩
	int speed_cooling;//��ǰ�н���һ��Ľ���
	int score;//���ܻ�õĵ÷�
	int x;
	int y;//���λ��
	int origin_color;//ԭ������ɫ
	int color;//��ǰ����ɫ

	bool if_slowed;//�Ƿ����ڼ���
	int slowing;//��ǰ���µļ���ʱ��
	int garlicing;//��ǰ���µı���ʱ��
	bool can_jump;//�ܷ�����ֲ��
public:
	//��ʼ��
	Zombie( );
	//��ʬ�ƶ�
	void move( Game& game );
	//��ʬ����
	void hit( Game& game );
	//�жϽ�ʬ�Ƿ��ܹ���ֲ��
	bool zombie_can_attack(Game&game);
	//��ʬ�ж�
	virtual void action( Game& game );
	//����״̬
	void slow(Game&game);
	//����״̬
	void garlic(Game&game);
};
class Ordinary:public Zombie{
public:
	Ordinary();
	void action( Game& game );
};
class Flag:public Zombie{
public:
	Flag();
	void action( Game& game );
};
class Conehead:public Zombie{
public:
	Conehead();
	void action( Game& game );
};
class Pole_vaulting:public Zombie{
private:
	string name2;
	int speed2;
public:
	Pole_vaulting();
	void action( Game& game );
	void jump( Game& game );
};
class Bucket:public Zombie{
public:
	Bucket();
	void action( Game& game );
};
class Newspaper:public Zombie{
private:
	string name2;
	int speed2;
	bool angry;//�Ƿ��ѷ���
public:
	Newspaper();
	void action( Game& game );
};
class Dancing:public Zombie{
	friend class Grid;
	friend class Back_up;
	friend class Game;
	friend class Zombie;
private:
	int first_time;//������һ���ٻ�����ʱ��
	int flash_time;//�ٻ��ĵƹ�ʱ��
	int state;//����׶�
	int make_cooling;//����ȴ���ٻ�ʱ��
	int make_time;//�ٻ�����ʱ��
	int flag;//�ܷ��ƶ�
	Back_up* left;
	Back_up* right;
	Back_up* top;
	Back_up* bottom;//��ֻ���轩ʬ
public:
	Dancing();
	void action( Game& game );
	//������ֵ
	int max_slowing();
	//�ж��Ƿ���ƶ�
	bool can_move( Game& game );
	//��Ӱ��轩ʬ
	void add_back_up( Game& game );
	//�����轩ʬ�Ƿ�ȱ��
	bool check( Game& game );
};
class Back_up:public Zombie{
	friend class Dancing;
	friend class Grid;
	friend class Game;
	friend class Lawn;
	friend class Zombie;
private:
	Dancing* dancing;
	int direction;//��λ
public:
	Back_up();
	void action( Game& game );
};
class Jack_in_the_box:public Zombie{
private:
	int life_time;//���ʱ��
	int bomb_time;//��ը����ʱ��

public:
	Jack_in_the_box();
	void action( Game& game );
};
class Catapult:public Zombie{
private:
	int ball_num;//��������
	int throw_time;//Ͷ����ʱ����
	int throw_cooling;
public:
	Catapult();
	void action( Game& game );
	int can_attack( Game& game );
};