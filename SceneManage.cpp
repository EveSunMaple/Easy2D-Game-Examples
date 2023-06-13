//================================
//源码作者：EveSunMaple
//BiliBili：https://space.bilibili.com/438392347
//CSDN：https://blog.csdn.net/qq_50604688
//未经允许禁止转载此文件
//================================

#include "Total.h"
#include "SceneManage.h"
#include <iostream>
#include <vector>
#include <queue>
#include <math.h>
#include <easy2d/easy2d.h>

using namespace easy2d;
using namespace std;

void MapBlock::SetMapBlock(int x, int y)
{
    MapBlock_x = x;
    MapBlock_y = y;
}
void MapBlock::SetHealth(float he)
{
    health = he;
}
void MapBlock::SetCollisionBox(int x, int y)
{
    Collision_x = x;
    Collision_y = y;
}
void MapBlock::SetElastic(float el)
{
    elastic = el;
}
void MapBlock::SetColor(Color color)
{
    Base_color = color;
}
void MapBlock::InitMapBlock()
{
    mapBlock->setWidth(Collision_x);
    mapBlock->setHeight(Collision_y);

    DrawingStyle style;
    style.mode = DrawingStyle::Mode::Solid; // 绘图模式为填充
    style.fillColor = Base_color;           // 填充色

    mapBlock = ShapeNode::createRect(Size(Collision_x, Collision_y));
    mapBlock->setDrawingStyle(style);
}
void MapBlock::Coordinates()
{
}



void MapText::SetText(class easy2d::Text* text)
{
    mapText = text;
}
void MapText::SetMapText(int x, int y)
{
    MapText_x = x;
    MapText_y = y;
}
void MapText::SetRotation(float ro)
{
    rotation = ro;
}
void MapText::SetScale(float sc)
{
    scale = sc;
}
void MapText::SetOpacity(float op)
{
    opacity = op;
}
void MapText::SetColor(Color color)
{
    Base_color = color;
}
void MapText::SetLineSpacing(int li)
{
    lineSpacing = li;
}
void MapText::SetWidth(int wi)
{
    width = wi;
}
void MapText::SetUnderLine(bool li)
{
    underLine = li;
}
void MapText::SetStrikeThrough(bool li)
{
    strikeThrough = li;
}
void MapText::InitMapText()
{
    // 创建文字样式
    TextStyle style;
    style.alignment = TextAlign::Left;      // 左对齐
    style.wrapping = true;                  // 开启自动换行
    style.wrappingWidth = width;            // 文字自动换行的宽度
    style.lineSpacing = lineSpacing;        // 行间距
    style.hasUnderline = underLine;         // 下划线
    style.hasStrikethrough = strikeThrough; // 删除线

    mapText->setTextStyle(style);
    mapText->setRotation(rotation);
    mapText->setScale(scale);
    mapText->setOpacity(opacity);
}
void MapText::Coordinates()
{
}



