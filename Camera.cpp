//================================
//源码作者：EveSunMaple
//BiliBili：https://space.bilibili.com/438392347
//CSDN：https://blog.csdn.net/qq_50604688
//未经允许禁止转载此文件
//================================
#include "Camera.h"
#include <easy2d/easy2d.h>
#include <vector>
#include <queue>
#include <iostream>
using namespace easy2d;
using namespace std;

void Camera::SetCamera(int x, int y)
{
    Camera_x = x;
    Camera_y = y;
}
void Camera::SetSpeed(float speed)
{
    maxSpeed = speed;
}
void Camera::SetCenter(int x, int y)
{
    Center_x = x;
    Center_y = y;
}
void Camera::SetRange(int lx, int ly, int rx, int ry)
{
    Response_lx = lx;
    Response_ly = ly;
    Response_rx = rx;
    Response_ry = ry;
}
void Camera::CtrlCamera(int lx, int ly, int rx, int ry)
{
    Ctrl_lx = lx;
    Ctrl_ly = ly;
    Ctrl_rx = rx;
    Ctrl_ry = ry;
}
void Camera::SetTarget(Player player)
{
    float posX = player.Player_x;
    float posY = player.Player_y;
    float Width = player.Collision_x;
    float Height = player.Collision_y;
    float lx = Camera_x + Center_x - Response_lx;
    float ly = Camera_y - Center_y + Response_ly;
    float rx = Camera_x + Center_x + Response_rx;
    float ry = Camera_y - Center_y - Response_ry;

    if (posX < lx)
    {
        Camera_x = posX - Center_x + Response_lx;
    }
    if (posY > ly)
    {
        Camera_y = posY + Center_y - Response_ly;
    }
    if (posX + Width > rx)
    {
        Camera_x = posX + Width - Center_x - Response_lx;
    }
    if (posY - Height < ry)
    {
        Camera_y = posY - Height + Center_y + Response_ly;
    }

    if (Ctrl_lx != 0 || Ctrl_ly != 0 || Ctrl_rx != 0 || Ctrl_ry != 0)
    {
        if (Camera_x + Speed_x < Ctrl_lx)
        {
            Camera_x = Ctrl_lx;
            Speed_x = 0;
        }
        if (Camera_x + Camera_width + Speed_x > Ctrl_rx)
        {
            Camera_x = Ctrl_rx - Camera_width;
            Speed_x = 0;
        }
        if (Camera_y + Speed_y > Ctrl_ly)
        {
            Camera_y = Ctrl_ly;
            Speed_y = 0;
        }
        if (Camera_y - Camera_height + Speed_y < Ctrl_ry)
        {
            Camera_y = Ctrl_ry + Camera_height;
            Speed_y = 0;
        }
    }
}
void Camera::ProjectPlayer(Player& player)
{
    player.Player_winx = player.Player_x - Camera_x;
    player.Player_winy = Camera_y - player.Player_y;
    player.player->setPos(player.Player_winx, player.Player_winy);
    player.player->setAnchor(0.5f, 0.5f);
    player.player->setRotation(player.Player_angle);
}
void Camera::ProjectWeapon(Weapon& weapon)
{
    weapon.Weapon_winx = weapon.Weapon_x - Camera_x;
    weapon.Weapon_winy = Camera_y - weapon.Weapon_y;
    weapon.weapon_Node->setPos(weapon.Weapon_winx, weapon.Weapon_winy);
    weapon.weapon_Node->setAnchor(0.5f, 0.5f);
    weapon.weapon_Node->setRotation(weapon.TureAngle);
    for (int i = 0; i < weapon.bullet_list.size(); i++)
    {
        weapon.bullet_list[i].Bullet_x += weapon.bullet_list[i].Speed_x;
        weapon.bullet_list[i].Bullet_y += weapon.bullet_list[i].Speed_y;
        weapon.bullet_list[i].Bullet_winx = weapon.bullet_list[i].Bullet_x - Camera_x;
        weapon.bullet_list[i].Bullet_winy = Camera_y - weapon.bullet_list[i].Bullet_y;
        if (weapon.bullet_list[i].bullet_Node != NULL)
        {
            weapon.bullet_list[i].bullet_Node->setPos(weapon.bullet_list[i].Bullet_winx, weapon.bullet_list[i].Bullet_winy);
            weapon.bullet_list[i].bullet_Node->setAnchor(0.5f, 0.5f);
            weapon.bullet_list[i].bullet_Node->setRotation(weapon.bullet_list[i].Angle);
        }
    }
}
void Camera::ProjectParticle(Particle& particle)
{
    particle.Particle_winx = particle.Particle_x - Camera_x;
    particle.Particle_winy = Camera_y - particle.Particle_y;
    double x = -particle.Particle_x + particle.Particle_winx;
    double y = particle.Particle_y + particle.Particle_winy;

    auto action = gcnew Spawn;
    class easy2d::ShapeNode* part = gcnew ShapeNode;
    class easy2d::Sprite* sprite = particle.particle_Sprite;

    DrawingStyle style;
    style.mode = DrawingStyle::Mode::Solid;          // 绘图模式为填充
    style.fillColor = particle.Base_color;           // 填充色
    part = ShapeNode::createCircle(particle.radius, style);

    particle.particle_Node->addChild(part);
    particle.particle_Node->setPos(x, y);

    float angle = particle.TureAngle * acos(-1) / 180;
    float time = 1 / Time::getDeltaTime();

    float speed_x = (sin(angle) * particle.Speed) * particle.LifeTime;
    float speed_y = (cos(angle) * particle.Speed) * particle.LifeTime;
    if (particle.Follow)
    {
        speed_x += particle.Base_Speed_x * 120 * particle.LifeTime;
        speed_y += particle.Base_Speed_y * 120 * particle.LifeTime;
    }
    auto move = gcnew MoveBy(1.0f, Vector2(speed_x, -speed_y));
    if (particle.action == NULL) action = gcnew Spawn({ move });
    else action = gcnew Spawn({ move, particle.action->clone() });

    part->setPos(-x + particle.Particle_winx, -y + particle.Particle_winy);
    part->runAction(action);
    part->setAnchor(0.5f, 0.5f);
    if (sprite != NULL)
    {
        part->addChild(sprite);
        sprite->setRotation(particle.TureAngle);
        sprite->setAnchor(0.5f, 0.5f);
    }

    Timer::add([=]() {particle.particle_Node->removeChild(part); }, particle.LifeTime, 1);
}
void Camera::ProjectMapBlock(MapBlock& mapblock)
{
    mapblock.MapBlock_winx = mapblock.MapBlock_x - Camera_x;
    mapblock.MapBlock_winy = Camera_y - mapblock.MapBlock_y;
    mapblock.mapBlock->setPos(mapblock.MapBlock_winx, mapblock.MapBlock_winy);
}
void Camera::ProjectMapText(MapText& maptext)
{
    maptext.MapText_winx = maptext.MapText_x - Camera_x;
    maptext.MapText_winy = Camera_y - maptext.MapText_y;
    maptext.mapText->setPos(maptext.MapText_winx, maptext.MapText_winy);
}
void Camera::Coordinates()
{
    Speed_x = Speed_y = 0;
    Camera_x += Speed_x;
    Camera_y += Speed_y;
}