#include <graphics.h>
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <cstring>
#include <cmath>

using namespace std;

int n=0, m=0;

void redrawG();

float I[100][100], v[100][100], g[100][100], r[100][100];

//g - adiac graf, r, v - adiac rezist, tensiune (pe ramuri)

int a[100][100], A[100], finOK =0;

//a - adiac arbore, A - lista elem arbore

void setgraph()
{

    int font = 10;

    int direction = 0;

    int font_size = 2;
    settextstyle(font, direction, font_size);
    setcolor(WHITE);
    setfillstyle(LTSLASH_FILL, LIGHTMAGENTA);
    setbkcolor(MAGENTA);

}

struct matrici
{
    int DB[100][100]= {};
} V[100], TV[100];





void creare_arbore()
{
    A[0]=1;

    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
        {
            if(g[i][j]==1 && A[i]==1 && !A[j])
                a[i][j] = a[j][i] = A[j] = 1;

            if(g[i][j]==1 && A[i]==0 && A[j]==1)
                a[i][j] = a[j][i] = A[i] = 1;
        }


/*

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
            cout << a[i][j] << " ";
        cout << endl;
    }
    cout << endl;
    */

}

int nrC=0, b[100][100], c[100][100];


// nrC - nr cicluri, b - adiac arbore + muchie separata, c - adiac grafic-arbore (co-arbore)
struct circ
{
    int K=0, e[100];
} q[100];





int X[50],p[50];

void atrib(int n, int p)
{
 /*   for(int i=0; i<n; i++)
        cout << X[i]+1;
    cout << endl;
    */

    for(int i=0; i<n; i++)
        q[p].e[i]=X[i];


    q[p].K = n;
}

void back(int k, int pas, int P)
{
    for(int i=0; i<n; i++)
        if(!p[i] && b[X[pas-1]][i])
        {
            X[pas]=i;
            p[i]=1;
            if(X[pas]==k && pas>2) atrib(pas+1, P);
            else back(k, pas+1, P);
            p[i]=0;
        }
}


void initBV(int v[], int k)
{
    for(int i=0; i<n; i++)
    {
        v[i]=0;
        for(int j=0; j<n; j++)
        {
            b[i][j]=a[i][j];
        }
        for(int i=0; i<q[k].K-1; i++)
            V[k].DB[q[k].e[i]][q[k].e[i+1]] =  V[k].DB[q[k].e[i+1]][q[k].e[i]] = 1;

    }
}

void creare_cicluri()
{
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
        {
            c[i][j]=g[i][j]-a[i][j];
            b[i][j]=a[i][j];
        }

    int k = 0, v[100]= {0},ok = 1;
    for(int i=0; i<n-1; i++)
        for(int j=i+1; j<n; j++)
            if(c[i][j])
            {

                b[i][j]=b[j][i]=1;
                X[0]=j;

                back(j, 1, k);

                initBV(v, k);

                k++;


            }
    nrC = k;

    /*
  for(int i=0; i<nrC; i++)
    {
        for(int j=0; j<q[i].K; j++)
            cout <<  q[i].e[j] +1 << " u";
        cout << endl;
    }

*/

}




void directieCicluri()
{
    for(int i=0; i<nrC; i++)
    {
        for(int j=0; j<q[i].K; j++)
        {
            if(V[i].DB[q[i].e[j+1]][q[i].e[j]]>0)
                V[i].DB[q[i].e[j]][q[i].e[j+1]]=-V[i].DB[q[i].e[j+1]][q[i].e[j]];
            else  V[i].DB[q[i].e[j]][q[i].e[j+1]]=-V[i].DB[q[i].e[j+1]][q[i].e[j]];
        }
    }
    /*
        for(int i=0; i<nrC; i++)
        {
            cout << i <<": " << endl;
            for(int k=0; k<n; k++)
            {
                for(int e=0; e<n; e++)
                 cout << V[i].DB[k][e] << " ";
              cout << endl;
            }
        }
    */


}

