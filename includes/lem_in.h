#ifndef LEM_IN_H

# define LEM_IN_H

#include "ft_printf.h"
# include "libft.h"
#include <fcntl.h>

typedef struct	s_room
{
	char			*name;
	int				index;
	int				coord_y;
	int				coord_x;
	struct	s_room 	*next;
	
}				t_room;

typedef struct	s_lemin
{
	struct	s_room	*rooms;
	struct	s_room	*start;
	struct	s_room	*end;
	int				**mass;
	int				connection;
	int				ants_count;
	int				rooms_count;
	
}				t_lemin;

void	parsing(int fd, t_lemin *lemin);
void    exitlem(t_lemin **lemin, char *str, char *str_tofree);
void	c_clear(t_room *head);
int		isitroom2(char *str, t_lemin *lemin, int i);
void	parstostruct(int fd, t_lemin *lemin, char **str, int status);
void	parstostruct2(int fd, t_lemin *lemin, char **str, int status);
int		isitroom(char *str, t_lemin *lemin);
t_room	*createroom(char *str, t_lemin *lemin);
int		checkroom(t_lemin *lemin, int coord_x, int coord_y, char *name);
void 	add(t_lemin *lemin, int status, char **str);
t_room 	*addrooms(t_lemin *lemin, char *str);
void 	startend(int fd, t_lemin *lemin, char **str, int status);
t_room 	*lastroom(t_room *rooms);
void	checkconnect(t_lemin *lemin, char **str);
int		isroom(t_lemin *lemin, char *str);
void	connection(t_lemin *lemin, char **str);
void	initmass(t_lemin *lemin);
void	clearmass(int **mass, int count);
int		getindex(t_lemin *lemin, char *str);
void	addconnect(t_lemin *lemin, char *str);
void	isvalid(t_lemin *lemin);
int		find(int **massive, int index, t_lemin *lemin);
void	findpathtoend(t_lemin *lemin);
void	antscheck(int fd, char **line, t_lemin *lemin);


#endif