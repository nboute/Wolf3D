t_map	*create_slide(t_map	*map, int densitx)
{
	int	x;
	int	y;
	int	val[2];
	int	walls;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		if (y > map->height / 10)
			val[1] = 4;
		if (y > (map->height * 3) / 10)
			val[1] = 5;
		if (y > (map->height * 3) / 5)
			val[1] = 6;
		if (walls > val[1] - 1)
			walls = rand() % val[1];
		else
			walls ++;
			val[0] = 0;
		while (x < map->width)
		{
			if (y < 5 || y >= map->height - 10 || x < 5 || x >= map->width - 5)
				map->map[x][y] = val[1] - 2;
			else if (y < 20)
				map->map[x][y] = 0;
			else if (!walls)
			{
				if (rand() % densitx < densitx - densitx / 3 - 1)
				{
					map->map[x][y] = 0;
					val[0]++;
				}
				else
					map->map[x][y] = 1;
			}
			else
				map->map[x][y] = 0;
			x++;
		}
		if (!val[0])
			map->map[(rand() % (map->width - 10)) + 5][y] = 0;
		y++;
	}

}
