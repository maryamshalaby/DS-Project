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
	int fd;          //fight_delay
	int kd;            //kill_delay
	enemy*next;//next enemy 
	
};
struct killed_enemy
{  int s;
 int fd;
 int kd;
 int kts;  //fight time for each enemy is equal to fd+kd 
	node*next;
};
killed_enemy*killedhead=NULL;  // pointer to the head of the killed enemy list

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
return true;
}
void fileloading(enemy*&inactive1,enemy*&inactive2) // keda we decided we'll put our enemies in two individual lists (normal emnemies and priority enemies) 
	// lazim nb3t lelfile loadig deh pointers 3ashan tshawir 3ala elheads beta3it ellists we lazim by ref 3ashan el pointer nafso hayit3'ayar 
	//inactive1 is head pointer of normal enemies list
	// inactive 2 and temp2 are used for same purpose for sheilded/priority enemy list 
{input.open("input.txt", ios::in);
	enemy*create= NULL;  enemy*temp1; enemy*temp2; // create is the pointer that points at newly created nodes every loop.
	//temp1 is pointer used in normal list to assign address of new node to prvious node, can't use head pointer for this task because i need it to stay in it's place.
	while(createnode(create)) // do while didn't work because we i insert -1 it still carried out the operation, didn't exit the loop
	{if(create->ty!=2 && inactive1==NULL) // if type of enemy is not sheilded and it is first node
	{inactive1=create; temp1=inactive1;} // assign head pointer (inactive1 to node), next pointer inside node points to NULL, and temp1 points to this first node
	else if(create->ty !=2)// if enemy is not sheilded and it is not first node 
	{temp1->next=create; temp1=create;} // make previous node point to current node, make temp1 point to current node, set pointer inside currnt node to null;
	else if(inactive2==NULL)// this means enemy is sheilded, we make sure it is first node
	{inactive2=create; temp2=inactive2;} // basically same thing done in case of normal enemy
	else {temp2->next=create; temp2=create;}// means enemy is sheilded and not first node, also same thing done to normal enemy
    }
	
}
void delete_enemy(enemy*head)
{ enemy*preloc=NULL;       enemy*loc=head;
 while(loc->t<timestep && loc->h!=0)
 { pleloc=preloc->next;      loc=loc->next;   }
 if ( loc->h==0)
   { if(preloc==NULL)   { head=head->next; delete preloc;   }
 else if(loc->next==NULL)  { preloc->next==NULL;  }
  else {  preloc->next=loc->next; }
    killed(killedhead,loc);
    delete loc;
   }
}
void killed(enemy*&killedhead,enemy*loc)
{  killed_enemy*a=new killed_enemy;
	killed_enemy*trav=killedhead;
   a->s=loc->s;
   a->fd=loc->fd;
   a->kd=loc->kd;
   a->kts=time_step;
	if(killedhead==NULL)
     {killedhead=a;     a->next=NULL;  }
           else { 
	   while(trav!=NULL) {  trav=trav->next; }
	    trav->next=a;
	    a->next=NULL;
	        } 
}
int main()
	
	[
	
output.open("output.txt",ios ::out);
	enemy*inactive1= NULL; enemy*inactive2=NULL;//hatahom nafs el ism 3ashan matl3'batsh
fileloading(inactive1,inactive2);
output<<"list of normal enemies"<<endl;
 while(inactive1!=NULL)
	 {output<<"s "<<inactive1->s<<" type "<<inactive1->ty<<endl;
 inactive1= inactive1->next;}
 output<<"list of sheilded enemies"<<endl;
  while(inactive2!=NULL)
	 {output<<"s "<<inactive2->s<<" type "<<inactive2->ty<<endl;
 inactive2= inactive2->next;}
	delete_enemy(inactive1);
        delete_enemy(inactive2);
	return 0;}


