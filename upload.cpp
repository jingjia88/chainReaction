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
            void makechild(struct node* cur,int layer,int limit,int Record[5][6],int Max[5][6],Color color[5][6],Color inputColor){
                if(layer>limit) return ;
                Color enmyColor;
                if(inputColor==Red){ enmyColor=Blue;}
                else{ enmyColor=Red;}
                int min=1000;int k =0;
                for(int i =0;i<5;i++){
                    for(int j =0;j<6;j++){
                        if(color[i][j]==inputColor||color[i][j]==White){
                            struct node* newNode=new node(i,j,inputColor);
                            for(int i =0;i<5;i++){
                                for(int j =0;j<6;j++){
                                    newNode->board[i][j] = Record[i][j];
                                    newNode->color[i][j] = color[i][j];
                                } 
                            }//std::cout<<i<<j<<"aaa"<<std::endl;
                            game(i,j,newNode->board,Max,newNode->color,inputColor);
                            cur->child[k] = newNode;
                            makechild(cur->child[k],layer+1,limit,cur->child[k]->board,Max,cur->child[k]->color,enmyColor);
                            if(layer==limit){
                                int grade = score(newNode->board,Max,newNode->color,enmyColor);
                                cur->child[k]->grade = grade;
                                if(grade<=min){
                                    min=grade;
                                }
                            }
                            k++;
                        }
                    } 
                }
                if(layer<limit){
                    for(int i =0;i<30&&cur->child[i]!=nullptr;i++){
                        if(min>cur->child[i]->grade){
                            min=cur->child[i]->grade;
                        }
                    }
                }
                cur->grade = min;
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
            int score(int Record[5][6],int Max[5][6],Color color[5][6],Color inputColor){
                int self=0,enmy=0;
                for(int i = 0;i<5;i++){
                    for(int j=0;j<6;j++){
                        if(color[i][j]==inputColor){
                            self+=Record[i][j];
                        }else if(color[i][j]!=White && color[i][j]!=Black && color[i][j]!=inputColor){
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
                gameTree tree;
                struct node* newNode=new node;
                for(int i =0;i<5;i++){
                    for(int j =0;j<6;j++){
                        newNode->board[i][j] = Record[i][j];
                        newNode->color[i][j] = color[i][j];
                    } 
                }
                tree.root = newNode;int max=-1000;
                tree.makechild(tree.root,2,3,Record,Max,color,inputColor);
                for(int i =0;tree.root->child[i]!=nullptr&&i<30;i++){
                    if(max<=tree.root->child[i]->grade){
                        max = tree.root->child[i]->grade;
                        this->x = tree.root->child[i]->cor_x;
                        this->y = tree.root->child[i]->cor_y;
                    }
                    //std::cout<<tree.root->child[i]->grade<<" "<<tree.root->child[i]->cor_x<<tree.root->child[i]->cor_y<<std::endl;
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