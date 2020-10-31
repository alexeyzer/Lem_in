#include "lem_in.h"

void ant_move(int *ants, t_path *path)
{
	path->ant = 1;
	*ants--;
}

void ants_go(t_lemin *lemin)
{
	int ants;
	t_path *path;

	ants = lemin->head_solution->headpaths->ants_go;
	path = lemin->head_solution->headpaths->headpath;
	ant_move(&ants, path);
	while (ants)
	{
		while (path->next)
		{
			if(!path->ant && path->next->ant)
				ant_move(&ants, path);
		}
		path = lemin->head_solution->headpaths->headpath;	
	}
}
