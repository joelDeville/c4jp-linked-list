#include <assert.h>
#include "linked_list.h"

//this linked list is implemented using a doubly linked, linear list
//it is NOT circular
void ll_init(struct ll_node *node) {
    assert(node != NULL);
   node->prev = NULL;
   node->next = NULL;
}

bool ll_has_next(struct ll_node *node) {
    assert(node != NULL);
    return node->next != NULL;
}

bool ll_has_prev(struct ll_node *node) {
    assert(node != NULL);
    return node->prev != NULL;
}

struct ll_node *ll_next(struct ll_node *node) {
    assert(node != NULL);
    return node->next;
}

struct ll_node *ll_prev(struct ll_node *node) {
    assert(node != NULL);
    return node->prev;
}

size_t ll_size(struct ll_node *head) {
    assert(head != NULL);
    size_t size = 0;

    struct ll_node *cur = head;
    while (cur != NULL) {
	    cur = cur->next;
	    size++;
    }

    return size;
}

struct ll_node *ll_head(struct ll_node *list) {
   assert(list != NULL);
   
   struct ll_node *head = list;
   while (head->prev != NULL) {
	   head = head->prev;
   }

   return head;
}

struct ll_node *ll_tail(struct ll_node *list) {
    assert(list != NULL);
    
    struct ll_node *tail = list;
    while (tail->next != NULL) {
	    tail = tail->next;
    }
    return tail;
}

struct ll_node *ll_get(struct ll_node *node, size_t index) {
    assert(node != NULL);

    struct ll_node *cur = node;
    int ind = 0;
    while (ind < index && cur != NULL) {
	cur = cur->next;
	ind++;
    }

    return cur;
}

void ll_insert_before(struct ll_node *new, struct ll_node *existing) {
    assert(new != NULL);
    assert(existing != NULL);

    new->prev = existing->prev;
    new->next = existing;
    
    //checking if existing node has prior element
    if (existing->prev != NULL) {
	existing->prev->next = new;
    }

    existing->prev = new;
}

void ll_insert_after(struct ll_node *new, struct ll_node *existing) {
    assert(new != NULL);
    assert(existing != NULL);
    
    new->prev = existing;
    new->next = existing->next;

    //checking if node after exists
    if (existing-> next != NULL) {
	    existing->next->prev = new;
    }

    existing->next = new;
}

void ll_insert_first(struct ll_node *new, struct ll_node *list) {
    assert(new != NULL);
    assert(list != NULL);
    
    //finding head of this list
    struct ll_node *head = ll_head(list);
    //adding new node as new first
    new->prev = NULL;
    new->next = head;
    head->prev = new;
}

void ll_insert_last(struct ll_node *new, struct ll_node *list) {
    assert(new != NULL);
    assert(list != NULL);
    
    //finding tail
    struct ll_node *tail = ll_tail(list);
    tail->next = new;
    new->prev = tail;
    new->next = NULL;
}

void ll_remove(struct ll_node *node) {
    assert(node != NULL);
    
    if (node->prev != NULL) {
	    node->prev->next = node->next;
    }

    if (node->next != NULL) {
	    node->next->prev = node->prev;
    }
}

struct ll_node *ll_min(struct ll_node *list, ll_comparator_t comparator) {
   assert(list != NULL);
   assert(comparator != NULL);
   
   struct ll_node* min_val = NULL;
   struct ll_node* cur = ll_head(list);
   while (cur != NULL) {
	   if (min_val == NULL) {
		   min_val = cur;
	   } else if (comparator(min_val, cur) > 0) {
		   min_val = cur;
	   }
	   cur = cur->next;
   }
   return min_val;
}

struct ll_node *ll_max(struct ll_node *list, ll_comparator_t comparator) {
    assert(list != NULL);
    assert(comparator != NULL);
    
    struct ll_node* max_val = NULL;
    struct ll_node* cur = ll_head(list);
    while (cur != NULL) {
	if (max_val == NULL) {
		max_val = cur;
	} else if (comparator(max_val, cur) < 0) {
		max_val = cur;
	}
	cur = cur->next;
    }
    return max_val;
}

struct ll_node *ll_filter(struct ll_node *list, ll_predicate_t predicate) {
    assert(list != NULL);
    assert(predicate != NULL);

    struct ll_node *head = NULL;
    struct ll_node *cur = ll_head(list);

    while (cur != NULL) {
	if (!predicate(cur)) {
		//remove node from this linked list if it does not match
		ll_remove(cur);
		
		//I know this is the head node, so set head to the next one
		if (cur->prev == NULL) {
			head = cur->next;
		}
	}
	cur = cur->next;
    }

    return head;
}
