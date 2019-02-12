/*--------------------------------------------------------------------------------------------------------------------*/
/* Author: Abrar Rouf                                                                                                 */
/* SET.c                                                                                                              */
/* -------------------------------------------------------------------------------------------------------------------*/
#include <stdlib.h>
#include <stdio.h>


struct Node
{
    int element;
    struct Node* next;
};

struct Set
{
    struct Node* head;
    struct Node* tail;
};

struct Set SET_new()
{
    struct Set set;
    set.head = NULL;
    set.tail = NULL;
    return set;
}

int SET_cardinality(struct Set *set)    /*traverses nodes in set and counts number of nodes visited*/
{
    struct Node* n;
    int nodeCounter = 0;

    for (n = set -> head; n != NULL; n = n -> next) nodeCounter++;
    return nodeCounter;
}

int SET_contains(struct Set *set, int element)  /*traverses nodes and returns 1 if desired element is found*/
{
    struct Node* n;

    for (n = set -> head; n != NULL; n = n -> next)
    {
        if (n -> element == element) return 1;  /*1 represents boolean true (element was found)*/
    }
    return 0;   /*0 represents boolean false (element was not found)*/
}

void SET_add(struct Set *set, int element)  /*adds new node with desired element if it does not already exist*/
{
    if(SET_contains(set, element) == 0)     /*checks to see if element is already in set*/
    {
        struct Node* node = malloc(sizeof(struct Node));
        node -> element = element;
        node -> next = set -> head;
        if (SET_cardinality(set) == 0) set -> tail = node;
        set -> head = node;
    }
}

void SET_remove(struct Set *set, int element)   /*removes node with desired element from set if it exists*/
{
    if (SET_contains(set, element) == 1)        /*checks if node with element exists in set*/
    {
        struct Node* node = set -> head;
        if (node -> element == element)         /*test if first node contains desired element*/
        {
            set -> head = node -> next;
            if (SET_cardinality(set) == 0) set -> tail = NULL;
            free(node);
        }
        else                                    /*iterate through nodes in set until element is found*/
        {
            struct Node* prevNode = NULL;
            for (node = set -> head; node != NULL; prevNode = node, node = node -> next)
            {
                if (node -> element == element)
                {
                    prevNode -> next = node -> next;
                    free(node);
                    break;
                }
            }
        }
    }
}

struct Set SET_union(struct Set s, struct Set t)
{
    struct Set uni = SET_new(); /*will contain copies of the passed sets so they are not modified by function calls*/
    struct Set uni2 = SET_new();
    struct Node* node;

    for (node = s.head; node != NULL; node = node -> next) SET_add(&uni, node -> element); /*populates copies of sets*/
    for (node = t.head; node != NULL; node = node -> next) SET_add(&uni2, node -> element);


    for (node = uni.head; node != NULL; node = node -> next)    /*removes repeats of elements in set to be returned*/
    {
        if (SET_contains(&uni, node -> element) == 1 && SET_contains(&uni2, node -> element) == 1) SET_remove(&uni2, node -> element);
    }

    for (node = uni.head; node != NULL; node = node -> next)    /*adds head of second set to end of set to be returned*/
    {
        if (node -> next == NULL)
        {
            node -> next = uni2.head;
            break;
        }
    }

    return uni;
}

struct Set SET_intersection(struct Set s, struct Set t)
{
    struct Set inter = SET_new();
    struct Node* node;

    for (node = s.head; node != NULL; node = node -> next)  /*adds new node containing an element if the element if found in both sets*/
    {
        if (SET_contains(&s, node -> element) == 1 && SET_contains(&t, node -> element) == 1) SET_add(&inter, node -> element);
    }

    return inter;
}

struct Set SET_difference(struct Set s, struct Set t)   /*returns set of integers in set s but not in set t*/
{
    struct Set diff = SET_new();
    struct Node* node;

    for (node = s.head; node != NULL; node = node -> next)  /*adds new node with element if element is in set s but not set t*/
    {
        if (SET_contains(&s, node -> element) != SET_contains(&t, node -> element)) SET_add(&diff, node -> element);
    }

    return diff;
}

int SET_min(struct Set *set)    /*iterates through set and finds smallest element*/
{
    struct Node* n = set -> head;
    int minElement = n -> element;  /*initializes smallest element to element of first node*/

    for (n = set -> head; n != NULL; n = n -> next)
    {
        if (n -> element < minElement) minElement = n -> element;
    }
    return minElement;
}

int SET_max(struct Set *set)    /*iterates through set and finds largest element*/
{
    struct Node* n = set -> head;
    int maxElement = n -> element;  /*initializes largest element to element of first node*/

    for (n = set -> head; n != NULL; n = n -> next)
    {
        if (n -> element > maxElement) maxElement = n -> element;
    }
    return maxElement;
}

int main()
{
    struct Set test = SET_new();    /*creates first test set*/
    struct Node* node;

    SET_add(&test, 0);              /*population of first test set*/
    SET_add(&test, 1);
    SET_add(&test, 2);
    SET_add(&test, 3);
    SET_add(&test, -2);
    printf("Elements in set 1: \n");    /*check if elements sucessfully added*/
    for (node = test.head; node != NULL; node = node -> next) printf("%d ", node -> element);
    printf("\n");

    printf("Contains 2 test: %d\n", SET_contains(&test, 2));    /*check if "2" is in first set before removal*/
    SET_remove(&test, 2);
    printf("Contains 2 test: %d\n", SET_contains(&test, 2));    /*check if "2" is in first set after removal*/

    printf("min: %d, max: %d\n", SET_min(&test), SET_max(&test));   /*prints min and max of first set after "2" removal*/

    printf("Elements in set 1: \n");    /*print elements currently in first test set*/
    for (node = test.head; node != NULL; node = node -> next) printf("%d ", node -> element);
    printf("\n");

    struct Set test2 = SET_new();   /*creates second test set*/
    SET_add(&test2, 4);             /*population of second test set*/
    SET_add(&test2, 3);
    SET_add(&test2, 0);
    printf("Elements in set 2: \n");/*prints elements in second test set*/
    for (node = test2.head; node != NULL; node = node -> next) printf("%d ", node -> element);
    printf("\n");

    struct Set uni = SET_union(test, test2);    /*test of union between test and test2 sets*/
    printf("Elements in union of set 1 & set 2: \n");
    for (node = uni.head; node != NULL; node = node -> next) printf("%d ", node -> element);
    printf("\n");

    struct Set inter = SET_intersection(test, test2);   /*test of intersection between test and test2 sets*/
    printf("Elements in intersection of set 1 and set 2: \n");
    for (node = inter.head; node != NULL; node = node -> next) printf("%d ", node -> element);
    printf("\n");

    struct Set diff = SET_difference(test, test2);  /*test of set difference between test and test2 sets*/
    printf("Set difference of set 1 & set 2: \n");
    for (node = diff.head; node != NULL; node = node -> next) printf("%d ", node -> element);
    printf("\n");

    return 0;
}