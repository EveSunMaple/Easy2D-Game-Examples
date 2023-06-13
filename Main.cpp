#include <easy2d/easy2d.h>
#include <iostream>
#include "Camera.h"
#include "SceneManage.h"
#define width 1280
#define height 960

using namespace easy2d;
using namespace std;

int Back_length = 256;
int Ground_width = 0;
int Ground_height = 0;

class BackGround : public Sprite
{
public:
    BackGround()
    {
        int i = 0, j = 0;
        for (Ground_width = 0; Ground_width < width * 4; i++)
        {
            for (Ground_height = 0; Ground_height < height * 4; j++)
            {
                auto sprite = gcnew Sprite;
                sprite->open("Backgrounds/purple.png"); // �ӱ���ͼƬ����
                this->addChild(sprite); //��ӽ���Ϸ
                sprite->setPos(Ground_width, Ground_height);
                sprite->setAnchor(0.5f, 0.5f);
                Ground_height += Back_length;
                if (Ground_height >= height * 4) break;
            }
            Ground_width += Back_length;
            if (Ground_width >= width * 4) break;
        }
        Ground_width = Back_length * (i / 4);
        Ground_height = Back_length * (j / i / 4);
        cout << Ground_width << endl;
        cout << Ground_height << endl;
    }
};
class WorldPage : public Sprite
{
public:
    Particle locus[6];
    Weapon weapon[2];
    Camera camera; //���һ������ͷ
    MapBlock Background;
    MapBlock map[5]; //��ӵ�ͼ��
    MapText text[5]; //�������
    Player player; //�����Ϸ����

