#include<stdio.h>
#include<conio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<windows.h>
#define number_of_user 100


int level;
int TIME;//meghdari ke tol mikeshe ta har kalame taype she
char read_word[11][10505][20];
int rand_word_each_level;//barye tabe kalame random
int i;//i=number of the word of each level
int k;//baraye shomaresh 25 ta vorodi
int first_time_pointer,second_time_pointer;
char compare;
float false_word;/*baraye in float tarif kardam ke
moghe mohasebe point ghesmat aasharam bede
*/
float point_per_word,point_per_round,total_point;
struct data{
    char USER_NAME[20];
    char PASSWORD[20];
    int LEVEL;
    float TOTAL_POINT;
};
int s;//shomare karbara dar hafeze
struct data player_info[number_of_user];
FILE *DATA;
int timer_for_load;



void kalame_random(void);
void read_word_function(void);
void daryaf_az_vorodi(void);
int check(int);
void SetColor(int ForgC);//taghir rang
void mohasebe_emtiaz_har_dor(void);
void TIME_WITH_ecs(void);
void TIME_WITHOUT_ecs(void);
void log_and_sign(void);
void saved_or_new_game(void);
void save_in_file_and_close(void);
void load(void);
void level_counter(void);
void start_each_level(void);
void save_or_next_level(void);
void moarefi_bazi(void);


int main(void)
{
    moarefi_bazi();
    load();
    log_and_sign();
    load();
    level_counter();
}




void moarefi_bazi(void)
{
    system("color 8E");
    printf("This game asks you to type 25 words each level as fast as you can\nand then gives you a point at the end of each level and a total point.\n\n                                                                writen by HOSSEIN MOSHTAGHIN");
    Sleep(15000);
    system("cls");
}




void level_counter(void)
{
    total_point=player_info[s].TOTAL_POINT;
    level=player_info[s].LEVEL;
    while(level<11)
    {
        point_per_round=0;
        save_or_next_level();
        start_each_level();
        read_word_function();
        kalame_random();
        SetColor(5);
        printf("\npoint of this round = %0.2f",point_per_round);
        SetColor(7);
        total_point=total_point+point_per_round;
        printf("\ntotal point till now = %.2f",total_point);
        getch();
        level++;
    }
}




void log_and_sign(void)
{

    int harki_user_eshteb_bezane;
    int s_backup;
    int log_or_sign;
    struct data temp_player_info;
    char u_n_sign_in[20],p_sign_in[20];
    int tedad_horof_password,tedad_horof_password_cpy;
    int u_n_check,p_check;//bara adad strcmp
    char copy_password_for_sign_in[20];



    system("color 56");
entekhab_noe_vorod:
    printf("enter 1 for log in          enter 2 for sign in         enter 3 for exit\n");
    log_or_sign=getch();


wrongpassword:
    tedad_horof_password=0;
    DATA=fopen("data.txt","r+");
    for(s=0;feof(DATA)==0;s++)
    {
        fscanf(DATA,"%s",player_info[s].USER_NAME);

        fscanf(DATA,"%s",player_info[s].PASSWORD);

        fscanf(DATA,"%d",&player_info[s].LEVEL);

        fscanf(DATA,"%f",&player_info[s].TOTAL_POINT);

    }



    switch(log_or_sign)
    {
        case '1':
        {
            printf("Enter an username = ");
            gets(player_info[s].USER_NAME);
            for(s_backup=s-1;s_backup>=0;s_backup--)
            {
                u_n_check=strcmp(player_info[s].USER_NAME,player_info[s_backup].USER_NAME);
                if(u_n_check==0)
                {

                    system("cls");
                    printf("this user name is used\n");
                    goto entekhab_noe_vorod;

                }
            }
            printf("Enter a password for your username = ");

            while(tedad_horof_password<20)//chap setare jay password
            {
                p_sign_in[tedad_horof_password]=getche();
                if(p_sign_in[tedad_horof_password]==13)/*
                    13 cod enter hast
                    */
                {
                    break;
                }
                player_info[s].PASSWORD[tedad_horof_password]=p_sign_in[tedad_horof_password];
                if(tedad_horof_password==0)
                    printf("\b%c",p_sign_in[tedad_horof_password]);
                else
                    printf("\b\b*%c",p_sign_in[tedad_horof_password]);
                tedad_horof_password++;
            }

            player_info[s].LEVEL=0;

            player_info[s].TOTAL_POINT=0;
            system("cls");
            break;
        }

//jjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj
        case '2':
        {
            s--;
            s_backup=s;
            harki_user_eshteb_bezane=-1;
            printf("Enter your username = ");
            gets(u_n_sign_in);
            printf("Enter your password = ");
            while(tedad_horof_password<20)//chap setare jay password
            {
                p_sign_in[tedad_horof_password]=getche();
                if(p_sign_in[tedad_horof_password]==13)
                {
                    break;
                }
                if(tedad_horof_password==0)
                    printf("\b%c",p_sign_in[tedad_horof_password]);
                else
                    printf("\b\b*%c",p_sign_in[tedad_horof_password]);
                tedad_horof_password++;
            }
            tedad_horof_password_cpy=tedad_horof_password;
            while(s_backup>=0)
            {
                strcpy(copy_password_for_sign_in,player_info[s_backup].PASSWORD);
                copy_password_for_sign_in[tedad_horof_password]=p_sign_in[tedad_horof_password];
                u_n_check=strcmp(player_info[s_backup].USER_NAME,u_n_sign_in);
                if(u_n_check==0)
                {
                    while(tedad_horof_password>=0)
                    {
                        if(copy_password_for_sign_in[tedad_horof_password]==p_sign_in[tedad_horof_password])
                        {

                        }
                        else
                        {
                            tedad_horof_password=tedad_horof_password_cpy;
                            break;
                        }
                        if(tedad_horof_password==0)
                        {
                            harki_user_eshteb_bezane=1;
                            system("cls");
                            printf("signed in\n");
                            Sleep(2000);
                            system("cls");
                            temp_player_info=player_info[s];
                            player_info[s]=player_info[s_backup];
                            player_info[s_backup]=temp_player_info;
                            saved_or_new_game();
                            return;
                        }
                        tedad_horof_password--;
                    }
                }
                s_backup--;
            }
            if(harki_user_eshteb_bezane==-1)
            {
                system("cls");
                printf("enter 1 for log in          enter 2 for sign in         enter 3 for exit\n");
                SetColor(4);
                printf("wrong password or username.please try again\n");
                SetColor(6);
                fclose(DATA);
                goto wrongpassword;
            }
            break;
        }
        case '3':
        {
            load();
            system("color 37");
            printf("press any key to continue...");
            getch();
            exit(0);
        }
        default:
        {
            system("cls");
            goto entekhab_noe_vorod;
        }
    }


}




