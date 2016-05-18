#include<allegro.h>
#include<cstdlib>
#include<math.h>
#include<stdio.h>
#include<process.h>
#define pi 3.141
#include <string>
#define WHITE makecol(255, 255, 255)
using namespace std;
int acc = 0;
time_t seconds;
int stop = 0;
int flag = 1;
string gr;
BITMAP *buffer;
BITMAP *SpikeBallSprite;
BITMAP *SpikeBall2Sprite;
BITMAP *man;
BITMAP *man1;
BITMAP *set;
BITMAP *Bomb;
BITMAP *Bomb2;
BITMAP *Bomb21;
BITMAP *TitleScreen;
int whichbit;
struct 
   {
      int x;
      int y;
      int flag;
      int tempx;
      int tempy;
   }player={500,420,1};
struct Highscore
{
      string name;
      float score;
}hs[11], temp;
   class ball
   {
      float u;
      float x;
      float y;
      float tempx;
      float tempy;
      float time;
      float theta;
      float range;
      float timeofflight;
      float sx;
      float sy;
      float g;
      public:
            int useflag;
            int col;
            void displayball();
            ball()
            {
               col=128;
               useflag = 0;
               u = 80.0;
               theta = (45.0+rand()%40) * (pi/180.0);
               g = 10.0;
               timeofflight =(u*(sin(theta)))/g;
               sx = u * cos(theta) * timeofflight;
               range=0.0;
            }
            void calculate();
            void check();
            void reinit();
}pos[100];
void Sortscore()
{
     
     FILE* Sfile;
     FILE* Sfile1;
     Sfile = fopen("Scores.txt", "r");
     Sfile1 = fopen("Sortedscores.txt","w");
     int iloop,jloop,ls;
     Highscore temp;
     char buffer1[1024];
     int countarr, c1;
     for(countarr = 0; countarr < 11; countarr++)
     {
         if(Sfile == NULL)
         {
              break;
         }         
         fscanf(Sfile, "%f %s", &hs[countarr].score, buffer1);
         hs[countarr].name = buffer1;
     }         
        for(iloop = 0;iloop < 10;iloop++)
        {
          ls = iloop;
        for(jloop = iloop + 1;jloop < 11;jloop++)
        {
               if(hs[jloop].score < hs[ls].score)
               {
                   ls = jloop;
               }
        }
        temp = hs[ls];
        hs[ls] = hs[iloop];
        hs[iloop] = temp;
       }
       for(c1 = 1; c1 < countarr; c1++)
       {
              fprintf(Sfile1, "%f %s \n", hs[c1].score, hs[c1].name.c_str());
       }
       fclose(Sfile);
       fclose(Sfile1);
       Sfile = fopen("Scores.txt", "w");
       for(c1 = 1; c1 < countarr; c1++)
       {
              fprintf(Sfile, "%f %s \n", hs[c1].score, hs[c1].name.c_str());
       }
       fclose(Sfile);       
}  
                               
int ctr=-1;
int ctrmax=0;

void ball :: reinit()
{
   useflag = 0;
   u = 80.0;
   theta = (45.0+rand()%40) * (pi/180.0);
   g = rand()%10 +1 ;
   timeofflight =(u*(sin(theta)))/g;
   sx = u * cos(theta) * timeofflight;
   range = 0.0;
}

