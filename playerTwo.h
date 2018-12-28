#include <iostream>

namespace playerTwo
{
    struct direc{
        int x, y;
        direc(int X, int Y) : x(X), y(Y) {}
    };
    class Student{
        public:
            int **value;
            void makeMove(int Record[5][6],int Max[5][6],Color color[5][6],Color inputColor){
                value = new int*[5];
                for(int i = 0; i < 5; i++) {
                    value[i] = new int[6];
                }
                for(int i =0;i<5;i++){
                    for(int j =0;j<6;j++){
                        value[i][j] = 0;
                    }
                }
                this->corner(Record);
                this->edge(Record);
                this->explode(Record,Max);
                this->eat(Record,color,inputColor);
                int max=-1;
                for(int i =0;i<5;i++){
                    for(int j =0;j<6;j++){
                        if(max<=value[i][j] && color[i][j]!=Black && (color[i][j]==inputColor||color[i][j]==White)){
                            max = value[i][j];
                            this->x = i;
                            this->y = j;
                        }
                    }
                }
                for(int i = 0; i < 6; ++i) {
                    delete[] value[i];   
                }
                delete[] value;
            }
            void eat(int Record[5][6],Color color[5][6], Color inputColor){
                if(inputColor==Red){inputColor = Blue;}else{inputColor=Red;}
                for(int i =0;i<5;i++){
                    for(int j =0;j<6;j++){
                        if(color[i][j]==inputColor){
                            if(i+1<5 && Record[i+1][j]>=Record[i][j]) value[i+1][j]+=3;
                            if(i-1>=0 && Record[i-1][j]>=Record[i][j]) value[i-1][j]+=3;
                            if(j+1<5 && Record[i][j+1]>=Record[i][j]) value[i][j+1]+=3;
                            if(j-1>=0 && Record[i][j-1]>=Record[i][j]) value[i][j-1]+=3;
                        }
                    }
                }
            }
            void explode(int Record[5][6],int Max[5][6]){
                for(int i =0;i<5;i++){
                    for(int j =0;j<6;j++){
                        if(Record[i][j]==Max[i][j]-1) value[i][j]+=1;
                    }
                }
            }
            void corner(int Record[5][6]){
                if(Record[0][0]<1 ) value[0][0]+=5;
                if(Record[0][5]<1 ) value[0][5]+=5;
                if(Record[4][0]<1 ) value[4][0]+=5;
                if(Record[4][5]<1 ) value[4][5]+=5;
            }
            void edge(int Record[5][6]){
                for(int i=1;i<5;i++){
                    if(Record[0][i]<1) value[0][i]+=2;
                }
                for(int i=1;i<4;i++){
                    if(Record[i][0]<1) value[i][0]+=2;
                }
                for(int i=1;i<5;i++){
                    if(Record[4][i]<1) value[4][i]+=2;
                }
                for(int i=1;i<4;i++){
                    if(Record[i][5]<1) value[i][5]+=2;
                }
            }
            // Any Code You Want to Add
            int getX(){
                // Your Code
                return x;
            }
            int getY(){
                // Your Code
                return y;
            }
        private:
            int x;
            int y;
    };
    class gameTree{
        public:
            struct node{
                int board[5][6];
                Color color[5][6];
                Color selfColor;
                struct node* child[30];
                int cor_x,cor_y;
                int grade;
            };

    };

    class play{
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
                    if(0<=x+di[i].x<5 && 0<=y+di[i].y<6){
                        //chain explode
                        if(Record[x+di[i].x][y+di[i].y]==Max[x+di[i].x][y+di[i].y]-1){
                            this->chain(x+di[i].x,y+di[i].y,Record,Max,color,inputColor);
                        }
                        //add point
                        Record[x+di[i].x][y+di[i].y]++; 
                        //draw color
                        if(Record[x+di[i].x][y+di[i].y]<Max[x+di[i].x][y+di[i].y]){
                            color[x+di[i].x][y+di[i].y]=inputColor;
                        }else{
                            color[x+di[i].x][y+di[i].y]=Black;
                        }
                    }
                }
            }
            int score(int Record[5][6],int Max[5][6],Color color[5][6],Color inputColor){
                int self=0,enmy=0;
                for(int i = 0;i<5;i++){
                    for(int j=0;j<6;j++){
                        if(color[i][j]==inputColor && Record[i][j]<Max[i][j]){
                            self+=Record[i][j];
                        }else if(color[i][j]!=inputColor && Record[i][j]<Max[i][j]){
                            enmy+=Record[i][j];
                        }
                    }
                }
                return self-enmy;
            }
    };

}
