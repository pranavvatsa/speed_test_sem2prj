#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

char input_text[100][500];
int no_of_lines = 0;

void draw_border(int x1, int y1, int x2, int y2)
{
    int tmp;
    
    attron(COLOR_PAIR(4));
    
    move(x1, y1);
    printw("+");
    for (tmp = y1+1 ; tmp <= y2-1; tmp++)
    {
    	printw("-");
    }
    printw("+");
    move(x2, y1);
    printw("+");
    for (tmp = y1+1; tmp <= y2-1; tmp++)
    {
    	printw("-");
    }
    printw("+");
	move(x1, y1);
    for (tmp = x1+1; tmp <= x2-1; tmp++)
    {
        move(tmp, y1);
    	printw("|");
    }
    move(x1, y2);
    for (tmp = x1+1; tmp <= x2-1; tmp++)
    {
    	move(tmp, y2);
    	printw("|");
    }
    attroff(COLOR_PAIR(4));
}

void addtext(int ch, int *i, char *a, char *chs)
{
    if(ch == 0x107) /* handling backspace */
    {
        *i=*i-2;
        chs[*i+1]='\0';
        mvaddch(11,*i+10+1,a[*i+1]|COLOR_PAIR(1));
        move (11, *i+10+1);
    }
    else if (ch >=0x20 && ch < 0x7f)
    //else if(('A'<=ch && ch<='Z') | ('a'<=ch && ch<='z') | ('0'<=ch && ch<='9') | ch=='!' | ch==',' | ch==' '| ch=='.')
    {
        if(a[*i]==chs[*i])
        {
            mvaddch(11,*i+10,ch|COLOR_PAIR(2));
        }
        else
        {
            mvaddch(11,*i+10,ch|COLOR_PAIR(3));
        }
    }
    else
    {
        *i=*i-1;
    }
}

int length(char *a)
{
    int i=0;
    
    while(a[i]!='\0')
    {
        i++;
    }
    return i;
}

void check(char *a, char *chs, int n, int mis)
{
    for(int i=0; i<n-1; i++)
    {
        if(a[i]!=chs[i])
        {
            mis++;
        }
    }
    mvprintw(13,10,"Mistakes:%d",mis);
}

int practice_test()
{
    //char a[500];
    int c;
    int line_no, j;
    struct timeval start_time, end_time;
    double elapsedtime;

    clear();

    draw_border(5,5,20,100);
    move (8, 10);
    printw("Type the below line as fast as you can!!");

    line_no = rand() % no_of_lines;

    int n=length(input_text[line_no]);
    move (11,10);
    printw("%s",input_text[line_no]);
	refresh();
    
    move (11,10);
    attroff(COLOR_PAIR(1)|A_BOLD);
    char chs[100];
    int ch;
    int i=0;
    
    gettimeofday(&start_time, NULL); 
    while(i < (n-1))
    {
        ch=getch();
        if (ch == '\033') break;
        chs[i]=ch;
        addtext(ch,&i,input_text[line_no],chs);
        i++;
    }
    gettimeofday(&end_time, NULL);
    elapsedtime = end_time.tv_sec - start_time.tv_sec;
    check(input_text[line_no],chs,n,0);
    mvprintw(14,10, "Time taken: %.02f seconds", elapsedtime);
    while (getch() != '\033');
}

void load_complexity()
{
	int ch;
    FILE *fp;
    int line_no, j;
    int c;
	
	clear();
	draw_border(5,5,20,100);
	move (7, 10);
	printw("Select the complexity of the text");
	move (9, 15);
	printw("Press 1 for LOW complexity");
	move (11, 15);
	printw("Press 2 for MEDIUM complexity");
	move (13, 15);
	printw("Press 3 for HIGH complexity");
	while (ch = getch())
	{
		switch(ch)
		{
			case '1':
		    	fp = fopen("low.txt", "r");
		    	break;
	    	case '2':
		    	fp = fopen("med.txt", "r");
		    	break;
	    	case '3':
		    	fp = fopen("high.txt", "r");
		    	break;
	    	default:
	    		continue;
		}
		if (fp == NULL)
		{
			perror ("Cannot open input file\n");
			exit(1);
		}
		else break;
	}

    for (line_no = 0, j = 0; (c = fgetc(fp)) != EOF; )
    {
    	if (c == '\n')
    	{
    		input_text[line_no][j] = '\0';
    		line_no++; no_of_lines++;
    		j = 0;
    	}
    	else
    	{
        	input_text[line_no][j] = c;
        	j++;
    	}
    }
    no_of_lines++;
    j--;
    input_text[line_no][j] = '\0';
	fclose(fp);
}

int welcome_screen()
{
    int ch;

    while (1)
    {
		clear();
		draw_border(5,5,20,100);
		move (7, 10);
		printw("Welcome to Typing Speed Test!!");
		move (9, 15);
		printw("Press 1 to start the Typing Test");
		move (11, 15);
		printw("Press 2 to select complexity");
		move (13, 15);
		printw("Type ESC to exit the Typing Test");
		ch = getch();
		switch(ch)
		{
		    case '1':
		    	if (no_of_lines)
		        	practice_test();
		        break;
	        case '2':
	        	load_complexity();
	        	break;
	        case '\033':
	        	return 0;
		}
	}
}

int main ()
{
    initscr();
    raw();
    keypad(stdscr,TRUE);
    cbreak();
    noecho();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_CYAN, COLOR_BLACK);
    attron(COLOR_PAIR(1)|A_BOLD);

    welcome_screen();
    
    endwin();
}





	
	