void Player::SetPlayer(int x, int y)
{
    Player_x = x;
    Player_y = y;
}
void Player::SetHealth(float he)
{
    health = he;
}
void Player::SetCollisionBox(int x, int y)
{
    Collision_x = x;
    Collision_y = y;
}
void Player::SetSpeed(float speed)
{
    maxSpeed = speed;
}
void Player::SetAcceleration(float speed)
{
    acceleration = speed;
}
void Player::SetSpeedAngle(float speed)
{
    maxSpeed_angle = speed;
}
void Player::SetAccelerationAngle(float speed)
{
    acceleration_angle = speed;
}
void Player::SetFriction(float fr)
{
    friction = fr;
}
void Player::SetFrictionAngle(float fr)
{
    friction_angle = fr;
}
void Player::SetColor(Color color)
{
    Base_color = color;
}
void Player::CtrlPlayer(int lx, int ly, int rx, int ry)
{
    Ctrl_lx = lx;
    Ctrl_ly = ly;
    Ctrl_rx = rx;
    Ctrl_ry = ry;
}
void Player::InitPlayer()
{
    player->setWidth(Collision_x);
    player->setHeight(Collision_y);
    player->setAnchor(0.5f, 0.5f);

    DrawingStyle style;
    style.mode = DrawingStyle::Mode::Solid; // 绘图模式为填充
    style.fillColor = Base_color;           // 填充色

    player = ShapeNode::createRect(Size(Collision_x, Collision_y));
    player->setDrawingStyle(style);
}
void Player::Coordinates()
{
    double time = (double)Time::getDeltaTime();
    //cout << time << endl;
    // 获取鼠标位置
    if (Mouse_Control)
    {
        float mouse_x = Input::getMouseX();
        float mouse_y = Input::getMouseY();
        float x = mouse_x - Player_winx;
        float y = Player_winy - mouse_y;
        float change = sqrt(x * x + y * y);
        x /= change; y /= change;
        float angle = acos(y);
        if (x < 0) angle = -angle;
        Traget_angle = angle / acos(-1) * 180;
        Change_angle = Traget_angle - Player_angle;
        if (Change_angle < -180)
        {
            Change_angle += 360;
            Player_angle -= 360;
        }
        if (Change_angle > 180)
        {
            Change_angle -= 360;
            Player_angle += 360;
        }

        float h = Speed_angle / (friction_angle * time);
        if (abs(Speed_angle * h) < abs(Change_angle))
        {
            if (Change_angle > 0) Speed_angle += acceleration_angle * time;
            if (Change_angle < 0) Speed_angle -= acceleration_angle * time;
        }
    }
    else
    {
        if (Input::isDown(KeyCode::D))
        {
            Speed_angle += acceleration_angle * time;
        }
        if (Input::isDown(KeyCode::A))
        {
            Speed_angle -= acceleration_angle * time;
        }
    }
    double limX = maxSpeed, limY = maxSpeed;
    double Angle = Player_angle * acos(-1) / 180;
    if (Input::isDown(KeyCode::W))
    {
        //limX = abs(sin(Angle) * maxSpeed);
        //limY = abs(cos(Angle) * maxSpeed);
        Speed_y += cos(Angle) * acceleration * time;
        Speed_x += sin(Angle) * acceleration * time;
    }
    if (Input::isDown(KeyCode::D))
    {
        //limX = abs(cos(Angle) * maxSpeed);
        //limY = abs(sin(Angle) * maxSpeed);
        Speed_y -= sin(Angle) * acceleration * time;
        Speed_x += cos(Angle) * acceleration * time;
    }
    if (Input::isDown(KeyCode::S))
    {
        //limX = abs(sin(Angle) * maxSpeed);
        //limY = abs(cos(Angle) * maxSpeed);
        Speed_y -= cos(Angle) * acceleration * time;
        Speed_x -= sin(Angle) * acceleration * time;
    }
    if (Input::isDown(KeyCode::A))
    {
        //limX = abs(cos(Angle) * maxSpeed);
        //limY = abs(sin(Angle) * maxSpeed);
        Speed_y += sin(Angle) * acceleration * time;
        Speed_x -= cos(Angle) * acceleration * time;
    }

    //cout << "X:" << Speed_x << "Y:" << Speed_y << endl;

    if (abs(Speed_x) < abs(sin(Angle) * friction * time)) Speed_x = 0;
    else
    {
        if (Speed_x < 0) Speed_x += abs(sin(Angle) * friction * time);
        if (Speed_x > 0) Speed_x -= abs(sin(Angle) * friction * time);
    }
    if (abs(Speed_y) < abs(cos(Angle) * friction * time)) Speed_y = 0;
    else
    {
        if (Speed_y < 0) Speed_y += abs(cos(Angle) * friction * time);
        if (Speed_y > 0) Speed_y -= abs(cos(Angle) * friction * time);
    }

    if (Speed_angle < 0) Speed_angle += friction_angle * time;
    if (Speed_angle > 0) Speed_angle -= friction_angle * time;
    if (abs(Speed_angle) <= friction_angle * time) Speed_angle = 0;

    if (abs(Speed_x) > limX)
    {
        if (Speed_x < 0) Speed_x = -limX;
        if (Speed_x > 0) Speed_x = limX;
    }
    if (abs(Speed_y) > limY)
    {
        if (Speed_y < 0) Speed_y = -limY;
        if (Speed_y > 0) Speed_y = limY;
    }

    if (abs(Speed_angle) > maxSpeed_angle)
    {
        if (Speed_angle < 0) Speed_angle = -maxSpeed_angle;
        if (Speed_angle > 0) Speed_angle = maxSpeed_angle;
    }

    Speed = sqrt(Speed_x * Speed_x + Speed_y * Speed_y);
}
void Player::CheckCollision(MapBlock Map)
{
    float posX = Player_x + Collision_x;
    float posY = Player_y - Collision_y;
    float lx = Map.MapBlock_x;
    float ly = Map.MapBlock_y;
    float rx = lx + Map.Collision_x;
    float ry = ly - Map.Collision_y;
    if ((Player_y < ly + Collision_y) && (Player_y > ry))
    {
        if ((posX + Speed_x >= lx) && (posX <= lx))
        {
            Player_x = lx - Collision_x;
            Speed_x = -Speed_x * Map.elastic;
        }
        if ((Player_x + Speed_x <= rx) && (Player_x >= rx))
        {
            Player_x = rx;
            Speed_x = -Speed_x * Map.elastic;
        }
    }
    if ((Player_x < rx) && (Player_x > lx - Collision_x))
    {
        if ((posY + Speed_y <= ly) && (posY >= ly))
        {
            Player_y = ly + Collision_y;
            Speed_y = -Speed_y * Map.elastic;
        }
        if ((Player_y + Speed_y >= ry) && (Player_y <= ry))
        {
            Player_y = ry;
            Speed_y = -Speed_y * Map.elastic;
        }
    }
}
void Player::UseResults()
{
    Player_x += Speed_x;
    Player_y += Speed_y;
    Player_angle += Speed_angle;
}



