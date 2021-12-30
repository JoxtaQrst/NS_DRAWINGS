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

void ProcessBlock(int x,int y)
{
    setlinestyle(0,2,3);
    rectangle(x-CT1,y-CT2,x+CT1,y+CT2);
    createarea(x-CT1,y-CT2,x+CT1,y+CT2);
    //floodfill(x,y,WHITE);
}

void Normal_Loop(int x,int y,int conditions,int &L)
{
    int c1_x,c1_y,c2_x,c2_y;
    setlinestyle(0,2,3);
    c1_x=x+SPL;       c1_y=y+DIMY;
    c2_x=x+DIMX;     c2_y=y+DIMY;
    L=y+(50*(1+conditions));
    //desenam
    line(x,y,x+DIMX,y);
    line(x+DIMX,y,x+DIMX,y+DIMY);
    line(x+SPL,y+DIMY,x+DIMX,y+DIMY);
    line(x,y,x,L);
    line(x+SPL,y+DIMY,x+SPL,L);
    line(x,L,x+SPL,L);
    //desenam conditiile
    for(int i=1;i<=conditions;i++)
    {
        line(c2_x,c2_y,c2_x,c2_y+DIMY);
        line(c2_x,c2_y+DIMY,c1_x,c1_y+DIMY);

        //CONDITIONS NAME
        c1_y+=DIMY;   c2_y+=DIMY;
    }
    //floodfill(x,y,WHITE);
    createarea(x,y,x+DIMX,y+DIMY);
}
void Reverse_Loop(int x,int y,int conditions,int &L)
{
    int c1_x,c1_y,c2_x,c2_y;
    c1_x=x+SPL;       c1_y=y;
    c2_x=x+DIMX;     c2_y=y;
    L=y+(50*(1+conditions));
    setlinestyle(0,2,3);
    //desneam conditiile
    for(int i=1;i<=conditions;i++)
    {
        line(c1_x,c1_y,c2_x,c2_y);
        line(c2_x,c2_y,c2_x,c2_y+DIMY);
        //CONDITIONS NAME
        c1_y+=DIMY;   c2_y+=DIMY;

    }
    //desenam
    line(c1_x,c1_y,c2_x,c2_y);
    line(x,y,x,L);
    line(x,L,x+DIMX,L);
    line(x+DIMX,L,x+DIMX,L);
    line(x+DIMX,L,x+DIMX,L-DIMY);
    line(x,y,x+SPL,y);
    line(x+SPL,L-DIMY,x+SPL,y);
    //floodfill(x,y,WHITE);
    createarea(x,y,x+DIMX,y+DIMY);
}

void True_Triangle(int x,int y,int Ax,int Ay)
{
    int Mx,My;
    setlinestyle(0,2,3);
    line(x,y,x,y+DIMY);
    line(x,y+DIMY,x+CT1,y+DIMY);
    line(x,y,x+CT1,y+DIMY);
    Mx= Ax+CT2;  My=Ay+CT2;

}
void False_Triangle(int x,int y,int Bx,int By)
{
    int Mx,My;
    setlinestyle(0,2,3);
    line(x+DIMX,y,x+DIMX,y+DIMY);
    line(x+DIMX,y+DIMY,x+CT1,y+DIMY);
    line(x+CT1,y+DIMY,x+DIMX,y);
    Mx= Bx-(CT2*2);  My=By+CT2;


}

void BranchingBlock(int x,int y)
{
    int Ax,Ay,Bx,By;
    Ax=x;        Ay=y;
    Bx=x+DIMX;   By=y;
    setlinestyle(0,2,3);
    line(x,y,x+DIMX,y);
    True_Triangle(x,y,Ax,Ay);
    False_Triangle(x,y,Bx,By);
    createarea(x,y,x+DIMX,y+DIMY);
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


//main program
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
    ProcessBlock(bordx+75,bordy+25);
    bordy+=DIMY;

    outtextxy(bordx-100,bordy+50,"Loop");
    Normal_Loop(bordx,bordy,2,L);
    bordy*=2;

    outtextxy(bordx-180,bordy,"Reverse L");
    Reverse_Loop(bordx,bordy-50,2,L);
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
    int startpx=100,startpy=100,L=0,x,y;
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

    ProcessBlock(startpx+75,startpy+25);
    //Normal_Loop(startpx,startpy,2,L);
    //Reverse_Loop(startpx,startpy,2,L);
    //BranchingBlock(startpx,startpy);


    //search in file
    //simple,if,else,while,for,etc.
    getch();
    closegraph();
    return 0;
}
