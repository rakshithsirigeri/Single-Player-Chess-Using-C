#include "MOVES.h"
#include <stdio.h>
//FUNCTION TO CHECK THREAT FOR A PIECE
int threatCheck(int x, int y,char **a,int level){
	char c,A,z;
	int i,j,*xy1;
	if(level%2==0){
		A='A';
		z='Z';
	}
	else {
		A='a';
		z='z';
	}
	xy1=(int*)malloc(2*sizeof(int));
	NODE start=NULL,cur,temp;
	for(i=0;i<8;i++){
		for(j=0;j<8;j++){
			c=a[i][j];
			if(c>A&&c<z){
				*xy1=i+1;
				*(xy1+1)=j+1;
				cur=suggestingMove(a,xy1);
	    if(start==NULL)
			{
				start=cur;
				temp=start;
			}
		else{
			while(temp->next!=NULL)	
				temp=temp->next;
			temp->next=cur;}
			}			
		}
	}
	cur=start;
	while(cur!=NULL){
		if(x==cur->x&&y==cur->y)
			{
			deleteMoves(start);
			return 1;
			}
		cur=cur->next;
	}
	deleteMoves(start);
	return 0;	
}
//Assigns generation for threat mobility and defence
float valueGeneration(char a){
	float point;
		switch(a){
		case 'Q':
		case 'q':point=0.9;
				break;
		case 'r':
		case 'R':point=0.7;
				break;
		case 'n':
		case 'N':point=0.7;
				break;
		case 'b':
		case 'B':point=0.6;
				break;
		case 'p':
		case 'P':point=0.3;
				break;
		case 'k':
		case 'K':point=1.0;
				break;
		default :point=0.0;
	}
	return point;
}
//Copies the board to generate a value for next moves
void copyBoard(char **b,char **a){
	int i,j;

	for(i=0;i<8;i++)
		for(j=0;j<8;j++)
			b[i][j]=a[i][j];
}
//Checks whether a pawn is causing threat to its opponent
float threatCausing(int x1,int y1,int x2,int y2,char **a,int level){
	char c,A,z;
	if(level%2==0){
		A='A';
		z='Z';
	}
	else {
		A='a';
		z='z';
	}
	c=a[x2][y2];
	if(c>A&&c<z)
		return 1.5*valueGeneration(c);
	return 0.0;		
}
//Generates all the possible moves of a player
NODE2 generateMoves(char **a,int level){
	int i,j,*xy,sav;
	float value;
	char **b,A,z;
	b=(char**)malloc(8*sizeof(char*));	
	for(i=0;i<8;i++)
		*(b+i)=(char*)malloc(8*sizeof(char));
	if(level%2==0)
		{
			A='a';
			z='z';}
	else {
			A='A';
			z='Z';
	}
	xy=(int*)malloc(2*sizeof(int));
	char c;
	NODE2 start2=NULL,cur2;
	NODE start=NULL,cur;
	for(i=0;i<8;i++){
		for(j=0;j<8;j++){
			c=a[i][j];
			if(c>A&&c<z){
				*xy=i+1;
				*(xy+1)=j+1;
				start=suggestingMove(a,xy);
				sav=threatCheck(i,j,a,level);
				if(sav==1)
					value=valueGeneration(c);
				else value=0.0;
				cur=start;
				while(cur!=NULL){
					start2=insertEnd2(start2,value,i+1,j+1,cur->x+1,cur->y+1,level);
					cur=cur->next;
				}
				start=deleteMoves(start);				
			}				
		}
	}
	cur2=start2;
    while(cur2!=NULL){
		copyBoard(b,a);	
		b[cur2->x2-1][cur2->y2-1]=a[cur2->x1-1][cur2->y1-1];
		b[cur2->x1-1][cur2->y1-1]=' ';
		if(cur2->level==1)
		cur2->nextlevel=generateMoves(b,2);
		sav=threatCheck(cur2->x2-1,cur2->y2-1,b,level);
		if(sav==1)
			cur2->value=cur2->value-0.5;
		cur2=cur2->next;
	}
	cur2=start2;
	while(cur2!=NULL){
		value=threatCausing(cur2->x1-1,cur2->y1-1,cur2->x2-1,cur2->y2-1,a,level);
		if(value!=0.0)
		printf("%f",value);
		cur2->value=cur2->value+value;
		cur2=cur2->next;
	}
	cur2=start2;
	while(cur2!=NULL){
		if(cur2->value==0.0)
		{
			c=a[cur2->x1-1][cur2->y1-1];
			if(c=='P')
			cur2->value=(1-valueGeneration(c))*((8-cur2->x2+1.0))*0.001;
			else cur2->value=(1-valueGeneration(c))*((8-cur2->x2+1))*0.01;
			}
		cur2=cur2->next;
	}
	return start2;
}
//It gives the minimized value of opponents move
float minimize(NODE2 start){
	NODE2 max,cur;
	if(start==NULL)
		return 0.0;
	
	max=start;
	cur=start;
	while(cur!=NULL){
		if(max->value>cur->value)
			max=cur;
		cur=cur->next;
		
	}
	deleteMoves2(start);
	;
	return max->value;
	
}
//Generates the next move
node2 mobility(char **a,int level){
	NODE2 max1,cur,min1;
	struct node2 max;
	max1=generateMoves(a,1);
	
	if(max1!=NULL){
			max.value=max1->value;
	max.x1=max1->x1;
	max.y1=max1->y1;
	max.x2=max1->x2;
	max.y2=max1->y2;
	max.next=NULL;
	}
	
	cur=max1;
	while(max1!=NULL){
		max1->value=max1->value+minimize(max1->nextlevel);
		if(max1->value>=max.value)
			{	max.value=max1->value;
	max.x1=max1->x1;
	max.y1=max1->y1;
	max.x2=max1->x2;
	max.y2=max1->y2;
	max.next=NULL;
				}
				max1=max1->next;
	}
	deleteMoves2(cur);
	return max;
	}
