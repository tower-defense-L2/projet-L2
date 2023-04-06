#include "../include/map.h"


#define PLACE 0
#define RETRY 1
#define SKIP 2

unsigned int _seed;
map_T *_map;

typedef struct obstacle_S {
    int largeur;
    int hauteur;
    char *nom;
} obstacle_T;

obstacle_T obstacles[] = {
        {1, 1, NULL},
        {1, 2, NULL},
        {2, 1, NULL},
        {2, 2, NULL},
        {3, 1, NULL},
        {3, 2, NULL},
        {1, 3, NULL},
        {2, 3, NULL},
        {3, 3, NULL},
};

int generate_obstacle(int nb, position_T *blacklist, int blacklist_size) {
  int i, x, y, j, k, state = PLACE, try = 0, skipped = 0;
  for (i = 0; i < nb; i++) {
    x = rand() % HAUTEUR;
    y = rand() % LARGEUR;
    for (j = 0; j < blacklist_size; j++) {
      if (try >= 10) {
        try = 0;
        state = SKIP;
        skipped++;
        break;
      }
      if ((x == blacklist[j].x && y == blacklist[j].y) || _map->cases[x][y]->type == OBSTACLE) {
        try++;
        i--;
        state = RETRY;
        break;
      }
    }
    if (state == SKIP || state == RETRY) {
      continue;
    }

    obstacle_T obstacle = obstacles[rand() % (sizeof(obstacles) / sizeof(obstacle_T))];
    if (x + obstacle.hauteur >= HAUTEUR) {
      x = HAUTEUR - obstacle.hauteur - 1;
    }
    if (y + obstacle.largeur >= LARGEUR) {
      y = LARGEUR - obstacle.largeur - 1;
    }
    state = PLACE;
    for (j = 0; j < obstacle.hauteur; j++) {
      for (k = 0; k < obstacle.largeur; k++) {
        if (try >= 10) {
          try = 0;
          state = SKIP;
          skipped++;
          break;
        }
        if (_map->cases[x + j][y + k]->type == OBSTACLE) {
          try++;
          state = RETRY;
          i--;
          break;
        }
      }
      if (state != PLACE) {
        break;
      }
    }
    if (state == SKIP || state == RETRY) {
      continue;
    }
    for (j = 0; j < obstacle.hauteur; j++) {
      for (k = 0; k < obstacle.largeur; k++) {
        _map->cases[x + j][y + k]->type = OBSTACLE;
      }
    }
  }
  return skipped;
}

position_T *create_pos(int x, int y) {
  position_T *pos = malloc(sizeof(position_T));
  pos->x = x;
  pos->y = y;
  return pos;
}

void a_star(int tab[HAUTEUR][LARGEUR], position_T start) {
  int i, j;
  for (i = 0; i < HAUTEUR; ++i) {
    for (j = 0; j < LARGEUR; ++j) {
      tab[i][j] = get_case(i, j)->type == OBSTACLE ? -10 : -1;
    }
  }

  file_T file;
  file_init(&file);
  file_push(&file, &start);
  tab[start.x][start.y] = 0;
  position_T *affected = malloc(sizeof(position_T) * 4);
  position_T *new_pos;
  while (!file_is_empty(&file)) {
    position_T *pos = file_pop(&file);
    int x = pos->x;
    int y = pos->y;
    int cost = tab[x][y];
    int affected_size = 0;
    if (x > 0 && _map->cases[x - 1][y]->type != OBSTACLE && tab[x - 1][y] == -1) {
      new_pos = create_pos(x - 1, y);
      file_push(&file, new_pos);
      tab[x - 1][y] = cost + 1;
      affected[affected_size++] = *new_pos;
    }
    if (x < HAUTEUR - 1 && _map->cases[x + 1][y]->type != OBSTACLE && tab[x + 1][y] == -1) {
      new_pos = create_pos(x + 1, y);
      file_push(&file, new_pos);
      tab[x + 1][y] = cost + 1;
      affected[affected_size++] = *new_pos;
    }
    if (y > 0 && _map->cases[x][y - 1]->type != OBSTACLE && tab[x][y - 1] == -1) {
      new_pos = create_pos(x, y - 1);
      file_push(&file, new_pos);
      tab[x][y - 1] = cost + 1;
      affected[affected_size++] = *new_pos;
    }
    if (y < LARGEUR - 1 && _map->cases[x][y + 1]->type != OBSTACLE && tab[x][y + 1] == -1) {
      new_pos = create_pos(x, y + 1);
      file_push(&file, new_pos);
      tab[x][y + 1] = cost + 1;
      affected[affected_size++] = *new_pos;
    }
  }
  free(affected);
}

