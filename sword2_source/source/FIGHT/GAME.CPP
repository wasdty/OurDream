//********************************************
//	��Ϸ�������     ��غ���
//  ������2000��5��29��
//********************************************

#include <windows.h>
#include <stdio.h>

#include "..\gamelib\goldpoint2.h"
#include "fight.h"

//////////////////////////////////
//ͨ�ñ���
//////////////////////////////////
LPDIRECTDRAWSURFACE *pic;
int Loopstatus;								//��ѭ�����ж�
//------------- ��Ϸ�������� ---------------------------

stRolePropertiy Propertiy_lib1;   //  ��ɫ״̬���ݴ�ŵ��ڴ�ռ�
stRolePropertiy * Propertiy1;   //  ָ���ɫ���ݵ�ָ��(������������)

stRolePropertiy Propertiy_lib2;   //�ڶ�����ɫ������
stRolePropertiy * Propertiy2;   
Fight fight;


/*   ���Զ����DrawSurface����   */
//��Ϸ��ʼ��
BOOL InitGame()
{	
	Propertiy1=&Propertiy_lib1;
	Propertiy_lib1.Hp=102;
	Propertiy2=&Propertiy_lib2;
	Propertiy_lib2.Hp=105;
//	fight.Init(&Propertiy_lib1); //  ��ʼ��/
	fight.Init();
	//��ʼ��һ����̨����   ��ȡ�ļ�

	Loopstatus=1;
	CreateBitmap(lpDDSBackGround, 0, 0, "Image\\background.bmp");

//	DDSetColorKey(pic,RGB(255,0,255));

	/*�Զ����������ݶ�ȡ */

	//��ʼ������
	font.InitFont(16, "����");

	Propertiy_lib1.Hp=100;
	Propertiy_lib2.Hp=100;
	Propertiy_lib1.Mp=100;
	Propertiy_lib2.Mp=100;
	Propertiy_lib1.Power=100;
	Propertiy_lib2.Power=100;
	Propertiy_lib1.Heart=100;
	Propertiy_lib2.Heart=100;
	Propertiy_lib1.Attack=10;
	Propertiy_lib2.Attack=13;
	Propertiy_lib1.Defend=5;
	Propertiy_lib2.Defend=5;

	CIniSet FightRoleInit("ini\\FightRoleInit.ini");
	Propertiy_lib1.Fight_Ini_Name="����˿";
	Propertiy_lib2.Fight_Ini_Name="����";
// ��������Ԥ�Ȱ����ȡ��ͷ������

	
	return true;
}

//--------------------------------------------------

