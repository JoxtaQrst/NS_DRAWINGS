#include <iostream>
#include <graphics.h>
#include <winbgim.h>
#include <math.h>
using namespace std;

int DIMX=150,DIMY=50,SPL=30,CT1=DIMX/2,CT2=DIMY/2;

// DIMX= Latimea initiala a blocurilor
// DIMY= Lungimea initiala a blocurilor
// SPL=  Padding-ul dintre loop si blocuri
// CT1=  Impartire triunghi coord x
// CT2=  Impartire triunghi coord y

struct area{
            int x,y,xx,yy;}S[50]; //creem o arie pt a determina unde am dat click cu mouse-ul
int nrb=1;
void createarea(int x,int y,int xx,int yy)
{
    S[nrb].x=x;
    S[nrb].y=y;
    S[nrb].xx=xx;
    S[nrb].yy=yy;
    nrb++;
}

void ProcessBlock(int x,int y,int X,int Y)
{
    setlinestyle(0,2,3);
    line(x,y,x+X,y);
    line(x,y,x,y+Y);
    line(x+X,y,x+X,y+Y);
    line(x,y+Y,x+DIMX,y+Y);

    createarea(x,y,X,Y);
    //floodfill(x,y,WHITE);
}

void Normal_Loop(int x,int y,int conditions,int &L,int X,int Y,int S)
{
    int c1_x,c1_y,c2_x,c2_y;
    setlinestyle(0,2,3);
    c1_x=x+S;     c1_y=y+Y;
    c2_x=x+X;     c2_y=y+Y;
    L=y+(50*(1+conditions));
    //desenam
    line(x,y,x+X,y);
    line(x+X,y,x+X,y+Y);
    line(x+S,y+Y,x+X,y+Y);
    line(x,y,x,L);
    line(x+S,y+Y,x+S,L);
    line(x,L,x+S,L);
    //desenam conditiile
    for(int i=1;i<=conditions;i++)
    {
        line(c2_x,c2_y,c2_x,c2_y+Y);
        line(c2_x,c2_y+Y,c1_x,c1_y+Y);

        //CONDITIONS NAME
        c1_y+=Y;   c2_y+=Y;
    }
    //floodfill(x,y,WHITE);
    createarea(x,y,x+X,y+Y);
}
void Reverse_Loop(int x,int y,int conditions,int &L,int X,int Y,int S)
{
    int c1_x,c1_y,c2_x,c2_y;
    c1_x=x+S;     c1_y=y;
    c2_x=x+X;     c2_y=y;
    L=y+(50*(1+conditions));
    setlinestyle(0,2,3);
    //desneam conditiile
    for(int i=1;i<=conditions;i++)
    {
        line(c1_x,c1_y,c2_x,c2_y);
        line(c2_x,c2_y,c2_x,c2_y+Y);
        //CONDITIONS NAME
        c1_y+=Y;   c2_y+=Y;

    }
    //desenam
    line(c1_x,c1_y,c2_x,c2_y);
    line(x,y,x,L);
    line(x,L,x+X,L);
    line(x+X,L,x+X,L);
    line(x+X,L,x+X,L-Y);
    line(x,y,x+S,y);
    line(x+S,L-Y,x+S,y);
    //floodfill(x,y,WHITE);
    createarea(x,y,x+X,y+Y);
}

void True_Triangle(int x,int y,int Ax,int Ay,int X,int Y,int C1,int C2)
{
    int Mx,My;
    setlinestyle(0,2,3);
    line(x,y,x,y+Y);
    line(x,y+Y,x+C1,y+Y);
    line(x,y,x+C1,y+Y);
    Mx= Ax+C2;  My=Ay+C2;

}
void False_Triangle(int x,int y,int Bx,int By,int X,int Y,int C1,int C2)
{
    int Mx,My;
    setlinestyle(0,2,3);
    line(x+X,y,x+X,y+Y);
    line(x+X,y+Y,x+C1,y+Y);
    line(x+C1,y+Y,x+X,y);
    Mx= Bx-(C2*2);  My=By+C2;


}

