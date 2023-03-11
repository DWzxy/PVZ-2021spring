#include"lawn.h"
#include"zombie.h"
#include<iostream>
using namespace std;
//初始化
Zombie::Zombie(QWidget* parent): Object(parent)
{
    slowing = 0;
    garlicing = 0;
    lawn = (Lawn*)parent;
    attacking = -1;
    if_slowed = 0;
    setAttribute(Qt::WA_TransparentForMouseEvents, true);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);//鼠标穿透
}
//判断僵尸是否能攻击植物
bool Zombie::can_attack()
{
    int x = get_x();
    int y = get_y();
    if (x >= whole_length) return false;
    if (lawn->plant[x][y] == NULL && lawn->pumpkin[x][y] == NULL) return false;
    int p = rx - x * single_length + width() / 2 - grass_left;
    if (p > single_length - 30 || p < 50) return false;
    return true;
}
//僵尸攻击
void Zombie::hit()
{
    int x = get_x(), y = get_y();
    Plant* now = lawn->plant[x][y];
    if (lawn->pumpkin[x][y] != NULL) now = lawn->pumpkin[x][y];
    now->minus(attack);
    if (attacking == 20) QSound::play(":/music/eat.wav");
    attacking--;
    if (attacking == 0) attacking = 20;
    if (now->type == Plant_type::garlic) garlicing = 17;
}
//僵尸前进
void Zombie::go()
{
    if (rx + width()  <= grass_left) {
        lawn->over();
        return;
    }
    rx -= speed;
    move(rx, ry);
}
void Zombie::die()
{
    Special* now = new Special(30, lawn);
    now->setMovie(new QMovie(":/zombie/zombiedie.gif"));
    rx += width() / 2;
    now->resize(332, 288);
    now->movie()->setSpeed(90);
    rx -= width()  ;
    now->move(rx, ry);
    now->movie()->start();
    now->show();
    lawn->special_list.push_back(now);

    now = new Special(30, lawn);
    now->setMovie(new QMovie(":/zombie/zombiehead.gif"));
    now->movie()->setSpeed(60);
    now->resize(300, 372);
    now->move(rx + width() / 2 - now->width() / 2, ry);
    now->movie()->start();
    now->show();
    lawn->special_list.push_back(now);
}
void Zombie::minus(int x)
{
    defence -= x;
    if (defence <= 0) alive = 0;
}
//冰冻状态
void Zombie::slow()
{
    if (slowing) {
        slowing--;
        if (slowing == 500) {
            if (if_slowed == 1) return;
            if_slowed = 1;
            speed /= 2;
            attack /= 2;
            if (type == dancing) {
                ((Dancing*) this)->make_time *= 2;
                ((Dancing*) this)->make_cooling *= 2;
            }
        }
        if (slowing == 0) {
            if_slowed = 0;
            speed *= 2;
            attack *= 2;
            if (type == dancing) {
                ((Dancing*) this)->make_time /= 2;
                ((Dancing*) this)->make_cooling /= 2;
            }
        }
    }
}
//被毒状态
void Zombie::garlic(Game& game)
{
    /*   if (garlicing) {
           garlicing--;
           if (garlicing == 10) {
               if (y == 0) y++;
               else if (y == whole_width - 1) y--;
               else {
                   int cnt = rand() % 2;
                   if (cnt) y++;
                   else y--;
               }
           }
           if (garlicing == 2) {
               game.lawn.grid_list[x][y].in_refresh = 1;
           }
       }*/
}
//被炸
void Zombie::boom()
{
    Special* cnt = new Special(1, lawn);
    cnt->setMovie(new QMovie(":/zombie/burndie.gif"));
    rx += width() / 2, ry += height() / 2;
    cnt->resize(212, 252);
    rx -= cnt->width() / 2, ry -= cnt->height() / 2;
    cnt->move(rx, ry);
    cnt->movie()->start();
    cnt->show();
    lawn->special_list.push_back(cnt);
}
Zombie::~Zombie()
{
    delete movie();
}
Ordinary::Ordinary(QWidget* parent): Zombie(parent)
{
    type = ordinary;
    attack = 2;
    defence = 200;
    speed = 0.7;

    resize(200, 252);
    background = new QMovie(":/zombie/zombie.gif");
    setMovie(background);
    setScaledContents(true);
    movie()->start();
    show();
    raise();
}
Flag::Flag(QWidget* parent): Zombie(parent)
{
    type = flag;
    attack = 2;
    defence = 200;
    speed = 0.8;

    resize(248, 288);
    background = new QMovie(":/zombie/flag.gif");
    setMovie(background);
    setScaledContents(true);
    movie()->start();
    show();
    raise();
}
Conehead::Conehead(QWidget* parent): Zombie(parent)
{
    type = conehead;
    attack = 2;
    defence = 570;
    speed = 0.7;
    have_cone = 1;

    resize(208, 288);
    background = new QMovie(":/zombie/cone.gif");
    setMovie(background);
    setScaledContents(true);
    movie()->start();
    show();
    raise();
}
Pole_vaulting::Pole_vaulting(QWidget* parent): Zombie(parent)
{
    type = pole_vaulting;
    attack = 2;
    defence = 500;
    speed = 1.3;
    speed2 = 0.7;
    has_jump = 0;
    jump_time = 0;

    resize(550, 330);
    move(rx, ry - 80);
    background = new QMovie(":/zombie/polezombie.gif");
    setMovie(background);
    setScaledContents(true);
    movie()->start();
    show();
    raise();
}
Bucket::Bucket(QWidget* parent): Zombie(parent)
{
    type = bucket;
    attack = 2;
    defence = 1370;
    speed = 0.7;
    have_bucket = 1;

    resize(220, 317);
    move(rx, ry - 15);
    background = new QMovie(":/zombie/bucket.gif");
    setMovie(background);
    setScaledContents(true);
    movie()->start();
    show();
    raise();
}
Newspaper::Newspaper(QWidget* parent): Zombie(parent)
{
    type = newspaper;
    attack = 2;
    defence = 420;
    speed = 0.7;
    speed2 = 1.8;
    angry = 0;
    angry_time = -1;

    resize(428, 325);
    background = new QMovie(":/zombie/newswalk_1.gif");
    setMovie(background);
    setScaledContents(true);
    movie()->start();
    show();
    raise();
}
Screen_door::Screen_door(QWidget* parent): Zombie(parent)
{
    type = screen_door;
    attack = 2;
    defence = 1300;
    speed = 0.7;
    have_door = 1;

    resize(365, 317);
    background = new QMovie(":/zombie/screen_door_zombie.gif");
    setMovie(background);
    setScaledContents(true);
    movie()->start();
    show();
    raise();
}
Dancing::Dancing(QWidget* parent): Zombie(parent)
{
    type = dancing;
    attack = 2;
    defence = 500;
    speed = 12;

    first_time = 25;
    flash_time = 11;
    state = 0;
    make_cooling = 0;
    make_time = 25;
    flag = 0;
    left = right = top = bottom = NULL;
}
Back_up::Back_up(): Zombie()
{
    type = back_up;
    attack = 2;
    defence = 200;
    speed = 55;
}
Jack_in_the_box::Jack_in_the_box(): Zombie()
{
    type = jack_in_the_box;
    attack = 2;
    defence = 367;
    speed = 33;

    int cnt = rand() % 20;
    if (cnt == 0) life_time = 45 + rand() % 34;
    else life_time = 133 + rand() % 98;
    bomb_time = 11;
}
Catapult::Catapult()
{
    type = catapult;
    attack = 4;
    defence = 850;
    speed = 25;

    ball_num = 20;
    throw_time = 40;
    throw_cooling = 0;
}
//普通僵尸行动
void Ordinary::action()
{
    slow();
    if (can_attack()) {
        if (attacking == -1) {
            attacking = 20;
            delete movie();
            setMovie(new QMovie(":/zombie/zombieattack.gif"));
            movie()->start();
        }
        hit();
    } else {
        go();
        if (attacking >= 0) {
            attacking = -1;
            delete movie();
            setMovie(new QMovie(":/zombie/zombie.gif"));
            movie()->start();
        }
    }
}
//摇旗僵尸行动
void Flag::action()
{
    slow();
    if (can_attack()) {
        if (attacking == -1) {
            attacking = 20;
            delete movie();
            setMovie(new QMovie(":/zombie/flagattack.gif"));
            movie()->start();
        }
        hit();
    } else {
        go();
        if (attacking >= 0) {
            attacking = -1;
            delete movie();
            setMovie(new QMovie(":/zombie/flag.gif"));
            movie()->start();
        }
    }
}
//路障僵尸行动
void Conehead::action()
{
    slow();
    if (have_cone && defence <= 200) {
        have_cone = 0;
        delete movie();
        resize(200, 252);
        rx += 4;
        ry += 34;
        move(rx, ry);
        setMovie(new QMovie(":/zombie/zombie.gif"));
        movie()->start();
        type = ordinary;
        attacking = -1;
    }
    if (can_attack()) {
        if (attacking == -1) {
            attacking = 20;
            delete movie();
            if (have_cone)setMovie(new QMovie(":/zombie/coneattack.gif"));
            else setMovie(new QMovie(":/zombie/zombieattack.gif"));
            movie()->start();
        }
        hit();
    } else {
        go();
        if (attacking >= 0) {
            attacking = -1;
            delete movie();
            if (have_cone)setMovie(new QMovie(":/zombie/cone.gif"));
            else setMovie(new QMovie(":/zombie/zombie.gif"));
            movie()->start();
        }
    }
}
////撑杆僵尸行动
void Pole_vaulting::action()
{
    slow();
    if (jump_time) {
        jump_time--;
        if (jump_time == 30) {
            if (target->type == tall_nut) {
                jump_time = 0;
                rx += 200;
            } else {
                delete movie();
                move(rx, ry - 70);
                resize(352, 404);
                setMovie(new QMovie(":/zombie/polezombiejump2.gif"));
                movie()->start();
            }
        }
        if (jump_time == 0) {
            has_jump = 1;
            delete movie();
            type = ordinary;
            resize(218, 320);
            move(rx, ry);
            setMovie(new QMovie(":/zombie/polezombiewalk.gif"));
            movie()->start();
            speed = speed2;
        }
        return;
    }
    if (has_jump == 1) {
        if (can_attack()) {
            if (attacking == -1) {
                attacking = 20;
                delete movie();
                setMovie(new QMovie(":/zombie/polezombieattack.gif"));
                movie()->start();
            }
            hit();
        } else {
            go();
            if (attacking >= 0) {
                attacking = -1;
                delete movie();
                setMovie(new QMovie(":/zombie/polezombiewalk.gif"));
                movie()->start();
            }
        }
    } else {
        if (can_jump()) jump();
        else go();
    }
}
void Pole_vaulting::jump()
{
    jump_time = 50;
    delete movie();
    resize(770, 458);
    move(rx - width() / 4, ry - 120);
    rx -= width() / 4;
    setMovie(new QMovie(":/zombie/polezombiejump.gif"));
    QSound::play(":/music/jump.wav");
    movie()->start();
}
bool Pole_vaulting::can_jump()
{
    int x = (rx + width() / 4 - grass_left) / single_length;
    int y = (ry + height() / 2 - grass_top) / single_width;

    int p = (rx + width() * 2 / 3 - grass_left) / single_length;

    if (x >= whole_length || x < 0) x = p;
    if (x >= whole_length || x < 0) return false;

    if (lawn->plant[x][y] == NULL && lawn->pumpkin[x][y] == NULL) return false;
    target = lawn->plant[x][y];
    if (target == NULL) target = lawn->pumpkin[x][y];

    return true;
}
void Pole_vaulting::die()
{
    Special* now = new Special(30, lawn);
    now->setMovie(new QMovie(":/zombie/polezombiedie.gif"));
    rx += width() / 2;
    now->resize(380, 332);
    now->movie()->setSpeed(70);
    rx -= width() / 2;
    now->move(rx, ry);
    now->movie()->start();
    now->show();
    lawn->special_list.push_back(now);

    now = new Special(30, lawn);
    now->setMovie(new QMovie(":/zombie/polezombiehead.gif"));
    now->resize(270, 468);
    now->move(rx + width() / 2  - now->width() / 2, pos().y());
    now->movie()->setSpeed(100);
    now->movie()->start();
    now->show();
    lawn->special_list.push_back(now);
}
//铁桶僵尸行动
void Bucket::action()
{
    slow();
    if (have_bucket && defence <= 200) {
        have_bucket = 0;
        delete movie();
        resize(200, 252);
        rx += 10;
        ry += 60;
        move(rx, ry);
        setMovie(new QMovie(":/zombie/zombie.gif"));
        movie()->start();
        type = ordinary;
        attacking = -1;
    }
    if (can_attack()) {
        if (attacking == -1) {
            attacking = 20;
            delete movie();
            if (have_bucket)setMovie(new QMovie(":/zombie/bucketattack.gif"));
            else setMovie(new QMovie(":/zombie/zombieattack.gif"));
            movie()->start();
        }
        hit();
    } else {
        go();
        if (attacking >= 0) {
            attacking = -1;
            delete movie();
            if (have_bucket)setMovie(new QMovie(":/zombie/bucket.gif"));
            else setMovie(new QMovie(":/zombie/zombie.gif"));
            movie()->start();
        }
    }
}
//读报僵尸行动
void Newspaper::action()
{
    slow();
    if (angry_time > 0) {
        angry_time--;
        if (angry_time == 0) {
            QSound::play(":/music/newspaper_lost.wav");
            speed = speed2;
            if (slowing) speed /= 2;
            delete movie();
            setMovie(new QMovie(":/zombie/newswalk.gif"));
            movie()->start();
            attacking = -1;
        }
        return;
    }

    if (angry == 0 && defence <= 270) {
        delete movie();
        setMovie(new QMovie(":/zombie/newslost.gif"));
        movie()->start();
        angry_time = 40;
        angry = 1;
    } else {
        if (can_attack()) {
            if (attacking == -1) {
                attacking = 20;
                delete movie();
                if (angry == 0)setMovie(new QMovie(":/zombie/newspaper_attack2.gif"));
                else setMovie(new QMovie(":/zombie/newspaper_attack.gif"));
                movie()->start();
            }
            hit();
        } else {
            if (attacking >= 0) {
                attacking = -1;
                delete movie();
                if (angry == 0) setMovie(new QMovie(":/zombie/newswalk_1.gif"));
                else  setMovie(new QMovie(":/zombie/newswalk.gif"));
                movie()->start();
            }
            go();
        }
    }
}
void Newspaper::die()
{
    Special* now = new Special(30, lawn);
    now->setMovie(new QMovie(":/zombie/newsdie.gif"));
    rx += width() / 2;
    now->resize(432, 328);
    now->movie()->setSpeed(70);
    rx -= width() / 2;
    now->move(rx, ry);
    now->movie()->start();
    now->show();
    lawn->special_list.push_back(now);

    now = new Special(30, lawn);
    now->setMovie(new QMovie(":/zombie/newshead.gif"));
    now->resize(308, 328);
    now->move(rx + width() / 2 - now->width() / 2, ry);
    now->movie()->setSpeed(100);
    now->movie()->start();
    now->show();
    lawn->special_list.push_back(now);
}
//铁栅门僵尸行动
void Screen_door::action()
{
    if (have_door) slowing = 0;
    slow();
    if (have_door && defence <= 200) {
        have_door = 0;
        attacking = -1;
        delete movie();
        resize(200, 252);
        move(rx + 70, ry + 50);
        rx += 70, ry += 50;
        setMovie(new QMovie(":/zombie/zombie.gif"));
        movie()->start();
        type = ordinary;
        attacking = -1;
    }
    if (can_attack()) {
        if (attacking == -1) {
            attacking = 20;
            delete movie();
            if (have_door) setMovie(new QMovie(":/zombie/screen_attack.gif"));
            else setMovie(new QMovie(":/zombie/zombieattack.gif"));
            movie()->start();
        }
        hit();
    } else {
        go();
        if (attacking >= 0) {
            attacking = -1;
            delete movie();
            if (have_door) setMovie(new QMovie(":/zombie/screen_door_zombie.gif"));
            else setMovie(new QMovie(":/zombie/zombie.gif"));
            movie()->start();
        }
    }
}
//舞王僵尸行动
void Dancing::action(Game& game)
{
    /*  if (defence < 0) return;
      flag = can_move(game);
      if (left != NULL) left->action(game);
      if (right != NULL) right->action(game);
      if (top != NULL) top->action(game);
      if (bottom != NULL) bottom->action(game);
      if (garlicing) garlic(game);
      else slow(game);
      if (zombie_can_attack(game) && !garlicing)hit(game);
      else if (flag) move(game);*/
    /*set_cursor( 0 , 4 );
    cout << speed_cooling << " " << speed << endl;
    if ( left != NULL )
        cout << left->speed_cooling << " " << left->speed << endl;
    if ( right != NULL )
        cout << right->speed_cooling << " " << right->speed << endl;
    if ( top != NULL )
        cout << top->speed_cooling << " " << top->speed << endl;
    if ( bottom != NULL )
        cout << bottom->speed_cooling << " " << bottom->speed << endl;*/
    /*  if (first_time) {
          first_time--;
          if (first_time == 0) {
              Grid* now = &game.lawn.grid_list[x][y];
              now->flashing = flash_time;
              speed = 55;
              if (slowing) speed = 110;
              add_back_up(game);
          }
      } else if (check(game)) {
          if (make_cooling == 0) make_cooling = make_time;
          make_cooling--;
          if (make_cooling == 0) {
              Grid* now = &game.lawn.grid_list[x][y];
              now->flashing = flash_time;
              add_back_up(game);
          }
      }*/
}
int Dancing::max_slowing()
{
    int now = slowing;
    if (left != NULL) now = max(now, left->slowing);
    if (right != NULL) now = max(now, right->slowing);
    if (top != NULL) now = max(now, top->slowing);
    if (bottom != NULL) now = max(now, bottom->slowing);
    return now;
}
bool Dancing::can_move(Game& game)
{
    /*   if (left != NULL && (left->zombie_can_attack(game) || left->garlicing)) return false;
       if (right != NULL && (right->zombie_can_attack(game) || right->garlicing)) return false;
       if (top != NULL && (top->zombie_can_attack(game) || top->garlicing)) return false;
       if (bottom != NULL && (bottom->zombie_can_attack(game) || bottom->garlicing)) return false;
       if (zombie_can_attack(game) || garlicing) return false;*/
    return true;
}
void Dancing::add_back_up(Game& game)
{
    /*   Back_up* now = NULL;
       if (x > 0 && left == NULL) {
           now = new Back_up();
           now->dancing = this;
           now->direction = 0;
           now->x = x - 1;
           now->y = y;
           left = now;
           game.lawn.grid_list[x - 1][y].zombie_list.push_back(now);
           game.lawn.grid_list[x - 1][y].in_refresh = 1;
           game.lawn.grid_list[x - 1][y].flashing = flash_time;
       }
       if (x < whole_length - 1 && right == NULL) {
           now = new Back_up();
           now->dancing = this;
           now->direction = 1;
           now->x = x + 1;
           now->y = y;
           right = now;
           game.lawn.grid_list[x + 1][y].zombie_list.push_back(now);
           game.lawn.grid_list[x + 1][y].in_refresh = 1;
           game.lawn.grid_list[x + 1][y].flashing = flash_time;
       }
       if (y > 0 && top == NULL) {
           now = new Back_up();
           now->dancing = this;
           now->direction = 2;
           now->x = x;
           now->y = y - 1;
           top = now;
           game.lawn.grid_list[x][y - 1].zombie_list.push_back(now);
           game.lawn.grid_list[x][y - 1].in_refresh = 1;
           game.lawn.grid_list[x][y - 1].flashing = flash_time;
       }
       if (y < whole_width - 1 && bottom == NULL) {
           now = new Back_up();
           now->dancing = this;
           now->direction = 3;
           now->x = x;
           now->y = y + 1;
           bottom = now;
           game.lawn.grid_list[x][y + 1].zombie_list.push_back(now);
           game.lawn.grid_list[x][y + 1].in_refresh = 1;
           game.lawn.grid_list[x][y + 1].flashing = flash_time;
       }*/
}
bool Dancing::check(Game& game)
{
    /*   if (x > 0 && left == NULL) return true;
       if (x < whole_length - 1 && right == NULL) return true;
       if (y > 0 && top == NULL) return true;
       if (y < whole_width - 1 && bottom == NULL) return true;
       return false;*/
}
//伴舞僵尸行动
void Back_up::action(Game& game)
{
    /*   if (defence < 0) return;
       speed = dancing->speed;
       speed_cooling = dancing->speed_cooling;
       //	slowing = dancing->slowing;
       if (garlicing) garlic(game);
       else slow(game);
       if (dancing->flag)move(game);    //只有舞王能移动才能行动
       else if (zombie_can_attack(game) && !garlicing) hit(game);*/
}
//小丑僵尸行动
void Jack_in_the_box::action(Game& game)
{
    /*   if (defence < 0) return;
       if (garlicing) garlic(game);
       else {
           //      move(game);
           slow(game);
       }
       life_time--;
       if (life_time != 0) return;
       game.lawn.grid_list[x][y].zombie_minus(this, defence, game);
       int row_up = max(y - 1, 0);
       int row_down = min(y + 1, whole_width - 1);
       int col_left = max(x - 1, 0);
       int col_right = min(x + 1, whole_length - 1);
       for (int i = col_left; i <= col_right; i++) {
           for (int j = row_up; j <= row_down; j++) {
               game.lawn.grid_list[i][j].bombing = bomb_time;
               Grid* now = &game.lawn.grid_list[i][j];
               if (now->plant != NULL)
                   now->plant_minus(now->plant, now->plant->defence);
               if (now->pumpkin != NULL)
                   now->plant_minus(now->pumpkin, now->pumpkin->defence);
           }
       }*/
}
//投石车僵尸行动
void Catapult::action(Game& game)
{
    /*  if (defence < 0) return;
      Grid* cnt = &game.lawn.grid_list[x][y];
      if (cnt->plant != NULL || cnt->pumpkin != NULL) {
          if (cnt->plant != NULL) {
              if (cnt->plant->type == spikeweed && cnt->pumpkin == NULL) {
                  cnt->zombie_minus(this, defence, game);
                  cnt->bombing = 11;
              }
              cnt->plant_minus(cnt->plant, cnt->plant->defence);
          }
          if (cnt->pumpkin != NULL)
              cnt->plant_minus(cnt->pumpkin, cnt->pumpkin->defence);
      }
      int now = can_attack(game);
      if (now != -1 && ball_num) {
          if (throw_cooling < throw_time) throw_cooling++;
          if (throw_cooling == throw_time) {
              throw_cooling = 0;
              ball_num--;
              Grid* cnt = &game.lawn.grid_list[now][y];
              if (cnt->plant != NULL) cnt->plant_minus(cnt->plant, attack);
              else cnt->plant_minus(cnt->pumpkin, attack);
          }
      } else {
          speed_cooling++;
          if (speed_cooling == speed) {
              speed_cooling = 0;
              if (x == 0) game.game_over();
              else x--;
          }
      }
      slow(game);*/
}
int Catapult::can_attack(Game& game)
{
    /*for (int i = 0; i <= x; i++) {
        Grid* cnt = &game.lawn.grid_list[i][y];
        if (cnt->plant != NULL || cnt->pumpkin != NULL) return i;
    }
    return -1;*/
}