float C[100][100]= {};

void constr_matr()
{
    for(int i=0; i<nrC; i++)
    {

        for(int j=0; j<n; j++)
            for(int k=0; k<n; k++)
            {

                if(V[i].DB[j][k]>0 && r[j][k])
                {
                    C[i][i]+=r[j][k];
                    for(int q=0; q<nrC; q++)
                        if(q!=i)
                        {
                            if(V[q].DB[j][k]>0)
                                C[i][q] +=r[j][k];
                            else if(V[q].DB[j][k]<0)
                                C[i][q] -=r[j][k];
                        }
                }
            }
        for(int j=0; j<n; j++)
            for(int k=0; k<n; k++)
            {
                if(V[i].DB[j][k]>0 && v[j][k])
                {
                    C[i][nrC]+=v[j][k];
                    /*   for(int q=0; q<nrC; q++)
                           if(q!=i)
                           {
                               if(V[q].DB[j][k]>0)
                                   C[i][nrC] +=v[j][k];
                               else if(V[q].DB[j][k]<0)
                                   C[i][nrC] -=v[j][k];
                           }
                           */

                }
            }
    }
/*
    for(int i=0; i<nrC; i++)
    {
        for(int j=0; j<=nrC; j++)
            cout << C[i][j] << " ";
        cout << endl;
    }
    cout << endl;
*/

}
float x[100], ratio;

char If[1000];

float Xi[]= {0.0094416, 0.2096333, 0.04831, 0.029109};
void calcIntensit()
{
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
        {
            for(int k=0; k<nrC; k++)
            {
                if(V[k].DB[i][j] && r[i][j])
                    I[i][j]+=x[k]*V[k].DB[i][j];
            }
        }

    for(int i=0; i<n; i++)
    {
        for(int j=i+1; j<n; j++)
          if(I[i][j])
           {     cout << i+1 << " " << j+1 <<" I: " << I[i][j]*1000 << " mA" << endl;
             redrawG();
            //  cleardevice();
             char nr1[10]; itoa(i+1, nr1, 10);
          //  outtext(nr1);

            char nr2[10]; itoa(j+1, nr2, 10);

            char valVIS[10]; itoa(I[i][j]*1000, valVIS, 10);

            outtextxy(30, 120, "I ");
            strcat(If, "I ");
            outtextxy(50, 120, nr1);
            strcat(If, nr1);
            outtextxy(70, 120, nr2);
            strcat(If, nr2);
            outtextxy(80, 120, " : ");
            strcat(If, " : ");
            moveto(100, 120);
            outtext(valVIS);
            strcat(If, valVIS);
            outtextxy(150, 120, " mA ");
            strcat(If, " mA ; ");
             delay(1000);
        //     cleardevice();

           }
        cout << endl;
    }
    cout << endl;

}
float Vi[100][100];
char Vf[1000];
void tensiune()
{

    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            if(r[i][j]) Vi[i][j] = r[i][j]*I[i][j];

    for(int i=0; i<n; i++)
    {
        for(int j=i+1; j<n; j++)
            if(r[i][j])
            {

            //  cleardevice();
                cout << i+1 << " " << j+1 <<" V: " << Vi[i][j] << " V" << endl;
              redrawG();

            char nr1[10]; itoa(i+1, nr1, 10);
          //  outtext(nr1);

            char nr2[10]; itoa(j+1, nr2, 10);

            char valVIS[10]; itoa((ceil)(Vi[i][j]), valVIS, 10);

           // outtext(nr2);

            outtextxy(30, 120, "V ");
            strcat(Vf, "V ");
            outtextxy(50, 120, nr1);
            strcat(Vf, nr2);
            outtextxy(70, 120, nr2);
            strcat(Vf, nr1);
            outtextxy(80, 120, ": ");
            strcat(Vf, ": ");
            moveto(100, 120);
            outtext(valVIS);
            strcat(Vf, valVIS);
            outtextxy(150, 120, " V ");
            strcat(Vf, " V ; ");
             delay(1000);

            // cleardevice();
            }
        cout << endl;
    }
    finOK = 1;
    cout << endl;
}


