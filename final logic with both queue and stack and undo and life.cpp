#include<stdlib.h>
#include<iostream>
#include<stdio.h>
#include<conio.h>
using namespace std;
static int s0,s1;
static int k,l;
static int p,q;
static int life=3;
#define row 8
#define col 8
//#define row 6
//#define col 6
struct maze
{
    int x;
    int y;
    struct maze *next;
};

            struct  maze *top=NULL;
struct node
{
    int x,y;
    struct node *next;
};
struct maze *front = NULL;
struct maze *rear= NULL;
static int score=0;
struct coords
{
    int x,y;
};
struct node *push(struct node *top,int x,int y,char a[row][col])
{
struct node *n;

        n=new node;
        n->x=x;
        n->y=y;
        a[n->x][n->y]='$';
        n->next=top;
        top=n;

    return top;
};
struct node *pop(struct node *top,char a[row][col])
{

    a[top->x][top->y]='*';
    struct node *x=top;
    top=top->next;
    delete(x);
    return top;
};
void createobstacles(char a[row][col])
{   a[1][0]=a[1][3]=a[1][6]=a[3][7]=a[3][4]=a[4][1]=a[4][6]=a[6][3]=a[6][6]='X';
    //a[2][3]=a[0][2]=a[0][3]=a[0][4]=a[1][4]=a[3][3]=a[4][2]=a[4][3]=a[4][4]='X';
//a[0][2]=a[0][3]=a[0][4]=a[1][0]=a[1][3]=a[1][4]=a[2][0]=a[2][1]=a[2][4]=a[3][0]=a[3][1]=a[3][4]=a[4][0]=a[4][3]=a[4][4]=a[5][0]='X';
}
void setMatrix(char a[row][col],int p,int q,int cx,int cy)
{
    int i,j;
    for(i=0;i<row;i++)
        for(j=0;j<col;j++)
        a[i][j]=' ';
    createobstacles(a);
    //c->x=0;
    //c->y=0;
    a[cx][cy]='S';
  a[p][q]='D';
  //a[3][4]='D';
  //  a[0][5]='D';

}
struct maze *pushQueue(struct maze *top,int x,int y)
{
struct maze *n;

        n=new maze;
        n->x=x;
        n->y=y;
        n->next=top;
        top=n;

    return top;
};
struct maze *popQueue(struct maze *top,char board[row][col])
{
    //cout<<"inside popQueue function\n";
    board[top->x][top->y]=' ';
    struct maze *x=top;
    top=top->next;
    delete(x);
    //cout<<"returning top\n";
    return top;
};

void Enqueue(int x,int y,char a[row][col])
{
    struct maze *temp;
    temp = new maze;
    temp->x = x;
    temp->y=y;
    temp->next=NULL;
    a[temp->x][temp->y]='$';
    if(front == NULL && rear == NULL)
    {
        front = rear = temp;
        return;
    }
    rear->next = temp;
    rear = temp;

}
void Dequeue(char a[row][col])
{

struct maze *temp= front;
a[temp->x][temp->y]='*';
if(front == NULL) return;
if(front == rear )
{
    front = rear = NULL;
}
else
{
    front = front->next;
}
delete(temp);
return;
}

