#include <LiquidCrystal.h>
//#include <FlexiTimer2.h>
#include <MsTimer2.h>
#include <pitches.h>

//=====================================ジョイスティック読み取り===================================================================================================
const int Y_pin = 1;
const int X_pin = 0;
const int SW_pin = 6;
int read_y;
int read_x;
int read_SW;
//================================================キャラ設定===================================================================================================
int i;              //カスタムキャラクター番号
int x;              //x軸移動
int rank;           //階層(0 or 1)
int setrange;
int setrange1;
int setrange2;
//==================================================攻撃設定===================================================================================================
const int BUTTON = 2;
int read_button;    //ボタンの読み取り
int j;
int k;
int atack;          //攻撃1中なら1
int atack2;         //攻撃2中なら1
int atack_x;        //攻撃1の初期位置(x)
int atack2_x;       //攻撃2の初期位置(x)
int atack_rank;     //攻撃1の初期階層
int atack2_rank;    //攻撃2の初期階層
int side;           //攻撃1の方向設定
int side2;          //攻撃2の方向設定
int life;           //ライフ
//===============================================ジャンプ設定===================================================================================================
int read_yy;        //ジャンプ中なら1
int jump;           //ジャンプの段階
//===================================================敵設定====================================================================================================
int enemy_x;        //敵の座標
int enemy_y;        //
int enemy2_x;       //
int enemy2_y;       //
int enemy3_x;       //
int enemy3_y;       //
int enemy4_x;       //
int enemy4_y;       //
int enemy5_x;       //
int enemy5_y;       //
int enemy6_x;       //
int enemy6_y;       //
int enemy7_x;       //
int enemy7_y;       //
int enemy_life;     //敵の体力
int enemy2_life;    //
int enemy3_life;    //
int enemy4_life;    //
int enemy5_life;    //
int enemy6_life;    //
int enemy7_life;    //
int span_atack1;    //敵の攻撃頻度
int span_atack2;    //
int atack_count;    //敵の攻撃位置
int atack_count2;
int enemyatack_x;
int enemyatack_y;
int enemyatack2_x;
int enemyatack2_y;
//================================================ゲーム進行====================================================================================================
int progress;                     //ゲームの進行具合***周回ごとに+1
int interval_delay;               //速度
int overcount;                    //ゲームオーバー時のbgm調整
unsigned long int memory_enemy;   //
unsigned long int memory_enemy2;  //
unsigned long int memory_enemy3;
unsigned long int memory_enemy4;
unsigned long int memory_enemy5;
unsigned long int memory_enemy6;
unsigned long int memory_enemy7;
//===============================================中断メニュー===================================================================================================
int cursor_x;
int cursor_y;
//============================================================================================================================================================

const int n=0; //ジョイスティック読み取りy
const int m=0; //ジョイスティック読み取りx

int q; //ステージ３カウント変数
int qq; //ステージ１カウント変数
int qqq; //ステージ２カウント変数

int d; //左右移動
//int j; //ステージ２、障害物移動
int jj; //ジャンプ変数
int ii; //キャラクター変更変数
//int i; //キャラクター変更媒介変数
int r; //ランダム変数0～15(位置)
int rr; //ランダム変数0～15(位置)

int rrr; //ランダム変数0～1(位置)
int jjj; //ランダム変数3～4(位置)
int kkk; //ランダム変数3～4(位置)
int lll; //ランダム変数3～4(位置)
int mmm; //ランダム変数3～4(位置)
int nnn; //ランダム変数0～1(位置)

int u; //stage1 random
int uu; //stage1 random

int aa;
int bb;
int cc;
int dd;

int ra; //ランダム数値0～9
int rb;
int rc;
int rd;
int re;
int rf;
int rg;
int rh;
int ri;
int rj;
int aaa; //ランダム数値-2～2
int bbb;
int ccc;
int ddd;

//const int x=0; //ジョイスティック読み取りx
const int y=0; //ジョイスティック読み取りy
int xx; //左右移動
int yy; //上下移動
const int w=0; //ジョイスティック読み取りx
const int z=0; //ジョイスティック読み取りy
int ww; //左右移動
int zz; //上下移動

int volatile t=0; //bgm-----------800/なし-----0/地上----600/地下----900/gameover----1000/clear----2000/game3----
volatile int W=48;

int p=0;
int pp=0;

int rxx; //ゲーム３の移動読み取り
int ryy;
int rx;
int ry;
int rz;
int c; //upとdown
int b; //rightとleft
int s; //game3のスコアカウント
int ss; //スコア

int customMODE;


LiquidCrystal lcd(12, 11, 5, 4, 10, 7); // RS, E, D4, D5, D6, D7

//const int SW_pin = 6; // digital pin connected to switch output
//const int X_pin = 0; // analog pin connected to X output
//const int Y_pin = 1; // analog pin connected to Y output


void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
  pinMode(3,OUTPUT);
  pinMode(13, OUTPUT);
  //FlexiTimer2::set(W, blink);
  //FlexiTimer2::start();
  MsTimer2::set(W, BGM);
  MsTimer2::start();
  pinMode(SW_pin,INPUT_PULLUP);
  pinMode(BUTTON,INPUT_PULLUP);
  customMODE=0;
}

