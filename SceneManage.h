//================================
//Դ�����ߣ�EveSunMaple
//BiliBili��https://space.bilibili.com/438392347
//CSDN��https://blog.csdn.net/qq_50604688
//δ�������ֹת�ش��ļ�
//================================
#pragma once
#include <easy2d/easy2d.h>
#include <vector>
#include <queue>
using namespace easy2d;
using namespace std;

//��ͼ����
class MapBlock
{
public:
    void SetMapBlock(int x, int y);									                //���õ�ͼ������
    void SetHealth(float he);                                                       //���õ�ͼ������
    void SetCollisionBox(int x, int y);                                             //���õ�ͼ����ײ��
    void SetElastic(float el);                                                      //���õ�ͼ�鵯��ת����
    void SetColor(Color color);                                                     //���õ�ͼ�鱳����ɫ
    void InitMapBlock();                                                            //��ʼ����ͼ��
    void Coordinates();                                                             //�Զ�������

    class easy2d::ShapeNode* mapBlock = gcnew ShapeNode;                              //�����ͼ��ڵ�
    int MapBlock_x = 0, MapBlock_y = 0;												//��ͼ��Ĭ������
    int MapBlock_winx = 0, MapBlock_winy = 0;										//��ͼ��Ĭ�ϴ�������
    float health = 0;                                                               //��ͼ��Ĭ������ֵ
    int Collision_x = 0, Collision_y = 0;                                           //��ͼ��Ĭ����ײ��
    float elastic = 0;                                                              //��ͼ��Ĭ�ϵ���ת����
    Color Base_color = Color::White;                                                //��ͼ��Ĭ�ϱ�����ɫ
};
//������
class MapText
{
public:
    void SetText(class easy2d::Text* text);                                         //�����ı�������
    void SetMapText(int x, int y);									                //�����ı�������
    void SetRotation(float ro);                                                     //�����ı���˳ʱ����ת
    void SetScale(float sc);                                                        //�������ִ�С
    void SetOpacity(float op);                                                      //�������ֲ�͸����
    void SetColor(Color color);                                                     //����������ɫ
    void SetLineSpacing(int li);                                                    //���������м��
    void SetWidth(int wi);                                                          //�����ı�����
    void SetUnderLine(bool li);                                                     //�����»���
    void SetStrikeThrough(bool li);                                                 //����ɾ����
    void InitMapText();                                                             //��ʼ��Ĭ������
    void Coordinates();                                                             //�Զ�������

    class easy2d::Text* mapText = gcnew Text;                                         //�������ֽڵ�
    int MapText_x = 0, MapText_y = 0;										        //����Ĭ������
    int MapText_winx = 0, MapText_winy = 0;									        //����Ĭ�ϴ�������
    float rotation = 0;                                                             //����Ĭ��˳ʱ����ת
    float scale = 1;                                                                //����Ĭ������
    float opacity = 1;                                                              //����Ĭ�ϲ�͸����
    int lineSpacing = 10;                                                           //����Ĭ���м��
    int width = 1000;                                                               //�ı���Ĭ�Ͽ��
    bool underLine = false;                                                         //�»���
    bool strikeThrough = false;                                                     //ɾ����
    Color Base_color = Color::White;                                                //����Ĭ����ɫ
};
//��ɫ��
class Player
{
public:
    void SetPlayer(int x, int y);									                //���ý�ɫ����
    void SetHealth(float he);                                                       //���ý�ɫ����
    void SetCollisionBox(int x, int y);                                             //���ý�ɫ��ײ��
    void SetSpeed(float speed);                                                     //���ý�ɫ�����ٶ�
    void SetAcceleration(float speed);                                              //���ý�ɫÿ֡���ٶ�
    void SetSpeedAngle(float speed);                                                //���ý�ɫ�����ٶ�
    void SetAccelerationAngle(float speed);                                         //���ý�ɫÿ֡���ٶ�
    void SetFriction(float fr);                                                     //���ý�ɫĦ��ϵ��
    void SetFrictionAngle(float fr);                                                //���ý�ɫ�Ƕ�Ħ��
    void SetColor(Color color);                                                     //���ý�ɫ������ɫ
    void CtrlPlayer(int lx, int ly, int rx, int ry);				                //���ý�ɫ�ƶ���Χ
    void CtrlPlayerMove(char up, char right, char down, char left);	                //���ý�ɫ��������
    void InitPlayer();                                                              //��ʼ����ɫ
    void Coordinates();                                                             //���̿��ƽ�ɫ����
    void CheckCollision(MapBlock Map);                                              //��ײ�ж�
    void UseResults();                                                              //�������

    class easy2d::ShapeNode* player = gcnew ShapeNode;                              //�����ɫ�ڵ�
    double Speed = 0;													            //��ɫ��ǰ�ٶ�
    double Player_angle = 0;                                                        //��ɫĬ�ϽǶȣ�UP��
    double Player_x = 0, Player_y = 0;												//��ɫĬ������
    double Player_winx = 0, Player_winy = 0;									    //��ɫĬ�ϴ�������
    double health = 100;                                                            //��ɫĬ������ֵ
    int Collision_x = 0, Collision_y = 0;                                           //��ɫĬ����ײ��   (�ޣ�
    double Speed_x = 0, Speed_y = 0;												//��ɫ�ƶ��ٶ�

private:
    double Speed_angle = 0;													        //��ɫ���ٶ�
    double Change_angle = 0;                                                        //Ŀ��ǶȲ���
    double Traget_angle = 0;                                                        //���Ŀ��Ƕ�
    double maxSpeed = 2;                                                            //��ɫĬ������ٶ�
    double maxSpeed_angle = 5;													    //��ɫĬ�������ٶ�
    double acceleration = 5.0f;                                                     //��ɫĬ��ÿ֡���ٶ�
    double acceleration_angle = 10.0f;                                              //��ɫĬ��ÿ֡���ٶ�
    double friction = 1.5f;												            //��ɫĬ��Ħ��ϵ��
    double friction_angle = 1.5f;												    //��ɫĬ�ϽǶ�Ħ��
    Color Base_color = Color::Purple;                                               //��ɫĬ�ϱ�����ɫ
    int Ctrl_lx = 0, Ctrl_ly = 0, Ctrl_rx = 0, Ctrl_ry = 0;							//��ɫĬ���ƶ���Χ (������)
};

