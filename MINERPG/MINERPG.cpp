#include "MINERPG.h"
extern char men[];
extern char bat[];
extern char bat2[];
extern char bat3[];
extern char wta[];
extern char sta[];
extern char win[];
extern char los[];
extern char upp[];
extern char dow[];
extern char cho[];
extern char r_0[];
extern char r_1[];
extern char r_2[];
extern char r_3[];
extern char r_4[];
extern char r_5[];
extern char a_0[];
extern char a_1[];
extern char a_2[];
extern char a_3[];
extern char a_4[];
extern char a_5[];
extern char a_6[];
extern char m_0[];
extern char m_1[];
extern char m_2[];
extern char m_3[];
extern char m_4[];
extern char m_5[];
extern char m_6[];
extern char m_7[];
extern char w_0[];
extern char w_1[];
extern char w_2[];
extern char w_3[];
extern char w_4[];
extern char w_5[];
extern char w_6[];
extern char w_7[];
extern char c_0[];
extern char c_1[];
extern char c_2[];
extern char c_3[];
extern char c_4[];
extern char c_5[];
extern char c_6[];
extern char c_7[];
extern char s_0[];
extern char s_1[];
extern char s_2[];
extern char s_3[];
extern char s_6[];
extern char d_0[];
extern char d_1[];
extern char d_2[];
extern char d_3[];
extern char d_4[];
extern char d_5[];
extern char d_6[];
extern char d_7[];
//
int hpipe[2];
bool pvp,esc;
role myrole,enemyrole;
status player,enemy;
int mgeline,row;
double lastmvp,lastmve;
skillpara sl[6][8];
int bulletspend[8];
int magicnum[7] = {0x45,0x79,0x69,0x7A,0x6F,0x68,0x61};
string classesname[6]= {"սʿ","��ʦ","�̿�","����ʦ","��ǹ��","Ӱ��ʿ"};
//
const int rarecolor[6]= {WHITE,GREEN,CYAN,PURPLE,YELLOW,RED};
const string rarelist[6]= {"��ͨ","����","ϡ��","ʷʫ","��˵","����"};
const string metal[5]= {"����","����","����","����","ս��֮Ӱ"};
const string nonmetal[5]= {"ľ��","����","ʯӢ","����","Զ��֮��"};
const string cloth[5]= {"����","Ƥ��","����","����","�籩֮Ϣ"};
const string gem[5]= {"���","ˮ��","��ʯ","��ҫ","����֮��"};
//
const string positionlist[6]= {"����","ͷ��","����","����","�ֲ�","�㲿"};
const string weapon[6]= {"����","����","ذ��","����","����","̫��"};
const string head[3]= {"ͷ��","��ñ","Ŀ��"};
const string neck[3]= {"����","����","��׹"};
const string trunk[3]= {"����","����","����"};
const string hand[3]= {"����","����","��ָ"};
const string foot[3]= {"��ѥ","սѥ","��ѥ"};
//
void equip::newequip(int lv,int classes)
{
    level=lv;
    position=rand()%6;
    int r;
    r=rand()%100;
    if(lv>30&&r<1){PlaySound(r_5,NULL,PM);rare=5;}
    else if(r<5){PlaySound(r_4,NULL,PM);rare=4;}
    else if(r<10){PlaySound(r_3,NULL,PM);rare=3;}
    else if(r<15){PlaySound(r_2,NULL,PM);rare=2;}
    else if(r<20){PlaySound(r_1,NULL,PM);rare=1;}
    else {PlaySound(r_0,NULL,PM);rare=0;}
    if(position)type=rand()%3;
    else type=classes;
    if(rare==5)
    {
        level=myrole.returnlv();
        if(position)type=1;
    }
}
void equip::creat(int lv,int ra,int pos,int ty)
{
    level=lv;
    rare=ra;
    position=pos;
    type=ty;
}
bool equip::showname(bool nom)
{
    if(!level)return false;
    string name;
    if(rare==5)
    {
        switch(position)
        {
        case 0:
            name="������ɻ�"+weapon[type];
            break;
        case 1:
            name="������������";
            break;
        case 2:
            name="���������֮ʯ";
            break;
        case 3:
            name="����İ�Ӱ����";
            break;
        case 4:
            name="������ֻ�ָ��";
            break;
        case 5:
            name="��������֮ѥ";
            break;
        }
        if(nom)color(rarecolor[rare]);
        else color(BACKGROUNDCOLOR,rarecolor[rare]);
        cout<<name;
        return true;
    }
    switch(position)
    {
    case 0://����
    {
        if(type==0||type==2||type==4)
            name=metal[rare]+weapon[type];
        else
            name=nonmetal[rare]+weapon[type];
    }
    break;
    case 1://ͷ
    {
        if(type==0||type==2)
            name=metal[rare]+head[type];
        else
            name=cloth[rare]+head[type];
    }
    break;
    case 2://��
    {
        if(type==0)
            name=nonmetal[rare]+neck[type];
        else
            name=gem[rare]+neck[type];
    }
    break;
    case 3://��
    {
        if(type==0)
            name=metal[rare]+trunk[type];
        else
            name=cloth[rare]+trunk[type];
    }
    break;
    case 4://��
    {
        if(type==0)
            name=cloth[rare]+hand[type];
        else if(type==1)
            name=nonmetal[rare]+hand[type];
        else
            name=gem[rare]+hand[type];
    }
    break;
    case 5://��
    {
        if(type==0||type==2)
            name=cloth[rare]+foot[type];
        else
            name=metal[rare]+foot[type];
    }
    break;
    }
    if(nom)color(rarecolor[rare]);
    else color(BACKGROUNDCOLOR,rarecolor[rare]);
    cout<<name;
    return true;
}
void equip::showexplain()
{
    if(!level)return;
    double basenum;
    basenum=0.2*(rare==5?5:rare+1)*level;
    int a,b,n;
    n=(int)basenum;
    if(!n)n=1;
    b=n/2;
    a=n-b;
    if(rare!=5)
    {
        color(WHITE);
        cout<<"�ȼ�:"<<level;
    }
    else
    {
        color(WHITE);
        cout<<"�ȼ�:";
        color(RED);
        cout<<level;
    }
    color(WHITE);
    cout<<"��Ʒ��:";
    color(rarecolor[rare]);
    cout<<rarelist[rare];
    color(WHITE);
    cout<<"��λ��:";
    switch(position)
    {
    case 0:
    {
        cout<<"����������:";
        if(type==0)
        {
            cout<<"����+";
            cout<<n*3;
        }
        else if(type==1)
        {
            cout<<"��ǿ+";
            cout<<n*3;
        }
        else if(type==2)
        {
            cout<<"����+";
            cout<<a*3;
            cout<<"��";
            cout<<"����+";
            cout<<b*3;
        }
        else if(type==3)
        {
            cout<<"����+";
            cout<<a*3;
            cout<<"��";
            cout<<"��ǿ+";
            cout<<b*3;
        }
        else if(type==4)
        {
            cout<<"����+";
            cout<<a*3;
            cout<<"��";
            cout<<"����+";
            cout<<b*4;
        }
        else if(type==5)
        {
            cout<<"����+";
            cout<<a*3;
            cout<<"��";
            cout<<"�ٶ�+";
            cout<<b*3;
        }
    }
    break;
    case 1://ͷ
    {
        cout<<"ͷ��������:";
        if(type==0)
        {
            cout<<"����+";
            cout<<n*3;
        }
        else if(type==1)
        {
            cout<<"����+";
            cout<<a*3;
            cout<<"��";
            cout<<"����+";
            cout<<b*4;
        }
        else if(type==2)
        {
            cout<<"����+";
            cout<<n*4;
        }
    }
    break;
    case 2://��
    {
        cout<<"����������:";
        if(type==0)
        {
            cout<<"����+";
            cout<<n*20;
        }
        else if(type==1)
        {
            cout<<"����+";
            cout<<a*20;
            cout<<"��";
            cout<<"����+";
            cout<<b*20;
        }
        else if(type==2)
        {
            cout<<"����+";
            cout<<n*20;
        }
    }
    break;
    case 3://��
    {
        cout<<"���ɩ�����:";
        if(type==0)
        {
            cout<<"����+";
            cout<<n*2;
        }
        else if(type==1)
        {
            cout<<"����+";
            cout<<a*2;
            cout<<"��";
            cout<<"ħ��+";
            cout<<b*2;
        }
        else if(type==2)
        {
            cout<<"ħ��+";
            cout<<n*2;
        }
    }
    break;
    case 4://��
    {
        cout<<"�ֲ�������:";
        if(type==0)
        {
            cout<<"�����ָ�+";
            cout<<n*1;
        }
        else if(type==1)
        {
            cout<<"�����ָ�+";
            cout<<a*1;
            cout<<"��";
            cout<<"�����ָ�+";
            cout<<b*1;
        }
        else if(type==2)
        {
            cout<<"�����ָ�+";
            cout<<n*1;
        }
    }
    break;
    case 5://��
    {
        cout<<"�㲿������:";
        if(type==0)
        {
            cout<<"�ٶ�+";
            cout<<n*3;
        }
        else if(type==1)
        {
            cout<<"�ٶ�+";
            cout<<a*3;
            cout<<"��";
            cout<<"����+";
            cout<<b*4;
        }
        else if(type==2)
        {
            cout<<"����+";
            cout<<n*3;
        }
    }
    break;
    }
    if(rare==5)
    {
        cout<<"��Ч��:";
        switch(position)
        {
        case 0:
            cout<<"�غϿ�ʼʱ����δѣ����Եз���ɻ��ڵȼ�����ʵ�˺�";
            break;
        case 1:
            cout<<"ս����ʼʱ���Եз�ʩ��3�غ��˺����ڵȼ�������֢״";
            break;
        case 2:
            cout<<"ÿ��ս����һ�Σ�����ʱ��50%�������ͷ�������";
            break;
        case 3:
            cout<<"�غϽ���ʱ�����м���Ч�������غ�-1";
            break;
        case 4:
            cout<<"�غϽ���ʱ�����м���ʣ����ȴ�غ�-1";
            break;
        case 5:
            cout<<"�غϽ���ʱ������20%���ж���";
            break;
        }
    }
    cout<<"��";
}
void equip::paraset(status* p)
{
    if(!level)return;
    double basenum;
    basenum=0.2*(rare==5?5:rare+1)*level;
    int a,b,n;
    n=(int)basenum;
    if(!n)n=1;
    b=n/2;
    a=n-b;
    switch(position)
    {
    case 0://����
    {
        if(type==0)p->atk+=n*3;
        else if(type==1)p->abp+=n*3;
        else if(type==2)p->atk+=a*3,p->crt+=b*3;
        else if(type==3)p->atk+=a*3,p->abp+=b*3;
        else if(type==4)p->atk+=a*3,p->hit+=b*4;
        else if(type==5)p->atk+=a*3,p->spd+=b*3;
    }
    break;
    case 1://ͷ
    {
        if(type==0)p->crt+=n*3;
        else if(type==1)p->crt+=a*3,p->hit+=b*4;
        else if(type==2)p->hit+=n*4;
    }
    break;
    case 2://��
    {
        if(type==0)p->HPmax+=n*20;
        else if(type==1)p->HPmax+=a*20,p->MPmax+=b*20;
        else if(type==2)p->MPmax+=n*20;
    }
    break;
    case 3://��
    {
        if(type==0)p->def+=n*2;
        else if(type==1)p->def+=a*2,p->abr+=b*2;
        else if(type==2)p->abr+=n*2;
    }
    break;
    case 4://��
    {
        if(type==0)p->HPrec+=n*1;
        else if(type==1)p->HPrec+=a*1,p->MPrec+=b*1;
        else if(type==2)p->MPrec+=n*1;
    }
    break;
    case 5://��
    {
        if(type==0)p->spd+=n*3;
        else if(type==1)p->spd+=a*3,p->avd+=b*4;
        else if(type==2)p->avd+=n*4;
    }
    break;
    }
}
void equip::effect(status* p)
{
    if(!level)return;
    if(rare!=5)return;
    switch(position)
    {
    case 0://����
    {
        string s;
        status *e;
        if(p->who)
        {
            s=myrole.name;
            e=&enemy;
        }
        else
        {
            s=enemyrole.name;
            e=&player;
        }
        color(WHITE);
        showmessage(s+"��������������ɻ꣬�����ʵ�˺���");
        damage(e,RE,-p->lv,HPbar);
    }
    break;
    case 1://ͷ
    {
        string s;
        status *e;
        if(p->who)
        {
            s=myrole.name;
            e=&enemy;
        }
        else
        {
            s=enemyrole.name;
            e=&player;
        }
        color(WHITE);
        showmessage(s+"����������������䣬ʩ����Ѫ��ȼ�պ��ж���");
        for(int i=0; i<3; i++)
        {
            e->debuff[i].duration=3;
            e->debuff[i].ratio=p->lv;
        }
        dealbuff(e);
    }
    break;
    case 2://��
    {
        if(p->rec)
        {
            string s;
            if(p->who)s=myrole.name;
            else s=enemyrole.name;
            color(WHITE);
            showmessage(s+"����������������������");
            p->HP=p->HPmax/2;
            p->MP=p->MPmax/2;
            showbar(*p);
            p->rec=false;
        }
        else return;
    }
    break;
    case 3://��
    {
        string s;
        bool hit=false;
        if(p->who)s=myrole.name;
        else s=enemyrole.name;
        for(int i=0; i<8; i++)
            if(p->attribute[i].ratio<0)
                if(p->attribute[i].duration)
                {
                    hit=true;
                    p->attribute[i].duration--;
                }
        for(int i=0; i<4; i++)
            if(p->debuff[i].duration)
            {
                hit=true;
                p->debuff[i].duration--;
            }
        if(hit)
        {
            color(WHITE);
            showmessage(s+"������������İ�Ӱ������Ч�������غ�-1��");
        }
        dealbuff(p);
    }
    break;
    case 4://��
    {
        string s;
        bool hit=false;
        if(p->who)s=myrole.name;
        else s=enemyrole.name;
        for(int i=0; i<8; i++)if(p->cd[i])
            {
                hit=true;
                p->cd[i]--;
            }
        if(hit)
        {
            color(WHITE);
            showmessage(s+"��������������ֻأ�����ʣ����ȴ�غ�-1��");
        }
        dealbuff(p);
    }
    break;
    case 5://��
    {
        string s;
        if(p->who)s=myrole.name;
        else s=enemyrole.name;
        color(WHITE);
        showmessage(s+"���������������գ������ж�����");
        damage(p,RE,0.20,MVbar);
    }
    break;
    }
}
//
void role::creat()
{
    level=1;
    exp=0;
    skillnum=2;
    cout<<"�����½�ɫ����(�س�����,���10���ַ�,����ռ2�ַ�,�Ḳ��ͬ����ɫ!!!): ";
    cin>>name;
    cout<<"ѡ��ְҵ: ";
    string explain[6];
    explain[0]="սʿ��һ�ֹ��϶�ǿ���ְҵ������ӵ�нϸߵ�������������"
               "��ǿ������������ʹսʿ����ӭ�ӵ��˵Ĺ�����"
               "��ǿ�����������սʿ�������ӭͷʹ����"
               "սʿ�ó��ƻ����˵��������ݻٵ��˵Ļ��׺�ʹ������Ѫ"
               "�Ӷ��޷���Ȼ�ָ�������";
    explain[1]="��ʦ��һ�����ض�����ְҵ������ӵ�нϸߵ������;���"
               "��ʦ���Ŀ��Ʒ����ܴӸ��ַ������Ƶ��˵�������"
               "��ǿ��Ĺ���ħ���ܸ����˴�������"
               "��ʦ�ó��������˵ľ����ø��ַ������Ƶ��˺�ʹ����"
               "ȼ�մӶ��޷���Ȼ�ָ�������";
    explain[2]="�̿���һ������������ְҵ������ӵ�нϸߵ����ݺͶ��졣"
               "�̿��������ֿ���ʹ���ܵ��˵Ĺ����������ж���"
               "�����ߵı������������ô̿�˲��Ե�����������˺���"
               "�̿��ó����Ƶ��˵Ĺ������������������ع������˺�ʹ�ö�ҩ"
               "�Ե�������޷��ֵ����˺���";
    explain[3]="����ʦ��һ�ֶ񶾶��ֲ���ְҵ������ӵ�н�Ϊȫ������ԡ�"
               "����ʦ����ʹ�ø����õ�����������˺���������"
               "ͬʱ��ӵ�п����ó����˺�˲�䱬����ǿ��������"
               "����ʦ�ó����Ƶ��˵Ļظ�������������ɳ������˺���ȫ���"
               "�˺���������Ӧ�����ֵ��ˡ�";
    explain[4]="��ǹ����һ�ּ��¶�������ְҵ������ӵ�нϸߵĶ��졣"
               "��ǹ�������˸���������ɣ�����ͨ������˲�䱬�������˺���"
               "ͬʱ��ǿ����ж��������������Լ�������Ƶ����ж���"
               "��ǹ���ó�ͨ�������������������ˣ����ߵı�������"
               "���������ڵ��˷���֮ǰ������ܡ�";
    explain[5]="Ӱ��ʿ��һ��Σ�ն�����ְҵ������ӵ�нϸߵ������;���"
               "Ӱ��ʿ������ħ����ն������������;����ϵ�˫���˺���"
               "ͨ�����صİ�Ӱħ���ܼ����ǿ�����������Ƶ��˵�ʩ����"
               "Ӱ��ʿ�ó�ͨ�����а�Ӱ֮����ն����ʳ���˵������뾫��"
               "��ӵ�о����±�ˮһս��������";
    classes=choose(6,classesname,explain);
    switch(classes)
    {
    case 0://սʿ
        strength=vitality=8;
        wit=spirit=5;
        agility=insight=5;
        break;
    case 1://��ʦ
        strength=vitality=5;
        wit=spirit=8;
        agility=insight=5;
        break;
    case 2://�̿�
        strength=vitality=5;
        wit=spirit=5;
        agility=insight=8;
        break;
    case 3://����ʦ
        strength=vitality=6;
        wit=spirit=6;
        agility=insight=6;
        break;
    case 4://��ǹ��
        strength=vitality=5;
        wit=spirit=5;
        agility=6;
        insight=10;
        break;
    case 5://Ӱ��ʿ 
        vitality=wit=5;
        strength=spirit=8;
        agility=insight=5;
        break;
    }
    rank=0;
    memset(equiplist,0,sizeof(equiplist));
    if(!strcmp(name,"Eyizoha"))
    {
        equiplist[0].creat(1,5,0,classes);
        for(int i=1; i<6; i++)equiplist[i].creat(1,5,i,1);
    }
}
void role::creat(int r,int ra,int vi,int wi,int st,int sp,int ag,int in)
{
    classes=-1;
    level=ra+1;
    exp=2*level-1;
    strength=r*st;
    vitality=r*vi;
    wit=r*wi;
    spirit=r*sp;
    agility=r*ag;
    insight=r*in;
    memset(equiplist,0,sizeof(equiplist));
}
void role::createnemy(int rank)
{
	int r,n;
	n=rank%ENEMYNUM+1;r=rank/ENEMYNUM+1;
	//00|01,10|12,20|22,30|32,40|42,50|52 
	//��|ǿ,��|��,��|��,��|��,��|��,��|�� 
	switch(n)
	{
		case 1:
			this->creat(r,rank,5,0,4,4,4,4);
	    	strcpy(this->name,"����");
	   		this->sskp=e_showsk;
			this->opp=e1_op;
   		break;
   		case 2:
			this->creat(r,rank,6,0,5,5,5,5);
	    	strcpy(this->name,"ǿ������");
	   		this->sskp=e_showsk;
			this->opp=e1_op;
   		break;
   		case 3:
			this->creat(r,rank,7,0,6,6,6,6);
	    	strcpy(this->name,"��������");
	   		this->sskp=e3_showsk;
			this->opp=e1_op;
   		break;
   		case 4:
			this->creat(r,rank,9,2,8,5,5,5);
	    	strcpy(this->name,"������ʿ");
	   		this->sskp=e4_showsk;
			this->opp=e4_op;
   		break;
   		case 5:
			this->creat(r,rank,7,8,2,8,5,6);
	    	strcpy(this->name,"�ҽ�ʬ��");
	   		this->sskp=e5_showsk;
			this->opp=e5_op;
			this->equiplist[3].creat(4*r,4,3,0);
   		break;
   		case 6:
			this->creat(r,rank,7,0,8,6,10,6);
	    	strcpy(this->name,"��������");
	   		this->sskp=e3_showsk;
			this->opp=e6_op;
   		break;
   		case 7:
			this->creat(r,rank,7,4,4,8,6,6);
	    	strcpy(this->name,"���ʬ��");
	   		this->sskp=e_showsk;
			this->opp=e7_op;
			this->equiplist[3].creat(4*r,4,3,0);
   		break;
   		case 8:
			this->creat(r,rank,9,4,8,4,2,6);
	    	strcpy(this->name,"������ʿ");
	   		this->sskp=e8_showsk;
			this->opp=e8_op;
			this->equiplist[5].creat(6*r,4,5,0);
   		break;
   		case 9:
			this->creat(r,rank,7,6,6,4,10,10);
	    	strcpy(this->name,"������Ӱ");
	   		this->sskp=e9_showsk;
			this->opp=e9_op;
			this->equiplist[0].creat(10*r,4,0,0);
   		break;
   		case 10:
			this->creat(r,rank,8,8,8,8,8,8);
	    	strcpy(this->name,"��Ѫ����");
	   		this->sskp=e10_showsk;
			this->opp=e10_op;
   		break;
   		case 11:
			this->creat(r,rank,12,6,4,4,6,6);
	    	strcpy(this->name,"����ʯ��");
	   		this->sskp=e11_showsk;
			this->opp=e11_op;
			this->equiplist[3].creat(16*r,4,3,1);
   		break;
   		case 12:
			this->creat(r,rank,10,2,6,6,10,10);
	    	strcpy(this->name,"�߷�Ů��");
	   		this->sskp=e12_showsk;
			this->opp=e12_op;
			this->equiplist[3].creat(18*r,4,2,2);
   		break;
	}
}
bool role::save()
{
    FILE *fp;
    role p;
    do
    {
        fp=fopen(name,"wb");
        if(fp==NULL)return false;
        fwrite(this,sizeof(role),1,fp);
        fclose(fp);
        fp=fopen(name,"rb");
        fread(&p,sizeof(role),1,fp);
        fclose(fp);
    }
    while(memcmp(&p,this,sizeof(role)));
    return true;
}
bool role::load(string str)
{
    FILE *fp;
    fp=fopen(str.c_str(),"rb");
    if(fp==NULL)return false;
    fread(this,sizeof(role),1,fp);
    fclose(fp);
    return true;
}
int role::returnlv()
{
    return level;
}
int role::returnexp()
{
    return exp;
}
equip role::returnequ(int i)
{
    return equiplist[i];
}
void role::display(int y,bool re)
{
    if(re)
    {
        color(WHITE);
        gotoxy(0,y+0);
        cout<<"����ɫ��Ϣ���������������ש�����������������������������������������������������������������������������������������������";
        gotoxy(0,y+1);
        cout<<"������:                 ������:          ����:          ����:          ����:          ����:          ����:              ��";
        gotoxy(0,y+2);
        cout<<"��ְҵ:                 ��װ��:                                                                                         ��";
        gotoxy(0,y+3);
        cout<<"���ȼ�:                 �ǩ�����������������������������������������������������������������������������������������������";
        gotoxy(0,y+4);
        cout<<"������:                 ����������:                                                                                     ��";
        gotoxy(0,y+5);
        cout<<"��ͨ�صȼ�:             ����������:                                                                                     ��";
        gotoxy(0,y+6);
        cout<<"�������������������������ߩ�����������������������������������������������������������������������������������������������";
        //
        gotoxy(7,y+1);
        cout<<name;
        //
        gotoxy(7,y+2);
        cout<<classesname[classes];
        //װ��
        gotoxy(31,y+2);
        for(int i=0; i<6; i++)if(equiplist[i].showname(true)&&i!=5)cout<<" ";
        //
        color(WHITE);
        gotoxy(7,y+3);
        cout<<level;
        //
        gotoxy(7,y+4);
        cout<<exp<<"/"<<level*level;
        gotoxy(35,y+4);
        switch(classes)
        {
        case 0://սʿ
            cout<<"������־ ";
            if(level>=4)cout<<"��Ѫ ";
            if(level>=10)cout<<"�ͻ� ";
            break;
        case 1://��ʦ
            cout<<"�ǻ��⾵ ";
            if(level>=4)cout<<"�ȷ� ";
            if(level>=10)cout<<"��λת�� ";
            break;
        case 2://�̿�
            cout<<"�̿ͱ��� ";
            if(level>=4)cout<<"˫ذ ";
            if(level>=10)cout<<"�Ż����� ";
            break;
        case 3://����ʦ
            cout<<"������Լ ";
            if(level>=4)cout<<"�� ";
            if(level>=10)cout<<"������� ";
            break;
        case 4://��ǹ��
            cout<<"����רע ";
            if(level>=4)cout<<"�����ӵ� ";
            if(level>=10)cout<<"������� ";
            break;
        case 5://Ӱ��ʿ 
            cout<<"Ӱ��Ѫͳ ";
            if(level>=4)cout<<"նӰ ";
            if(level>=10)cout<<"��Ӱ�� ";
            break;
        }
        //
        gotoxy(11,y+5);
        cout<<rank;
        gotoxy(35,y+5);
        for(int i=0; i<skillnum; i++)cout<<sl[classes][i].name<<" ";
    }
    gotoxy(31,y+1);
    cout<<vitality;
    gotoxy(46,y+1);
    cout<<wit;
    gotoxy(61,y+1);
    cout<<strength;
    gotoxy(76,y+1);
    cout<<spirit;
    gotoxy(91,y+1);
    cout<<agility;
    gotoxy(106,y+1);
    cout<<insight;
    gotoxy(0,y+7);
}
bool role::victory()
{
    rank++;
    system("cls");
    display(0);
    PlaySound(win,NULL,PM);
    color(GREEN);
    cout<<"ս��ʤ����\n";
    color(WHITE);
    getexp(enemyrole.returnexp());
    space_esc();
    //
    if(hitthat(0.6))
    {
        system("cls");
        display(0);
        color(GREEN);
        cout<<"�����װ����\n";
        color(WHITE);
        equip equ;
        equ.newequip(enemyrole.returnlv(),classes);
        equ.showname(true);
        cout<<"\n";
        equ.showexplain();
        cout<<"\n";
        if(!changeequ(equ))return false;
    }
    //
    while(1)
    {
        system("cls");
        display(0);
        gotoxy(0,39);
        if(save())cout<<"���ȱ���ɹ���";
        else cout<<"���ȱ���ʧ�ܣ�";
        gotoxy(0,40);
        cout<<"ѡ�����:";
        string list[4]= {"������ս","�鿴װ��","�������Ե�","���ز˵�"};
        switch(choose(4,list))
        {
        case 0:
            return true;
        case 1:
            explainequip();
            break;
        case 2:
            resetpoint();
            break;
        case 3:
            return false;
        default:
            return false;
        }
    }
}
bool role::defeat()
{
    PlaySound(los,NULL,PM);
    system("cls");
    display(0);
    color(RED);
    cout<<"ս��ʧ�ܣ�\n";
	color(WHITE);
    cout<<"ʧȥ"<<enemyrole.returnlv()<<"�㾭�顣\n";
    exp-=enemyrole.returnlv();if(exp<0)exp=0; 
    space_esc();
    while(1)
    {
        system("cls");
        display(0);
        gotoxy(0,39);
        if(save())cout<<"���ȱ���ɹ���";
        else cout<<"���ȱ���ʧ�ܣ�";
        gotoxy(0,40);
        cout<<"ѡ�����:";
        string list[5]= {"������ս","��ս��һ��","�鿴װ��","�������Ե�","���ز˵�"};
        switch(choose(5,list))
        {
        case 0:
            return true;
        case 1:
            if(rank)rank--;
            return true;
        case 2:
            explainequip();
            break;
        case 3:
            resetpoint();
            break;
        case 4:
            return false;
        default:
            return false;
        }
    }
}
void role::getexp(int ex)
{
    cout<<"���"<<ex<<"�㾭�顣\n";
    exp+=ex;
    cout<<"����/�¼�����:"<<exp<<"/"<<level*level;
    while(exp>=(level*level))levelup();
}
void role::resetpoint()
{
    system("cls");
    int point=level;
    if(point==1)
    {
        display(0);
        return;
    }
    switch(classes)
    {
    case 0://սʿ
        strength=vitality=8;
        wit=spirit=5;
        agility=insight=5;
        break;
    case 1://��ʦ
        strength=vitality=5;
        wit=spirit=8;
        agility=insight=5;
        break;
    case 2://�̿�
        strength=vitality=5;
        wit=spirit=5;
        agility=insight=8;
        break;
    case 3://����ʦ
        strength=vitality=6;
        wit=spirit=6;
        agility=insight=6;
        break;
    case 4://��ǹ��
        strength=vitality=5;
        wit=spirit=5;
        agility=6;
        insight=10;
        break;
    case 5://Ӱ��ʿ 
        vitality=wit=5;
        strength=spirit=8;
        agility=insight=5;
        break;
    }
    display(0);
    color(WHITE);
    switch(classes)
    {
    case 0://սʿ
        cout<<"������־:ÿ�������������10��������2��ħ����";
        break;
    case 1://��ʦ
        cout<<"�ǻ��⾵:ÿ�������������1�㷨ǿ��4�����С�";
        break;
    case 2://�̿�
        cout<<"�̿ͱ���:ÿ�����ݶ������1�㹥����1���ٶȣ�ÿ�㶴��������2�����ܡ�";
        break;
    case 3://����ʦ
        cout<<"������Լ:ÿ�������������2�㷨ǿ��ÿ�㾫��������2�㹥����";
        break;
    case 4://��ǹ��
        cout<<"����רע:ÿ�㶴��������1�㹥����1���ٶȺ�1�����С�";
        break;
    case 5://Ӱ��ʿ 
        cout<<"Ӱ��Ѫͳ:ÿ�������������10��������ÿ�㾫��������10�㷨����";
        break;
    }
    CONSOLE_SCREEN_BUFFER_INFO xy;
    int k=0;
    cout<<"\nѡ����������(";
    string list[6]= {"����","����","����","����","����","����"};
    string explain[6];
    explain[0]="ÿ�������������20���������ֵ��1�������ָ���";
    explain[1]="ÿ�������������20�������ֵ��1�㷨���ָ���";
    explain[2]="ÿ�������������3�㹥����2�㻤�ס�";
    explain[3]="ÿ�㾫��������3�㷨ǿ��2��ħ����";
    explain[4]="ÿ�����ݿ������3���ٶȺ�4�����ܡ�";
    explain[5]="ÿ�㶴��������3�㱩����4�����С�";
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &xy);
    while(--point)
    {
        cout<<point<<"):";
        switch(k=choose(6,list,explain,k))
        {
        case 0://����
            vitality++;
            break;
        case 1://����
            wit++;
            break;
        case 2://����
            strength++;
            break;
        case 3://����
            spirit++;
            break;
        case 4://����
            agility++;
            break;
        case 5://����
            insight++;
            break;
        }
        display(0,false);
        gotoxy(xy.dwCursorPosition.X,xy.dwCursorPosition.Y);
    }
    gotoxy(xy.dwCursorPosition.X,xy.dwCursorPosition.Y);
    cout<<point<<"):";
}
void role::explainequip()
{
    system("cls");
    display(0);
    int t=0,i=0,n=0;
    for(i=0; i<6; i++)if(equiplist[i].level)n++;
    if(!n)return;
    char ch=0;
    bool ar;
    CONSOLE_SCREEN_BUFFER_INFO xy;
    cout<<"�ո������װ����ESC�����ء�\n";
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &xy);
    while(!equiplist[t].level)INC(t,6);
    while(1)
    {
        gotoxy(xy.dwCursorPosition.X,xy.dwCursorPosition.Y);
        for(i=0; i<6; i++)
        {
            ar=false;
            if(i==t)ar=equiplist[i].showname(false);
            else ar=equiplist[i].showname(true);
            color(WHITE);
            if(ar)cout<<" ";
        }
        gotoxy(0,xy.dwCursorPosition.Y+1);
        cout<<"                                                                                                                          ";
        gotoxy(0,xy.dwCursorPosition.Y+1);
        equiplist[t].showexplain();
        ch=getch();
        if(ch==0)ch=getch();
        if(ch==LEFT)do
            {
                DEC(t,6);
            }
            while(!equiplist[t].level);
        if(ch==RIGHT)do
            {
                INC(t,6);
            }
            while(!equiplist[t].level);
        if(ch==' ')
        {
            gotoxy(0,xy.dwCursorPosition.Y+2);
            color(RED);
            cout<<"ȷ��������";
            string list[2]= {"��","��"};
            switch(choose(2,list))
            {
            case 0:
                break;
            case 1:
                equiplist[t].level=0;
                equiplist[t].rare=0;
                n--;
                if(!n)return;
                do
                {
                    INC(t,6);
                }
                while(!equiplist[t].level);
                gotoxy(xy.dwCursorPosition.X,xy.dwCursorPosition.Y);
                cout<<"                                                                                                                          ";
                break;
            default:
                return;
            }
            gotoxy(0,xy.dwCursorPosition.Y+2);
            cout<<"               ";
            display(0);
        }
        if(ch==0x1B)return;
    }
}
void role::levelup()
{
    CONSOLE_SCREEN_BUFFER_INFO xy;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &xy);
    color(YELLOW);
    level++;
    //
    for(int i=0; i<6; i++)if(equiplist[i].rare==5)equiplist[i].level=level;
    //
    if((level%2==0)&&(1<=(level/2))&&((level/2)<=8))
    {
        if(level!=4&&level!=10)skillnum++;
        cout<<"\n�ȼ�����!ϰ���¼���!\n";
    }
    else cout<<"\n�ȼ�����!           \n";
    //
    color(WHITE);
    switch(classes)
    {
    case 0://սʿ
        cout<<"������־:ÿ�������������10��������2��ħ����";
        break;
    case 1://��ʦ
        cout<<"�ǻ��⾵:ÿ�������������1�㷨ǿ��4�����С�";
        break;
    case 2://�̿�
        cout<<"�̿ͱ���:ÿ�����ݶ������1�㹥����1���ٶȣ�ÿ�㶴��������2�����ܡ�";
        break;
    case 3://����ʦ
        cout<<"������Լ:ÿ�������������2�㷨ǿ��ÿ�㾫��������2�㹥����";
        break;
    case 4://��ǹ��
        cout<<"����רע:ÿ�㶴��������1�㹥����1���ٶȺ�1�����С�";
        break;
    case 5://Ӱ��ʿ 
        cout<<"Ӱ��Ѫͳ:ÿ�������������10��������ÿ�㾫��������10�㷨����";
        break;
    }
    cout<<"\nѡ����������: ";
    string list[6]= {"����","����","����","����","����","����"};
    string explain[6];
    explain[0]="ÿ�������������20���������ֵ��1�������ָ���";
    explain[1]="ÿ�������������20�������ֵ��1�㷨���ָ���";
    explain[2]="ÿ�������������3�㹥����2�㻤�ס�";
    explain[3]="ÿ�㾫��������3�㷨ǿ��2��ħ����";
    explain[4]="ÿ�����ݿ������3���ٶȺ�4�����ܡ�";
    explain[5]="ÿ�㶴��������3�㱩����4�����С�";
    switch(choose(6,list,explain))
    {
    case 0://����
        vitality++;
        break;
    case 1://����
        wit++;
        break;
    case 2://����
        strength++;
        break;
    case 3://����
        spirit++;
        break;
    case 4://����
        agility++;
        break;
    case 5://����
        insight++;
        break;
    }
    display(0);
    gotoxy(xy.dwCursorPosition.X,xy.dwCursorPosition.Y);
}
bool role::changeequ(equip equ)
{
    if(equiplist[equ.position].level)
    {
        string list[2]= {"��","��"};
        color(WHITE);
        cout<<"�Ƿ��滻����װ��: ";
        CONSOLE_SCREEN_BUFFER_INFO xy;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &xy);
        cout<<"\n";
        equiplist[equ.position].showname(true);
        cout<<"\n";
        equiplist[equ.position].showexplain();
        gotoxy(xy.dwCursorPosition.X,xy.dwCursorPosition.Y);
        switch(choose(2,list))
        {
        case 0:
            break;
        case 1:
            equiplist[equ.position]=equ;
            break;
        default:
            return false;
        }
    }
    else
    {
        string list[2]= {"��","��"};
        color(RED);
        cout<<"�Ƿ�װ��: ";
        color(WHITE);
        switch(choose(2,list))
        {
        case 0:
            equiplist[equ.position]=equ;
            break;
        case 1:
            break;
        default:
            return false;
        }
    }
    display(0);
    return true;
}
void role::showequip()
{
    for(int i=0; i<6; i++)
    {
        gotoxy(93,35+i);
        equiplist[i].showname(true);
    }
}
status role::battlestatus(bool who)
{
    status me;
    me.who=who;
    me.classes=classes;
    me.HPmax=100+vitality*20;
    me.HPrec=vitality;
    me.MPmax=20+wit*20;
    me.MPrec=wit;
    me.atk=5+strength*3;
    me.def=strength*2;
    me.abp=5+spirit*3;
    me.abr=spirit*2;
    me.spd=5+agility*3;
    me.avd=agility*4;
    me.crt=5+insight*3;
    me.hit=insight*4;
    //
    switch(classes)
    {
		case 0://������־:ÿ�������������10��������2��ħ����
        me.HPmax+=vitality*10;
        me.abr+=vitality*2;
        break;
		case 1://�ǻ��⾵:ÿ�������������1�㷨ǿ��4������
        me.abp+=wit;
        me.hit+=wit*4;
        break;
		case 2://�̿ͱ���:ÿ�����ݶ������1�㹥����1���ٶȣ�ÿ�㶴��������2������
        me.atk+=agility;
        me.spd+=agility;
        me.avd+=insight*2;
        break;
		case 3://������Լ:ÿ�������������2�㷨ǿ��ÿ�㾫��������2�㹥��
        me.abp+=strength*2;
        me.atk+=spirit*2;
        break;
		case 4://����רע:ÿ�㶴��������1�㹥��,1���ٶȺ�1������ 
        me.atk+=insight;
        me.spd+=insight;
        me.hit+=insight; 
        break;
        case 5://Ӱ��Ѫͳ:ÿ�������������10��������ÿ�㾫��������10�㷨��
        me.HPmax+=strength*10;
        me.MPmax+=spirit*10;
        break;
    }
    //
    me.move=0;
    memset(me.attribute,0,sizeof(me.attribute));
    memset(me.debuff,0,sizeof(me.debuff));
    me.skill=skillnum;
    me.lv=level;
    memset(me.cd,0,8*sizeof(int));
    for(int i=0; i<6; i++)equiplist[i].paraset(&me);
    me.HP=me.HPmax;
    me.MP=me.MPmax;
    me.special=6;
    me.rec=true;
    return me;
}
//
int main(int argc,char* argv[])
{  
	char hstr[20];  
	int pid, problem, c;  
	int termstat; 
	if(argc==1)
    {
    	//
		setvbuf(stdout,NULL,_IONBF,0);
		if(_pipe(hpipe,256,O_BINARY)==-1)exit(1);
		itoa(hpipe[0],hstr,10);  
		if((pid=spawnl(P_NOWAIT,argv[0],argv[0],hstr,NULL))==-1)exit(1);
		//
	    system("mode 122,41");
	    system("title Eyizoha QQ779381838");
	    color(WHITE,BACKGROUNDCOLOR);
	    system("cls");
	    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	    CONSOLE_CURSOR_INFO cci;
	    GetConsoleCursorInfo(hOut,&cci);
	    cci.bVisible=false;
	    SetConsoleCursorInfo(hOut,&cci);
	    srand(time(NULL));
		srand(time(NULL)*magicnum[rand()%7]);
	    initialize();
	    while(1){start(menu());}
    }
	else
	{
		system("title BGM");
		int bgm;
		hpipe[0]=atoi(argv[1]);
		while(1)
		{
			if(read(hpipe[0],&bgm,sizeof(int)))
			{
				switch(bgm)
				{
					case -1:exit(0);
					case 0:PlaySound(NULL,NULL,PM);break;
					case 1:PlaySound(men,NULL,PM|SND_LOOP);break;
					case 2:PlaySound(wta,NULL,PM|SND_LOOP);break;
					case 3:PlaySound(bat,NULL,PM|SND_LOOP);break;
					case 4:PlaySound(bat2,NULL,PM|SND_LOOP);break;
					case 5:PlaySound(bat3,NULL,PM|SND_LOOP);break;
				}
			}
			Sleep(100);
		}
	}
}
void setbgm(int b)
{
	int bgm=b;
	write(hpipe[1],&bgm,sizeof(int));
}
void start(int t)
{
    if(t==0)
    {
        color(WHITE);
        system("cls");
        gotoxy(0,0);
        myrole.creat();
        if(myrole.save())
        {
            cout<<"\n��ɫ����ɹ���";
            Sleep(500);
        }
        else
        {
            cout<<"\n��ɫ����ʧ�ܣ�";
            Sleep(500);
        }
    }
    else if(t==1)
    {
        string s,n;
        bool p=true;
        while(p)
        {
            color(WHITE);
            system("cls");
            gotoxy(0,0);
            cout<<"������Ҫ��ȡ��ɫ���֣��س�ȷ��(��ɫ�浵����ڱ���������Ŀ¼��): ";
            cin>>s;
            if(myrole.load(s))
            {
                n=myrole.name;
                if(s==n)
                {
                    cout<<"��ɫ��ȡ�ɹ���";
                    p=false;
                    Sleep(500);
                }
                else
                {
                    cout<<"��ɫ��ȡʧ�ܣ�";
                    Sleep(500);
                }
            }
            else
            {
                cout<<"��ɫ��ȡʧ�ܣ�";
                Sleep(500);
            }
        }
    }
    else if(t==2)
    {
        pvp=true;
        string s,n;
        bool p=true;
        while(p)
        {
            color(WHITE);
            system("cls");
            gotoxy(0,0);
            cout<<"����һ����ҵĽ�ɫ���֣��س�ȷ��(��ɫ�浵����ڱ���������Ŀ¼��): ";
            cin>>s;
            if(myrole.load(s))
            {
                n=myrole.name;
                if(s==n)
                {
                    cout<<"��ɫ��ȡ�ɹ���";
                    p=false;
                    Sleep(500);
                }
                else
                {
                    cout<<"��ɫ��ȡʧ�ܣ�";
                    Sleep(500);
                }
            }
            else
            {
                cout<<"��ɫ��ȡʧ�ܣ�";
                Sleep(500);
            }
        }
        p=true;
        while(p)
        {
            color(WHITE);
            system("cls");
            gotoxy(0,0);
            cout<<"���������ҵĽ�ɫ���֣��س�ȷ��(��ɫ�浵����ڱ���������Ŀ¼��): ";
            cin>>s;
            if(enemyrole.load(s))
            {
                n=enemyrole.name;
                if(s==n)
                {
                    cout<<"��ɫ��ȡ�ɹ���";
                    p=false;
                    Sleep(500);
                }
                else
                {
                    cout<<"��ɫ��ȡʧ�ܣ�";
                    Sleep(500);
                }
            }
            else
            {
                cout<<"��ɫ��ȡʧ�ܣ�";
                Sleep(500);
            }
        }
    }
    setbgm(2);
    PlaySound(sta,NULL,PM);
    bool ctn;
    if(pvp)
    {
        system("cls");
        gotoxy(0,40);
        cout<<"���ո����ʼս����ESC�����ز˵���";
        myrole.display(20);
        gotoxy(60,19);
        cout<<"VS";
        enemyrole.display(12);
        ctn=space_esc();
    }
    else
    {
        bool brk=true;
        while(brk)
        {
            system("cls");
            myrole.display(0);
            gotoxy(0,39);
            if(myrole.save())cout<<"���ȱ���ɹ���";
            else cout<<"���ȱ���ʧ�ܣ�";
            gotoxy(0,40);
            cout<<"ѡ�����:";
            string list[4]= {"��ʼ��ս","�鿴װ��","�������Ե�","���ز˵�"};
            switch(choose(4,list))
            {
            case 0:
                ctn=true;
                brk=false;
                break;
            case 1:
                myrole.explainequip();
                break;
            case 2:
                myrole.resetpoint();
                break;
            case 3:
                ctn=false;
                brk=false;
                break;
            default:
                ctn=false;
                brk=false;
                break;
            }
        }
    }
    while(ctn)
    {
        if(!pvp)
        {
            enemyrole.createnemy(myrole.rank);
            if(battle())ctn=myrole.victory();
            else ctn=myrole.defeat();
        }
        if(pvp)
        {
            battle();
            system("cls");
            myrole.display(20);
            gotoxy(60,19);
            cout<<"VS";
            enemyrole.display(12);
            gotoxy(0,40);
            cout<<"���ո������ս����ESC�����ز˵���";
            ctn=space_esc();
        }
    }
    pvp=false;
}
int menu()
{
	setbgm(1);
    drawmenu();
    int t=0,i;
    char ch=0;
    bool show=false;
    string p[4]= {" �½���ɫ "," ��ȡ��ɫ "," ��Ҷ�ս "," ��Ϸ˵�� "};
    while(1)
    {

        color(WHITE,4);
        for(i=0; i<4; i++)
        {
            gotoxy(56,19+i);
            if(i==t)color(4,WHITE);
            cout<<p[i];
            color(WHITE,4);
        }
        ch=getch();
        if(ch==0)ch=getch();
        if(ch==UP)DEC(t,4);
        if(ch==DOWN)INC(t,4);
        if(ch==' '&&t!=3){PlaySound(cho,NULL,PM);return t;}
        if(ch==0x1B){setbgm(-1);exit(0);}
        //
        if(t==3&&!show)show=illustration(true);
        else if(t!=3&&show)show=illustration(false);
    }
}
bool illustration(bool p)
{
    if(p)
    {
    	PlaySound(dow,NULL,PM);
        color(WHITE,4);
        gotoxy(32,28);
        cout<<"��Ϸ����:                                                 ";
        gotoxy(32,29);
        cout<<"�����ѡ�񣬿ո��ȷ����ESC�����ء�                       ";
        gotoxy(32,30);
        cout<<"˫���غϽ���ʱ����ͣ�����ո���Լ�����                    ";
        gotoxy(32,31);
        cout<<"ע��:�������������������������뷨��                     ";
        gotoxy(32,32);
        cout<<"���ݼ��㹫ʽ:                                             ";
        gotoxy(32,33);
        cout<<"���������˺�=�����˺���40/(40+�Է�����)                   ";
        gotoxy(32,34);
        cout<<"����ħ���˺�=�����˺���40/(40+�Է�ħ��)                   ";
        gotoxy(32,35);
        cout<<"������ʵ�˺�=�����˺�                                     ";
        gotoxy(32,36);
        cout<<"�������и���=�������и��ʡ�(100+��������)/(100+�Է�����)  ";
        gotoxy(32,37);
        cout<<"���ձ�������=�����������ʡ�(100+��������)/100             ";
        gotoxy(32,38);
        cout<<"�����˺�=�����˺���150%                                   ";
        color(7);
        gotoxy(58,24);
        cout<<"��  ��";
        gotoxy(58,25);
        cout<<"��  ��";
        gotoxy(58,26);
        cout<<"��  ��";
        color(7,4);
        gotoxy(58,23);
        cout<<"���ޡ�";
        gotoxy(30,27);
        cout<<"�������������������������������ޡ�����������������������������";
        gotoxy(30,39);
        cout<<"��������������������������������������������������������������";
        for(int i=28; i<=38; i++)
        {
            gotoxy(30,i);
            cout<<"��";
            gotoxy(90,i);
            cout<<"��";
        }
    }
    else
    {
    	PlaySound(upp,NULL,PM);
        color(7,4);
        gotoxy(54,23);
        cout<<"��������������";
        color(WHITE);
        gotoxy(58,24);
        cout<<"      ";
        gotoxy(58,25);
        cout<<"      ";
        gotoxy(58,26);
        cout<<"      ";
        for(int i=27; i<=39; i++)
        {
            gotoxy(30,i);
            cout<<"                                                              ";
        }
    }
    return p;
}
void drawmenu()
{
    system("cls");
    color(7,1);
    gotoxy(0,0);
    cout<<"��������������������������������������������������������������������������������������������������������������������������";
    gotoxy(0,1);
    cout<<"��������������������������������������������������������������������������������������������������������������������������";
    gotoxy(0,12);
    cout<<"����������������������������������������������������������BY-YZH�ש�������������������������������������������������������";
    gotoxy(0,13);
    cout<<"�������������������������������������������������������������ޡ�����������������������������������������������������������";
    for(int i=2; i<=11; i++)
    {
        gotoxy(0,i);
        cout<<"��";
        gotoxy(2,i);
        cout<<"��";
        gotoxy(120,i);
        cout<<"��";
        gotoxy(118,i);
        cout<<"��";
    }
    //
    color(7,4);
    gotoxy(4,2);
    cout<<"������������������������������������������������������������������������������������������������������������������";
    gotoxy(4,11);
    cout<<"������������������������������������������������������������������������������������������������������������������";
    for(int i=3; i<=10; i++)
    {
        gotoxy(4,i);
        cout<<"��";
        gotoxy(116,i);
        cout<<"��";
    }
    color(YELLOW,4);
    gotoxy(6,3);
    cout<<" @@@            @@@     @@@@    @@@@        @@@    @@@@@@@@@         @@@@@@@@@      @@@@@@@@@      @@@@@@@@   ";
    gotoxy(6,4);
    cout<<" @@@@          @@@@      @@      @@@@@       @      @@               @@      @@     @@      @@   @@@      @@@ ";
    gotoxy(6,5);
    cout<<" @  @@        @  @@      @@      @   @@@     @      @@               @@      @@     @@      @@  @@          @ ";
    gotoxy(6,6);
    cout<<" @   @@      @   @@      @@      @     @@    @      @@@@@@@          @@@@@@@@       @@@@@@@@   @@             ";
    gotoxy(6,7);
    cout<<" @    @@    @    @@      @@      @      @@@  @      @@               @@   @@@       @@         @@             ";
    gotoxy(6,8);
    cout<<" @     @@  @     @@      @@      @       @@@ @      @@               @@    @@@      @@         @@@        @@@@";
    gotoxy(6,9);
    cout<<" @      @@@      @@      @@      @         @@@      @@               @@     @@@     @@          @@@        @@ ";
    gotoxy(6,10);
    cout<<"@@@      @      @@@@    @@@@    @@@        @@@@    @@@@@@@@@@       @@@@@    @@@@  @@@@@          @@@@@@@@@ @ ";
    //
    color(7);
    gotoxy(54,14);
    cout<<"    ��  ��    ";
    gotoxy(54,15);
    cout<<"    ��  ��    ";
    gotoxy(54,16);
    cout<<"    ��  ��    ";
    gotoxy(54,17);
    cout<<"    ��  ��    ";
    color(7,4);
    gotoxy(54,18);
    cout<<"�������ޡ�����";
    gotoxy(54,19);
    cout<<"��          ��";
    gotoxy(54,20);
    cout<<"��          ��";
    gotoxy(54,21);
    cout<<"��          ��";
    gotoxy(54,22);
    cout<<"��          ��";
    gotoxy(54,23);
    cout<<"��������������";
    //
    color(7);
    gotoxy(0,18);
    cout<<"                ,$               ��";
    gotoxy(0,19);
    cout<<"               I+8?             // ";
    gotoxy(0,20);
    cout<<"              NI $Z            //  ";
    gotoxy(0,21);
    cout<<"              =:N,Z+          //   ";
    gotoxy(0,22);
    cout<<"               +I?+          //    ";
    gotoxy(0,23);
    cout<<"              ?~D8ZI        //     ";
    gotoxy(0,24);
    cout<<"        Z   ,$7=I77?Z$     //      ";
    gotoxy(0,25);
    cout<<"       NID8 =77=I7II77    //       ";
    gotoxy(0,26);
    cout<<"      $$ZO8:7,$I=?$I$7   //        ";
    gotoxy(0,27);
    cout<<"      IZOOI$  ?7?++?77ZO~,=        ";
    gotoxy(0,28);
    cout<<"       =OOO    ?+++?  =7I7 +:      ";
    gotoxy(0,29);
    cout<<"              7I7II$    N$         ";
    gotoxy(0,30);
    cout<<"              ?~I+?I?   +          ";
    gotoxy(0,31);
    cout<<"             ==??Z?I?              ";
    gotoxy(0,32);
    cout<<"              ++? ?+~              ";
    gotoxy(0,33);
    cout<<"              ?I  IO               ";
    gotoxy(0,34);
    cout<<"              :?  ?+               ";
    gotoxy(0,35);
    cout<<"             :?    ?I              ";
    gotoxy(0,36);
    cout<<"             ~I    ??              ";
    gotoxy(0,37);
    cout<<"             =      =              ";
    gotoxy(0,38);
    cout<<"             7      ?+,,,          ";
    gotoxy(0,39);
    cout<<"            I7,:::~?I=$$~:,        ";
    gotoxy(0,40);
    cout<<"           :$?=,                   ";
    //
    gotoxy(85,18);
    cout<<"��                Z,              ";
    gotoxy(85,19);
    cout<<" \\\\              ~8+$           ";
    gotoxy(85,20);
    cout<<"  \\\\             Z7 ?M          ";
    gotoxy(85,21);
    cout<<"   \\\\           +Z=O:=          ";
    gotoxy(85,22);
    cout<<"    \\\\           +?I+           ";
    gotoxy(85,23);
    cout<<"     \\\\         ~OOD=?          ";
    gotoxy(85,24);
    cout<<"      \\\\      ZZI7$7=77    Z    ";
    gotoxy(85,25);
    cout<<"       \\\\     7ZII77+7I= ODIN,  ";
    gotoxy(85,26);
    cout<<"        \\\\    I$I7?~I7 I:OOZ7$  ";
    gotoxy(85,27);
    cout<<"        =,~OZZI7?++?$I  Z?OOZI    ";
    gotoxy(85,28);
    cout<<"        :+ ZI7=  ?+++?   OOO=     ";
    gotoxy(85,29);
    cout<<"           8N    $I7I77           ";
    gotoxy(85,30);
    cout<<"            +   ?????~?           ";
    gotoxy(85,31);
    cout<<"                ?I?Z?~?=          ";
    gotoxy(85,32);
    cout<<"                ,+? ?++           ";
    gotoxy(85,33);
    cout<<"                 O7  II           ";
    gotoxy(85,34);
    cout<<"                 +?  ?::          ";
    gotoxy(85,35);
    cout<<"                I?:   I,          ";
    gotoxy(85,36);
    cout<<"                ??    I~          ";
    gotoxy(85,37);
    cout<<"                +=     =          ";
    gotoxy(85,38);
    cout<<"            ,,,I?      7          ";
    gotoxy(85,39);
    cout<<"          ,:~$$=I?~:::,7I         ";
    gotoxy(85,40);
    cout<<"                     ,=?$:       ";
    //
}
void gotoxy(int x,int y)
{
    COORD pos;
    pos.X=x;
    pos.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}
