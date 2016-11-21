//********************************************
//	��Ʒ ��غ���
//  ������2000��7��07��
//********************************************
#include "..\gamelib\goldpoint2.h"
#include "..\interface\interface2.h"
#include "..\main.h"
#include "..\map.h"
#include "..\role.h"
#include "menu_inc.h"

int CGoods::MAX_GOODS=0;
stGoods *CGoods::GOODS=NULL;
RECT CGoods::GoodsRect;
int CGoods::PicWidth=24;
int CGoods::PicHeight=24;	//��ƷͼƬ�Ĵ�С

CGoods::CGoods()
{
	Select=-1;
}

CGoods::~CGoods()
{
	if( GOODS != NULL && MAX_GOODS > 0 ) 
	{
		_FREE(GOODS);
		MAX_GOODS=0;
	}
}

//��ȡ����
void CGoods::LoadWindowIni(char *filename, char *index)
{
	LoadListWindowIni(filename, index);

	//��Ʒ���ܴ���
	CIniSet Ini(filename);
	char* strFile = Ini.ReadText(index, "AboutWindowFile");
	char* strIndex = Ini.ReadText(index, "AboutWindowIndex");
	AboutWindow.LoadWindowIni(strFile, strIndex);
	_FREE(strFile);
	_FREE(strIndex);
	AboutWindow.dialogx-=32;
	AboutWindow.dialogy-=32;
	AboutWindow.dialogw+=64;
	AboutWindow.dialogh+=64;
}

//��ȡ�����б�
void CGoods::LoadGoodsIni(char *filename)
{
	char *index;
	char *temp;

	CIniSet Ini(filename);
	PicWidth=Ini.ReadInt( "��Ʒ", "Width" );
	PicHeight=Ini.ReadInt( "��Ʒ", "Height" );
	GoodsRect=GetRect(0,0,PicWidth, PicHeight);

	MAX_GOODS = Ini.GetContinueDataNum("��Ʒ�б�");
	GOODS=(stGoods *)realloc(GOODS, sizeof(stGoods)*MAX_GOODS);

	for(int i=0; i<MAX_GOODS; i++)
	{
		index=Ini.ReadText("��Ʒ�б�", i);

		GOODS[i].Id=Ini.ReadInt(index, "Id");		//�����ƷId
		
		//�����Ʒ����
		temp=Ini.ReadText(index, "Name");
		strcpy( GOODS[i].Name, temp);
		_FREE(temp);
		
		//�����Ʒ����
		temp=Ini.ReadText(index, "About");
		strcpy( GOODS[i].About, temp);
		_FREE(temp);

		GOODS[i].Class=Ini.ReadInt(index, "Class");

		GOODS[i].Money=Ini.ReadInt(index, "Money");			//��ֵ
		GOODS[i].Exp=Ini.ReadInt(index, "Exp");				//����
		GOODS[i].Hp=Ini.ReadInt(index, "Hp");				//����
		GOODS[i].MaxHp=Ini.ReadInt(index, "MaxHp");			//�������ֵ
		GOODS[i].Mp=Ini.ReadInt(index, "Mp");				//ħ��
		GOODS[i].MaxMp=Ini.ReadInt(index, "MaxMp");			//ħ�����ֵ

		GOODS[i].Attack=Ini.ReadInt(index, "Attack");		//����
		GOODS[i].AttackPer=Ini.ReadInt(index,"AttackPer");	//�����ٷֱ�
		GOODS[i].Defend=Ini.ReadInt(index, "Defend");		//����
		GOODS[i].DefendPer=Ini.ReadInt(index,"DefendPer");	//�����ٷֱ�

		GOODS[i].Magic=Ini.ReadInt(index, "MagicAct");		//ħ��
		GOODS[i].Stamina=Ini.ReadInt(index, "Stamina");		//����
		GOODS[i].Luck=Ini.ReadInt(index, "Luck");			//����
		GOODS[i].Speed=Ini.ReadInt(index, "Speed");			//����
		GOODS[i].Bp=Ini.ReadInt(index, "Bp");				//����
		GOODS[i].Ip=Ini.ReadInt(index, "Ip");				//����

		//������Ʒ��ͼƬ
		temp=Ini.ReadText(index, "PicFileName");
		strcpy( GOODS[i].PicFileName, temp);
		CreateBitmap( GOODS[i].Pic, PicWidth, PicHeight, temp);
		DDSetColorKey( GOODS[i].Pic, ColorKey );
		_FREE(temp);

		_FREE(index);
	}
}

