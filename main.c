#include <stdio.h>
#include <stdlib.h>

struct node
{
    int value;
    struct node *next;
};

struct node *new_node(int value)
{
    struct node *n = malloc(sizeof(struct node));
    if (!n)
    {
        exit(1);
    }
    n->value = value;
    n->next = NULL;
    return n;
}

struct node *generate_list(int size)
{
    if (!size)
    {
        return NULL;
    }

    struct node *list = new_node(1);
    struct node *tail = list;
    for (int i = 2; i <= size; i++)
    {
        tail->next = new_node(i);
        tail = tail->next;
    }
    return list;
}

void free_list(struct node *list)
{
    if (!list)
    {
        return;
    }

    struct node *tmp;
    while (list)
    {
        tmp = list->next;
        free(list);
        list = tmp;
    }
}

void print_list(struct node *list)
{
    printf("[");

    while (list)
    {
        printf("%d", list->value);
        if (list->next)
        {
            printf(", ");
        }
        list = list->next;
    }

    printf("]");
}

struct node *reverse_list(struct node *list)
{
    struct node *current = list;
    struct node *head = NULL;
    struct node *next = NULL;

    while (current)
    {
        next = current->next;
        current->next = head;
        head = current;
        current = next;
    }

    return head;
}

struct node *reverse_list_recursive(struct node *list, struct node *reversed)
{
    if (!list)
    {
        return reversed;
    }

    struct node *remaining = list->next;
    list->next = reversed;
    return reverse_list_recursive(remaining, list);
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("usage: %s <list-size: uint>\n", argv[0]);
        exit(1);
    }

    char *endptr = NULL;
    long int size = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || size < 0)
    {
        printf("usage: %s <list-size: uint>\n", argv[0]);
        exit(1);
    }

    struct node *list = generate_list(size);

    printf("iterative: ");
    print_list(list);
    printf(" <-> ");
    list = reverse_list(list);
    print_list(list);
    printf("\n");

    list = reverse_list(list);

    printf("recursive: ");
    print_list(list);
    printf(" <-> ");
    list = reverse_list_recursive(list, NULL);
    print_list(list);
    printf("\n");

    free_list(list);
    return 0;
}