void ball :: displayball()
{
   //whichbit = 1 + rand()%10;
   SpikeBallSprite = load_bitmap( "Spikedball.bmp", NULL);
   //Bomb = load_bitmap( "Bomb1.bmp", NULL);
   SpikeBall2Sprite = load_bitmap( "Spikeball2.bmp", NULL);
   char buf[20]={0};
   acquire_screen();
   /*FILE*fp=fopen("data.txt","a");
   fprintf(fp,"%f %f %f %f %f\n",x,sx,range,(x-sx+range),(y));
   fclose(fp);*/
   /*sprintf(buf,"%f",x-sx+range);
   textout_ex( buffer, font, buf, 0, 0, makecol( 255, 0, 0), makecol( 0, 0, 0) );
   sprintf(buf,"%f",480.0-y);
   textout_ex( buffer, font, buf, 100,0,makecol(255,0,0),makecol(0,0,0));*/
   //draw_sprite(buffer,SpikeBall2Sprite,(int)(tempx-sx+range),(int)(480.0-tempy));
   circlefill(buffer,(int)(tempx-sx+range),(int)(480.0-tempy),20,makecol(0,0,0));
circlefill(buffer,(int)(x-sx+range),(int)(480.0-y),20,makecol(col,255,0));
   //draw_sprite(buffer,SpikeBallSprite,(int)(x-sx+range),(int)(480.0-y));
   if(x-sx+range > 630.0)
   {
      //draw_sprite(buffer,SpikeBall2Sprite,(int)(x-sx+range),(int)(480.0-y));
      circlefill(buffer,(int)(x-sx+range),(int)(480.0-y),20,makecol(0,0,0));
      ctr--;
      this->reinit();
   }
   /*
   sprintf(buf,"%d",(int)(x-sx+range));
   textout_ex( buffer, font, buf, 0, 20, makecol( 255, 0, 0), makecol( 0, 0, 0) );
   sprintf(buf,"%d",player.x);
   textout_ex( buffer, font, buf, 100,20,makecol(255,0,0),makecol(0,0,0));
   */
   draw_sprite(screen,buffer,0,0);
   if((int)(500-y) > player.y)
   {
      if(abs((int)(x-sx+range)-(player.x+7))<=20)
      {
         player.flag=0;
      }
   }
   release_screen();
}

void ball :: calculate()
{
   if(timeofflight >= (2* u*(sin(theta))/g))
   { 
      circlefill(buffer,(int)(x-sx+range),(int)(480.0-y),20,makecol(0,0,0));
      float c = 0.0;
      float t2=2.0 * theta;
      timeofflight = 0;
      c=(u*u*sin(t2))/g;
      range+= c;
   }
   tempx = x;
   tempy = y;
   x = u * cos(theta) * timeofflight;
   y = (u* sin(theta) * timeofflight) - (0.5 * g * timeofflight * timeofflight);
   // displayball();
   timeofflight+=0.1;
}


void moveplayer()
{
   man = load_bitmap( "stickfig.bmp", NULL);
   man1 = load_bitmap( "man1.bmp", NULL);
   player.tempx=player.x;
   player.tempy=player.y; 
   if( key[KEY_RIGHT] )
   {
      player.x+=4;
   } 
   else if( key[KEY_LEFT])
   {
      player.x-=4;
   } 
   acquire_screen();
   if(player.x>30 && player.y <475 && player.x <595) // restrict player movement >30
   {
      draw_sprite( buffer,man1, player.tempx, player.tempy);
      draw_sprite( buffer, man, player.x, player.y);
      /*rectfill( buffer, player.tempx, player.tempy, player.tempx + 10, player.tempy + 60, makecol ( 0, 0, 0));
      rectfill( buffer, player.x, player.y, player.x + 10, player.y + 60, makecol ( 0, 0, 255));*/
   }

   release_screen();
}