void gaussSol()
{

    float t;

    for(int j=0; j<nrC; j++)
    {
        for(int i=0; i<nrC; i++)
        {
            if(i!=j)
            {
                t=C[i][j]/C[j][j];
                for(int k=0; k<nrC+1; k++)
                {
                    C[i][k]=C[i][k]-t*C[j][k];
                }
            }
        }
    }

    for(int i=0; i<nrC; i++)
    {
        x[i]=C[i][nrC]/C[i][i];
      //  cout<<"x"<<i << "="<<x[i]<<" ";
    }

}



void initAlg()
{
    creare_arbore();
    creare_cicluri();
    directieCicluri();
    constr_matr();
    gaussSol();
    calcIntensit();
    tensiune();

}


void dCr(int on)
{
    int crX,oldClr;
    char uBarStr[2] = { '_',0 };
    if (!on)
    {
        oldClr=getcolor();
        setcolor(getbkcolor());
    }
    crX=getx();
    outtext(uBarStr);
    moveto(crX,gety());
    if (!on) setcolor(oldClr);
}

void getGrSir(char *inSir)
{
    int sirIx=0;
    int xVal[255];
    char inChr, outSir[2];
    int oldClr;
    outSir[1]=0;
    xVal[0]=getx();
    do
    {
        dCr(1);
        inChr=getch();
        dCr(0);
        if (inChr==0) getch();
        else
        {
            if (inChr==8)
            {
                oldClr=getcolor();
                --sirIx;
                if (sirIx<0) sirIx=0;
                moveto(xVal[sirIx],gety());
                setcolor(getbkcolor());
                outSir[0]=inSir[sirIx];
                outtext(outSir);
                moveto(xVal[sirIx],gety());

                setcolor(oldClr);
            }
            else
            {
                inSir[sirIx]=inChr;

                outSir[0]=inChr;
                outtext(outSir);

                ++sirIx;

                xVal[sirIx]=getx();
            }
        }
    }
    while(inChr!=13 && inChr!=10);
    inSir[sirIx]=0;
}

void firstPage(int &N)
{   setgraph();
    char *stringN;
    int midx = getmaxx() / 2,  midy = getmaxy() / 2;
    settextstyle(7, 0, 4);
    outtextxy(midx/3, midy-40, "Analiza Circuitelor Electrice");
    delay(1000);
    settextstyle(10, 0, 2);
    outtextxy(midx/3, midy, "Introduceti numarul de noduri: ");
    getch();
    moveto(midx/3, midy*4/3);
    //  moveto(midx/3,midy/3);
    do
    {
    getGrSir(stringN);
    N=atoi(stringN);
    }while('0'> stringN[0] || stringN[0]>'9');
    cleardevice();
    delay(1000);
    outtextxy(20, 1/2*getmaxy(), " Veti folosi tastele 'r' si 'e',");
    outtextxy(20, 1/2*getmaxy() +60, " respectiv orice alta litera ");
    outtextxy(20, 1/2*getmaxy()+ 120, " pentru a preciza tipul elementelor circuitului: ");
    while(!kbhit);
     delay(3000);

    cleardevice();

}


struct nod
{
    int info, x, y;
    nod *next;
};


nod *L[100];

struct muchie
{
    int info, nA, nB;
    char elem;
} muchii[100];



int isNod(int x, int y, int r)
{
    for(int i=1; i<=n; i++)
        if(x<=L[i]->x+r && L[i]->x-r<=x && y<=L[i]->y+r && L[i]->y-r<=y)
            return i;
    return 0;

}

