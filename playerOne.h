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
        bool maxPlayer;
        int cor_x,cor_y,grade;
        struct node* child[5][6];
        node(){}
        node(int x,int y):cor_x(x),cor_y(y){};
    };
    int edge[5][6];
    Color self;
    class gameTree{
        public:
            int minmax(int depth,int limit,struct node* now,bool maxPlayer){
                if(depth==0) return now->grade;
                //設置顏色
                Color enmyColor=Blue;
                if(self==Blue) enmyColor=Red;
                //
                if(maxPlayer){
                    this->makechild(now,self);
                    int best=-10000;
                    for(int i=0;i<5;i++){
                        for(int j=0;j<6;j++){
                            if(now->child[i][j]==NULL) continue;
                            int value=minmax(depth-1,limit,now->child[i][j],false);
                            if(value>best){
                                best=value;
                                //回傳座標
                                if(depth==limit){
                                    this->x=i;
                                    this->y=j;
                                }
                            } 
                            delete now->child[i][j];
                        }
                    }
                    if(best==-10000) best=now->grade;
                    now->grade = best;
                    return best;
                }else{
                    this->makechild(now,enmyColor);
                    int best=10000;
                    for(int i=0;i<5;i++){
                        for(int j=0;j<6;j++){
                            if(now->child[i][j]==NULL) continue;
                            int value = minmax(depth-1,limit,now->child[i][j],true);
                            if(value<best){ 
                                best=value;
                            } 
                            delete now->child[i][j];
                        }
                    }
                    if(best==10000) best=now->grade;
                    now->grade = best;
                    return best;
                }
            }
            void makechild(struct node* now,Color inputColor){
                //建造孩子
                for(int i =0;i<5;i++){
                    for(int j=0;j<6;j++){
                        now->child[i][j]=NULL;
                        //如果這步可以走
                        if(now->color[i][j]==inputColor||now->color[i][j]==White){
                            struct node* newNode=new node(i,j);
                            this->copy(newNode,now->board,now->color);
                            newNode->maxPlayer = !now->maxPlayer;
                            game(i,j,newNode->board,newNode->color,inputColor);
                            newNode->grade = score(newNode->board,edge,newNode->color,self);
                            now->child[i][j]=newNode;
                        }
                    }
                }
            }
            struct direc di[4]={{1,0},{-1,0},{0,1},{0,-1}};
            void game(int x,int y,int Record[5][6],Color color[5][6],Color inputColor){
                if(color[x][y]==inputColor||color[x][y]==White){
                    Record[x][y]++;
                    color[x][y]=inputColor;
                    if(Record[x][y]==edge[x][y]){
                        color[x][y]=Black;
                        this->chain(x,y,Record,color,inputColor);
                    }
                }else{
                    throw "wrong position!";
                }
            }
            void chain(int x,int y,int Record[5][6],Color color[5][6],Color inputColor){
                for(int i = 0;i<4;i++){
                    int corX=x+di[i].x;int corY=y+di[i].y;
                    if(0<=corX && corX<5 && 0<=corY && corY<6){
                        //add point
                        Record[corX][corY]++;
                        //chain explode
                        if(Record[corX][corY]==edge[corX][corY]){
                            this->chain(corX,corY,Record,color,inputColor);
                        }
                        //draw color
                        if(Record[corX][corY]<edge[corX][corY]){
                            color[corX][corY]=inputColor;
                        }else{
                            color[corX][corY]=Black;
                        }
                    }
                }
            }
            int score(int Record[5][6],int Max[5][6],Color color[5][6],Color inputColor){
                int myself=0,enmy=0;
                for(int i = 0;i<5;i++){
                    for(int j=0;j<6;j++){
                        if(color[i][j]==inputColor){
                            myself+=Record[i][j];myself++;
                        }else if(color[i][j]!=White && color[i][j]!=Black && color[i][j]!=inputColor){
                            enmy+=Record[i][j];enmy++;
                        }
                    }
                }
                return myself-enmy;
            }
            static void printScore(struct node* now){
                for(int i = 0;i<5;i++){
                    for(int j=0;j<6;j++){
                        if(now->child[i][j]==NULL){
                            std::cout<<"n ";
                        }else{
                            std::cout<<now->child[i][j]->grade<<" ";
                        }
                    }   
                    std::cout<<std::endl;
                }
            }
            static void printBoard(struct node* now){
                for(int i = 0;i<5;i++){
                    for(int j=0;j<6;j++){
                        std::cout<<now->board[i][j]<<"-"<<now->color[i][j]<<" ";
                    }   
                    std::cout<<std::endl;
                }
            }
            void copy(struct node *to,int from[5][6],Color color[5][6]){
                for(int i =0;i<5;i++){
                    for(int j=0;j<6;j++){
                        to->color[i][j] = color[i][j];
                        to->board[i][j] = from[i][j];
                    }
                }
            }
            friend class Student;
        private:
            int x,y;
            struct node* root;
    };
    class Student{
        public:
            void makeMove(int Record[5][6],int Max[5][6],Color color[5][6],Color inputColor){
                for(int i =0;i<5;i++){
                    for(int j=0;j<6;j++){
                        edge[i][j]=Max[i][j];
                    }
                }
                self=inputColor;
                gameTree tree;
                tree.root = new node;
                this->copy(tree.root,Record,color,false);
                int value=tree.minmax(4,4,tree.root,true);
                this->x=tree.x;
                this->y=tree.y;
                delete tree.root;
                std::cout<<tree.x<<tree.y<<" "<<value<<std::endl;
            }
            static void copy(struct node *to,int from[5][6],Color color[5][6],bool maxPlayer){
                to->maxPlayer = maxPlayer;
                for(int i =0;i<5;i++){
                    for(int j=0;j<6;j++){
                        to->color[i][j] = color[i][j];
                        to->board[i][j] = from[i][j];
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

};




#endif