void loop(){
  goto custom;
  goto menu1;
  i=1;
  qq=0;
  ii=i%5;
  r=random(0,16);
  rr=random(0,16);
  while(1){ //ステージ１
    stage11:


    while(i<5){

      p=digitalRead(SW_pin);
      int n=analogRead(Y_pin);
      if(n<480){
        d=d+1;
      }
      else if(n>600){
        d=d-1;
      }
      else{
        d=d;
      }
      ii=i%5;
      lcd.begin(16,2);
      lcd.setCursor(r,0);
      lcd.write(byte(ii));
      lcd.setCursor(r+3,0);
      lcd.write(byte(ii));
      lcd.setCursor(r-2,0);
      lcd.write(byte(ii));
      lcd.setCursor(r+7,0);
      lcd.write(byte(ii));
      lcd.setCursor(r-5,0);
      lcd.write(byte(ii));
      lcd.setCursor(rr,0);
      lcd.write(byte(ii));
      lcd.setCursor(rr+1,0);
      lcd.write(byte(ii));
      lcd.setCursor(rr-1,0);
      lcd.write(byte(ii));
      lcd.setCursor(rr+2,0);
      lcd.write(byte(ii));
      lcd.setCursor(rr-2,0);
      lcd.write(byte(ii));
      lcd.setCursor(u,0);
      lcd.write(byte(ii));
      lcd.setCursor(u+1,0);
      lcd.write(byte(ii));
      lcd.setCursor(u-uu,0);
      lcd.write(byte(ii));

      lcd.setCursor(d,1);
      lcd.write(byte(0));
      i++;

      delay(200);
      if(i==5){
        i=1;
        while(i<5){
          int n=analogRead(Y_pin);
          if(n<480){
            d=d+1;
          }
          else if(n>600){
            d=d-1;
          }
          else{
            d=d;
          }
          ii=i%5;
          lcd.begin(16,2);
          lcd.setCursor(r,1);
          lcd.write(byte(ii));
          lcd.setCursor(r+3,1);
          lcd.write(byte(ii));
          lcd.setCursor(r-2,1);
          lcd.write(byte(ii));
          lcd.setCursor(r+7,1);
          lcd.write(byte(ii));
          lcd.setCursor(r-5,1);
          lcd.write(byte(ii));
          lcd.setCursor(rr,1);
          lcd.write(byte(ii));
          lcd.setCursor(rr+1,1);
          lcd.write(byte(ii));
          lcd.setCursor(rr-1,1);
          lcd.write(byte(ii));
          lcd.setCursor(rr+2,1);
          lcd.write(byte(ii));
          lcd.setCursor(rr-2,1);
          lcd.write(byte(ii));
          lcd.setCursor(u,1);
          lcd.write(byte(ii));
          lcd.setCursor(u+1,1);
          lcd.write(byte(ii));
          lcd.setCursor(u-uu,1);
          lcd.write(byte(ii));



          lcd.setCursor(d,1);
          lcd.write(byte(0));

          if(i>=2 && (d==r || d==r+3 || d==r-2 || d==r+7 || d==r-5 || d==rr || d==rr+1 || d==rr-1 || d==rr+2 || d==rr-2 || d==u || d==u+1 || d==u-uu)){ //あたり判定
            lcd.begin(16,2);
            lcd.setCursor(0,0);
            lcd.print("Game Over");
            t=900;
            delay(4000);
            xx=0;
            yy=0;
            qq=0;
            q=0;
            qqq=0;
            t=800;
            goto menu1;
          }
          i++;
          delay(200);
        }
        r=random(0,16);
        rr=random(0,16);
        uu=random(1,3);
        u=d;
        i=1; //whileループ
        qq++; //ステージ１から抜け出す
        if(qq>=15){
          goto stage2;
        }
      }

      if(p==0){
        xx=0;
        yy=1;
        ww=0;
        zz=1;
        t=800;
        q=0;
        qq=0;
        qqq=0;
        goto menu1;
      }
      Serial.print(i);

    }

  }
  while(1){ //ステージ２
    stage22:
    qqq++;
    if(qqq==5){ //ステージ2から抜け出す
      qqq=0;
      q=0;
      qq=0;
      goto stage3;
    }
    j=0;
    while(j<32){
      p=digitalRead(SW_pin);
      int m = analogRead(X_pin);

      if(m<480){
        lcd.begin(16,2);
        lcd.setCursor(5,0);
        lcd.write(byte(5));
        lcd.setCursor(15-j,1);
        lcd.print("F");
        lcd.setCursor(15-j+jjj,rrr);
        lcd.print("I");
        lcd.setCursor(15-j+jjj+kkk,1);
        lcd.print("G");
        lcd.setCursor(15-j+jjj+kkk+lll,1);
        lcd.print("H");
        lcd.setCursor(15-j+jjj+kkk+lll+mmm,nnn);
        lcd.print("T");
        if((15-j+jjj==5 && rrr==0) || (15-j+jjj+kkk+lll+mmm==5 && nnn==0)){
          lcd.begin(16,2);
          lcd.setCursor(0,0);
          lcd.print("Game Over");
          t=900;
          delay(4000);
          xx=0;
          yy=0;
          ww=0;
          zz=1;
          q=0;
          qq=0;
          qqq=0;
          t=800;
          goto menu1;
        }
        delay(200);

        lcd.begin(16,2);
        lcd.setCursor(5,1);
        lcd.write(byte(5));
        lcd.setCursor(15-j-1,1);
        lcd.print("F");
        lcd.setCursor(15-j+jjj-1,rrr);
        lcd.print("I");
        lcd.setCursor(15-j+jjj+kkk-1,1);
        lcd.print("G");
        lcd.setCursor(15-j+jjj+kkk+lll-1,1);
        lcd.print("H");
        lcd.setCursor(15-j+jjj+kkk+lll+mmm-1,nnn);
        lcd.print("T");
        if(15-j-1==5 || (15-j+jjj-1==5 && rrr==1) || 15-j+jjj+kkk-1==5 || 15-j+jjj+kkk+lll-1==5 || (15-j+jjj+kkk+lll+mmm-1==5 && nnn==1)){
          lcd.begin(16,2);
          lcd.setCursor(0,0);
          lcd.print("Game Over");
          t=900;
          delay(4000);
          xx=0;
          yy=0;
          ww=0;
          zz=1;
          q=0;
          qq=0;
          qqq=0;
          t=800;
          goto menu1;
        }

        j=j+2;;
        delay(200);
        if(j==31){

          rrr=random(0,2);
          jjj=random(2,4);
          kkk=random(2,4);
          lll=random(2,4);
          mmm=random(2,4);
          nnn=random(0,2);
        }
      lcd.print("t:  ");
      lcd.print(t);
      lcd.println("\n\n");
      }
      else{
        p=digitalRead(SW_pin);
        lcd.begin(16,2);
        lcd.setCursor(5,1);
        lcd.write(byte(5));
        lcd.setCursor(15-j,1);
        lcd.print("F");
        lcd.setCursor(15-j+jjj,rrr);
        lcd.print("I");
        lcd.setCursor(15-j+jjj+kkk,1);
        lcd.print("G");
        lcd.setCursor(15-j+jjj+kkk+lll,1);
        lcd.print("H");
        lcd.setCursor(15-j+jjj+kkk+lll+mmm,nnn);
        lcd.print("T");
        if(15-j==5 || (15-j+jjj==5 && rrr==1) || 15-j+jjj+kkk==5 || 15-j+jjj+kkk+lll==5 || (15-j+jjj+kkk+lll==5 && nnn==1)){
          lcd.begin(16,2);
          lcd.setCursor(0,0);
          lcd.print("Game Over");
          t=900;
          delay(4000);
          xx=0;
          yy=0;
          ww=0;
          zz=1;
          q=0;
          qq=0;
          qqq=0;
          t=800;
          goto menu1;
        }

        j++;
        delay(200);
        if(j==31){

          rrr=random(0,2);
          jjj=random(2,4);
          kkk=random(2,4);
          lll=random(2,4);
          mmm=random(2,4);
          nnn=random(0,2);
        }
      lcd.print("t:  ");
      lcd.print(t);
      lcd.println("\n\n");
      if(p==0){
        xx=0;
        yy=1;
        ww=0;
        zz=1;
        qqq=0;
        q=0;
        qq=0;
        t=800;
        goto menu1;
      }
      }
      if(p==0){
        xx=0;
        yy=1;
        ww=0;
        zz=1;
        qqq=0;
        q=0;
        qq=0;
        t=800;
        goto menu1;
      }
    }
  }
  while(1){ //ステージ3
    q=0;
    j=0;
    stage33:
    ra=random(1,10);
    rb=random(1,10);
    rc=random(1,10);
    rd=random(1,10);
    re=random(1,10);
    rf=random(1,10);
    rg=random(1,10);
    rh=random(1,10);
    ri=random(1,10);
    rj=random(1,10);
    while(j<49){


      p=digitalRead(SW_pin);
      int m = analogRead(X_pin);


      if(m<480){
        if(j<47){
        lcd.begin(16,2);
        lcd.setCursor(5,0);
        lcd.write(byte(5));
        lcd.setCursor(15-j,1);
        lcd.print(ra);
        lcd.setCursor(15-j+3,1);
        lcd.print(rb);
        lcd.setCursor(15-j+3+jjj,1);
        lcd.print(rc);
        lcd.setCursor(15-j+3+jjj+4,1);
        lcd.print(rd);
        lcd.setCursor(15-j+3+jjj+4+kkk,1);
        lcd.print(re);
        lcd.setCursor(15-j+3+jjj+4+kkk+3,1);
        lcd.print(rf);
        lcd.setCursor(15-j+3+jjj+4+kkk+3+lll,1);
        lcd.print(rg);
        lcd.setCursor(15-j+3+jjj+4+kkk+3+lll+4,1);
        lcd.print(rh);
        lcd.setCursor(15-j+3+jjj+4+kkk+3+lll+4+mmm,1);
        lcd.print(ri);
        lcd.setCursor(15-j+3+jjj+4+kkk+3+lll+4+mmm+3,1);
        lcd.print(rj);
        delay(200);

        lcd.begin(16,2);
        lcd.setCursor(5,1);
        lcd.write(byte(5));
        lcd.setCursor(15-j-1,1);
        lcd.print(ra);
        lcd.setCursor(15-j+3-1,111);
        lcd.print(rb);
        lcd.setCursor(15-j+3+jjj-1,1);
        lcd.print(rc);
        lcd.setCursor(15-j+3+jjj+4-1,1);
        lcd.print(rd);
        lcd.setCursor(15-j+3+jjj+4+kkk-1,1);
        lcd.print(re);
        lcd.setCursor(15-j+3+jjj+4+kkk+3-1,1);
        lcd.print(rf);
        lcd.setCursor(15-j+3+jjj+4+kkk+3+lll-1,1);
        lcd.print(rg);
        lcd.setCursor(15-j+3+jjj+4+kkk+3+lll+4-1,1);
        lcd.print(rh);
        lcd.setCursor(15-j+3+jjj+4+kkk+3+lll+4+mmm-1,1);
        lcd.print(ri);
        lcd.setCursor(15-j+3+jjj+4+kkk+3+lll+4+mmm+3-1,1);
        lcd.print(rj);
        if(15-j-1==5 || 15-j+3-1==5 || 15-j+3+jjj-1==5 || 15-j+3+jjj+4-1==5 || 15-j+3+jjj+4+kkk-1==5 || 15-j+3+jjj+4+kkk+3-1==5 || 15-j+3+jjj+4+kkk+3+lll-1==5 || 15-j+3+jjj+4+kkk+3+lll+4-1==5 || 15-j+3+jjj+4+kkk+3+lll+4+mmm-1==5 || 15-j+3+jjj+4+kkk+3+lll+4+mmm+3-1==5){
          lcd.begin(16,2);
          lcd.setCursor(0,0);
          lcd.print("Game Over");
          t=900;
          delay(4000);
          xx=0;
          yy=0;
          ww=0;
          zz=1;
          q=0;
          qq=0;
          qqq=0;
          t=800;
          goto menu1;
        }


        j=j+2;
        delay(200);
        }
        if(j>=47){
          xx=0;
          yy=0;

          while(1){ //ステージ３の答え選び（ジャンプ時）
            int x=analogRead(Y_pin);
            int y=analogRead(X_pin);
            if(x>600){
              xx=xx-1;
            }
            else if(x<480){
              xx=xx+1;
            }
            else{
              xx=xx;
            }

            if(y<480){
              yy=yy-1;
            }
            else if(y>600){
              yy=yy+1;
            }
            else{
              yy=yy;
            }
            while(1){ //答えランダム配置設定（ジャンプ時）
              aa=random(3,13);
              if(aa!=4 && aa!=5 && aa!=7 && aa!=8 && aa!=10 && aa!=11){
                break;
              }
            }
            while(1){
              bb=random(3,13);
              if(bb!=4 && bb!=5 && bb!=7 && bb!=8 && bb!=10 && bb!=11 && bb!=aa){
                break;
              }
            }
            while(1){
              cc=random(3,13);
              if(cc!=4 && cc!=5 && cc!=7 && cc!=8 && cc!=10 && cc!=11 && cc!=aa && cc!=bb){
                break;
              }
            }
            while(1){
              dd=random(3,13);
              if(dd!=4 && dd!=5 && dd!=7 && dd!=8 && dd!=10 && dd!=11 && dd!=aa && dd!=bb && dd!=cc){
                break;
              }
            }
            while(1){
              aaa=random(-2,4);
              if(aaa!=0){
                break;
              }
            }
            while(1){
              bbb=random(-2,4);
              if(bbb!=0 && bbb!=aaa){
                break;
              }
            }
            while(1){
              ccc=random(-2,4);
              if(ccc!=0 && ccc!=aaa && ccc!=bbb){
                break;
              }
            }
            while(1){ //答え選択画面（ジャンプ時）
              int x=analogRead(Y_pin);
              int y=analogRead(X_pin);
              if(x>800){
                xx=xx-1;
              }
              else if(x<100){
                xx=xx+1;
              }
              else{
                xx=xx;
              }

              if(y<100){
                yy=yy-1;
              }
              else if(y>800){
                yy=yy+1;
              }
              else{
                yy=yy;
              }
              lcd.begin(16,2);
              lcd.setCursor(xx,yy);
              lcd.write(byte(0));
              lcd.setCursor(aa,0);
              lcd.print(ra+rb+rc+rd+re+rf+rg+rh+ri+rj);
              lcd.setCursor(bb,0);
              lcd.print(ra+rb+rc+rd+re+rf+rg+rh+ri+rj+aaa);
              lcd.setCursor(cc,0);
              lcd.print(ra+rb+rc+rd+re+rf+rg+rh+ri+rj+bbb);
              lcd.setCursor(dd,0);
              lcd.print(ra+rb+rc+rd+re+rf+rg+rh+ri+rj+ccc);
              delay(170);
              if((xx==aa || x==aa+1) && yy==0){
                lcd.begin(16,2);
                lcd.setCursor(0,0);
                lcd.print("Correct Answer");
                delay(2000);
                q++;
                j=0;
                xx=0;
                yy=1;
                ww=0;
                zz=1;
                qq=0;
                qqq=0;

                goto stage33;
              }
              else if((xx==bb || xx==bb+1) && yy==0){
                lcd.begin(16,2);
                lcd.setCursor(0,0);
                t=900;
                lcd.print("Game Over");
                delay(4000);
                xx=0;
                yy=1;
                ww=0;
                zz=1;
                q=0;
                qq=0;
                qqq=0;
                t=800;
                goto menu1;
              }
              else if((xx==cc || xx==cc+1) && yy==0){
                lcd.begin(16,2);
                lcd.setCursor(0,0);
                lcd.print("Game Over");
                t=900;
                delay(4000);
                xx=0;
                yy=1;
                ww=0;
                zz=1;
                q=0;
                qq=0;
                qqq=0;
                t=800;
                goto menu1;
              }
              else if((xx==dd || xx==dd+1) && yy==0){
                lcd.begin(16,2);
                lcd.setCursor(0,0);
                lcd.print("Game Over");
                t=900;
                delay(4000);
                xx=0;
                yy=1;
                ww=0;
                zz=1;
                q=0;
                qq=0;
                qqq=0;
                t=800;
                goto menu1;
              }
            }
          }
          rrr=random(0,2);
          jjj=random(3,5);
          kkk=random(3,5);
          lll=random(3,5);
          mmm=random(3,5);
          nnn=random(0,2);
          ra=random(1,10);
          rb=random(1,10);
          rc=random(1,10);
          rd=random(1,10);
          re=random(1,10);
          rf=random(1,10);
          rg=random(1,10);
          rh=random(1,10);
          ri=random(1,10);
          rj=random(1,10);
        }
      lcd.print("t:  ");
      lcd.print(t);
      lcd.println("\n\n");
      }
      else{
        p=digitalRead(SW_pin);
        lcd.begin(16,2);
        lcd.setCursor(5,1);
        lcd.write(byte(5));
        lcd.setCursor(15-j,1);
        lcd.print(ra);
        lcd.setCursor(15-j+3,1);
        lcd.print(rb);
        lcd.setCursor(15-j+3+jjj,1);
        lcd.print(rc);
        lcd.setCursor(15-j+3+jjj+4,1);
        lcd.print(rd);
        lcd.setCursor(15-j+3+jjj+4+kkk,1);
        lcd.print(re);
        lcd.setCursor(15-j+3+jjj+4+kkk+3,1);
        lcd.print(rf);
        lcd.setCursor(15-j+3+jjj+4+kkk+3+lll,1);
        lcd.print(rg);
        lcd.setCursor(15-j+3+jjj+4+kkk+3+lll+4,1);
        lcd.print(rh);
        lcd.setCursor(15-j+3+jjj+4+kkk+3+lll+4+mmm,1);
        lcd.print(ri);
        lcd.setCursor(15-j+3+jjj+4+kkk+3+lll+4+mmm+3,1);
        lcd.print(rj);
        if(15-j+3+jjj+4+kkk+3+lll+4+mmm+3==5 || 15-j+3+jjj+4+kkk+3+lll+4+mmm==5 || 15-j+3+jjj+4+kkk+3+lll+4==5 || 15-j+3+jjj+4+kkk+3+lll==5 || 15-j+3+jjj+4+kkk+3==5 || 15-j+3+jjj+4+kkk==5 || 15-j+3+jjj+4==5 || 15-j+3+jjj==5 || 15-j+3==5 || 15-j==5){
          lcd.begin(16,2);
          lcd.setCursor(0,0);
          lcd.print("Game Over");
          t=900;
          delay(4000);
          xx=0;
          yy=0;
          ww=0;
          zz=1;
          q=0;
          qq=0;
          qqq=0;
          t=800;
          goto menu1;
        }

        j++;
        delay(200);
        if(j>=47){
          xx=8;
          yy=1;

          while(1){ //ステージ３の答え選び（通常時）
            int x=analogRead(Y_pin);
            int y=analogRead(X_pin);
            if(x>600){
              xx=xx-1;
            }
            else if(x<480){
              xx=xx+1;
            }
            else{
              xx=xx;
            }

            if(y<480){
              yy=yy-1;
            }
            else if(y>600){
              yy=yy+1;
            }
            else{
              yy=yy;
            }
            while(1){ //答えランダム配置設定（通常時）
              aa=random(3,13);
              if(aa!=4 && aa!=5 && aa!=7 && aa!=8 && aa!=10 && aa!=11){
                break;
              }
            }
            while(1){
              bb=random(3,13);
              if(bb!=4 && bb!=5 && bb!=7 && bb!=8 && bb!=10 && bb!=11 && bb!=aa){
                break;
              }
            }
            while(1){
              cc=random(3,13);
              if(cc!=4 && cc!=5 && cc!=7 && cc!=8 && cc!=10 && cc!=11 && cc!=aa && cc!=bb){
                break;
              }
            }
            while(1){
              dd=random(3,13);
              if(dd!=4 && dd!=5 && dd!=7 && dd!=8 && dd!=10 && dd!=11 && dd!=aa && dd!=bb && dd!=cc){
                break;
              }
            }
            while(1){
              aaa=random(-2,3);
              if(aaa!=0){
                break;
              }
            }
            while(1){
              bbb=random(-2,3);
              if(bbb!=0 && bbb!=aaa){
                break;
              }
            }
            while(1){
              ccc=random(-2,3);
              if(ccc!=0 && ccc!=aaa && ccc!=bbb){
                break;
              }
            }
            while(1){ //答え選択画面（通常時）
              int x=analogRead(Y_pin);
              int y=analogRead(X_pin);
              if(x>800){
                xx=xx-1;
              }
              else if(x<100){
                xx=xx+1;
              }
              else{
                xx=xx;
              }

              if(y<100){
                yy=yy-1;
              }
              else if(y>800){
                yy=yy+1;
              }
              else{
                yy=yy;
              }
              lcd.begin(16,2);
              lcd.setCursor(xx,yy);
              lcd.write(byte(0));
              lcd.setCursor(aa,0);
              lcd.print(ra+rb+rc+rd+re+rf+rg+rh+ri+rj);
              lcd.setCursor(bb,0);
              lcd.print(ra+rb+rc+rd+re+rf+rg+rh+ri+rj+aaa);
              lcd.setCursor(cc,0);
              lcd.print(ra+rb+rc+rd+re+rf+rg+rh+ri+rj+bbb);
              lcd.setCursor(dd,0);
              lcd.print(ra+rb+rc+rd+re+rf+rg+rh+ri+rj+ccc);
              delay(170);
              if((xx==aa || x==aa+1) && yy==0){
                lcd.begin(16,2);
                lcd.setCursor(0,0);
                lcd.print("Correct Answer");
                delay(2000);
                j=0;
                xx=0;
                yy=1;
                ww=0;
                zz=1;
                q++;
                if(q==3){
                  lcd.begin(16,2);
                  lcd.print("Game clear");
                  t=1000;
                  delay(10000);
                  q=0;
                  qq=0;
                  qqq=0;
                  t=800;
                  goto menu1;
                }
                goto stage33;
              }
              else if((xx==bb || xx==bb+1) && yy==0){
                lcd.begin(16,2);
                lcd.setCursor(0,0);
                lcd.print("Game Over");
                t=900;
                delay(4000);
                xx=0;
                yy=1;
                ww=0;
                zz=1;
                q=0;
                qq=0;
                qqq=0;
                t=800;
                goto menu1;
              }
              else if((xx==cc || xx==cc+1) && yy==0){
                lcd.begin(16,2);
                lcd.setCursor(0,0);
                lcd.print("Game Over");
                t=900;
                delay(4000);
                xx=0;
                yy=1;
                ww=0;
                zz=1;
                q=0;
                qq=0;
                qqq=0;
                t=800;
                goto menu1;
              }
              else if((xx==dd || xx==dd+1) && yy==0){
                lcd.begin(16,2);
                lcd.setCursor(0,0);
                lcd.print("Game Over");
                t=900;
                delay(4000);
                xx=0;
                yy=1;
                ww=0;
                zz=1;
                q=0;
                qq=0;
                qqq=0;
                t=800;
                goto menu1;
              }
            }
          }
          rrr=random(0,2);
          jjj=random(3,5);
          kkk=random(3,5);
          lll=random(3,5);
          mmm=random(3,5);
          nnn=random(0,2);
          ra=random(1,10);
          rb=random(1,10);
          rc=random(1,10);
          rd=random(1,10);
          re=random(1,10);
          rf=random(1,10);
          rg=random(1,10);
          rh=random(1,10);
          ri=random(1,10);
          rj=random(1,10);
        }
      lcd.print("t:  ");
      lcd.print(t);
      lcd.println("\n\n");
      if(p==0){
        xx=0;
        yy=1;
        ww=0;
        zz=1;
        q=0;
        qq=0;
        qqq=0;
        t=800;
        goto menu1;
      }
      }
      if(p==0){
        xx=0;
        yy=1;
        ww=0;
        zz=1;
        q=0;
        qq=0;
        qqq=0;
        t=800;
        goto menu1;
      }
    }
  }


  while(1){
   setting:
    randomSeed(analogRead(5));
    rz=random(2,5);
    randomSeed(analogRead(rz));
    rx = random(1,13);
    if(rx==1){
      rx=1;
      c=1;
      ry=14;
      t=600;
      goto play;
    }
    else if(rx==10){
      rx=10;
      ry=14;
      c=1;
      t=600;
      goto play;
    }
    else if(rx==11){
      rx=11;
      ry=3;
      c=1;
      t=600;
      goto play;
    }
    else if(rx==12){
      rx=12;
      ry=12;
      c=1;
      t=600;
      goto play;
    }
    else{
      goto setting;
    }
  }



  while(1){
    play:
  p=digitalRead(SW_pin);
  int rxx=analogRead(Y_pin);
  int ryy=analogRead(X_pin);


  if(rxx>800 && ryy<rxx && ryy>1020-rxx){ //移動指定
    rx=rx-1;
    b=0; //left
    s=s+1;
  }
  else if(rxx<200 && ryy>rxx && ryy<1020-rxx){
    rx=rx+1;
    b=1; //right
    s=s+1;
  }
  if(ryy<200 && ryy<rxx && ryy<1020-rxx){
    ry=ry-1;
    c=0; //up
    s=s+1;
  }
  else if(ryy>800 && ryy>1020-rxx && ryy>rxx){
    ry=ry+1;
    c=1; //down
    s=s+1;
  }
  else{
    ry=ry;
    rx=rx;
  }
  if(ry<=-1){
    ry=0;
    c=0;
    goto block1;
  }










  if(ry==0){ //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    if(rx==14 && b==1){
      rx=13;
      goto block1;
    }
    else if(rx==10 && b==0){
      rx=11;
      goto block1;
    }
    else if(rx==10 && b==1){
      rx=9;
      goto block1;
    }
    else if(rx==8 && b==0){
      rx=9;
      goto block1;
    }
    else if(rx==8 && b==1){
      rx=7;
      goto block1;
    }
    else if(rx==1 && b==0){
      rx=2;
      goto block1;
    }


    else{ //block1
      block1:
      lcd.begin(16,2);
      lcd.setCursor(rx,1-c);
      lcd.write(byte(0));
      lcd.setCursor(0,0);
      lcd.write(byte(6));
      lcd.setCursor(1,0);
      lcd.write(byte(6));
      lcd.setCursor(2,0);
      lcd.write(byte(6));
      lcd.setCursor(3,0);
      lcd.write(byte(6));
      lcd.setCursor(4,0);
      lcd.write(byte(6));
      lcd.setCursor(5,0);
      lcd.write(byte(6));
      lcd.setCursor(6,0);
      lcd.write(byte(6));
      lcd.setCursor(7,0);
      lcd.write(byte(6));
      lcd.setCursor(8,0);
      lcd.write(byte(6));
      lcd.setCursor(9,0);
      lcd.write(byte(6));
      lcd.setCursor(10,0);
      lcd.write(byte(6));
      lcd.setCursor(11,0);
      lcd.write(byte(6));
      lcd.setCursor(12,0);
      lcd.write(byte(6));
      lcd.setCursor(13,0);
      lcd.write(byte(6));
      lcd.setCursor(14,0);
      lcd.write(byte(6));
      lcd.setCursor(15,0);
      lcd.write(byte(6));
      lcd.setCursor(0,1);
      lcd.write(byte(6));
      lcd.setCursor(1,1);
      lcd.write(byte(6));
      lcd.setCursor(8,1);
      lcd.write(byte(6));
      lcd.setCursor(10,1);
      lcd.write(byte(6));
      lcd.setCursor(14,1);
      lcd.write(byte(6));
      lcd.setCursor(15,1);
      lcd.write(byte(6));
      }
  }
















  if(ry==1){ //----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    if(c==1 && rx==1){
      rx=2;
      goto block2;
    }
    else if(c==1 && rx==8 && b==1){
      rx=7;
      goto block2;
    }
    else if(c==1 && rx==8 && b==0){
      rx=9;
      goto block2;
    }
    else if(c==1 && rx==10 && b==1){
      rx=9;
      goto block2;
    }
    else if(c==1 && rx==10 && b==0){
      rx=11;
      goto block2;
    }
    else if(c==1 && rx==14){
      rx=13;
      goto block2;
    }
    else if(c==0 && rx==1){
      rx=2;
      goto block2;
    }
    else if(c==0 && rx==3){
      rx=2;
      goto block2;
    }
    else if(c==0 && rx==4){
      rx=5;
      goto block2;
    }
    else if(c==0 && rx==6 && b==1){
      rx=5;
      goto block2;
    }
    else if(c==0 && rx==6 && b==0){
      rx=7;
      goto block2;
    }
    else if(c==0 && rx==8 && b==1){
      rx=7;
      goto block2;
    }
    else if(c==0 && rx==8 && b==0){
      rx=9;
      goto block2;
    }
    else if(c==0 && rx==10 && b==1){
      rx=9;
      goto block2;
    }
    else if(c==0 && rx==10 && b==0){
      rx=11;
      goto block2;
    }
    else if(c==0 && rx==12){
      rx=11;
      goto block2;
    }
    else if(ryy<200 && ryy<rxx && ryy<1020-rxx && c==0 && rx==13){
      ry=2;
      goto block3;
    }


    else{ //block2
      block2:
      lcd.begin(16,2);
      lcd.setCursor(rx,1-c);
      lcd.write(byte(0));

      lcd.setCursor(0,1);
      lcd.write(byte(6));
      lcd.setCursor(1,1);
      lcd.write(byte(6));
      lcd.setCursor(3,1);
      lcd.write(byte(6));
      lcd.setCursor(4,1);
      lcd.write(byte(6));
      lcd.setCursor(6,1);
      lcd.write(byte(6));
      lcd.setCursor(8,1);
      lcd.write(byte(6));
      lcd.setCursor(10,1);
      lcd.write(byte(6));
      lcd.setCursor(12,1);
      lcd.write(byte(6));
      lcd.setCursor(13,1);
      lcd.write(byte(6));
      lcd.setCursor(14,1);
      lcd.write(byte(6));
      lcd.setCursor(15,1);
      lcd.write(byte(6));
      lcd.setCursor(0,0);
      lcd.write(byte(6));
      lcd.setCursor(1,0);
      lcd.write(byte(6));
      lcd.setCursor(8,0);
      lcd.write(byte(6));
      lcd.setCursor(10,0);
      lcd.write(byte(6));
      lcd.setCursor(14,0);
      lcd.write(byte(6));
      lcd.setCursor(15,0);
      lcd.write(byte(6));

    }
  }

  if(ry==2){ //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    if(c==1 && rx==1){
      rx=2;
      goto block3;
    }
    else if(c==1 && rx==3 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=2;
      goto block3;
    }
    else if(c==1 && rx==4 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=5;
      goto block3;
    }
    else if(c==1 && rx==6 && b==1 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=5;
      goto block3;
    }
    else if(c==1 && rx==6 && b==0 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=7;
      goto block3;
    }
    else if(c==1 && rx==8 && b==1 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=7;
      goto block3;
    }
    else if(c==1 && rx==8 && b==0 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=9;
      goto block3;
    }
    else if(c==1 && rx==10 && b==1 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=9;
      goto block3;
    }
    else if(c==1 && rx==10 && b==0 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=11;
      goto block3;
    }
    else if(c==1 && rx==12 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=11;
      goto block3;
    }
    else if(c==0 && rx==4 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=5;
      goto block3;
    }
    else if(c==0 && rx==6 && b==1 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=5;
      goto block3;
    }
    else if(c==0 && rx==6 && b==0 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=7;
      goto block3;
    }
    else if(c==0 && rx==8 && b==1 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=7;
      goto block3;
    }
    else if(c==0 && rx==8 && b==0 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=9;
      goto block3;
    }
    else if(c==0 && rx==10 && b==1 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=9;
      goto block3;
    }
    else if(c==0 && rx==10 && b==0 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=11;
      goto block3;
    }
    else if(c==0 && rx==12 && b==1 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=11;
      goto block3;
    }
    else if(c==0 && rx==12 && b==0 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=13;
      goto block3;
    }
    else if(c==0 && rx==14 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=13;
      goto block3;
    }
    else if(ryy>800 && ryy>1020-rxx && ryy>rxx && rx==3){ //----------------------------------
      ry=1;
      goto block2;
    }
    else if(ryy>800 && ryy>1020-rxx && ryy>rxx && rx==4){
      ry=1;
      goto block2;
    }
    else if(ryy>800 && ryy>1020-rxx && ryy>rxx && rx==6){
      ry=1;
      goto block2;
    }
    else if(ryy>800 && ryy>1020-rxx && ryy>rxx && rx==12){
      ry=1;
      goto block2;
    }
    else if(ryy>800 && ryy>1020-rxx && ryy>rxx && rx==13 && c==1){
      ry=1;
      goto block2;
    }
    else if((ryy<200 && ryy<rxx && ryy<1020-rxx) && (rx==1 || rx==2 || rx==3 || rx==4 || rx==12 || rx==14)){
      ry=3;
      goto block4;
    }


    else{ //block3
      block3:
      lcd.begin(16,2);
      lcd.setCursor(rx,1-c);
      lcd.write(byte(0));

      lcd.setCursor(0,0);
      lcd.write(byte(6));
      lcd.setCursor(1,0);
      lcd.write(byte(6));
      lcd.setCursor(3,0);
      lcd.write(byte(6));
      lcd.setCursor(4,0);
      lcd.write(byte(6));
      lcd.setCursor(6,0);
      lcd.write(byte(6));
      lcd.setCursor(8,0);
      lcd.write(byte(6));
      lcd.setCursor(10,0);
      lcd.write(byte(6));
      lcd.setCursor(12,0);
      lcd.write(byte(6));
      lcd.setCursor(13,0);
      lcd.write(byte(6));
      lcd.setCursor(14,0);
      lcd.write(byte(6));
      lcd.setCursor(15,0);
      lcd.write(byte(6));
      lcd.setCursor(0,1);
      lcd.write(byte(6));
      lcd.setCursor(1,1);
      lcd.write(byte(6));
      lcd.setCursor(2,1);
      lcd.write(byte(6));
      lcd.setCursor(3,1);
      lcd.write(byte(6));
      lcd.setCursor(4,1);
      lcd.write(byte(6));
      lcd.setCursor(6,1);
      lcd.write(byte(6));
      lcd.setCursor(8,1);
      lcd.write(byte(6));
      lcd.setCursor(10,1);
      lcd.write(byte(6));
      lcd.setCursor(12,1);
      lcd.write(byte(6));
      lcd.setCursor(14,1);
      lcd.write(byte(6));
      lcd.setCursor(15,1);
      lcd.write(byte(6));

    }
  }







  if(ry==3){ //------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    if(c==1 && rx==4 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=5;
      goto block4;
    }
    else if(c==1 && rx==6 && b==1 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=5;
      goto block4;
    }
    else if(c==1 && rx==6 && b==0 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=7;
      goto block4;
    }
    else if(c==1 && rx==8 && b==1 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=7;
      goto block4;
    }
    else if(c==1 && rx==8 && b==0 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=9;
      goto block4;
    }
    else if(c==1 && rx==10 && b==1 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=9;
      goto block4;
    }
    else if(c==1 && rx==10 && b==0 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=11;
      goto block4;
    }
    else if(c==1 && rx==12 && b==1 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=11;
      goto block4;
    }
    else if(c==1 && rx==12 && b==0 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=13;
      goto block4;
    }
    else if(c==1 && rx==14 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=13;
      goto block4;
    }
    else if(c==0 && rx==0 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=1;
      goto block4;
    }
    else if(c==0 && rx==6 && b==1 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=5;
      goto block4;
    }
    else if(c==0 && rx==6 && b==0 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=7;
      goto block4;
    }
    else if(c==0 && rx==8 && b==1 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=7;
      goto block4;
    }
    else if(c==0 && rx==8 && b==0 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=9;
      goto block4;
    }
    else if(c==0 && rx==10 && b==1 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=9;
      goto block4;
    }
    else if(c==0 && rx==10 && b==0 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=11;
      goto block4;
    }
    else if(c==0 && rx==15 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=14;
      goto block4;
    }
    else if(c==1 && rx==2 && ryy>800 && ryy>1020-rxx && ryy>rxx){ //--------------------------------
      ry=2;
      goto block3;
    }


    else{ //block4
      block4:
      lcd.begin(16,2);
      lcd.setCursor(rx,1-c);
      lcd.write(byte(0));

      lcd.setCursor(0,1);
      lcd.write(byte(6));
      lcd.setCursor(6,1);
      lcd.write(byte(6));
      lcd.setCursor(8,1);
      lcd.write(byte(6));
      lcd.setCursor(10,1);
      lcd.write(byte(6));
      lcd.setCursor(15,1);
      lcd.write(byte(6));
      lcd.setCursor(0,0);
      lcd.write(byte(6));
      lcd.setCursor(1,0);
      lcd.write(byte(6));
      lcd.setCursor(2,0);
      lcd.write(byte(6));
      lcd.setCursor(3,0);
      lcd.write(byte(6));
      lcd.setCursor(4,0);
      lcd.write(byte(6));
      lcd.setCursor(6,0);
      lcd.write(byte(6));
      lcd.setCursor(8,0);
      lcd.write(byte(6));
      lcd.setCursor(10,0);
      lcd.write(byte(6));
      lcd.setCursor(12,0);
      lcd.write(byte(6));
      lcd.setCursor(14,0);
      lcd.write(byte(6));
      lcd.setCursor(15,0);
      lcd.write(byte(6));

    }
  }




  if(ry==4){ //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    if(c==1 && rx==0 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=1;
      goto block5;
    }
    else if(c==1 && rx==6 && b==1 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=5;
      goto block5;
    }
    else if(c==1 && rx==6 && b==0 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=7;
      goto block5;
    }
    else if(c==1 && rx==8 && b==1 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=7;
      goto block5;
    }
    else if(c==1 && rx==8 && b==0 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=9;
      goto block5;
    }
    else if(c==1 && rx==10 && b==1 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=9;
      goto block5;
    }
    else if(c==1 && rx==10 && b==0 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=11;
      goto block5;
    }
    else if(c==1 && rx==15 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=14;
      goto block5;
    }
    else if(c==0 && rx==0 && rxx<800 && ryy<rxx && ryy>1020-rxx){
      rx=1;
      goto block5;
    }
    else if(c==0 && rx==2 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=1;
      goto block5;
    }
    else if(c==0 && rx==6 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=7;
      goto block5;
    }
    else if(c==0 && rx==8 && b==1 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=7;
      goto block5;
    }
    else if(c==0 && rx==8 && b==0 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=9;
      goto block5;
    }
    else if(c==0 && rx==10 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=9;
      goto block5;
    }
    else if(c==0 && rx==13 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=14;
      goto block5;
    }
    else if(c==0 && rx==15 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=14;
      goto block5;
    }
    else if((c==0 && ryy<200 && ryy<rxx && ryy<1020-rxx) && (rx==2 || rx==3 || rx==4 || rx==6 || rx==8 || rx==10 || rx==11 || rx==12 || rx==13)){
      ry=5;
      goto block6;
    }

    else{ //block5
      block5:
      lcd.begin(16,2);
      lcd.setCursor(rx,1-c);
      lcd.write(byte(0));

      lcd.setCursor(0,0);
      lcd.write(byte(6));
      lcd.setCursor(6,0);
      lcd.write(byte(6));
      lcd.setCursor(8,0);
      lcd.write(byte(6));
      lcd.setCursor(10,0);
      lcd.write(byte(6));
      lcd.setCursor(15,0);
      lcd.write(byte(6));
      lcd.setCursor(0,1);
      lcd.write(byte(6));
      lcd.setCursor(2,1);
      lcd.write(byte(6));
      lcd.setCursor(3,1);
      lcd.write(byte(6));
      lcd.setCursor(4,1);
      lcd.write(byte(6));
      lcd.setCursor(5,1);
      lcd.write(byte(6));
      lcd.setCursor(6,1);
      lcd.write(byte(6));
      lcd.setCursor(8,1);
      lcd.write(byte(6));
      lcd.setCursor(10,1);
      lcd.write(byte(6));
      lcd.setCursor(11,1);
      lcd.write(byte(6));
      lcd.setCursor(12,1);
      lcd.write(byte(6));
      lcd.setCursor(13,1);
      lcd.write(byte(6));
      lcd.setCursor(15,1);
      lcd.write(byte(6));

    }
  }





  if(ry==5){ //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    if(c==1 && rx==0 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=1;
      goto block6;
    }
    else if(c==1 && rx==2 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=1;
      goto block6;
    }
    else if(c==1 && rx==6 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=7;
      goto block6;
    }
    else if(c==1 && rx==8 && b==1 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=7;
      goto block6;
    }
    else if(c==1 && rx==8 && b==0 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=9;
      goto block6;
    }
    else if(c==1 && rx==10 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=9;
      goto block6;
    }
    else if(c==1 && rx==13 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=14;
      goto block6;
    }
    else if(c==1 && rx==15 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=14;
      goto block6;
    }
    else if(c==0 && rx==0 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=1;
      goto block6;
    }
    else if(c==0 && rx==5 && b==1 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=4;
      goto block6;
    }
    else if(c==0 && rx==5 && b==0 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=6;
      goto block6;
    }
    else if(c==0 && rx==15 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=14;
      goto block6;
    }
    else if((c==1 && ryy>800 && ryy>1020-rxx && ryy>rxx) && (rx==2 || rx==3 || rx==4 || rx==5 || rx==11 || rx==12 || rx==13)){
      ry=4;
      goto block5;
    }

    else{ //block6
      block6:
      lcd.begin(16,2);
      lcd.setCursor(rx,1-c);
      lcd.write(byte(0));

      lcd.setCursor(0,1);
      lcd.write(byte(6));
      lcd.setCursor(5,1);
      lcd.write(byte(6));
      lcd.setCursor(15,1);
      lcd.write(byte(6));
      lcd.setCursor(0,0);
      lcd.write(byte(6));
      lcd.setCursor(2,0);
      lcd.write(byte(6));
      lcd.setCursor(3,0);
      lcd.write(byte(6));
      lcd.setCursor(4,0);
      lcd.write(byte(6));
      lcd.setCursor(5,0);
      lcd.write(byte(6));
      lcd.setCursor(6,0);
      lcd.write(byte(6));
      lcd.setCursor(8,0);
      lcd.write(byte(6));
      lcd.setCursor(10,0);
      lcd.write(byte(6));
      lcd.setCursor(11,0);
      lcd.write(byte(6));
      lcd.setCursor(12,0);
      lcd.write(byte(6));
      lcd.setCursor(13,0);
      lcd.write(byte(6));
      lcd.setCursor(15,0);
      lcd.write(byte(6));

    }
  }



  if(ry==6){ //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    if(c==1 && rx==0 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=1;
      goto block7;
    }
    else if(c==1 && rx==5 && b==1 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=4;
      goto block7;
    }
    else if(c==1 && rx==5 && b==0 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=6;
      goto block7;
    }
    else if(c==1 && rx==15 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=14;
      goto block7;
    }
    else if(c==0 && rx==0 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=1;
      goto block7;
    }
    else if(c==0 && rx==2 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=1;
      goto block7;
    }
    else if(c==0 && rx==3 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=4;
      goto block7;
    }
    else if(c==0 && rx==5 && b==1 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=4;
      goto block7;
    }
    else if(c==0 && rx==5 && b==0 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=6;
      goto block7;
    }
    else if(c==0 && rx==7 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=6;
      goto block7;
    }
    else if(c==0 && rx==13 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=14;
      goto block7;
    }
    else if(c==0 && rx==15 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=14;
      goto block7;
    }
    else if((c==0 && ryy<200 && ryy<rxx && ryy<1020-rxx) && (rx==2 || rx==3 || rx==9 || rx==10 || rx==11 || rx==12 || rx==13)){
      ry=7;
      goto block8;
    }

    else{ //block7
      block7:
      lcd.begin(16,2);
      lcd.setCursor(rx,1-c);
      lcd.write(byte(0));

      lcd.setCursor(0,0);
      lcd.write(byte(6));
      lcd.setCursor(5,0);
      lcd.write(byte(6));
      lcd.setCursor(15,0);
      lcd.write(byte(6));
      lcd.setCursor(0,1);
      lcd.write(byte(6));
      lcd.setCursor(2,1);
      lcd.write(byte(6));
      lcd.setCursor(3,1);
      lcd.write(byte(6));
      lcd.setCursor(5,1);
      lcd.write(byte(6));
      lcd.setCursor(7,1);
      lcd.write(byte(6));
      lcd.setCursor(8,1);
      lcd.write(byte(6));
      lcd.setCursor(9,1);
      lcd.write(byte(6));
      lcd.setCursor(10,1);
      lcd.write(byte(6));
      lcd.setCursor(11,1);
      lcd.write(byte(6));
      lcd.setCursor(12,1);
      lcd.write(byte(6));
      lcd.setCursor(13,1);
      lcd.write(byte(6));
      lcd.setCursor(15,1);
      lcd.write(byte(6));

    }
  }




  if(ry==7){ //------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    if(c==1 && rx==0 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=1;
      goto block8;
    }
    else if(c==1 && rx==2 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=1;
      goto block8;
    }
    else if(c==1 && rx==3 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=4;
      goto block8;
    }
    else if(c==1 && rx==5 && b==1 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=4;
      goto block8;
    }
    else if(c==1 && rx==5 && b==0 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=6;
      goto block8;
    }
    else if(c==1 && rx==7 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=6;
      goto block8;
    }
    else if(c==1 && rx==13 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=14;
      goto block8;
    }
    else if(c==1 && rx==15 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=14;
      goto block8;
    }
    else if(c==0 && rx==0 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=1;
      goto block8;
    }
    else if(c==0 && rx==4 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=3;
      goto block8;
    }
    else if(c==0 && rx==8 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=9;
      goto block8;
    }
    else if(c==0 && rx==15 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=14;
      goto block8;
    }
    else if((c==1 && ryy>800 && ryy>1020-rxx && ryy>rxx) && (rx==2 || rx==3 || rx==7 || rx==8 || rx==9 || rx==10 || rx==11 || rx==12 || rx==13)){
      ry=6;
      goto block7;
    }
    else if((c==0 && ryy<200 && ryy<rxx && ryy<1020-rxx) && (rx==4 || rx==6 || rx==7)){
      ry=8;
      goto block9;
    }
    else if(c==0 && rx==3){
      while(1){
        p = digitalRead(SW_pin);
        ss=42000/s;
        lcd.begin(16,2);
        lcd.setCursor(0,0);
        lcd.print("Game clear");
        t=1000;
        lcd.setCursor(0,1);
        lcd.print("score");
        lcd.setCursor(6,1);
        lcd.print(ss);
        delay(170);
        if(p==0){
          xx=0;
          yy=0;
          ww=0;
          zz=1;
          s=0;
          q=0;
          qq=0;
          qqq=0;

          goto menu1;
        }
      }
    }

    else{ //block8
      block8:
      lcd.begin(16,2);
      lcd.setCursor(rx,1-c);
      lcd.write(byte(0));

      lcd.setCursor(0,1);
      lcd.write(byte(6));
      lcd.setCursor(3,1);
      lcd.write(byte(0));
      lcd.setCursor(4,1);
      lcd.write(byte(6));
      lcd.setCursor(5,1);
      lcd.write(byte(6));
      lcd.setCursor(6,1);
      lcd.write(byte(6));
      lcd.setCursor(7,1);
      lcd.write(byte(6));
      lcd.setCursor(8,1);
      lcd.write(byte(6));
      lcd.setCursor(15,1);
      lcd.write(byte(6));
      lcd.setCursor(0,0);
      lcd.write(byte(6));
      lcd.setCursor(2,0);
      lcd.write(byte(6));
      lcd.setCursor(3,0);
      lcd.write(byte(6));
      lcd.setCursor(5,0);
      lcd.write(byte(6));
      lcd.setCursor(7,0);
      lcd.write(byte(6));
      lcd.setCursor(8,0);
      lcd.write(byte(6));
      lcd.setCursor(9,0);
      lcd.write(byte(6));
      lcd.setCursor(10,0);
      lcd.write(byte(6));
      lcd.setCursor(11,0);
      lcd.write(byte(6));
      lcd.setCursor(12,0);
      lcd.write(byte(6));
      lcd.setCursor(13,0);
      lcd.write(byte(6));
      lcd.setCursor(15,0);
      lcd.write(byte(6));

    }
  }

  if(ry==8){ //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    if(c==1 && rx==0 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=1;
      goto block9;
    }
    else if(c==1 && rx==4 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=3;
      goto block9;
    }
    else if(c==1 && rx==8 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=9;
      goto block9;
    }
    else if(c==1 && rx==15 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=14;
      goto block9;
    }
    else if(c==0 && rx==3 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=4;
      goto block9;
    }
    else if(c==0 && rx==5 && b==1 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=4;
      goto block9;
    }
    else if(c==0 && rx==5 && b==0 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=6;
      goto block9;
    }
    else if(c==0 && rx==8 && b==1 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=7;
      goto block9;
    }
    else if(c==0 && rx==8 && b==0 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=9;
      goto block9;
    }
    else if(c==0 && rx==10 && b==1 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=9;
      goto block9;
    }
    else if(c==0 && rx==10 && b==0 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=11;
      goto block9;
    }
    else if(c==0 && rx==12 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=11;
      goto block9;
    }
    else if((c==1 && ryy>800 && ryy>1020-rxx && ryy>rxx) && (rx==4 || rx==6)){
      ry=7;
      goto block8;
    }
    else if((c==0 && ryy<200 && ryy<rxx && ryy<1020-rxx) && (rx==8 || rx==12 || rx==13)){
      ry=9;
      goto block10;
    }
    if(c==1 && rx==3){

        p = digitalRead(SW_pin);
        ss=42000/s;
        lcd.begin(16,2);
        lcd.setCursor(0,0);
        lcd.print("Game clear");
        t=1000;
        lcd.setCursor(0,1);
        lcd.print("score");
        lcd.setCursor(6,1);
        lcd.print(ss);
        delay(10000);
        xx=0;
        yy=0;
        ww=0;
        zz=1;
        s=0;
        customMODE=0;
        goto custom;
        if(p==0){
          xx=0;
          yy=0;
          ww=0;
          zz=1;
          s=0;
          t=800;
          goto custom;
        }

    }

    else{ //block9
      block9:
      lcd.begin(16,2);
      lcd.setCursor(rx,1-c);
      lcd.write(byte(0));

      lcd.setCursor(0,0);
      lcd.write(byte(6));
      lcd.setCursor(3,0);
      lcd.write(byte(0));
      lcd.setCursor(4,0);
      lcd.write(byte(6));
      lcd.setCursor(5,0);
      lcd.write(byte(6));
      lcd.setCursor(6,0);
      lcd.write(byte(6));
      lcd.setCursor(7,0);
      lcd.write(byte(6));
      lcd.setCursor(8,0);
      lcd.write(byte(6));
      lcd.setCursor(15,0);
      lcd.write(byte(6));
      lcd.setCursor(0,1);
      lcd.write(byte(6));
      lcd.setCursor(1,1);
      lcd.write(byte(6));
      lcd.setCursor(2,1);
      lcd.write(byte(6));
      lcd.setCursor(3,1);
      lcd.write(byte(6));
      lcd.setCursor(5,1);
      lcd.write(byte(6));
      lcd.setCursor(8,1);
      lcd.write(byte(6));
      lcd.setCursor(10,1);
      lcd.write(byte(6));
      lcd.setCursor(12,1);
      lcd.write(byte(6));
      lcd.setCursor(13,1);
      lcd.write(byte(6));
      lcd.setCursor(14,1);
      lcd.write(byte(6));
      lcd.setCursor(15,1);
      lcd.write(byte(6));


    }
  }

  if(ry==9){ //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    if(c==1 && rx==3 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=4;
      goto block10;
    }
    else if(c==1 && rx==5 && b==1 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=4;
      goto block10;
    }
    else if(c==1 && rx==5 && b==0 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=6;
      goto block10;
    }
    else if(c==1 && rx==8 && b==1 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=7;
      goto block10;
    }
    else if(c==1 && rx==8 && b==0 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=9;
      goto block10;
    }
    else if(c==1 && rx==10 && b==1 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=9;
      goto block10;
    }
    else if(c==1 && rx==10 && b==0 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=11;
      goto block10;
    }
    else if(c==1 && rx==12 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=11;
      goto block10;
    }
    else if(c==0 && rx==3 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=4;
      goto block10;
    }
    else if(c==0 && rx==5 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=4;
      goto block10;
    }
    else if(c==0 && rx==6 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=7;
      goto block10;
    }
    else if(c==0 && rx==10 && b==1 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=9;
      goto block10;
    }
    else if(c==0 && rx==10 && b==0 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=11;
      goto block10;
    }
    else if(c==0 && rx==14 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=13;
      goto block10;
    }
    else if((c==1 && ryy>800 && ryy>1020-rxx && ryy>rxx) && (rx==1 || rx==2 || rx==3 || rx==10 || rx==12 || rx==13 || rx==14)){
      ry=8;
      goto block9;
    }
    else if((c==0 && ryy<200 && ryy<rxx && ryy<1020-rxx) && (rx==1 || rx==2 || rx==3 || rx==6 || rx==5 || rx==14)){
      ry=10;
      goto block11;
    }

    else{ //block10
      block10:
      lcd.begin(16,2);
      lcd.setCursor(rx,1-c);
      lcd.write(byte(0));

      lcd.setCursor(0,1);
      lcd.write(byte(6));
      lcd.setCursor(1,1);
      lcd.write(byte(6));
      lcd.setCursor(2,1);
      lcd.write(byte(6));
      lcd.setCursor(3,1);
      lcd.write(byte(6));
      lcd.setCursor(5,1);
      lcd.write(byte(6));
      lcd.setCursor(6,1);
      lcd.write(byte(6));
      lcd.setCursor(10,1);
      lcd.write(byte(6));
      lcd.setCursor(14,1);
      lcd.write(byte(6));
      lcd.setCursor(15,1);
      lcd.write(byte(6));
      lcd.setCursor(0,0);
      lcd.write(byte(6));
      lcd.setCursor(1,0);
      lcd.write(byte(6));
      lcd.setCursor(2,0);
      lcd.write(byte(6));
      lcd.setCursor(3,0);
      lcd.write(byte(6));
      lcd.setCursor(5,0);
      lcd.write(byte(6));
      lcd.setCursor(8,0);
      lcd.write(byte(6));
      lcd.setCursor(10,0);
      lcd.write(byte(6));
      lcd.setCursor(12,0);
      lcd.write(byte(6));
      lcd.setCursor(13,0);
      lcd.write(byte(6));
      lcd.setCursor(14,0);
      lcd.write(byte(6));
      lcd.setCursor(15,0);
      lcd.write(byte(6));

    }
  }



  if(ry==10){ //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    if(c==1 && rx==3 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=4;
      goto block11;
    }
    else if(c==1 && rx==5 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=4;
      goto block11;
    }
    else if(c==1 && rx==6 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=7;
      goto block11;
    }
    else if(c==1 && rx==10 && b==1 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=9;
      goto block11;
    }
    else if(c==1 && rx==10 && b==0 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=11;
      goto block11;
    }
    else if(c==1 && rx==14 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=13;
      goto block11;
    }
    else if(c==0 && rx==0 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=1;
      goto block11;
    }
    else if(c==0 && rx==7 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=6;
      goto block11;
    }
    else if(c==0 && rx==8 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=9;
      goto block11;
    }
    else if(c==0 && rx==10 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=9;
      goto block11;
    }
    else if(c==0 && rx==13 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=14;
      goto block11;
    }
    else if(c==0 && rx==15 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=14;
      goto block11;
    }
    else if(c==1 && ryy>800 && ryy>1020-rxx && ryy>rxx && rx==6){
      ry=9;
      goto block10;
    }
    else if((c==0 && ryy<200 && ryy<rxx && ryy<1020-rxx) && (rx==7 || rx==8 || rx==11 || rx==12 || rx==13)){
      ry=11;
      goto block12;
    }

    else{ //block11
      block11:
      lcd.begin(16,2);
      lcd.setCursor(rx,1-c);
      lcd.write(byte(0));

      lcd.setCursor(0,0);
      lcd.write(byte(6));
      lcd.setCursor(1,0);
      lcd.write(byte(6));
      lcd.setCursor(2,0);
      lcd.write(byte(6));
      lcd.setCursor(3,0);
      lcd.write(byte(6));
      lcd.setCursor(5,0);
      lcd.write(byte(6));
      lcd.setCursor(6,0);
      lcd.write(byte(6));
      lcd.setCursor(10,0);
      lcd.write(byte(6));
      lcd.setCursor(14,0);
      lcd.write(byte(6));
      lcd.setCursor(15,0);
      lcd.write(byte(6));
      lcd.setCursor(0,1);
      lcd.write(byte(6));
      lcd.setCursor(7,1);
      lcd.write(byte(6));
      lcd.setCursor(8,1);
      lcd.write(byte(6));
      lcd.setCursor(10,1);
      lcd.write(byte(6));
      lcd.setCursor(11,1);
      lcd.write(byte(6));
      lcd.setCursor(12,1);
      lcd.write(byte(6));
      lcd.setCursor(13,1);
      lcd.write(byte(6));
      lcd.setCursor(15,1);
      lcd.write(byte(6));

    }
  }



  if(ry==11){ //----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    if(c==1 && rx==0 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=1;
      goto block12;
    }
    else if(c==1 && rx==7 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=6;
      goto block12;
    }
    else if(c==1 && rx==8 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=9;
      goto block12;
    }
    else if(c==1 && rx==10 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=9;
      goto block12;
    }
    else if(c==1 && rx==13 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=14;
      goto block12;
    }
    else if(c==1 && rx==15 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=14;
      goto block12;
    }
    else if(c==0 && rx==0 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=1;
      goto block12;
    }
    else if(c==0 && rx==2 && b==1 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=1;
      goto block12;
    }
    else if(c==0 && rx==2 && b==0 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=3;
      goto block12;
    }
    else if(c==0 && rx==4 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=3;
      goto block12;
    }
    else if(c==0 && rx==5 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=6;
      goto block12;
    }
    else if(c==0 && rx==10 && b==1 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=9;
      goto block12;
    }
    else if(c==0 && rx==10 && b==0 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=11;
      goto block12;
    }
    else if(c==0 && rx==15 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=14;
      goto block12;
    }
    else if((c==1 && ryy>800 && ryy>1020-rxx && ryy>rxx) && (rx==7 || rx==8 || rx==11 || rx==12 || rx==13)){
      ry=10;
      goto block11;
    }

    else{ //block12
      block12:
      lcd.begin(16,2);
      lcd.setCursor(rx,1-c);
      lcd.write(byte(0));

      lcd.setCursor(0,1);
      lcd.write(byte(6));
      lcd.setCursor(2,1);
      lcd.write(byte(6));
      lcd.setCursor(2,1);
      lcd.write(byte(6));
      lcd.setCursor(4,1);
      lcd.write(byte(6));
      lcd.setCursor(5,1);
      lcd.write(byte(6));
      lcd.setCursor(10,1);
      lcd.write(byte(6));
      lcd.setCursor(10,1);
      lcd.write(byte(6));
      lcd.setCursor(15,1);
      lcd.write(byte(6));
      lcd.setCursor(0,0);
      lcd.write(byte(6));
      lcd.setCursor(7,0);
      lcd.write(byte(6));
      lcd.setCursor(8,0);
      lcd.write(byte(6));
      lcd.setCursor(10,0);
      lcd.write(byte(6));
      lcd.setCursor(11,0);
      lcd.write(byte(6));
      lcd.setCursor(12,0);
      lcd.write(byte(6));
      lcd.setCursor(13,0);
      lcd.write(byte(6));
      lcd.setCursor(15,0);
      lcd.write(byte(6));

    }
  }



  if(ry==12){ //----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    if(c==1 && rx==0 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=1;
      goto block13;
    }
    else if(c==1 && rx==2 && b==1 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=0;
      goto block13;
    }
    else if(c==1 && rx==2 && b==0 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=3;
      goto block13;
    }
    else if(c==1 && rx==4 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=3;
      goto block13;
    }
    else if(c==1 && rx==5 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=6;
      goto block13;
    }
    else if(c==1 && rx==10 && b==1 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=9;
      goto block13;
    }
    else if(c==1 && rx==10 && b==0 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=11;
      goto block13;
    }
    else if(c==1 && rx==15 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=14;
      goto block13;
    }
    else if(c==0 && rx==0 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=1;
      goto block13;
    }
    else if(c==0 && rx==2 && b==1 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=1;
      goto block13;
    }
    else if(c==0 && rx==2 && b==0 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=3;
      goto block13;
    }
    else if(c==0 && rx==4 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=3;
      goto block13;
    }
    else if(c==0 && rx==5 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=6;
      goto block13;
    }
    else if(c==0 && rx==7 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=6;
      goto block13;
    }
    else if(c==0 && rx==10 && rxx>800 && ryy<rxx && ryy>1020-rxx){
      rx=11;
      goto block13;
    }
    else if(c==0 && rx==12 && rxx<200 && ryy>rxx && ryy<1020-rxx){
      rx=11;
      goto block13;
    }
    else if((c==1 && ryy>800 && ryy>1020-rxx && ryy>rxx) && (rx==2 || rx==4 || rx==5)){
      ry=11;
      goto block12;
    }
    else if((c==0 && ryy<200 && ryy<rxx && ryy<1020-rxx) && (rx==4 || rx==7 || rx==8 || rx==9 || rx==10 || rx==12 || rx==13 || rx==14)){
      ry=13;
      goto block14;
    }

    else{ //block13
      block13:
      lcd.begin(16,2);
      lcd.setCursor(rx,1-c);
      lcd.write(byte(0));

      lcd.setCursor(0,0);
      lcd.write(byte(6));
      lcd.setCursor(2,0);
      lcd.write(byte(6));
      lcd.setCursor(2,0);
      lcd.write(byte(6));
      lcd.setCursor(4,0);
      lcd.write(byte(6));
      lcd.setCursor(5,0);
      lcd.write(byte(6));
      lcd.setCursor(10,0);
      lcd.write(byte(6));
      lcd.setCursor(10,0);
      lcd.write(byte(6));
      lcd.setCursor(15,0);
      lcd.write(byte(6));
      lcd.setCursor(0,1);
      lcd.write(byte(6));
      lcd.setCursor(2,1);
      lcd.write(byte(6));
      lcd.setCursor(4,1);
      lcd.write(byte(6));
      lcd.setCursor(5,1);
      lcd.write(byte(6));
      lcd.setCursor(7,1);
      lcd.write(byte(6));
      lcd.setCursor(8,1);
      lcd.write(byte(6));
      lcd.setCursor(9,1);
      lcd.write(byte(6));
      lcd.setCursor(10,1);
      lcd.write(byte(6));
      lcd.setCursor(12,1);
      lcd.write(byte(6));
      lcd.setCursor(13,1);
      lcd.write(byte(6));
      lcd.setCursor(14,1);
      lcd.write(byte(6));
      lcd.setCursor(15,1);
      lcd.write(byte(6));

    }
  }



  if(ry==13){ //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

   if(c==1 && rx==0 && rxx>800 && ryy<rxx && ryy>1020-rxx){
    rx=1;
    goto block14;
   }
   else if(c==1 && rx==2 && b==1 && rxx<200 && ryy>rxx && ryy<1020-rxx){
    rx=1;
    goto block14;
   }
   else if(c==1 && rx==2 && b==0 && rxx>800 && ryy<rxx && ryy>1020-rxx){
    rx=3;
    goto block14;
   }
   else if(c==1 && rx==4 && rxx<200 && ryy>rxx && ryy<1020-rxx){
    rx=3;
    goto block14;
   }
   else if(c==1 && rx==5 && rxx>800 && ryy<rxx && ryy>1020-rxx){
    rx=6;
    goto block14;
   }
   else if(c==1 && rx==7 && rxx<200 && ryy>rxx && ryy<1020-rxx){
    rx=6;
    goto block14;
   }
   else if(c==1 && rx==10 && rxx>800 && ryy<rxx && ryy>1020-rxx){
    rx=11;
    goto block14;
   }
   else if(c==1 && rx==12 && rxx<200 && ryy>rxx && ryy<1020-rxx){
    rx=11;
    goto block14;
   }
   else if(c==0 && rx==0 && rxx>800 && ryy<rxx && ryy>1020-rxx){
    rx=1;
    goto block14;
   }
   else if(c==0 && rx==2 && b==1 && rxx<200 && ryy>rxx && ryy<1020-rxx){
    rx=1;
    goto block14;
   }
   else if(c==0 && rx==2 && b==0 && rxx>800 && ryy<rxx && ryy>1020-rxx){
    rx=3;
    goto block14;
   }
   else if(c==0 && rx==5 && b==1 && rxx<200 && ryy>rxx && ryy<1020-rxx){
    rx=4;
    goto block14;
   }
   else if(c==0 && rx==5 && b==0 && rxx>800 && ryy<rxx && ryy>1020-rxx){
    rx=6;
    goto block14;
   }
   else if(c==0 && rx==15 && rxx<200 && ryy>rxx && ryy<1020-rxx){
    rx=14;
    goto block14;
   }
   else if((c==1 && ryy>800 && ryy>1020-rxx && ryy>rxx) && (rx==7 || rx==8 || rx==9 || rx==12 || rx==13 || rx==14)){
    ry=12;
    goto block13;
   }

   else{ //block14
      block14:
      lcd.begin(16,2);
      lcd.setCursor(rx,1-c);
      lcd.write(byte(0));

      lcd.setCursor(0,1);
      lcd.write(byte(6));
      lcd.setCursor(2,1);
      lcd.write(byte(6));
      lcd.setCursor(5,1);
      lcd.write(byte(6));
      lcd.setCursor(15,1);
      lcd.write(byte(6));
      lcd.setCursor(0,0);
      lcd.write(byte(6));
      lcd.setCursor(2,0);
      lcd.write(byte(6));
      lcd.setCursor(4,0);
      lcd.write(byte(6));
      lcd.setCursor(5,0);
      lcd.write(byte(6));
      lcd.setCursor(7,0);
      lcd.write(byte(6));
      lcd.setCursor(8,0);
      lcd.write(byte(6));
      lcd.setCursor(9,0);
      lcd.write(byte(6));
      lcd.setCursor(10,0);
      lcd.write(byte(6));
      lcd.setCursor(12,0);
      lcd.write(byte(6));
      lcd.setCursor(13,0);
      lcd.write(byte(6));
      lcd.setCursor(14,0);
      lcd.write(byte(6));
      lcd.setCursor(15,0);
      lcd.write(byte(6));

    }
  }


  if(ry==14){ //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    if(c==1 && rx==0){
      rx=1;
      goto block15;
    }
    else if(c==1 && rx==2 && b==1){
      rx=1;
      goto block15;
    }
    else if(c==1 && rx==2 && b==0){
      rx=3;
      goto block15;
    }
    else if(c==1 && rx==5 && b==1){
      rx=4;
      goto block15;
    }
    else if(c==1 && rx==5 && b==0){
      rx=6;
      goto block15;
    }
    else if(c==1 && rx==15){
      rx=14;
      goto block15;
    }
    else if(c==0){
      c==1;
      goto block15;
    }

    else{ //block15
      block15:
      lcd.begin(16,2);
      lcd.setCursor(rx,1-c);
      lcd.write(byte(0));

      lcd.setCursor(0,0);
      lcd.write(byte(6));
      lcd.setCursor(2,0);
      lcd.write(byte(6));
      lcd.setCursor(5,0);
      lcd.write(byte(6));
      lcd.setCursor(15,0);
      lcd.write(byte(6));
      lcd.setCursor(0,1);
      lcd.write(byte(6));
      lcd.setCursor(1,1);
      lcd.write(byte(6));
      lcd.setCursor(2,1);
      lcd.write(byte(6));
      lcd.setCursor(3,1);
      lcd.write(byte(6));
      lcd.setCursor(4,1);
      lcd.write(byte(6));
      lcd.setCursor(5,1);
      lcd.write(byte(6));
      lcd.setCursor(6,1);
      lcd.write(byte(6));
      lcd.setCursor(7,1);
      lcd.write(byte(6));
      lcd.setCursor(8,1);
      lcd.write(byte(6));
      lcd.setCursor(9,1);
      lcd.write(byte(6));
      lcd.setCursor(10,1);
      lcd.write(byte(6));
      lcd.setCursor(11,1);
      lcd.write(byte(6));
      lcd.setCursor(12,1);
      lcd.write(byte(6));
      lcd.setCursor(13,1);
      lcd.write(byte(6));
      lcd.setCursor(14,1);
      lcd.write(byte(6));
      lcd.setCursor(15,1);
      lcd.write(byte(6));



    }
  }
  else if(ry>=15){ //-------------------------------------------------------------------------------------------------------------------------------------------------------------------
    ry=14;
    c==1;
    goto block15;
  }


  if(p==0){
    xx=0;
    yy=2;
    ww=0;
    zz=1;

    q=0;
    qq=0;
    qqq=0;
    goto menu1;
  }
  Serial.print("c ");
  Serial.print(c);
  Serial.print("\n");
  Serial.print("b ");
  Serial.print(b);
  Serial.print("\n");
  Serial.print("rx ");
  Serial.print(rx);
  Serial.print("\n");
  Serial.print("ry ");
  Serial.print(ry);
  Serial.print("\n");
  Serial.print("rxx ");
  Serial.print(rxx);
  Serial.print("\n");
  Serial.print("ryy ");
  Serial.print(ryy);
  Serial.print("\n");
  Serial.print("s ");
  Serial.print(s);
  Serial.println("\n\n");
  delay(200);

}




