//================================
//Դ�����ߣ�EveSunMaple
//BiliBili��https://space.bilibili.com/438392347
//CSDN��https://blog.csdn.net/qq_50604688
//δ�������ֹת�ش��ļ�
//================================
#pragma once
#include "SceneManage.h"
#include <string.h>
#include <easy2d/easy2d.h>
using namespace easy2d;

//�������
class Camera
{
public:
	void SetCamera(int x, int y);													//��������ͷ����
	void SetSpeed(float speed);														//��������ͷ�ٶ�
	void SetCenter(int x, int y);													//��������ͷ��������
	void SetRange(int lx, int ly, int rx, int ry);									//��������ͷ������ֵ
	void CtrlCamera(int lx, int ly, int rx, int ry);								//��������ͷ�ƶ���Χ
	void CtrlCameraMove(char up, char right, char down, char left);					//��������ͷ��������
	void SetTarget(Player player);													//��������ͷ����Ŀ��
	void ProjectPlayer(Player& player);												//������ͶӰ������ͷ��
	void ProjectWeapon(Weapon& weapon);												//������ͶӰ������ͷ��
	void ProjectParticle(Particle& particle);										//������ͶӰ������ͷ��
	void ProjectMapBlock(MapBlock& mapblock);										//�ѵ�ͼ��ͶӰ������ͷ��
	void ProjectMapText(MapText& maptext);											//������ͶӰ������ͷ��
	void Coordinates();																//���̿�������ͷ����

	int Camera_x = 0, Camera_y = 0;													//����ͷĬ������
	float Camera_width = 1280, Camera_height = 960;									//����ͷ��С
	float Speed_x = 0, Speed_y = 0;													//����ͷ�ƶ��ٶ�
	float maxSpeed = 5;																//����ͷĬ���ٶ�
	int Center_x = Camera_width / 2, Center_y = Camera_height / 2;					//����ͷĬ�ϸ�������
	int Response_lx = 0, Response_ly = 0, Response_rx = 0, Response_ry = 0;			//����ͷĬ�ϸ�����ֵ
	int Ctrl_lx = 0, Ctrl_ly = 0, Ctrl_rx = 0, Ctrl_ry = 0;							//����ͷĬ���ƶ���Χ (������)
};