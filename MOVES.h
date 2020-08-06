#include "linkedList.h"
#include <stdio.h>


// FUNCTIOM TO THE CHECH VALIDITY OF SELECTION
int selectionCheck(char **a,int *xy,int moves){
	char c;
	int x1=*(xy),y1=*(xy+1);
	if((x1>0&&x1<9)&&(y1>0&&y1<9)){
		c=a[x1-1][y1-1];
		if(c!=' '){
			if(moves%2==0){
				if(!(c>='A'&&c<='Z')){
					return 0;
				}	
			}
			else{
				if(!(c>='a'&&c<='z')){
					return 0;
				}	
			}
		}
		else{
			return 0;
		}
	}
	else{
		return 0;
	}
	return 1;
}


//FUNCTION TO SUGGEST MOVES FOR WHITE PAWN
NODE pawnC(char **a,int x1,int y1,NODE start){
	char c=a[x1-1][y1-1];
	
		c=a[x1][y1-1];
		if(c==' '){
			start=insertEnd(start,x1,y1-1);
		}
		if(x1==2&&c==' '){
			c=a[x1+1][y1-1];
			if(c==' ')
				start=insertEnd(start,x1+1,y1-1);
		}
		if((x1)>=0&&(x1)<=7&&(y1-2)>=0&&(y1-2)<=7){
			c=a[x1][y1-2];
			if(c>='a'&&c<='z')
				start=insertEnd(start,x1,y1-2);
		}
			if((x1)>=0&&(x1)<=7&&(y1)>=0&&(y1)<=7){
			c=a[x1][y1];
			if(c>='a'&&c<='z')
				start=insertEnd(start,x1,y1);
		}
	return start;	
}

//FUNCTION TO SUGGEST MOVES FOR BLACK PAWN
NODE pawnL(char **a,int x1,int y1,NODE start){
	char c;
	c=a[x1-2][y1-1];
	if(c==' '){
		start=insertEnd(start,x1-2,y1-1);
	}
	if(x1==7&&c==' '){
		c=a[x1-3][y1-1];
		if(c==' ')
			start=insertEnd(start,x1-3,y1-1);
	}
	if((x1-2)>=0&&(x1-2)<=7&&(y1-2)>=0&&(y1-2)<=7){
		c=a[x1-2][y1-2];
		if(c>='A'&&c<='Z')
				start=insertEnd(start,x1-2,y1-2);
		}
	if((x1-2)>=0&&(x1-2)<=7&&(y1)>=0&&(y1)<=7){
		c=a[x1-2][y1];
		if(c>='A'&&c<='Z')
				start=insertEnd(start,x1-2,y1);
		}
	return start;	
}


//FUNCTION TO SUGGEST MOVES FOR ROOK
NODE rook(char **a,int x1,int y1,NODE start,char q){
		
	int x=x1,y=y1,A,S,flag=0;
	char c;
	if(q=='R')
	{	A=(int)'a';
		S=(int)'z';
		
		}
	else {
		A=(int)'A';
		S=(int)'Z';
	}
	
	while(x<=7&&flag==0){
		c=a[x][y-1];
		if(c>=A&&c<=S){
			start=insertEnd(start,x,y-1);
			flag=1;
		}
		if(c!=' ')
			break;
		else 
			start=insertEnd(start,x,y-1);
		x+=1;
	}
	flag=0;
	x=x1; y=y1;
	while(x>=2&&flag==0){
			c=a[x-2][y-1];
	
			if(c>=A&&c<=S){
			start=insertEnd(start,x-2,y-1);
			flag=1;
		}
		if(c!=' ')
			break;
		else 
			start=insertEnd(start,x-2,y-1);
		x-=1;
	}
	flag=0;x=x1; y=y1;
	while(y<=7&&flag==0){
		c=a[x-1][y];
		if(c>=A&&c<=S){
			start=insertEnd(start,x-1,y);
			flag=1;
		}
		if(c!=' ')
			break;
		else 
			start=insertEnd(start,x-1,y);
		y+=1;
	}
		flag=0;x=x1; y=y1;
	while(y>=2&&flag==0){
		c=a[x-1][y-2];
		if(c>=A&&c<=S){
			start=insertEnd(start,x-1,y-2);
			flag=1;
		}
		if(c!=' ')
			break;
		else 
			start=insertEnd(start,x-1,y-2);
		y-=1;
	}
	return start;
}





