/* point_list_array.c - array implementation of point_list */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#include "point_list_array.h"

/* Point functions */

/* Initialize a point p with name, x, and y.  Assume memory for p is
   allocated by the caller. */
void point_init(struct point *p, char *name, double x, double y)
{
    assert(p != NULL);

    strcpy(p->name, name);
    p->x = x;
    p->y = y;
}

/* Output a point to the console */
void point_print(struct point *p)
{
    assert (p != NULL);
    
    printf("%s: (%lf, %lf)\n", p->name, p->x, p->y);
}

/* Compute distance between p1 and p2 */
double point_distance(struct point *p1, struct point *p2)
{
    double dx, dy, dx2, dy2, distance;

    assert(p1 != NULL);
    assert(p2 != NULL);
    
    dx = p2->x - p1->x;
    dy = p2->y - p1->y;
    
    dx2 = pow(dx, 2);
    dy2 = pow(dy, 2);
    
    distance = sqrt(dx2 + dy2);
    
    return distance;
}

/* Point list functions */

/* Initialize a point_list.  Assume memory for l is allocated by caller. */
void point_list_init(struct point_list *l, char *name)
{
    assert(l != NULL);
    assert(name != NULL);
    
    strcpy(l->name, name);
    l->length = 0;
}


/* Add a point p to a point list l.  Assume list has enough room */
void point_list_add(struct point_list *l, struct point *p)
{
    assert(l != NULL);
    assert(p != NULL);
    assert(l->length < MAX_LIST_POINTS);

    l->plist[l->length] = *p;
    l->length++;
}

/* Return a pointer to the point located at index i */
struct point *point_list_getindex(struct point_list *l, int i)
{
    assert(l != NULL);
    
    return &(l->plist[i]);
}

/* Return the index of the first occurrence of a point named name */
int point_list_find_name(struct point_list *l, char *name)
{
	assert (l != NULL);
    int rv = -1;
    int i;
    
    for (i = 0; i < l->length; i++) {
        if (strncmp(l->plist[i].name, name, MAX_STR_LEN) == 0) {
            rv = i;
            break;
        }
    }
    
    return rv;
}

/* Output a list to the console */
void point_list_print(struct point_list *l)
{
    int i;
    
    assert(l != NULL);
    
    for (i = 0; i < l->length; i++) {
        point_print(&(l->plist[i]));
    }
}

/* Returns the length list */
int point_list_length(struct point_list *l)
{
	assert(l != NULL);
  
	return l->length;
}

/* Remove the point located at index i from list l */
int point_list_remove_index(struct point_list *l, int i)
{
	assert(l != NULL);
	int length = point_list_length(l);

	if (i >= length || i < 0)
		return -1;
	
	for (i; i < length; i++)
	{
        l->plist[i] = l->plist[i+1];
    }
    
    l->length--;
    
    return 0;
}

/* Remove the first point named name from list l */
int point_list_remove_name(struct point_list *l, char *name)
{
	assert(l != NULL);
	
	int index, length;
	length = point_list_length(l); 
	index = point_list_find_name(l, name);
   	
	if (index == -1)
		return -1;


	point_list_remove_index(l, index);
    
	return 0;
}

/* Find the closest point in list to point p, return NULL if list empty */
int point_list_closest(struct point_list *l, struct point *p)
{
	assert(l != NULL);
	assert(p != NULL);
	
	int i;
	int length = point_list_length(l);
	double min_d, temp_d;
	int min_i;
   
	if (length <= 0)
		return -1;
		
	min_i = 0;
	min_d = point_distance(&(l->plist[0]), p);
		
	for (i = 1; i < length; i++) {
	    temp_d = point_distance(&(l->plist[i]), p);
	    if (temp_d < min_d) {
	        min_d = temp_d;
	        min_i = i;
	    }
	}	
	return min_i;
}

void copy_point_list(struct point_list *l, struct point_list *l2)
{
	int i;
	assert(l != NULL);
    assert(l2 != NULL);
    
    point_list_init(l2, l->name);
	
	for (i = 0; i < l->length; i++) {
		struct point temp;
		point_init(&temp, l->plist[i].name, l->plist[i].x, l->plist[i].x);
		point_list_add(l2, &temp);
	}
}

/* Output a list of points from l ordered nearest to farthest from point p */
void point_list_print_all_near_to_far(struct point_list *l, struct point *p)
{
	assert(l != NULL);
	assert(p != NULL);
	
	struct point_list list;
	
	copy_point_list(l, &list);
    
    while(list.length > 0) {
    	int index = point_list_closest(&list, p);
    	point_print(point_list_getindex(&list, index));
    	point_list_remove_index(&list, index);
    }
}