    WorldPage()
    {
        camera.SetRange(150, 150, 150, 150); //��������ͷ������ֵ

        map[0].SetMapBlock(-10000, -200); //���õ�ͼ�������
        map[0].SetCollisionBox(20000, 1000); //���õ�ͼ��Ĵ�С

        map[1].SetMapBlock(-700, 0); //���õ�ͼ�������
        map[1].SetCollisionBox(100, 200); //���õ�ͼ��Ĵ�С

        map[2].SetMapBlock(500, 200); //���õ�ͼ�������
        map[2].SetCollisionBox(100, 400); //���õ�ͼ��Ĵ�С

        map[3].SetMapBlock(200, 0); //���õ�ͼ�������
        map[3].SetCollisionBox(300, 5); //���õ�ͼ��Ĵ�С
        map[3].SetElastic(0.8); //���õ�ͼ��ĵ���
        map[3].SetColor(Color::Orange); //���õ�ͼ�����ɫ

        map[4].SetMapBlock(1300, -150); //���õ�ͼ�������
        map[4].SetCollisionBox(300, 50); //���õ�ͼ��Ĵ�С
        map[4].SetElastic(1.5); //���õ�ͼ��ĵ���
        map[4].SetColor(Color::Red); //���õ�ͼ�����ɫ

        text[0].SetText(gcnew Text("����һ��ʾ��")); //�����ı�������
        text[0].SetMapText(-2300, -70); //�����ı��������

        text[1].SetText(gcnew Text("ʹ��WASD����")); //�����ı�������
        text[1].SetMapText(-1800, -50); //�����ı��������

        text[2].SetText(gcnew Text("������ͼ�飡")); //�����ı�������
        text[2].SetMapText(-900, -50); //�����ı��������

        text[3].SetText(gcnew Text("��������Խ��ȥ"));//�����ı�������
        text[3].SetMapText(0, -50); //�����ı��������

        text[4].SetText(gcnew Text("ʹ�õ����飡")); //�����ı�������
        text[4].SetMapText(1400, -50); //�����ı��������

        Background.InitMapBlock(); //��ʼ��Ĭ�ϵ�ͼ�� 
        this->addChild(Background.mapBlock); //��ӽ���Ϸ
        auto ground = gcnew BackGround;
        Background.mapBlock->addChild(ground); //��ӽ���Ϸ
        ground->setAnchor(0.5f, 0.5f);
        for (int i = 0; i < 5; i++)
        {
            map[i].InitMapBlock(); //��ʼ��Ĭ�ϵ�ͼ�� 
            this->addChild(map[i].mapBlock); //��ӽ���Ϸ
            text[i].InitMapText(); //��ʼ��Ĭ������ 
            this->addChild(text[i].mapText); //��ӽ���Ϸ
        }

        player.SetPlayer(0, 0); //������Ϸ��������
        player.SetCollisionBox(0, 0); //������Ϸ�����С
        player.SetSpeed(10); //������Ϸ�����ٶ�
        player.InitPlayer(); //��ʼ��Ĭ������

        auto scaleto = new ScaleTo(0.5f, 0.1f);
        auto scaleto1 = new ScaleTo(0.1f, 0.1f);
        auto scaleto2 = new ScaleTo(0.8f, 0.0f);
        auto opacityTo = new OpacityTo(0.2f, 0.0f);
        auto opacityTo1 = new OpacityTo(1.0f, 0.0f);
        auto two = new Spawn({ scaleto, opacityTo });
        auto three = new Spawn({ scaleto1, opacityTo });
        auto four = new Spawn({ scaleto2, opacityTo1 });
        locus[0].SetAction(two);
        //locus[0].SetFollow(true);
        locus[0].InitParticle(500, 180, Color::LightSkyBlue);
        this->addChild(locus[0].particle_Node); //��ӽ���Ϸ
        locus[1].SetAction(two);
        //locus[1].SetFollow(true);
        locus[1].InitParticle(500, 180, Color::LightSkyBlue);
        this->addChild(locus[1].particle_Node); //��ӽ���Ϸ
        locus[2].SetAction(three);
        //locus[2].SetFollow(true);
        locus[2].InitParticle(500, 180, Color::Yellow);
        this->addChild(locus[2].particle_Node); //��ӽ���Ϸ
        locus[3].SetAction(three);
        //locus[3].SetFollow(true);
        locus[3].InitParticle(500, 180, Color::Yellow);
        this->addChild(locus[3].particle_Node); //��ӽ���Ϸ
        locus[4].SetAction(four);
        locus[4].SetRadius(2);
        locus[4].InitParticle(0, 180, Color::White);
        this->addChild(locus[4].particle_Node); //��ӽ���Ϸ
        locus[5].SetAction(four);
        locus[5].SetRadius(2);
        locus[5].InitParticle(0, 180, Color::White);
        this->addChild(locus[5].particle_Node); //��ӽ���Ϸ

        auto bullet = gcnew Sprite;
        bullet->open("PNG/Lasers/laserBlue01.png"); // �ӱ���ͼƬ����

        weapon[0].SetRadius(0);
        weapon[0].InitWeapon(1000, 0, Color::White);
        weapon[0].SetLifeTime(10);
        weapon[0].SetSpriteBullet(bullet);
        this->addChild(weapon[0].weapon_Node); //��ӽ���Ϸ
        weapon[1].SetRadius(0);
        weapon[1].InitWeapon(1000, 0, Color::White);
        weapon[1].SetLifeTime(10);
        weapon[1].SetSpriteBullet(bullet);
        this->addChild(weapon[1].weapon_Node); //��ӽ���Ϸ

        auto sprite = gcnew Sprite;
        sprite->open("PNG/playerShip1_blue.png"); // �ӱ���ͼƬ����
        player.player->addChild(sprite); //��ӽ���Ϸ
        sprite->setAnchor(0.5f, 0.5f);

        this->addChild(player.player); //��ӽ���Ϸ
    }
    void onUpdate()
    {
        weapon[0].SetWeaponToPlayer(34, 20, player);
        weapon[1].SetWeaponToPlayer(-34, 20, player);
        if (Input::isDown(MouseCode::Left))
        {
            weapon[0].Coordinates(this, player);
            weapon[1].Coordinates(this, player);
        }
        camera.ProjectWeapon(weapon[0]); //������ͶӰ������ͷ��
        camera.ProjectWeapon(weapon[1]); //������ͶӰ������ͷ��

        locus[4].SetParticleToPlayer(44, -20, player);
        locus[5].SetParticleToPlayer(-44, -20, player);
        camera.ProjectParticle(locus[4]); //������ͶӰ������ͷ��
        camera.ProjectParticle(locus[5]); //������ͶӰ������ͷ��
        if (Input::isDown(KeyCode::W))
        {
            locus[0].SetParticleToPlayer(25, -15, player);
            locus[1].SetParticleToPlayer(-25, -15, player);
            locus[2].SetParticleToPlayer(25, -15, player);
            locus[3].SetParticleToPlayer(-25, -15, player);
            camera.ProjectParticle(locus[0]); //������ͶӰ������ͷ��
            camera.ProjectParticle(locus[1]); //������ͶӰ������ͷ��
            camera.ProjectParticle(locus[2]); //������ͶӰ������ͷ��
            camera.ProjectParticle(locus[3]); //������ͶӰ������ͷ��
        }

        camera.ProjectMapBlock(Background); //�ѱ���ͶӰ������ͷ��
        if (camera.Camera_x <= Background.MapBlock_x) Background.MapBlock_x -= Ground_width;
        if (camera.Camera_y >= Background.MapBlock_y) Background.MapBlock_y += Ground_height;
        if (camera.Camera_x >= Background.MapBlock_x + Ground_width) Background.MapBlock_x += Ground_width;
        if (camera.Camera_y <= Background.MapBlock_y - Ground_height) Background.MapBlock_y -= Ground_height;

        player.Coordinates(); //��ʼ�������㣬ʹ��WASD����
        for (int i = 0; i < 5; i++)
        {
            //player.CheckCollision(map[i]); //�������ͼ�����ײ
            camera.ProjectMapBlock(map[i]); //�ѵ�ͼ��ͶӰ������ͷ��
            camera.ProjectMapText(text[i]); //���ı���ͶӰ������ͷ��
        }
        player.UseResults(); //�����������
        camera.SetTarget(player); //��������ͷ����Ŀ��
        camera.ProjectPlayer(player); //������ͶӰ������ͷ��
    }
};

int main()
{
    if (Game::init("Easy2Dƽ̨��Ծʵ��", 1280, 960))
    {
        Renderer::showFps(true);			//��ʾFPS

        auto sprite = gcnew Sprite;
        sprite->open("PNG/Lasers/laserBlue11.png"); // �ӱ���ͼƬ����
        sprite->setAnchor(0.5f, 0.5f);
        Window::setCustomCursor(sprite);

        auto world = new Scene;             //�½�����

        SceneManager::enter(world);         //���볡��

        auto worldPage = gcnew WorldPage;   //��������

        world->addChild(worldPage);         //��������ӽ�����

        Game::start();
    }
    Game::destroy();
    return 0;
}