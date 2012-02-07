/* point_list_linked.c - array implementation of point_list */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#include "point_list_linked.h"

/* Point functions */

/* Initialize a point p with name, x, and y.  Assume memory for p is
   allocated by the caller. */
void point_init(struct point *p, char *name, double x, double y)
{
    assert(p != NULL);

    strcpy(p->name, name);
    p->x = x;
    p->y = y;
	p->next = NULL;
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
    
    strcpy(l->name, name);;
	l->head = NULL;
	l->tail = NULL;
}


/* Add a point p to a point list l.  Assume list has enough room */
void point_list_add(struct point_list *l, struct point *p)
{
	struct point *pnew;
	
    assert(l != NULL);
    assert(p != NULL);

	/* allocate a new point */
	pnew = (struct point *) malloc(sizeof(struct point));
	assert(pnew != NULL);
	
	*pnew = *p;
	pnew->next = NULL;
	
	/* add to list */
	
	if (l->length == 0) {
		l->head = pnew;
		l->tail = pnew;
	} else {
		l->tail->next = pnew;
		l->tail = pnew;
	}
    l->length++;
}

/* Return a pointer to the point located at index i */
struct point *point_list_getindex(struct point_list *l, int i)
{
	struct point *pcur = NULL;
	int count = 0;

    assert(l != NULL);

	for (pcur = l->head; pcur != NULL; pcur = pcur->next) {
		if (count == i) {
			break;
		}
		count++;
	}

	return pcur;
}

/* Return the index of the first occurrence of a point named name */
int point_list_find_name(struct point_list *l, char *name)
{
	assert(l != NULL);
	assert(name != NULL);
    int rv = -1;
    struct point *pcur;
    int i = 0;
    
    for (pcur = l->head; pcur != NULL; pcur = pcur->next) {
		if (strncmp(pcur->name, name, MAX_STR_LEN) == 0) {
        	rv = i;
            break;
		}
		i++;
	}
    return rv;
}

/* Output a list to the console */
void point_list_print(struct point_list *l)
{
	struct point *pcur;

    assert(l != NULL);

	for (pcur = l->head; pcur != NULL; pcur = pcur->next) {
		point_print(pcur);		
	}
}

/* Remove the point located at index i from list l */
int point_list_remove_index(struct point_list *l, int i)
{
    assert(l != NULL);
    int length = l->length;
    
    if (length == 0 || i >= length)
    	return -1;
    	
    struct point *cur = point_list_getindex(l, i);
    
    /* one element in list*/
    if (length == 1) {
    	l->head = NULL;
    	l->tail = NULL;
    	l->length = 0;
    } 
    /* index is head */
    else if (i == 0) {
    	struct point *next = point_list_getindex(l, i+1);
    	l->head = next;
    }
    /* index is tail*/
    else if (i == length-1) {
    	struct point *prev = point_list_getindex(l, i-1);
    	l->tail = prev;
    	prev->next = NULL;
    	l->tail = prev;
    }
    /* index is in middle*/
    else {
    	 struct point *prev = point_list_getindex(l, i-1);
    	 struct point *next = point_list_getindex(l, i+1);
    	 prev->next = next;
    }
    
    l->length--;
    free(cur);

    return 0;
}

/* Remove the first point named name from list l */
int point_list_remove_name(struct point_list *l, char *name)
{
 	assert(l != NULL);
 	assert(name != NULL);
 	
 	int index = point_list_find_name(l, name);
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
	
	int length = l->length;
	double min_d, temp_d;
	int min_i;
	
	
	if (length <= 0)
		return -1;	
		
	struct point *pcur = l->head;
	min_i = 0;
	min_d = point_distance(pcur, p);
	
	int count = 1;
	for (pcur = pcur->next; pcur != NULL; pcur = pcur->next) {
		temp_d = point_distance(pcur, p);
		if (temp_d < min_d) {
			min_d = temp_d;
			min_i = count;
		}
		count++;
	}

	return min_i;
}

void copy_point_list(struct point_list *l, struct point_list *l2)
{
	int i;
	assert(l != NULL);
    assert(l2 != NULL);
    
    point_list_init(l2, l->name);
    
    struct point *pcur = l->head;
    point_list_add(l2, pcur);
	
	for (pcur = pcur->next; pcur != NULL; pcur = pcur->next) {
		struct point temp;
		point_init(&temp, pcur->name, pcur->x, pcur->x);
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
