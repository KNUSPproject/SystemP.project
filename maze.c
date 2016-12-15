#include	<stdlib.h>
#include	<sys/time.h>
#include	<curses.h>
#include	<unistd.h>
#include	<time.h>
#include	<signal.h>
#include	"maze.h"

#define	MAX_OB	80
#define	NUM_OB	80
#define NUM_MON	5

struct travler t;
struct monster m[NUM_MON];
struct obstacle wall[MAX_OB];
struct obstacle	fall[MAX_OB];
struct obstacle	warp[MAX_OB];

void set_up();
void map_setting();
void sight_vis(int, int);
void anew(int, int);
void start(int, int);
int set_ticker(int);
void move_m();


void main(){
	set_up();
	start(NUM_OB, NUM_MON);
	endwin();
}

void set_up(){
	int x, y;
	initscr();
	
	t.pos_x = INIT_X;
	t.pos_y = INIT_Y;
	t.sym	= CHA_SYMBOL;

	mvaddch(t.pos_x, t.pos_y, t.sym);

	for(x = 0; x < SCX; x++){
                for(y = 0; y < SCY; y++){
                        if(x == 0 || x == SCX-1) mvaddch(x, y, '@');
                        else
                                if(y == 0 || y == SCY-1) mvaddch(x, y, '@');
                }
        }

	map_setting(NUM_OB);
	mon_setting(NUM_MON);
	sight_vis(NUM_OB, NUM_MON);
	for(x = 0; x < NUM_OB; x++)
		if(wall[x].vis == 1) mvaddch(wall[x].pos_x, wall[x].pos_y, wall[x].sym);
	for(x = 0; x < NUM_MON; x++)
		if(m[x].vis == 1) mvaddch(m[x].pos_x, m[x].pos_y, m[x].sym);
	
        refresh();
}

void map_setting(int n){
	int i;
	int x, y;
	srand(time(NULL));

	for(i = 0; i < n; i++){
		x = rand()%(SCX-2) + 1;
		y = rand()%(SCY-2) + 1;
		wall[i].vis = 0;
		wall[i].pos_x = x;
		wall[i].pos_y = y;
		wall[i].sym = WALL_SYMBOL;
	} //set walls (cannot move into walls.)
}

void mon_setting(int n){
	int i;
	int x, y;
	srand(time(NULL));

	for(i = 0; i < n; i++){
		x = rand()&(SCX-2) +1;
		y = rand()&(SCY-2) +1;
		m[i].vis = 0;
		m[i].pos_x = x;
		m[i].pos_y = y;
		m[i].sym = MON_SYMBOL;
	}
}


void anew(int n, int nm){
	int i;
	mvaddch(t.pos_x, t.pos_y, t.sym);
	
	for(i = 0; i < n; i++){
		if(wall[i].vis == 0) mvaddch(wall[i].pos_x, wall[i].pos_y, ' ');
		else mvaddch(wall[i].pos_x, wall[i].pos_y, wall[i].sym);
	}
	for(i = 0; i < nm; i++){
		if(m[i].vis == 0) mvaddch(m[i].pos_x, m[i].pos_y, ' ');
		else mvaddch(m[i].pos_x, m[i].pos_y, m[i].sym);
	}
	refresh();
	move(LINES-1,0);
}

void move_t(char c, int n){
	int xdir, ydir;
	int wall_check(int, int, int, int, int);
	
	if(c == 'a'){
		xdir = 0; ydir = -1;
		if(t.pos_y-1 > 0 && wall_check(t.pos_x, t.pos_y, n, xdir, ydir) == 0){
			mvaddch(t.pos_x, t.pos_y, ' ');
			t.pos_y --;
		}
	}
	if(c == 'd'){
		xdir = 0; ydir = 1;
		if(t.pos_y+1 < SCY-1 && wall_check(t.pos_x, t.pos_y, n, xdir, ydir) == 0){
			mvaddch(t.pos_x, t.pos_y, ' ');
			t.pos_y ++;
		}
	}
	if(c == 'w'){
		xdir = -1, ydir = 0;
		if(t.pos_x-1 > 0 && wall_check(t.pos_x, t.pos_y, n, xdir, ydir)== 0){
			mvaddch(t.pos_x, t.pos_y, ' ');
			t.pos_x --;
		}
	}
	if(c == 's'){
		xdir = 1; ydir = 0;
		if(t.pos_x+1 < SCX-1 && wall_check(t.pos_x, t.pos_y, n, xdir, ydir) == 0){
			mvaddch(t.pos_x, t.pos_y, ' ');
			t.pos_x ++;
		}
	}
}