void create_path(int tab[HAUTEUR][LARGEUR], position_T end) {
  int x = end.x;
  int y = end.y;
  int cost = tab[x][y];
  tab[x][y] = 100;
  while (cost != 0) {
    if (x > 0 && tab[x - 1][y] == cost - 1) {
      x--;
    } else if (x < HAUTEUR - 1 && tab[x + 1][y] == cost - 1) {
      x++;
    } else if (y > 0 && tab[x][y - 1] == cost - 1) {
      y--;
    } else if (y < LARGEUR - 1 && tab[x][y + 1] == cost - 1) {
      y++;
    }
    tab[x][y] = 100;
    _map->cases[x][y]->type = CHEMIN;
    cost--;
  }
  tab[x][y] = 1000;
  case_T *old_caset, *caset = _map->cases[x][y];
  while (x != end.x || y != end.y) {
    if (caset->type == CHEMIN) {
      if (x > 0 && (tab[x - 1][y] == 100 || (x - 1 == end.x && y == end.y))) {
        x--;
      } else if (x < HAUTEUR - 1 && (tab[x + 1][y] == 100 || (x + 1 == end.x && y == end.y))) {
        x++;
      } else if (y > 0 && (tab[x][y - 1] == 100 || (y - 1 == end.y && x == end.x))) {
        y--;
      } else if (y < LARGEUR - 1 && (tab[x][y + 1] == 100 || (y + 1 == end.y && x == end.x))) {
        y++;
      }
      tab[x][y] *= 10;
      old_caset = caset;
      caset = _map->cases[x][y];
      position_T pos = {x, y};
      caset->case_pl.chemin.position = pos;
      old_caset->case_pl.chemin.suivant = &caset->case_pl.chemin;
    }
  }
  old_caset = caset;
  caset = _map->cases[end.x][end.y];
  caset->type = CHEMIN;
  caset->case_pl.chemin.position = end;
  old_caset->case_pl.chemin.suivant = &caset->case_pl.chemin;
}

void ajout_emplacement(){
	for (int i = 0; i < HAUTEUR; ++i){
		for (int j = 0; j < LARGEUR; ++j){
			if (_map->cases[i][j]->type == CHEMIN){
        _map->cases[i][j]->case_pl.chemin.enemi = NULL;
				if (i > 0 && _map->cases[i - 1][j]->type == VIDE){
					_map->cases[i - 1][j]->type = EMPLACEMENT;
					_map->cases[i - 1][j]->case_pl.emplacement.tour = NULL;
				}
				if (i > 0 && j > 0 && _map->cases[i - 1][j - 1]->type == VIDE){
					_map->cases[i - 1][j - 1]->type = EMPLACEMENT;
					_map->cases[i - 1][j - 1]->case_pl.emplacement.tour = NULL;
				}
				if (i > 0 && j < LARGEUR - 1 && _map->cases[i - 1][j + 1]->type == VIDE){
					_map->cases[i - 1][j + 1]->type = EMPLACEMENT;
					_map->cases[i - 1][j + 1]->case_pl.emplacement.tour = NULL;
				}
				if (i < HAUTEUR - 1 && _map->cases[i + 1][j]->type == VIDE){
					_map->cases[i + 1][j]->type = EMPLACEMENT;
					_map->cases[i + 1][j]->case_pl.emplacement.tour = NULL;
				}
				if (i < HAUTEUR - 1 && j > 0 && _map->cases[i + 1][j - 1]->type == VIDE){
					_map->cases[i + 1][j - 1]->type = EMPLACEMENT;
					_map->cases[i + 1][j - 1]->case_pl.emplacement.tour = NULL;
				}
				if (i < HAUTEUR - 1 && j < LARGEUR - 1 && _map->cases[i + 1][j + 1]->type == VIDE){
					_map->cases[i + 1][j + 1]->type = EMPLACEMENT;
					_map->cases[i + 1][j + 1]->case_pl.emplacement.tour = NULL;
				}
				if (j > 0 && _map->cases[i][j - 1]->type == VIDE){
					_map->cases[i][j - 1]->type = EMPLACEMENT;
					_map->cases[i][j - 1]->case_pl.emplacement.tour = NULL;
				}
				if (j < LARGEUR - 1 && _map->cases[i][j + 1]->type == VIDE){
					_map->cases[i][j + 1]->type = EMPLACEMENT;
					_map->cases[i][j + 1]->case_pl.emplacement.tour = NULL;
				}
			}
		}
	}
}

void generate_map(unsigned int seed, position_T start, position_T end, void (*callback)(map_T *, position_T)) {
  _seed = seed;
  srand(seed);
  _map = malloc(sizeof(map_T) + sizeof(case_T **) * HAUTEUR);
  int i, j;
  for (i = 0; i < HAUTEUR; ++i) {
    for (j = 0; j < LARGEUR; ++j) {
      _map->cases[i][j] = malloc(sizeof(case_T));
      _map->cases[i][j]->type = VIDE;
    }
  }
  position_T blacklisted_pos[] = {start, end};
  int skipped = generate_obstacle(100, blacklisted_pos, 2);
  int calculated_path[HAUTEUR][LARGEUR];
  a_star(calculated_path, start);
  if (calculated_path[end.x][end.y] == -1) {
    printf("No path found\nTrying to find a new end position\n");
    int x, found = 0;
    for (x = 0; x < LARGEUR && !found; ++x) {
      found = calculated_path[HAUTEUR - 1][x] != -1;
      end.x = HAUTEUR - 1;
      end.y = x;
      if (found) {
        printf("Found a new end position at (%d, %d)\n", end.x, end.y);
      }
    }
    if (!found) {
      printf("No path found\n");
    }
  }
  create_path(calculated_path, end);
//  print_meta_array(calculated_path);
  ajout_emplacement();

}

void destroy_map() {
  int i, j;
  for (i = 0; i < HAUTEUR; ++i) {
    for (j = 0; j < LARGEUR; ++j) {
      free(_map->cases[i][j]);
    }
  }
  free(_map->cases);
  _map = NULL;
}

int map_initialized() {
  return _map != NULL;
}

map_T *get_map() {
  return _map;
}

int get_seed() {
  return _seed;
}

case_T *get_case(int x, int y) {
  return _map->cases[x][y];
}