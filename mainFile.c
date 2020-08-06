#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include "computerMoves.h"
#include <string.h>
#include <time.h>
#include "scores.h"

char **a;
char message;
int select=0,move=0;
int *xy,*xy2,*xy3,moves=0,chec=0,*score,end=0;
char playw[]="WHITE'S MOVE",playb[]="BLACK'S MOVE", check[]="CHECK",endgame[15]="";

NODE start=NULL;

//INIALIZES THE BOARD
void initialize(){
	int i;
	for(i=0;i<8;i++){
			a[1][i]='P';
			a[2][i]=' ';
			a[3][i]=' ';
			a[4][i]=' ';
			a[5][i]=' ';
			a[6][i]='p';
		}
		a[0][0]='R';a[0][1]='N';a[0][2]='B';a[0][3]='Q';a[0][4]='K';a[0][5]='B';a[0][6]='N';a[0][7]='R';
		a[7][0]='r';a[7][1]='n';a[7][2]='b';a[7][3]='q';a[7][4]='k';a[7][5]='b';a[7][6]='n';a[7][7]='r';
		for(i=0;i<2;i++)
		xy3=(int*)malloc(2*sizeof(int));
}
//FUNCTION TO SET COLOR TO BACKGROUND
void setup(){
	glClearColor(0.47f,0.47f,0.47f,1.0f);
}

//FUNCTION CALLED WHEN THE MOUSE IS CLICKED
void onMouseClic(int button,int state, int x, int y){
	char c,q;
	int i,j;
	if(x>=60&&x<=540&&y>=60&&y<=540)
	{	if(button==GLUT_RIGHT_BUTTON&&state==GLUT_DOWN){
			select=0;
			start=deleteMoves(start);
			message='S';
		}
		if(button==GLUT_LEFT_BUTTON&&state==GLUT_DOWN){
		if(select==0&&move==0){
			*xy=y/60;
			*(xy+1)=x/60;
			if(selectionCheck(a,xy,moves)==1)
			{
				select = 1;
				message='M';
				start=suggestingMove(a,xy);
			}
				
		}
		else{
			
			*xy2=y/60;
			*(xy2+1)=x/60;
			
			if(validMove(xy2,xy,start)){
				c=a[*xy-1][*(xy+1)-1];	
				q=a[y/60-1][x/60-1];			
				a[y/60-1][x/60-1]=c;
				a[*xy-1][*(xy+1)-1]=' ';
				message='S';
				if(q=='k')
	{	end++;
		strcpy(endgame,"WHITE WIN!!");
		}
	if(q=='K'){
		end++;
		strcpy(endgame,"BLACK WIN!!");
	}
				if(q!=' ')
					scoreBoard(q,score,moves+1);
					
				start=deleteMoves(start);
				select=0;
				if(checkCheck(a,moves)){
					chec=1;
				}
				else
					 chec=0;
				moves++;
				
			}
			
		}
		
		
	}
	}
	glutPostRedisplay();

}

int reverse(int a){
	int b;
	b=a%10;
	a=a/10;
	b=b*10+a%10;
	return b;
	
}
//FUNCTION TO DISPLAY THE SUGGESTION FOR PLAYER
void drawSuggestion(){
	NODE cur;
	int x,y;
	if(start!=NULL){
		cur=start;
	
		while(cur!=NULL){
			x=cur->x;
			y=cur->y;
				glColor3f(0.0f,0.0f,0.0f);
				glPolygonMode(GL_BACK,GL_FILL);
				glRectf(-0.8f+y*0.2f,0.8f-x*0.2f,-0.8f+y*0.2f+0.05f,0.8f-x*0.2f-0.05f);
			cur=cur->next;
		}
		
	}
}