void printMatrix(char a[row][col])
{
    cout<<"\nlife is" <<life<<"\t\tScore is "<<score<<endl;
    int i,j;
    for(i=0;i<=col+1;i++)
        printf("!");
        printf("\n");
    for(i=0;i<row;i++)
    {   printf("!");
        for(j=0;j<col;j++)
            printf("%c",a[i][j]);
        printf("!");
        printf("\n");
    }
for(i=0;i<=col+1;i++)
        printf("!");
}
int mazeWithQueues(struct coords c,char a[row][col])
{
    int x;
    int endReached=0,blocked=0;
            int f=0;
    while(f!=1)
{


    x=0;
    c.x=front->x;
        c.y=front->y;
       // cout<<endl<<front->x<<endl<<front->y<<endl;
        if((c.y+1<col)&&(a[c.x][c.y+1]!='X') && (a[c.x][c.y+1]!='*')  && (a[c.x][c.y+1]!='$'))
        {
            if(a[c.x][c.y+1]!='D'){
            //cout<<"\nright\n";
            Enqueue(c.x,c.y+1,a);
            x=1;
        }
        else
            {
                endReached=1;
                x=1;
              a[c.x][c.y+1]='*';
              Dequeue(a);
                f=1;
            }
        }
        if((c.x+1<row) && (a[c.x+1][c.y]!='X') && (a[c.x+1][c.y]!='*')  && (a[c.x+1][c.y]!='$'))
        {
            if(a[c.x+1][c.y]!='D'){
            //cout<<"\ndown\n";
            Enqueue(c.x+1,c.y,a);
            x=1;
        }
        else{
                endReached=1;
            a[c.x+1][c.y]='*';
            Dequeue(a);
             f=1;
             x=1;
        }
        }
        if((c.x-1>=0) && (a[c.x-1][c.y]!='X') && (a[c.x-1][c.y]!='*')  && (a[c.x-1][c.y]!='$'))
        {
              if(a[c.x-1][c.y]!='D')
              {
                x=1;
            //cout<<"\ntop\n";
            Enqueue(c.x-1,c.y,a);
              }
              else
              {
                  endReached=1;
                  x=1;
                    a[c.x-1][c.y]='*';
                    Dequeue(a);
                   f=1;
              }
        }
        if((c.y-1>=0) && (a[c.x][c.y-1]!='X') && (a[c.x][c.y-1]!='*') && (a[c.x][c.y-1]!='$') )
        {
            if(a[c.x][c.y-1]!='D'){
            //cout<<"\nleft\n";
            Enqueue(c.x,c.y-1,a);
            x=1;
            }
            else
            {
                endReached=1;
                x=1;
                 a[c.x][c.y-1]='*';
                 Dequeue(a);
                 f=1;

            }
        }
if( x==0 && front==rear)
{
blocked=1;
cout<<"blocked";
break;
}
else
   {
        //cout<<"\n\n";
        if(f!=1)
        Dequeue(a);
        //printMatrix(a,&c);
   }

}
if(blocked==1)
    return 0;
else if(endReached==1)
    return 1;
}