void BranchingBlock(int x,int y,int X,int Y,int C1,int C2)
{
    int Ax,Ay,Bx,By;
    Ax=x;        Ay=y;
    Bx=x+X;   By=y;
    setlinestyle(0,2,3);
    line(x,y,x+X,y);
    True_Triangle(x,y,Ax,Ay,X,Y,C1,C2);
    False_Triangle(x,y,Bx,By,X,Y,C1,C2);
    createarea(x,y,x+X,y+Y);
}

// blocks for Legend
void ProcessBlockL(int x,int y)
{
    setlinestyle(0,2,3);
    rectangle(x-CT1,y-CT2,x+CT1,y+CT2);
    //floodfill(x,y,WHITE);
}

void Normal_LoopL(int x,int y,int conditions,int &L)
{
    int c1_x,c1_y,c2_x,c2_y;
    setlinestyle(0,2,3);
    c1_x=x+SPL;       c1_y=y+DIMY;
    c2_x=x+DIMX;     c2_y=y+DIMY;
    L=y+(50*(1+conditions));
    line(x,y,x+DIMX,y);
    line(x+DIMX,y,x+DIMX,y+DIMY);
    line(x+SPL,y+DIMY,x+DIMX,y+DIMY);
    line(x,y,x,L);
    line(x+SPL,y+DIMY,x+SPL,L);
    line(x,L,x+SPL,L);

    for(int i=1;i<=conditions;i++)
    {
        line(c2_x,c2_y,c2_x,c2_y+DIMY);
        line(c2_x,c2_y+DIMY,c1_x,c1_y+DIMY);

        //CONDITIONS NAME
        c1_y+=DIMY;   c2_y+=DIMY;
    }
    //floodfill(x,y,WHITE);
}
void Reverse_LoopL(int x,int y,int conditions,int &L)
{
    int c1_x,c1_y,c2_x,c2_y;
    c1_x=x+SPL;       c1_y=y;
    c2_x=x+DIMX;     c2_y=y;
    L=y+(50*(1+conditions));
    setlinestyle(0,2,3);
    for(int i=1;i<=conditions;i++)
    {
        line(c1_x,c1_y,c2_x,c2_y);
        line(c2_x,c2_y,c2_x,c2_y+DIMY);
        //CONDITIONS NAME
        c1_y+=DIMY;   c2_y+=DIMY;

    }
    line(c1_x,c1_y,c2_x,c2_y);
    line(x,y,x,L);
    line(x,L,x+DIMX,L);
    line(x+DIMX,L,x+DIMX,L);
    line(x+DIMX,L,x+DIMX,L-DIMY);
    line(x,y,x+SPL,y);
    line(x+SPL,L-DIMY,x+SPL,y);
    //floodfill(x,y,WHITE);
}
void True_TriangleL(int x,int y,int Ax,int Ay)
{
    char text[]={"DA"};
    int lat,lun,Mx,My;
    setlinestyle(0,2,3);
    line(x,y,x,y+DIMY);
    line(x,y+DIMY,x+CT1,y+DIMY);
    line(x,y,x+CT1,y+DIMY);
    Mx= Ax+CT2;  My=Ay+CT2;
    settextstyle(4,0,1);
    outtextxy(Mx,My,text);
    //print "DA" in middle of the triangle

}
void False_TriangleL(int x,int y,int Bx,int By)
{
    char text[]={"NU"};
    int lat,lun,Mx,My;
    lat=textwidth(text);
    lun=textheight(text);
    setlinestyle(0,2,3);
    line(x+DIMX,y,x+DIMX,y+DIMY);
    line(x+DIMX,y+DIMY,x+CT1,y+DIMY);
    line(x+CT1,y+DIMY,x+DIMX,y);
    Mx= Bx-(CT2*2);  My=By+CT2;
    settextstyle(4,0,1);
    outtextxy(Mx,My,text);
    //print "NU" in middle of the triangle

}

void BranchingBlockL(int x,int y)
{
    //int Lg=textwidth(text);
    //int Lt=textheight(text);
    int Ax,Ay,Bx,By;
    Ax=x;        Ay=y;
    Bx=x+DIMX;   By=y;
    setlinestyle(0,2,3);
    line(x,y,x+DIMX,y);
    True_TriangleL(x,y,Ax,Ay);
    False_TriangleL(x,y,Bx,By);
    //floodfill(x,y,WHITE);
    //outtextxy();
}


