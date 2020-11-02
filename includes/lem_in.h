/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <aguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 12:54:56 by andrew            #+#    #+#             */
/*   Updated: 2020/11/02 15:16:17 by aguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H

# define LEM_IN_H

# include "ft_printf.h"
# include "libft.h"
# include <fcntl.h>

typedef struct	s_room
{
	char			*name;
	int				index;
	double			coord_y;
	double			coord_x;
	struct s_room	*next;
}				t_room;

typedef struct	s_solution
{
	struct s_paths		*headpaths;
	int					movements;
	struct s_solution	*next;
}				t_solution;

typedef struct	s_file
{
	char			*line;
	struct s_file	*next;
}				t_file;

typedef struct	s_paths
{
	struct s_path		*headpath;
	int					len_path;
	int					ants_go;
	struct s_paths		*next;
}				t_paths;

typedef struct	s_path
{
	int					from;
	int					to;
	int					ant;
	struct s_path		*next;
	struct s_path		*prev;
}				t_path;

typedef struct	s_pathsolver
{
	int						index;
	int						len_path;
	struct s_path			*path;
	struct s_pathtosolve	*pathtosolve;
}				t_pathsolver;

typedef struct	s_pathtosolve
{
	struct s_pathsolver			*path_solver;
	struct s_pathtosolve		*next;
}				t_pathtosolve;

typedef struct	s_queue
{
	struct s_pathsolver *path_solver;
	struct s_queue		*next;
}				t_queue;

typedef struct	s_lemin
{
	struct s_room		*rooms;
	struct s_room		*start;
	struct s_room		*end;
	struct s_solution	*head_solution;
	int					**mass;
	int					connection;
	double				ants_count;
	struct s_file		*head_file;
	int					rooms_count;
}				t_lemin;

t_path			*getlustpath(t_path *path);
int				is_path_clear(t_paths *paths);
int				isallpathsclear(t_paths *headpaths);
int				ant_scan_f(t_path *path);
int				ant_scan_b(t_path *path);
void			move_ants(t_lemin *lemin, t_path *path);
t_paths			*getthelitlest(t_paths *head);
void			getantsmany(int n, t_paths *head);
void			ants_go(t_lemin *lemin);
void			parsing(int fd, t_lemin **lemin);
void			exitlem(t_lemin **lemin, char *str, char **str_tofree);
void			c_clear(t_room *head);
int				isitroom2(char **str, t_lemin **lemin, int i);
void			parstostruct(int fd, t_lemin **lemin, char **str, int status);
void			parstostruct2(int fd, t_lemin **lemin, char **str, int status);
int				isitroom(char **str, t_lemin **lemin);
t_room			*createroom(char **str, t_lemin **lemin, int i);
int				checkroom(t_lemin **lemin, int coord_x, \
int coord_y, char *name);
void			add(t_lemin **lemin, int status, char **str);
t_room			*addrooms(t_lemin **lemin, char **str);
void			startend(int fd, t_lemin **lemin, char **str, int status);
t_room			*lastroom(t_room *rooms);
void			checkconnect(t_lemin **lemin, char **str);
int				isroom(t_lemin **lemin, char *str);
void			connection(t_lemin **lemin, char **str);
void			initmass(t_lemin **lemin);
void			clearmass(int **mass, int count);
int				getindex(t_lemin **lemin, char *str);
void			addconnect(t_lemin **lemin, char *str);
void			isvalid(t_lemin **lemin);
int				find(int **massive, int index, t_lemin *lemin);
void			findpathtoend(t_lemin **lemin);
void			antscheck(int fd, char **line, t_lemin **lemin);
void			visual(t_lemin *lemin);
int				*massvisited(t_lemin *lemin);
t_pathsolver	*createpathsolver(int index);
t_path			*solv_path(t_lemin *lemin);
t_queue			*createqueue();
void			queueadd(t_queue	*quary, t_pathsolver *pathsolver);
t_pathtosolve	*createpathtosolve(int index, t_queue *queue);
void			addpathstosolve(t_pathtosolve *paths, int index, \
t_queue *queue);
void			cleanpathtosolve(t_pathtosolve **head);
void			cleanpathsolver(t_pathsolver **pathsolver);
void			cleanpath(t_path **head);
t_path			*createpath(int from, int to);
int				createitog(int to, t_pathsolver *now, t_queue **queue, \
t_lemin *lemin);
void			addpaths(t_lemin *l, t_queue **queue, int *v, \
t_pathsolver *now);
void			processqueue(t_lemin *lem, t_queue **queue, int *visit);
int				getcountofpaths(t_pathtosolve *pathtosolve);
void			connectpath(t_pathsolver *pathsolver, t_lemin *lemin);
t_pathtosolve	*getpath(t_pathtosolve *head, int len);
void			chosebest(t_pathsolver *pathsolver, t_lemin *lemin);
void			makeshort(t_pathsolver *pathsolver, t_lemin *lemin);
char			*namebyindex(t_room *rooms, int index);
t_pathtosolve	*getshortpath(t_pathsolver *pathsolver);
void			printpath(t_path *head, t_lemin *lemin);
void			mainsolver(t_lemin *lemin);
int				getlenpath(t_path *head);
t_paths			*createpaths(t_path *head);
void			addpathtopaths(t_paths *wheretoadd, t_path *path_toadd);
t_solution		*createsolution(t_paths *head);
void			addsolution(t_solution *headsolution, t_paths *head_ofpaths);
int				pathscount(t_paths *head_ofpaths);
int				getmovements(t_paths *head_ofpaths, int n);
void			getants(t_paths *head_ofpaths, int n);
int				getcountofpathsswithpathin(t_paths *head_ofpaths);
int				specialgetnextlin(const int fd, char **line, t_lemin *lemin);
void			cleanfile(t_file *head);
void			addpathtomass(t_lemin *lemin, t_path *solved_path);
int				checkperesech(t_lemin *lemin);
int				checksamerooms(t_lemin *lemin);
void			dellperesech(t_lemin	*lemin);
t_paths			*givepaths(t_lemin *lemin);
void			findbest(t_lemin *lemin);
t_paths			*becomelastpaths(t_paths *head);
void			newsolution(t_lemin *lemin, t_solution *lastsolution);
int				connectpathspecial(t_lemin *lemin, int index, t_path *now_path);
int				findspecial(t_lemin *lemin);
t_solution		*getsolfromsoltns(int i, t_solution *head);
int				minmovementsfromsolutions(t_solution *head);
t_paths			*copypahs(t_paths *head_tocopy);
void			scpecialclearqueue(t_queue **head);
void			littlehelpfunc(t_path *now_path, int index, int i);
void			sortpaths(t_paths *head, int i);
t_paths			*compare(t_paths *head_ofpaths, t_paths *now, \
t_paths *compareto);
void			clear(t_lemin *lemin, t_path *newpath, int roomto);
t_paths			*findcurrentpath(t_paths *head, int i);
void			be3(t_path *path, t_lemin *lemin);
void			delete(t_paths **head, t_paths *todelete);
void			deletep2(t_paths **head, t_paths *todelete);
void			addspec(t_paths *head, t_paths *new);
void			fileprint(t_lemin *lemin);
void			push(t_path *current, t_lemin *lemin);
void			clearsolution(t_lemin *lemin);
#endif
