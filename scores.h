//Sets different scores for both players based on kills
void scoreBoard(char c,int *score,int mov){
	int point=0;
	switch(c){
		case 'Q':
		case 'q':point=9;
				break;
		case 'r':
		case 'R':point=7;
				break;
		case 'n':
		case 'N':point=7;
				break;
		case 'b':
		case 'B':point=5;
				break;
		case 'p':
		case 'P':point=3;
				break;
		default :point=0;
	}
	if(mov%2==0)
		*(score +1)=*(score+1)+point;
	else
	*(score)=*(score)+point;	
}
