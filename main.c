#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

/*_
    "  ABSDEFGHIJ      ABSDEFGHIJ "
   ," .__________.    .__________."
   ,"0|          |   0|          |"
   ,"1|          |   1|          |"
   ,"2|          |   2|          |"
   ,"3|          |   3|          |"
   ,"4|          |   4|          |"
   ,"5|          |   5|          |"
   ,"6|          |   6|          |"
   ,"7|          |   7|          |"
   ,"8|          |   8|          |"
   ,"9|          |   9|          |"
   ," .__________.    .__________."
   ,
*/
#define N_lINES 13
#define FIELD_SIZE 10

typedef enum
{
    INIT=0
   ,DRAW
   ,PROCESSING
   ,EXIT
}eGameState;
typedef enum
{
    EMPTY=0
   ,SHOT
   ,STRAIK
   ,KILL
   ,SHIP
   ,EFILD_INFO_END
}eFieldInfo;
char draw_symbol[EFILD_INFO_END]=
{
       ' '    //EMPTY=0
      ,'*'   //SHOT
      ,'X'     //STRAIK
      ,'#'    //KILL
      ,'&'   //SHIP
};
#define  ARROW_KEY_PRESSED 0xE0
#define  KEY_ENTER           13
#define  KEY_UP              72
#define  KEY_DOWN            80
#define  KEY_RIGHT           77
#define  KEY_LEFT            75

#define TARGET              '+'

#define PLAYER_1 0
#define PLAYER_2 ~PLAYER_1

char *FIELD[] =
{
    "  ABSDEFGHIJ      ABSDEFGHIJ "
   ," .__________.     .__________."
   ,"0|          |    0|          |"
   ,"1|          |    1|          |"
   ,"2|          |    2|          |"
   ,"3|          |    3|          |"
   ,"4|          |    4|          |"
   ,"5|          |    5|          |"
   ,"6|          |    6|          |"
   ,"7|          |    7|          |"
   ,"8|          |    8|          |"
   ,"9|          |    9|          |"
   ," .__________.     .__________."
   ,
};

void draw_field(eFieldInfo *, unsigned short );

void ship_generate(eFieldInfo *);

unsigned char get_target_position(unsigned char *,unsigned char *);

int main()
{
    eGameState game_state=INIT;
    unsigned char isRan= 1;
    int player=PLAYER_1;

    eFieldInfo p1_data [FIELD_SIZE * FIELD_SIZE]= {EMPTY};
    eFieldInfo p2_data [FIELD_SIZE * FIELD_SIZE]= {EMPTY};

    eFieldInfo *tmp;
    unsigned char target_x =0;
    unsigned char target_y =0;
    unsigned short shot_position = 0;

    while(isRan)
    {
        switch (game_state) {
        case INIT:
        {
            ship_generate(p1_data);
            ship_generate(p2_data);
            p1_data[0]=KILL;
            //init game data
            game_state=DRAW;
            break;
        }
        case DRAW:
        {
            system("cls");
            tmp=(player ==PLAYER_1)? p1_data:p2_data;
            //drawing


                draw_field(tmp,shot_position);
                if(get_target_position(&target_x, &target_y))
                {
                    game_state=PROCESSING;
                }
                shot_position = (target_x <<8)|( target_y);

            break;
        }
        case PROCESSING:
        {
           //processing
            //...
            player= ~player;
            //logik ili ili player 1ili2
            game_state=DRAW;
            break;
        }
        case EXIT:
            break;
        }
    }

    return 0;
}
//--------------------------------------------------------
void draw_field(eFieldInfo *ap_data, unsigned short a_target)
{
    printf("%s\n",FIELD[0]);
    printf("%s\n",FIELD[1]);

    unsigned char target_x=0;
    unsigned char target_y=0;
    target_x=a_target;
    target_y=a_target >> 8;

    for(int  i = 0; i < 10; ++i)
    {
        printf("%c%c",FIELD[i+2][0],FIELD[i+2][1]);
        for(int j =0;j <FIELD_SIZE ;++j)//print field data 1
            printf("%c",draw_symbol[ap_data[i* FIELD_SIZE+j]]);
        for(int j=12;j<19;++j)
            printf("%c", FIELD [i+2][j]);
        for(int j =0;j <FIELD_SIZE ;++j)//print field data 2
           if(i== target_y&&j==target_x)
               printf("%c",TARGET);
            else
            printf(" ");//information shot

        printf("%c\n", FIELD [ i + 2][29] );
    }
    printf("%s\n",FIELD[N_lINES-1] );
}
//-----
void ship_generate(eFieldInfo *ap_data)
{
    /*
        "  ABSDEFGHIJ      ABSDEFGHIJ "
       ," .__________.    .__________."
       ,"0|#    #### |   0|          |"
       ,"1|  #       |   1|          |"
       ,"2|      #   |   2|          |"
       ,"3|#  #  #   |   3|          |"
       ,"4|#  #  #   |   4|          |"
       ,"5|#  #      |   5|          |"
       ,"6|   #    # |   6|          |"
       ,"7|      #   |   7|          |"
       ,"8|          |   8|          |"
       ,"9| ##   ##  |   9|          |"
       ," .__________.    .__________."
       ,
    */
    //0 Lines i*n+j
    ap_data[0*10+0]=SHIP;
    ap_data[0*10+5]=SHIP;
    ap_data[0*10+6]=SHIP;
    ap_data[0*10+7]=SHIP;
    ap_data[0*10+8]=SHIP;
    //1 Lines
    ap_data[1*10+3]=SHIP;
    //2 Lines
    ap_data[2*10+7]=SHIP;
    //3 Lines
    ap_data[3*10+0]=SHIP;
    ap_data[3*10+3]=SHIP;
    ap_data[3*10+7]=SHIP;
    //4 Lines
    ap_data[4*10+0]=SHIP;
    ap_data[4*10+3]=SHIP;
    ap_data[4*10+7]=SHIP;
    //5 Lines
    ap_data[5*10+0]=SHIP;
    ap_data[5*10+3]=SHIP;
    //6 Lines
    ap_data[6*10+4]=SHIP;
    ap_data[6*10+8]=SHIP;
    //7 Lines
    ap_data[7*10+7]=SHIP;
    //8 Lines
    //ap_data[8*10+0]=SHIP;
    //9 Lines
    ap_data[9*10+1]=SHIP;
    ap_data[9*10+2]=SHIP;
    ap_data[9*10+6]=SHIP;
    ap_data[9*10+7]=SHIP;
}
//------------------------------------------
unsigned char get_target_position(unsigned char *ap_x,unsigned char *ap_y)
{
    int key=0;
    key = getch();
    switch (key)
    {
    case KEY_DOWN:
    {
        if(*ap_x < (FIELD_SIZE - 1))
            (*ap_x)++;
        return 0;
    }
   case KEY_UP:
    {
        if(*ap_x > 0)
            (*ap_x)--;
        return 0;
    }
    case KEY_LEFT:
    {
        if(*ap_y>0)
            (*ap_y)--;
        return 0;
    }
    case KEY_RIGHT:
    {
        if(*ap_y<(FIELD_SIZE - 1))
            (*ap_y)++;
        return 0;
    }
   case KEY_ENTER:
        return 1;
}
        return 0;
};







