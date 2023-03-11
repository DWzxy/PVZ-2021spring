#pragma once
#include<QMovie>
#include<QWidget>
#include<QIcon>
#include<QMovie>
#include<QObject>
#include<QTimer>
#include<QCursor>
#include<QPixmap>
#include<QPainter>
#include<QRect>
#include<QFont>
#include<QRect>
#include<QPalette>
#include<QGraphicsOpacityEffect>
#include<QMouseEvent>
#include<QPushButton>
#include<QSound>
#include<QColor>
#include<QMediaPlayer>
#include<QMediaPlaylist>
#include"object.h"
using namespace std;

//单个草块大小
const int single_length = 162;
const int single_width = 194;
//草块行列数
const int whole_length = 9;
const int whole_width = 5;
//草坪位置
const int grass_top = 168;
const int grass_left = 500;
const int grass_bottom = grass_top + single_width  * whole_width;
const int grass_right = grass_left +  single_length  * whole_length;

//植物栏长度
const int plant_length = 1150;
//植物栏宽度
const int plant_width = 160;
//植物卡长度
const int card_length = 90;
//植物卡宽度
const int card_width = 126;
//植物卡之间的间隔
const int card_gap = 10;
//传送带长度
const int belt_length = (card_length + card_gap) * 11;

int get_x_num(int x);
int get_y_num(int y);//获取当前草块

enum Plant_type {shovel, leave, back, menu, rubbish,
                 peashooter, sunflower, cherry_bomb, wall_nut, potato_mine, snow_pea,
                 chomper, repeater, squash, threepeater, jalapeno, torchwood,
                 tall_nut, pumpkin,
                 spikeweed, garlic
                };
enum Zombie_type {
    ordinary, flag, conehead, pole_vaulting, bucket, newspaper, screen_door,
    dancing, back_up, jack_in_the_box, catapult
};
enum Bullet_type { pea, snow, fire };
enum Grid_state { shop, plant, wipe };
enum Lawn_type {day, night};
enum Lawn_state {normal, pause, lose, over};
