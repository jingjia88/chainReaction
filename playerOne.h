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
        node(){}
        node(int x,int y,Color c):cor_x(x),cor_y(y),selfColor(c){};
    };
    class gameTree{
        public:
            int* makechild(int Record[5][6],int Max[5][6],Color color[5][6],Color inputColor){
                int max=-1000;int* res=new int[2];
                for(int i =0;i<5;i++){
                    for(int j =0;j<6;j++){
                        struct node* newNode=new node(i,j,inputColor);
                        if(color[i][j]==inputColor||color[i][j]==White){
                            for(int i =0;i<5;i++){
                                for(int j =0;j<6;j++){
                                    newNode->board[i][j] = Record[i][j];
                                    newNode->color[i][j] = color[i][j];
                                } 
                            }
                            game(i,j,newNode->board,Max,newNode->color,inputColor);
                            newNode->grade = score(newNode->board,Max,newNode->color,inputColor);
                            root->child[6*i+j] = newNode;
                            if(newNode->grade>max){
                                max=newNode->grade;
                                res[0] =i;
                                res[1] =j;
                            } 
                        }
                    } 
                }
                return res;
            }
            struct direc di[4]={{1,0},{-1,0},{0,1},{0,-1}}; 
            void game(int x,int y,int Record[5][6],int Max[5][6],Color color[5][6],Color inputColor){
                if(color[x][y]==inputColor||color[x][y]==White){
                    Record[x][y]++;
                    color[x][y]=inputColor;
                    if(Record[x][y]==Max[x][y]){
                        color[x][y]=Black;
                        this->chain(x,y,Record,Max,color,inputColor);
                    }
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
            friend class Student;

        private:
            struct node* root;
    };
    class Student{
        public:
            void makeMove(int Record[5][6],int Max[5][6],Color color[5][6],Color inputColor){
                Color enmyColor;
                if(inputColor==Red){ enmyColor=Blue;}
                else{ enmyColor=Red;}
                
                gameTree tree;
                struct node* newNode=new node;
                newNode->selfColor= enmyColor;
                for(int i =0;i<5;i++){
                    for(int j =0;j<6;j++){
                        newNode->board[i][j] = Record[i][j];
                        newNode->color[i][j] = color[i][j];
                    } 
                }
                tree.root = newNode;
                int *arr =tree.makechild(Record,Max,color,inputColor);
                x = arr[0];
                y = arr[1]; 
                delete []arr;
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
    
    
};
    



#endif