//FUNCTION TO SUGGEST MOVES FOR BISHOP
NODE bishop(char**a,int x1,int y1,NODE start,char b){
		
	int x=x1,y=y1,A,S,flag=0;
	char c;
	if(b=='B')
	{	A=(int)'a';
		S=(int)'z';
		
		}
	else {
		A=(int)'A';
		S=(int)'Z';
	}
	while(x>=2&&y>=2&&flag==0){
		c=a[x-2][y-2];
		if(c>=A&&c<=S){
			start=insertEnd(start,x-2,y-2);
			flag=1;
		}
		if(c!=' ')
			break;
		else 
			start=insertEnd(start,x-2,y-2);
		x=x-1;
		y=y-1;
	}
	x=x1;
	y=y1;
	flag=0;
	
	
	while(x<=7&&y<=7&&flag==0){
		c=a[x][y];
		if(c>=A&&c<=S){
			start=insertEnd(start,x,y);
			flag=1;
		}
		if(c!=' ')
			break;
		else 
			start=insertEnd(start,x,y);
		x=x+1;
		y=y+1;
	}
	x=x1;
	y=y1;
	flag=0;
	
	
	while(x>=2&&y<=7&&flag==0){
		c=a[x-2][y];
		if(c>=A&&c<=S){
			start=insertEnd(start,x-2,y);
			flag=1;
		}
		if(c!=' ')
			break;
		else 
			start=insertEnd(start,x-2,y);
		x=x-1;
		y=y+1;
	}
	x=x1;
	y=y1;
	flag=0;
	
	
	while(x<=7&&y>=2&&flag==0){
		c=a[x][y-2];
		if(c>=A&&c<=S){
			start=insertEnd(start,x,y-2);
			flag=1;
		}
		if(c!=' ')
			break;
		else 
			start=insertEnd(start,x,y-2);
		x=x+1;
		y=y-1;
	}
	return start;
}






//FUNCION TO SUGGEST MOVES FOR KNIGHT
NODE knight(char** a,int x1,int y1,NODE start,char k){
	int A,Z,x,y;
	char c;
		if(k=='N'){
			A=(int)'a';
			Z=(int)'z';
		}
		else {
			A=(int)'A';
			Z=(int)'Z';
		}
	x=x1+2;
	if(x<=8){
		y=y1+1;
		if(y<=8){
			c=a[x-1][y-1];
			if((c>=A&&c<=Z)||c==' ')
				{start=insertEnd(start,x-1,y-1);
				}
		}
		y=y1-1;
		if(y>=1){
			c=a[x-1][y-1];
			if((c>=A&&c<=Z)||c==' ')
				{start=insertEnd(start,x-1,y-1);
				}	
		}
	}
	x=x1-2;
	if(x>=1){
		y=y1+1;
		if(y<=8){
			c=a[x-1][y-1];
			if((c>=A&&c<=Z)||c==' ')
				start=insertEnd(start,x-1,y-1);
		}
		y=y1-1;
		if(y>=1){
			c=a[x-1][y-1];
			if((c>=A&&c<=Z)||c==' ')
				start=insertEnd(start,x-1,y-1);
			
		}
	}
	
	y=y1+2;
	if(y<=8){
		x=x1+1;
		if(x<=8){
			c=a[x-1][y-1];
			if((c>=A&&c<=Z)||c==' ')
				start=insertEnd(start,x-1,y-1);
		}
		x=x1-1;
		if(x>=1){
			c=a[x-1][y-1];
			if((c>=A&&c<=Z)||c==' ')
				start=insertEnd(start,x-1,y-1);
		}
	}
	y=y1-2;
	if(y>=1){
		x=x1+1;
		if(x<=8){
			c=a[x-1][y-1];
			if((c>=A&&c<=Z)||c==' ')
				start=insertEnd(start,x-1,y-1);
		}
		x=x1-1;
		if(x>=1){
			c=a[x-1][y-1];
			if((c>=A&&c<=Z)||c==' ')
				start=insertEnd(start,x-1,y-1);
		}
	}
	return start;
}




//FUNCION TO SUGGEST MOVES FOR KING
NODE king(char **a,int x1,int y1,NODE start,char k){
	int x,y,A,Z;
	char c;
	if(k=='K'){
		A=(int)'a';
		Z=(int)'z';
	}
	else{
		A=(int)'A';
		Z=(int)'Z';
	}
	x=x1+1;
	if(x<=8){
		y=y1+1;
		if(y<=8){
			c=a[x-1][y-1];
			if((c>=A&&c<=Z)||c==' ')
				{start=insertEnd(start,x-1,y-1);
				}
		}
		y=y1-1;
		if(y>=1){
			c=a[x-1][y-1];
			if((c>=A&&c<=Z)||c==' ')
				{start=insertEnd(start,x-1,y-1);
				}
			
		}
	}
	x=x1-1;
	if(x>=1){
		y=y1+1;
		if(y<=8){
			c=a[x-1][y-1];
			if((c>=A&&c<=Z)||c==' ')
				start=insertEnd(start,x-1,y-1);
		}
		y=y1-1;
		if(y>=1){
			c=a[x-1][y-1];
			if((c>=A&&c<=Z)||c==' ')
				start=insertEnd(start,x-1,y-1);
			
		}
	}
	x=x1;
	y=y1+1;
	if(y<=8){
		c=a[x-1][y-1];
		if((c>=A&&c<=Z)||c==' ')
			start=insertEnd(start,x-1,y-1);
	}
	y=y1-1;
	if(y>=1){
		c=a[x-1][y-1];
		if((c>=A&&c<=Z)||c==' ')
			start=insertEnd(start,x-1,y-1);
	}
	y=y1;
	x=x1+1;
	if(x<=8){
		c=a[x-1][y-1];
		if((c>=A&&c<=Z)||c==' ')
			start=insertEnd(start,x-1,y-1);
	}
	x=x1-1;
	if(x>=1){
		c=a[x-1][y-1];
		if((c>=A&&c<=Z)||c==' ')
			start=insertEnd(start,x-1,y-1);
	}
	return start;
}