//��ѭ��
void MainLoop()
{
	//��ʱ����
	NowTick=timeGetTime();
	if( NowTick < OldTick+DelayTick ) return;
	OldTick=NowTick;

	//��ȡ��굱ǰ������
	GetCursorPos(&point);
	if( WindowMode != 0 )	//����
	{
		point.x-=RectWindow.left;
		point.y-=RectWindow.top;
	}
	
	Mouse.GetMouseState();		//��ȡ���������Ϣ
	mouse=Mouse.GetMouseData();	//��ȡ��껺����Ϣ
	Key.GetKeyData();			//��ȡ���̻�������(������ʱ����)
	key=Key.GetKey();			//��ȡ��������

	//�л�ȫ���봰��
	if( (Key.GetState( DIK_LALT ) || Key.GetState( DIK_RALT )) && Key.GetState( DIK_RETURN ) )
	{
		if ( bSwitch && bActive )
		{
			if( WindowMode == 0 )
				lpDD->RestoreDisplayMode();
			GetWindowRect(hWnd, &RectWindow);
			WindowMode = 1-WindowMode;
			ChangeCoopLevel(hWnd);
		}
	}

//   LoopstatusΪ�ж�ʹ���ĸ�ѭ��
	if(Loopstatus==1)		//  ��Ϸ���е������ѭ��
	{
		DelayTick=0;
			//���������
		if( mouse == LB_UP )
		{
			if(point.x>=0&&point.x<=72&&point.y>=0&&point.y<=72)	//��ʽ1
			{
				Loopstatus=2;
				fight.Start("ini\\background1.ini",
					NULL,&Propertiy_lib2,NULL,
					"��ɫ��","��ɫ��","��ɫ��","��ɫ��");
			}
			else if(point.x>=72&&point.x<=144&&point.y>=0&&point.y<=72)	//��ʽ2
			{
				Loopstatus=2;
				fight.Start("ini\\background1.ini",
					NULL,&Propertiy_lib2,NULL,
					"��ɫ��","��ɫ��",NULL,"��ɫ��");
			}
			else if(point.x>=144&&point.x<=216&&point.y>=0&&point.y<=72)	//��ʽ3
			{
				Loopstatus=2;
				fight.Start("ini\\background1.ini",
					NULL,&Propertiy_lib2,NULL,
					"��ɫ��",NULL,NULL,"��ɫ��");
			}
			else if(point.x>=216&&point.x<=288&&point.y>=0&&point.y<=72)	//��ʽ4
			{
				Loopstatus=2;
				fight.Start("ini\\background1.ini",
					NULL,&Propertiy_lib2,NULL,
					NULL,"��ɫ��",NULL,NULL);
			}

			else if(point.x>=0&&point.x<=72&&point.y>=72&&point.y<=144)	//��ʽ5
			{
				Loopstatus=2;
				fight.Start("ini\\background1.ini",
					&Propertiy_lib2,NULL,&Propertiy_lib1,
					"��ɫ��","��ɫ��","��ɫ��","��ɫ��");
			}
			else if(point.x>=72&&point.x<=144&&point.y>=72&&point.y<=144)	//��ʽ6
			{
				Loopstatus=2;
				fight.Start("ini\\background1.ini",
					&Propertiy_lib2,NULL,&Propertiy_lib1,
					"��ɫ��","��ɫ��",NULL,"��ɫ��");
			}
			else if(point.x>=144&&point.x<=216&&point.y>=72&&point.y<=144)	//��ʽ7
			{
				Loopstatus=2;
				fight.Start("ini\\background1.ini",
					&Propertiy_lib2,NULL,&Propertiy_lib1,
					"��ɫ��",NULL,NULL,"��ɫ��");
			}
			else if(point.x>=216&&point.x<=288&&point.y>=72&&point.y<=144)	//��ʽ8
			{
				Loopstatus=2;
				fight.Start("ini\\background1.ini",
					&Propertiy_lib2,NULL,&Propertiy_lib1,
					NULL,"��ɫ��",NULL,NULL);
			}
			else if(point.x>=0&&point.x<=72&&point.y>=144&&point.y<=216)	//��ʽ9
			{
				Loopstatus=2;
				fight.Start("ini\\background1.ini",
					&Propertiy_lib1,&Propertiy_lib2,&Propertiy_lib1,
					"��ɫ��","��ɫ��","��ɫ��","��ɫ��");
			}
			else if(point.x>=72&&point.x<=144&&point.y>=144&&point.y<=216)	//��ʽ10
			{
				Loopstatus=2;
				fight.Start("ini\\background1.ini",
					&Propertiy_lib1,&Propertiy_lib2,&Propertiy_lib1,
					"��ɫ��","��ɫ��",NULL,"��ɫ��");
			}
			else if(point.x>=144&&point.x<=216&&point.y>=144&&point.y<=216)	//��ʽ11
			{
				Loopstatus=2;
				fight.Start("ini\\background1.ini",
					&Propertiy_lib1,&Propertiy_lib2,&Propertiy_lib1,
					"��ɫ��",NULL,NULL,"��ɫ��");
			}
			else if(point.x>=216&&point.x<=288&&point.y>=144&&point.y<=216)	//��ʽ12
			{
				Loopstatus=2;
				fight.Start("ini\\background1.ini",
					&Propertiy_lib1,&Propertiy_lib2,&Propertiy_lib1,
					NULL,"��ɫ��",NULL,NULL);
			}

/*				fight.Start("ini\\background1.ini",
					NULL,&Propertiy_lib2,&Propertiy_lib1,
					"��ɫ��","��ɫ��",NULL,"��ɫ��");*/
		}
		Blt(lpDDSBack,0,0,lpDDSBackGround,RectScreen,false);
		//Blt(lpDDSBack,0,0,fight.background,RectScreen,false);
		font.PrintText(lpDDSBack, 100, 250,"�����г����õļ��ַ�ʽ");
		font.PrintText(lpDDSBack, 100, 300,"���ڴ�����Ϸ�����Ľ��̣�sb��ɵĽ���!");
		font.PrintText(lpDDSBack, 100, 350,"ESC���˳�");
	}
	else if(Loopstatus==2)	//  ս��ϵͳ����ѭ��
	{
		Loopstatus=fight.Loop(mouse,point);
	}

	//������Ļ
	//(ע����Ϸ�е����ж�����ö���Blt��lpDDSBack,Ȼ��һ����µ���Ļ)
	UpdateScreen();
}