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

int SET_cardinality(struct Set *set)
{
    struct Node* n;
    int nodeCounter = 0;

    for (n = set -> head; n != NULL; n = n -> next) nodeCounter++;
    return nodeCounter;
}

int SET_contains(struct Set *set, int element)
{
    struct Node* n;

    for (n = set -> head; n != NULL; n = n -> next)
    {
        if (n -> element == element) return 1;
    }
    return 0;
}

void SET_add(struct Set *set, int element)
{
    if(SET_contains(set, element) == 0)
    {
        struct Node* node = malloc(sizeof(struct Node));
        node -> element = element;
        node -> next = set -> head;
        if (SET_cardinality(set) == 0) set -> tail = node;
        set -> head = node;
    }
}

void SET_remove(struct Set *set, int element)
{
    if (SET_contains(set, element) == 1)
    {
        struct Node* node = set -> head;
        if (node -> element == element)
        {
            set -> head = node -> next;
            if (SET_cardinality(set) == 0) set -> tail = NULL;
            free(node);
        }
        else
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
    struct Set uni = SET_new();
    struct Set uni2 = SET_new();
    struct Node* node;

    for (node = s.head; node != NULL; node = node -> next) SET_add(&uni, node -> element);
    for (node = t.head; node != NULL; node = node -> next) SET_add(&uni2, node -> element);


    for (node = uni.head; node != NULL; node = node -> next)
    {
        if (SET_contains(&uni, node -> element) == 1 && SET_contains(&uni2, node -> element) == 1) SET_remove(&uni2, node -> element);
    }

    for (node = uni.head; node != NULL; node = node -> next)
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

    for (node = s.head; node != NULL; node = node -> next)
    {
        if (SET_contains(&s, node -> element) == 1 && SET_contains(&t, node -> element) == 1) SET_add(&inter, node -> element);
    }

    return inter;
}

struct Set SET_difference(struct Set s, struct Set t)
{
    struct Set diff = SET_new();
    struct Node* node;

    for (node = s.head; node != NULL; node = node -> next)
    {
        if (SET_contains(&s, node -> element) != SET_contains(&t, node -> element)) SET_add(&diff, node -> element);
    }

    return diff;
}

int SET_min(struct Set *set)
{
    struct Node* n = set -> head;
    int minElement = n -> element;

    for (n = set -> head; n != NULL; n = n -> next)
    {
        if (n -> element < minElement) minElement = n -> element;
    }
    return minElement;
}

int SET_max(struct Set *set)
{
    struct Node* n = set -> head;
    int maxElement = n -> element;

    for (n = set -> head; n != NULL; n = n -> next)
    {
        if (n -> element > maxElement) maxElement = n -> element;
    }
    return maxElement;
}

int main()
{
    struct Set test = SET_new();
    struct Node* node;

    SET_add(&test, 0);
    SET_add(&test, 1);
    SET_add(&test, 2);
    SET_add(&test, 3);
    SET_add(&test, -2);
    printf("Elements in set 1: \n");
    for (node = test.head; node != NULL; node = node -> next) printf("%d ", node -> element);
    printf("\n");

    printf("Contains 2 test: %d\n", SET_contains(&test, 2));
    SET_remove(&test, 2);
    printf("Contains 2 test: %d\n", SET_contains(&test, 2));

    printf("min: %d, max: %d\n", SET_min(&test), SET_max(&test));

    printf("Elements in set 1: \n");
    for (node = test.head; node != NULL; node = node -> next) printf("%d ", node -> element);
    printf("\n");

    struct Set test2 = SET_new();
    SET_add(&test2, 4);
    SET_add(&test2, 3);
    SET_add(&test2, 0);
    printf("Elements in set 2: \n");
    for (node = test2.head; node != NULL; node = node -> next) printf("%d ", node -> element);
    printf("\n");

    struct Set uni = SET_union(test, test2);
    printf("Elements in union of set 1 & set 2: \n");
    for (node = uni.head; node != NULL; node = node -> next) printf("%d ", node -> element);
    printf("\n");

    struct Set inter = SET_intersection(test, test2);
    printf("Elements in intersection of set 1 and set 2: \n");
    for (node = inter.head; node != NULL; node = node -> next) printf("%d ", node -> element);
    printf("\n");

    struct Set diff = SET_difference(test, test2);
    printf("Set difference of set 1 & set 2: \n");
    for (node = diff.head; node != NULL; node = node -> next) printf("%d ", node -> element);
    printf("\n");

    return 0;
}