int compare(struct coords *u,char a[row][col], char user_matrix[row][col],char coords,int p,int q)
{
int f=0;
//cout<<p<<"\t"<<q;
        if(coords=='w')
        {   if(u->x-1<0 || user_matrix[u->x-1][u->y]=='X' || a[u->x-1][u->y]==' ')
                {   life=life-1;
                    score=score-5;
                    cout<<"\nyou hit a an invalid location point are deducted and now your score is : "<<score;

                }
                else if(u->x-1==p && u->y==q)
                {   //cout<<p<<"\t"<<q<<"\t"<<u->x-1<<"\t"<<u->y;
                    score=score+2;
                    cout<<"\ncongratulations you reached the destination and now your score is : "<<score;
                    f=1;
                     user_matrix[p][q]='@';

                    return f;
                }
                else if(user_matrix[u->x-1][u->y]=='@')
                {
                    cout<<"\nno change in point don't act smart! and now your score is : "<<score;
                    u->x=u->x-1;
                    user_matrix[u->x][u->y]='@';
                }

                else if(a[u->x-1][u->y]=='$')
                {   life=life-1;
                    score=score-1;
                    cout<<"\nprobably wrong path and points deducted and now your score is : "<<score;
                    u->x=u->x-1;
                    user_matrix[u->x][u->y]='@';
                }
                else if(a[u->x-1][u->y]=='*')
                {
                    score=score+2;
                    cout<<"keep going and now your score is : "<<score;
                    u->x=u->x-1;
                    user_matrix[u->x][u->y]='@';

                }

        }


                if(coords=='s')
        {
                if(u->x+1>=row || user_matrix[u->x+1][u->y]=='X' || a[u->x+1][u->y]==' ')
                {   life=life-1;
                    score=score-5;
                    cout<<"you hit a an invalid location point are deducted and now your score is : "<<score;
                }
                else if(u->x+1==p && u->y==q)
                {
                    score = score+2;
                    cout<<"congratulations you reached the destination and now your score is : "<<score;
                    f=1;
                    user_matrix[p][q]='@';
                    return f;
                }
                else if(user_matrix[u->x+1][u->y]=='@')
                {
                    cout<<"no change in points don't act smart! and now your score is : "<<score;
                    u->x=u->x+1;
                    user_matrix[u->x][u->y]='@';
                }
                else if(a[u->x+1][u->y]=='$')
                {   life=life-1;
                    score=score-1;
                    cout<<"probably wrong path and points deducted and now your score is : "<<score;
                    u->x=u->x+1;
                    user_matrix[u->x][u->y]='@';
                }

                else if(a[u->x+1][u->y]=='*')
                {
                    score = score+2;
                    cout<<"keep going and now your score is : "<<score;
                    u->x=u->x+1;
                    user_matrix[u->x][u->y]='@';

                }


        }

        if(coords=='a')
        {    if(u->y-1<0 || user_matrix[u->x][u->y-1]=='X' || a[u->x][u->y-1]==' ')
                {   life=life-1;
                    score=score-5;
                    cout<<"you hit a an invalid location point are deducted and now your score is : "<<score;

                }
            else if(u->x==p && u->y-1==q)
                {
                    score = score + 2;
                    cout<<"congratulations you reached the destination and now your score is : "<<score;
                    f=1;
                    user_matrix[p][q]='@';
                    return f;
                }

                else if(user_matrix[u->x][u->y-1]=='@')
                {
                    cout<<"no change in point don't act smart! and now your score is : "<<score;
                    u->y=u->y-1;
                    user_matrix[u->x][u->y]='@';
                }
                else if(a[u->x][u->y-1]=='$')
                {   life=life-1;
                    score = score-1;
                    cout<<"probably wrong path and points deducted and now your score is : "<<score;
                    u->y=u->y-1;
                    user_matrix[u->x][u->y]='@';
                }
                else if(a[u->x][u->y-1]=='*')
                {
                    score =score +2;
                    cout<<"keep going and now your score is : "<<score;
                    u->y=u->y-1;
                    user_matrix[u->x][u->y]='@';

                }


        }

        if(coords=='d')
        {
                if(u->y+1>=col || user_matrix[u->x][u->y+1]=='X' || a[u->x][u->y+1]==' ')
                {   life=life-1;
                    score = score-5;
                    cout<<"you hit a an invalid location point are deducted and now your score is : "<<score;
                }
                else if(u->x==p && u->y+1==q)
                {
                    score=score+2;
                    cout<<"congratulations you reached the destination and now your score is : "<<score;
                    f=1;
                     user_matrix[p][q]='@';
                    return f;
                }
                else if(user_matrix[u->x][u->y+1]=='@')
                {
                    cout<<"no change in point don't act smart! and now your score is : "<<score;
                    u->y=u->y+1;
                    user_matrix[u->x][u->y]='@';
                }
                else if(a[u->x][u->y+1]=='$')
                {   life=life-1;
                    score = score -1;
                    cout<<"probably wrong path and points deducted and now your score is : "<<score;
                    u->y=u->y+1;
                    user_matrix[u->x][u->y]='@';
                }
                else if(a[u->x][u->y+1]=='*')
                {
                    score=score+2;
                    cout<<"keep going and now your score is : "<<score;
                    u->y=u->y+1;
                    user_matrix[u->x][u->y]='@';

                }


        }
        return f;
}
movement(struct coords *user,char a[row][col],char user_matrix[row][col],int p,int q)
{
    char coords;
    cout<<"enter the coordsection you want to go: ";
    cin>>coords;
    int x=compare(user,a,user_matrix,coords,p,q);
    return x;
}
int compareQueues(struct coords *u,char a[row][col], char user_matrix[row][col],char dir)
{
int f=0;int fl=0;
//cout<<p<<"\t"<<q;
 //top=pushQueue(top,u->x,u->y);///yahan nhn aayega its inputing values again in stack that is y its skipping values yeh step sirf ek hi baar hona ch
        if(dir=='w')
        {   if(u->x-1<0 || user_matrix[u->x-1][u->y]=='X' || a[u->x-1][u->y]==' ')
                {
                    life=life-1;
                    f=0;

                        int i=0;
                        while(i<3)
                        {
                            if(top->next==NULL)
                                {
                                    fl=1;
                                    //cout<<"im in top->next==null "<<i<<endl;
                                    break;
                                }
                                //cout<<i<<endl;
                                i++;
                            top=popQueue(top,user_matrix);
                            //cout<<top->x<<" , "<< top->y<<endl;
                        }
                        //cout<<"out of the loop\n";
                        if(fl==1)
                        {
                            //cout<<"im in f==1        "<<k<<" , "<<l;
                            u->x=k;
                            u->y=l;
                        }
                        else
                        {
                            u->x=top->x;
                            u->y=top->y;
                        }

                    score=score-5;
                    cout<<"\nyou hit a an invalid location point are deducted and now your score is : "<<score;

                }
                else if(u->x-1==p && u->y==q)
                {   //cout<<p<<"\t"<<q<<"\t"<<u->x-1<<"\t"<<u->y;

                    score=score+2;
                    cout<<"\ncongratulations you reached the destination and now your score is : "<<score;
                    f=1;
                     user_matrix[p][q]='@';

                    return f;
                }
                else if(user_matrix[u->x-1][u->y]=='@')
                {
                    cout<<"\nno change in point don't act smart! and now your score is : "<<score;
                    u->x=u->x-1;
                    top=pushQueue(top,u->x,u->y);
                    user_matrix[u->x][u->y]='@';
                }

                else if(a[u->x-1][u->y]=='$')
                {
                    life=life-1;
                    score=score-1;
                    cout<<"\nprobably wrong path and points deducted and now your score is : "<<score;
                    u->x=u->x-1;
                    top=pushQueue(top,u->x,u->y);
                    user_matrix[u->x][u->y]='@';
                }
                else if(a[u->x-1][u->y]=='*')
                {
                    score=score+2;
                    cout<<"keep going and now your score is : "<<score;
                    u->x=u->x-1;
                    top=pushQueue(top,u->x,u->y);
                    user_matrix[u->x][u->y]='@';

                }

        }


                if(dir=='s')
        {
                if(u->x+1>=row || user_matrix[u->x+1][u->y]=='X' || a[u->x+1][u->y]==' ')
                {
                    life=life-1;
                    fl=0;

                        int i=0;
                        while(i<3)
                        {
                            if(top==NULL)
                                {
                                    fl=1;
                                    //cout<<i<<endl;
                                    break;
                                }
                                //cout<<i<<endl;
                                i++;
                            top=popQueue(top,user_matrix);
                            //cout<<top->x<<" , "<< top->y<<endl;
                        }
                        //cout<<"out of the loop\n";
                        if(fl==1)
                        {
                            u->x=k;
                            u->y=l;
                            user_matrix[u->x][u->y]='@';
                        }
                        else
                        {
                            u->x=top->x;
                            u->y=top->y;
                        }

                    score=score-5;
                    cout<<"you hit a an invalid location point are deducted and now your score is : "<<score;
                }
                else if(u->x+1==p && u->y==q)
                {
                    score = score+2;
                    cout<<"congratulations you reached the destination and now your score is : "<<score;
                    f=1;
                    user_matrix[p][q]='@';
                    return f;
                }
                else if(user_matrix[u->x+1][u->y]=='@')
                {
                    cout<<"no change in points don't act smart! and now your score is : "<<score;
                    u->x=u->x+1;
                    top=pushQueue(top,u->x,u->y);
                    user_matrix[u->x][u->y]='@';
                }
                else if(a[u->x+1][u->y]=='$')
                {
                    life=life-1;
                    score=score-1;
                    cout<<"probably wrong path and points deducted and now your score is : "<<score;
                    u->x=u->x+1;
                    top=pushQueue(top,u->x,u->y);
                    user_matrix[u->x][u->y]='@';
                }

                else if(a[u->x+1][u->y]=='*')
                {
                    score = score+2;
                    cout<<"keep going and now your score is : "<<score;
                    u->x=u->x+1;
                    top=pushQueue(top,u->x,u->y);
                    user_matrix[u->x][u->y]='@';

                }


        }

        if(dir=='a')
        {    if(u->y-1<0 || user_matrix[u->x][u->y-1]=='X' || a[u->x][u->y-1]==' ')
                {
                    life=life-1;
                    fl=0;

                        int i=0;
                        while(i<3)
                        {

                            if(top==NULL)
                                {
                                    fl=1;
                                    //cout<<"im in top==null"<<i<<endl;
                                    break;
                                }
                                //cout<<"im in normal i "<<i<<endl;
                                i++;
                            top=popQueue(top,user_matrix);
                            //cout<<top->x<<" , "<< top->y<<endl;
                        }
                        cout<<"out of the loop\n";
                        if(fl==1)
                        {
                            //cout<<"im in f==1\n";
                            //cout<<k<<" , "<<l<<endl;
                            u->x=k;
                            u->y=l;
                        }
                        else
                        {
                            //cout<<"im in else\n";
                            u->x=top->x;
                            u->y=top->y;
                        }

                    score=score-5;
                    cout<<"you hit a an invalid location point are deducted and now your score is : "<<score;

                }
            else if(u->x==p && u->y-1==q)
                {
                    score = score + 2;
                    cout<<"congratulations you reached the destination and now your score is : "<<score;
                    f=1;
                    user_matrix[p][q]='@';
                    return f;
                }

                else if(user_matrix[u->x][u->y-1]=='@')
                {
                    cout<<"no change in point don't act smart! and now your score is : "<<score;
                    u->y=u->y-1;
                    top=pushQueue(top,u->x,u->y);
                    user_matrix[u->x][u->y]='@';
                }
                else if(a[u->x][u->y-1]=='$')
                {
                    life=life-1;
                    score = score-1;
                    cout<<"probably wrong path and points deducted and now your score is : "<<score;
                    u->y=u->y-1;
                    top=pushQueue(top,u->x,u->y);
                    user_matrix[u->x][u->y]='@';
                }
                else if(a[u->x][u->y-1]=='*')
                {
                    score =score +2;
                    cout<<"keep going and now your score is : "<<score;
                    u->y=u->y-1;
                    top=pushQueue(top,u->x,u->y);
                    user_matrix[u->x][u->y]='@';

                }


        }

        if(dir=='d')
        {
                if(u->y+1>=col || user_matrix[u->x][u->y+1]=='X' || a[u->x][u->y+1]==' ')
                {
                    life=life-1;
                    fl=0;

                        int i=0;
                        while(i<3)
                        {
                            if(top==NULL)
                                {
                                    fl=1;
                                    //cout<<i<<endl;
                                    break;
                                }
                            //    cout<<i<<endl;
                                i++;
                            top=popQueue(top,user_matrix);
                            //cout<<top->x<<" , "<< top->y<<endl;
                        }
                        //cout<<"out of the loop\n";
                        if(fl==1)
                        {
                            u->x=k;
                            u->y=l;
                        }
                        else
                        {
                            u->x=top->x;
                            u->y=top->y;
                        }

                    score = score-5;
                    cout<<"you hit a an invalid location point are deducted and now your score is : "<<score;
                }
                else if(u->x==p && u->y+1==q)
                {
                    score=score+2;
                    cout<<"congratulations you reached the destination and now your score is : "<<score;
                    f=1;
                     user_matrix[p][q]='@';
                    return f;
                }
                else if(user_matrix[u->x][u->y+1]=='@')
                {
                    cout<<"no change in point don't act smart! and now your score is : "<<score;
                    u->y=u->y+1;
                    top=pushQueue(top,u->x,u->y);
                    user_matrix[u->x][u->y]='@';
                }
                else if(a[u->x][u->y+1]=='$')
                {
                    life=life-1;
                    score = score -1;
                    cout<<"probably wrong path and points deducted and now your score is : "<<score;
                    u->y=u->y+1;
                    top=pushQueue(top,u->x,u->y);
                    user_matrix[u->x][u->y]='@';
                }
                else if(a[u->x][u->y+1]=='*')
                {
                    score=score+2;
                    cout<<"keep going and now your score is : "<<score;
                    u->y=u->y+1;
                    top=pushQueue(top,u->x,u->y);
                    user_matrix[u->x][u->y]='@';

                }


        }
        return f;
}
movementQueues(struct coords *user,char a[row][col],char user_matrix[row][col])
{
    char dir;
    cout<<"enter the direction you want to go: ";
    cin>>dir;
    int x=compareQueues(user,a,user_matrix,dir);
    return x;
}
void queueImplementation(struct coords c,char a[row][col],char user_matrix[row][col],int p,int q)
{
        int is_Maze_Valid=mazeWithQueues(c,a);
         top=pushQueue(top,c.x,c.y);
    if(is_Maze_Valid)
    {
        ///user input system

        setMatrix(user_matrix,p,q,c.x,c.y);
        user_matrix[c.x][c.y]='@';
        printMatrix(user_matrix);
        struct coords user;
        user.x=c.x;
        user.y=c.y;
        printMatrix(a);
        cout<<endl;
        int pqr;
        while(pqr!=1 && life>0)
        {
         pqr=movementQueues(&user,a,user_matrix);
         system("cls");
         printMatrix(user_matrix);
        }
        if(life==0)
            cout<<"\nu lost game over!";
        //printMatrix(a,c);

        //printMatrix(a,c);
        cout<<endl;

  }
}
int mazewithstacks(struct coords c,char a[row][col],struct node *top)
{   int f=0;
int k=1;
    while(1)
        {
            int x=0;
            c.x=top->x;
            c.y=top->y;
            top=pop(top,a);
            if( a[c.x][c.y+1]!='X' && c.y+1<col && f!=1 && a[c.x][c.y+1]!='*' && a[c.x][c.y+1]!='$')
            {
                if(a[c.x][c.y+1]!='D')
                {
                    x=1;
                    //cout<<"\nneighbour is to the right\n";
                    top=push(top,c.x,c.y+1,a);
                }
                else
            {
                x=1;
                a[c.x][c.y+1]='*';
                f=1;
                //printMatrix(a);
                break;
            }

            }

            if ( a[c.x][c.y-1]!='X' && c.y-1>=0 && f!=1 && a[c.x][c.y-1]!='*' && a[c.x][c.y-1]!='$')
            {
                      if(a[c.x][c.y-1]!='D')
                {
                    x=1;
                    //cout<<"\nneighbour is to the left\n";
                    //printf("x: %d \ty: %d\n",x,y);
                    top=push(top,c.x,c.y-1,a);
                }
                else
            {
                x=1;
                a[c.x][c.y-1]='*';
                f=1;
                //printMatrix(a);
                break;
            }

            }

            if ( (a[c.x-1][c.y]!='X' && c.x-1>=0 && f!=1 && a[c.x-1][c.y]!='*' )|| a[c.x-1][c.y]=='$')
            {
                  if(a[c.x-1][c.y]!='D')
                {
                    x=1;
                    //cout<<"\nneighbour is to the top\n";
                    top=push(top,c.x-1,c.y,a);
                }
            else
            {
                x=1;
                a[c.x-1][c.y]='*';
                f=1;
                //printMatrix(a);
                break;
            }

            }

            if ( a[c.x+1][c.y]!='X'  && c.x+1<row && f!=1 && a[c.x+1][c.y]!='*' && a[c.x+1][c.y]!='$')
            {
                  if(a[c.x+1][c.y]!='D')
                {
                    x=1;
                    //cout<<"\nneighbour is to down\n";
                    top=push(top,c.x+1,c.y,a);
            }
            else
            {
                x=1;
                a[c.x+1][c.y]='*';
                f=1;
                //printMatrix(a);
                break;
            }
            }

            if(x==0 && top==NULL)
         {
             cout<<"blocked";
             k=0;
             break;
        }
            //printMatrix(a);
            //cout<<endl;

}
if(k==0)
    return k;
else
    return 1;
}
void stackImplementation(struct coords c,char a[row][col],char user_matrix[row][col],struct node *top,int p,int q)
{
    int is_valid_maze=mazewithstacks(c,a,top);
    //cout<<endl<<is_valid_maze<<endl;
    if(is_valid_maze)
    {
        setMatrix(user_matrix,p,q,c.x,c.y);
        user_matrix[c.x][c.y]='@';
        printMatrix(user_matrix);
        cout<<endl;
        struct coords user;
        user.x=c.x;
        user.y=c.y;
        printMatrix(a);
        int pqr;
        //cout<<p<<"\t"<<q;
        while(pqr!=1 && life>0)
        {
         pqr=movement(&user,a,user_matrix,p,q);
         printMatrix(user_matrix);
         cout<<endl;

        }
        if(life==0)
            cout<<"game over";
        cout<<endl;
        //printMatrix(a,c);
        cout<<endl;

    }
}