void color(int c)
{
    HANDLE hConsole=GetStdHandle((STD_OUTPUT_HANDLE));
    SetConsoleTextAttribute(hConsole,BACKGROUNDCOLOR*16+c);
}
void color(int c,int b)
{
    HANDLE hConsole=GetStdHandle((STD_OUTPUT_HANDLE));
    SetConsoleTextAttribute(hConsole,b*16+c);
}
bool space_esc()
{
    char ch;
    while(1)
    {
        ch=getch();
        if(ch==' ')return true;
        else if(ch==0x1B)return false;
    }
}
void initialize()
{
    sl[0][0].name="����";
    sl[0][0].explain="������,����ȴ,����80%,����20%:�Եз�������ͨ���������100%�������������˺���";
    sl[0][0].spend=0;
    sl[0][0].cd=0;
    sl[0][0].sp=w_0attack;

    sl[0][1].name="���Ԥ��";
    sl[0][1].explain="����30MP,��ȴ2�غ�:׼�����г�棬����200%�Ĺ���2�غϡ��������Ч��������80%�ж�����";
    sl[0][1].spend=30;
    sl[0][1].cd=2;
    sl[0][1].sp=w_1charge;

    sl[0][2].name="��е";
    sl[0][2].explain="����40MP,��ȴ3�غ�,����100%:�ƻ��з��������뻤�ף����͵з�60%�Ĺ����뻤��4�غϡ�";
    sl[0][2].spend=40;
    sl[0][2].cd=3;
    sl[0][2].sp=w_2disarm;

    sl[0][3].name="��ʯ֮��";
    sl[0][3].explain="����20MP,��ȴ4�غ�:�Լ�����ʯ����־ǿ������������200%������ħ��6�غϲ�������м���״̬��";
    sl[0][3].spend=20;
    sl[0][3].cd=4;
    sl[0][3].sp=w_3stone;

    sl[0][4].name="�²д��";
    sl[0][4].explain="����50MP,��ȴ3�غ�,����80%,����20%:�����з��������ش��з����ж����������160%�������������˺���ʩ��4(����:6)�غϼ���40%��4(����:6)�غ��˺�Ϊ25%����������Ѫ��";
    sl[0][4].spend=50;
    sl[0][4].cd=3;
    sl[0][4].sp=w_4cripple;

    sl[0][5].name="�����ͻ�";
    sl[0][5].explain="����40MP,��ȴ5�غ�,����100%,����50%:ʹ�ö����ͻ��з����Եз����400%���׵������˺�������50%(����:75%)���ж��������з��ж���������ѣ����1�غϡ�";
    sl[0][5].spend=40;
    sl[0][5].cd=5;
    sl[0][5].sp=w_5shieldhit;

    sl[0][6].name="Ѫ������";
    sl[0][6].explain="������,��ȴ5�غ�:ͨ�����ϵķ�������Ѫ��ǿ��������������ÿ��ʧ1%������ֵ�����2%�Ĺ���4�غϣ����ÿ��1�㷨ǿ��ָ�2%������ʧ����ֵ��";
    sl[0][6].spend=0;
    sl[0][6].cd=5;
    sl[0][6].sp=w_6bloodwake;

    sl[0][7].name="��������";
    sl[0][7].explain="����20%HP,��ȴ1�غ�,����80%,����40%:������������ֵ���ͷ���������֮���ش��з����Եз����200%��������ֵ����ʵ�˺���δ����ʱ������������ֵ��";
    sl[0][7].spend=0;
    sl[0][7].cd=1;
    sl[0][7].sp=w_7rage;
    //
    sl[1][0].name="����";
    sl[1][0].explain="������,����ȴ,����80%,����20%:�Եз�������ͨ���������100%�������������˺���";
    sl[1][0].spend=0;
    sl[1][0].cd=0;
    sl[1][0].sp=m_0attack;

    sl[1][1].name="������ħ";
    sl[1][1].explain="����40MP,��ȴ2�غ�:Ϊ��������ħ���������൱�ڷ�ǿ�Ĺ�����������3�غϣ��ü����ͷ�������̽���һ�ι�����";
    sl[1][1].spend=40;
    sl[1][1].cd=2;
    sl[1][1].sp=m_1enchants;

    sl[1][2].name="�籩��";
    sl[1][2].explain="����60MP,��ȴ3�غ�:�÷籩���������γɻ��ܣ����30%���ٶ�ͬʱÿ��1�㷨ǿ�����1%�Ļ��ף�����5�غϡ�";
    sl[1][2].spend=60;
    sl[1][2].cd=3;
    sl[1][2].sp=m_2stormshieldl;

    sl[1][3].name="����ѩ";
    sl[1][3].explain="����80MP,��ȴ4�غ�,����80%,����20%:�ٻ�����ѩ�����з������6��40%��ǿ��ħ���˺���ÿ���˺��������������뱩����ÿ�����л���ʩ��1�غϵı���Ч��(����40%�ٶȺ�80%����)��";
    sl[1][3].spend=80;
    sl[1][3].cd=4;
    sl[1][3].sp=m_3snowstorm;

    sl[1][4].name="��ǹ��";
    sl[1][4].explain="����50MP,����ȴ,����80%,����30%:��з�����һ֧��������ı�ǹ�����150%��ǿ��ħ���˺�����Ŀ�걻�������˺�������";
    sl[1][4].spend=50;
    sl[1][4].cd=0;
    sl[1][4].sp=m_4icelance;

    sl[1][5].name="������";
    sl[1][5].explain="����40MP,��ȴ5�غ�,����200%,����50%:��ħ��ֱ���з����飬���120%��ǿ����ʵ�˺��������͵з�50%�ķ�ǿ��ħ��3�غϣ��ü��ܱ���ʱ��ѣ�εз�1�غϡ�";
    sl[1][5].spend=40;
    sl[1][5].cd=5;
    sl[1][5].sp=m_5mindblast;

    sl[1][6].name="ڤ��";
    sl[1][6].explain="����100MP,��ȴ5�غ�:����һ��ڤ�룬ÿ��2�㷨ǿ��ָ�1%���������ֵͬʱ�������м���1�غϵ���ȴʱ�䡣";
    sl[1][6].spend=100;
    sl[1][6].cd=5;
    sl[1][6].sp=m_6muse;

    sl[1][7].name="����ȼ��";
    sl[1][7].explain="����20%MP,��ȴ3�غ�,����100%,����20%:������������ֵ��ȼ�з�������ȼ�յз�200%���ķ���ֵ�ķ��������200%���ķ���ֵ��ħ���˺���ͬʱʩ��2�غ��˺�Ϊ50%���ķ���ֵȼ�ա�";
    sl[1][7].spend=0;
    sl[1][7].cd=3;
    sl[1][7].sp=m_7manaburn;
    //
    sl[2][0].name="����";
    sl[2][0].explain="������,����ȴ,����80%,����20%:�Եз�������ͨ���������100%�������������˺���";
    sl[2][0].spend=0;
    sl[2][0].cd=0;
    sl[2][0].sp=a_0attack;

    sl[2][1].name="��ɱ";
    sl[2][1].explain="����30MP,��ȴ3�غ�,����100%,����40%:�Եз�����һ���������������160%�������������˺����з�ÿ��ʧ1%����ֵ���������ü���3%���˺���";
    sl[2][1].spend=30;
    sl[2][1].cd=3;
    sl[2][1].sp=a_1assassinate;

    sl[2][2].name="��ä��";
    sl[2][2].explain="����40MP,��ȴ6�غ�,����80%:��з�Ͷ����ä������ʹ�з���ä�����͵з�50%�����кͱ���4�غϡ�";
    sl[2][2].spend=40;
    sl[2][2].cd=6;
    sl[2][2].sp=a_2blindingpowder;

    sl[2][3].name="Ǳ��";
    sl[2][3].explain="������,��ȴ5�غ�:����Ǳ��״̬������300%������1�غϡ�����20%�ٶ�1�غϡ����100%����2�غϲ��������֢״��";
    sl[2][3].spend=0;
    sl[2][3].cd=5;
    sl[2][3].sp=a_3sneak;

    sl[2][4].name="�㶾ذ��";
    sl[2][4].explain="����50MP,��ȴ4�غ�,����80%,����30%:��з�Ͷ��һ�Ѵ㶾ذ�ף�����൱�ڵз���ǰ����ֵ20%�������˺���ʩ��4�غ��˺�Ϊ���������ֵ5%(ÿ�㷨ǿ��������0.2%)���ж���";
    sl[2][4].spend=50;
    sl[2][4].cd=4;
    sl[2][4].sp=a_4poisondagger;

    sl[2][5].name="�ƹ�";
    sl[2][5].explain="����20MP,��ȴ8�غ�,����100%,����10%:���䲻����ػ��з����㣬���͵з�40%�Ļ���3�غϲ�ʹ��ѣ��1(����:2)�غϡ�";
    sl[2][5].spend=20;
    sl[2][5].cd=8;
    sl[2][5].sp=a_5stickstrike;

    sl[2][6].name="����ҩ��";
    sl[2][6].explain="����40MP,��ȴ6�غ�,����80%:��з�Ͷ��һƿ����ҩ��ʹ�õз�����4�غϣ�����״̬ʱ����50%�Ĺ����뷨ǿ��";
    sl[2][6].spend=40;
    sl[2][6].cd=6;
    sl[2][6].sp=a_6weakagent;

    sl[2][7].name="��������";
    sl[2][7].explain="����40MP,��ȴ2�غ�:�Եз�����һ�ι��������غ������еĹ��������󶼽���һ��50%���ʵ������ж����ж��ɹ�ʱ׷��һ�ι������ж�ʧ��ʱ���½����ж�ֱ���ۼ��ж�ʧ��3�Ρ�";
    sl[2][7].spend=40;
    sl[2][7].cd=2;
    sl[2][7].sp=a_7fatalrhythm;
    //
    sl[3][0].name="����";
    sl[3][0].explain="������,����ȴ,����80%,����20%:�Եз�������ͨ���������100%�������������˺���";
    sl[3][0].spend=0;
    sl[3][0].cd=0;
    sl[3][0].sp=c_0attack;

    sl[3][1].name="�����";
    sl[3][1].explain="����50MP,��ȴ3�غ�,����100%,����25%:�����ٻ����ε�����˲���и�з���ʩ��4(����:6)�غ��˺�Ϊ100%��������Ѫ��";
    sl[3][1].spend=50;
    sl[3][1].cd=3;
    sl[3][1].sp=c_1sectumsempra;

    sl[3][2].name="�һ���";
    sl[3][2].explain="����50MP,��ȴ3�غ�,����100%,����25%:�����ٻ����ȵĻ�������ϯ���з���ʩ��4(����:6)�غ��˺�Ϊ100%��ǿ��ȼ�ա�";
    sl[3][2].spend=50;
    sl[3][2].cd=3;
    sl[3][2].sp=c_2blaze;

    sl[3][3].name="�嶾��";
    sl[3][3].explain="����50MP,��ȴ3�غ�,����100%,����25%:�����ٻ��ֲ��ľ綾������ʴ�з���ʩ��4(����:6)�غ��˺�Ϊ50%����+50%��ǿ���ж���";
    sl[3][3].spend=50;
    sl[3][3].cd=3;
    sl[3][3].sp=c_3fivepoisons;

    sl[3][4].name="�ػ���";
    sl[3][4].explain="����40MP,��ȴ4�غ�:�����ػ�����������200%�ٶ�1�غϣ�ͬʱ���ݵз������뷨ǿ�ı�����ÿ��1�㷨ǿ������Ӧ������2%�Ļ��׻�ħ��������6�غϡ�";
    sl[3][4].spend=40;
    sl[3][4].cd=4;
    sl[3][4].sp=c_4daemon;

    sl[3][5].name="������";
    sl[3][5].explain="����20MP,��ȴ1�غ�:���������з�������֢״��ʹ�з�����֢״�����غ�+1��";
    sl[3][5].spend=20;
    sl[3][5].cd=1;
    sl[3][5].sp=c_5increase;

    sl[3][6].name="�����";
    sl[3][6].explain="������,��ȴ6�غ�,����100%:�����ֶ�з���꣬������������ֵ20%����ʵ�˺���Ϊ�����ָ����ڸ�ֵ������ֵ��ͬʱ�����������ֵ20%�ķ�����Ϊ�����ָ����ڸ�ֵ�ķ���ֵ��";
    sl[3][6].spend=0;
    sl[3][6].cd=6;
    sl[3][6].sp=c_6imperio;

    sl[3][7].name="���串����";
    sl[3][7].explain="����100MP,��ȴ7�غ�:����ʩ���ڵз����ϵ���������Ч��������з�����֢״��������֢״�������˺�˲��ʩ���ڵз���";
    sl[3][7].spend=100;
    sl[3][7].cd=7;
    sl[3][7].sp=c_7summarycurse;
    //
    sl[4][0].name="����/��װ";
    sl[4][0].explain="������,����ȴ,����80%,����20%:��з�����һ���ӵ������100%�������������˺������������ӵ�ʱ��������װ��������������";
    sl[4][0].spend=0;
    sl[4][0].cd=0;
    sl[4][0].sp=s_0attack;
    bulletspend[0]=0;

    sl[4][1].name="���ٰ�ǹ";
    sl[4][1].explain="����30MP,��ȴ3�غ�:���ٰ�ǹ�Եз�����һ�ι�����������һ������غϡ�";
    sl[4][1].spend=30;
    sl[4][1].cd=3;
    sl[4][1].sp=s_1quickfire;
    bulletspend[1]=1;

    sl[4][2].name="��׼���";
    sl[4][2].explain="����40MP,��ȴ4�غ�,����100%,����20%:��з�Ҫ������һ�ξ�׼��������160%�������������˺���ÿ��2�����ж��������ü���1%���˺���";
    sl[4][2].spend=40;
    sl[4][2].cd=4;
    sl[4][2].sp=s_2deadeyeshoot;
    bulletspend[2]=1;

    sl[4][3].name="ս������";
    sl[4][3].explain="������,��ȴ8�غ�,����80%:�Եз�����һ��ս�����ƣ���յз����ж�����Ϊ�����������ֵ�����ֵ���ж�����";
    sl[4][3].spend=0;
    sl[4][3].cd=8;
    sl[4][3].sp=s_3tacticalcounter;
    bulletspend[3]=0;

    sl[4][4].name="�������";
    sl[4][4].explain="����60MP,��ȴ6�غ�,����80%,����20%:��з��������������ӵ������3��100%�������������˺���ÿ���ӵ��������������뱩�����������ӵ�ȫ��������ѣ�εз�1�غϡ�";
    sl[4][4].spend=60;
    sl[4][4].cd=6;
    sl[4][4].sp=s_4interceptingshoot;
    bulletspend[4]=3;

    sl[4][5].name="������װ";
    sl[4][5].explain="����20MP,��ȴ6�غ�:����һ�ο�����װ��������������������һ������غϡ�";
    sl[4][5].spend=20;
    sl[4][5].cd=6;
    sl[4][5].sp=s_5quickreload;
    bulletspend[5]=0;

    sl[4][6].name="�������";
    sl[4][6].explain="����40MP,��ȴ6�غ�,����80%:�Եз�ʩ��һ��������ǣ�������80%�Ļ�����ħ��2�غϡ�";
    sl[4][6].spend=40;
    sl[4][6].cd=6;
    sl[4][6].sp=s_6deathmarker;
    bulletspend[6]=0;

    sl[4][7].name="���꼲��";
    sl[4][7].explain="����60MP,��ȴ8�غ�,����60%,����10%:������з���������������е��ӵ���ÿ���ӵ����150%�������������˺���ÿ���ӵ��������������뱩����";
    sl[4][7].spend=60;
    sl[4][7].cd=8;
    sl[4][7].sp=s_7stormshoot;
    bulletspend[7]=1;
    //
    sl[5][0].name="����";
    sl[5][0].explain="������,����ȴ,����80%,����10%:�Եз�������ͨ���������100%�������������˺���";
    sl[5][0].spend=0;
    sl[5][0].cd=0;
    sl[5][0].sp=d_0attack;
    
    sl[5][1].name="Ӱ��";
    sl[5][1].explain="����50MP,��ȴ4�غ�:�԰�Ӱ����̫�������150%�Ĺ���������5�غϡ�";
    sl[5][1].spend=50;
    sl[5][1].cd=4;
    sl[5][1].sp=d_1shadowblade;
    
    sl[5][2].name="����֮Ӱ";
    sl[5][2].explain="����20MP,��ȴ4�غ�,����80%:���ת��������������״̬����Ӱ�в��԰�Ӱ��׽�з�Ӱ�ӣ�����ʱ������״̬ת�Ƹ��з���";
    sl[5][2].spend=20;
    sl[5][2].cd=4;
    sl[5][2].sp=d_2curseshadow;
    
    sl[5][3].name="����ն";
    sl[5][3].explain="����30MP,��ȴ3�غ�:���ٶԵз������������ι�����";
    sl[5][3].spend=30;
    sl[5][3].cd=3;
    sl[5][3].sp=d_3triplechop;
    
    sl[5][4].name="���밵Ӱ";
    sl[5][4].explain="����50%MP,��ȴ4�غ�:���Ĵ�������ֵ�γɰ�Ӱ�������������400%����1�غϲ��ָ�200%���ķ���ֵ������ֵ��";
    sl[5][4].spend=0;
    sl[5][4].cd=4;
    sl[5][4].sp=d_4intoshadow;
    
    sl[5][5].name="Ӱ��";
    sl[5][5].explain="����40MP,��ȴ4�غ�,����100%:��Ӱ�Ӳ��Ƶз��谭�з�ʩ����ʹ�乥����������м�����ȴ��ʱ+2��";
    sl[5][5].spend=40;
    sl[5][5].cd=4;
    sl[5][5].sp=d_5shadowdurance;
    
    sl[5][6].name="��ӰѪ��";
    sl[5][6].explain="����50%HP,��ȴ7�غ�:���Ĵ�������ֵ�׼���Ӱǿ�����������40%��������ֵ�Ļ��׺�ħ���Լ�60%��������ֵ�ķ�ǿ������7�غϡ�";
    sl[5][6].spend=0;
    sl[5][6].cd=7;
    sl[5][6].sp=d_6bloodsacrifice;
    
    sl[5][7].name="Ӱ����";
    sl[5][7].explain="����120MP,��ȴ6�غ�,����80%,����10%:�ٻ�8�Ѱ�Ӱ֮�������з���ÿ��Ӱ���������������뱩����Ӱ������ʱ���25%��ǿ����ʵ�˺�������4�غϵĶ�Ӧ����25%����Ч����";
    sl[5][7].spend=120;
    sl[5][7].cd=6;
    sl[5][7].sp=d_7shadowswordcircle;
}
bool hitthat(double p)
{
    if(rand()<=p*RAND_MAX)return true;
    else return false;
}
void drawbar(double p)
{
    int i;
    if(p>=0.99999999)
    {
        for(i=10; i--; i>0)cout<<"��";
        return;
    }
    int a;
    CONSOLE_SCREEN_BUFFER_INFO xy;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &xy);
    for(i=10; i--; i>0)cout<<"  ";
    gotoxy(xy.dwCursorPosition.X,xy.dwCursorPosition.Y);
    a=(int)(p*10);
    for(i=a; i--; i>0)cout<<"��";
    if(a==10)return;
    i=(int)((p*10-(int)(p*10))*8);
    switch(i)
    {
    case 0:
        cout<<"  ";
        break;
    case 1:
        cout<<"��";
        break;
    case 2:
        cout<<"��";
        break;
    case 3:
        cout<<"��";
        break;
    case 4:
        cout<<"��";
        break;
    case 5:
        cout<<"��";
        break;
    case 6:
        cout<<"��";
        break;
    case 7:
        cout<<"��";
        break;
    }
    for(i=9-a; i--; i>0)cout<<"  ";
}
void drawmvbar(double p,bool who)
{
    color(CYAN);
    int i,a;
    char d[5];
    if(p>=0.99999999)p=1;
    if(who)
    {
        if(p<lastmvp)
        {
            gotoxy(96,2);
            cout<<"                    ";
            gotoxy(118,2);
            cout<<"    ";
        }
        itoa((int)(p*100),d,10);
        gotoxy(118,2);
        cout<<d<<'%';
        lastmvp=p;
        gotoxy(96,2);
        a=(int)(p*10);
        for(i=a; i--; i>0)cout<<"��";
        if(a==10)return;
        i=(int)((p*10-(int)(p*10))*8);
        switch(i)
        {
        case 0:
            cout<<"  ";
            break;
        case 1:
            cout<<"��";
            break;
        case 2:
            cout<<"��";
            break;
        case 3:
            cout<<"��";
            break;
        case 4:
            cout<<"��";
            break;
        case 5:
            cout<<"��";
            break;
        case 6:
            cout<<"��";
            break;
        case 7:
            cout<<"��";
            break;
        }
    }
    else
    {
        if(p<lastmve)
        {
            gotoxy(96,4);
            cout<<"                    ";
            gotoxy(118,4);
            cout<<"    ";
        }
        itoa((int)(p*100),d,10);
        gotoxy(118,4);
        cout<<d<<'%';
        lastmve=p;
        gotoxy(96,4);
        a=(int)(p*10);
        for(i=a; i--; i>0)cout<<"��";
        if(a==10)return;
        i=(int)((p*10-(int)(p*10))*8);
        switch(i)
        {
        case 0:
            cout<<"  ";
            break;
        case 1:
            cout<<"��";
            break;
        case 2:
            cout<<"��";
            break;
        case 3:
            cout<<"��";
            break;
        case 4:
            cout<<"��";
            break;
        case 5:
            cout<<"��";
            break;
        case 6:
            cout<<"��";
            break;
        case 7:
            cout<<"��";
            break;
        }
    }
}
void writenum(int p,int f)
{
    CONSOLE_SCREEN_BUFFER_INFO xy;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &xy);
    color(WHITE);
    if(p<f)color(RED);
    if(p>f)color(GREEN);
    cout<<"      ";
    gotoxy(xy.dwCursorPosition.X,xy.dwCursorPosition.Y);
    cout<<p;
}
int choose(int n,string* p)
{
    int t=0,i=0;
    char ch=0;
    CONSOLE_SCREEN_BUFFER_INFO xy;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &xy);
    while(1)
    {
        gotoxy(xy.dwCursorPosition.X,xy.dwCursorPosition.Y);
        for(i=0; i<n; i++)
        {
            if(i==t)color(BACKGROUNDCOLOR,WHITE);
            cout<<p[i];
            color(WHITE,BACKGROUNDCOLOR);
            cout<<' ';
        }
        color(WHITE);
        ch=getch();
        if(ch==0)ch=getch();
        if(ch==LEFT)DEC(t,n);
        if(ch==RIGHT)INC(t,n);
        if(ch==' '){PlaySound(cho,NULL,PM);return t;}
        if(ch==0x1B)return -1;
    }
}
int choose(int n,string* p,string* explain,int k)
{
    int t=k,i=0;
    char ch=0;
    CONSOLE_SCREEN_BUFFER_INFO xy;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &xy);
    while(1)
    {
        gotoxy(xy.dwCursorPosition.X,xy.dwCursorPosition.Y);
        for(i=0; i<n; i++)
        {
            if(i==t)color(BACKGROUNDCOLOR,WHITE);
            cout<<p[i];
            color(WHITE,BACKGROUNDCOLOR);
            cout<<' ';
        }
        gotoxy(0,xy.dwCursorPosition.Y+1);
        cout<<"                                                                                                                          ";
        cout<<"                                                                                                                          ";
        color(13);
        gotoxy(0,xy.dwCursorPosition.Y+1);
        cout<<explain[t];
        color(WHITE);
        ch=getch();
        if(ch==0)ch=getch();
        if(ch==LEFT)DEC(t,n);
        if(ch==RIGHT)INC(t,n);
        if(ch==' '){PlaySound(cho,NULL,PM);return t;}
    }
}
int skillchoose(status* p,int n,string* name,string* explain)
{
    int t=0,i=0;
    char ch=0;
    CONSOLE_SCREEN_BUFFER_INFO xy;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &xy);
    while(1)
    {
        gotoxy(xy.dwCursorPosition.X,xy.dwCursorPosition.Y);
        for(i=0; i<n; i++)
        {
            if(i==t)color(BACKGROUNDCOLOR,WHITE);
            cout<<name[i];
            if(p->cd[i])cout<<'('<<p->cd[i]<<')';
            color(WHITE,BACKGROUNDCOLOR);
            cout<<' ';
        }
        gotoxy(0,xy.dwCursorPosition.Y+1);
        cout<<"                                                                                                                          ";
        cout<<"                                                                                                                          ";
        color(13);
        gotoxy(0,xy.dwCursorPosition.Y+1);
        cout<<explain[t];
        color(WHITE);
        ch=getch();
        if(ch==0)ch=getch();
        if(ch==LEFT)DEC(t,n);
        if(ch==RIGHT)INC(t,n);
        if(ch==' ')return t;
        if(ch==0x1B)return -1;
    }
}
void drawboard()
{
    color(WHITE);
    system("cls");
    gotoxy(0,0);
    cout<<"�з�:                                   ������:      ����:      ��ǿ:      ħ��:      ���ж���";
    gotoxy(0,1);
    cout<<"������������������������                ���ٶ�:      ����:      ����:      ����:      ��      ������������������������";
    gotoxy(0,2);
    cout<<"��                    ��HP:             ����������:                                   ���ҷ�: ��                    ��";
    gotoxy(0,3);
    cout<<"�ǩ���������������������                ��                                            ��      �ǩ���������������������";
    gotoxy(0,4);
    cout<<"��                    ��MP:             ��                                            ���з�: ��                    ��";
    gotoxy(0,5);
    cout<<"������������������������                ��                                            ��      ������������������������";
    gotoxy(0,6);
    cout<<"�����������������������������������������ߩ��������������������������������������������ߩ���������������������������������";
    gotoxy(0,7);
    cout<<"״̬: ";
    gotoxy(0,8);
    cout<<"�������������������������������������������������������������ש�����������������������������������������������������������";
    for(int i=9; i<=27; i++)
    {
        gotoxy(60,i);
        cout<<"��";
    }
    gotoxy(0,28);
    cout<<"�������������������������������������������������������������ߩ�����������������������������������������������������������";
    gotoxy(0,29);
    cout<<"����:";
    gotoxy(0,32);
    cout<<"��������������������������������������������������������������������������������������������������������������������������";
    gotoxy(0,33);
    cout<<"״̬: ";
    gotoxy(0,34);
    cout<<"�����������������������������������������ש��������������������������������������������ש���������������������������������";
    gotoxy(0,35);
    cout<<"�ҷ�:                                   ������:      ����:      ��ǿ:      ħ��:      ������:";
    gotoxy(0,36);
    cout<<"������������������������                ���ٶ�:      ����:      ����:      ����:      ��ͷ��:";
    gotoxy(0,37);
    cout<<"��                    ��HP:             ����������:                                   ������:";
    gotoxy(0,38);
    cout<<"�ǩ���������������������                ��                                            ������:";
    gotoxy(0,39);
    cout<<"��                    ��MP:             ��                                            ���ֲ�:";
    gotoxy(0,40);
    cout<<"������������������������                ��                                            ���㲿:";
}
bool battle()
{
	setbgm(rand()%3+3);
    drawboard();
    //
    player=myrole.battlestatus(true);
    enemy=enemyrole.battlestatus(false);
    //
    mgeline=9;
    row=0;
    lastmvp=0;
    lastmve=0;
    esc=false;
    //
    string s;
    showskill();
    myrole.showequip();
    showbar(player);
    showbar(enemy);
    showsta(player);
    showsta(enemy);
    showmessage("ս����ʼ��");
    //����
    if(player.classes==1&&player.lv>=10)m_phaseblink(&player);
    if(enemy.classes==1&&enemy.lv>=10)m_phaseblink(&enemy);
    //װ��
    myrole.returnequ(1).effect(&player);
    enemyrole.returnequ(1).effect(&enemy);
    //
    while(1)
    {
        turnend(turnstart(whoseturn(&player,&enemy)));
        if(esc||!space_esc()){setbgm(2);return false;}
        //
        if(player.HP<=0)myrole.returnequ(2).effect(&player);
        if(enemy.HP<=0)enemyrole.returnequ(2).effect(&enemy);
        //
        if(player.HP<=0)
        {
            color(WHITE);
            s=myrole.name;
            showmessage(s+"�ѱ����ܣ�");
            getch();
            setbgm(2);
            return false;
        }
        if(enemy.HP<=0)
        {
            color(WHITE);
            s=enemyrole.name;
            showmessage(s+"�ѱ����ܣ�");
            getch();
            setbgm(2);
            return true;
        }
    }
}
void showmessage(string s)
{
    //color(WHITE);
    if(mgeline>27)
    {
        row=(row+1)%2;
        while(mgeline>9)
        {
            mgeline--;
            gotoxy(62*row,mgeline);
            cout<<"                                                            ";
        }
    }
    gotoxy(62*row,mgeline);
    cout<<s;
    mgeline++;
}
status* whoseturn(status* player,status* enemy)
{
    double *p,*e;
    int ps,es;
    double interval;
    p=&player->move;
    e=&enemy->move;
    ps=player->spd;
    es=enemy->spd;
    interval=0.02/(ps>=es?ps:es);
    drawmvbar(*p,true);
    drawmvbar(*e,false);
    while(1)
    {
        if(*p>=0.99999999&&*e>=0.99999999)
        {
            if(hitthat(0.5))
            {
                *p=0;
                return player;
            }
            else
            {
                *e=0;
                return enemy;
            }
        }
        if(*p>=0.99999999)
        {
            *p=0;
            return player;
        }
        if(*e>=0.99999999)
        {
            *e=0;
            return enemy;
        }
        *p+=ps*interval;
        *e+=es*interval;
        drawmvbar(*p,true);
        drawmvbar(*e,false);
        Sleep(10);
    }
}
status* turnstart(status* p)
{
    color(8);
    showmessage("������������������������������������������������������������");
    int i;
    string s;
    bool hpr=true,mpr=true;
    //
    status f;
    if(p->who)
    {
        f=myrole.battlestatus(true);
        s=myrole.name;
    }
    else
    {
        f=enemyrole.battlestatus(false);
        s=enemyrole.name;
    }
    color(YELLOW);
    showmessage(s+"�غϿ�ʼ��");
    //DEBUFF
    for(i=0; i<3; i++) //��Ѫȼ���ж�
    {
        if(p->debuff[i].duration)
        {
            p->debuff[i].duration--;
            switch(i)
            {
            case 0:
                color(WHITE);
                showmessage(s+"��Ѫ���ܵ������˺���");
                damage(p,AD,-p->debuff[i].ratio,HPbar);
                hpr=false;
                break;
            case 1:
                color(WHITE);
                showmessage(s+"ȼ�գ��ܵ�ħ���˺���");
                damage(p,AP,-p->debuff[i].ratio,HPbar);
                mpr=false;
                break;
            case 2:
                color(WHITE);
                showmessage(s+"�ж����ܵ���ʵ�˺���");
                damage(p,RE,-p->debuff[i].ratio,HPbar);
                break;
            }
        }
    }
    //
    //����
    if(p->HP<=0)return p;
    //�Զ��ָ�
    if(hpr)damage(p,RE,p->HPrec,HPbar);
    else
    {
        color(WHITE);
        showmessage(s+"��Ѫ�����غ��޷���Ȼ�ָ�������");
    }
    if(mpr)damage(p,RE,p->MPrec,MPbar);
    else
    {
        color(WHITE);
        showmessage(s+"ȼ�գ����غ��޷���Ȼ�ָ�������");
    }
    //
    //���ԼӼ�
    for(i=0; i<8; i++) //����ǿ����������
        if(p->attribute[i].duration)p->attribute[i].duration--;
    dealbuff(p);
    //ѣ��
    if(p->debuff[3].duration)//ѣ��
    {
        p->debuff[3].duration--;
        color(WHITE);
        showmessage(s+"��ѣ�Σ����غ��޷��ж���");
        showbuff(*p);
        return p;
    }
    //equip
    if(p->who)myrole.returnequ(0).effect(p);
    else enemyrole.returnequ(0).effect(p);
    if(player.HP<=0||enemy.HP<=0)return p;
    //������
    if(p->who||pvp)esc=operate(p);
    else enemyrole.opp(p);
    //
    return p;
}
void turnend(status* p)
{
    if(esc)return;
    if(player.HP<=0||enemy.HP<=0)return;
    //����������
    if(p->who||pvp)
    {
        gotoxy(5,29);
        cout<<"                                                                                                                     ";
        cout<<"                                                                                                                          ";
        cout<<"                                                                                                                          ";
    }
    //����
    if(p->classes==2&&p->lv>=10)a_preparation(p);
    if(p->classes==3&&p->lv>=4)c_vicious(p);
    if(p->classes==3&&p->lv>=10)c_boundary(p);
    if(p->classes==5&&p->lv>=10)d_shadowstep(p);
    //-cd
    for(int i=0; i<8; i++)if(p->cd[i])p->cd[i]--;
    //equip
    for(int i=3; i<6; i++)
    {
        if(p->who)myrole.returnequ(i).effect(p);
        else enemyrole.returnequ(i).effect(p);
    }
}
bool operate(status* p)
{
    int i,n,type;
    if(p->who)type=player.classes;
    else type=enemy.classes;
    n=p->skill;
    string name[8],explain[8];
    for(i=0; i<n; i++)
    {
        name[i]=sl[type][i].name;
        explain[i]=sl[type][i].explain;
    }
    while(1)
    {
        color(WHITE);
        gotoxy(5,29);
        i=skillchoose(p,n,name,explain);
        if(i==-1)return true;
        if(p->cd[i])
        {
            color(RED);
            showmessage("������ȴ�У�");
        }
        else if(sl[type][i].spend>p->MP)
        {
            color(RED);
            showmessage("�������㣡");
        }
        else if(bulletspend[i]>p->special)
        {
            color(RED);
            showmessage("�ӵ����㣡");
        }
        else
        {
            sl[type][i].sp(p);
            return false;
        }
    }
}
void setbuff(status* p,int type,int t,int d,double r)
{
	double sum=0;
	int maxd=d,mind=p->attribute[t].duration;
	if(type==ATT)
	{
		if(p->attribute[t].duration>d)
		{
			maxd=p->attribute[t].duration;
			mind=d;
		}
		sum=d*r+p->attribute[t].duration*p->attribute[t].ratio+mind*r*p->attribute[t].ratio;
		sum/=maxd;
		p->attribute[t].duration=maxd;
		p->attribute[t].ratio=sum;
	}
	else if(type==DEB)
	{
		if(t!=3)
		{
			if(p->debuff[t].duration>maxd)maxd=p->debuff[t].duration;
			sum=d*r+p->debuff[t].duration*p->debuff[t].ratio;
			sum/=maxd;
			p->debuff[t].duration=maxd;
			p->debuff[t].ratio=sum;
		}
		else
		{
			p->debuff[t].duration+=d;
		}
	}
}
void dealbuff(status* p)
{
    int i;
    status f;
    if(p->who)f=myrole.battlestatus(true);
    else f=enemyrole.battlestatus(false);
    for(i=0; i<8; i++)
        if(!p->attribute[i].duration)p->attribute[i].ratio=0;
    for(i=0; i<4; i++)
        if(!p->debuff[i].duration)p->debuff[i].ratio=0;
    for(i=0; i<8; i++) //����ǿ����������
    {
        switch(i)
        {
        case 0:
            p->atk=(int)(f.atk*(1+p->attribute[i].ratio)+0.00001);
            break;
        case 1:
            p->def=(int)(f.def*(1+p->attribute[i].ratio)+0.00001);
            break;
        case 2:
            p->abp=(int)(f.abp*(1+p->attribute[i].ratio)+0.00001);
            break;
        case 3:
            p->abr=(int)(f.abr*(1+p->attribute[i].ratio)+0.00001);
            break;
        case 4:
            p->spd=(int)(f.spd*(1+p->attribute[i].ratio)+0.00001);
            break;
        case 5:
            p->avd=(int)(f.avd*(1+p->attribute[i].ratio)+0.00001);
            break;
        case 6:
            p->crt=(int)(f.crt*(1+p->attribute[i].ratio)+0.00001);
            break;
        case 7:
            p->hit=(int)(f.hit*(1+p->attribute[i].ratio)+0.00001);
            break;
        }
    }
    showsta(*p);
    showbuff(*p);
}
int damage(status* p,int ty,double dam,int bar)
{
    int dmg;
    string s;
    char d[10];
    //
    if(p->who)s=myrole.name;
    else s=enemyrole.name;
    //
    if(ty==AD)dmg=(int)(40*dam/(40+p->def));
    else if(ty==AP)dmg=(int)(40*dam/(40+p->abr));
    else dmg=(int)dam;
    itoa(dmg>0?dmg:(-dmg),d,10);
    if(bar==HPbar)
    {
        if(dam>0)color(GREEN);
        else if(dam<0)color(RED);
        p->HP+=dmg;
        if(p->HP>p->HPmax)p->HP=p->HPmax;
        if(p->HP<0)p->HP=0;
        if(dmg<0)showmessage(s+"�ܵ�"+d+"���˺���");
        else if(dmg>0)showmessage(s+"�ָ�"+d+"��������");
    }
    else if(bar==MPbar)
    {
        color(BLUE);
        p->MP+=dmg;
        if(p->MP>p->MPmax)p->MP=p->MPmax;
        if(p->MP<0)p->MP=0;
        if(dmg<0)showmessage(s+"����"+d+"�㷨����");
        else if(dmg>0)showmessage(s+"�ָ�"+d+"�㷨����");
    }
    else
    {
        color(CYAN);
        p->move+=dam;
        p->move+=0.00000001;
        if(p->move>1)p->move=1;
        if(p->move<0)p->move=0;
        showmessage(s+percent(dam)+"�ж�����");
        drawmvbar(p->move,p->who);
    }
    showbar(*p);
    return dmg;
}
void showbar(status p)
{
    if(p.who)
    {
        double per;
        per=(double)p.HP/p.HPmax;
        gotoxy(2,37);
        if(per>0.6)color(GREEN);
        else if(per<0.3)color(RED);
        else color(YELLOW);
        drawbar(per);
        per=(double)p.MP/p.MPmax;
        gotoxy(2,39);
        color(BLUE);
        drawbar(per);
        color(WHITE);
        gotoxy(27,37);
        cout<<"             ";
        gotoxy(27,37);
        cout<<p.HP<<'/'<<p.HPmax;
        gotoxy(27,38);
        cout<<'+'<<p.HPrec;
        gotoxy(27,39);
        cout<<"             ";
        gotoxy(27,39);
        cout<<p.MP<<'/'<<p.MPmax;
        gotoxy(27,40);
        cout<<'+'<<p.MPrec;
    }
    else
    {
        double per;
        per=(double)p.HP/p.HPmax;
        gotoxy(2,2);
        if(per>0.6)color(GREEN);
        else if(per<0.3)color(RED);
        else color(YELLOW);
        drawbar(per);
        per=(double)p.MP/p.MPmax;
        gotoxy(2,4);
        color(BLUE);
        drawbar(per);
        color(WHITE);
        gotoxy(27,2);
        cout<<"             ";
        gotoxy(27,2);
        cout<<p.HP<<'/'<<p.HPmax;
        gotoxy(27,3);
        cout<<'+'<<p.HPrec;
        gotoxy(27,4);
        cout<<"             ";
        gotoxy(27,4);
        cout<<p.MP<<'/'<<p.MPmax;
        gotoxy(27,5);
        cout<<'+'<<p.MPrec;
    }
}
void showsta(status p)
{
    if(p.who)
    {
        status f;
        f=myrole.battlestatus(true);
        gotoxy(47,35);
        writenum(p.atk,f.atk);
        gotoxy(58,35);
        writenum(p.def,f.def);
        gotoxy(69,35);
        writenum(p.abp,f.abp);
        gotoxy(80,35);
        writenum(p.abr,f.abr);
        gotoxy(47,36);
        writenum(p.spd,f.spd);
        gotoxy(58,36);
        writenum(p.avd,f.avd);
        gotoxy(69,36);
        writenum(p.crt,f.crt);
        gotoxy(80,36);
        writenum(p.hit,f.hit);
    }
    else
    {
        status f;
        f=enemyrole.battlestatus(false);
        gotoxy(47,0);
        writenum(p.atk,f.atk);
        gotoxy(58,0);
        writenum(p.def,f.def);
        gotoxy(69,0);
        writenum(p.abp,f.abp);
        gotoxy(80,0);
        writenum(p.abr,f.abr);
        gotoxy(47,1);
        writenum(p.spd,f.spd);
        gotoxy(58,1);
        writenum(p.avd,f.avd);
        gotoxy(69,1);
        writenum(p.crt,f.crt);
        gotoxy(80,1);
        writenum(p.hit,f.hit);
    }
}
void showbuff(status p)
{
    int i;
    color(WHITE);
    if(p.who)gotoxy(5,33);
    else gotoxy(5,7);
    cout<<"                                                                                                                     ";
    if(p.who)gotoxy(5,33);
    else gotoxy(5,7);
    for(i=0; i<8; i++)
    {
        if(p.attribute[i].duration)
        {
            if(p.attribute[i].ratio>=0)color(GREEN);
            else color(RED);
            switch(i)//����ǿ����������
            {
            case 0:
                cout<<p.attribute[i].duration<<'x'<<"����"<<percent(p.attribute[i].ratio)<<' ';
                break;
            case 1:
                cout<<p.attribute[i].duration<<'x'<<"����"<<percent(p.attribute[i].ratio)<<' ';
                break;
            case 2:
                cout<<p.attribute[i].duration<<'x'<<"��ǿ"<<percent(p.attribute[i].ratio)<<' ';
                break;
            case 3:
                cout<<p.attribute[i].duration<<'x'<<"ħ��"<<percent(p.attribute[i].ratio)<<' ';
                break;
            case 4:
                cout<<p.attribute[i].duration<<'x'<<"�ٶ�"<<percent(p.attribute[i].ratio)<<' ';
                break;
            case 5:
                cout<<p.attribute[i].duration<<'x'<<"����"<<percent(p.attribute[i].ratio)<<' ';
                break;
            case 6:
                cout<<p.attribute[i].duration<<'x'<<"����"<<percent(p.attribute[i].ratio)<<' ';
                break;
            case 7:
                cout<<p.attribute[i].duration<<'x'<<"����"<<percent(p.attribute[i].ratio)<<' ';
                break;
            }
        }
    }
    for(i=0; i<4; i++) //��Ѫȼ���ж�ѣ��
    {
        color(RED);
        if(p.debuff[i].duration)
        {
            char d[5];
            itoa((int)p.debuff[i].ratio,d,10);
            switch(i)
            {
            case 0:
                cout<<p.debuff[i].duration<<'x'<<"��Ѫ-"<<d<<' ';
                break;
            case 1:
                cout<<p.debuff[i].duration<<'x'<<"ȼ��-"<<d<<' ';
                break;
            case 2:
                cout<<p.debuff[i].duration<<'x'<<"�ж�-"<<d<<' ';
                break;
            case 3:
                cout<<p.debuff[i].duration<<'x'<<"ѣ��"<<' ';
                break;
            }
        }
    }
}
string percent(double p)
{
    char a[5];
    string s;
    if(p>=0)s="+";
    else p=-p,s="-";
    p+=0.0000001;
    itoa((int)(p*100),a,10);
    s+=a;
    s+='%';
    return s;
}
void showskill()
{
    color(WHITE);
    gotoxy(5,35);
    cout<<myrole.name<<'('<<"LV."<<player.lv<<classesname[player.classes]<<')';
    switch(player.classes)
    {
    case 0://սʿ
        if(player.lv>=4)
        {
            gotoxy(42,38);
            cout<<"��Ѫ:�������ез�ʱ������һ����Ȼ�����ָ���";
        }
        if(player.lv>=10)
        {
            gotoxy(42,39);
            cout<<"�ͻ�:�������ез�ʱ��ÿ���3���˺�����ٶ�";
            gotoxy(42,40);
            cout<<"��1%�ж�����";
        }
        break;
    case 1://��ʦ
        if(player.lv>=4)
        {
            gotoxy(42,38);
            cout<<"�ȷ�:�������ез�ʱ������һ����Ȼ�����ָ���";
        }
        if(player.lv>=10)
        {
            gotoxy(42,39);
            cout<<"��λת��:ս����ʼʱ�ͽ��й���������50%��";
            gotoxy(42,40);
            cout<<"�ж�����";
        }
        break;
    case 2://�̿�
        if(player.lv>=4)
        {
            gotoxy(42,38);
            cout<<"˫ذ:�������ез�ʱ����50%������������˺���";
        }
        if(player.lv>=10)
        {
            gotoxy(42,39);
            cout<<"�Ż�����:�غϽ���ʱ����20%�������̽���һ����";
            gotoxy(42,40);
            cout<<"��Ļغϡ�";
        }
        break;
    case 3://����ʦ
        if(player.lv>=4)
        {
            gotoxy(42,38);
            cout<<"��:�غϽ���ʱ��ʹ�з����֢״�����غ�+1��";
        }
        if(player.lv>=10)
        {
            gotoxy(42,39);
            cout<<"�������:�غϽ���ʱ�ָ�3%���������ֵ�����";
            gotoxy(42,40);
            cout<<"����ֵ��";
        }
        break;
    case 4://��ǹ��
        s_showbullet(&player);
        if(player.lv>=4)
        {
            gotoxy(42,38);
            cout<<"�����ӵ�:�ӵ����ез�ʱ��ÿ��5�㷨ǿ�������";
            gotoxy(42,39);
            cout<<"�����������ֵ1%��ħ���˺���";
        }
        if(player.lv>=10)
        {
            gotoxy(42,40);
            cout<<"�������:�ӵ����ез�ʱ��ʹ���ж������롣";
        }
        break;
    case 5://Ӱ��ʿ
        if(player.lv>=4)
        {
            gotoxy(42,38);
            cout<<"նӰ:���������⸽��100%��ǿ��ħ���˺���";
        }
        if(player.lv>=10)
        {
        	gotoxy(42,39);
            cout<<"��Ӱ��:�غϽ���ʱ��ÿ��ʧ1%������ֵ�����1%";
            gotoxy(42,40);
            cout<<"���ٶȣ�����1�غϡ�";
        }
        break;
    }
    if(!pvp)
    {
        gotoxy(5,0);
        cout<<enemyrole.name<<'('<<"LV."<<enemy.lv<<')';
        enemyrole.sskp();
    }
    else
    {
        gotoxy(5,0);
        cout<<enemyrole.name<<'('<<"LV."<<enemy.lv<<classesname[enemy.classes]<<')';
        switch(enemy.classes)
        {
        case 0://սʿ
            if(enemy.lv>=4)
            {
                gotoxy(42,3);
                cout<<"��Ѫ:�������ез�ʱ������һ����Ȼ�����ָ���";
            }
            if(enemy.lv>=10)
            {
                gotoxy(42,4);
                cout<<"�ͻ�:�������ез�ʱ��ÿ���3���˺�����ٶ�";
                gotoxy(42,5);
                cout<<"��1%�ж�����";
            }
            break;
        case 1://��ʦ
            if(enemy.lv>=4)
            {
                gotoxy(42,3);
                cout<<"�ȷ�:�������ез�ʱ������һ����Ȼ�����ָ���";
            }
            if(enemy.lv>=10)
            {
                gotoxy(42,4);
                cout<<"��λת��:ս����ʼʱ�Լ����й���������50%��";
                gotoxy(42,5);
                cout<<"�ж�����";
            }
            break;
        case 2://�̿�
            if(enemy.lv>=4)
            {
                gotoxy(42,3);
                cout<<"˫ذ:�������ез�ʱ����50%������������˺���";
            }
            if(enemy.lv>=10)
            {
                gotoxy(42,4);
                cout<<"�Ż�����:�غϽ���ʱ����20%�ĸ������̽���һ��";
                gotoxy(42,5);
                cout<<"����Ļغϡ�";
            }
            break;
        case 3://����ʦ
            if(player.lv>=4)
            {
                gotoxy(42,3);
                cout<<"��:�غϽ���ʱ��ʹ�з����֢״�����غ�+1��";
            }
            if(player.lv>=10)
            {
                gotoxy(42,4);
                cout<<"�������:�غϽ���ʱ�ָ�3%���������ֵ�����";
                gotoxy(42,5);
                cout<<"����ֵ��";
            }
            break;
        case 4://��ǹ��
            s_showbullet(&enemy);
            if(player.lv>=4)
            {
                gotoxy(42,3);
                cout<<"�����ӵ�:�ӵ����ез�ʱ��ÿ��5�㷨ǿ�������";
                gotoxy(42,4);
                cout<<"�����������ֵ1%��ħ���˺���";
            }
            if(player.lv>=10)
            {
                gotoxy(42,5);
                cout<<"�������:�ӵ����ез�ʱ��ʹ���ж������롣";
            }
            break;
        case 5://Ӱ��ʿ
        if(player.lv>=4)
        {
            gotoxy(42,3);
            cout<<"նӰ:���������⸽��100%��ǿ��ħ���˺���";
        }
        if(player.lv>=10)
        {
        	gotoxy(42,4);
            cout<<"��Ӱ��:�غϽ���ʱ��ÿ��ʧ1%������ֵ�����1%��";
            gotoxy(42,5);
            cout<<"�ٶȣ�����1�غϡ�";
        }
        break;
        }
    }
}
//���ܣ�սʿ
void w_bloodsuck(status* p)
{
    //��Ѫ
    //����:�������е���ʱ������һ����Ȼ�����ָ���
    string s;
    if(p->who)s=myrole.name;
    else s=enemyrole.name;
    color(WHITE);
    showmessage(s+"����������Ѫ������һ����Ȼ�����ָ���");
    damage(p,RE,p->HPrec,HPbar);
}
void w_beatback(status* p,double ham)
{
    //�ͻ�
    //����:�������е���ʱ��ÿ��3�㹥��������ٶԷ�1%�ж�����
    string s;
    status *e;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    color(WHITE);
    showmessage(s+"���������ͻ������˶Է��ж�����");
    damage(e,RE,0.01*ham/3,MVbar);
}
void w_0attack(status* p)
{
    //����
    //������,����80%,����20%:�Եз�������ͨ��������ɻ��ڹ������������˺���
    string s;
    status *e;
    bool hit=false;
    double ham;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="���й�����";
    if(hitthat((double)(p->hit+100)/(e->avd+100)*0.8))
    {
        hit=true;
        if(hitthat((double)(p->crt+100)/100*0.2))
        {
            s+="��������������˺���";
            ham=1.5*p->atk;
        }
        else
        {
            s+="��������˺���";
            ham=p->atk;
        }
    }
    else s+="δ���С�";
    PlaySound(w_0,NULL,PM);
    color(WHITE);
    showmessage(s);
    if(hit)ham=damage(e,AD,-ham,HPbar);
    if(hit&&(p->lv>=4))w_bloodsuck(p);
    if(hit&&(p->lv>=10))w_beatback(p,ham);
}
void w_1charge(status* p)
{
    //���
    //����20MP:���г�棬����200%�Ĺ���2�غϲ�����75%�ж�����
    string s;
    if(p->who)s=myrole.name;
    else s=enemyrole.name;
    s+="���г�棬���������������ж�����" ;
    damage(p,RE,-sl[0][1].spend,MPbar);
    p->cd[1]=sl[0][1].cd+1;
    PlaySound(w_1,NULL,PM);
    color(WHITE);
    showmessage(s);
    setbuff(p,ATT,0,2,2);
    if(p->attribute[4].ratio<0)p->attribute[4].duration=0;
    dealbuff(p);
    damage(p,RE,0.8,MVbar);
}
void w_2disarm(status* p)
{
    //��е
    //����20MP,����75%:�ƻ�����װ�������͵���50%�Ĺ����뻤��5�غϡ�
    string s;
    status *e;
    bool hit=false;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="������е��";
    if(hitthat((double)(p->hit+100)/(e->avd+100)))
    {
        s+="���ͶԷ������뻤�ס�";
        hit=true;
    }
    else s+="δ���С�";
    damage(p,RE,-sl[0][2].spend,MPbar);
    p->cd[2]=sl[0][2].cd+1;
    PlaySound(w_2,NULL,PM);
    color(WHITE);
    showmessage(s);
    if(hit)
    {
    	setbuff(e,ATT,0,4,-0.6);
    	setbuff(e,ATT,1,4,-0.6);
        dealbuff(e);
    }
}
void w_3stone(status* p)
{
    //��ʯ֮��
    //����25MP:�Լ�����ʯ����־ǿ������������300%ħ��3�غϲ�������м���״̬��
    string s;
    if(p->who)s=myrole.name;
    else s=enemyrole.name;
    s+="������ʯ֮��������ħ�����������״̬��" ;
    damage(p,RE,-sl[0][3].spend,MPbar);
    p->cd[3]=sl[0][3].cd+1;
    PlaySound(w_3,NULL,PM);
    color(WHITE);
    showmessage(s);
    for(int i=0; i<8; i++)
        if(p->attribute[i].ratio<0)p->attribute[i].ratio=p->attribute[i].duration=0;
    for(int i=0; i<3; i++)p->debuff[i].duration=0;
    setbuff(p,ATT,1,6,2);
   	setbuff(p,ATT,3,6,2);
    dealbuff(p);
}
void w_4cripple(status* p)
{
    //�²д��
    //����20MP,����80%,����25%:�ش��з����ж����������120%�������˺��ͼ���Ч��ͬʱʹ������Ѫ��
    string s;
    status *e;
    bool hit=false;
    double ham;
    int d=4;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="�����²д����";
    if(hitthat((double)(p->hit+100)/(e->avd+100)*0.8))
    {
        hit=true;
        if(hitthat((double)(p->crt+100)/100*0.2))
        {
            s+="��������������˺������ٺ���Ѫ��";
            ham=1.5*1.6*p->atk;
            d=6;
        }
        else
        {
            s+="��������˺������ٺ���Ѫ��";
            ham=1.6*p->atk;
        }
    }
    else s+="δ���С�";
    damage(p,RE,-sl[0][4].spend,MPbar);
    p->cd[4]=sl[0][4].cd+1;
    color(WHITE);
    showmessage(s);
    if(hit)
    {
        PlaySound(w_4,NULL,PM);
        damage(e,AD,-ham,HPbar);
        setbuff(e,ATT,4,d,-0.4);
    	setbuff(e,DEB,0,d,0.25*p->atk);
        dealbuff(e);
    }
    else
    {
        PlaySound(w_0,NULL,PM);
    }
}
void w_5shieldhit(status* p)
{
    //�����ͻ�
    //����30MP,����100%,����50%:ʹ�ö����ͻ����ˣ��Ե�����ɻ��ڻ��׵������˺������˺�ѣ�Ρ�
    string s,w;
    status *e;
    bool hit=false;
    double ham,mvb;
    if(p->who)
    {
        s=myrole.name;
        w=enemyrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        w=myrole.name;
        e=&player;
    }
    s+="���������ͻ���";
    if(hitthat((double)(p->hit+100)/(e->avd+100)))
    {
        hit=true;
        if(hitthat((double)(p->crt+100)/100*0.5))
        {
            s+="��������������˺��ͻ���";
            ham=1.5*4*p->def;
            mvb=0.75;
        }
        else
        {
            s+="��������˺��ͻ���";
            ham=4*p->def;
            mvb=0.5;
        }
    }
    else s+="δ���С�";
    damage(p,RE,-sl[0][5].spend,MPbar);
    p->cd[5]=sl[0][5].cd+1;
    PlaySound(w_5,NULL,PM);
    color(WHITE);
    showmessage(s);
    if(hit)
    {
        damage(e,AD,-ham,HPbar);
        damage(e,RE,-mvb,MVbar);
        if(e->move<=0.0000001)
        {
            showmessage(w+"�ж������ף���ѣ�Ρ�");
            setbuff(e,DEB,3,1,0);
            dealbuff(e);
        }
    }
}
void w_6bloodwake(status* p)
{
    //Ѫ������
    //����30MP:ͨ�����ϵķ�������Ѫ����ÿ��ʧ1%������ֵ�����2%�Ĺ���4�غϣ����ÿ��1�㷨ǿ��ָ�2%����������ֵ��
    string s;
    double ham;
    if(p->who)s=myrole.name;
    else s=enemyrole.name;
    s+="�ͷ�Ѫ�����ѣ��������������ָ�����ֵ��" ;
    damage(p,RE,-sl[0][6].spend,MPbar);
    p->cd[6]=sl[0][6].cd+1;
    PlaySound(w_6,NULL,PM);
    color(WHITE);
    showmessage(s);
    setbuff(p,ATT,0,4,2*(1-(double)p->HP/p->HPmax));
    dealbuff(p);
    ham=(double)((p->HPmax-p->HP)*p->abp)/50;
    damage(p,RE,ham,HPbar);
}
void w_7rage(status* p)
{
    //����֮��
    //����10MP,����75%,����10%:�ͷŻ���֮�������ĵ�ǰ����ֵ��20%���Ե�����ɸ���ֵ��������ʵ�˺���δ����ʱ������������ֵ��
    string s;
    status *e;
    bool hit=false;
    double ham;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="�ͷ���������";
    damage(p,RE,-sl[0][7].spend,MPbar);
    p->cd[7]=sl[0][7].cd+1;
    ham=(int)(0.2*p->HP);
    damage(p,RE,-ham,HPbar);
    if(hitthat((double)(p->hit+100)/(e->avd+100)*0.8))
    {
        hit=true;
        if(hitthat((double)(p->crt+100)/100*0.4))
        {
            s+="�����������ʵ�˺���";
            ham*=3;
        }
        else
        {
            s+="�����ʵ�˺���";
            ham*=2;
        }
    }
    else s+="δ���У���������ֵ��";
    PlaySound(w_7,NULL,PM);
    color(WHITE);
    showmessage(s);
    if(hit)damage(e,RE,-ham,HPbar);
    else damage(p,RE,ham,HPbar);
}
//���ܣ���ʦ
void m_manasuck(status* p)
{
    //�ȷ�
    //����:�������е���ʱ������һ����Ȼ�����ָ���
    string s;
    if(p->who)s=myrole.name;
    else s=enemyrole.name;
    color(WHITE);
    showmessage(s+"���������ȷ�������һ����Ȼ�����ָ���");
    damage(p,RE,p->MPrec,MPbar);
}
void m_phaseblink(status* p)
{
    //��λת��
    //����:���й���ʱ������50%���ж�����
    string s;
    if(p->who)s=myrole.name;
    else s=enemyrole.name;
    color(WHITE);
    showmessage(s+"����������λת�ƣ������ж�����");
    damage(p,RE,0.5,MVbar);
}
void m_0attack(status* p)
{
    //����
    //������,����80%,����20%:�Եз�������ͨ��������ɻ��ڹ������������˺���
    string s;
    status *e;
    bool hit=false;
    double ham;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="���й�����";
    if(hitthat((double)(p->hit+100)/(e->avd+100)*0.8))
    {
        hit=true;
        if(hitthat((double)(p->crt+100)/100*0.2))
        {
            s+="��������������˺���";
            ham=1.5*p->atk;
        }
        else
        {
            s+="��������˺���";
            ham=p->atk;
        }
    }
    else s+="δ���С�";
    PlaySound(m_0,NULL,PM);
    color(WHITE);
    showmessage(s);
    if(hit)damage(e,AD,-ham,HPbar);
    if(hit&&(p->lv>=4))m_manasuck(p);
    if(p->lv>=10)m_phaseblink(p);
}
void m_1enchants(status* p)
{
    //������ħ
    //����20MP:Ϊ��������ħ���������൱�ڷ�ǿ�Ĺ�����������5�غ�
    string s;
    if(p->who)s=myrole.name;
    else s=enemyrole.name;
    status f;
    if(p->who)f=myrole.battlestatus(true);
    else f=enemyrole.battlestatus(false);
    s+="Ϊ������ħ�����������������̹�����" ;
    damage(p,RE,-sl[1][1].spend,MPbar);
    p->cd[1]=sl[1][1].cd+1;
    PlaySound(m_1,NULL,PM);
    color(WHITE);
    showmessage(s);
    setbuff(p,ATT,0,3,(double)p->abp/f.atk);
    dealbuff(p);
    Sleep(1541);
    m_0attack(p);
}
void m_2stormshieldl(status* p)
{
    //�籩��
    //����50MP:����30%�ٶȣ�ÿ��1�㷨ǿ����5%���ף�����6�غ�
    string s;
    if(p->who)s=myrole.name;
    else s=enemyrole.name;
    s+="�ͷŷ籩�ܣ������������׺��ٶȡ�" ;
    damage(p,RE,-sl[1][2].spend,MPbar);
    p->cd[2]=sl[1][2].cd+1;
    PlaySound(m_2,NULL,PM);
    color(WHITE);
    showmessage(s);
    setbuff(p,ATT,1,5,0.01*p->abp);
    setbuff(p,ATT,4,5,0.3);
    dealbuff(p);
}
void m_3snowstorm(status* p)
{
    //����ѩ
    //����60MP,����80%,����20%:�ٻ�����ѩ�����з������6�λ���60%��ǿ��ħ���˺���ÿ���˺��������������뱩����ÿ�����л��ḽ��1�غϵı���Ч��(����40%�ٶȺ�60%����)��
    string s;
    status *e;
    double ham=0;
    int hit=0,crt=0;
    char d[2];
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="�ͷű���ѩ��";
    damage(p,RE,-sl[1][3].spend,MPbar);
    p->cd[3]=sl[1][3].cd+1;
    for(int i=1; i<=6; i++)
    {
        if(hitthat((double)(p->hit+100)/(e->avd+100)*0.8))
        {
            hit++;
            if(hitthat((double)(p->crt+100)/100*0.2))
            {
                crt++;
                ham+=1.5*0.4*p->abp;
            }
            else
            {
                ham+=0.4*p->abp;
            }
        }
    }
    if(hit==0)
    {
        s+="δ���С�";
        PlaySound(m_3,NULL,PM);
        color(WHITE);
        showmessage(s);
    }
    else
    {
        s+="����";
        itoa(hit,d,10);
        s+=d;
        s+="�α���";
        itoa(crt,d,10);
        s+=d;
        s+="�Σ����ħ���˺��ͱ�����";
        PlaySound(m_3,NULL,PM);
        color(WHITE);
        showmessage(s);
        damage(e,AP,-ham,HPbar);
        setbuff(e,ATT,4,hit,-0.4);
        setbuff(e,ATT,5,hit,-0.8);
        dealbuff(e);
    }
}
void m_4icelance(status* p)
{
    //��ǹ��
    //����40MP,����80%,����40%:��з������ǹ����ɻ���200%��ǿ��ħ���˺����������˺�������
    string s;
    status *e;
    bool hit=false;
    double ham;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="�ͷű�ǹ��";
    if(hitthat((double)(p->hit+100)/(e->avd+100)*0.8))
    {
        hit=true;
        if(hitthat((double)(p->crt+100)/100*0.3))
        {
            s+="���������ħ���˺�";
            ham=1.5*1.5*p->abp;
        }
        else
        {
            s+="���ħ���˺�";
            ham=1.5*p->abp;
        }
        if(e->attribute[4].ratio<0&&e->attribute[5].ratio<0)
		{
			s+="���Ա���Ŀ���˺�������";
			ham*=2; 
		} 
    }
    else s+="δ���С�";
    damage(p,RE,-sl[1][4].spend,MPbar);
    p->cd[4]=sl[1][4].cd+1;
    PlaySound(m_4,NULL,PM);
    color(WHITE);
    showmessage(s);
    if(hit)damage(e,AP,-ham,HPbar);
}
void m_5mindblast(status* p)
{
    //������
    //����60MP,����100%,����40%:��ħ��ֱ���з����飬��ɻ���200%��ǿ����ʵ�˺��������͵з�30%�ķ�ǿ��ħ��3�غϣ��ü��ܱ���ʱ��ѣ�εз�1�غ�
    string s;
    status *e;
    bool hit=false;
    double ham;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="�ͷ������𱬣�";
    if(hitthat((double)(p->hit+100)/(e->avd+100)*2))
    {
        hit=true;
        if(hitthat((double)(p->crt+100)/100*0.5))
        {
            s+="�����������ʵ�˺����ͷ�ǿħ����ѣ�Ρ�";
            ham=1.5*1.2*p->abp;
            setbuff(e,DEB,3,1,0);
        }
        else
        {
            s+="�����ʵ�˺����ͷ�ǿħ����";
            ham=1.2*p->abp;
        }
    }
    else s+="δ���С�";
    damage(p,RE,-sl[1][5].spend,MPbar);
    p->cd[5]=sl[1][5].cd+1;
    PlaySound(m_5,NULL,PM);
    color(WHITE);
    showmessage(s);
    if(hit)
    {
        damage(e,RE,-ham,HPbar);
        setbuff(e,ATT,2,3,-0.5);
        setbuff(e,ATT,3,3,-0.5);
        dealbuff(e);
    }
}
void m_6muse(status* p)
{
    //ڤ��
    //����15MP,��ȴ9�غ�:����һ��ڤ�룬ÿ��2�㷨ǿ��ָ�1%���������ֵͬʱ�������м���1�غϵ���ȴʱ�䡣
    string s;
    double ham;
    if(p->who)s=myrole.name;
    else s=enemyrole.name;
    s+="����ڤ�룬�ָ�����ֵ�����ټ�����ȴʱ�䡣" ;
    damage(p,RE,-sl[1][6].spend,MPbar);
    p->cd[6]=sl[1][6].cd+1;
    PlaySound(m_6,NULL,PM);
    color(WHITE);
    showmessage(s);
    ham=(double)(p->HPmax*p->abp)/200;
    damage(p,RE,ham,HPbar);
    for(int i=0; i<8; i++)if(p->cd[i])p->cd[i]--;
}
void m_7manaburn(status* p)
{
    //����ȼ��
    //����30%MP,��ȴ2�غ�,����100%,����10%:����������������ȼ�з��ķ��������ĵз��ĵ�ֵ�������Եз���������ķ�����ֵ��ħ���˺���
    string s;
    status *e;
    bool hit=false;
    double ham;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="�ͷŷ���ȼ�գ�";
    damage(p,RE,-sl[1][7].spend,MPbar);
    p->cd[7]=sl[1][7].cd+1;
    ham=(int)(0.2*p->MP);
    damage(p,RE,-ham,MPbar);
    if(hitthat((double)(p->hit+100)/(e->avd+100)))
    {
        hit=true;
        if(hitthat((double)(p->crt+100)/100*0.2))
        {
            s+="���������ħ���˺���������ʧ��ȼ�ա�";
            setbuff(e,DEB,1,2,ham*0.5);
            ham*=3;
        }
        else
        {
            s+="���ħ���˺���������ʧ��ȼ�ա�";
            setbuff(e,DEB,1,2,ham*0.5);
            ham*=2;
        }
    }
    else s+="δ���С�";
    PlaySound(m_7,NULL,PM);
    color(WHITE);
    showmessage(s);
    if(hit)
    {
    	damage(e,AP,-ham,HPbar);
        damage(e,RE,-ham,MPbar);
        dealbuff(e);
    }
}
//���ܣ��̿�
void a_doubledagger(status* p)
{
    //˫ذ:����50%���������˺���
    string s;
    status *e;
    double ham;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="��������˫ذ��";
    if(hitthat(0.5))
    {
        if(hitthat((double)(p->crt+100)/100*0.4))
        {
            s+="������";
            ham=1.5*p->atk;
        }
        else
        {
            ham=p->atk;
        }
        Sleep(300);
        PlaySound(a_0,NULL,PM);
        color(WHITE);
        showmessage(s+"��������˺���");
        damage(e,AD,-ham,HPbar);
    }
}
void a_preparation(status* p)
{
    //�Ż�����:�غϽ���ʱ����20%�ĸ������̽���һ������Ļغϡ�
    string s;
    if(p->who)s=myrole.name;
    else s=enemyrole.name;
    if(hitthat(0.2))
    {
        color(WHITE);
        showmessage(s+"���������Ż����������ж���غϡ�");
        damage(p,RE,1,MVbar);
    }
}
void a_0attack(status* p)
{
    //����
    //������,����80%,����20%:�Եз�������ͨ��������ɻ��ڹ������������˺���
    string s;
    status *e;
    bool hit=false;
    double ham;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="���й�����";
    if(hitthat((double)(p->hit+100)/(e->avd+100)*0.8))
    {
        hit=true;
        if(hitthat((double)(p->crt+100)/100*0.2))
        {
            s+="��������������˺���";
            ham=1.5*p->atk;
        }
        else
        {
            s+="��������˺���";
            ham=p->atk;
        }
    }
    else s+="δ���С�";
    PlaySound(a_0,NULL,PM);
    color(WHITE);
    showmessage(s);
    if(hit)damage(e,AD,-ham,HPbar);
    if(hit&&(p->lv>=4))a_doubledagger(p);
}
void a_1assassinate(status* p)
{
    //��ɱ
    //����25MP,��ȴ2�غ�,����100%,����40%:�Եз�����������ɱ����ɻ���160%�������������˺����з�ÿ��ʧ1%����ֵ���������ü���3%���˺�
    string s;
    status *e;
    bool hit=false;
    double ham,up;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="���д�ɱ��";
    up=3*(1-(double)e->HP/e->HPmax);
    ham=1.6*p->atk*(1+up);
    if(hitthat((double)(p->hit+100)/(e->avd+100)))
    {
        hit=true;
        if(hitthat((double)(p->crt+100)/100*0.4))
        {
            s+="��������������˺����˺�";
            s+=percent(up);
            s+="��";
            ham*=1.5;
        }
        else
        {
            s+="��������˺����˺�";
            s+=percent(up);
            s+="��";
        }
    }
    else s+="δ���С�";
    damage(p,RE,-sl[2][1].spend,MPbar);
    p->cd[1]=sl[2][1].cd+1;
    PlaySound(a_1,NULL,PM);
    color(WHITE);
    showmessage(s);
    if(hit)damage(e,AD,-ham,HPbar);
}
void a_2blindingpowder(status* p)
{
    //��ä��
    //����25MP,��ȴ5�غ�,����100%:��з�Ͷ����ä������ʹ������ä�����͵з�75%�����кͱ���4�غ�
    string s;
    status *e;
    bool hit=false;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="Ͷ����ä��������";
    if(hitthat((double)(p->hit+100)/(e->avd+100)*0.8))
    {
        s+="���ͶԷ����кͱ�����";
        hit=true;
    }
    else s+="δ���С�";
    damage(p,RE,-sl[2][2].spend,MPbar);
    p->cd[2]=sl[2][2].cd+1;
    PlaySound(a_2,NULL,PM);
    color(WHITE);
    showmessage(s);
    if(hit)
    {
    	setbuff(e,ATT,6,4,-0.5);
    	setbuff(e,ATT,7,4,-0.5);
        dealbuff(e);
    }
}
void a_3sneak(status* p)
{
    //Ǳ��
    //����Ǳ��״̬������400%�����ܡ�����60%�ٶ�1�غϣ�ͬʱ���400%����2�غϲ��������֢״
    string s;
    if(p->who)s=myrole.name;
    else s=enemyrole.name;
    s+="����Ǳ��״̬�������ٶȡ��������ܺͱ��������֢״��" ;
    damage(p,RE,-sl[2][3].spend,MPbar);
    p->cd[3]=sl[2][3].cd+1;
    PlaySound(a_3,NULL,PM);
    color(WHITE);
    showmessage(s);
    setbuff(p,ATT,4,1,-0.2);
    setbuff(p,ATT,5,1,3);
    setbuff(p,ATT,6,2,1);
    for(int i=0; i<3; i++)p->debuff[i].duration=0;
    dealbuff(p);
}
void a_4poisondagger(status* p)
{
    //�㶾ذ��
    //����40MP,��ȴ4�غ�,����80%,����20%:��з�Ͷ��һ�Ѵ㶾ذ�ף�����൱�ڵз���ǰ����ֵ20%�������˺�������5�غ��˺�Ϊ100%��ǿ���ж�
    string s;
    status *e;
    bool hit=false;
    double ham;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="Ͷ���㶾ذ�ף�";
    if(hitthat((double)(p->hit+100)/(e->avd+100)*0.8))
    {
        hit=true;
        if(hitthat((double)(p->crt+100)/100*0.3))
        {
            s+="��������������˺����ж���";
            ham=1.5*0.2*e->HP;
        }
        else
        {
            s+="��������˺����ж���";
            ham=0.2*e->HP;
        }
    }
    else s+="δ���С�";
    damage(p,RE,-sl[2][4].spend,MPbar);
    p->cd[4]=sl[2][4].cd+1;
    PlaySound(a_4,NULL,PM);
    color(WHITE);
    showmessage(s);
    if(hit)
    {
        damage(e,AD,-ham,HPbar);
        setbuff(e,DEB,2,4,e->HPmax*(5+p->abp*0.2)*0.01);
        dealbuff(e);
    }
}
void a_5stickstrike(status* p)
{
    //�ƹ�
    //����10MP,��ȴ8�غ�,����100%,����20%:���䲻����ͻ��з�ͷ����ʹ����ѣ��1(����:2)�غ�
    string s;
    status *e;
    bool hit=false;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="�����ƹ���";
    if(hitthat((double)(p->hit+100)/(e->avd+100)))
    {
        hit=true;
        if(hitthat((double)(p->crt+100)/100*0.1))
        {
            s+="���������ͻ��ײ�ѣ�Ρ�";
            setbuff(e,DEB,3,2,0);
        }
        else
        {
            s+="���ͻ��ײ�ѣ�Ρ�";
            setbuff(e,DEB,3,1,0);
        }
    }
    else s+="δ���С�";
    damage(p,RE,-sl[2][5].spend,MPbar);
    p->cd[5]=sl[2][5].cd+1;
    PlaySound(a_5,NULL,PM);
    color(WHITE);
    showmessage(s);
    if(hit)
	{
		setbuff(e,ATT,1,3,-0.4);
		dealbuff(e);
	} 

}
void a_6weakagent(status* p)
{
    //����ҩ��
    //����40MP,��ȴ2�غ�,����100%:��з�Ͷ��һƿ����ҩ��ʹ�õз�״̬����3�غϣ�����״̬ʱ����50%�Ĺ�������ǿ���ٶ�
    string s;
    status *e;
    bool hit=false;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="Ͷ������ҩ����";
    if(hitthat((double)(p->hit+100)/(e->avd+100)*0.8))
    {
        s+="���ͶԷ������뷨ǿ��";
        hit=true;
    }
    else s+="δ���С�";
    damage(p,RE,-sl[2][6].spend,MPbar);
    p->cd[6]=sl[2][6].cd+1;
    PlaySound(a_6,NULL,PM);
    color(WHITE);
    showmessage(s);
    if(hit)
    {
    	setbuff(e,ATT,0,4,-0.5);
    	setbuff(e,ATT,2,4,-0.5);
        dealbuff(e);
    }
}
void a_7fatalrhythm(status* p)
{
    //��������
    //����30MP,��ȴ6�غ�:�Եз�����һ�ι��������غ������еĹ�����������50%�����ٽ���һ�ι���
    string s;
    int k=3;
    if(p->who)s=myrole.name;
    else s=enemyrole.name;
    s+="�����������࣬�������ɴι�����" ;
    damage(p,RE,-sl[2][7].spend,MPbar);
    p->cd[7]=sl[2][7].cd+1;
    color(WHITE);
    showmessage(s);
    a_0attack(p);
    while(k)
    {
        if(hitthat(0.5))
        {
            a_0attack(p);
            Sleep(300);
        }
        else k--;
    }
}
//
void c_vicious(status* p)
{
    //��:�غϽ���ʱ��ʹ�з�֢״�����غ�+1��
    string s;
    status *e;
    int k,d;
    k=rand()%3;
    d=rand()%2;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    for(int i=0; i<3; i++)
    {
        if(e->debuff[k].duration)
        {
            s+="���������񶾣�ʹ�Է�";
            switch(k)
            {
            case 0:
                s+="��Ѫ";
                break;
            case 1:
                s+="ȼ��";
                break;
            case 2:
                s+="�ж�";
                break;
            }
            color(WHITE);
            showmessage(s+"�����غ�+1��");
            e->debuff[k].duration++;
            dealbuff(e);
            return;
        }
        else if(d)INC(k,3);
        else DEC(k,3);
    }
}
void c_boundary(status* p)
{
    //�������:�غϽ���ʱ�ָ�3%���������ֵ�������ֵ
    string s;
    if(p->who)s=myrole.name;
    else s=enemyrole.name;
    color(WHITE);
    showmessage(s+"��������������磬�ָ������ͷ�����");
    damage(p,RE,0.03*p->HPmax,HPbar);
    damage(p,RE,0.03*p->MPmax,MPbar);
}
void c_0attack(status* p)
{
    //����
    //������,����80%,����20%:�Եз�������ͨ��������ɻ��ڹ������������˺���
    string s;
    status *e;
    bool hit=false;
    double ham;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="���й�����";
    if(hitthat((double)(p->hit+100)/(e->avd+100)*0.8))
    {
        hit=true;
        if(hitthat((double)(p->crt+100)/100*0.2))
        {
            s+="��������������˺���";
            ham=1.5*p->atk;
        }
        else
        {
            s+="��������˺���";
            ham=p->atk;
        }
    }
    else s+="δ���С�";
    PlaySound(c_0,NULL,PM);
    color(WHITE);
    showmessage(s);
    if(hit)damage(e,AD,-ham,HPbar);
}
void c_1sectumsempra(status* p)
{
    //�����
    //����30MP,��ȴ5�غ�,����100%,����25%:���4(����:6)�غ��˺�Ϊ100%��������Ѫ
    string s;
    status *e;
    bool hit=false;
    int d=4;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="�ͷ�����䣬";
    if(hitthat((double)(p->hit+100)/(e->avd+100)))
    {
        hit=true;
        if(hitthat((double)(p->crt+100)/100*0.25))
        {
            s+="�����������Ѫ��";
            d=6;
        }
        else
        {
            s+="�����Ѫ��";
        }
    }
    else s+="δ���С�";
    damage(p,RE,-sl[3][1].spend,MPbar);
    p->cd[1]=sl[3][1].cd+1;
    PlaySound(c_1,NULL,PM);
    color(WHITE);
    showmessage(s);
    if(hit)
    {
    	setbuff(e,DEB,0,d,p->atk);
        dealbuff(e);
    }
}
void c_2blaze(status* p)
{
    //�һ���
    //����30MP,��ȴ5�غ�,����100%,����25%:���4(����:6)�غ��˺�Ϊ100%��ǿ��ȼ��
    string s;
    status *e;
    bool hit=false;
    int d=4;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="�ͷ��һ��䣬";
    if(hitthat((double)(p->hit+100)/(e->avd+100)))
    {
        hit=true;
        if(hitthat((double)(p->crt+100)/100*0.25))
        {
            s+="���������ȼ�ա�";
            d=6;
        }
        else
        {
            s+="���ȼ�ա�";
        }
    }
    else s+="δ���С�";
    damage(p,RE,-sl[3][2].spend,MPbar);
    p->cd[2]=sl[3][2].cd+1;
    PlaySound(c_2,NULL,PM);
    color(WHITE);
    showmessage(s);
    if(hit)
    {
    	setbuff(e,DEB,1,d,p->abp);
        dealbuff(e);
    }
}
void c_3fivepoisons(status* p)
{
    //�嶾��
    //����40MP,��ȴ5�غ�,����100%,����25%:���4(����:6)�غ��˺�Ϊ50%����50%��ǿ���ж�
    string s;
    status *e;
    bool hit=false;
    int d=4;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="�ͷ��嶾�䣬";
    if(hitthat((double)(p->hit+100)/(e->avd+100)))
    {
        hit=true;
        if(hitthat((double)(p->crt+100)/100*0.25))
        {
            s+="����������ж���";
            d=6;
        }
        else
        {
            s+="����ж���";
        }
    }
    else s+="δ���С�";
    damage(p,RE,-sl[3][3].spend,MPbar);
    p->cd[3]=sl[3][3].cd+1;
    PlaySound(c_3,NULL,PM);
    color(WHITE);
    showmessage(s);
    if(hit)
    {
    	setbuff(e,DEB,2,d,0.5*(p->atk+p->abp));
        dealbuff(e);
    }
}
void c_4daemon(status* p)
{
    //�ػ���
    //���ݵз������뷨ǿ�ı���������Ӧ�������ܺ��൱��120%��ǿ�Ļ�����ħ��������10�غ�
    string s;
    status *e;
    double k;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="�ͷ��ػ��䣬�����������ס�ħ�����ٶȡ�" ;
    damage(p,RE,-sl[3][4].spend,MPbar);
    p->cd[4]=sl[3][4].cd+1;
    PlaySound(c_4,NULL,PM);
    color(WHITE);
    showmessage(s);
    k=(double)e->atk/(e->atk+e->abp);
    setbuff(p,ATT,4,1,2);
    setbuff(p,ATT,1,6,0.02*p->abp*k);
    setbuff(p,ATT,3,6,0.02*p->abp*(1-k));
    dealbuff(p);
}
void c_5increase(status* p)
{
    //������
    //����10MP,��ȴ1�غ�,����100%:���������з�������֢״��ʹ�з�����֢״�����غ�+1
    string s;
    status *e;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="�ͷ������䣬ʹ�Է�֢״�����غ�+1��";
    damage(p,RE,-sl[3][5].spend,MPbar);
    p->cd[5]=sl[3][5].cd+1;
    PlaySound(c_5,NULL,PM);
    color(WHITE);
    showmessage(s);
    for(int i=0; i<3; i++)
        if(e->debuff[i].duration)e->debuff[i].duration++;
    dealbuff(e);
}
void c_6imperio(status* p)
{
    //�����
    //������,��ȴ10�غ�,����100%:����������������ֵ10%����ʵ�˺���Ϊ�����ָ����ڸ�ֵ����������ֵ
    string s;
    status *e;
    bool hit=false;
    double ham1,ham2;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="�ͷŶ���䣬";
    damage(p,RE,-sl[3][6].spend,MPbar);
    p->cd[6]=sl[3][6].cd+1;
    ham1=(int)(0.2*e->HPmax);
    ham2=(int)(0.2*e->MPmax);
    if(hitthat((double)(p->hit+100)/(e->avd+100)))
    {
        s+="͵ȡ����ֵ�ͷ���ֵ��";
        hit=true;
    }
    else s+="δ���С�";
    PlaySound(c_6,NULL,PM);
    color(WHITE);
    showmessage(s);
    if(hit)
    {
        damage(e,RE,-ham1,HPbar);
        damage(e,RE,-ham2,MPbar);
        damage(p,RE,ham1,HPbar);
        damage(p,RE,ham2,MPbar);
    }
}
void c_7summarycurse(status* p)
{
    //���串����
    //����50MP,��ȴ5�غ�,����100%:����ʩ���ڵз����ϵ���������Ч��������з�����֢״��������֢״�������˺�˲��ʩ���ڵз�
    string s;
    status *e;
    double ham[3],sum=0;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="�ͷ����串�������ܽ�����֢״�˺���";
    damage(p,RE,-sl[3][7].spend,MPbar);
    p->cd[7]=sl[3][7].cd+1;
    PlaySound(c_7,NULL,PM);
    color(WHITE);
    showmessage(s);
    for(int i=0; i<3; i++)
    {
        ham[i]=e->debuff[i].duration*e->debuff[i].ratio;
        e->debuff[i].duration=0;
    }
    dealbuff(e);
    sum+=40*ham[0]/(40+e->def);
    sum+=40*ham[1]/(40+e->abr);
    sum+=ham[2];
    damage(e,RE,-sum,HPbar);
}
//
void s_showbullet(status* p)
{
    if(p->who) gotoxy(53,37);
    else gotoxy(53,2);
    // 
    color(WHITE);
    cout<<"����:";
    if(p->special)color(GREEN);
    else color(RED);
    cout<<p->special;
    color(WHITE);
    cout<<"/6";
}
void s_burstbullet(status* p)
{
    //�����ӵ�:�ӵ����е���ʱ��ÿ��5�㷨ǿ�����������������ֵ1%��ħ���˺���
    string s;
    status *e;
    double ham;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    ham=e->HPmax*0.01*p->abp*0.2;
    color(WHITE);
    showmessage(s+"�������������ӵ������ħ���˺���");
    damage(e,AP,-ham,HPbar);
}
void s_momentumshoot(status* p)
{
    //�������:�ӵ����е���ʱ��ʹ���ж�������
    string s;
    status *e;
    double ham;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    ham=e->move*0.5;
    color(WHITE);
    showmessage(s+"���������������������Է��ж�����");
    damage(e,RE,-ham,MVbar);
}
void s_0attack(status* p)
{
    //����1���ӵ�/������,����ȴ,����80%,����20%:����˷���һ���ӵ������100%�������������˺������������ӵ�ʱ��������װ��������������
    string s;
    status *e;
    bool hit=false;
    double ham;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    if(p->special==0)
    {
        PlaySound(s_1,NULL,PM);
        color(WHITE);
        showmessage(s+"������װ�����ֱ�������");
        p->special=6;
        s_showbullet(p);
        return;
    }
    s+="���й�����";
    p->special--;
    s_showbullet(p);
    if(hitthat((double)(p->hit+100)/(e->avd+100)*0.8))
    {
        hit=true;
        if(hitthat((double)(p->crt+100)/100*0.2))
        {
            s+="��������������˺���";
            ham=1.5*p->atk;
        }
        else
        {
            s+="��������˺���";
            ham=p->atk;
        }
    }
    else s+="δ���С�";
    PlaySound(s_0,NULL,PM);
    color(WHITE);
    showmessage(s);
    if(hit)damage(e,AD,-ham,HPbar);
    if(hit&&(p->lv>=4))s_burstbullet(p);
    if(hit&&(p->lv>=10))s_momentumshoot(p);
}
void s_1quickfire(status* p)
{
    //����30MP+1���ӵ�,��ȴ2�غ�:���ٰ�ǹ�Ե��˽���һ�ι����������һ������غϡ�
    string s;
    if(p->who)s=myrole.name;
    else s=enemyrole.name;
    damage(p,RE,-sl[4][1].spend,MPbar);
    p->cd[1]=sl[4][1].cd+1;
    color(WHITE);
    showmessage(s+"�ͷſ��ٰ�ǹ�����������ж���غϡ�");
    s_0attack(p);
    damage(p,RE,1,MVbar);
}
void s_2deadeyeshoot(status* p)
{
    //����40MP,��ȴ3�غ�,����100%,����20%:��з�Ҫ������һ�ξ�׼��������200%�������������˺���ÿ��1�����ж��������ü���1%���˺�
    string s;
    status *e;
    bool hit=false;
    double ham,up;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="���о�׼�����";
    up=p->hit*0.5*0.01;
    ham=1.6*p->atk*(1+up);
    if(hitthat((double)(p->hit+100)/(e->avd+100)))
    {
        hit=true;
        if(hitthat((double)(p->crt+100)/100*0.2))
        {
            s+="��������������˺����˺�";
            s+=percent(up);
            s+="��";
            ham*=1.5;
        }
        else
        {
            s+="��������˺����˺�";
            s+=percent(up);
            s+="��";
        }
    }
    else s+="δ���С�";
    damage(p,RE,-sl[4][2].spend,MPbar);
    p->cd[2]=sl[4][2].cd+1;
    p->special-=bulletspend[2];
    s_showbullet(p);
    PlaySound(s_2,NULL,PM);
    color(WHITE);
    showmessage(s);
    if(hit)damage(e,AD,-ham,HPbar);
    if(hit&&(p->lv>=4))s_burstbullet(p);
    if(hit&&(p->lv>=10))s_momentumshoot(p);
}
void s_3tacticalcounter(status* p)
{
    //�Եз�����һ��ս�����ƣ�͵ȡ�Է��ж���
    string s;
	status *e;
	bool hit=false;
	double k;
    if(p->who)
	{
		s=myrole.name;
		e=&enemy;
	}
    else 
	{
		s=enemyrole.name;
		e=&player;
	}
    s+="����ս�����ƣ�" ;
    if(hitthat((double)(p->hit+100)/(e->avd+100)*0.8))
    {
    	hit=true;
		s+="͵ȡ�Է��ж�����";
	} 
    else s+="ʧ�ܡ�";
    damage(p,RE,-sl[4][3].spend,MPbar);
    p->cd[3]=sl[4][3].cd+1;
    k=e->move;
    PlaySound(s_3,NULL,PM);
    color(WHITE);
	showmessage(s);
	if(hit)
	{
	    damage(e,RE,-k,MVbar);
	    damage(p,RE,k,MVbar);
	}
}
void s_4interceptingshoot(status* p)
{
    //����60MP,��ȴ6�غ�,����80%,����20%:��з��������������ӵ������3��120%�������������˺���ÿ���ӵ��������������뱩�����������ӵ�ȫ��������ѣ�εз�1�غ�
    string s;
    status *e;
    double ham=0;
    int hit=0;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="����������������������ӵ���";
    damage(p,RE,-sl[4][4].spend,MPbar);
    p->cd[4]=sl[4][4].cd+1;
    color(WHITE);
    showmessage(s);
    for(int i=1; i<=3; i++)
    {
        p->special--;
        s_showbullet(p);
        PlaySound(s_0,NULL,PM);
        if(hitthat((double)(p->hit+100)/(e->avd+100)*0.8))
        {
            hit++;
            if(hitthat((double)(p->crt+100)/100*0.2))
            {
                showmessage("�ӵ����У�������");
                ham=1.5*p->atk;
            }
            else
            {
                showmessage("�ӵ����С�");
                ham=p->atk;
            }
            damage(e,AD,-ham,HPbar);
            if(hit&&(p->lv>=4))s_burstbullet(p);
            if(hit&&(p->lv>=10))s_momentumshoot(p);
        }
        else showmessage("�ӵ�δ���С�");
        Sleep(500);
    }
    if(hit==3)
    {
        showmessage("�ӵ�ȫ�����У����ѣ�Ρ�");
        e->debuff[3].duration=1;
        dealbuff(e);
    }
}
void s_5quickreload(status* p)
{
    //����50MP,��ȴ5�غ�:����һ�ο�����װ��������������������һ������غϡ�
    string s;
    if(p->who)s=myrole.name;
    else s=enemyrole.name;
    damage(p,RE,-sl[4][5].spend,MPbar);
    p->cd[5]=sl[4][5].cd+1;
    PlaySound(s_1,NULL,PM);
    color(WHITE);
    showmessage(s+"���п�����װ����װ�����ж���غϡ�");
    p->special=6;
    s_showbullet(p);
    damage(p,RE,1,MVbar);
}
void s_6deathmarker(status* p)
{
    //�Եз�ʩ��һ��������ǣ�������50%�Ļ�����ħ��2�غ�
    string s;
	status *e;
	bool hit=false;
    if(p->who)
	{
		s=myrole.name;
		e=&enemy;
	}
    else 
	{
		s=enemyrole.name;
		e=&player;
	}
    s+="ʩ��������ǣ�";
    damage(p,RE,-sl[4][6].spend,MPbar);
    p->cd[6]=sl[4][6].cd+1;
    PlaySound(s_6,NULL,PM);
    if(hitthat((double)(p->hit+100)/(e->avd+100)*0.8))
	{
		hit=true;
    	s+="���ͶԷ����׺�ħ����";
    }
    else s+="δ���С�"; 
    color(WHITE);
	showmessage(s);
    if(hit)
    {
    	setbuff(e,ATT,1,2,-0.8);
    	setbuff(e,ATT,3,2,-0.8);
		dealbuff(e);
    }
}
void s_7stormshoot(status* p)
{
    //����80MP,��ȴ8�غ�,����60%,����10%:������з���������������е��ӵ���ÿ���ӵ����150%�������������˺���ÿ���ӵ��������������뱩����
    string s;
    status *e;
    double ham=0;
    int hit=0;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="�ͷű��꼲�䣬��������ʣ���ӵ���";
    damage(p,RE,-sl[4][7].spend,MPbar);
    p->cd[7]=sl[4][7].cd+1;
    color(WHITE);
    showmessage(s);
    while(p->special)
    {
        p->special--;
        s_showbullet(p);
        PlaySound(s_0,NULL,PM);
        if(hitthat((double)(p->hit+100)/(e->avd+100)*0.6))
        {
            hit++;
            if(hitthat((double)(p->crt+100)/100*0.1))
            {
                showmessage("�ӵ����У�������");
                ham=1.5*1.5*p->atk;
            }
            else
            {
                showmessage("�ӵ����С�");
                ham=1.5*p->atk;
            }
            damage(e,AD,-ham,HPbar);
            s_burstbullet(p);
            s_momentumshoot(p);
        }
        else showmessage("�ӵ�δ���С�");
        Sleep(300);
    }
}
//
void d_shadowchop(status* p)
{
	//նӰ:���������⸽��100%��ǿ��ħ���˺���
	string s;
    status *e;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    color(WHITE);
    showmessage(s+"��������նӰ�����ħ���˺���");
    damage(e,AP,-p->abp,HPbar);
}
void d_shadowstep(status* p)
{
	//��Ӱ��:�غϽ���ʱ��ÿ��ʧ1%������ֵ�����1%���ٶȣ�����1�غϡ�
	string s;
	double r;
    if(p->who)s=myrole.name;
    else s=enemyrole.name;
    r=(double)(p->HPmax-p->HP)/p->HPmax;
    if(r>0)
    {
    	color(WHITE);
	    showmessage(s+"����������Ӱ��������ٶȡ�");
	    setbuff(p,ATT,4,1,r);
	    dealbuff(p);
    }
}
void d_0attack(status* p)
{
	//������,����ȴ,����80%,����10%:�Եз�������ͨ���������100%�������������˺���
	string s;
    status *e;
    bool hit=false;
    double ham;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="���й�����";
    if(hitthat((double)(p->hit+100)/(e->avd+100)*0.8))
    {
        hit=true;
        if(hitthat((double)(p->crt+100)/100*0.1))
        {
            s+="��������������˺���";
            ham=1.5*p->atk;
        }
        else
        {
            s+="��������˺���";
            ham=p->atk;
        }
    }
    else s+="δ���С�";
    PlaySound(d_0,NULL,PM);
    color(WHITE);
    showmessage(s);
    if(hit)damage(e,AD,-ham,HPbar);
    if(hit&&(p->lv>=4))d_shadowchop(p);
}
void d_1shadowblade(status* p)
{
	//����50MP,��ȴ5�غ�:�԰�Ӱ����̫�������100%�Ĺ���������5�غϡ�
	string s;
    if(p->who)s=myrole.name;
    else s=enemyrole.name;
    s+="�ͷ�Ӱ�У������������������С�" ;
    damage(p,RE,-sl[5][1].spend,MPbar);
    p->cd[1]=sl[5][1].cd+1;
    PlaySound(d_1,NULL,PM);
    color(WHITE);
    showmessage(s);
    setbuff(p,ATT,0,5,1.5);
    setbuff(p,ATT,7,5,1.5);
    dealbuff(p);
}
void d_2curseshadow(status* p)
{
	//����20MP,��ȴ4�غ�,����80%:���ת��������������״̬����Ӱ�в��԰�Ӱ��׽�з�Ӱ�ӣ�����ʱ������״̬ת�Ƹ��з���
    string s;
    status *e;
    bool hit=false;
    int d=4;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="�ͷ�����֮Ӱ��";
    if(hitthat((double)(p->hit+100)/(e->avd+100)))
    {
        hit=true;
        s+="ת��������������״̬���з���";
    }
    else s+="���������������״̬��";
    damage(p,RE,-sl[5][2].spend,MPbar);
    p->cd[2]=sl[5][2].cd+1;
    PlaySound(d_2,NULL,PM);
    color(WHITE);
    showmessage(s);
    //
    int debnum=0,deblst[12];
    for(int i=0; i<8; i++)if(p->attribute[i].ratio<0)deblst[debnum++]=i;
    for(int i=0; i<4; i++)if(p->debuff[i].duration)deblst[debnum++]=i+8; 
    int index,temp;
	for(int i=0;i<debnum-1;i++)
	{
		index=rand()%(debnum-i);
		temp=deblst[index];
		deblst[index]=deblst[debnum-i-1];
		deblst[debnum-i-1]=temp;
	}
	debnum=debnum<2?debnum:2;
	for(int i=0;i<debnum;i++)
	{
		if(hit)
	    {
	    	if(deblst[i]<8)
			setbuff(e,ATT,deblst[i],p->attribute[deblst[i]].duration,p->attribute[deblst[i]].ratio);
	    	else
	    	setbuff(e,DEB,deblst[i]-8,p->debuff[deblst[i]-8].duration,p->debuff[deblst[i]-8].ratio);
	    }
	    if(deblst[i]<8)
	    p->attribute[deblst[i]].duration=0;
	    else
	    p->debuff[deblst[i]-8].duration=0;
	}
    dealbuff(p);
    dealbuff(e);
}
void d_3triplechop(status* p)
{
	//����30MP,��ȴ3�غ�:���ٶԵз������������ι�����
	string s;
    if(p->who)s=myrole.name;
    else s=enemyrole.name;
    damage(p,RE,-sl[5][3].spend,MPbar);
    p->cd[3]=sl[5][3].cd+1;
    PlaySound(d_3,NULL,PM);
    color(WHITE);
    showmessage(s+"��������ն�������������Ρ�");
    d_0attack(p);
    Sleep(300);
    d_0attack(p);
    Sleep(300);
	d_0attack(p);
}
void d_4intoshadow(status* p)
{
	//����50%MP,��ȴ4�غ�:���Ĵ�������ֵ�γɰ�Ӱ�������������400%����1�غϲ��ָ�100%���ķ���ֵ������ֵ��
	string s;
    double ham;
    if(p->who)s=myrole.name;
    else s=enemyrole.name;
    s+="�ͷŶ��밵Ӱ���ָ�����ֵ��������ܡ�" ;
    damage(p,RE,-sl[5][4].spend,MPbar);
    p->cd[4]=sl[5][4].cd+1;
    PlaySound(d_4,NULL,PM);
    color(WHITE);
    showmessage(s);
    ham=(int)(0.5*p->MP);
    damage(p,RE,-ham,MPbar);
    damage(p,RE,2*ham,HPbar);
	setbuff(p,ATT,5,1,4);
	dealbuff(p);
}
void d_5shadowdurance(status* p)
{
	//����60MP,��ȴ4�غϣ�����100%:��Ӱ�Ӳ��Ƶз��谭�з�ʩ����ʹ�乥����������м�����ȴ��ʱ+2��
    string s;
    status *e;
    bool hit=false;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="�ͷ�Ӱ����";
    damage(p,RE,-sl[5][5].spend,MPbar);
    p->cd[5]=sl[5][5].cd+1;
    PlaySound(d_5,NULL,PM);
    if(hitthat((double)(p->hit+100)/(e->avd+100)))
    {
    	hit=true;
		s+="ʹ�Է�������ȴ��ʱ���ӡ�";
	}
	else s+="δ���С�";
	color(WHITE);
    showmessage(s);
	if(hit)
	{
		for(int i=1;i<8;i++)e->cd[i]+=2;
	}
}
void d_6bloodsacrifice(status* p)
{
	//����50%HP,��ȴ7�غ�:���Ĵ�������ֵ�׼���Ӱǿ�����������25%��������ֵ�Ļ��׺�ħ���Լ�50%��������ֵ�ķ�ǿ������7�غϡ�
	string s;
	double ham;
    if(p->who)s=myrole.name;
    else s=enemyrole.name;
    status f;
    if(p->who)f=myrole.battlestatus(true);
    else f=enemyrole.battlestatus(false);
    s+="���а�ӰѪ����������������,ħ���ͷ�ǿ��" ;
    damage(p,RE,-sl[5][6].spend,MPbar);
    p->cd[6]=sl[5][6].cd+1;
    ham=(int)(0.5*p->HP);
    damage(p,RE,-ham,HPbar);
    PlaySound(d_6,NULL,PM);
    color(WHITE);
    showmessage(s);
    setbuff(p,ATT,1,7,0.4*ham/f.def);
    setbuff(p,ATT,2,7,0.6*ham/f.abp);
    setbuff(p,ATT,3,7,0.4*ham/f.abr);
    dealbuff(p);
}
void d_7shadowswordcircle(status* p)
{
	//����160MP,��ȴ5�غ�:�ٻ�8�Ѱ�Ӱ֮�������з���ÿ��Ӱ���������������뱩����Ӱ������ʱ���25%��ǿ����ʵ�˺�������3�غϵĶ�Ӧ���Լ���Ч����
    string s;
    status *e;
    double ham=0;
    int hit=0,crt=0;
    char d[2];
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="�ͷ�Ӱ����";
    damage(p,RE,-sl[5][7].spend,MPbar);
    p->cd[7]=sl[5][7].cd+1;
    PlaySound(d_7,NULL,PM);
    for(int i=0; i<8; i++)
    {
        if(hitthat((double)(p->hit+100)/(e->avd+100)*0.8))
        {
            hit++;
            if(hitthat((double)(p->crt+100)/100*0.1))
            {
                crt++;
                ham+=1.5*0.25*p->abp;
            }
            else
            {
                ham+=0.25*p->abp;
            }
            setbuff(e,ATT,i,4,-0.25);
        }
    }
    if(hit==0)
    {
        s+="δ���С�";
        color(WHITE);
        showmessage(s);
    }
    else
    {
        s+="����";
        itoa(hit,d,10);
        s+=d;
        s+="�α���";
        itoa(crt,d,10);
        s+=d;
        s+="�Σ������ʵ�˺��ͼ��档";
        color(WHITE);
        showmessage(s);
        damage(e,RE,-ham,HPbar);
        dealbuff(e);
    }
}
//���˼��� 
void e_regenerate(status* p)
{
	string s;
    double ham;
    if(p->who)s=myrole.name;
    else s=enemyrole.name;
    s+="�����������ָ���������ֵ��" ;
    damage(p,RE,-100,MPbar);
    p->cd[1]=1+1;
    PlaySound(c_4,NULL,PM);
    color(WHITE);
    showmessage(s);
    ham=(double)(p->HPmax-p->HP)*0.5;
    damage(p,RE,ham,HPbar);
}
void e_gaze(status* p)
{
	string s;
    status *e;
    bool hit=false;
    double ham;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="�ͷ�ʯ�����ӣ�";
    if(hitthat((double)(p->hit+100)/(e->avd+100)*2))
    {
        hit=true;
        if(hitthat((double)(p->crt+100)/100*0.2))
        {
            s+="�����������ʵ�˺���ѣ�Ρ�";
            ham=1.5*e->HPmax*0.2;
        }
        else
        {
            s+="�����ʵ�˺���ѣ�Ρ�";
            ham=e->HPmax*0.2;
        }
    }
    else s+="δ���С�";
    damage(p,RE,-120,MPbar);
    p->cd[2]=3+1;
    PlaySound(c_6,NULL,PM);
    color(WHITE);
    showmessage(s);
    if(hit)
    {
        damage(e,RE,-ham,HPbar);
        setbuff(e,DEB,3,1,0);
        dealbuff(e);
    }
}
//�����趨
void e1_op(status* p)
{
    e1_attack(p);
}
void e1_attack(status* p)
{
    string s;
    status *e;
    bool hit=false;
    double ham;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="���й�����";
    if(hitthat((double)(p->hit+100)/(e->avd+100)*0.8))
    {
        hit=true;
        if(hitthat((double)(p->crt+100)/100*0.2))
        {
            s+="��������������˺���";
            ham=1.5*p->atk;
        }
        else
        {
            s+="��������˺���";
            ham=p->atk;
        }
    }
    else s+="δ���С�";
    PlaySound(w_0,NULL,PM);
    color(WHITE);showmessage(s);
    if(hit)damage(e,AD,-ham,HPbar);
}
void e3_op(status* p)
{
    e3_attack(p);
}
void e3_showsk()
{
    gotoxy(42,3);
    cout<<"����:�������е���ʱ��60%����ʩ��1�غ��˺�Ϊ";
    gotoxy(42,4);
    cout<<"100%��ǿ����Ѫ��ȼ�ջ��ж�";
}
void e3_attack(status* p)
{
    string s;
    status *e;
    bool hit=false;
    double ham;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="���й�����";
    if(hitthat((double)(p->hit+100)/(e->avd+100)*0.8))
    {
        hit=true;
        if(hitthat((double)(p->crt+100)/100*0.2))
        {
            s+="��������������˺���";
            ham=1.5*p->atk;
        }
        else
        {
            s+="��������˺���";
            ham=p->atk;
        }
    }
    else s+="δ���С�";
    PlaySound(w_0,NULL,PM);
    color(WHITE);showmessage(s);
    if(hit)
    {
        damage(e,AD,-ham,HPbar);
        e3_sk(p);
    }
}
void e3_sk(status* p)
{
    string s;
    status *e;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    if(hitthat(0.6))
    {
        int k;
        k=rand()%3;
        s+="�����������䣬���";
        if(k==0)s+="��Ѫ��";
        else if(k==1)s+="ȼ�ա�";
        else s+="�ж���";
        color(WHITE);
        showmessage(s);
        setbuff(e,DEB,k,1,p->abp);
        showbuff(*e);
    }
}
void e4_op(status* p)
{
    if(p->MP>=sl[0][1].spend&&p->cd[1]==0)w_1charge(p);
    else e4_attack(p);
}
void e4_showsk()
{
    color(WHITE);
    gotoxy(42,3);
    cout<<"��Ѫ:�������е���ʱ������һ����Ȼ�����ָ���";
}
void e4_attack(status* p)
{
    //����
    //������,����80%,����20%:�Եз�������ͨ��������ɻ��ڹ������������˺���
    string s;
    status *e;
    bool hit=false;
    double ham;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="���й�����";
    if(hitthat((double)(p->hit+100)/(e->avd+100)*0.8))
    {
        hit=true;
        if(hitthat((double)(p->crt+100)/100*0.2))
        {
            s+="��������������˺���";
            ham=1.5*p->atk;
        }
        else
        {
            s+="��������˺���";
            ham=p->atk;
        }
    }
    else s+="δ���С�";
    PlaySound(w_0,NULL,PM);
    color(WHITE);
    showmessage(s);
    if(hit)
	{
		damage(e,AD,-ham,HPbar);
		w_bloodsuck(p);
	}
}
void e5_op(status* p)
{
    status* e=&player;
    if(p->MP>=sl[2][7].spend&&p->cd[7]==0)m_7manaburn(p);
    else if(p->MP>=sl[3][2].spend&&p->cd[2]==0&&e->debuff[1].duration==0)c_2blaze(p);
    else e5_attack(p);
}
void e5_showsk()
{
    color(WHITE);
    gotoxy(42,3);
    cout<<"�ȷ�:�������е���ʱ������һ����Ȼ�����ָ���";
}
void e5_attack(status* p)
{
    //����
    //������,����80%,����20%:�Եз�������ͨ��������ɻ��ڹ������������˺���
    string s;
    status *e;
    bool hit=false;
    double ham;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="���й�����";
    if(hitthat((double)(p->hit+100)/(e->avd+100)*0.8))
    {
        hit=true;
        if(hitthat((double)(p->crt+100)/100*0.2))
        {
            s+="��������������˺���";
            ham=1.5*p->atk;
        }
        else
        {
            s+="��������˺���";
            ham=p->atk;
        }
    }
    else s+="δ���С�";
    PlaySound(m_0,NULL,PM);
    color(WHITE);
    showmessage(s);
    if(hit)
    {
    	damage(e,AD,-ham,HPbar);
		m_manasuck(p);
    }
}
void e6_op(status* p)
{
    if(p->MP>=sl[2][3].spend&&p->cd[3]==0)a_3sneak(p);
    else e1_attack(p);
}
void e7_op(status* p)
{
    if(p->MP>=sl[2][5].spend&&p->cd[5]==0)m_5mindblast(p);
    else if(p->MP>=sl[3][3].spend&&p->cd[3]==0)c_3fivepoisons(p);
    else if(p->MP>=sl[3][6].spend&&p->cd[6]==0)c_6imperio(p);
    else e1_attack(p);
}
void e8_showsk()
{
    gotoxy(42,3);
    cout<<"�ͻ�:�������е���ʱ��ÿ���3���˺�����ٶ�";
    gotoxy(42,4);
    cout<<"��1%�ж�����";
}
void e8_op(status* p)
{
    if(p->MP>=sl[0][1].spend&&p->cd[1]==0)w_1charge(p);
    else if(p->MP>=sl[0][4].spend&&p->cd[4]==0)w_4cripple(p);
    else e8_attack(p);
}
void e8_attack(status* p)
{
    //����
    //������,����80%,����20%:�Եз�������ͨ��������ɻ��ڹ������������˺���
    string s;
    status *e;
    bool hit=false;
    double ham;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="���й�����";
    if(hitthat((double)(p->hit+100)/(e->avd+100)*0.8))
    {
        hit=true;
        if(hitthat((double)(p->crt+100)/100*0.2))
        {
            s+="��������������˺���";
            ham=1.5*p->atk;
        }
        else
        {
            s+="��������˺���";
            ham=p->atk;
        }
    }
    else s+="δ���С�";
    PlaySound(w_0,NULL,PM);
    color(WHITE);showmessage(s);
    if(hit)w_beatback(p,damage(e,AD,-ham,HPbar));
}
void e9_showsk()
{
    gotoxy(42,3);
    cout<<"˫ذ:�������е���ʱ����50%������������˺���";
}
void e9_op(status* p)
{
    if(p->MP>=sl[2][3].spend&&p->cd[3]==0)a_3sneak(p);
    else if(p->MP>=sl[2][1].spend&&p->cd[1]==0)a_1assassinate(p);
    else a_0attack(p);
}
void e10_showsk()
{
    gotoxy(42,3);
    cout<<"��Ѫ:��������˺�ʱ���ָ��˺�ֵ20%��������";
}
void e10_op(status* p)
{
    if(p->MP>=sl[0][6].spend&&p->cd[6]==0&&p->HP<=p->HPmax*0.3)w_6bloodwake(p);
    else if(p->MP>=sl[0][4].spend&&p->cd[4]==0)w_4cripple(p);
    else if(p->MP>=sl[2][1].spend&&p->cd[1]==0)a_1assassinate(p);
    else e10_attack(p);
}
void e10_sk(status* p,double ham)
{
    string s;
    status *e;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="����������Ѫ���ָ�����ֵ��";
    color(WHITE);
    showmessage(s);
    damage(p,RE,-0.2*ham,HPbar);
}
void e10_attack(status* p)
{
    string s;
    status *e;
    bool hit=false;
    double ham;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="���й�����";
    if(hitthat((double)(p->hit+100)/(e->avd+100)*0.8))
    {
        hit=true;
        if(hitthat((double)(p->crt+100)/100*0.2))
        {
            s+="��������������˺���";
            ham=1.5*p->atk;
        }
        else
        {
            s+="��������˺���";
            ham=p->atk;
        }
    }
    else s+="δ���С�";
    PlaySound(a_0,NULL,PM);
    color(WHITE);showmessage(s);
    if(hit)
    {
        e10_sk(p,damage(e,AD,-ham,HPbar));
    }
}
void e11_showsk()
{
    gotoxy(42,3);
    cout<<"�ػ�:��������ʱ��25%�������1�غ�ѣ�Ρ�";
}
void e11_sk(status* p)
{
    string s;
    status *e;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    if(hitthat(0.25))
    {
        s+="���������ػ������ѣ�Ρ�";
        color(WHITE);
        showmessage(s);
        setbuff(e,DEB,3,1,0);
        showbuff(*e);
    }
}
void e11_op(status* p)
{
    if(p->MP>=sl[0][3].spend&&p->cd[3]==0&&(p->attribute[1].duration||p->attribute[3].duration||p->attribute[4].duration||p->debuff[0].duration||p->debuff[1].duration||p->debuff[2].duration))w_3stone(p);
	else if(p->MP>=sl[0][2].spend&&p->cd[2]==0)w_2disarm(p);
    else if(p->MP>=sl[0][5].spend&&p->cd[5]==0)w_5shieldhit(p);
    else e11_attack(p);
}
void e11_attack(status* p)
{
    string s;
    status *e;
    bool hit=false;
    double ham;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="���й�����";
    if(hitthat((double)(p->hit+100)/(e->avd+100)*0.8))
    {
        hit=true;
        if(hitthat((double)(p->crt+100)/100*0.2))
        {
            s+="��������������˺���";
            ham=1.5*p->atk;
        }
        else
        {
            s+="��������˺���";
            ham=p->atk;
        }
    }
    else s+="δ���С�";
    PlaySound(w_0,NULL,PM);
    color(WHITE);showmessage(s);
    if(hit)
    {
        damage(e,AD,-ham,HPbar);
        e11_sk(p);
    }
}
void e12_showsk()
{
    gotoxy(42,3);
    cout<<"����:�������е���ʱ�����10�غ��˺�Ϊ10%��";
    gotoxy(42,4);
    cout<<"ǿ���ж���";
}
void e12_sk(status* p)
{
    string s;
    status *e;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="������������������ж���";
    color(WHITE);
    showmessage(s);
    setbuff(e,DEB,2,10,p->abp*0.1);
    showbuff(*e);
}
void e12_op(status* p)
{
    if(p->HP<=p->HPmax*0.4&&p->MP>=100&&p->cd[1]==0)e_regenerate(p);
	else if(p->MP>=120&&p->cd[2]==0)e_gaze(p);
    else e12_attack(p);
}
void e12_attack(status* p)
{
    string s;
    status *e;
    bool hit=false;
    double ham;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="���й�����";
    if(hitthat((double)(p->hit+100)/(e->avd+100)*0.8))
    {
        hit=true;
        if(hitthat((double)(p->crt+100)/100*0.2))
        {
            s+="��������������˺���";
            ham=1.5*p->atk;
        }
        else
        {
            s+="��������˺���";
            ham=p->atk;
        }
    }
    else s+="δ���С�";
    PlaySound(c_0,NULL,PM);
    color(WHITE);showmessage(s);
    if(hit)
    {
        damage(e,AD,-ham,HPbar);
        e12_sk(p);
    }
}