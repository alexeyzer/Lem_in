#ifndef LEM_IN_H

# define LEM_IN_H

#include "ft_printf.h"
# include "libft.h"
#include <fcntl.h>

typedef struct	s_room
{
	char			*name;
	int				index;
	double				coord_y;
	double				coord_x;
	struct	s_room 	*next;
	
}				t_room;

typedef struct	s_path
{
	int					from;
	int					to;
	struct	s_path		*next;
}				t_path;

typedef struct	s_pathsolver
{
	int					index;
	int					len_path;
	struct	s_path		*path;
	struct	s_pathtosolve	*pathtosolve;
	
}				t_pathsolver;

typedef struct	s_pathtosolve
{
	struct	s_pathsolver	*path_solver;
	struct	s_pathtosolve		*next;
}				t_pathtosolve;

typedef struct	s_queue
{
	struct	s_pathsolver	*path_solver;
	struct	s_queue			*next;
}				t_queue;


typedef struct	s_lemin
{
	struct	s_room	*rooms;
	struct	s_room	*start;
	struct	s_room	*end;
	int				**mass;
	int				connection;
	double				ants_count;
	int				rooms_count;
	
}				t_lemin;

void	parsing(int fd, t_lemin **lemin);
void    exitlem(t_lemin **lemin, char *str, char **str_tofree);
void	c_clear(t_room *head);
int		isitroom2(char **str, t_lemin **lemin, int i);
void	parstostruct(int fd, t_lemin **lemin, char **str, int status);
void	parstostruct2(int fd, t_lemin **lemin, char **str, int status);
int		isitroom(char **str, t_lemin **lemin);
t_room	*createroom(char **str, t_lemin **lemin);
int		checkroom(t_lemin **lemin, int coord_x, int coord_y, char *name);
void 	add(t_lemin **lemin, int status, char **str);
t_room 	*addrooms(t_lemin **lemin, char **str);
void 	startend(int fd, t_lemin **lemin, char **str, int status);
t_room 	*lastroom(t_room *rooms);
void	checkconnect(t_lemin **lemin, char **str);
int		isroom(t_lemin **lemin, char *str);
void	connection(t_lemin **lemin, char **str);
void	initmass(t_lemin **lemin);
void	clearmass(int **mass, int count);
int		getindex(t_lemin **lemin, char *str);
void	addconnect(t_lemin **lemin, char *str);
void	isvalid(t_lemin **lemin);
int		find(int **massive, int index, t_lemin *lemin);
void	findpathtoend(t_lemin **lemin);
void	antscheck(int fd, char **line, t_lemin **lemin);
void	visual(t_lemin *lemin);
int		*massvisited(t_lemin *lemin);
t_pathsolver	*createpathsolver(int index);
void			solv(t_lemin *lemin);
t_queue			*createqueue();
void			queueadd(t_queue	*quary, t_pathsolver *pathsolver);
t_pathtosolve	*createpathtosolve(int index, t_queue *queue);
void			addpathstosolve(t_pathtosolve *paths, int index, t_queue *queue);
void			cleanpathtosolve(t_pathtosolve **head);
void			cleanpathsolver(t_pathsolver **pathsolver);
void			cleanpath(t_path **head);
t_path			*createpath(int from, int to);
void			createitog(int to, t_pathsolver *now);
void			addpaths(t_lemin *lem, t_queue *queue, int *visit, t_pathsolver *now);
void			processqueue(t_lemin *lem, t_queue **queue, int *visit);
int				getcountofpaths(t_pathtosolve *pathtosolve);
void			connectpath(t_pathsolver *pathsolver, t_lemin *lemin);
t_pathtosolve	*getpath(t_pathtosolve *head, int len);
void			chosebest(t_pathsolver *pathsolver, t_lemin *lemin);
void			makeshort(t_pathsolver *pathsolver, t_lemin *lemin);
char			*namebyindex(t_room *rooms, int index);
t_pathtosolve	*getshortpath(t_pathsolver *pathsolver);


#endif