#include <iostream>
using namespace std;
struct direc{
    int x, y;
    direc(int X, int Y) : x(X), y(Y) {}
};
class Board{
    public:
        struct direc di[4]={{1,0},{-1,0},{0,1},{0,-1}}; 
        void game(int x,int y,int Record[5][6],int Max[5][6],Color color[5][6],Color inputColor){
            if(color[x][y]==inputColor||color[x][y]==White){
                Record[x][y]++;
                color[x][y]=inputColor;
                            
                if(Record[x][y]==Max[x][y]){ 
                    color[x][y]=Black;
                    this->chain(x,y,Record,Max,color,inputColor);
                }
            }else{
                throw "wrong position!";
            }
        }
        void chain(int x,int y,int Record[5][6],int Max[5][6],Color color[5][6],Color inputColor){
            for(int i = 0;i<4;i++){
                int corX=x+di[i].x;int corY=y+di[i].y;
                if(0<=corX && corX<5 && 0<=corY && corY<6){
                    //add point
                    Record[corX][corY]++; 
                    //chain explode
                    if(Record[corX][corY]==Max[corX][corY]){
                        this->chain(corX,corY,Record,Max,color,inputColor);
                    }
                    
                    //draw color
                    if(Record[corX][corY]<Max[corX][corY]){
                        color[corX][corY]=inputColor;
                    }else{
                        color[corX][corY]=Black;
                    }
                }
            }
        }
    
};