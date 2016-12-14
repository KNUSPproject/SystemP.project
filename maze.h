#define SCX	30
#define	SCY	40

#define	WALL_SYMBOL	'@'
#define	MON_SYMBOL	'#'
#define	CHA_SYMBOL	'*'

#define	OB_WALL	1
#define	OB_FALL	2
#define OB_WARP	3

#define	INIT_X	1
#define	INIT_Y	1

#define	SIGHT	1

#define YONGHO	30

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