void saved_or_new_game(void)
{
    char bazi_jadid_ya_save;
    char bazi_jadid_ya_save1;

entekhab_noe_bazi:  printf("Do you want to continue your previous game?Y/N\n");
    bazi_jadid_ya_save=getch();
    switch(bazi_jadid_ya_save)
    {
        case('y'):
        {
            system("cls");
            break;
        }
        case('Y'):
        {
            system("cls");
            break;
        }
        case('N'):
        {
            goto motmaen_shodan_az_tasmim_karbar;
            break;
        }
        case ('n'):
        {
motmaen_shodan_az_tasmim_karbar:    printf("Are you sure?!You will lose your saved detailes.\nYes Im sure(then press Y)\nNo Im not(then press N)\n");
            bazi_jadid_ya_save1=getch();
            switch(bazi_jadid_ya_save1)
            {
                case('n'):
                {
                    system("cls");
                    goto entekhab_noe_bazi;
                    break;
                }
                case('N'):
                {
                    system("cls");
                    goto entekhab_noe_bazi;
                    break;
                }
                case('y'):
                {
                    player_info[s].TOTAL_POINT=0;
                    player_info[s].LEVEL=0;
                    system("cls");
                    printf("you have started a new game");
                    Sleep(2000);
                    system("cls");
                    break;
                }
                case('Y'):
                {
                    player_info[s].TOTAL_POINT=0;
                    player_info[s].LEVEL=0;
                    system("cls");
                    printf("you have started a new game");
                    Sleep(2000);
                    system("cls");
                    break;
                }
                default :
                {
                    system("cls");
                    printf("Do you want to continue your previous game?Y/N\n");
                    goto motmaen_shodan_az_tasmim_karbar;
                    break;
                }
            }
            break;
        }
        default :
        {
            system("cls");
            goto entekhab_noe_bazi;
            break;
        }
    }
}