while(1){
  startpoint:
  //=============================================キャラ設定============================================================================================キャラ設定
  read_x = analogRead(Y_pin);
  read_y = analogRead(X_pin);
  read_SW = digitalRead(SW_pin);
  read_button = digitalRead(BUTTON);
  if(read_x<100){
    x = x + 1;
  }
  else if(read_x>950){
    x = x - 1;
  }
  lcd.begin(16,2);
  lcd.setCursor(x,rank);
  lcd.write(byte(i));
  if(x<0){
    x=x+1;
  }
  else if(x>15){
    x=x-1;
  }
  //===============================================攻撃設定=============================================================================================攻撃設定
  if(j==1 && read_x<100){
    side=1;
  }
  else if(j==1 && read_x>950){
    side=0;
  }
  if(k==1 && read_x<100){
    side2=1;
  }
  else if(k==1 && read_x>950){
    side2=0;
  }
  if(j==1 && rank==1){
    atack_rank=1;
  }
  else if(j==1 && rank==0){
    atack_rank=0;
  }
  if(k==1 && rank==1){
    atack2_rank=1;
  }
  else if(k==1 && rank==0){
    atack2_rank=0;
  }

  if(read_button==1){
    atack=1;
  }

  if(atack==1){
    j=j+2;
    atack_x=x;
    if(side==1){
      lcd.setCursor(atack_x+j-2,atack_rank);
      lcd.write(byte(12));
      if(atack_x+j-2>15){
        atack=0;
        j=1;
      }
    }
    else if(side==0){
      lcd.setCursor(atack_x-j+2,atack_rank);
      lcd.write(byte(12));
      if(atack_x-j+2<0){
        atack=0;
        j=1;
      }
    }
  }
  if(j>3 && atack==1 && read_button==1){
    atack2=1;
  }
  if(atack2==1){
    k=k+2;
    atack2_x=x;
    if(side2==1){
      lcd.setCursor(atack2_x+k-2,atack2_rank);
      lcd.write(byte(12));
      if(atack2_x+k-2>15){
        atack2=0;
        k=1;
      }
    }
    else if(side2==0){
      lcd.setCursor(atack2_x-k+2,atack2_rank);
      lcd.write(byte(12));
      if(atack2_x-k+2<0){
        atack2=0;
        k=1;
      }
    }
  }
  if(read_button==1 && j==3){
    tone(13,500,50);
  }
  if(read_button==1 && k==3){
    tone(13,500,50);
  }
  //============================================ジャンプ設定==========================================================================================ジャンプ設定
  read_x = analogRead(Y_pin);
  read_y = analogRead(X_pin);
  if(read_y<100){//ジャンプモード
    read_yy=1;
  }
  if(read_yy==1){//ジャンプモード中に++される
    jump++;
  }

  if(jump==1){//以下各ジャンプセクション
    i=11;
    rank=1;
  }
  else if(jump==2){
    i=10;
    rank=0;
  }
  else if(jump==3 && read_y>100){//ジャンプモード解除
    jump=0;
    rank=1;
    i=10;
    read_yy=0;
  }
  else if(jump==3 && read_y<100){
    i=11;
    rank=0;
  }
  else if(jump==4){//ジャンプモード解除
    jump=0;
    rank=1;
    i=10;
    read_yy=0;
  }
  //================================================敵1設定==============================================================================================敵1設定
  if(enemy_life>0){
    lcd.setCursor(enemy_x,enemy_y);
    lcd.write(byte(13));
  }
  else if(enemy_life==0){
    memory_enemy = progress;
    enemy_life = enemy_life - 1;
  }
  if((side==1 && enemy_x==atack_x+j-2 && enemy_y==atack_rank) ||
     (side==1 && enemy_x==atack_x+j-1 && enemy_y==atack_rank) ||
     (side==0 && enemy_x==atack_x-j+2 && enemy_y==atack_rank) ||
     (side==0 && enemy_x==atack_x-j+1 && enemy_y==atack_rank) ||
     (side2==1 && enemy_x==atack2_x+k-2 && enemy_y==atack2_rank) ||
     (side2==1 && enemy_x==atack2_x+k-1 && enemy_y==atack2_rank) ||
     (side2==0 && enemy_x==atack2_x-k+2 && enemy_y==atack2_rank) ||
     (side2==0 && enemy_x==atack2_x-k+1 && enemy_y==atack2_rank)){
      enemy_life = enemy_life - 1;
  }
  //================================================敵2設定==============================================================================================敵2設定
  if(progress>=memory_enemy+25 && enemy2_life>0){
    lcd.setCursor(enemy2_x,enemy2_y);
    lcd.write(byte(13));
  }
  else if(enemy2_life==0){
    memory_enemy2 = progress;
    atack_count=0;
    span_atack2=25;
    enemy2_life = enemy2_life - 1;
  }
  if(((side==1 && enemy2_x==atack_x+j-2 && enemy2_y==atack_rank) ||
     (side==1 && enemy2_x==atack_x+j-1 && enemy2_y==atack_rank) ||
     (side==0 && enemy2_x==atack_x-j+2 && enemy2_y==atack_rank) ||
     (side==0 && enemy2_x==atack_x-j+1 && enemy2_y==atack_rank) ||
     (side2==1 && enemy2_x==atack2_x+k-2 && enemy2_y==atack2_rank) ||
     (side2==1 && enemy2_x==atack2_x+k-1 && enemy2_y==atack2_rank) ||
     (side2==0 && enemy2_x==atack2_x-k+2 && enemy2_y==atack2_rank) ||
     (side2==0 && enemy2_x==atack2_x-k+1 && enemy2_y==atack2_rank))&&enemy_life<=0&&progress>=memory_enemy+25){
      enemy2_life = enemy2_life - 1;
  }
  if(progress>=memory_enemy+span_atack2 && enemy2_life>0){
    lcd.setCursor(14-atack_count,1);
    lcd.write(byte(14));
    atack_count++;
  }
  if(14-atack_count<0){
    atack_count=0;
    span_atack2 = span_atack2 + 20;
  }
  //================================================敵3設定==============================================================================================敵3設定
  if(progress>=memory_enemy2+25 && enemy3_life>0){
    lcd.setCursor(enemy3_x,enemy3_y);
    lcd.write(byte(13));
  }
  else if(enemy3_life==0){
    memory_enemy3 = progress;
    atack_count=0;
    atack_count2=0;
    span_atack1=25;
    span_atack2=25;
    enemy3_life = enemy3_life - 1;
  }
  if(((atack==1 && side==1 && enemy3_x==atack_x+j-2 && enemy3_y==atack_rank) ||
     (atack==1 && side==1 && enemy3_x==atack_x+j-1 && enemy3_y==atack_rank) ||
     (atack==1 && side==0 && enemy3_x==atack_x-j+2 && enemy3_y==atack_rank) ||
     (atack==1 && side==0 && enemy3_x==atack_x-j+1 && enemy3_y==atack_rank) ||
     (atack2==1 && side2==1 && enemy3_x==atack2_x+k-2 && enemy3_y==atack2_rank) ||
     (atack2==1 && side2==1 && enemy3_x==atack2_x+k-1 && enemy3_y==atack2_rank) ||
     (atack2==1 && side2==0 && enemy3_x==atack2_x-k+2 && enemy3_y==atack2_rank) ||
     (atack2==1 && side2==0 && enemy3_x==atack2_x-k+1 && enemy3_y==atack2_rank))&&enemy2_life<=0&&progress>=memory_enemy2+25){
      enemy3_life = enemy3_life - 1;
  }
  if(progress>=memory_enemy2+25 && enemy4_life>0){
    lcd.setCursor(enemy4_x,enemy4_y);
    lcd.write(byte(13));
  }
  else if(enemy4_life==0){
    memory_enemy4 = progress;
    atack_count=0;
    atack_count2=0;
    span_atack1=25;
    span_atack2=25;
    enemy4_life = enemy4_life - 1;
  }
  if(((atack==1 && side==1 && enemy4_x==atack_x+j-2 && enemy4_y==atack_rank) ||
     (atack==1 && side==1 && enemy4_x==atack_x+j-1 && enemy4_y==atack_rank) ||
     (atack==1 && side==0 && enemy4_x==atack_x-j+2 && enemy4_y==atack_rank) ||
     (atack==1 && side==0 && enemy4_x==atack_x-j+1 && enemy4_y==atack_rank) ||
     (atack2==1 && side2==1 && enemy4_x==atack2_x+k-2 && enemy4_y==atack2_rank) ||
     (atack2==1 && side2==1 && enemy4_x==atack2_x+k-1 && enemy4_y==atack2_rank) ||
     (atack2==1 && side2==0 && enemy4_x==atack2_x-k+2 && enemy4_y==atack2_rank) ||
     (atack2==1 && side2==0 && enemy4_x==atack2_x-k+1 && enemy4_y==atack2_rank))&&enemy2_life<=0&&progress>=memory_enemy2+25){
      enemy4_life = enemy4_life - 1;
  }if(progress>=memory_enemy2+25 && enemy5_life>0){
    lcd.setCursor(enemy5_x,enemy5_y);
    lcd.write(byte(13));
  }
  else if(enemy5_life==0){
    memory_enemy5 = progress;
    atack_count=0;
    atack_count2=0;
    span_atack1=25;
    span_atack2=25;
    enemy5_life = enemy5_life - 1;
  }
  if(((atack==1 && side==1 && enemy5_x==atack_x+j-2 && enemy5_y==atack_rank) ||
     (atack==1 && side==1 && enemy5_x==atack_x+j-1 && enemy5_y==atack_rank) ||
     (atack==1 && side==0 && enemy5_x==atack_x-j+2 && enemy5_y==atack_rank) ||
     (atack==1 && side==0 && enemy5_x==atack_x-j+1 && enemy5_y==atack_rank) ||
     (atack2==1 && side2==1 && enemy5_x==atack2_x+k-2 && enemy5_y==atack2_rank) ||
     (atack2==1 && side2==1 && enemy5_x==atack2_x+k-1 && enemy5_y==atack2_rank) ||
     (atack2==1 && side2==0 && enemy5_x==atack2_x-k+2 && enemy5_y==atack2_rank) ||
     (atack2==1 && side2==0 && enemy5_x==atack2_x-k+1 && enemy5_y==atack2_rank))&&enemy2_life<=0&&progress>=memory_enemy2+25){
      enemy5_life = enemy5_life - 1;
  }
  if(progress>=memory_enemy2+span_atack1 && atack_count==0 && (enemy3_life>0 || enemy4_life>0 || enemy5_life>0)){
    enemy3_x = enemy3_x - 1;
    enemy4_x = enemy4_x - 1;
    enemy5_x = enemy5_x - 1;
  }
  if(enemy5_x<0 && progress>=memory_enemy2+25 && (enemy3_life>0 || enemy4_life>0 || enemy5_life>0)){
    atack_count=1;
  }
  if(atack_count==1 && progress>=memory_enemy2+25 && (enemy3_life>0 || enemy4_life>0 || enemy5_life>0)){
    enemy3_x = enemy3_x + 1;
    enemy4_x = enemy4_x + 1;
    enemy5_x = enemy5_x + 1;
  }
  if(enemy3_x>=16 && progress>=memory_enemy2+25 && (enemy3_life>0 || enemy4_life>0 || enemy5_life>0)){
    span_atack1 = span_atack1 + 33;
    enemy3_x=15;
    enemy4_x=14;
    enemy5_x=13;
    atack_count=0;
  }
  //================================================敵6設定==============================================================================================敵6設定
  if(progress>=memory_enemy3+25 &&
     progress>=memory_enemy4+25 &&
     progress>=memory_enemy5+25 && enemy6_life>0){
    if(setrange==0){
      x=7;
      setrange=1;
    }
    lcd.setCursor(enemy6_x,enemy6_y);
    lcd.write(byte(13));
  }
  else if(enemy6_life==0){
    memory_enemy6 = progress;
    atack_count=0;
    span_atack1=25;
    enemy6_life = enemy6_life - 1;
  }
  if(((atack==1 && side==1 && enemy6_x==atack_x+j-2 && enemy6_y==atack_rank) ||
     (atack==1 && side==1 && enemy6_x==atack_x+j-1 && enemy6_y==atack_rank) ||
     (atack==1 && side==0 && enemy6_x==atack_x-j+2 && enemy6_y==atack_rank) ||
     (atack==1 && side==0 && enemy6_x==atack_x-j+1 && enemy6_y==atack_rank) ||
     (atack2==1 && side2==1 && enemy6_x==atack2_x+k-2 && enemy6_y==atack2_rank) ||
     (atack2==1 && side2==1 && enemy6_x==atack2_x+k-1 && enemy6_y==atack2_rank) ||
     (atack2==1 && side2==0 && enemy6_x==atack2_x-k+2 && enemy6_y==atack2_rank) ||
     (atack2==1 && side2==0 && enemy6_x==atack2_x-k+1 && enemy6_y==atack2_rank))&&enemy3_life<=0&&progress>=memory_enemy3+25&&progress>=memory_enemy4+25&&progress>=memory_enemy5+25){
      enemy6_life = enemy6_life - 1;
  }
  if(progress>=memory_enemy3+25 &&
     progress>=memory_enemy4+25 &&
     progress>=memory_enemy5+25 && enemy7_life>0){
    lcd.setCursor(enemy7_x,enemy7_y);
    lcd.write(byte(13));
  }
  else if(enemy7_life==0){
    memory_enemy7 = progress;
    atack_count2=0;
    span_atack2=25;
    enemy7_life = enemy7_life - 1;
  }
  if(((atack==1 && side==1 && enemy7_x==atack_x+j-2 && enemy7_y==atack_rank) ||
     (atack==1 && side==1 && enemy7_x==atack_x+j-1 && enemy7_y==atack_rank) ||
     (atack==1 && side==0 && enemy7_x==atack_x-j+2 && enemy7_y==atack_rank) ||
     (atack==1 && side==0 && enemy7_x==atack_x-j+1 && enemy7_y==atack_rank) ||
     (atack2==1 && side2==1 && enemy7_x==atack2_x+k-2 && enemy7_y==atack2_rank) ||
     (atack2==1 && side2==1 && enemy7_x==atack2_x+k-1 && enemy7_y==atack2_rank) ||
     (atack2==1 && side2==0 && enemy7_x==atack2_x-k+2 && enemy7_y==atack2_rank) ||
     (atack2==1 && side2==0 && enemy7_x==atack2_x-k+1 && enemy7_y==atack2_rank))&&enemy3_life<=0&&progress>=memory_enemy3+25&&progress>=memory_enemy4+25&&progress>=memory_enemy5+25){
      enemy7_life = enemy7_life - 1;
  }
  if(progress>=memory_enemy3+span_atack1 &&
     progress>=memory_enemy4+span_atack1 &&
     progress>=memory_enemy5+span_atack1 && enemy6_life>0){
    if(setrange1==0){
      enemyatack_x=enemy6_x;
      enemyatack_y=enemy6_y;
      setrange1=1;
    }
    lcd.setCursor(enemyatack_x-atack_count-1,enemyatack_y);
    lcd.write(byte(14));
    if(enemyatack_y==0){
      lcd.setCursor(enemyatack_x-atack_count,enemyatack_y);
      lcd.write(byte(14));
    }
    atack_count++;
  }

  if(progress>=memory_enemy3+span_atack2 &&
     progress>=memory_enemy4+span_atack2 &&
     progress>=memory_enemy5+span_atack2 && enemy7_life>0){
    if(setrange2==0){
      enemyatack2_x=enemy7_x;
      enemyatack2_y=enemy7_y;
      setrange2=1;
    }
    lcd.setCursor(enemyatack2_x+atack_count2+1,enemyatack2_y);
    lcd.write(byte(14));
    if(enemyatack2_y==0){
      lcd.setCursor(enemyatack2_x+atack_count2,enemyatack2_y);
      lcd.write(byte(14));
    }
    atack_count2++;
  }

  if(enemyatack_x-atack_count-1<0 && enemy3_life<0 && enemy4_life<0 && enemy5_life<0){
    atack_count=0;
    span_atack1 = span_atack1 + 20;
    setrange1=0;
    if(enemy6_y==1){
      enemy6_y=0;
    }
    else if(enemy6_y==0){
      enemy6_y=1;
    }
  }
  if(enemyatack2_x+atack_count2+1>15 && enemy3_life<0 && enemy4_life<0 && enemy5_life<0 && setrange2==1){
    atack_count2=0;
    span_atack2 = span_atack2 + 20;
    setrange2=0;
    if(enemy7_y==1){
      enemy7_y=0;
    }
    else if(enemy7_y==0){
      enemy7_y=1;
    }
  }

  if(setrange2==0 && progress>=memory_enemy3
                  && progress>=memory_enemy4
                  && progress>=memory_enemy5){
     enemy6_x =random(12,16);
     enemy7_x =random(0,4);
  }
  //==============================================当たり判定===========================================================================================当たり判定
  if(enemy_life>0 && enemy2_life>0 && enemy3_life>0 &&
     enemy4_life>0 && enemy5_life>0 && enemy6_life>0 &&
     enemy7_life>0){
      if(x==enemy_x && rank==enemy_y){
        tone(3,100,50);
        life = life - 1;
      }
   }
  else if(enemy_life<0 && enemy2_life>0 &&
           enemy3_life>0 && enemy4_life>0 &&
           enemy5_life>0 && enemy6_life>0 &&
           enemy7_life>0){
            if((x==enemy2_x && rank==enemy2_y) ||
               (x==14-atack_count && rank==1)){
                tone(3,100,50);
                life = life - 1;
            }
  }
  else if(enemy_life<0 && enemy2_life<0 &&
           (enemy3_life>0 || enemy4_life>0 ||
           enemy5_life>0) && enemy6_life>0 &&
           enemy7_life>0){
            if((x==enemy3_x && rank==enemy3_y) ||
               (x==enemy4_x && rank==enemy4_y) ||
               (x==enemy5_x && rank==enemy5_y)){
                tone(3,100,50);
                life = life - 1;
            }
  }
  else if(enemy_life<0 && enemy2_life<0 &&
           enemy3_life<0 && enemy4_life<0 &&
           enemy5_life<0 && (enemy6_life>0 ||
           enemy7_life>0)){
            if((x==enemy6_x && rank==enemy6_y) ||
               (x==enemy7_x && rank==enemy7_y) ||
               (x==enemyatack_x-atack_count-1 && rank==enemyatack_y) ||
               (x==enemyatack2_x+atack_count2+1 && rank==enemyatack2_y) ||
               (x==enemyatack_x-atack_count && rank==enemyatack_y && enemyatack_y==0) ||
               (x==enemyatack2_x+atack_count2 && rank==enemyatack2_y && enemyatack2_y==0)){
                tone(3,100,50);
                life = life - 1;
            }
  }
  //==========================================中断メニュー============================================================================================中断メニュー
  if(read_SW==0){
    while(1){
      read_x = analogRead(Y_pin);
      read_y = analogRead(X_pin);
      read_SW = digitalRead(SW_pin);
      if(read_x<100){
        cursor_x = cursor_x + 1;
      }
      else if(read_x>1000){
        cursor_x = cursor_x - 1;
      }
      if(read_y<50){
        cursor_y = cursor_y - 1;
      }
      else if(read_y>1000){
        cursor_y = cursor_y + 1;
      }
      lcd.begin(16,2);
      lcd.setCursor(cursor_x,cursor_y);
      lcd.write(byte(15));
      if(cursor_x<0){
        cursor_x=cursor_x+1;
      }
      else if(cursor_x>15){
        cursor_x=cursor_x-1;
      }

      else if(cursor_y==-1){
        cursor_y=1;
      }

      else if(cursor_y>1){
        cursor_y=cursor_y-1;
      }
      lcd.setCursor(6,0);
      lcd.print("restart");
      lcd.setCursor(6,1);
      lcd.print("back");

      if(cursor_x==6 && cursor_y==0){//restart＞＞メニューボタン
        cursor_x=0;
        cursor_y=0;
        enemy6_life=-1;
        enemy7_life=-1;
        //break;
        customMODE=0;//
        goto custom;//
      }
      else if(cursor_x==6 && cursor_y==1){//back＞＞再開
        cursor_x=0;
        cursor_y=0;
        break;
      }
      delay(150);
      Serial.print(cursor_x);
      Serial.print(", ");
      Serial.println(cursor_y);
    }
  }
  //=========================================ゲームオーバー=========================================================================================ゲームオーバー
  if(life<0){
    if(overcount==0){
      t=900;
      overcount = overcount + 1;
    }
    digitalWrite(39,HIGH);
    digitalWrite(35,HIGH);
    digitalWrite(29,HIGH);
    digitalWrite(31,HIGH);
    digitalWrite(33,HIGH);
    digitalWrite(37,HIGH);
    digitalWrite(25,LOW);
    digitalWrite(27,LOW);
    digitalWrite(41,LOW);
    lcd.begin(16,2);
    lcd.setCursor(0,0);
    lcd.print("game over");
    //enemy6_life=-1;
    //enemy7_life=-1;
    if(t>=908){
      Serial.print("test====================test");
      customMODE=0;
      goto custom;
      }
  }
  //==============================================モニタ確認===========================================================================================モニタ設定
  Serial.print(life);
  Serial.print(", ");
  Serial.print(enemy7_life);
  Serial.print(", ");
  Serial.print(enemyatack2_x);
  Serial.print(", ");
  Serial.print(atack_count2);
  Serial.print(", ");
  Serial.println(enemyatack2_x+atack_count2);
  delay(interval_delay);
  progress++;
  //================================================周回===================================================================================================周回
  if(enemy6_life<0 && enemy7_life<0){
    delay(1000);
    interval_delay = interval_delay - 20;
    cursor_x=0;
    cursor_y=0;
    life=9;
    x=0;
    i=10;
    j=1;
    rank=1;
    setrange=0;
    setrange1=0;
    setrange2=0;
    atack_rank=1;
    atack2_rank=1;
    atack=0;
    atack2=0;
    side=1;
    side2=1;
    read_yy=0;
    jump=0;
    enemy_x=15;
    enemy_y=1;
    enemy2_x=15;
    enemy2_y=1;
    enemy3_x=15;
    enemy3_y=1;
    enemy4_x=14;
    enemy4_y=1;
    enemy5_x=13;
    enemy5_y=1;
    enemy6_x=15;
    enemy6_y=1;
    enemy7_x=0;
    enemy7_y=0;
    progress=0;
    enemy_life=5;     //敵1の体力
    enemy2_life=6;    //敵2の体力
    enemy3_life=10;
    enemy4_life=10;
    enemy5_life=10;
    enemy6_life=15;
    enemy7_life=15;
    span_atack1=25;
    span_atack2=25;    //初期攻撃頻度
    atack_count=0;
    atack_count2=0;
    enemyatack_x=10000;
    enemyatack_y=10000;
    enemyatack2_x=10000;
    enemyatack2_y=10000;
    memory_enemy=pow(10,5);
    memory_enemy2=pow(10,5);
    memory_enemy3=pow(10,5);
    memory_enemy4=pow(10,5);
    memory_enemy5=pow(10,5);
    memory_enemy6=pow(10,5);
    memory_enemy7=pow(10,5);
  }
  //==========================================残り体力表示============================================================================================残り体力表示
  if(life==9){
    digitalWrite(37,HIGH);
    digitalWrite(41,HIGH);
    digitalWrite(35,HIGH);
    digitalWrite(29,HIGH);
    digitalWrite(31,HIGH);
    digitalWrite(33,LOW);
    digitalWrite(39,HIGH);
    digitalWrite(25,LOW);
    digitalWrite(27,LOW);
  }
  else if(life==8){
    digitalWrite(37,HIGH);
    digitalWrite(41,HIGH);
    digitalWrite(35,HIGH);
    digitalWrite(29,HIGH);
    digitalWrite(31,HIGH);
    digitalWrite(33,HIGH);
    digitalWrite(39,HIGH);
    digitalWrite(25,LOW);
    digitalWrite(27,LOW);
  }
  else if(life==7){
    digitalWrite(37,HIGH);
    digitalWrite(41,LOW);
    digitalWrite(35,HIGH);
    digitalWrite(29,HIGH);
    digitalWrite(31,LOW);
    digitalWrite(33,LOW);
    digitalWrite(39,HIGH);
    digitalWrite(25,LOW);
    digitalWrite(27,LOW);
  }
  else if(life==6){
    digitalWrite(37,HIGH);
    digitalWrite(41,HIGH);
    digitalWrite(35,LOW);
    digitalWrite(29,HIGH);
    digitalWrite(31,HIGH);
    digitalWrite(33,HIGH);
    digitalWrite(39,HIGH);
    digitalWrite(25,LOW);
    digitalWrite(27,LOW);
  }
  else if(life==5){
    digitalWrite(37,HIGH);
    digitalWrite(41,HIGH);
    digitalWrite(35,LOW);
    digitalWrite(29,HIGH);
    digitalWrite(31,HIGH);
    digitalWrite(33,LOW);
    digitalWrite(39,HIGH);
    digitalWrite(25,LOW);
    digitalWrite(27,LOW);
  }
  else if(life==4){
    digitalWrite(37,HIGH);
    digitalWrite(41,HIGH);
    digitalWrite(35,HIGH);
    digitalWrite(29,HIGH);
    digitalWrite(31,LOW);
    digitalWrite(33,LOW);
    digitalWrite(39,LOW);
    digitalWrite(25,LOW);
    digitalWrite(27,LOW);
  }
  else if(life==3){
    digitalWrite(39,HIGH);
    digitalWrite(35,HIGH);
    digitalWrite(41,HIGH);
    digitalWrite(29,HIGH);
    digitalWrite(31,HIGH);
    digitalWrite(25,LOW);
    digitalWrite(27,LOW);
    digitalWrite(33,LOW);
    digitalWrite(37,LOW);
  }
  else if(life==2){
    digitalWrite(39,HIGH);
    digitalWrite(35,HIGH);
    digitalWrite(41,HIGH);
    digitalWrite(33,HIGH);
    digitalWrite(31,HIGH);
    digitalWrite(25,LOW);
    digitalWrite(27,LOW);
    digitalWrite(29,LOW);
    digitalWrite(37,LOW);
  }
  else if(life==1){
    digitalWrite(35,HIGH);
    digitalWrite(29,HIGH);
    digitalWrite(25,LOW);
    digitalWrite(27,LOW);
    digitalWrite(31,LOW);
    digitalWrite(33,LOW);
    digitalWrite(37,LOW);
    digitalWrite(39,LOW);
    digitalWrite(41,LOW);
  }
  else if(life==0){
    digitalWrite(39,HIGH);
    digitalWrite(35,HIGH);
    digitalWrite(29,HIGH);
    digitalWrite(31,HIGH);
    digitalWrite(33,HIGH);
    digitalWrite(37,HIGH);
    digitalWrite(25,LOW);
    digitalWrite(27,LOW);
    digitalWrite(41,LOW);
  }
  else if(life<0){
    digitalWrite(27,HIGH);
    digitalWrite(25,LOW);
    digitalWrite(29,LOW);
    digitalWrite(31,LOW);
    digitalWrite(33,LOW);
    digitalWrite(35,LOW);
    digitalWrite(37,LOW);
    digitalWrite(39,LOW);
    digitalWrite(41,LOW);
  }
}