void addNewNode(int x, int y, int i)
{
    nod *q = new nod;
    q->info = i;
    q->x = x, q->y = y;
    q -> next = NULL;
    L[i] = q;
    n++;
}

int isMuchie(int nA, int nB)
{
    for(int i=1; i<=m; i++)
        if((muchii[i].nA == nA && muchii[i].nB == nB) || (muchii[i].nA == nB && muchii[i].nB == nA))
            return i;
    return 0;
}

void addNewMuchie(int nA, int nB, char elem, int info)
{
    muchii[info].info = info;
    muchii[info].nA = nA;
    muchii[info].nB = nB;
    muchii[info].elem = elem;
    m++;
}


void refresh()
{
    int v = getvisualpage();
    int a = getactivepage();
    setvisualpage(a);
    setactivepage(v);
}
void redrawG()
{

     for(int i=1; i<=n; i++)
       circle(L[i]->x, L[i]->y, 10);
     for(int i=1; i<=m; i++)
     {
           line(L[muchii[i].nA]->x, L[muchii[i].nA]->y, L[muchii[i].nB]->x, L[muchii[i].nB]->y);
            moveto(L[muchii[i].nA]->x, L[muchii[i].nA]->y);
            char nr1[10]; itoa(L[muchii[i].nA]->info, nr1, 10);
            outtext(nr1);
            moveto(L[muchii[i].nB]->x, L[muchii[i].nB]->y);
            char nr2[10]; itoa(L[muchii[i].nB]->info, nr2, 10);
            outtext(nr2);

          if(muchii[i].elem=='r')
          {
            moveto((L[muchii[i].nA]->x+ L[muchii[i].nB]->x)/2, (L[muchii[i].nA]->y+ L[muchii[i].nB]->y)/2);
            outtext("R");

           }
            if(muchii[i].elem == 'e')
           {
            moveto((L[muchii[i].nA]->x+ L[muchii[i].nB]->x)/2, (L[muchii[i].nA]->y+ L[muchii[i].nB]->y)/2);
            outtext("E");
           }
     }
     delay(1000);

     if(finOK)
     {
         moveto(20, 20);
         outtext(Vf);

         moveto(20, 40);
         outtext(If);
     }
    // cleardevice();
   //  closegraph();

}




