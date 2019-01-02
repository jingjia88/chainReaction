#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include "playerOne.h"
#include "playerTwo.h"
#include "Board.h"
enum PlayStatus{
    // not important
};

int main()
{
    int Record[5][6],Max[5][6]; Color color[5][6],inputColor;
    for(int i =0;i<5;i++){
        for(int j = 0;j<6;j++){
            Record[i][j] = 0;
            Max[i][j] = 4;
            color[i][j] = White;
        }
    }
    for(int i =1;i<5;i++) Max[0][i]=3;
    for(int i =1;i<4;i++) Max[i][0]=3;
    for(int i =1;i<5;i++) Max[4][i]=3;
    for(int i =1;i<4;i++) Max[i][5]=3;
    Max[0][0] = 2;Max[0][5]=2;Max[4][0]=2;Max[4][5]=2;
    Board play;
    struct node{
        int board[5][6];
        Color color[5][6];
        Color selfColor;
        int cor_x,cor_y;
        int grade;
        struct node* child[30];
        node(){}
        node(int x,int y,Color c):cor_x(x),cor_y(y),selfColor(c){};
    };
    
    // something check who is the winner
    playerOne::Student one;
    playerTwo::Student two;
    int x,y; bool playone = false;
    // two.makeMove(Record,Max,color,Blue);
    // x = two.getX();y = two.getY();
    one.makeMove(Record,Max,color,Blue);
    x = one.getX();y = one.getY();
    play.game(x,y,Record,Max,color,Blue);  
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
        cout<<x<<"/"<<y<<playone<<endl;
        play.game(x,y,Record,Max,color,inputColor);  
        bool onewin=false,twowin=false;
        for(int i =0;i<5;i++){
            for(int j =0;j<6;j++){
                if(color[i][j]==Blue) onewin=true;
                if(color[i][j]==Red) twowin=true;
                cout<<Record[i][j]<<"-"<<color[i][j]<<"="<<Max[i][j]<<" ";
            } 
            cout<<endl;
        }
        if(onewin==false){
            cout<<"two win"<<endl;
            break;
        }
        if(twowin==false){
            cout<<"one win"<<endl;
            break;
        }
    }
}