class Bullet
{
public:
    class easy2d::ShapeNode* bullet_Node = gcnew ShapeNode;                         //�����ӵ��ڵ�
    class easy2d::Sprite* bullet_Sprite = NULL;                                     //�����ӵ����� ���棩
    float Bullet_x = 0, Bullet_y = 0;										        //�ӵ�����
    float Bullet_winx = 0, Bullet_winy = 0;										    //�ӵ���������
    float Speed_x = 0, Speed_y = 0;                                                 //�ӵ��ƶ��ٶ�
    float Angle = 0;                                                                //�ӵ�����Ƕ�
    Color Base_color = Color::WhiteSmoke;                                           //�ӵ�Ĭ����ɫ
};

//������
class Weapon
{
public:
    void SetRadius(int r);                                                          //�����ӵ���С
    void SetActionBullet(class easy2d::Spawn* sp);                                  //�����ӵ�����
    void SetActionWeapon(class easy2d::Spawn* sp);                                  //������������
    void SetSpriteBullet(easy2d::Sprite* sprite);                                   //�����ӵ�ͼƬ
    void SetSpriteWeapon(easy2d::Sprite* sprite);                                   //��������ͼƬ
    void SetLifeTime(float time);                                                   //�����ӵ�ʱ��
    void SetWeaponToPlayer(float x, float y, Player player);                        //��԰󶨽�ɫ
    void InitWeapon(float speed, float angle, Color color);                         //����������ֵ
    void Coordinates(easy2d::Sprite* sprite, Player player);                                                             //��������

    deque<Bullet> bullet_list;                                                     //�����ӵ��б�
    class easy2d::ShapeNode* bullet_Node = gcnew ShapeNode;                         //�����ӵ��ڵ�
    class easy2d::Sprite* bullet_Sprite = NULL;                                     //�����ӵ�����
    class easy2d::Spawn* bullet_Action = NULL;                                      //�����ӵ�����
    class easy2d::ShapeNode* weapon_Node = gcnew ShapeNode;                         //���������ڵ�
    class easy2d::Sprite* weapon_Sprite = NULL;                                     //������������
    class easy2d::Spawn* weapon_Action = NULL;                                      //������������
    float FireTime = 0.1f, NowTime = 0;                                             //�ӵ�������
    float LifeTime = 1;                                                             //�ӵ�����ʱ��
    float Speed = 10;                                                               //�ӵ������ٶ�
    float Angle = 0;                                                                //�ӵ�����Ƕ�
    float TureAngle = 0;                                                            //�ӵ�����Ƕ� ���棩
    int radius = 10;                                                                //�ӵ�Ĭ�ϴ�С
    float Weapon_x = 0, Weapon_y = 0;										        //����Ĭ������
    float Weapon_winx = 0, Weapon_winy = 0;										    //����Ĭ�ϴ�������
    float Base_Speed_x = 0, Base_Speed_y = 0;                                       //�ӵ������ٶ�
    Color Base_color = Color::WhiteSmoke;                                           //�ӵ�Ĭ����ɫ
};

//������
class Particle
{
public:
    void SetAction(class easy2d::Spawn* sp);                                        //�������Ӷ���
    void SetRadius(int r);                                                          //�������Ӵ�С
    void SetFollow(bool f);                                                         //�������Ӹ���
    void SetSprite(easy2d::Sprite* sprite);                                         //��������ͼƬ
    void SetLifeTime(float time);                                                   //��������ʱ��
    void SetParticleToPlayer(float x, float y, Player player);                      //��԰󶨽�ɫ
    void InitParticle(float speed, float angle, Color color);                       //����������ֵ
    void Coordinates();                                                             //��������

    bool Follow = false;
    class easy2d::ShapeNode* particle_Node = gcnew ShapeNode;                       //�������ӽڵ�
    class easy2d::Sprite* particle_Sprite = NULL;                                   //�������Ӿ���
    class easy2d::Spawn* action = NULL;                                             //�������Ӷ���
    float LifeTime = 1;                                                             //�������Ӵ���ʱ��
    float Speed = 0;                                                                //���ӷ����ٶ�
    float Angle = 0;                                                                //���ӷ���Ƕ�
    float TureAngle = 0;                                                            //���ӷ���Ƕ� ���棩
    int radius = 10;                                                                //����Ĭ�ϴ�С
    float Particle_x = 0, Particle_y = 0;										    //����Ĭ������
    float Particle_winx = 0, Particle_winy = 0;										//����Ĭ�ϴ�������
    float Base_Speed_x = 0, Base_Speed_y = 0;                                       //���ӻ����ٶ�
    Color Base_color = Color::WhiteSmoke;                                           //����Ĭ����ɫ
};
