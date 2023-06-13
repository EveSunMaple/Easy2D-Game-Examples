//================================
//源码作者：EveSunMaple
//BiliBili：https://space.bilibili.com/438392347
//CSDN：https://blog.csdn.net/qq_50604688
//未经允许禁止转载此文件
//================================
#pragma once
#include <easy2d/easy2d.h>
#include <vector>
#include <queue>
using namespace easy2d;
using namespace std;

//地图块类
class MapBlock
{
public:
    void SetMapBlock(int x, int y);									                //设置地图块坐标
    void SetHealth(float he);                                                       //设置地图块生命
    void SetCollisionBox(int x, int y);                                             //设置地图块碰撞箱
    void SetElastic(float el);                                                      //设置地图块弹力转化率
    void SetColor(Color color);                                                     //设置地图块背景颜色
    void InitMapBlock();                                                            //初始化地图块
    void Coordinates();                                                             //自定义运算

    class easy2d::ShapeNode* mapBlock = gcnew ShapeNode;                              //定义地图块节点
    int MapBlock_x = 0, MapBlock_y = 0;												//地图块默认坐标
    int MapBlock_winx = 0, MapBlock_winy = 0;										//地图块默认窗口坐标
    float health = 0;                                                               //地图块默认生命值
    int Collision_x = 0, Collision_y = 0;                                           //地图块默认碰撞箱
    float elastic = 0;                                                              //地图块默认弹力转化率
    Color Base_color = Color::White;                                                //地图块默认背景颜色
};
//文字类
class MapText
{
public:
    void SetText(class easy2d::Text* text);                                         //设置文本框内容
    void SetMapText(int x, int y);									                //设置文本框坐标
    void SetRotation(float ro);                                                     //设置文本框顺时针旋转
    void SetScale(float sc);                                                        //设置文字大小
    void SetOpacity(float op);                                                      //设置文字不透明度
    void SetColor(Color color);                                                     //设置文字颜色
    void SetLineSpacing(int li);                                                    //设置文字行间距
    void SetWidth(int wi);                                                          //设置文本框宽度
    void SetUnderLine(bool li);                                                     //设置下划线
    void SetStrikeThrough(bool li);                                                 //设置删除线
    void InitMapText();                                                             //初始化默认文字
    void Coordinates();                                                             //自定义运算

    class easy2d::Text* mapText = gcnew Text;                                         //定义文字节点
    int MapText_x = 0, MapText_y = 0;										        //文字默认坐标
    int MapText_winx = 0, MapText_winy = 0;									        //文字默认窗口坐标
    float rotation = 0;                                                             //文字默认顺时针旋转
    float scale = 1;                                                                //文字默认缩放
    float opacity = 1;                                                              //文字默认不透明度
    int lineSpacing = 10;                                                           //文字默认行间距
    int width = 1000;                                                               //文本框默认宽度
    bool underLine = false;                                                         //下划线
    bool strikeThrough = false;                                                     //删除线
    Color Base_color = Color::White;                                                //文字默认颜色
};
//角色类
class Player
{
public:
    void SetPlayer(int x, int y);									                //设置角色坐标
    void SetHealth(float he);                                                       //设置角色生命
    void SetCollisionBox(int x, int y);                                             //设置角色碰撞箱
    void SetSpeed(float speed);                                                     //设置角色行走速度
    void SetAcceleration(float speed);                                              //设置角色每帧加速度
    void SetSpeedAngle(float speed);                                                //设置角色行走速度
    void SetAccelerationAngle(float speed);                                         //设置角色每帧加速度
    void SetFriction(float fr);                                                     //设置角色摩擦系数
    void SetFrictionAngle(float fr);                                                //设置角色角度摩擦
    void SetColor(Color color);                                                     //设置角色背景颜色
    void CtrlPlayer(int lx, int ly, int rx, int ry);				                //设置角色移动范围
    void CtrlPlayerMove(char up, char right, char down, char left);	                //设置角色按键控制
    void InitPlayer();                                                              //初始化角色
    void Coordinates();                                                             //键盘控制角色坐标
    void CheckCollision(MapBlock Map);                                              //碰撞判断
    void UseResults();                                                              //完成运算

    class easy2d::ShapeNode* player = gcnew ShapeNode;                              //定义角色节点
    double Speed = 0;													            //角色当前速度
    double Player_angle = 0;                                                        //角色默认角度（UP）
    double Player_x = 0, Player_y = 0;												//角色默认坐标
    double Player_winx = 0, Player_winy = 0;									    //角色默认窗口坐标
    double health = 100;                                                            //角色默认生命值
    int Collision_x = 0, Collision_y = 0;                                           //角色默认碰撞箱   (无）
    double Speed_x = 0, Speed_y = 0;												//角色移动速度

private:
    double Speed_angle = 0;													        //角色角速度
    double Change_angle = 0;                                                        //目标角度差量
    double Traget_angle = 0;                                                        //鼠标目标角度
    double maxSpeed = 2;                                                            //角色默认最大速度
    double maxSpeed_angle = 5;													    //角色默认最大角速度
    double acceleration = 5.0f;                                                     //角色默认每帧加速度
    double acceleration_angle = 10.0f;                                              //角色默认每帧角速度
    double friction = 1.5f;												            //角色默认摩擦系数
    double friction_angle = 1.5f;												    //角色默认角度摩擦
    Color Base_color = Color::Purple;                                               //角色默认背景颜色
    int Ctrl_lx = 0, Ctrl_ly = 0, Ctrl_rx = 0, Ctrl_ry = 0;							//角色默认移动范围 (不限制)
};