void Weapon::SetRadius(int r)
{
    radius = r;
}
void Weapon::SetActionBullet(class easy2d::Spawn* sp)
{
    bullet_Action = sp;
}
void Weapon::SetActionWeapon(class easy2d::Spawn* sp)
{
    weapon_Action = sp;
}
void Weapon::SetSpriteBullet(easy2d::Sprite* sprite)
{
    bullet_Sprite = sprite;
}
void Weapon::SetSpriteWeapon(easy2d::Sprite* sprite)
{
    weapon_Sprite = sprite;
}
void Weapon::SetLifeTime(float time)
{
    LifeTime = time;
}
void Weapon::SetWeaponToPlayer(float x, float y, Player player)
{
    Base_Speed_x = player.Speed_x;
    Base_Speed_y = player.Speed_y;
    TureAngle = player.Player_angle + Angle;
    double angle = player.Player_angle * acos(-1) / 180;
    float change_x = 0, change_y = 0;
    change_y += cos(angle) * y;
    change_x += sin(angle) * y;
    change_y -= sin(angle) * x;
    change_x += cos(angle) * x;
    Weapon_x = player.Player_x + change_x;
    Weapon_y = player.Player_y + change_y;
}
void Weapon::InitWeapon(float speed, float angle, Color color)
{
    Speed = speed;
    Angle = angle;
    Base_color = color;

    DrawingStyle style;
    style.mode = DrawingStyle::Mode::Solid;          // 绘图模式为填充
    style.fillColor = Base_color;           // 填充色
    weapon_Node = ShapeNode::createCircle(radius, style);
    bullet_Node = ShapeNode::createCircle(radius, style);
}
void Weapon::Coordinates(easy2d::Sprite* sprite, Player player)
{
    float time = Time::getDeltaTime();
    NowTime += time;
    if (NowTime >= FireTime)
    {
        NowTime -= FireTime;
        Bullet bullet;

        DrawingStyle style;
        style.mode = DrawingStyle::Mode::Solid;          // 绘图模式为填充
        style.fillColor = Base_color;           // 填充色
        bullet.bullet_Node = ShapeNode::createCircle(1, style);
        bullet.bullet_Node->setAnchor(0.5f, 0.5f);
        auto bullet_sp = gcnew Sprite;
        bullet_sp->open("PNG/Lasers/laserBlue01.png"); // 从本地图片加载
        bullet.bullet_Sprite = bullet_sp;
        bullet.bullet_Sprite->setAnchor(0.5f, 0.5f);

        bullet.Angle = TureAngle;
        bullet.Bullet_x = Weapon_x;
        bullet.Bullet_y = Weapon_y;
        //bullet.bullet_Node = bullet_Node;
        //bullet.bullet_Sprite = bullet_Sprite;
        bullet.Base_color = Base_color;
        float angle = bullet.Angle * acos(-1) / 180;
        bullet.Speed_x = sin(angle) * Speed * time + Base_Speed_x;
        bullet.Speed_y = cos(angle) * Speed * time + Base_Speed_y;

        //cout << time << endl;
        if (bullet_Sprite != NULL)
        {
            bullet.bullet_Node->addChild(bullet.bullet_Sprite);
            bullet.bullet_Sprite->setAnchor(0.5f, 0.5f);
        }
        sprite->addChild(bullet.bullet_Node);
        bullet_list.push_back(bullet);
        Timer::add([=]()
            {
                sprite->removeChild(bullet.bullet_Node);
                bullet_list.pop_front();
            }, LifeTime, 1);
    }
}



void Particle::SetAction(class easy2d::Spawn* sp)
{
    action = sp;
}
void Particle::SetRadius(int r)
{
    radius = r;
}
void Particle::SetFollow(bool f)
{
    Follow = f;
}
void Particle::SetSprite(easy2d::Sprite* sprite)
{
    particle_Sprite = sprite;
}
void Particle::SetLifeTime(float time)
{
    LifeTime = time;
}
void Particle::SetParticleToPlayer(float x, float y, Player player)
{
    Base_Speed_x = player.Speed_x;
    Base_Speed_y = player.Speed_y;
    TureAngle = player.Player_angle + Angle;
    double angle = player.Player_angle * acos(-1) / 180;
    float change_x = 0, change_y = 0;
    change_y += cos(angle) * y;
    change_x += sin(angle) * y;
    change_y -= sin(angle) * x;
    change_x += cos(angle) * x;
    Particle_x = player.Player_x + change_x;
    Particle_y = player.Player_y + change_y;
}
void Particle::InitParticle(float speed, float angle, Color color)
{
    Speed = speed;
    Angle = angle;
    Base_color = color;
}