//main menu
int windowx=1300,windowy=850;
void menu()
{
    settextstyle(4,0,4);
    setbkcolor(WHITE);
    setcolor(BLACK);

    outtextxy(windowx/4,25,"Nassi-Schneiderman Diagram");

    setlinestyle(1,1,2);
    line(0,60,windowx,60);

    line(windowx-550,65,windowx-550,windowy);
    line(windowx-550,windowy-280,windowx,windowy-280);
    //area where the node info should be shown is [windowx-550,windowy-280,windowx,windowy-280]
}

void legenda(int L)
{
    int bordx=windowx-250,bordy=150;

    settextstyle(4,0,4);
    outtextxy(bordx-20,bordy-50,"Legenda");

    settextstyle(4,0,3);
    outtextxy(bordx-250,bordy+20,"Process Block");
    ProcessBlockL(bordx+75,bordy+25);
    bordy+=DIMY;

    outtextxy(bordx-100,bordy+50,"Loop");
    Normal_LoopL(bordx,bordy,2,L);
    bordy*=2;

    outtextxy(bordx-180,bordy,"Reverse L");
    Reverse_LoopL(bordx,bordy-50,2,L);
    bordy+=(DIMY*2);

    outtextxy(bordx-190,bordy+20,"If Statment");
    BranchingBlockL(bordx,bordy);

    settextstyle(4,0,4);
    bordy+=100;
    outtextxy(bordx-100,bordy,"Made by");
    outtextxy(bordx-150,bordy+50,"Tudor Tescu");
    outtextxy(bordx-45,bordy+100,"&");
    outtextxy(bordx-150,bordy+150,"Fabian Pintea");
}
//searching and displaying on another text the code
/*
int searchA(int x,int y)
{
    int i,ok=0;
    for(i=1;i<=50;i++)
    {
        //S[nrb].x,y,xx,yy;
        if((S[i].x<x&&S[i].y<y)&&(S[i].xx>x&&S[i].yy>y))
           {
             ok=1;
             break;
           }
    }
    if(ok==1)
    {
        initwindow(300,300);
        floodfill(0,0,WHITE);
        outtext("TEST");
    }
}

// showarea
void showarea()
{
    int i;
    for(i=1;i<=50;i++)
    {
        cout<<"x="<<S[i].x<<" ";
        cout<<"y="<<S[i].y<<endl;
        cout<<"xx="<<S[i].xx<<" ";
        cout<<"yy="<<S[i].yy<<endl;
        cout<<endl;
    }
}

void click(int x,int y)
{
     searchA(x,y);

}

*/
int main()
{

    initwindow(windowx,windowy);
    floodfill(0,0,WHITE);
    int startpx=100,startpy=100,L=0;
    //declare dimensiuni initiale
    int X=DIMX,Y=DIMY,C1=CT1,C2=CT2,S=SPL;
    menu();
    legenda(L);
    /*
    if(ismouseclick(WM_LBUTTONDBLCLK))
    {
        getmouseclick(WM_LBUTTONDBLCLK, x, y);
        cout<<"Mouse clicked at"<<endl;
        cout<<"x="<<x<<" "<<"y="<<y;
        //click(x,y);
        //showarea();
    }
    */

    /*
    Testing purposes
    ProcessBlock(startpx+75,startpy+25);
    startpy+=DIMY;
    Normal_Loop(startpx,startpy,2,L);
    startpy*=2;
    ProcessBlock(startpx+75,startpy+25);
    startpy+=DIMY;
    ProcessBlock(startpx+75,startpy+25);
    startpy+=DIMY;
    Reverse_Loop(startpx,startpy,2,L);*/


    //Individual display

    ProcessBlock(startpx,startpy,X,Y);
    //Normal_Loop(startpx,startpy,2,L,X,Y,S);
    //Reverse_Loop(startpx,startpy,2,L,X,Y,S);
    //BranchingBlock(startpx,startpy,X,Y,C1,C2);


    //search in file
    //simple,if,else,while,for,etc.
    //while reading code->display blocks
    //if ( for in for ) modify X and Y ( S AND C1,C2 if necesarry), startpx,startpy
    //else return to X=DIMX,Y=DIMY,S=SPL,C1=CT1,C2=CT2
    getch();
    closegraph();
    return 0;
}
