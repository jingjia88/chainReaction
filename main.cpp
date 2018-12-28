#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include "playerOne.h"
#include "playerTwo.h"

enum PlayStatus{
    // not important
};

void run(int x,int y){

}
int main()
{
    int Record[5][6],Max[5][6]; Color color[5][6],inputColor;
    for(int i =0;i<5;i++){
        for(int j = 0;j<6;j++){
            Record[i][j] = 0;
            Max[i][j] = 3;
        }
    }
    for(int i =1;i<6;i++) Max[0][i]=2;
    for(int i =1;i<5;i++) Max[i][0]=2;
    for(int i =1;i<6;i++) Max[5][i]=2;
    for(int i =1;i<5;i++) Max[i][6]=2;
    Max[0][0] = 1;Max[0][6]=1;Max[5][0]=1;Max[5][6]=1;
    // something check who is the winner
    playerOne::Student one;
    playerTwo::Student two;
    int x,y; bool playone = true;
    while(true){
        if(playone){
            inputColor=Blue;
            one.makeMove(Record,Max,color,inputColor);
            x = one.getX();y = one.getY();
            playone = false;
        }else{
            inputColor=Red;
            two.makeMove(Record,Max,color,inputColor);
            x = two.getX();y = two.getY();
            playone = true;
        }
        run(x,y);
    }

}