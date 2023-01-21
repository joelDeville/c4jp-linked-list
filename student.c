#include <assert.h>
#include "student.h"

static int gpa_comparator(struct ll_node *node1, struct ll_node *node2) {
	//retrieving pointers to the node's containing structure
	struct student *s1 = LL_ENTRY(node1, struct student, node);
	struct student *s2 = LL_ENTRY(node2, struct student, node);

	if (s1->gpa > s2->gpa) {
		return 1;
	} else if (s1->gpa < s2->gpa) {
		return -1;
	}

	return 0;
}

struct student *student_worst_performer(struct student *list) {
    assert(list != NULL);

    return LL_ENTRY(ll_min(&list->node, gpa_comparator), struct student, node);
}

struct student *student_valedictorian(struct student *list) {
    assert(list != NULL);
    return LL_ENTRY(ll_max(&list->node, gpa_comparator), struct student, node);
}

static bool honor_roll_qualify(struct ll_node *n) {
    struct student *st = LL_ENTRY(n, struct student, node);
    return st->gpa >= 3.5;
}

struct student *student_honour_roll(struct student *list) {
    assert(list != NULL);
    
    struct ll_node *head = ll_filter(&list->node, honor_roll_qualify);
    return (head == NULL) ? NULL : LL_ENTRY(head, struct student, node);
}
