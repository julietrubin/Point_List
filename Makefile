all: point_list_test_array point_list_test_linked

point_list_test_array : point_list_test.c point_list_array.c
	gcc -g -o point_list_test_array point_list_test.c point_list_array.c -lm

point_list_test_linked : point_list_test.c point_list_linked.c
	gcc -g -o point_list_test_linked -DLINKED_IMPL point_list_test.c point_list_linked.c -lm

clean :
	/bin/rm -rf point_list_test_array point_list_test_linked *.dSYM
	