//FUNCTION FOR THE MAIN DISPLAY
void display(){
	int i=0,j=0;
	char c;
	GLfloat x1,y1;
	//Displays selection mode or suggestion mode
	glClear(GL_COLOR_BUFFER_BIT);\
	glColor3f(1.0f,1.0f,1.0f);
	glRectf(-0.84f,0.84f,0.84f,-0.84f);
	glRasterPos2f(0.9f,0.9f);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, message);
    //Displays white or black's play			
	glRasterPos2f(-0.9f,0.9f);
		if(moves%2==0){
			glColor3f(1.0,1.0,1.0);
			for(i=0;playw[i]!='\0';i++)
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, playw[i]);
		}
		else {
			glRasterPos2f(-0.9f,-0.9f);
			glColor3f(0.0,0.0,0.0);
			for(i=0;playb[i]!='\0';i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, playb[i]);	
		}
	//Displays whether it has a check condition
		if(chec==1){
				glColor3f(1.0,0.0,0.0);
				glRasterPos2f(-0.05f,0.9f);
				for(i=0;check[i]!='\0';i++)
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, check[i]);
		}
		
		
     //Displays the score		
		glColor3f(1.0,1.0,1.0);
		glRasterPos2f(-1.0f,0.8f);
	    i=*score;
		i=reverse(i);		
		for(i;i>0;i=i/10){
		
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, i%10+'0');
		}
		glColor3f(0.0,0.0,0.0);
			glRasterPos2f(0.9f,-0.8f);
			i=*(score+1);
			i=reverse(i);
			for(i;i>0;i=i/10){
					glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, i%10+'0');
			}		
		
		//DISPLAYING BOARD ALONG WITH PAWNS
		for(i=0;i<8;i++){
		y1=0.8f-i*0.2f;
		for(j=0;j<8;j++){
			
			x1=-0.8f+j*0.2f;
			c=a[i][j];
				if((i+j)%2==0){
					glColor3f(0.490f,0.686f,0.635f);
					glPolygonMode(GL_BACK,GL_FILL);
					glRectf(x1,y1,x1+0.2f,y1-0.2f);
				}
				else{
					glColor3f(0.6f,1.0f,0.78f);
					glPolygonMode(GL_BACK,GL_FILL);
					glRectf(x1,y1,x1+0.2f,y1-0.2f);
				}
					if(c>'A'&&c<'Z')
						glColor3f(1.0,1.0,1.0);
					else
						glColor3f(0.0,0.0,0.0);
				glRasterPos2f(x1+0.1f,y1-0.1f);
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
		}
		
	}
	//Check whether the game has ended or not
	if(end==1||end==2){
		glColor3f(1.0f,1.0f,1.0f);
		end++;
		glRasterPos2f(-0.1f,0.1f);
		for(i=0;endgame[i]!='\0';i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, endgame[i]);
	}
	drawSuggestion();
	glFlush();
	glutSwapBuffers();
}
//FUNCTION FOR COMPUTER MOVE
void computermove(){
	node2 mov;
	int x,x1;
	char c,q;
	if(moves==0){
		x=rand()%7;
		c=a[1][x];
		x1=rand()%2;
		a[x1+1][x]=c;
		a[1][x]=' ';
		moves++;
	}
	else {
	 		mov=mobility(a,1);
			q=a[mov.x2-1][mov.y2-1];
			a[mov.x2-1][mov.y2-1]=a[mov.x1-1][mov.y1-1];
			a[mov.x1-1][mov.y1-1]=' ';	
			if(q=='k')
	{		
            end++;
			strcpy(endgame,"WHITE WIN!!");
	}
	if(q=='K'){
		end++;
		strcpy(endgame,"BLACK WIN!!");
	}
	if(q!=' ')
		scoreBoard(q,score,moves+1);
	if(checkCheck(a,moves)){
		chec=1;
	}
	else
		chec=0;
	moves++;
	}
	glutPostRedisplay();
}
//Function calls on mouse click
void onMouseClick(int button,int state, int x, int y){
	if(moves%2==0)
		computermove();
	else 
		onMouseClic(button,state,x,y);	
		}


int main(int argc,char *argv[]){
	int i;
	a=(char**)malloc(8*sizeof(char*));	

	for(i=0;i<8;i++)
		*(a+i)=(char*)malloc(8*sizeof(char));
	initialize();
	
	message='S';
	xy=(int*)malloc(2*sizeof(int));
	xy2=(int*)malloc(2*sizeof(int));
	score=(int*)malloc(2*sizeof(int));
	
	*score=0;
	*(score+1)=0;
	
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowSize(600,600);
	glutInitWindowPosition(300,100);
	glutCreateWindow("CHESS BOARD");
	
	setup();
	
	glutMouseFunc(onMouseClick);	
	glutDisplayFunc(display);
	
	glutMainLoop();
	return 0;
	
}