int wall_check(int x, int y, int n, int xdir, int ydir){
	int i;
	for(i = 0; i < n; i++){
		if(x + xdir == wall[i].pos_x && y + ydir == wall[i].pos_y) return 1;
	}
	return 0;
} //retuen 1 when t_positions are same as wall's

void move_m(){
        int dir, i, ok;
        int wall_check_m(int, int, int, int);
	int n = NUM_MON;
        srand(time(NULL));

        for(i = 0; i < n; i++){
                dir = rand()%4;
                ok = wall_check_m(m[i].pos_x, m[i].pos_y, n, dir);
		if(ok == 0) mvaddch(m[i].pos_x, m[i].pos_y, ' ');
                if(dir == 0 && ok == 0) m[i].pos_x++;
                if(dir == 1 && ok == 0) m[i].pos_x--;
                if(dir == 2 && ok == 0) m[i].pos_y++;
                if(dir == 3 && ok == 0) m[i].pos_y--;
        }
	anew(NUM_OB,NUM_MON);
}

int wall_check_m(int x, int y, int n, int dir){
	int i;
	for(i = 0; i < n; i++){
		if(dir == 0 && x+1 == wall[i].pos_x) return 1;
		if(dir == 0 && x+1 == SCX) return 1;
		if(dir == 1 && x-1 == wall[i].pos_x) return 1;
		if(dir == 1 && x-1 == 0) return 1;
		if(dir == 2 && y+1 == wall[i].pos_y) return 1;
		if(dir == 2 && y+1 == SCY) return 1;
		if(dir == 3 && y-1 == wall[i].pos_y) return 1;
		if(dir == 3 && y-1 == 0) return 1;
	}
	return 0;
}

void death(int mn){
	int i;
	for(i = 0; i < mn; i++){
		if(t.pos_x == m[i].pos_x && t.pos_y == m[i].pos_y){
			endwin();
			exit(1);
		}
	}
}

int set_ticker(int n_msecs){
        struct itimerval t;
        long n_sec, n_usecs;

        n_sec = n_msecs / 1000;
        n_usecs = (n_msecs % 1000) * 1000L;

        t.it_interval.tv_sec = n_sec;
        t.it_interval.tv_usec = n_usecs;
        t.it_value.tv_sec = n_sec;
        t.it_value.tv_usec = n_usecs;

        return setitimer(ITIMER_REAL, &t, NULL);
}

void sight_vis(int n, int nm){
	int i;
	int 	ranx_min = t.pos_x - SIGHT,
		ranx_max = t.pos_x + SIGHT,
		rany_min = t.pos_y - SIGHT,
		rany_max = t.pos_y + SIGHT;

	for(i = 0; i < n; i++){
		if(wall[i].pos_x >= ranx_min && wall[i].pos_x <= ranx_max){
			if(wall[i].pos_y >= rany_min && wall[i].pos_y <= rany_max){
				wall[i].vis = 1; // if obstacles are in t's sight, can see.
			}
			else wall[i].vis = 0;
		}
		else wall[i].vis = 0;
	}
	for(i = 0; i < nm; i++){
                if(m[i].pos_x >= ranx_min && m[i].pos_x <= ranx_max){
                        if(m[i].pos_y >= rany_min && m[i].pos_y <= rany_max){
                                m[i].vis = 1; // if obstacles are in t's sight, can see.
                        }
                        else m[i].vis = 0;
                }
                else m[i].vis = 0;
        }

}

void start(int n, int m){
	char c;

	if(set_ticker(300)==-1)
		perror("set_ticker");

	signal(SIGALRM, move_m);
	
	while(1){
		c = getchar();
		move_t(c, n);
		sight_vis(n, m);
		anew(n, m);
		death(m);
	}
}






	