int main()
{
   float sco; 
   int i,f=0;
   time_t start;
   double timediff;
   char t[20], q[20];
   allegro_init();
   install_keyboard();
   set_color_depth(16);
   set_gfx_mode( GFX_AUTODETECT, 640, 480, 0, 0);
   buffer = create_bitmap( 640, 480);
   time(&seconds);
   srand((unsigned int) seconds);
   rest(1000);


   string  edittext;                         // an empty string for editting
   string::iterator iter = edittext.begin(); // string iterator
   int     caret  = 11;                       // tracks the text caret
   bool    insert = true;
   int flagscan = 1;
   while(!key[KEY_ESC])
   {                
      while(keypressed())
      {                                         
         if(flagscan == 0)
         {
           break;
         }  
         int  newkey   = readkey();
         char ASCII    = newkey & 0xff;
         char scancode = newkey >> 8;
 
         // a character key was pressed; add it to the string
         if(ASCII >= 32 && ASCII <= 126)
         {
            // add the new char, inserting or replacing as need be
            if(insert || iter == edittext.end())
               iter = edittext.insert(iter, ASCII);
            else
               edittext.replace(caret, 1, 1, ASCII);
 
            // increment both the caret and the iterator
            caret++;
            iter++;
         }
         // some other, "special" key was pressed; handle it here
         else
            switch(scancode)
            {
               case KEY_ENTER:
       
                    flagscan = 0;
                    stop = 1;
                    acc = 1;
                    break;
               case KEY_DEL:
                  if(iter != edittext.end()) iter = edittext.erase(iter);
               break;
 
               case KEY_BACKSPACE:
                  if(iter != edittext.begin())
                  {
                     caret--;
                     iter--;
                     iter = edittext.erase(iter);
                  }
               break;
 
               case KEY_RIGHT:
                  if(iter != edittext.end())   caret++, iter++;
               break;
 
               case KEY_LEFT:
                  if(iter != edittext.begin()) caret--, iter--;
               break;
 
               case KEY_INSERT:
                  if(insert) insert = 0; else insert = 1;
               break;
 
               default:
               break;
            }
      }
 
      if(flagscan != 0)
      {
      clear(buffer);
      TitleScreen = load_bitmap("TitleScreen.bmp",NULL);
      draw_sprite(buffer,TitleScreen,0,0);
      textout_ex( buffer, font, "WELCOME TO FALLING BALLS!! Please Enter Your Name To Begin!", 100,240,makecol(255,255,0),makecol(0,0,0));
      // output the string to the screen
      textout(buffer, font, edittext.c_str(), 100, 250, WHITE);
         start = time(0);
      vline(buffer, caret * 9, 247, 257, WHITE);
 
      // blit to screen
      blit(buffer, screen, 0, 0, 0, 0, 640, 480);
      }
      if(acc == 1)
      {
       clear(buffer);
      }
      

      if(stop == 1)
      {
          acc = 2;         
         if(!player.flag)
         {
            clear(buffer);             

            temp.score = timediff;             
            textout_ex( buffer, font, "Sorry, You Lose !", 300,220,makecol(255,255,0),makecol(0,0,0));
            textout_ex( buffer, font, "Your score is :", 300,240,makecol(255,255,0),makecol(0,0,0));
            sprintf(t,"%f",temp.score);
            textout_ex( buffer, font,t,300,260,makecol(255,255,0),makecol(0,0,0));
            draw_sprite(screen,buffer,0,0);
            rest(1500);
            clear(buffer);

            FILE *Sfile;
            FILE *Sfile1;
            Sfile = fopen("Scores.txt","a+");
            Sfile1 = fopen("Sortedscores.txt","r");
            fscanf(Sfile1, "%f", &sco);
            if(temp.score > sco)
            {
            fprintf(Sfile, "%f %s \n", temp.score, edittext.c_str());
            }
            fclose(Sfile);
            Sortscore();
            textout_ex( buffer, font, "Name:", 200,200,makecol(255,0,0),makecol(0,0,0));
            textout_ex( buffer, font, "Score:", 280,200,makecol(255,0,0),makecol(0,0,0));
            int j1;
            for(j1 = 1; j1 < 11; j1++)
            {
              sprintf(t,"%s", hs[j1].name.c_str());
              sprintf(q,"%f", hs[j1].score);
              textout_ex( buffer, font,t,200,(200 + (j1 * 10)),makecol(255,255,0),makecol(0,0,0));
              textout_ex( buffer, font,q,280,(200 + (j1 * 10)),makecol(255,255,0),makecol(0,0,0)); 
            }      
            draw_sprite(screen,buffer,0,0);
            rest(3000);
            break; 
         }
          textout_ex( buffer, font,"Score:", 550,0,makecol(255,0,0),makecol(0,0,0));
             textout_ex( buffer, font,"NOB:", 450,0,makecol(255,0,0),makecol(0,0,0));
         if(ctr<ctrmax)
            for(i=0;i<=ctrmax;i++)
         if(pos[i].useflag==0)
         {
            pos[i].useflag=1;
            ctr++;
            break;
         }
         for(i=0;i<=ctrmax;i++)
         {
            if(pos[i].useflag == 1)
            {
            pos[i].col = 100 + rand() % 156 ;
            pos[i].calculate();
            pos[i].displayball();
            }
         }
         timediff=difftime( time(0), start);
         if((int)timediff % 5 == 0 && f)
         {
            ctrmax++;
            f=0;
         }
         if((int)timediff > (ctrmax)*5+1)
         f=1;
         sprintf(t,"%f",timediff);
         textout_ex( buffer, font, t, 600,0,makecol(255,0,0),makecol(0,0,0));
         sprintf(t,"%d",ctrmax);
         textout_ex( buffer, font, t, 500,0,makecol(255,0,0),makecol(0,0,0));
         rest(10);
         moveplayer();
         }
   }
      
   return 0;
}
END_OF_MAIN();