void read_word_function(void)
{
    int k;//25 kalame har level
	FILE *F1,*F2,*F3,*F4,*F5,*F6,*F7,*F8,*F9,*F10,*F11;

	switch(level)
	{
		case 0:
		{
			F1=fopen("L01.txt","r");
			for(i=0;i<209;i++)
			{
				fscanf(F1,"%s",read_word[0][i]);
			}
			fclose(F1);
			break;
		}
		case 1:
		{
			F2=fopen("L02.txt","r");
			for(i=0;i<972;i++)
			{
				fscanf(F2,"%s",read_word[1][i]);
			}
			fclose(F2);
			break;
		}
		case 2:
		{
			F3=fopen("L03.txt","r");
			for(i=0;i<3130;i++)
			{
				fscanf(F3,"%s",read_word[2][i]);
			}
			fclose(F3);
			break;
		}
		case 3:
		{
			F4=fopen("L04.txt","r");
			for(i=0;i<984;i++)
			{
				fscanf(F4,"%s",read_word[3][i]);
			}
			fclose(F4);
			break;
		}
		case 4:
		{
			F5=fopen("L05.txt","r");
			for(i=0;i<5757;i++)
			{
				fscanf(F5,"%s",read_word[4][i]);
			}
			fclose(F5);
			break;
		}
		case 5:
		{
			F6=fopen("L06.txt","r");
			for(i=0;i<10505;i++)
			{
				fscanf(F6,"%s",read_word[5][i]);
			}
			fclose(F6);
			break;
		}
		case 6:
		{
			F7=fopen("L07.txt","r");
			for(i=0;i<936;i++)
			{
				fscanf(F7,"%s",read_word[6][i]);
			}
			fclose(F7);
			break;
		}
		case 7:
		{
			F8=fopen("L08.txt","r");
			for(i=0;i<1371;i++)
			{
				fscanf(F8,"%s",read_word[7][i]);
			}
			fclose(F8);
			break;
		}
		case 8:
		{
			F9=fopen("L09.txt","r");
			for(i=0;i<7442;i++)
			{
				fscanf(F9,"%s",read_word[8][i]);
			}
			fclose(F9);
			break;
		}
		case 9:
		{
			F10=fopen("L10.txt","r");
			for(i=0;i<534;i++)
			{
				fscanf(F10,"%s",read_word[9][i]);
			}
			fclose(F10);
			break;
		}
		case 10:
		{
			F11=fopen("L11.txt","r");
			for(i=0;i<334;i++)
			{
				fscanf(F11,"%s",read_word[10][i]);
			}
			fclose(F11);
			break;
		}
	}
}




void kalame_random(void)
{
    system("color F0");
    SetColor(1);
    printf("Level %d\n\n\n",level+1);
    SetColor(0);
    for(k=0;k<25;k++)
    {
        srand(time(NULL));
        rand_word_each_level=rand()%i;
        strlwr(read_word[level][rand_word_each_level]);//horof bozorgh be kochil tabdil mishan
        daryaf_az_vorodi();
        mohasebe_emtiaz_har_dor();
    }
}




void daryaf_az_vorodi(void)
{
    int hint;//be ma komak mikone bebinim ke az esc esstefade shode ya na
    int j;//shomarande tedad horof kalame


   	printf("%d.%s\n",k+1,read_word[level][rand_word_each_level]);
    first_time_pointer=time(NULL);

    for(j=0;read_word[level][rand_word_each_level][j]!='\0';j++)
    {
        if(j==0)
        {
            false_word=0;
        }
        compare=getche();
        if(compare==27)
            hint=1;
        j=check(j);
    }
    second_time_pointer=time(NULL);


    point_calc();
}




int check(int j)
{
    if(compare==27)
    {
        switch(j)
        {
            case 0:
                {
                    printf("\b   \\time has been paused whenever youre ready start typing last word from the first letter");
                    break;
                }
            case 1:
                {
                    printf("\b\b     \\time has been paused whenever youre ready start typing last word from the first letter");
                    break;
                }
            case 2:
                {
                    printf("\b\b\b   \\time has been paused whenever youre ready start typing last word from the first letter");
                    break;
                }
            case 3:
                {
                    printf("\b\b\b\b     \\time has been paused whenever youre ready start typing last word from the first letter");
                    break;
                }
            case 4:
                {
                    printf("\b\b\b\b\b   \\time has been paused whenever youre ready start typing last word from the first letter");
                    break;
                }
            case 5:
                {
                    printf("\b\b\b\b\b\b     \\time has been paused whenever youre ready start typing last word from the first letter");
                    break;
                }
            case 6:
                {
                    printf("\b\b\b\b\b\b\b   \\time has been paused whenever youre ready start typing last word from the first letter");
                    break;
                }
            case 7:
                {
                    printf("\b\b\b\b\b\b\b\b     \\time has been paused whenever youre ready start typing last word from the first letter");
                    break;
                }
            case 8:
                {
                    printf("\b\b\b\b\b\b\b\b\b   \\time has been paused whenever youre ready start typing last word from the first letter");
                    break;
                }
            case 9:
                {
                    printf("\b\b\b\b\b\b\b\b\b\b     \\time has been paused whenever youre ready start typing last word from the first letter");
                    break;
                }
            case 10:
                {
                    printf("\b\b\b\b\b\b\b\b\b\b\b   \\time has been paused whenever youre ready start typing last word from the first letter");
                    break;
                }
            case 11:
                {
                    printf("\b\b\b\b\b\b\b\b\b\b\b\b     \\time has been paused whenever youre ready start typing last word from the first letter");
                    break;
                }
            case 12:
                {
                    printf("\b\b\b\b\b\b\b\b\b\b\b\b\b   \\time has been paused whenever youre ready start typing last word from the first letter");
                    break;
                }
            case 13:
                {
                    printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b     \\time has been paused whenever youre ready start typing last word from the first letter");
                    break;
                }
            case 14:
                {
                    printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b   \\time has been paused whenever youre ready start typing last word from the first letter");
                    break;
                }
            case 15:
                {
                    printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b     \\time has been paused whenever youre ready start typing last word from the first letter");
                    break;
                }
            case 16:
                {
                    printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b   \\time has been paused whenever youre ready start typing last word from the first letter");
                    break;
                }
            case 17:
                {
                    printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b     \\time has been paused whenever youre ready start typing last word from the first letter");
                    break;
                }
            case 18:
                {
                    printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b   \\time has been paused whenever youre ready start typing last word from the first letter");
                    break;
                }
            case 19:
                {
                    printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b     \\time has been paused whenever youre ready start typing last word from the first letter");
                    break;
                }
        }
        printf("\\(press esc to save and exit)\n");
        compare=getch();
        if(compare==27)
        {
            save_in_file_and_close();
        }
        else
        {
            first_time_pointer=time(NULL);
            j=0;
        }
    }
        if(read_word[level][rand_word_each_level][j]==compare||read_word[level][rand_word_each_level][j]==compare+32)
        {
            SetColor(10);
            printf("\b%c",compare);
        }
        else
        {
            SetColor(4);
            printf("\b%c",compare);
            false_word=false_word+1;
        }
    SetColor(0);
    return j;
}




