
#include "lem_in.h"

t_lemin *init_lemin()
{
    t_lemin *lemin;

    lemin = NULL;
    if (!(lemin=malloc(sizeof(t_lemin))))
        return (NULL);
    lemin->ants_count = 0;
    lemin->rooms_count = 0;
    lemin->rooms = NULL;
    lemin->mass = NULL;
    lemin->start = NULL;
    lemin->connection = 0;
    lemin->end = NULL;
    return (lemin);
}

int main(int argc, char **argv)
{
    int fd;
    t_lemin *lemin;
    char *line;

    lemin = NULL;
    fd = 0;
    line = NULL;
    if (argc == 2)
    {
        fd = open(argv[1], O_RDONLY);
        if (fd < 0)
        {
            ft_printf("Invalid file\n");
            return (0);
        }
    }
    lemin = init_lemin();
    parsing(fd, lemin);
    isvalid(lemin);
    return (0);
}

void    exitlem(t_lemin **lemin, char *str, char *str_tofree)
{
    t_room *head;

    head = NULL;
    if (str_tofree != NULL)
        free(str_tofree);
    if (str != NULL)
        ft_printf("%s", str);
    if (*lemin != NULL)
    {
        head = (*lemin)->rooms;
        (*lemin)->rooms = NULL;
        if (head != NULL)
                c_clear(head);
        if ((*lemin)->mass != NULL)
            clearmass((*lemin)->mass, (*lemin)->rooms_count);
        (*lemin)->mass = NULL;
        free(*lemin);
        *lemin = NULL;
    }
    exit(0);
}

void c_clear(t_room *head)
{
    while(head->next != NULL)
    {
        c_clear(head->next);
        head->next = NULL;
    }
    free(head);
    head = NULL;
}