//CUSTOM======================================================================================================================================================
//=========================================================================CUSTOM=============================================================================
//============================================================================================================================================================
while(1){
  custom:
  if(customMODE==0 | customMODE==1 | customMODE==2 | customMODE==3 | customMODE==4 | customMODE==5 | customMODE==6 | customMODE==7 | customMODE==8){
    byte customChar0[] = {
      B00000,
      B00000,
      B00000,
      B00000,
      B00000,
      B01110,
      B01010,
      B01110
    };
    byte customChar1[] = {
      B11111,
      B11111,
      B00000,
      B00000,
      B00000,
      B00000,
      B00000,
      B00000
    };
    byte customChar2[] = {
      B00000,
      B00000,
      B11111,
      B11111,
      B00000,
      B00000,
      B00000,
      B00000
    };
    byte customChar3[] = {
      B00000,
      B00000,
      B00000,
      B00000,
      B11111,
      B11111,
      B00000,
      B00000
    };
    byte customChar4[] = {
      B00000,
      B00000,
      B00000,
      B00000,
      B00000,
      B00000,
      B11111,
      B11111
    };
    byte customChar5[] = {
      B00000,
      B00100,
      B00101,
      B11110,
      B00100,
      B00100,
      B01010,
      B10010,
    };
    byte customChar6[] = {
      B11111,
      B11111,
      B11111,
      B11111,
      B11111,
      B11111,
      B11111,
      B11111,
    };
    lcd.createChar(0, customChar0);
    lcd.createChar(1, customChar1);
    lcd.createChar(2, customChar2);
    lcd.createChar(3, customChar3);
    lcd.createChar(4, customChar4);
    lcd.createChar(5, customChar5);
    lcd.createChar(6, customChar6);
    t=800;
    d=1;
    j=0;
    rrr=0;
    jjj=3;
    kkk=3;
    lll=3;
    mmm=3;
    nnn=0;
    xx=0;
    yy=0;
    ww=5;
    zz=1;
    ra=1;
    rb=5;
    rc=9;
    rd=2;
    re=8;
    rf=5;
    rg=4;
    rh=3;
    ri=7;
    rj=6;
    randomSeed(analogRead(7));
    s=0;
  }
  else if(customMODE==9){
    byte customChar10[] = {
      B00000,
      B00000,
      B00000,
      B00000,
      B00100,
      B01110,
      B00100,
      B01010
    };
    byte customChar11[] = {
      B00100,
      B01110,
      B00100,
      B01010,
      B00000,
      B00000,
      B00000
    };
    byte customChar12[] = {
      B00000,
      B00000,
      B00000,
      B00000,
      B00000,
      B01100,
      B01100,
      B00000
    };
    byte customChar13[] = {
      B11111,
      B11111,
      B10101,
      B11111,
      B11111,
      B10001,
      B11111,
      B11111,
    };
    byte customChar14[]  {
      B00000,
      B00000,
      B00000,
      B00000,
      B00000,
      B11111,
      B00000,
      B00000,
    };
    byte customChar15[] {
      B00000,
      B00000,
      B01110,
      B01110,
      B01110,
      B00000,
      B00000,
      B00000
    };
    lcd.createChar(10, customChar10);
    lcd.createChar(11, customChar11);
    lcd.createChar(12, customChar12);
    lcd.createChar(13, customChar13);
    lcd.createChar(14, customChar14);
    lcd.createChar(15, customChar15);
    pinMode(25, OUTPUT);
    pinMode(27, OUTPUT);
    pinMode(29, OUTPUT);
    pinMode(31, OUTPUT);
    pinMode(33, OUTPUT);
    pinMode(35, OUTPUT);
    pinMode(37, OUTPUT);
    pinMode(39, OUTPUT);
    pinMode(41, OUTPUT);
    randomSeed(analogRead(2));//シード値の初期化
    interval_delay=150;
    life=9;
    cursor_x=0;
    cursor_y=0;
    x=0;
    i=10;
    j=1;
    rank=1;
    setrange=0;
    setrange1=0;
    setrange2=0;
    atack_rank=1;
    atack2_rank=1;
    atack=0;
    atack2=0;
    side=1;
    side2=1;
    read_yy=0;
    jump=0;
    enemy_x=15;
    enemy_y=1;
    enemy2_x=15;
    enemy2_y=1;
    enemy3_x=15;
    enemy3_y=1;
    enemy4_x=14;
    enemy4_y=1;
    enemy5_x=13;
    enemy5_y=1;
    enemy6_x=15;
    enemy6_y=1;
    enemy7_x=0;
    enemy7_y=0;
    progress=0;
    enemy_life=5;     //敵1の体力
    enemy2_life=6;    //敵2の体力
    enemy3_life=10;
    enemy4_life=10;
    enemy5_life=10;
    enemy6_life=15;
    enemy7_life=15;
    span_atack1=25;
    span_atack2=25;    //初期攻撃頻度
    atack_count=0;
    atack_count2=0;
    enemyatack_x=10000;
    enemyatack_y=10000;
    enemyatack2_x=10000;
    enemyatack2_y=10000;
    memory_enemy=pow(10,5);
    memory_enemy2=pow(10,5);
    memory_enemy3=pow(10,5);
    memory_enemy4=pow(10,5);
    memory_enemy5=pow(10,5);
    memory_enemy6=pow(10,5);
    memory_enemy7=pow(10,5);
    overcount=0;
    W=200;
    t=2000;
  }






  if(customMODE==0){
    goto menu1;
  }
  else if(customMODE==1){//ゲーム１＞＞ステージ１
    qq=0;
    goto stage1;
  }
  else if(customMODE==2){//ゲーム１＞＞ステージ２
    qqq=0;
    goto stage2;
  }
  else if(customMODE==3){//ゲーム１＞＞ステージ３
    q=0;
    goto stage3;
  }
  else if(customMODE==4){//ゲーム２＞＞ランダム
    s=0;
    goto setting;
  }
  else if(customMODE==5){//ゲーム２＞＞初期位置１
    s=0;
    c=1;
    rx=1;
    ry=14;
    t=600;
    goto play;
  }
  else if(customMODE==6){//ゲーム２＞＞初期位置２
    s=0;
    c=1;
    rx=10;
    ry=14;
    t=600;
    goto play;
  }
  else if(customMODE==7){//ゲーム２＞＞初期位置３
    s=0;
    c=1;
    rx=11;
    ry=3;
    t=600;
    goto play;
  }
  else if(customMODE==8){//ゲーム２＞＞初期位置４
    s=0;
    c=1;
    rx=12;
    ry=12;
    t=600;
    goto play;
  }
  else if(customMODE==9){//ゲーム３
    goto startpoint;
  }
}


















  while(1){ //ステージ１の宣伝
    stage1:
    p=digitalRead(SW_pin);
    lcd.begin(16,2);
    lcd.setCursor(5,0);
    lcd.print("stage1");
    delay(3000);
    lcd.setCursor(5,1);
    lcd.print("start!");
    delay(2000);
    lcd.clear();
    t=0;
    goto stage11;
    if(p==0){
      goto menu1;
    }
  }
  if(1){ //ステージ２の宣伝
    stage2:
    lcd.begin(16,2);
    lcd.setCursor(5,0);
    lcd.print("stage2");
    delay(3000);
    lcd.setCursor(5,1);
    lcd.print("start!");
    delay(2000);
    lcd.clear();
    qqq=0;
    t=0;
    goto stage22;
  }
  while(1){ //ステージ３の宣伝
    stage3:
    lcd.begin(16,2);
    lcd.setCursor(5,0);
    lcd.print("stage3");
    delay(3000);
    lcd.setCursor(5,1);
    lcd.print("start!");
    delay(2000);
    lcd.clear();
    j=0;
    q=0;
    t=0;
    goto stage33;
  }
  if(t<3000){
    while(1){ //メニュー
      int p=digitalRead(SW_pin);
      int x=analogRead(Y_pin);
      int y=analogRead(X_pin);
      if(x>600){
        xx=xx-1;
      }
      else if(x<480){
        xx=xx+1;
      }
      else{
        xx=xx;
      }

      if(y<480){
        yy=yy-1;
      }
      else if(y>600){
        yy=yy+1;
      }
      else{
        yy=yy;
      }

      if((yy==0 || yy==1) && xx<5){ //メニュー１ページ目
        menu1:
        t=800;
        lcd.begin(16,2);
        lcd.setCursor(xx,yy);
        lcd.write(byte(0));
        lcd.setCursor(5,0);
        lcd.print("/game1");
        lcd.setCursor(5,1);
        lcd.print("/option");
      }
      else if(yy==0 && xx>4){ //メニュー１＞ゲーム１
        customMODE=1;
        goto custom;
        //goto stage1;
      }
      else if(yy==1 && xx>4){ //メニュー１＞オプション
        while(1){
          xx=0;
          yy=1;
          p = digitalRead(SW_pin);
          int w=analogRead(Y_pin);
          int z=analogRead(X_pin);
          if(w>900){
            ww=ww-1;
          }
          else if(w<100){
            ww=ww+1;
          }
          else{
            ww=ww;
          }

          if(z<100){
            zz=zz-1;
          }
          else if(z>900){
            zz=zz+1;
          }
          else{
            zz=zz;
          }

          lcd.begin(16,2);
          lcd.setCursor(ww,zz);
          lcd.write(byte(0));
          lcd.setCursor(0,0);
          lcd.print("stage 1 2 3");
          delay(170);
          if(p==0){
            goto menu1;
          }
          else if(p==1){
            delay(1);
          }
          if(ww==6 && zz==0){ //メニュー１＞オプション＞ステージ１
            qq=0;
            customMODE=1;
            goto custom;
            //goto stage1;
          }
          else if(ww==8 && zz==0){ //メニュー１＞オプション＞ステージ２
            qqq=0;
            customMODE=2;
            goto custom;
            //goto stage2;
          }
          else if(ww==10 && zz==0){ //メニュー＞オプション＞ステージ３
            q=0;
            customMODE=3;
            goto custom;
            //goto stage3;
          }
          Serial.print(" ");
          Serial.print(p);
        }
        if(xx<0){
          xx=0;
          yy=yy;

          goto menu1;
        }
      }
      else if(yy>=2 && yy<=3){ //メニュー２
        menu2:
        lcd.begin(16,2);
        lcd.setCursor(xx,yy%2);
        lcd.write(byte(0));
        lcd.setCursor(5,0);
        lcd.print("/game2");
        lcd.setCursor(5,1);
        lcd.print("/option");
        if(yy==2 && xx==5){ //メニュー２＞ゲーム２
          s=0;
          customMODE=4;
          goto custom;
          //goto setting;
        }
        if(yy>=4){
          xx=0;
          yy=4;
          goto menu3;
        }
        else if(xx<0){
          xx=0;
          yy=yy;
          goto menu2;
        }
        if(yy==3 && xx==5){ //メニュー２＞オプション
          ww=6;
          zz=1;
          while(1){
            xx=0;
            yy=1;
            p = digitalRead(SW_pin);
            int w=analogRead(Y_pin);
            int z=analogRead(X_pin);
            if(w>900){
              ww=ww-1;
            }
            else if(w<100){
              ww=ww+1;
            }
            else{
              ww=ww;
            }

            if(z<100){
              zz=zz-1;
            }
            else if(z>900){
              zz=zz+1;
            }
            else{
              zz=zz;
            }

            lcd.begin(16,2);
            lcd.setCursor(ww,zz);
            lcd.write(byte(0));
            lcd.setCursor(0,0);
            lcd.print("start 1 2 3 4");
            lcd.setCursor(0,1);
            lcd.print("point");
            delay(170);
            if(p==0){
              xx=0;
              yy=1;
              ww=0;
              zz=1;
              t=800;
              goto menu1;
            }
            if(ww==6 && zz==0){ //メニュー2＞オプション＞１(1,14)
              s=0;
              c=1;
              rx=1;
              ry=14;
              t=600;
              customMODE=5;
              goto custom;
              //goto play;
            }
            else if(ww==8 && zz==0){ //メニュー2＞オプション＞２(10,14)
              s=0;
              c=1;
              rx=10;
              ry=14;
              t=600;
              customMODE=6;
              goto custom;
              //goto play;
            }
            else if(ww==10 && zz==0){ //メニュー2＞オプション＞３(11,3)
              s=0;
              c=1;
              rx=11;
              ry=3;
              t=600;
              customMODE=7;
              goto custom;
              //goto play;
            }
            else if(ww==12 && zz==0){ //メニュー2＞オプション＞４(12,12)
              s=0;
              c=1;
              rx=12;
              ry=12;
              t=600;
              customMODE=8;
              goto custom;
            //goto play;
            }
            Serial.print(" ");
            Serial.print(p);
          }
        }
      }
      else if(yy>=4){ //メニュー3
        menu3:
        lcd.begin(16,2);
        lcd.setCursor(xx,yy%2);
        lcd.write(byte(0));
        lcd.setCursor(5,0);
        lcd.print("/game3");
        lcd.setCursor(5,1);
        lcd.print("/option");
        if(xx<0){
          xx=xx+1;
          yy=yy;
          goto menu3;
        }
        else if(yy>=6){
          xx = xx;
          yy = yy - 1;
          goto menu3;
        }
        else if(xx==5 && yy==4){
          customMODE=9;
          goto custom;
        }
        else if(xx==5 && yy==5){
          while(1){
            lcd.begin(16,2);
            lcd.print("Hello World");
          }
        }





      }



      else if(yy<0){
        yy=0;
        lcd.begin(16,2);
        lcd.setCursor(xx,0);
        lcd.write(byte(0));
        lcd.setCursor(5,0);
        lcd.print("/game1");
        lcd.setCursor(5,1);
        lcd.print("/option");
      }
      delay(170);
    }

  }










  Serial.print("t  ");
  Serial.print(t);
  Serial.println("\n\n");
}

