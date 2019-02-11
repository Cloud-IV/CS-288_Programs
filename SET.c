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
        if (n -> element == element) return element;
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
    if (SET_contains(set, element) == element)
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
    struct Node* node;

    for (node = s.head; node != NULL; node = node -> next)
    {
        if (SET_contains(&s, node -> element) == SET_contains(&t, node -> element)) SET_remove(&t, node -> element);
    }

    struct Set uni = s;
    for (node = uni.head; node != NULL; node = node -> next)
    {
        if (node -> next == NULL)
        {
            node -> next = t.head;
            break;
        }
    }

    return s;
}

struct Set SET_intersection(struct Set s, struct Set t)
{
    struct Set inter;
    inter.head = NULL;
    inter.tail = NULL;

    return inter;
}

struct Set SET_difference(struct Set s, struct Set t)
{
    /* return s - t */
    return s;
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
    SET_add(&test, 1);
    SET_add(&test, 2);
    SET_add(&test, 3);
    printf("%d\n", SET_contains(&test, 2));
    SET_remove(&test, 2);
    printf("%d\n", SET_contains(&test, 2));

    printf("min: %d, max: %d\n", SET_min(&test), SET_max(&test));

    struct Node* node;
    for (node = test.head; node != NULL; node = node -> next) printf("%d ", node -> element);
    printf("\n");
    struct Set test2 = SET_new();
    SET_add(&test2, 4);
    SET_add(&test2, 3);
    SET_union(test, test2);
    for (node = test.head; node != NULL; node = node -> next) printf("%d ", node -> element);
    printf("\n");

    return 0;
}