/* point_list_test.c - point list test program */

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>

/* Conditionally include the appropriate implementation header file */

#ifdef LINKED_IMPL
#include "point_list_linked.h"
#else
#include "point_list_array.h"
#endif

int main(void)
{
    struct point p1, p2, p3, p4, p5;
    struct point *p1_p;
    struct point_list l1;
    double d1;
    int i;
    
    printf("[init points A and B]\n");
    point_init(&p1, "A", 1.0, 1.0);
    point_init(&p2, "B", 4.0, 5.0);
    
    point_print(&p1);
    point_print(&p2);
    
    printf("[init list l1]\n");
    point_list_init(&l1, "List 1");
    point_list_add(&l1, &p1);
    point_list_add(&l1, &p2);
    
    point_list_print(&l1);
    
    d1 = point_distance(&p1, &p2);
    printf("distance = %lf\n", d1);

    printf("[init points C and D]\n");
    point_init(&p3, "C", 3.0, 3.0);
    point_init(&p4, "D", 11.0, 9.0);
    point_list_add(&l1, &p3);
    point_list_add(&l1, &p4);
    
    point_list_print(&l1);

	point_print(point_list_getindex(&l1, 2));



    printf("[remove index 2]\n");
    point_list_remove_index(&l1, 2);

    point_list_print(&l1);


    printf("[remove A and D]\n");
    point_list_remove_name(&l1, "A");
    point_list_remove_name(&l1, "D");

    point_list_print(&l1);

    printf("[add C and D]\n");
    
    point_list_add(&l1, &p3);
    point_list_add(&l1, &p4);
    
    point_list_print(&l1);
    
    point_init(&p5, "X", 2.0, 2.0);
    
    point_print(&p5);
  
    i = point_list_closest(&l1, &p5);
    
    printf("[Find closest point to X]\n");
    
    point_print(point_list_getindex(&l1, i));
    
    printf("[Print all points ordered near to far]\n");
    
    point_list_print_all_near_to_far(&l1, &p5);

	printf("[Print original list]\n");
	point_list_print(&l1);



    return 0;
}