int main()
{
    cout<<"\t\t\tWELCOME TO THE MAZE GAME\n";
    cout<<"YOU WILL BE INTRODUCED WITH TWO LEVELS ONE WHERE THE PATH WILL BE A DEFINITIVE ONE \nAND THE OTHER WHERE U WILL HAVE TO CHOOSE A MORE EFFICIENT AND OPTIMISED PATH\n";
    cout<<"\n\n............Press any key to continue..........\n";
    getch();
    //+cout<<"which way you "
    struct maze *head=NULL;
    struct node *top=NULL;
    //struct maze *t=NULL;
    struct coords c;
    char a[row][col];
    int level;
    cout<<"enter 1 for definite path and 2 for shortest path";
    cin>>level;
    cout<<"Enter the coordinates of the origin in x, y form: ";
    cin>>c.x>>c.y;
     a[c.x][c.y]='S';
     //top=pushQueue(top,c.x,c.y);
  cout<<"Enter the destination : ";
  cin>>p>>q;
  a[p][q]='D';
  char user_matrix[row][col];
  if(level==1){
    setMatrix(a,p,q,c.x,c.y);
    Enqueue(c.x,c.y,a);
    ////printMatrix(a,&c);
    queueImplementation(c,a,user_matrix,p,q);
}
else{
    setMatrix(a,p,q,c.x,c.y);///finalizes the position and sets everything in place
        top=push(top,c.x,c.y,a);
        stackImplementation(c,a,user_matrix,top,p,q);
}

return 0;
}