void point_calc(void)
{
    TIME=second_time_pointer-first_time_pointer;
    if(TIME<1)
    {
        TIME=1;
    }

    point_per_word=((2*(strlen(read_word[level][rand_word_each_level])))-false_word)/TIME*(10+level+1)/10;
    printf("\n____________________\n\n");
    mohasebe_emtiaz_har_dor();
}




void mohasebe_emtiaz_har_dor(void)
{
    point_per_round=point_per_round+point_per_word;
}




void SetColor(int ForgC)//manba www.codewithc.com
{
     WORD wColor;
     //This handle is needed to get the current background attribute

     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;
     //csbi is used for wAttributes word

     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          //To mask out all but the background attribute, and to add the color
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
}



void save_in_file_and_close(void)
{
    player_info[s].TOTAL_POINT=total_point;
    player_info[s].LEVEL=level;
    rewind(DATA);
    while(s>=0)
        {
        strcat(player_info[s].USER_NAME,"\n");
        fputs(player_info[s].USER_NAME,DATA);
        strcat(player_info[s].PASSWORD,"\n");
        fputs(player_info[s].PASSWORD,DATA);
        fprintf(DATA,"%d\n",player_info[s].LEVEL);

        if(s==0)
        {
            fprintf(DATA,"%0.2f",player_info[s].TOTAL_POINT);
        }
        else
        {
            fprintf(DATA,"%0.2f\n",player_info[s].TOTAL_POINT);
        }
        s--;
    }
    fclose(DATA);
    load();
    system("cls");
    system("color 37");
    printf("press any key to continue...");
    getch();
    exit(0);
}




void load(void)
{
    system("cls");
    system("color 40");
    for(timer_for_load=6;timer_for_load>0;timer_for_load--)
    {
        if(timer_for_load%3==0)
        printf("loading.");
        if(timer_for_load%3==2)
        printf("loading..");
        if(timer_for_load%3==1)
        printf("loading...");
        Sleep(500);
        system("cls");
    }
}




void start_each_level()
{
    int shomaresh_maakos;
    system("cls");
    system("color 6B");
    for(shomaresh_maakos=5;shomaresh_maakos>0;shomaresh_maakos--)
    {
        printf("start game in %d",shomaresh_maakos);
        Sleep(1000);/*inja bar hasb mili sanye gozashtam javab nadad :/
        bar hasb sanye gozashtam
        */
        system("cls");
    }
}




void save_or_next_level(void)
{
    int s_or_n;
    while(1)
    {
        system("cls");
        system("color 89");
        printf("do you want to start this level or save and exit?\n(");
        SetColor(14);
        printf("S");
        SetColor(9);
        printf("tart)\n(");
        SetColor(14);
        printf("E");
        SetColor(9);
        printf("xit)\n");
        s_or_n=getch();
        if(s_or_n=='s'||s_or_n=='S')
        {
            printf("\nby the way you can pause the game with \"esc\"");
            Sleep(5000);
            break;
        }
        if(s_or_n=='e'||s_or_n=='E')
            save_in_file_and_close();
    }
    system("cls");
}