//��ʾ��Ʒ�б���
void CGoods::ShowGoodsListWindow(LPDIRECTDRAWSURFACE surf, bool bShowWindow, int left, int top)
{
	int n;
	static int MouseY =-1;
	ShowListWindow(surf, bShowWindow, left, top);

	//����ƶ�ѡ��
	if( MouseY != point.y )
	{
		MouseY=point.y;
		if( point.x > x && point.x < x+Width-ScrollBar.Width &&
			point.y > y && point.y < y+Height )
		{
			Select=(point.y-y)/LineHeight + ScrollBar.CurNum;		//��ǰѡ��
			if( Select >= role[0].Propertiy.CurGoodsNum ) 
				Select=role[0].Propertiy.CurGoodsNum-1;				//�������������һ��
		}
	}

	//��ʾ��Ŀ����һҳ�����ʾһҳ��������ʾȫ��
	int shownum=(ScrollBar.PageNum<role[0].Propertiy.CurGoodsNum)?
			ScrollBar.PageNum:role[0].Propertiy.CurGoodsNum;

	for(int i=0; i<shownum; i++)
	{		
		n=ScrollBar.CurNum+i;
		//������ʾ
		if( n==Select )
		{
			//���²�����ʾ������
			if( ScrollBar.PageNum < ScrollBar.MaxNum-ScrollBar.MinNum )
				Bar(surf, x, y+LineHeight*i+2, x+Width-ScrollBar.Width, y+LineHeight*(i+1)-2, SelectColor);
			else
				Bar(surf, x, y+LineHeight*i+2, x+Width-1, y+LineHeight*(i+1)-2, SelectColor);
		}
		//��ʾʾ��ͼƬ
		Blt(surf, x, y+LineHeight*i, GOODS[role[0].Propertiy.Goods[n]].Pic, 
			GetRect(0, 0, PicWidth, LineHeight), true);
		//��Ӱ��ʾ����
		DWORD c=Font.GetColor();
		Font.SetColor(0);
		Font.PrintText(surf, x+Column[1].x+1, y+4+LineHeight*i+1, GOODS[role[0].Propertiy.Goods[n]].Name);
		Font.PrintText(surf, x+Column[3].x+1, y+4+LineHeight*i+1, "%5d", role[0].Propertiy.GoodsNum[n]);
		Font.SetColor(c);
		Font.PrintText(surf, x+Column[1].x, y+4+LineHeight*i, GOODS[role[0].Propertiy.Goods[n]].Name);
		Font.PrintText(surf, x+Column[3].x, y+4+LineHeight*i, "%5d", role[0].Propertiy.GoodsNum[n]);
	}

	//ѡ��
	if( mouse == LB_UP )
	{
		if( point.x > x && point.x < x+Width-ScrollBar.Width &&
			point.y > y && point.y < y+Height )
		{
			int sel=(point.y-y)/LineHeight + ScrollBar.CurNum;
			if( sel == Select )	//ʹ��
			{
				CMenu::Sound_Click.Play();
				UseGoods(sel);
				Menu.ReInitMenu();	//������Ļ
				if(Select!=(point.y-y)/LineHeight + ScrollBar.CurNum)
					Select =-1;
				return;
			}
		}
	}

	//ʹ��
	if( A_UP &&Select>-1)
	{
		if( role[0].Propertiy.CurGoodsNum > 0 )
		{
			CMenu::Sound_Click.Play();
			UseGoods(Select);
			Menu.ReInitMenu();	//������Ļ
			if(Select!=(point.y-y)/LineHeight + ScrollBar.CurNum)
				Select =-1;
			return;
		}
	}
	
	//��һ��
	if( DOWN_DOWN && Select < ScrollBar.MaxNum-1 )
	{
		Select++;
		CMenu::Sound_Change.Play();
		if( Select >= ScrollBar.CurNum + ScrollBar.PageNum )
		{
			Select = ScrollBar.CurNum+1;
			ScrollBar.SetCurNum(Select);
		}

		if( Select >= ScrollBar.MinNum + role[0].Propertiy.CurGoodsNum )
		{
			Select = ScrollBar.MinNum;
			ScrollBar.SetCurNum(Select);
		}
	}

	//��һ��
	if( UP_DOWN && Select > 0 )
	{
		Select--;
		CMenu::Sound_Change.Play();
		if( Select < ScrollBar.MinNum )
			Select = ScrollBar.MinNum;

		if( Select < ScrollBar.CurNum )
		{
			ScrollBar.SetCurNum(ScrollBar.CurNum-1);
		}
	}

}

//��ʾ��Ʒ˵��
void CGoods::ShowAboutWindow(LPDIRECTDRAWSURFACE surf, bool bShowWindow)
{
	AboutWindow.ShowWindow(surf, bShowWindow);
	//��ʾ˵������
	if(Select>-1)
		Font.PrintText(surf, AboutWindow.dialogx+34, AboutWindow.dialogy+34, GOODS[role[0].Propertiy.Goods[Select]].About);
}