//FUNCION TO SUGGEST MOVES FOR QUEEN
NODE queen(char** a,int x1,int y1,NODE start,char q){
	if(q=='Q'){
		start=rook(a,x1,y1,start,'R');
		start=bishop(a,x1,y1,start,'B');
		return start;
	}
	start=rook(a,x1,y1,start,'r');
		start=bishop(a,x1,y1,start,'b');
	return start;
}





//FUNCTION TO SUGGEST  MOVES
//RANGE FROM 1 to 8
NODE suggestingMove(char** a,int *xy1){
	char c;
	int x1=*(xy1),y1=*(xy1+1);
	NODE start=NULL;
	c=a[x1-1][y1-1];
	switch(c){
		case 'P': start=pawnC(a,x1,y1,start);
					break;
		case 'p': start=pawnL(a,x1,y1,start);
					break;
		case 'R':
		case 'r':start=rook(a,x1,y1,start,c);
				break;
		case 'b':
		case 'B': start=bishop(a,x1,y1,start,c);
					break;	
		case 'Q':
		case 'q':start=queen(a,x1,y1,start,c);
					break;
		case 'N':
		case 'n':start=knight(a,x1,y1,start,c);
				break;
		case 'K':
		case 'k':start=king(a,x1,y1,start,c);
					break;
	}
	if(start==NULL)
		return NULL;
			
	return start;
}





//FUCTION TO VALIDATE THE MOVES
bool validMove(int *xy2,int *xy1,NODE start){
	NODE cur;
	cur=start;
	int x1=*(xy1),y1=*(xy1+1),x2=*(xy2),y2=*(xy2+1);
	if(!(x2>0&&x2<9&&y2>0&&y2<9)){
		return false;
	}
	while(cur!=NULL){
		if((cur->x==x2-1)&&(cur->y==y2-1)){
			return true;
		}
		cur=cur->next;		
	}
	return false;	
}



//FUNCTION TO DELETE MOVES
NODE deleteMoves(NODE start){
	while(start!=NULL){
		start=deleteBegin(start);	
	}
	return start;
}

NODE2 deleteMoves2(NODE2 start){
	while(start!=NULL){
		start=deleteBegin2(start);	
	}
	return start;
}



//FUNCTION TO CHECK CHECK
bool checkCheck(char **a,int mov){
	int x1=0,y1=0,i,j,Z,A,flag=0;
	NODE check,cur;
	int *xy1;
	xy1=(int*)malloc(2*sizeof(int));
	char c;
	if(mov%2==0){
		A=(int)'A';
		Z=(int)'Z';
		c='k';
	}
	else
	{	c='K';
		A=(int)'a';
		Z=(int)'z';
	}
	for(i=0;i<8;i++){
		for(j=0;j<8;j++){
			if(c==a[i][j]){
				x1=i;
				y1=j;
				flag=1;
				break;
			}
			if(c==a[i][j]){
				x1=i;
				y1=j;
				flag=1;
				break;
			}
			if(flag==1)
				break;
		}
	}
	
	check=(NODE)malloc(sizeof(struct node));
	check->x=0;
	check->y=0;
	check->next=NULL;
	cur=check;
	for(i=0;i<8;i++){
		for(j=0;j<8;j++){
			c=a[i][j];
			if(c>=A&&c<=Z){
				*xy1=i+1;
				*(xy1+1)=j+1;
				while(cur->next!=NULL)
					cur=cur->next;
				cur->next=suggestingMove(a,xy1);
			}
				
		}
	}
	cur=check;
	while(cur!=NULL){
		if(cur->x==x1&&cur->y==y1){
			deleteMoves(check);
			return true;
		}
		cur=cur->next;
	}
	deleteMoves(check);
	return false;	
}
