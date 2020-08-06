#include <stdlib.h>
//Structure definition of orginal pawns
struct node{
	int x,y;
	struct node * next;
};
typedef struct node * NODE;
//Structure definition of computing pawns
struct node2{
	int level,x1,y1,x2,y2;
	float value;
	struct node2* next,*nextlevel;
};
typedef struct node2 * NODE2;

NODE2 insertEnd2(NODE2 start,float value,int x1,int y1,int x2,int y2,int level){
	NODE2 temp,cur;
	temp=(NODE2)malloc(sizeof(struct node2));
	temp->x1=x1;
	temp->y1=y1;
	temp->value=value;
	temp->x2=x2;
	temp->y2=y2;
	temp->level=level;
	temp->nextlevel=NULL;
	temp->next=NULL;
	cur=start;
	
	if(start==NULL)
		{
			return temp;
		}
	
	while(cur->next!=NULL)
		cur=cur->next;
	cur->next=temp;
	
	return start;
}

NODE insertEnd(NODE start,int x1,int y1){
	NODE temp,cur;
	temp=(NODE)malloc(sizeof(struct node));
	temp->x=x1;
	temp->y=y1;
	temp->next=NULL;
	cur=start;
	
	if(start==NULL)
		{
			return temp;
		}
	
	while(cur->next!=NULL)
		cur=cur->next;
	cur->next=temp;
	
	return start;
}

NODE deleteBegin(NODE start){
	NODE temp;
	if(start==NULL)
		return NULL;
	temp=start;
	start=start->next;
	free(temp);
	return start;
}
NODE2 deleteBegin2(NODE2 start){
	NODE2 temp;
	if(start==NULL)
		return NULL;
	temp=start;
	start=start->next;
	free(temp);
	return start;
}
