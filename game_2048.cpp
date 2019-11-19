#include <ncurses.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

enum key {kup, kdown, kleft, kright};
void trans_coor(int i, int j, int& x, int& y, int& z, key k);
bool add_item(vector< vector<int> >& v);
void easy_display();
void refresh_screen(const vector< vector<int> >& v);
void perform(vector< vector<int> > & v, key k);
//void initial_checkerboard(vector<vetor<int> > &arr)
vector< vector<int> > initial_checkerboard(void)
{
  vector< vector <int> > arr(4, vector<int>(4));
  srand(time(0));
  //cout << std::rand();
  int x1 = rand() % 4;
  int y1  = rand() % 4;
   
  int x2 = rand() % 4;
  int y2 = rand() % 4;
  
  while(x1 == x2 && y1 == y2)
  {
    x2 = rand() %4;
    y2 = rand() %4;
  }
  arr[x1][y1] = 2;
  arr[x2][y2] = 2;
  return arr;
}

bool add_item(vector< vector<int> >& v)
{
  bool keep = false;
  int i,j=0;
  for(i=0;i<4;i++)
    for(j=0;j<4;j++)
      if(v[i][j] ==0)
        keep=true;
  if(keep == false)
    return keep; 
  srand(time(0));
  //cout << std::rand();
  int x = rand() % 4;
  int y = rand() % 4;

  while(v[x][y] != 0)
  {
    x = rand() %4;
    y = rand() %4;
  }
  v[x][y] = 2;
  return keep;
}

void refresh_screen(const vector< vector<int> >& v)
{
  int i,j,k,q=0;
  int int_n[4]={0,0,0,0};
  char n[]="0\0";
  clear();
  for(i=0;i<4;i++)
  {
    for(j=0;j<4;j++)
    {
      for(q=0;q<4;q++)
        int_n[q]=0;
      k = v[i][j];
      if(k/1000!=0)
        int_n[0]=k/1000;
      if((k%1000)/100!=0)
        int_n[1]=(k%1000)/100;
      if((k%100)/10!=0)
        int_n[2]=(k%100)/10;
      if(k%10!=0)
        int_n[3]=k%10;
      mvprintw(i*2, j*5, "|");
      k=0;
      for(q=0;q<4;q++)
      {
        if(k==0)
        {
          if(int_n[q]==0)
            continue;
        }
        k=1;
        n[0]=0x30+int_n[q];
        mvprintw(i*2, j*5+q+1, n);
      }
    }
    mvprintw(i*2,20, "|");
  }
  refresh();
}

void trans_coor(int i, int j, int& x, int& y, int& z, key k)
{
  if(k==kup)
  {
     x=j;
     y=i;
     z=1;
  }
  else if(k==kdown)
  {
     x=3-j;
     y=i;
     z=-1;
  }
  else if(k==kleft)
  {
     x=i;
     y=j;
     z=1;
  }
  else if(k==kright)
  {
     x=i;
     y=3-j;
     z=-1;
  }
}

void perform(vector< vector<int> > & v, key k)
{
  int i,j,q,p=0;
  int x,y,z=0;
    for(i=0;i<4;i++)
    {
      for(p=0;p<3;p++)
      {
      for(j=0;j<3;j++)
      {
        trans_coor(i, j, x, y, z, k);
        if(v[x][y] == 0)
        {
          if(k==kup || k==kdown)
          {
            q = v[x+z][y];
            v[x+z][y]=0;
          }
          else
          {
            q = v[x][y+z];
            v[x][y+z]=0;
          }
          v[x][y] = q;
        }
      }
      }
      for(j=0;j<3;j++)
      {
        trans_coor(i, j, x, y, z, k);
        if(k==kup || k==kdown)
        {
          q = v[x+z][y];
          if(v[x][y]==q)
          { 
            v[x+z][y]=0;
            v[x][y]=2*q;
          }
        }
        else
        { 
          q = v[x][y+z];
          if(v[x][y]==q)
          { 
            v[x][y+z]=0;
            v[x][y]=2*q;
          }
        }
      }
      for(j=0;j<3;j++)
      {
        trans_coor(i, j, x, y, z, k);
        if(v[x][y] == 0)
        {
          if(k==kup || k==kdown)
          {
            q = v[x+z][y];
            v[x+z][y]=0;
          }
          else
          {
            q = v[x][y+z];
            v[x][y+z]=0;
          }
          v[x][y] = q;
        }
      }
    }
}

int main()
{
  //easy_display();
  //getchar();
  //endwin();
  char c;
  initscr();
  vector <vector <int> > arr(4, vector<int>(4));
  arr = initial_checkerboard();
  //cout << arr;
  curs_set(FALSE);
  clear();
  refresh_screen(arr);
  bool keep = true;
  key k=kup;
  while(1)
  {
    c = getchar();
    if(c=='w')
      k=kup;
    else if(c=='s')
      k=kdown;
    else if(c=='a')
      k=kleft;
    else if(c=='d')
      k=kright;
    else if(c=='q')
      break;
    else
      {
        mvprintw(12, 12, "You must press 'w' or 's' or 'a' or 'd'");
        refresh();
        continue;
      }
    perform(arr, k);
    keep = add_item(arr);
    refresh_screen(arr);
    if(keep == false)
      break;
  }
  refresh_screen(arr);
  mvprintw(12, 12, "You are failure!");
  mvprintw(14, 14, "Please press 'q' to quit!");
  refresh();
  while(getchar() != 'q');
  endwin();
  return 0;
}

void easy_display()
{
  initscr();
  mvprintw(10, 20, "abc");
  refresh();
}
