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
        node* child[5][6];
        node(int x,int y):cor_x(x),cor_y(y){
            for(int i=0;i<5;i++){
                for(int j=0;j<6;j++){
                    child[i][j]=NULL;
                }
            }
        };
        ~node() {}
    };
    int edge[5][6];
    Color self;
    class gameTree{
        public:
            int minmax(int depth,int limit,struct node* now,bool maxPlayer,int alpha,int beta){
                if(depth==0) return now->grade;
                //設置顏色
                Color enmyColor=Blue;
                if(self==Blue) enmyColor=Red;
                //
                if(maxPlayer){
                    this->makechild(now,self);
                    for(int i=0;i<5;i++){
                        for(int j=0;j<6;j++){
                            if(now->child[i][j]==NULL) continue;
                            int value=minmax(depth-1,limit,now->child[i][j],false,alpha,beta);
                            if(value>alpha){
                                alpha=value;
                                //回傳座標
                                if(depth==limit){
                                    this->x=i;
                                    this->y=j;
                                }
                            }
                            delete now->child[i][j];
                            if (beta <= alpha){
                                if(depth==limit){
                                    this->x=i;
                                    this->y=j;
                                }
                                break;
                            }
                        }
                    }
                    if(alpha==-1000) alpha=now->grade;
                    now->grade = alpha;
                    return alpha;
                }else{
                    this->makechild(now,enmyColor);
                    for(int i=0;i<5;i++){
                        for(int j=0;j<6;j++){
                            if(now->child[i][j]==NULL) continue;
                            int value = minmax(depth-1,limit,now->child[i][j],true,alpha,beta);
                            if(value<beta) beta=value;
                            delete now->child[i][j];
                            if(beta<=alpha) break;
                        }
                    }
                    if(beta==1000) beta=now->grade;
                    now->grade = beta;
                    return beta;
                }
            }
            void makechild(struct node* now,Color inputColor){
                //建造孩子
                for(int i =0;i<5;i++){
                    for(int j=0;j<6;j++){
                        //如果這步可以走
                        if(now->color[i][j]==inputColor||now->color[i][j]==White){
                            now->child[i][j]=new node(i,j);
                            this->copy(now->child[i][j],now->board,now->color);
                            now->child[i][j]->maxPlayer = !now->maxPlayer;
                            game(i,j,now->child[i][j]->board,now->child[i][j]->color,inputColor);
                            now->child[i][j]->grade = score(now->child[i][j]->board,edge,now->child[i][j]->color,self);
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
                tree.root = new node(-1,-1);
                this->copy(tree.root,Record,color,false);
                int value=tree.minmax(4,4,tree.root,true,-1000,1000);
                this->x=tree.x;
                this->y=tree.y;//std::cout<<tree.x<<tree.y<<" "<<value<<std::endl;
                delete tree.root;
                
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