//------------------------------------

//��ʼ������
void CGoods::Init(LPDIRECTDRAWSURFACE surf)
{
	ScrollBar.MinNum=0;
	ScrollBar.MaxNum=role[0].Propertiy.CurGoodsNum;

	GetGameSurface(surf);
	PopWindow(surf, PopWindowStyle, PopWindowStep);
	AboutWindow.ShowWindow(surf);
}

//�˵�ѭ��
void CGoods::DoMenu(LPDIRECTDRAWSURFACE surf, bool bShow)
{
	ShowAboutWindow(surf, bShow);
	ShowGoodsListWindow(surf, bShow);
}

//ʹ��һ����Ʒ
void CGoods::UseGoods(int sel)
{
	int goods=role[0].Propertiy.Goods[sel];
	if( role[0].Propertiy.CurGoodsNum > 0 )
	
		Blt(lpDDSBackGround, 0,0, lpDDSBack, RectScreen, false);

	int num=Menu.RoleSel.DoMenu(lpDDSBack);
	if( num != -1 )
	{
		//����Ч��
		if(!GoodEffect(goods, &role[num]))
		{
			char x[256];
			sprintf(x, "����Ʒ����ʹ��");
			GameMessage.DoMenu(lpDDSBack, x);
			return;
		}
		role[0].DelObject(GOODS[goods].Name, 1);
		ScrollBar.MinNum=0;
		ScrollBar.MaxNum=role[0].Propertiy.CurGoodsNum;
		
		//����������
		if( ScrollBar.MaxNum < ScrollBar.PageNum )
			ScrollBar.MaxNum = ScrollBar.PageNum;

		//��ǰλ������
		if( ScrollBar.CurNum > ScrollBar.MaxNum - ScrollBar.PageNum )
		{
			ScrollBar.CurNum = ScrollBar.MaxNum - ScrollBar.PageNum;
		}
		
		//��ǰλ������
		if( ScrollBar.MaxNum - ScrollBar.CurNum < ScrollBar.PageNum )
		{
			ScrollBar.CurNum = ScrollBar.MaxNum - ScrollBar.PageNum;
		}

		ScrollBar.CountNewRect();
	}
}

//ʹ����Ʒ�Ľ��
int CGoods::GoodEffect(int GoodNum, CRole *Role)
{
	if( GOODS[GoodNum].Class==GC_GOODS )//����
	{
		Role->Propertiy.Exp+=GOODS[GoodNum].Exp;		//����

		Role->Propertiy.MaxHp+=GOODS[GoodNum].MaxHp;	//�������ֵ
		Role->Propertiy.Hp+=GOODS[GoodNum].Hp;			//����
		if( Role->Propertiy.Hp > Role->Propertiy.MaxHp )
			Role->Propertiy.Hp = Role->Propertiy.MaxHp;

		Role->Propertiy.MaxMp+=GOODS[GoodNum].MaxMp;	//ħ�����ֵ
		Role->Propertiy.Mp+=GOODS[GoodNum].Mp;			//ħ��
		if( Role->Propertiy.Mp > Role->Propertiy.MaxMp )
			Role->Propertiy.Mp = Role->Propertiy.MaxMp;		

		Role->oldAttack+=GOODS[GoodNum].Attack;		//����
		Role->oldAttack = (int)(Role->oldAttack*(100.0+GOODS[GoodNum].AttackPer)/100.0f);

		Role->oldDefend+=GOODS[GoodNum].Defend;		//����
		Role->oldDefend = (int)(Role->oldDefend*(100.0+GOODS[GoodNum].DefendPer)/100.0f);
		Role->ReCalcPro();

		Role->Propertiy.Magic+=GOODS[GoodNum].Magic;		//ħ��

		Role->Propertiy.Stamina+=GOODS[GoodNum].Stamina;	//����
		Role->Propertiy.Luck+=GOODS[GoodNum].Luck;			//����
		Role->Propertiy.Speed+=GOODS[GoodNum].Speed;		//����
		Role->Propertiy.Bp+=GOODS[GoodNum].Bp;				//����
		Role->Propertiy.Ip+=GOODS[GoodNum].Ip;				//����
		return 1;
	}
	
	return 0;	
}

//��ȡ������
int CGoods::GetGoodsNum(char *name)
{
	for(int i=0; i<MAX_GOODS; i++)
	{
		if( strcmp(name, GOODS[i].Name)==0 )
			return i;
	}
	return -1;
}