void BGM(){
  Serial.println(t);


 if(t==0){
  W=48;
  tone(13,NOTE_E5,W);//ミ
 }
 else if(t==1){
  tone(13,NOTE_E5,W);//ミ
 }
 else if(t==3){
  tone(13,NOTE_E5,W);//ミ
 }
 else if(t==5){
  tone(13,NOTE_C5,W);//ド
 }
 else if(t==6){
  tone(13,NOTE_E5,2*W);//ミ
 }
 else if(t==8){
 tone(13,NOTE_G5,2*W);//ソ
 }
 else if(t==12){
 tone(13,NOTE_G4,2*W);//ソ
 }





 else if(t==16){
  tone(13,NOTE_C5,2*W);//ド
 }
 else if(t==19){
  tone(13,NOTE_G4,2*W);//ソ
 }
 else if(t==22){
  tone(13,NOTE_E4,60);//ミ
 }
 else if(t==25){
  tone(13,NOTE_A4,W);//ラ
 }
 else if(t==27){
  tone(13,NOTE_B4,W);//シ
 }
 else if(t==29){
 tone(13,NOTE_AS4,W);//ラシャ
 }
 else if(t==30){
 tone(13,NOTE_A3,2*W);//ラ
 }


 else if(t==33){
  tone(13,NOTE_G4,W);//ソ
 }
 else if(t==34){
  tone(13,NOTE_E5,W);//ミ
 }
 else if(t==35){
  tone(13,NOTE_G5,W);//ソ
 }
 else if(t==36){
  tone(13,NOTE_A5,2*W);//ラ
  t=39;
 }
 else if(t==40){
  tone(13,NOTE_F5,W);//ファ
 }
 else if(t==41){
 tone(13,NOTE_G5,W);//ソ
 }
 else if(t==43){
 tone(13,NOTE_E5,W);//ミ
 }
 else if(t==45){
  tone(13,NOTE_C5,W);//ド
 }
 else if(t==46){
 tone(13,NOTE_D5,W);//レ
 }
 else if(t==47){
 tone(13,NOTE_B4,W);//シ
 }



 else if(t==50){
  tone(13,NOTE_C5,2*W);//ド５
 }
 else if(t==53){
  tone(13,NOTE_G4,W);//ソ４
 }
 else if(t==56){
  tone(13,NOTE_E4,2*W);//ミ４
 }
 else if(t==59){
  tone(13,NOTE_A4,W);//ラ４
 }
 else if(t==61){
  tone(13,NOTE_B4,W);//シ４
 }
 else if(t==63){
 tone(13,NOTE_AS4,W);//ラシャ４
 }
 else if(t==64){
 tone(13,NOTE_A4,W);//ラ４
 }
 else if(t==66){
  tone(13,NOTE_G4,W);//ソ４
 }
 else if(t==67){
 tone(13,NOTE_E5,W);//ミ５
 }
 else if(t==68){
 tone(13,NOTE_G5,W);//ソ５
 }
 else if(t==69){
 tone(13,NOTE_A5,2*W);//ラ５
 }
 else if(t==71){
 tone(13,NOTE_F5,W);//ファ５
 }
 else if(t==72){
  tone(13,NOTE_G5,W);//ソ５
 }
 else if(t==74){
 tone(13,NOTE_E5,W);//ミ５
 }
 else if(t==76){
 tone(13,NOTE_C5,W);//ド５
 }
 else if(t==77){
 tone(13,NOTE_D5,W);//レ５
 }
 else if(t==78){
 tone(13,NOTE_B4,W);//シ４
 }




 if(t==83){
  tone(13,NOTE_G5,W);//ソ５
 }
 else if(t==84){
  tone(13,NOTE_FS5,2*W);//ファシャ５
 }
 else if(t==85){
  tone(13,NOTE_F5,W);//ファ５
 }
 else if(t==86){
  tone(13,NOTE_DS5,W);//レシャ５
 }
 else if(t==88){
  tone(13,NOTE_E5,W);//ミ５
 }
 else if(t==90){
 tone(13,NOTE_GS4,W);//ソシャ４
 }
 else if(t==91){
 tone(13,NOTE_A4,W);//ラ４
 }
 else if(t==92){
  tone(13,NOTE_C5,W);//ド５
 }
 else if(t==94){
 tone(13,NOTE_A4,W);//ラ４
 }
 else if(t==95){
 tone(13,NOTE_C5,W);//ド５
 }
 else if(t==96){
 tone(13,NOTE_D5,W);//レ５
 }
 else if(t==99){
 tone(13,NOTE_G5,W);//ソ５
 }
 else if(t==100){
  tone(13,NOTE_FS5,W);//ファシャ５
 }
 else if(t==101){
 tone(13,NOTE_F5,W);//ファ５
 }
 else if(t==102){
 tone(13,NOTE_DS5,W);//レシャ５
 }
 else if(t==104){
 tone(13,NOTE_E5,W);//ミ５
 }




 else if(t==106){
 tone(13,NOTE_C6,W);//ド６
 }
 else if(t==108){
 tone(13,NOTE_C6,W);//ド６
 }
 else if(t==109){
 tone(13,NOTE_C6,2*W);//ド６
 }
 else if(t==115){
 tone(13,NOTE_G5,W);//ソ５
 }
 else if(t==116){
 tone(13,NOTE_FS5,W);//ファシャ５
 }
 else if(t==117){
 tone(13,NOTE_F5,W);//ファ５
 }
 else if(t==118){
 tone(13,NOTE_DS5,W);//レシャ５
 }
 else if(t==120){
 tone(13,NOTE_E5,W);//ミ５
 }


















 else if(t==122){
  tone(13,NOTE_GS4,W);//ソシャ４
 }
 else if(t==123){
  tone(13,NOTE_A4,W);//ラ４
 }
 else if(t==124){
  tone(13,NOTE_C5,W);//ド５
 }
 else if(t==126){
  tone(13,NOTE_A4,W);//ラ４
 }
 else if(t==127){
  tone(13,NOTE_C5,W);//ド５
 }
 else if(t==128){
 tone(13,NOTE_D5,W);//レ５
 }
 else if(t==131){
 tone(13,NOTE_DS5,2*W);//レシャ５
 }
 else if(t==134){
  tone(13,NOTE_D5,W);//レ５
 }





 if(t==137){
  tone(13,NOTE_C5,2*W);//ド５
 }
 else if(t==147){
  tone(13,NOTE_G5,W);//ソ５
 }
 else if(t==148){
  tone(13,NOTE_FS5,W);//ファシャ５
 }
 else if(t==149){
  tone(13,NOTE_F5,W);//ファ５
 }
 else if(t==150){
  tone(13,NOTE_DS5,W);//レシャ５
 }
 else if(t==152){
 tone(13,NOTE_E5,W);//ミ５
 }
 else if(t==154){
 tone(13,NOTE_GS4,W);//ソシャ４
 }
 else if(t==155){
  tone(13,NOTE_A4,W);//ラ４
 }
 else if(t==156){
 tone(13,NOTE_C5,W);//ド５
 }
 else if(t==158){
 tone(13,NOTE_A4,W);//ラ４
 }
 else if(t==159){
 tone(13,NOTE_C5,W);//ド５
 }
 else if(t==160){
 tone(13,NOTE_D5,W);//レ５
 }






 else if(t==163){
  tone(13,NOTE_G5,W);//ソ５
 }
 else if(t==164){
  tone(13,NOTE_FS5,W);//ファシャ５
 }
 else if(t==165){
  tone(13,NOTE_F5,W);//ファ５
 }
 else if(t==166){
  tone(13,NOTE_DS5,W);//レシャ５
 }
 else if(t==168){
  tone(13,NOTE_E5,W);//ミ５
 }
 else if(t==170){
 tone(13,NOTE_C6,W);//ド６
 }
 else if(t==172){
 tone(13,NOTE_C6,W);//ド６
 }
 else if(t==173){
  tone(13,NOTE_C6,2*W);//ド６
 }
 else if(t==179){
 tone(13,NOTE_G5,W);//ソ５
 }
 else if(t==180){
 tone(13,NOTE_FS5,W);//ファシャ５
 }
 else if(t==181){
 tone(13,NOTE_F5,W);//ファ５
 }
 else if(t==182){
 tone(13,NOTE_DS5,W);//レシャ５
 }
 else if(t==184){
  tone(13,NOTE_E5,W);//ミ５
 }



 else if(t==186){
  tone(13,NOTE_GS4,W);//ソシャ４
 }
 else if(t==187){
  tone(13,NOTE_A4,W);//ラ４
 }
 else if(t==188){
  tone(13,NOTE_C5,W);//ド５
 }
 else if(t==190){
  tone(13,NOTE_A4,W);//ラ４
 }
 else if(t==191){
  tone(13,NOTE_C5,W);//ド５
 }
 else if(t==192){
 tone(13,NOTE_D5,W);//レ５
 }
 else if(t==195){
 tone(13,NOTE_DS5,2*W);//レシャ５
 }
 else if(t==198){
  tone(13,NOTE_D5,W);//レ５
 }
 else if(t==201){
 tone(13,NOTE_C5,2*W);//ド５
 }








 else if(t==209){
  tone(13,NOTE_C5,W);//ド５
 }
 else if(t==210){
  tone(13,NOTE_C5,W);//ド５
 }
 else if(t==212){
  tone(13,NOTE_C5,W);//ド５
 }
 else if(t==214){
  tone(13,NOTE_C5,W);//ド５
 }
 else if(t==215){
  tone(13,NOTE_D5,2*W);//レ５
 }
 else if(t==217){
 tone(13,NOTE_E5,W);//ミ５
 }
 else if(t==218){
 tone(13,NOTE_C5,W);//ド５
 }
 else if(t==220){
  tone(13,NOTE_A4,W);//ラ４
 }
 else if(t==221){
 tone(13,NOTE_G4,2*W);//ソ４
 }
 else if(t==225){
 tone(13,NOTE_C5,W);//ド５
 }
 else if(t==226){
 tone(13,NOTE_C5,W);//ド５
 }
 else if(t==228){
 tone(13,NOTE_C5,W);//ド５
 }
 else if(t==230){
  tone(13,NOTE_C5,W);//ド５
 }
 else if(t==231){
 tone(13,NOTE_D5,W);//レ５
 }
 else if(t==232){
 tone(13,NOTE_E5,W);//ミ５
 }




 else if(t==241){
  tone(13,NOTE_C5,W);//ド５
 }
 else if(t==242){
  tone(13,NOTE_C5,W);//ド５
 }
 else if(t==244){
  tone(13,NOTE_C5,W);//ド５
 }
 else if(t==246){
  tone(13,NOTE_C5,W);//ド５
 }
 else if(t==247){
  tone(13,NOTE_D5,2*W);//レ５
 }
 else if(t==249){
 tone(13,NOTE_E5,W);//ミ５
 }
 else if(t==250){
 tone(13,NOTE_C5,W);//ド５
 }
 else if(t==252){
  tone(13,NOTE_A4,W);//ラ４
 }
 else if(t==253){
 tone(13,NOTE_G4,2*W);//ソ４
 }








 else if(t==257){
  tone(13,NOTE_E5,W);//ミ５
 }
 else if(t==258){
  tone(13,NOTE_E5,W);//ミ５
 }
 else if(t==260){
  tone(13,NOTE_E5,W);//ミ５
 }
 else if(t==262){
  tone(13,NOTE_C5,W);//ド５
 }
 else if(t==263){
  tone(13,NOTE_E5,2*W);//ミ５
 }
 else if(t==265){
 tone(13,NOTE_G5,2*W);//ソ５
 }
 else if(t==269){
 tone(13,NOTE_G4,2*W);//ソ４
 }
 else if(t==273){
  tone(13,NOTE_C5,2*W);//ド５
 }
 else if(t==276){
 tone(13,NOTE_G4,W);//ソ４
 }
 else if(t==279){
 tone(13,NOTE_E4,2*W);//ミ４
 }



 else if(t==282){
  tone(13,NOTE_A4,W);//ラ４
 }
 else if(t==284){
  tone(13,NOTE_B4,W);//シ４
 }
 else if(t==286){
  tone(13,NOTE_AS4,W);//ラシャ４
 }
 else if(t==287){
  tone(13,NOTE_A4,2*W);//ラ４
 }
 else if(t==290){
  tone(13,NOTE_G4,W);//ソ４
 }
 else if(t==291){
 tone(13,NOTE_E5,W);//ミ５
 }
 else if(t==292){
 tone(13,NOTE_G5,W);//ソ５
 }
 else if(t==293){
  tone(13,NOTE_A5,2*W);//ラ５
 }
 else if(t==295){
 tone(13,NOTE_F5,W);//ファ５
 }
 else if(t==296){
 tone(13,NOTE_G5,W);//ソ５
 }
 else if(t==298){
 tone(13,NOTE_E5,W);//ミ５
 }
 else if(t==300){
 tone(13,NOTE_C5,W);//ド５
 }
 else if(t==301){
  tone(13,NOTE_D5,W);//レ５
 }
 else if(t==302){
 tone(13,NOTE_B4,W);//シ４
 }






 else if(t==305){
  tone(13,NOTE_C5,2*W);//ド５
 }
 else if(t==308){
  tone(13,NOTE_G4,W);//ソ４
 }
 else if(t==311){
  tone(13,NOTE_E4,2*W);//ミ４
 }
 else if(t==314){
  tone(13,NOTE_A4,W);//ラ４
 }
 else if(t==316){
  tone(13,NOTE_B4,W);//シ４
 }
 else if(t==318){
 tone(13,NOTE_AS4,W);//ラシャ４
 }
 else if(t==319){
 tone(13,NOTE_A4,2*W);//ラ４
 }
 else if(t==322){
  tone(13,NOTE_G4,W);//ソ４
 }
 else if(t==323){
 tone(13,NOTE_E5,W);//ミ５
 }
 else if(t==324){
 tone(13,NOTE_G5,W);//ソ５
 }
 else if(t==325){
 tone(13,NOTE_A5,2*W);//ラ５
 }
 else if(t==327){
 tone(13,NOTE_F5,W);//ファ５
 }
 else if(t==328){
  tone(13,NOTE_G5,W);//ソ５
 }





 else if(t==330){
  tone(13,NOTE_E5,W);//ミ５
 }
 else if(t==332){
  tone(13,NOTE_C5,W);//ド５
 }
 else if(t==333){
  tone(13,NOTE_D5,W);//レ５
 }
 else if(t==334){
  tone(13,NOTE_B4,W);//シ４
 }
 else if(t==337){
  tone(13,NOTE_E5,W);//ミ５
 }
 else if(t==338){
 tone(13,NOTE_C5,W);//ド５
 }
 else if(t==340){
 tone(13,NOTE_G4,W);//ソ４
 }
 else if(t==343){
  tone(13,NOTE_GS4,2*W);//ソシャ４
 }
 else if(t==345){
 tone(13,NOTE_A4,W);//ラ４
 }
 else if(t==346){
 tone(13,NOTE_F5,W);//ファ５
 }
 else if(t==348){
 tone(13,NOTE_F5,W);//ファ５
 }
 else if(t==349){
 tone(13,NOTE_A4,2*W);//ラ４
 }




 else if(t==354){
  tone(13,NOTE_B4,W);//シ４
 }
 else if(t==355){
  tone(13,NOTE_A5,W);//ラ５
 }
 else if(t==356){
  tone(13,NOTE_A5,W);//ラ５
 }
 else if(t==357){
  tone(13,NOTE_A5,W);//ラ５
 }
 else if(t==358){
  tone(13,NOTE_G5,W);//ソ５
 }
 else if(t==359){
 tone(13,NOTE_F5,W);//ファ５
 }
 else if(t==361){
 tone(13,NOTE_E5,W);//ミ５
 }
 else if(t==362){
  tone(13,NOTE_C5,W);//ド５
 }
 else if(t==364){
 tone(13,NOTE_A4,W);//ラ４
 }
 else if(t==365){
 tone(13,NOTE_G4,2*W);//ソ４
 }
 else if(t==369){
 tone(13,NOTE_E5,W);//ミ５
 }
 else if(t==370){
 tone(13,NOTE_C5,W);//ド５
 }
 else if(t==372){
 tone(13,NOTE_G4,W);//ソ４
 }
 else if(t==375){
  tone(13,NOTE_GS4,2*W);//ソシャ４
 }






 else if(t==377){
  tone(13,NOTE_A4,W);//ラ４
 }
 else if(t==378){
  tone(13,NOTE_F5,W);//ファ５
 }
 else if(t==380){
  tone(13,NOTE_F5,W);//ファ５
 }
 else if(t==381){
  tone(13,NOTE_A4,2*W);//ラ４
 }
 else if(t==385){
  tone(13,NOTE_B4,W);//シ４
 }
 else if(t==386){
 tone(13,NOTE_F5,W);//ファ５
 }
 else if(t==388){
 tone(13,NOTE_F5,W);//ファ５
 }
 else if(t==389){
  tone(13,NOTE_F5,W);//ファ５
 }
 else if(t==390){
 tone(13,NOTE_E5,W);//ミ５
 }
 else if(t==391){
 tone(13,NOTE_D5,2*W);//レ５
 }
 else if(t==393){
 tone(13,NOTE_C5,2*W);//ド５
 }






 else if(t==401){
  tone(13,NOTE_E5,W);//ミ５
 }
 else if(t==402){
  tone(13,NOTE_C5,W);//ド５
 }
 else if(t==404){
  tone(13,NOTE_G4,W);//ソ４
 }
 else if(t==407){
  tone(13,NOTE_GS4,2*W);//ソシャ４
 }
 else if(t==409){
  tone(13,NOTE_A4,W);//ラ４
 }
 else if(t==410){
 tone(13,NOTE_F5,W);//ファ５
 }
 else if(t==412){
 tone(13,NOTE_F5,W);//ファ５
 }
 else if(t==413){
  tone(13,NOTE_A4,2*W);//ラ４
 }
 else if(t==418){
 tone(13,NOTE_B4,W);//シ４
 }
 else if(t==419){
 tone(13,NOTE_A5,W);//ラ５
 }
 else if(t==420){
 tone(13,NOTE_A5,W);//ラ５
 }
 else if(t==421){
 tone(13,NOTE_A5,W);//ラ５
 }
 else if(t==422){
 tone(13,NOTE_G5,W);//ソ５
 }
 else if(t==423){
  tone(13,NOTE_F5,W);//ファ５
 }




 else if(t==425){
  tone(13,NOTE_E5,W);//ミ５
 }
 else if(t==426){
  tone(13,NOTE_C5,W);//ド５
 }
 else if(t==428){
  tone(13,NOTE_A4,W);//ラ４
 }
 else if(t==429){
  tone(13,NOTE_G4,2*W);//ソ４
 }
 else if(t==433){
  tone(13,NOTE_E5,W);//ミ５
 }
 else if(t==434){
 tone(13,NOTE_C5,W);//ド５
 }
 else if(t==436){
 tone(13,NOTE_G4,W);//ソ４
 }
 else if(t==439){
  tone(13,NOTE_GS4,2*W);//ソシャ４
 }
 else if(t==441){
 tone(13,NOTE_A4,W);//ラ４
 }
 else if(t==442){
 tone(13,NOTE_F5,W);//ファ５
 }
 else if(t==444){
 tone(13,NOTE_F5,W);//ファ５
 }
 else if(t==445){
 tone(13,NOTE_A4,2*W);//ラ４
 }







 else if(t==449){
  tone(13,NOTE_B4,W);//シ４
 }
 else if(t==450){
  tone(13,NOTE_F5,W);//ファ５
 }
 else if(t==452){
  tone(13,NOTE_F5,W);//ファ５
 }
 else if(t==454){
  tone(13,NOTE_F5,W);//ファ５
 }
 else if(t==455){
  tone(13,NOTE_E5,W);//ミ５
 }
 else if(t==456){
 tone(13,NOTE_D5,W);//レ５
 }
 else if(t==457){
 tone(13,NOTE_C5,2*W);//ド５
 }
 else if(t==465){
  tone(13,NOTE_C5,W);//ド５
 }
 else if(t==466){
 tone(13,NOTE_C5,W);//ド５
 }
 else if(t==468){
 tone(13,NOTE_C5,W);//ド５
 }
 else if(t==470){
 tone(13,NOTE_C5,W);//ド５
 }
 else if(t==471){
 tone(13,NOTE_D5,2*W);//レ５
 }



 else if(t==473){
  tone(13,NOTE_E5,W);//ミ５
 }
 else if(t==474){
  tone(13,NOTE_C5,W);//ド５
 }
 else if(t==476){
  tone(13,NOTE_A4,W);//ラ４
 }
 else if(t==477){
  tone(13,NOTE_G4,2*W);//ソ４
 }
 else if(t==481){
  tone(13,NOTE_C5,W);//ド５
 }
 else if(t==482){
 tone(13,NOTE_C5,W);//ド５
 }
 else if(t==484){
 tone(13,NOTE_C5,2*W);//ド５
 }
 else if(t==486){
  tone(13,NOTE_C5,W);//ド５
 }
 else if(t==487){
 tone(13,NOTE_D5,W);//レ５
 }
 else if(t==488){
 tone(13,NOTE_E5,W);//ミ５
 }






 else if(t==497){
  tone(13,NOTE_C5,W);//ド５
 }
 else if(t==498){
  tone(13,NOTE_C5,W);//ド５
 }
 else if(t==500){
  tone(13,NOTE_C5,W);//ド５
 }
 else if(t==502){
  tone(13,NOTE_C5,W);//ド５
 }
 else if(t==503){
  tone(13,NOTE_D5,2*W);//レ５
 }
 else if(t==505){
 tone(13,NOTE_E5,W);//ミ５
 }
 else if(t==506){
 tone(13,NOTE_C5,W);//ド５
 }
 else if(t==508){
  tone(13,NOTE_A4,W);//ラ４
 }
 else if(t==509){
 tone(13,NOTE_G4,2*W);//ソ４
 }
 else if(t==513){
 tone(13,NOTE_E5,W);//ミ５
 }
 else if(t==514){
 tone(13,NOTE_E5,W);//ミ５
 }
 else if(t==516){
 tone(13,NOTE_E5,W);//ミ５
 }
 else if(t==518){
 tone(13,NOTE_C5,W);//ド５
 }
 else if(t==519){
  tone(13,NOTE_E5,2*W);//ミ５
 }





 else if(t==521){
  tone(13,NOTE_G5,2*W);//ソ５
 }
 else if(t==525){
  tone(13,NOTE_G4,2*W);//ソ４
 }
 else if(t==529){
  tone(13,NOTE_E5,W);//ミ５
 }
 else if(t==530){
  tone(13,NOTE_C5,W);//ド５
 }
 else if(t==532){
  tone(13,NOTE_G4,W);//ソ４
 }
 else if(t==535){
 tone(13,NOTE_GS4,2*W);//ソシャ４
 }
 else if(t==537){
 tone(13,NOTE_A4,W);//ラ４
 }
 else if(t==538){
  tone(13,NOTE_F5,W);//ファ５
 }
 else if(t==540){
 tone(13,NOTE_F5,W);//ファ５
 }
 else if(t==541){
 tone(13,NOTE_A4,2*W);//ラ４
 }






 else if(t==546){
  tone(13,NOTE_B4,W);//シ４
 }
 else if(t==547){
  tone(13,NOTE_A5,W);//ラ５
 }
 else if(t==548){
  tone(13,NOTE_A5,W);//ラ５
 }
 else if(t==549){
  tone(13,NOTE_A5,W);//ラ５
 }
 else if(t==550){
  tone(13,NOTE_G5,W);//ソ５
 }
 else if(t==551){
 tone(13,NOTE_F5,W);//ファ５
 }
 else if(t==553){
 tone(13,NOTE_E5,W);//ミ５
 }
 else if(t==554){
  tone(13,NOTE_C5,W);//ド５
 }
 else if(t==556){
 tone(13,NOTE_A4,W);//ラ４
 }
 else if(t==557){
 tone(13,NOTE_G4,2*W);//ソ４
 }
 else if(t==561){
 tone(13,NOTE_E5,W);//ミ５
 }
 else if(t==562){
 tone(13,NOTE_C5,W);//ド５
 }
 else if(t==564){
 tone(13,NOTE_G4,W);//ソ４
 }
 else if(t==567){
  tone(13,NOTE_GS4,2*W);//ソシャ４
 }





 else if(t==569){
  tone(13,NOTE_A4,W);//ラ４
 }
 else if(t==570){
  tone(13,NOTE_F5,W);//ファ５
 }
 else if(t==572){
  tone(13,NOTE_F5,W);//ファ５
 }
 else if(t==573){
  tone(13,NOTE_A4,2*W);//ラ４
 }
 else if(t==577){
  tone(13,NOTE_B4,W);//シ４
 }
 else if(t==578){
 tone(13,NOTE_F5,W);//ファ５
 }
 else if(t==580){
 tone(13,NOTE_F5,W);//ファ５
 }
 else if(t==581){
  tone(13,NOTE_F5,W);//ファ５
 }
 else if(t==582){
 tone(13,NOTE_E5,W);//ミ５
 }
 else if(t==583){
 tone(13,NOTE_D5,W);//レ５
 }
 else if(t==585){
 tone(13,NOTE_C5,2*W);//ド５
 }
 else if(t==592){
 t=15;
 }



 else if(t==600){//--------------------------------------------------------------------------------------------------------------------------------------------------
  W=100;
  tone(13,NOTE_C4,W);//ド４//NOTE_C4
 }
 else if(t==601){
  tone(13,NOTE_C5,W);//ド５
 }
 else if(t==602){
  tone(13,NOTE_A3,W);//ラ３
 }
 else if(t==603){
  tone(13,NOTE_A4,W);//ラ４
 }
 else if(t==604){
  tone(13,NOTE_AS3,W);//ラシャ３
 }
 else if(t==605){
  tone(13,NOTE_AS4,W);//ラシャ４
 }
 else if(t==612){
  tone(13,NOTE_C4,W);//ド４
 }
 else if(t==613){
  tone(13,NOTE_C5,W);//ド５
 }
 else if(t==614){
  tone(13,NOTE_A3,W);//ラ３
 }
 else if(t==615){
  tone(13,NOTE_A4,W);//ラ４
 }
 else if(t==616){
  tone(13,NOTE_AS3,W);//ラシャ３
 }
 else if(t==617){
  tone(13,NOTE_AS4,W);//ラシャ４
 }



 else if(t==624){
 tone(13,NOTE_F3,W);//ファ３
 }
 else if(t==625){
  tone(13,NOTE_F4,W);//ファ４
 }
 else if(t==626){
  tone(13,NOTE_D3,W);//レ３
 }
 else if(t==627){
  tone(13,NOTE_D4,W);//レ４
 }
 else if(t==628){
  tone(13,NOTE_DS3,W);//レシャ３
 }
 else if(t==629){
  tone(13,NOTE_DS4,W);//レシャ４
 }
 else if(t==636){
  tone(13,NOTE_F3,W);//ファ３
 }
 else if(t==637){
  tone(13,NOTE_F4,W);//ファ４
 }
 else if(t==638){
  tone(13,NOTE_D3,W);//レ３
 }
 else if(t==639){
  tone(13,NOTE_D4,W);//レ４
 }
 else if(t==640){
  tone(13,NOTE_DS3,W);//レシャ３
 }
 else if(t==641){
  tone(13,NOTE_DS4,W);//レシャ４
 }
 else if(t==646){
  W=W*4/3;
  tone(13,NOTE_DS4,W);//------------DS4/E4/DS4
 }
 else if(t==647){
  tone(13,NOTE_D4,W);//----------------D4/D4/D4
 }
 else if(t==648){
  W=W*3/4;
  tone(13,NOTE_CS4,W);//------------CD4/CS4/CS4
 }





 else if(t==648){
  tone(13,NOTE_C4,2*W);//ド４
 }
 else if(t==650){
  tone(13,NOTE_DS4,2*W);//レシャ４
 }
 else if(t==652){
  tone(13,NOTE_D4,2*W);//レ４
 }
 else if(t==654){
  tone(13,NOTE_GS3,2*W);//ソシャ３
 }
 else if(t==656){
  tone(13,NOTE_G3,2*W);//ソ３
 }
 else if(t==658){
  tone(13,NOTE_CS4,2*W);//レシャ４
 }





 else if(t==660){
  W=W*2/3;
  tone(13,NOTE_C4,W);//ド４
 }
 else if(t==661){
  tone(13,NOTE_FS4,W);//ファシャ４
 }
 else if(t==662){
  tone(13,NOTE_F4,W);//ファ４
 }
 else if(t==663){
  tone(13,NOTE_E4,W);//ミ４
 }
 else if(t==664){
  tone(13,NOTE_AS4,W);//ラシャ４
 }
 else if(t==665){
  tone(13,NOTE_A4,W);//ラ４
  W=W*3/2;
 }
 else if(t==666){
  W=W/2;
  tone(13,NOTE_GS4,2*W);//ソシャ４
 }
 else if(t==668){
  tone(13,NOTE_DS4,2*W);//レシャ４
 }
 else if(t==670){
  tone(13,NOTE_B3,2*W);//シ３
 }
 else if(t==672){
  tone(13,NOTE_AS3,2*W);//ラシャ３
 }
 else if(t==674){
  tone(13,NOTE_A3,2*W);//ラ３
 }
 else if(t==676){
  tone(13,NOTE_GS3,2*W);//ソシャ３
  W=100;
 }
 else if(t==720){
  t=599;
 }
 else if(t==800){
  t=t-1;
 }









 else if(t==900){//--------------------------------------------game over
  W=96;
  tone(13,NOTE_B3,W);//シ４
 }
 else if(t==901){
  tone(13,NOTE_F4,W);//ファ５
 }
 else if(t==903){
  tone(13,NOTE_F4,W);//ファ５
 }
 else if(t==904){
  W=4*W/3;
  tone(13,NOTE_F4,W);//ファ５
 }
 else if(t==905){
  tone(13,NOTE_E4,W);//ミ５
 }
 else if(t==906){
  W=3*W/4;
 tone(13,NOTE_D4,W);//レ５
 }
 else if(t==907){
  W=W*6/4;
 tone(13,NOTE_C4,2*W);//ド５
 }
 else if(t==910){
  t=800;
 }





 else if(t==1000){//------------------------------------------------clear
  W=48;
  tone(13,NOTE_G3,W);//ソ３
 }
 else if(t==1001){
  tone(13,NOTE_C4,W);//ド４
 }
 else if(t==1002){
  tone(13,NOTE_E4,W);//ミ４
 }
 else if(t==1003){
  tone(13,NOTE_G4,W);//ソ４
 }
 else if(t==1004){
  tone(13,NOTE_C5,W);//ド５
 }
 else if(t==1005){
 tone(13,NOTE_E5,W);//ミ５
 }
 else if(t==1006){
  W=W*2/3;
 tone(13,NOTE_G5,8*W);//ソ５
 }
 else if(t==1008){
  tone(13,NOTE_E5,8*W);//ミ５
 }
 else if(t==1010){
  W=W*3/2;
  tone(13,NOTE_GS3,W);//ソシャ３
 }
 else if(t==1011){
  tone(13,NOTE_C4,60);//ド４
 }
 else if(t==1012){
  tone(13,NOTE_DS4,W);//レシャ４
 }
 else if(t==1013){
  tone(13,NOTE_GS4,W);//ソシャ４
 }
 else if(t==1014){
 tone(13,NOTE_C5,W);//ド５
 }
 else if(t==1015){
 tone(13,NOTE_DS5,W);//レシャ５
 }
 else if(t==1016){
  W=W*2/3;
 tone(13,NOTE_GS5,8*W);//ソシャ５
 }
 else if(t==1018){
  tone(13,NOTE_DS5,8*W);//レシャ５
 }



 else if(t==1020){
  W=W*3/2;
  tone(13,NOTE_AS3,W);//ラシャ３
 }
 else if(t==1021){
  tone(13,NOTE_D4,W);//レ４
 }
 else if(t==1022){
  tone(13,NOTE_F4,W);//ファ4
 }
 else if(t==1023){
  tone(13,NOTE_AS4,W);//ラシャ４
 }
 else if(t==1024){
 tone(13,NOTE_D5,W);//レ５
 }
 else if(t==1025){
 tone(13,NOTE_F5,W);//ファ５
 }
 else if(t==1026){
  W=W*2/3;
  tone(13,NOTE_AS5,8*W);//ラシャ５
 }
 else if(t==1028){
  W=W*3/2;
 tone(13,NOTE_AS5,W);//ラシャ５
 }
 else if(t==1029){
 tone(13,NOTE_AS5,W);//ラシャ５
 }
 else if(t==1030){
  tone(13,NOTE_AS5,W);//ラシャ５
 }
 else if(t==1031){
  tone(13,NOTE_C6,8*W);//ド６
 }
 else if(t==1033){
  t=800;
 }
//============================================
 else if(t==2002){
  tone(13,NOTE_F3,W);//ファ
 }
 else if(t==2004){
  tone(13,NOTE_E3,W);//ミ
 }
 else if(t==2006){
  tone(13,NOTE_C3,W);//ド
 }
 else if(t==2008){
  tone(13,NOTE_A2,W);//ラ
 }
 else if(t==2010){
  tone(13,NOTE_F3,W);//ファ
 }
 else if(t==2012){
  tone(13,NOTE_E3,W);//ミ
 }
 else if(t==2014){
  tone(13,NOTE_C3,W);//ド
 }
 else if(t==2016){
  tone(13,NOTE_A2,W);//ラ
 }
 else if(t==2017){
  tone(13,NOTE_A4,4*W+W);//ラ
 }
 else if(t==2022){
  tone(13,NOTE_A4,W);//ラ
 }
 else if(t==2023){
  tone(13,NOTE_AS4,W);//シ
 }
 else if(t==2024){
  tone(13,NOTE_B4,W);//シ
 }
 else if(t==2025){
  tone(13,NOTE_C5,2*W);//ド
 }
 else if(t==2027){
  tone(13,NOTE_A4,2*W+W);//ラ
 }
 else if(t==2030){
  tone(13,NOTE_C5,W);//ド
 }
 else if(t==2031){
  tone(13,NOTE_AS4,W);//シ
 }
 else if(t==2032){
  tone(13,NOTE_A4,W);//ラ
 }
 else if(t==2033){
  tone(13,NOTE_AS4,5*W);//シ
 }
 else if(t==2038){
  tone(13,NOTE_AS4,W);//シ
 }
 else if(t==2039){
  tone(13,NOTE_C5,W);//ド
 }
 else if(t==2040){
  tone(13,NOTE_CS5,W);//ド
 }
 else if(t==2041){
  tone(13,NOTE_D5,2*W);//レ
 }
 else if(t==2043){
  tone(13,NOTE_AS4,3*W);//シ
 }
 else if(t==2046){
  tone(13,NOTE_D5,W);//レ
 }
 else if(t==2047){
  tone(13,NOTE_C5,W);//ド
 }
 else if(t==2048){
  tone(13,NOTE_B4,W);//シ
 }
 else if(t==2049){
  tone(13,NOTE_C5,4*W);//ド
 }
 else if(t==2053){
  tone(13,NOTE_F5,2*W);//ファ
 }
 else if(t==2055){
  tone(13,NOTE_E5,W);
 }
 else if(t==2056){
  tone(13,NOTE_D5,W);
 }
 else if(t==2058){
  tone(13,NOTE_AS4,W);
 }
 else if(t==2059){
  tone(13,NOTE_A4,W);
 }
 else if(t==2060){
  tone(13,NOTE_AS4,W);
 }
 else if(t==2061){
  tone(13,NOTE_E4,2*W);
 }
 else if(t==2063){
  tone(13,NOTE_G4,2*W);
 }
 else if(t==2065){
  tone(13,NOTE_F3,W);
 }
 else if(t==2066){
  tone(13,NOTE_F4,W);
 }
 else if(t==2067){
  tone(13,NOTE_C3,W);
 }
 else if(t==2068){
  tone(13,NOTE_E4,W);
 }
 else if(t==2069){
  tone(13,NOTE_F3,W);
 }
 else if(t==2070){
  tone(13,NOTE_C4,W);
 }
 else if(t==2071){
  tone(13,NOTE_C3,W);
 }
 else if(t==2072){
  tone(13,NOTE_A3,W);
 }
 else if(t==2074){
  tone(13,NOTE_F2,W);
 }
 else if(t==2075){
  tone(13,NOTE_F2,W);
 }
 else if(t==2076){
  tone(13,NOTE_F2,W);
 }
 else if(t==2077){
  tone(13,NOTE_F2,W);
 }
 else if(t==2086){
  t=2000;
 }




 t++;
}
