#ifndef PLAYERONE_H
#define PLAYERONE_H

#include <iostream>
enum Color{
    White, // Initital 0
    Blue, // Player One
    Red, // Player Two
    Black //Explosion
};
namespace playerOne
{
    struct direc{
        int x, y;
        direc(int X, int Y) : x(X), y(Y) {}
    };
    struct node{
        int board[5][6];
        Color color[5][6];
        Color selfColor;
        int cor_x,cor_y;
        int grade;
        struct node* child[30];
        node(int x,int y,Color c):cor_x(x),cor_y(y),selfColor(c){}
    };
    class Student{
        public:
            void makeMove(int Record[5][6],int Max[5][6],Color color[5][6],Color inputColor){
                gameTree tree;
                tree.root=new node(0,0,inputColor);
                for(int i =0;i<5;i++){
                    for(int j =0;j<6;j++){
                        
                    } 
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
            void makechild(){

            }
            friend class Student;

        private:
            struct node* root;
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
};



#endif