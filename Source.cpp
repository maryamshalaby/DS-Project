#include<iostream>
#include<fstream>
using namespace std;
ifstream input;
ofstream output;

struct enemy{
	int s;//sequence
	int ty;//type
	int t;//arrival time
	int h;//health
	int pow;//fire power
	int prd;//reload period
	char r;//region
	int st; //shot time, we can calculate fd, kd, ft from it
	int d; //distance 
	enemy*nextregion; // pointer that points on next enemy in same region 
	enemy*next;//next enemy 
};

struct tower{
	char name;
	int th; //starting health
	 int n; // max number of enemies a towercan attack 
	 int tp; //tower fire poower
	 int p; //paved distance
	 enemy*region;//normal fighters
	 enemy*regionh;// high priority fighters
};

struct castle{
	tower* a;
	tower* b;
	tower* c;
	tower* d;
};

bool createnode(enemy*&create) // b3tna el create by ref 3ashan han3'yar fel value beta3itha. mmkn n5aliha betshawir 3ala null elawil 
	// had to move it above fileloding to be able to use it inside file loading
{int s;
input>>s;
if(s==-1)
	return false; //meaning don't carry out node creation 
	create=new enemy;
create->s=s;
input>>create->ty;/*create->t>>create->h>>create->pow>>create->prd>>create->r;*/
create->next=NULL;
create->nextregion=NULL;
return true;
}
void intitower(tower&t, int h, int n, int tp)// intitializes tower data values
{t.th=h; t.n=n; t.tp=tp;
	t.region=NULL;
	t.regionh=NULL;}

void regionlinking(enemy*active1,enemy*active2,tower&t)// links enemies in same region to each other
{enemy*temp=NULL; // first normal enemies
 while(active1!=NULL)
      { if(active1->r==t.name)
         {if (temp==NULL)
		 {temp=active1; t.region=active1; active1=temp->next;}
		 else {temp->nextregion=active1; temp=active1;}}
		active1=active1->next;}
 enemy*temp=NULL; // then sheilded enemies
 while(active2!=NULL)
      { if(active2->r==t.name)
         {if (temp==NULL)
		 {temp=active2; t.regionh=active2; active2=temp->next;}
		 else {temp->nextregion=active2; temp=active2;}}
		active2=active2->next;}
}
void fileloading(enemy*&active1,enemy*&active2,castle &ca, int &c1,int &c2,int &c3) // keda we decided we'll put our enemies in two individual lists (normal emnemies and priority enemies) 
	// lazim nb3t lelfile loadig deh pointers 3ashan tshawir 3ala elheads beta3it ellists we lazim by ref 3ashan el pointer nafso hayit3'ayar 
	//active1 is head pointer of normal enemies list
	// active 2 and temp2 are used for same purpose for sheilded/priority enemy list 
{ input.open("input.txt", ios::in);
//next part is intializing towers, giving their data values 
tower a,b,c,d;
int h,n,tp;
input>>h>>n>>tp;
a.name='a'; b.name='b'; c.name='c'; d.name='d';
intitower(a,h,n,tp);
intitower(b,h,n,tp);
intitower(c,h,n,tp);
intitower(d,h,n,tp);
input>>c1>>c2>>c3;
	enemy*create= NULL;  enemy*temp1; enemy*temp2; // create is the pointer that points at newly created nodes every loop.
	//temp1 is pointer used in normal list to assign address of new node to prvious node, can't use head pointer for this task because i need it to stay in it's place.
	while(createnode(create)) // do while didn't work because we i insert -1 it still carried out the operation, didn't exit the loop
	{if(create->ty!=2 && active1==NULL) // if type of enemy is not sheilded and it is first node
	{active1=create; temp1=active1;} // assign head pointer (inactive1 to node), next pointer inside node points to NULL, and temp1 points to this first node
	else if(create->ty !=2)// if enemy is not sheilded and it is not first node 
	{temp1->next=create; temp1=create;} // make previous node point to current node, make temp1 point to current node, set pointer inside currnt node to null;
	else if(active2==NULL)// this means enemy is sheilded, we make sure it is first node
	{active2=create; temp2=active2;} // basically same thing done in case of normal enemy
	else {temp2->next=create; temp2=create;}// means enemy is sheilded and not first node, also same thing done to normal enemy
    }
regionlinking(active1,active2,a);
regionlinking(active1,active2,b);
regionlinking(active1,active2,c);
regionlinking(active1,active2,d);
ca.a=&a; ca.b=&b; ca.c=&c; ca.d=&d;// assigns tower adresses to main castle 
}


int main(){
	castle c; int c1,c2,c3;
output.open("output.txt",ios ::out);
	enemy*active1= NULL; enemy*active2=NULL; //hatahom nafs el ism 3ashan matl3'batsh
fileloading(active1,active2,c,c1,c2,c3);
output<<"list of normal enemies"<<endl;
 while(active1!=NULL)
	 {output<<"s "<<active1->s<<" type "<<active1->ty<<endl;
 active1= active1->next;}
 output<<"list of sheilded enemies"<<endl;
  while(active2!=NULL)
	 {output<<"s "<<active2->s<<" type "<<active2->ty<<endl;
 active2= active2->next;}

	return 0;}