class Bullet
{
public:
    class easy2d::ShapeNode* bullet_Node = gcnew ShapeNode;                         //定义子弹节点
    class easy2d::Sprite* bullet_Sprite = NULL;                                     //定义子弹精灵 （真）
    float Bullet_x = 0, Bullet_y = 0;										        //子弹坐标
    float Bullet_winx = 0, Bullet_winy = 0;										    //子弹窗口坐标
    float Speed_x = 0, Speed_y = 0;                                                 //子弹移动速度
    float Angle = 0;                                                                //子弹发射角度
    Color Base_color = Color::WhiteSmoke;                                           //子弹默认颜色
};

//武器类
class Weapon
{
public:
    void SetRadius(int r);                                                          //设置子弹大小
    void SetActionBullet(class easy2d::Spawn* sp);                                  //设置子弹动画
    void SetActionWeapon(class easy2d::Spawn* sp);                                  //设置武器动画
    void SetSpriteBullet(easy2d::Sprite* sprite);                                   //设置子弹图片
    void SetSpriteWeapon(easy2d::Sprite* sprite);                                   //设置武器图片
    void SetLifeTime(float time);                                                   //设置子弹时间
    void SetWeaponToPlayer(float x, float y, Player player);                        //相对绑定角色
    void InitWeapon(float speed, float angle, Color color);                         //设置武器数值
    void Coordinates(easy2d::Sprite* sprite, Player player);                                                             //武器运算

    deque<Bullet> bullet_list;                                                     //定义子弹列表
    class easy2d::ShapeNode* bullet_Node = gcnew ShapeNode;                         //定义子弹节点
    class easy2d::Sprite* bullet_Sprite = NULL;                                     //定义子弹精灵
    class easy2d::Spawn* bullet_Action = NULL;                                      //定义子弹动画
    class easy2d::ShapeNode* weapon_Node = gcnew ShapeNode;                         //定义武器节点
    class easy2d::Sprite* weapon_Sprite = NULL;                                     //定义武器精灵
    class easy2d::Spawn* weapon_Action = NULL;                                      //定义武器动画
    float FireTime = 0.1f, NowTime = 0;                                             //子弹发射间隔
    float LifeTime = 1;                                                             //子弹存在时间
    float Speed = 10;                                                               //子弹发射速度
    float Angle = 0;                                                                //子弹发射角度
    float TureAngle = 0;                                                            //子弹发射角度 （真）
    int radius = 10;                                                                //子弹默认大小
    float Weapon_x = 0, Weapon_y = 0;										        //武器默认坐标
    float Weapon_winx = 0, Weapon_winy = 0;										    //武器默认窗口坐标
    float Base_Speed_x = 0, Base_Speed_y = 0;                                       //子弹基础速度
    Color Base_color = Color::WhiteSmoke;                                           //子弹默认颜色
};

//粒子类
class Particle
{
public:
    void SetAction(class easy2d::Spawn* sp);                                        //设置粒子动画
    void SetRadius(int r);                                                          //设置粒子大小
    void SetFollow(bool f);                                                         //设置粒子跟随
    void SetSprite(easy2d::Sprite* sprite);                                         //设置粒子图片
    void SetLifeTime(float time);                                                   //设置粒子时间
    void SetParticleToPlayer(float x, float y, Player player);                      //相对绑定角色
    void InitParticle(float speed, float angle, Color color);                       //设置粒子数值
    void Coordinates();                                                             //粒子运算

    bool Follow = false;
    class easy2d::ShapeNode* particle_Node = gcnew ShapeNode;                       //定义粒子节点
    class easy2d::Sprite* particle_Sprite = NULL;                                   //定义粒子精灵
    class easy2d::Spawn* action = NULL;                                             //定义粒子动画
    float LifeTime = 1;                                                             //定义粒子存在时间
    float Speed = 0;                                                                //粒子发射速度
    float Angle = 0;                                                                //粒子发射角度
    float TureAngle = 0;                                                            //粒子发射角度 （真）
    int radius = 10;                                                                //粒子默认大小
    float Particle_x = 0, Particle_y = 0;										    //粒子默认坐标
    float Particle_winx = 0, Particle_winy = 0;										//粒子默认窗口坐标
    float Base_Speed_x = 0, Base_Speed_y = 0;                                       //粒子基础速度
    Color Base_color = Color::WhiteSmoke;                                           //粒子默认颜色
};