void drawGraph()
{

    //  N = getch();

    int N, M;
    firstPage(N);
    delay(1000);
    refresh();
    delay(1000);
    POINT cursorPos;
    while(n<N)
    {
        GetCursorPos(&cursorPos);
        if(ismouseclick(WM_LBUTTONDOWN))
        {

            if(!isNod(cursorPos.x, cursorPos.y, 50))
            {
                addNewNode(cursorPos.x, cursorPos.y, n+1);
                fillellipse(cursorPos.x, cursorPos.y, 10, 10);

                refresh();

            }

            clearmouseclick(WM_LBUTTONDOWN);
        }

    }

    //  refresh();
//   delay(1000);
    int activeNod = 0, k=0;

    M = 0;

    while(!kbhit())
    {
        GetCursorPos(&cursorPos);
        if(ismouseclick(WM_LBUTTONDOWN))
        {

            if(isNod(cursorPos.x, cursorPos.y, 30))
            {

                int currentNod = isNod(cursorPos.x, cursorPos.y, 30);

                if(activeNod)
                {
                    if(!isMuchie(activeNod, currentNod) && activeNod!=currentNod)
                    {

                        int val;
                        char  P= getch();


                          switch(P)
                        {
                        case 'r':

                            moveto((L[activeNod]->x + L[currentNod]->x)/2, (L[currentNod]->y + L[activeNod]->y)/2);

                            outtext("R");
                            line(L[activeNod]->x, L[activeNod]->y, L[currentNod]->x, L[currentNod]->y);

                            r[activeNod-1][currentNod-1] = r[currentNod-1][activeNod-1] = 1;


                            break;
                        case 'e':

                            line(L[activeNod]->x, L[activeNod]->y, L[currentNod]->x, L[currentNod]->y);
                            moveto((L[activeNod]->x + L[currentNod]->x)/2, (L[currentNod]->y + L[activeNod]->y)/2);

                             outtext("E");

                             v[activeNod-1][currentNod-1] = v[currentNod-1][activeNod-1] = 1;

                            break;

                        default:

                            line(L[activeNod]->x, L[activeNod]->y, L[currentNod]->x, L[currentNod]->y);
                        }



                        addNewMuchie(activeNod, currentNod, P, m+1);



                        g[activeNod-1][currentNod-1] = g[currentNod-1][activeNod-1]=1;
                        activeNod = 0;
                    }


                }
                else
                {


                    activeNod = currentNod;
                }


            }

            clearmouseclick(WM_LBUTTONDOWN);
        }
    }
    M = m;

    cleardevice();
    delay(1000);
    redrawG();

    delay(1000);
    while(!kbhit)
        delay(1000);
    delay(4000);
    cleardevice();
}
void input()
{
     int valRE;
     char valreS[10];

  for(int i=0; i<n; i++)
     for(int j=i+1; j<n; j++)
      {
          redrawG();
       // cleardevice();
       if(r[i][j])
        {


         //   cout << i + 1 << " " << j +1 << " R: " << endl;


            char nr1[10]; itoa(i+1, nr1, 10);
          //  outtext(nr1);

            char nr2[10]; itoa(j+1, nr2, 10);
           // outtext(nr2);

            outtextxy(30, 120, "R ");
            outtextxy(50, 120, nr1);
            outtextxy(70, 120, nr2);
            outtextxy(80, 120, " : ");
            moveto(100, 120);
       //     gotoxy();
            getch();

            do
            {
            getGrSir(valreS);
            valRE = atoi(valreS);
            }while('0'> valreS[0] || valreS[0]>'9');
            outtextxy(140, 120, " ohm");

          //  scanf("%d", &valRE);
             r[i][j] = r[j][i] = valRE;

            delay(2000);
             cleardevice();

        }
        else if(v[i][j])
        {
           // cout << i +1 << " " << j +1 << " E: " << endl;

            char nr1[10]; itoa(i+1, nr1, 10);
          //  outtext(nr1);

            char nr2[10]; itoa(j+1, nr2, 10);
           // outtext(nr2);

            outtextxy(30, 120, "E ");
            outtextxy(50, 120, nr1);
            outtextxy(70, 120, nr2);
            outtextxy(80, 120, " : ");
            moveto(100, 120);
          //  gotoxy();;
             getch();
            do
            {
            getGrSir(valreS);
            valRE = atoi(valreS);
            }while('0'> valreS[0] || valreS[0]>'9');

            outtextxy(140, 120, " V");


            v[i][j]= v[j][i] = valRE;
            delay(2000);
            cleardevice();

        }

      }
      /*
    for(int i=0; i<n; i++)
    { for(int j=0; j<n; j++)
     cout << g[i][j] << " ";
     cout << endl;
    }
    cout << endl;
      for(int i=0; i<n; i++)
    { for(int j=0; j<n; j++)
     cout << r[i][j] << " ";
     cout << endl;
    }
    cout << endl;
      for(int i=0; i<n; i++)
    { for(int j=0; j<n; j++)
     cout << v[i][j] << " ";
     cout << endl;
    }
    */
}


int main()
{
    int gd=DETECT,gm;
    initgraph(&gd,&gm," ");
   // setgraph();
    //  setGraphic();
     drawGraph();
    if(m>=n)
    {
    input();
    initAlg();
    delay(1000);
    cleardevice();
    delay(1000);
    settextstyle(10, 0, 1);
    redrawG();
    delay(3000);
    while(!kbhit)
        delay(3000);
    }


    return 0;
}
