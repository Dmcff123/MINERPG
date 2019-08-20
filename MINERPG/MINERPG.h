#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <io.h>  
#include <fcntl.h>  
#include <process.h> 
#include <string>
#include <time.h>
#include <iostream>
#include <mmsystem.h>
#define PM SND_MEMORY|SND_ASYNC
#define BACKGROUNDCOLOR 0
#define GREEN 10
#define YELLOW 14
#define RED 12
#define BLUE 9
#define WHITE 15
#define CYAN 11
#define PURPLE 13
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define INC(x,n) (x)=(((x)+1)%(n))
#define DEC(x,n) (x)=(((x)+((n)-1))%(n))
#define AD 0
#define AP 1
#define RE 2
#define ATT 0
#define DEB 1
#define HPbar 0
#define MPbar 1
#define MVbar 2
#define ENEMYNUM 12 
using namespace std;
class role;
typedef struct buff{
	int duration;
	double ratio;	
}buff;
typedef struct status{
 	public:
 	bool who;//���� 
 	int classes;//ְҵ 
	int HPmax,HP,HPrec;//��������������������ظ� 
	int MPmax,MP,MPrec;//������������������ظ� 
	int atk,def;//�������������� 
	int abp,abr;//����ǿ�ȣ��������� 
	int spd,avd;//�ٶȣ����� 
	int crt,hit; //���������� 
	double move;//�ж��� 
	buff attribute[8];//����ǿ���������� 
	buff debuff[4];//��Ѫ��ȼ�գ��ж���ѣ��
	int skill;//������
	int lv;//�ȼ� 
	int cd[8];//��ȴ 
	int special;//���� 
	bool rec;//���� 
}status;
typedef struct skillpara{
	string name;
	string explain;
	int spend;
	int cd;
	void (*sp)(status*);	
}skillpara;//���ܲ��� 
typedef struct equip{
	int level;//�ȼ�
	int position;//λ�ã�������ͷ�������������ɣ��ֲ����㲿 
	int rare;//Ʒ�ʣ���ͨ�����ʣ�ϡ�У�ʷʫ����˵ 
	int type;//20,11,02,ذ��ǹ 	
	void newequip(int lv,int classes);
	void creat(int lv,int position,int rare,int type);
	bool showname(bool nom);
	void showexplain();
	void paraset(status* p);
	void effect(status* p);
}equip;//װ������ 
class role{
	private:
	int classes;//ְҵ 
	int level;//�ȼ� 
	int exp;// ���� or ���뾭�� 
	int vitality;//���� 
	int wit;//����
	int strength;//����  
	int spirit;//���� 
	int agility;//���� 
	int insight;//���� 
	int skillnum;//������ 
	equip equiplist[6];//װ�� 
	public:
	char name[9];//���� 
	int rank;//������� 
	void creat();
	void creat(int r,int lv,int st,int vi,int wi,int sp,int ag,int in);
	void createnemy(int rank);
	bool save();
	bool load(string);
	void display(int,bool re=true);
	int returnlv();
	int returnexp();
	equip returnequ(int);
	bool victory();
	bool defeat();
	void getexp(int);
	void levelup();
	void resetpoint();
	void explainequip();
	bool changeequ(equip);
	void showequip(); 
	status battlestatus(bool);
	//
	void (*sskp)();
	void (*opp)(status*);
};
void setbgm(int);
void gotoxy(int x, int y);
void color(int c);
void color(int c,int b);
bool space_esc();
void initialize();
int menu(); 
void start(int);
bool illustration(bool);
void drawmenu();
void drawboard();
bool hitthat(double);
int choose(int n,string* p);
int choose(int n,string* p,string* explain,int k=0);
int skillchoose(status* p,int n,string* name,string* explain);
void drawbar(double);
void drawmvbar(double,bool);
void writenum(int,int);
bool battle();
void showskill();
void showmessage(string);
status* whoseturn(status*,status*);
status* turnstart(status*);
void turnend(status*);
bool operate(status*);
void setbuff(status*,int,int,int,double);
void dealbuff(status*);
int damage(status*,int,double,int);//˭���࣬���٣�Ŀ�� 
void showbar(status);
void showsta(status);
void showbuff(status);
string percent(double);
//���ܣ�սʿ 
void w_bloodsuck(status*);
void w_beatback(status*,double);
void w_0attack(status*);
void w_1charge(status*);
void w_2disarm(status*);
void w_3stone(status*);
void w_4cripple(status*);
void w_5shieldhit(status*);
void w_6bloodwake(status*);
void w_7rage(status*);
//���ܣ���ʦ
void m_manasuck(status*);
void m_phaseblink(status*);
void m_0attack(status*);
void m_1enchants(status*);
void m_2stormshieldl(status*);
void m_3snowstorm(status*);
void m_4icelance(status*);
void m_5mindblast(status*);
void m_6muse(status*);
void m_7manaburn(status*); 
//���ܣ��̿�
void a_doubledagger(status*);
void a_preparation(status*);
void a_0attack(status*); 
void a_1assassinate(status*);
void a_2blindingpowder(status*);
void a_3sneak(status*);
void a_4poisondagger(status*);
void a_5stickstrike(status*);
void a_6weakagent(status*);
void a_7fatalrhythm(status*);
//���ܣ�����ʦ
void c_vicious(status*);
void c_boundary(status*);
void c_0attack(status*); 
void c_1sectumsempra(status*);
void c_2blaze(status*);
void c_3fivepoisons(status*);
void c_4daemon(status*);
void c_5increase(status*);
void c_6imperio(status*);
void c_7summarycurse(status*);
//���ܣ���ǹ��
void s_showbullet(status*);
void s_burstbullet(status*);
void s_momentumshoot(status*);
void s_0attack(status*); 
void s_1quickfire(status*);
void s_2deadeyeshoot(status*);
void s_3tacticalcounter(status*);
void s_4interceptingshoot(status*);
void s_5quickreload(status*);
void s_6deathmarker(status*);
void s_7stormshoot(status*);
//���ܣ�Ӱ��ʿ
void d_shadowchop(status*);
void d_shadowstep(status*);
void d_0attack(status*);
void d_1shadowblade(status*);
void d_2curseshadow(status*);
void d_3triplechop(status*);
void d_4intoshadow(status*);
void d_5shadowdurance(status*);
void d_6bloodsacrifice(status*);
void d_7shadowswordcircle(status*);
//
void e_regenerate(status*);
void e_gaze(status*);
//�����趨 
void e_showsk(){return;}
void e1_op(status*);
void e1_attack(status*);
void e3_op(status*);
void e3_attack(status*);
void e3_sk(status*);
void e3_showsk();
void e4_showsk();
void e4_op(status*);
void e4_attack(status*);
void e5_showsk();
void e5_op(status*);
void e5_attack(status*);
void e6_showsk();
void e6_op(status*);
void e7_op(status*);
void e8_showsk();
void e8_op(status*);
void e8_attack(status*);
void e9_showsk();
void e9_op(status*);
void e10_showsk();
void e10_op(status*);
void e10_sk(status*,double);
void e10_attack(status*);
void e11_showsk();
void e11_op(status*);
void e11_sk(status*,double);
void e11_attack(status*);
void e12_showsk();
void e12_op(status*);
void e12_sk(status*,double);
void e12_attack(status*); 
//
