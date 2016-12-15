#define SCX	30
#define	SCY	40

#define LV2X	1
#define	LV2Y	40
#define	LV3X	2
#define	LV3Y	80

#define	WALL_SYMBOL	'@'
#define	MON_SYMBOL	'#'
#define	CHA_SYMBOL	'*'
#define TRS_SYMBOL	'$'

#define	OB_WALL	1
#define	OB_FALL	2
#define OB_WARP	3

#define	INIT_X	1
#define	INIT_Y	1

#define	SIGHT	5

#define LV2WAL	20 //the amount of increased wall of level 2.
#define LV2SIT	1 //the amount of decreased sight range of level 2.
#define LV2MON	5 //the amount of increased monster of level 2.

#define LV3WAL	40
#define LV3SIT	4
#define LV3MON	10	

struct level_setup{
	int x, y;
	int wal;
	int mon;
	int sit;
};
//use this struct to set up level.

struct travler{
	int pos_x;
	int pos_y; //positions
	char sym;
};

struct monster{
	int vis; //1 : visible
	int pos_x;
	int pos_y; //positions
	char sym;
};

struct obstacle{
	int vis; //1 : visible
	int pos_x, pos_y;
	char sym;
};

struct treasure{
	int vis; //1 : visible
	int pos_x, pos_y;
	char sym;
};
