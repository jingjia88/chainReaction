#include <iostream>

class Board{
    public:
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
                if(0<=x+di[i].x<5 && 0<=y+di[i].y<6){
                    //add point
                    Record[x+di[i].x][y+di[i].y]++; 
                    //draw color
                    if(Record[x+di[i].x][y+di[i].y]<Max[x+di[i].x][y+di[i].y]){
                        color[x+di[i].x][y+di[i].y]=inputColor;
                    }else{
                        color[x+di[i].x][y+di[i].y]=Black;
                    }
                    //chain explode
                    if(Record[x+di[i].x][y+di[i].y]==Max[x+di[i].x][y+di[i].y]){
                        this->chain(x+di[i].x,y+di[i].y,Record,Max,color,inputColor);
                    }
                }
            }
    
};