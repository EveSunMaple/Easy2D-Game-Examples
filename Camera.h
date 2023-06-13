//================================
//源码作者：EveSunMaple
//BiliBili：https://space.bilibili.com/438392347
//CSDN：https://blog.csdn.net/qq_50604688
//未经允许禁止转载此文件
//================================
#pragma once
#include "SceneManage.h"
#include <string.h>
#include <easy2d/easy2d.h>
using namespace easy2d;

//摄像机类
class Camera
{
public:
	void SetCamera(int x, int y);													//设置摄像头坐标
	void SetSpeed(float speed);														//设置摄像头速度
	void SetCenter(int x, int y);													//设置摄像头跟随中心
	void SetRange(int lx, int ly, int rx, int ry);									//设置摄像头跟随阈值
	void CtrlCamera(int lx, int ly, int rx, int ry);								//设置摄像头移动范围
	void CtrlCameraMove(char up, char right, char down, char left);					//设置摄像头按键控制
	void SetTarget(Player player);													//设置摄像头跟随目标
	void ProjectPlayer(Player& player);												//把人物投影到摄像头中
	void ProjectWeapon(Weapon& weapon);												//把武器投影到摄像头中
	void ProjectParticle(Particle& particle);										//把粒子投影到摄像头中
	void ProjectMapBlock(MapBlock& mapblock);										//把地图块投影到摄像头中
	void ProjectMapText(MapText& maptext);											//把文字投影到摄像头中
	void Coordinates();																//键盘控制摄像头坐标

	int Camera_x = 0, Camera_y = 0;													//摄像头默认坐标
	float Camera_width = 1280, Camera_height = 960;									//摄像头大小
	float Speed_x = 0, Speed_y = 0;													//摄像头移动速度
	float maxSpeed = 5;																//摄像头默认速度
	int Center_x = Camera_width / 2, Center_y = Camera_height / 2;					//摄像头默认跟随中心
	int Response_lx = 0, Response_ly = 0, Response_rx = 0, Response_ry = 0;			//摄像头默认跟随阈值
	int Ctrl_lx = 0, Ctrl_ly = 0, Ctrl_rx = 0, Ctrl_ry = 0;							//摄像头默认移动范围 (不限制)
};