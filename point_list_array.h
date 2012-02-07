/* point_list_array.h - header file for point list interface */

#define MAX_STR_LEN 32
#define MAX_LIST_POINTS 100

struct point {
    char name[MAX_STR_LEN];
    double x;
    double y;
};

struct point_list {
    char name[MAX_STR_LEN];
    struct point plist[MAX_LIST_POINTS];
    int length;
};

/* point functions */

void point_init(struct point *p, char *name, double x, double y);
void point_print(struct point *p);
double point_distance(struct point *p1, struct point *p2);

/* point_list functions */

void point_list_init(struct point_list *l, char *name);
void point_list_add(struct point_list *l, struct point *p);
struct point *point_list_getindex(struct point_list *l, int i);
int point_list_find_name(struct point_list *l, char *name);
void point_list_print(struct point_list *l);
int point_list_length(struct point_list *l);
int point_list_remove_index(struct point_list *l, int i);
int point_list_remove_name(struct point_list *l, char *name);
int point_list_closest(struct point_list *l, struct point *p);
void copy_point_list(struct point_list *l, struct point_list *l2);
void point_list_print_all_near_to_far(struct point_list *l, struct point *p);

