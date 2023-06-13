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
                sprite->open("Backgrounds/purple.png"); // 从本地图片加载
                this->addChild(sprite); //添加进游戏
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
    Camera camera; //添加一个摄像头
    MapBlock Background;
    MapBlock map[5]; //添加地图块
    MapText text[5]; //添加文字
    Player player; //添加游戏人物

    WorldPage()
    {
        camera.SetRange(150, 150, 150, 150); //设置摄像头跟随阈值

        map[0].SetMapBlock(-10000, -200); //设置地图块的坐标
        map[0].SetCollisionBox(20000, 1000); //设置地图块的大小

        map[1].SetMapBlock(-700, 0); //设置地图块的坐标
        map[1].SetCollisionBox(100, 200); //设置地图块的大小

        map[2].SetMapBlock(500, 200); //设置地图块的坐标
        map[2].SetCollisionBox(100, 400); //设置地图块的大小

        map[3].SetMapBlock(200, 0); //设置地图块的坐标
        map[3].SetCollisionBox(300, 5); //设置地图块的大小
        map[3].SetElastic(0.8); //设置地图块的弹力
        map[3].SetColor(Color::Orange); //设置地图块的颜色

        map[4].SetMapBlock(1300, -150); //设置地图块的坐标
        map[4].SetCollisionBox(300, 50); //设置地图块的大小
        map[4].SetElastic(1.5); //设置地图块的弹力
        map[4].SetColor(Color::Red); //设置地图块的颜色

        text[0].SetText(gcnew Text("这是一个示例")); //设置文本框内容
        text[0].SetMapText(-2300, -70); //设置文本框的坐标

        text[1].SetText(gcnew Text("使用WASD控制")); //设置文本框内容
        text[1].SetMapText(-1800, -50); //设置文本框的坐标

        text[2].SetText(gcnew Text("跳过地图块！")); //设置文本框内容
        text[2].SetMapText(-900, -50); //设置文本框的坐标

        text[3].SetText(gcnew Text("借助板子越过去"));//设置文本框内容
        text[3].SetMapText(0, -50); //设置文本框的坐标

        text[4].SetText(gcnew Text("使用弹力块！")); //设置文本框内容
        text[4].SetMapText(1400, -50); //设置文本框的坐标

        Background.InitMapBlock(); //初始化默认地图块 
        this->addChild(Background.mapBlock); //添加进游戏
        auto ground = gcnew BackGround;
        Background.mapBlock->addChild(ground); //添加进游戏
        ground->setAnchor(0.5f, 0.5f);
        for (int i = 0; i < 5; i++)
        {
            map[i].InitMapBlock(); //初始化默认地图块 
            this->addChild(map[i].mapBlock); //添加进游戏
            text[i].InitMapText(); //初始化默认文字 
            this->addChild(text[i].mapText); //添加进游戏
        }

        player.SetPlayer(0, 0); //设置游戏人物坐标
        player.SetCollisionBox(0, 0); //设置游戏人物大小
        player.SetSpeed(10); //设置游戏人物速度
        player.InitPlayer(); //初始化默认人物

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
        this->addChild(locus[0].particle_Node); //添加进游戏
        locus[1].SetAction(two);
        //locus[1].SetFollow(true);
        locus[1].InitParticle(500, 180, Color::LightSkyBlue);
        this->addChild(locus[1].particle_Node); //添加进游戏
        locus[2].SetAction(three);
        //locus[2].SetFollow(true);
        locus[2].InitParticle(500, 180, Color::Yellow);
        this->addChild(locus[2].particle_Node); //添加进游戏
        locus[3].SetAction(three);
        //locus[3].SetFollow(true);
        locus[3].InitParticle(500, 180, Color::Yellow);
        this->addChild(locus[3].particle_Node); //添加进游戏
        locus[4].SetAction(four);
        locus[4].SetRadius(2);
        locus[4].InitParticle(0, 180, Color::White);
        this->addChild(locus[4].particle_Node); //添加进游戏
        locus[5].SetAction(four);
        locus[5].SetRadius(2);
        locus[5].InitParticle(0, 180, Color::White);
        this->addChild(locus[5].particle_Node); //添加进游戏

        auto bullet = gcnew Sprite;
        bullet->open("PNG/Lasers/laserBlue01.png"); // 从本地图片加载

        weapon[0].SetRadius(0);
        weapon[0].InitWeapon(1000, 0, Color::White);
        weapon[0].SetLifeTime(10);
        weapon[0].SetSpriteBullet(bullet);
        this->addChild(weapon[0].weapon_Node); //添加进游戏
        weapon[1].SetRadius(0);
        weapon[1].InitWeapon(1000, 0, Color::White);
        weapon[1].SetLifeTime(10);
        weapon[1].SetSpriteBullet(bullet);
        this->addChild(weapon[1].weapon_Node); //添加进游戏

        auto sprite = gcnew Sprite;
        sprite->open("PNG/playerShip1_blue.png"); // 从本地图片加载
        player.player->addChild(sprite); //添加进游戏
        sprite->setAnchor(0.5f, 0.5f);

        this->addChild(player.player); //添加进游戏
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
        camera.ProjectWeapon(weapon[0]); //把武器投影到摄像头中
        camera.ProjectWeapon(weapon[1]); //把武器投影到摄像头中

        locus[4].SetParticleToPlayer(44, -20, player);
        locus[5].SetParticleToPlayer(-44, -20, player);
        camera.ProjectParticle(locus[4]); //把粒子投影到摄像头中
        camera.ProjectParticle(locus[5]); //把粒子投影到摄像头中
        if (Input::isDown(KeyCode::W))
        {
            locus[0].SetParticleToPlayer(25, -15, player);
            locus[1].SetParticleToPlayer(-25, -15, player);
            locus[2].SetParticleToPlayer(25, -15, player);
            locus[3].SetParticleToPlayer(-25, -15, player);
            camera.ProjectParticle(locus[0]); //把粒子投影到摄像头中
            camera.ProjectParticle(locus[1]); //把粒子投影到摄像头中
            camera.ProjectParticle(locus[2]); //把粒子投影到摄像头中
            camera.ProjectParticle(locus[3]); //把粒子投影到摄像头中
        }

        camera.ProjectMapBlock(Background); //把背景投影到摄像头中
        if (camera.Camera_x <= Background.MapBlock_x) Background.MapBlock_x -= Ground_width;
        if (camera.Camera_y >= Background.MapBlock_y) Background.MapBlock_y += Ground_height;
        if (camera.Camera_x >= Background.MapBlock_x + Ground_width) Background.MapBlock_x += Ground_width;
        if (camera.Camera_y <= Background.MapBlock_y - Ground_height) Background.MapBlock_y -= Ground_height;

        player.Coordinates(); //开始人物运算，使用WASD控制
        for (int i = 0; i < 5; i++)
        {
            //player.CheckCollision(map[i]); //计算与地图块的碰撞
            camera.ProjectMapBlock(map[i]); //把地图块投影到摄像头中
            camera.ProjectMapText(text[i]); //把文本框投影到摄像头中
        }
        player.UseResults(); //完成人物运算
        camera.SetTarget(player); //设置摄像头跟随目标
        camera.ProjectPlayer(player); //把人物投影到摄像头中
    }
};

int main()
{
    if (Game::init("Easy2D平台跳跃实例", 1280, 960))
    {
        Renderer::showFps(true);			//显示FPS

        auto sprite = gcnew Sprite;
        sprite->open("PNG/Lasers/laserBlue11.png"); // 从本地图片加载
        sprite->setAnchor(0.5f, 0.5f);
        Window::setCustomCursor(sprite);

        auto world = new Scene;             //新建场景

        SceneManager::enter(world);         //进入场景

        auto worldPage = gcnew WorldPage;   //加载世界

        world->addChild(worldPage);         //把世界添加进场景

        Game::start();
    }
    Game::destroy();
    return 0;
}