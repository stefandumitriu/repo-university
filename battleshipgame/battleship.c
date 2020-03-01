#include <ncurses.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Pe parcursul codului folosesc urmatoarele notatii pentru matricea calculatorului
// respectiv a jucatorului: 0 - nimic, neselectat; 1 - barca, neselectat;
// 2 - nimic, selectat; 3 - barca, selectat

// Functie pentru generarea matricei calculatorului (random)
void cpuMatrixGen(int **mat) {
    srand(time(0));
    int shipsCounter[4]={4,3,2,1}, i ,j;
    for(i = 1; i <= 10; i++) {
        for(j = 1; j <= 10; j++)
            mat[i][j] = 0;
    }
    for(i = 0; i <= 11; i++) {
        mat[i][0] = 8;
        mat[i][11] = 8;
    } 
    for(j = 0; j <= 11; j++) {
        mat[0][j] = 8;
        mat[11][j] = 8;
    }
    for(i = 3; i >= 0; i--) {
        while(shipsCounter[i] != 0) {
            int shipDim = i + 1;
            int free = 1;
            int randDirection = rand() % 2;
            if(randDirection == 0) { 
                while(1) {
                    int randX = rand() % 10 + 1;
                    int randY = rand() % 10 + 1;
                    if(randX + shipDim > 10) {
                            break;
                    }
                    for(int y = randY - 1; y <= randY + 1; y++) {
                        for(int x = randX - 1; x <= randX + shipDim + 1; x++) {
                            if(mat[y][x] == 1)
                                    free = 0;
                        }
                    }
                    if(!free)
                        break;
                    for(int x = randX; x < randX + shipDim; x++)
                        mat[randY][x] = 1;
                    shipsCounter[i]--;
                    break;
                }
            }
            if(randDirection == 1) {
                while(1) {
                    int randX = rand() % 10 + 1;
                    int randY = rand() % 10 + 1;
                    if(randY + shipDim > 10)
                            break;
                    for(int y = randY - 1; y <= randY + shipDim + 1; y++) {
                        for(int x = randX - 1; x <= randX + 1; x++) {
                            if(mat[y][x] == 1)
                                    free = 0;
                        }
                    }
                    if(!free)
                        break;
                    for(int y = randY; y < randY + shipDim; y++)
                        mat[y][randX] = 1;
                    shipsCounter[i]--;
                    break;
                }
            }
        }
    }
}
/* Functie pentru printarea in mediul grafic a matricei jucatorului (primeste ca parametru 
alegerea facuta in setari de alegere a unui fisier de input )*/
void playerGridPrint(int map_choice, char *argv[], WINDOW *grid_graphic, int **player_matrix) {
    
    FILE *player_grid;
    player_grid = fopen(argv[map_choice],"r");
    int i, j, num;
    for(i = 0; i < 10; i++) {
        move(i,0);
        refresh();
        wprintw(grid_graphic,"|");
        for(j = 0; j < 10; j++) {
            fscanf(player_grid, "%d", &num);
            if(num == 1) {
                wprintw(grid_graphic,"X|");
                player_matrix[i][j] = 1;
            }
            else {
                wprintw(grid_graphic, " |");
                player_matrix[i][j] = 0;
            }
        }
        wprintw(grid_graphic,"\n");
    }
    fclose(player_grid);
}
// Functie de printare a grid-ului initial al calculatorului (cu toate casutele ascunse)
void cpuGridPrint(WINDOW *cpu_grid) {
    int i, j;
    for(i = 2; i <= 11; i++) {
        move(i,1);
        refresh();
        wprintw(cpu_grid,"|");
        for(j = 0; j < 10; j++) {
            wprintw(cpu_grid,"*|");
        }
        wprintw(cpu_grid,"\n");
    }
}
// Functie de printare a grid-ului jucatorului la returnarea intr-un joc
void playerGridPrint_modified(WINDOW *grid_graphic, int **player_matrix, int color_choice) {
    int i,j;
    start_color();
    init_pair(1,color_choice,-1);
    for(i = 0; i < 10; i++) {
        move(i,0);
        refresh();
        wprintw(grid_graphic,"|");
        for(j = 0; j < 10; j++) {
            if(player_matrix[i][j] == 0) {
                wprintw(grid_graphic, " |");
            }
            else if(player_matrix[i][j] == 1) {
                wprintw(grid_graphic, "X|");
            }
            else if(player_matrix[i][j] == 2) {
                wprintw(grid_graphic, "O|");
            }
            else if(player_matrix[i][j] == 3) {
                wattron(grid_graphic, COLOR_PAIR(1));
                wprintw(grid_graphic,"X");
                wattroff(grid_graphic,COLOR_PAIR(1));
                wprintw(grid_graphic,"|");
            }
            wrefresh(grid_graphic);
        }
        wprintw(grid_graphic,"\n");
    }
}
// Functie de printare a hartii in momentul in care se alege Randomize Map in timpul jocului
void rand_mapPrint(WINDOW *player_grid, int **playerMatrix) {
	int i,j;
	for(i = 0; i < 10; i++) {
		move(i,0);
		refresh();
		wprintw(player_grid,"|");
		for(j = 0; j < 10; j++) {
			if(playerMatrix[i][j] == 0) {
				wprintw(player_grid," |");
			}
			if(playerMatrix[i][j] == 1) {
				wprintw(player_grid,"X|");
			}
			wrefresh(player_grid);
		}
		wprintw(player_grid,"\n");
	}
}
// Functie de printare a grid-ului calculatorului la returnarea in joc
void cpuGridPrint_modified(WINDOW *grid_graphic, int **cpu_matrix, int color_choice) {
    int i,j;
    start_color();
    init_pair(1,color_choice,-1);
    for(i = 1; i <= 10; i++) {
        move(i+1,1);
        refresh();
        wprintw(grid_graphic,"|");
        for(j = 1; j <= 10; j++) {
            if(cpu_matrix[i][j] == 0) {
                wprintw(grid_graphic,"*|");
            }
            else if(cpu_matrix[i][j] == 1) {
                wprintw(grid_graphic,"*|");
            }
            else if(cpu_matrix[i][j] == 2) {
                wprintw(grid_graphic," |");
            }
            else if(cpu_matrix[i][j] == 3) {
                wattron(grid_graphic,COLOR_PAIR(1));
                wprintw(grid_graphic,"X");
                wattroff(grid_graphic,COLOR_PAIR(1));
                wprintw(grid_graphic,"|");
            }
        }
        wprintw(grid_graphic,"\n");
    }
}
// Functie de randomizare a matricei jucatorului pentru optiunea de Randomize Map
void randomize_matrix(int **playerMatrix, int rand_map_ship_Counter[4]) {
	int i,j, mat[12][12];
	for(i = 1; i <= 10; i++) {
        for(j = 1; j <= 10; j++)
            mat[i][j] = 0;
    }
    for(i = 0; i <= 11; i++) {
        mat[i][0] = 2;
        mat[i][11] = 2;
    } 
    for(j = 0; j <= 11; j++) {
        mat[0][j] = 2;
        mat[11][j] = 2;
    }
	srand(time(0));
	for(i = 3; i >= 0; i--) {
		int shipDim = i + 1;
		while(rand_map_ship_Counter[i] != 0) {
			int free = 1;
			int randDirection = rand() % 2;
			if(randDirection == 0) {
				while(1) {
					int randX = rand() % 10 + 1;
                    int randY = rand() % 10 + 1;
                    if(randX + shipDim > 10) {
                            break;
                    }
                    for(int y = randY - 1; y <= randY + 1; y++) {
                        for(int x = randX - 1; x <= randX + shipDim + 1; x++) {
                            if(mat[y][x] == 1)
                                    free = 0;
                        }
                    }
                    if(!free)
                        break;
                    for(int x = randX; x < randX + shipDim; x++)
                        mat[randY][x] = 1;
                    rand_map_ship_Counter[i]--;
                    break;
				}
			}
			if(randDirection == 1) {
				while(1) {
					int randX = rand() % 10 + 1;
                    int randY = rand() % 10 + 1;
                    if(randY + shipDim > 10)
                            break;
                    for(int y = randY - 1; y <= randY + shipDim + 1; y++) {
                        for(int x = randX - 1; x <= randX + 1; x++) {
                            if(mat[y][x] == 1)
                                    free = 0;
                        }
                    }
                    if(!free)
                        break;
                    for(int y = randY; y < randY + shipDim; y++)
                        mat[y][randX] = 1;
                    rand_map_ship_Counter[i]--;
                    break;
				}
			}
		}
	}
	for(i = 1; i <= 10; i++)
		for(j = 1;j <= 10; j++)
			playerMatrix[i - 1][j - 1] = mat[i][j];
}
// Functie de incarcare a meniului de setari
void load_settings(int argc, char *argv[], int *map_choice, int *color_choice) {
	int current_option = 1;
    int maxRow, maxColumn;
    int i, j;
    getmaxyx(stdscr, maxRow, maxColumn);
    WINDOW *settings_menu = newwin(maxRow, maxColumn, 0, 0);
    keypad(settings_menu,TRUE);
    char menu_name[20] = "Settings";
    char setting_options[2][20] = {"Player Map Grid", "Accent Color"};
    char color_text[4][7] = {"Red", "Green", "Yellow", "Blue"};
    start_color();
    init_pair(2, COLOR_RED, -1);
    int **mat_player;
    mat_player = (int **) malloc(10 * sizeof(int*));
    for(i = 0; i < 10; i++)
    	mat_player[i] = (int *) malloc(10 * sizeof(int));

    WINDOW *choose_color = derwin(settings_menu, 6, 10, 4, maxColumn / 2 + strlen(setting_options[1]) / 2 + 1);
    WINDOW *choose_map = newwin(maxRow, maxColumn, 0, 0);
    WINDOW *grid = derwin(choose_map, 10, 22, maxRow / 2 - 5, maxColumn / 2 - 11);
    while(1) {
    	mvwprintw(settings_menu, 1, maxColumn / 2 - strlen(menu_name) / 2, "%s", menu_name);
        for(i = 0; i < 2; i++) {
        	if(i + 1 == current_option)
        		wattron(settings_menu, A_REVERSE);
        	mvwprintw(settings_menu, i + 3, maxColumn / 2 - strlen(setting_options[i]) / 2, "%s", setting_options[i]);
        	wattroff(settings_menu, A_REVERSE);
        }
        int key = wgetch(settings_menu);
        if(key == KEY_DOWN && current_option == 1)
        	current_option++;
        if(key == KEY_UP && current_option == 2)
        	current_option--;
        if((key == 10 || key == KEY_RIGHT) && current_option == 2) {
        	box(choose_color, 0, 0);
        	keypad(choose_color, TRUE);
        	while(1) {
        		for(j = 0; j < 4; j++) {
        			if(j + 1 == (*color_choice))
        				wattron(choose_color, A_REVERSE);
        			mvwprintw(choose_color, j + 1, 2, "%s", color_text[j]);
        			wattroff(choose_color, A_REVERSE);
        		}
        		int key_color = wgetch(choose_color);
        		if((*color_choice) > 1 && key_color == KEY_UP)
        			(*color_choice)--;
        		else if((*color_choice) < 4 && key_color == KEY_DOWN)
        			(*color_choice)++;
        		else if(key_color == 10 || key_color == 27 || key_color == KEY_LEFT) {
        			wclear(choose_color);
        			wrefresh(choose_color);
        			break;
        		}
        		wrefresh(choose_color);
        	}
        }
        if(key == 10 && current_option == 1) {
        	wclear(settings_menu);
        	wrefresh(settings_menu);
        	keypad(choose_map, TRUE);
        	int k;
        	playerGridPrint((*map_choice), argv, grid, mat_player);
        	wrefresh(grid);
        	while(1) {
        			if((*map_choice) == 1)
        				wattron(choose_map, COLOR_PAIR(2));
        			mvwprintw(choose_map, 2, maxColumn / 2 - 1, "<");
        			wattroff(choose_map, COLOR_PAIR(2));
        			
        			wattron(choose_map, A_REVERSE);
        			mvwprintw(choose_map, 2 , maxColumn / 2, "%d", (*map_choice));
        			wattroff(choose_map, A_REVERSE);

        			if((*map_choice) == argc - 1)
        				wattron(choose_map, COLOR_PAIR(2));
        			mvwprintw(choose_map, 2, maxColumn / 2 + 1, ">");
        			wattroff(choose_map, COLOR_PAIR(3));
        		int key_map = wgetch(choose_map);
        		if(key_map == KEY_RIGHT && (*map_choice) < argc - 1) {
        			(*map_choice)++;
        			wclear(grid);
        			playerGridPrint((*map_choice), argv, grid, mat_player);
        			wrefresh(grid);
        		}
        		if(key_map == KEY_LEFT && (*map_choice) > 1) {
        			(*map_choice)--;
        			wclear(grid);
        			playerGridPrint((*map_choice), argv, grid, mat_player);
        			wrefresh(grid);
        		}
        		if(key_map == 10 || key_map == 27) {
        			wclear(grid);
        			wrefresh(grid);
        			wclear(choose_map);
        			wrefresh(choose_map);
        			free(mat_player);
        			break;
        		}
        		wrefresh(choose_map);
        	}
        }
        if(key == 27) {
            wclear(settings_menu);
            wrefresh(settings_menu);
            break;
        }
    }  
}
// Functie de delay pentru mutarea calculatorului
void delay(int n) {
    int ms = n * (CLOCKS_PER_SEC / 1000);
    clock_t now, start;
    now = start = clock();
    while((now - start) < ms) {
        now = clock();
    }
}
// Functie de afisare cand un jucator castiga jocul
void load_win_screen(int shipsDestroyed_Player, int shipsDestroyed_cpu, int winner) {
    int maxRow, maxColumn;
    getmaxyx(stdscr, maxRow, maxColumn);
    WINDOW* win_screen = newwin(maxRow, maxColumn, 0, 0);
    keypad(win_screen,TRUE);
    char win_text_Player[100] = "Congratulations! You won the game!";
    char win_text_cpu[100] = "The CPU won the game.";
    if(winner == 1)
    	mvwprintw(win_screen,maxRow / 2, maxColumn / 2 - strlen(win_text_Player) / 2, "%s", win_text_Player);
    else if(winner == 0)
    	mvwprintw(win_screen,maxRow / 2, maxColumn / 2 - strlen(win_text_cpu) / 2, "%s", win_text_cpu);
    mvwprintw(win_screen, maxRow / 2 + 1, maxColumn / 2 - 3, "Player: %d", shipsDestroyed_Player);
    mvwprintw(win_screen, maxRow / 2 + 2, maxColumn / 2 - 3, "CPU: %d", shipsDestroyed_cpu);
    char info[100] = "Press ENTER to go to main menu";
    mvwprintw(win_screen,maxRow / 2 + 3, maxColumn / 2 - strlen(info) / 2, "%s", info);
    while(1) {
        int key = wgetch(win_screen);
        if(key == 10)
            {
                wclear(win_screen);
                wrefresh(win_screen);
                break;
            }
    }
}
// Functie de incarcare a meniului de alegere a uneia dintre optiuni cand se apasa TAB
void load_ingame_options(int *dest_in_adv, int *rand_map) {
	curs_set(FALSE);
	int maxRow, maxColumn;
	getmaxyx(stdscr, maxRow, maxColumn);
	char options[2][30] = {"Destroy in advance", "Randomize map"};
	WINDOW *ingame_options = newwin(4, 32, maxRow - 5, maxColumn / 4 - 16);
	keypad(ingame_options, TRUE);
	box(ingame_options, 0, 0);
	wrefresh(ingame_options);
	int current_option = 1;
	int i;
	while(1) {
		for(i = 0; i < 2; i++) {
			if(i + 1 == current_option)
				wattron(ingame_options, A_REVERSE);
			mvwprintw(ingame_options, i + 1, 16 - strlen(options[i]) / 2, "%s", options[i]);
			wattroff(ingame_options, A_REVERSE);
		}
		int key = wgetch(ingame_options);
		if(key == KEY_UP && current_option == 2)
			current_option--;
		else if(key == KEY_DOWN && current_option == 1)
			current_option++;
		else if(key == '\t') {
			wclear(ingame_options);
			wrefresh(ingame_options);
			curs_set(TRUE);
			break;
		}
		else if(key == 10 && current_option == 1) {
			*dest_in_adv = 1;
			wclear(ingame_options);
			wrefresh(ingame_options);
			curs_set(TRUE);
			break;
		}
		else if(key == 10 && current_option == 2) {
			*rand_map = 1;
			wclear(ingame_options);
			wrefresh(ingame_options);
			curs_set(TRUE);
			break;
		}
		wrefresh(ingame_options);
	}
}
// Functie in care se verifica dimensiunea unei barci, precum si pozitia exacta a acesteia (se salveaza in parametrii)
int check_ship_size(int **cpuMatrix, int i, int j, int *get_bound_Row_up, int *get_bound_Row_down, int *get_bound_Column_left, int *get_bound_Column_right) {
    int ship_size = 1;
    int aux_i = i;
    int aux_j = j;
    (*get_bound_Row_down) = i;
    (*get_bound_Row_up) = i;
    (*get_bound_Column_left) = j;
    (*get_bound_Column_right) = j;
    if(cpuMatrix[i - 1][j] == 1 || cpuMatrix[i - 1][j] == 3) {
        ship_size++;
        i--;
        while(cpuMatrix[i - 1][j] == 1 || cpuMatrix[i - 1][j] == 3) {
            ship_size++;
            i--;
        }
    	(*get_bound_Row_up) = i;
    }
    i = aux_i;
    if(cpuMatrix[i + 1][j] == 1 || cpuMatrix[i + 1][j] == 3) {
        ship_size++;
        i++;
        while(cpuMatrix[i + 1][j] == 1 || cpuMatrix[i + 1][j] == 3) {
            ship_size++;
            i++;
        }
        (*get_bound_Row_down) = i;
    }
    i = aux_i;
    if(cpuMatrix[i][j - 1] == 1 || cpuMatrix[i][j - 1] == 3) {
        ship_size++;
        j--;
        while(cpuMatrix[i][j - 1] == 1 || cpuMatrix[i][j - 1] == 3) {
            ship_size++;
            j--;
        }
        (*get_bound_Column_left) = j;
    }
    j = aux_j;
    if(cpuMatrix[i][j + 1] == 1 || cpuMatrix[i][j + 1] == 3) {
        ship_size++;
        j++;
        while(cpuMatrix[i][j + 1] == 1 || cpuMatrix[i][j + 1] == 3) {
            ship_size++;
            j++;
        }
        (*get_bound_Column_right) = j;
    }
    return ship_size;
}
// Functie care verifica daca o barca inamica este sau nu distrusa complet
int check_destroyed_cpu(int **cpuMatrix, int i, int j) {
    int get_bound_Row_up, get_bound_Row_down, get_bound_Column_left, get_bound_Column_right;
    int ship_size = check_ship_size(cpuMatrix, i, j, &get_bound_Row_up, &get_bound_Row_down, &get_bound_Column_left, &get_bound_Column_right);
    int hit_counter = 0;
    int x, y;
    for(x = get_bound_Row_up; x <= get_bound_Row_down; x++)
        for(y = get_bound_Column_left; y <= get_bound_Column_right; y++) {
                if(cpuMatrix[x][y] == 3)
                    hit_counter++;
            }
    if(hit_counter == ship_size)
        return 1;
    return 0;
}
// Functie care verifica dimensiunea unei barci la randomizare (se tine cont daca un segment este distrus
// pentru a redimensiona barca
int check_ship_size_rand_map(int **playerMatrix, int i, int j) {
	int ship_size = 1;
	int aux_i = i;
	int aux_j = j;
	if(playerMatrix[i + 1][j] == 1 || playerMatrix[i + 1][j] == 3) {
		if(playerMatrix[i + 1][j] == 1)
			ship_size++;
		playerMatrix[i + 1][j] = 0;
		i++;
		while(playerMatrix[i + 1][j] == 1) {
			if(playerMatrix[i + 1][j] == 1)
				ship_size++;
			playerMatrix[i + 1][j] = 0;
			i++;
		}
	}
	i = aux_i;
	if(playerMatrix[i - 1][j] == 1 || playerMatrix[i - 1][j] == 3) {
		if(playerMatrix[i - 1][j] == 1)
			ship_size++;
		playerMatrix[i - 1][j] = 0;
		i--;
		while(playerMatrix[i - 1][j] == 1) {
			if(playerMatrix[i - 1][j] == 1)
				ship_size++;
			playerMatrix[i - 1][j] = 0;
			i--;
		}
	}
	i = aux_i;
	j = aux_j;
	if(playerMatrix[i][j + 1] == 1 || playerMatrix[i][j + 1] == 3) {
		if(playerMatrix[i][j + 1] == 1)
			ship_size++;
		playerMatrix[i][j + 1] = 0;
		j++;
		while(playerMatrix[i][j + 1] == 1 || playerMatrix[i][j + 1] == 3) {
			if(playerMatrix[i][j + 1] == 1)	
				ship_size++;
			playerMatrix[i][j + 1] = 0;
			j++;
		}
	}
	j = aux_j;
	if(playerMatrix[i][j - 1] == 1 || playerMatrix[i][j - 1] == 3) {
		if(playerMatrix[i][j - 1] == 1)
			ship_size++;
		playerMatrix[i][j - 1] = 0;
		j--;
		while(playerMatrix[i][j - 1] == 1 || playerMatrix[i][j - 1] == 3) {
			if(playerMatrix[i][j - 1] == 1)
				ship_size++;
			playerMatrix[i][j - 1] = 0;
			j--;
		}
	}
	j = aux_j;
	return ship_size;
}
// Functie care verifica daca o barca a player-ului este distrusa 
int check_destroyed_Player(int **playerMatrix, int i, int j) {
	int get_bound_Row_up, get_bound_Row_down, get_bound_Column_left, get_bound_Column_right;
	int **playerMatrix_borded;
	int a, b;
	
	playerMatrix_borded = (int **) malloc(12 * sizeof(int*));
	for(a = 0; a < 12; a++)
		playerMatrix_borded[a] = (int *) malloc(12 * sizeof(int*));

	for(a = 0; a <= 11; a++) {
		playerMatrix_borded[a][0] = 2;
		playerMatrix_borded[a][11] = 2;
	}
	for(b = 0; b <= 11; b++) {
		playerMatrix_borded[0][b] = 2;
		playerMatrix_borded[11][b] = 2;
	}
	for(a = 1; a <= 10; a++)
		for(b = 1; b <= 10; b++)
			playerMatrix_borded[a][b] = playerMatrix[a - 1][b - 1];
    int ship_size = check_ship_size(playerMatrix_borded, i + 1, j + 1, &get_bound_Row_up, &get_bound_Row_down, &get_bound_Column_left, &get_bound_Column_right);
    int hit_counter = 0;
    int x, y;
    for(x = get_bound_Row_up; x <= get_bound_Row_down; x++)
        for(y = get_bound_Column_left; y <= get_bound_Column_right; y++) {
                if(playerMatrix_borded[x][y] == 3)
                    hit_counter++;
            }
    if(hit_counter == ship_size)
        return 1;
    return 0;
}
// Functia de distrugere in avans cu zece ture
void destroy_in_advance(WINDOW *player_grid, WINDOW *cpu_grid, int **playerMatrix, int **cpuMatrix,int **free_pos, int *shipsDestroyed_Player, int *shipsDestroyed_cpu, int *hit_counter_Player, int *hit_counter_cpu, int *game_exists, int color_choice) {
	curs_set(FALSE);
	int i;
	srand(time(0));
	start_color();
	init_pair(1,color_choice,-1);
	for(i = 0; i < 10;i++) {
		int playerLine, playerRow;
		playerLine =  rand() % 10;
		playerRow = rand() % 10;
		if(playerMatrix[playerLine][playerRow] > 1) {
			do {
				playerLine = rand() % 10;
				playerRow = rand() % 10;
			} while(playerMatrix[playerLine][playerRow] > 1);
		}
		if(playerMatrix[playerLine][playerRow] == 0) {
			playerMatrix[playerLine][playerRow] = 2;
			mvwprintw(player_grid, playerLine, playerRow * 2 + 1, "O");
		}
		else if(playerMatrix[playerLine][playerRow] == 1)
			{
				playerMatrix[playerLine][playerRow] = 3;
				wattron(player_grid, COLOR_PAIR(1));
				mvwprintw(player_grid, playerLine, playerRow * 2 + 1, "X");
				wattroff(player_grid, COLOR_PAIR(1));
				if(check_destroyed_Player(playerMatrix, playerLine, playerRow) == 1)
					(*shipsDestroyed_cpu)++;
				(*hit_counter_cpu)++;
			}
		wrefresh(player_grid);
		delay(500);
		if((*hit_counter_cpu) == 20) {
        	*game_exists = 0;
            load_win_screen(*shipsDestroyed_Player, *shipsDestroyed_cpu, 0);
            return;
        }
		int cpuLine, cpuRow;
		cpuLine = rand() % 10;
		cpuRow = rand() % 10;
		if(cpuMatrix[cpuLine + 1][cpuRow + 1] > 1) {
			do {
				cpuLine = rand() % 10;
				cpuRow = rand() % 10;
			} while(cpuMatrix[cpuLine + 1][cpuRow + 1] > 1);
		}
		if(cpuMatrix[cpuLine + 1][cpuRow + 1] == 0) {
			wattron(cpu_grid, COLOR_PAIR(1));
			mvwprintw(cpu_grid, cpuLine, cpuRow * 2 + 1, " ");
			wattroff(cpu_grid, COLOR_PAIR(1));
			cpuMatrix[cpuLine + 1][cpuRow + 1] = 2;
		}
		else if(cpuMatrix[cpuLine + 1][cpuRow + 1] == 1) {
			wattron(cpu_grid, COLOR_PAIR(1));
			mvwprintw(cpu_grid, cpuLine, cpuRow * 2 + 1, "X");
			wattroff(cpu_grid, COLOR_PAIR(1));
			cpuMatrix[cpuLine + 1][cpuRow + 1] = 3;
			if(check_destroyed_cpu(cpuMatrix, cpuLine + 1, cpuRow + 1) == 1)
				(*shipsDestroyed_Player)++;
			free_pos[cpuLine + 1][cpuRow + 1] = 0;
			(*hit_counter_Player)++;
			if((*hit_counter_Player) == 20) {
		    	*game_exists = 0;
		        load_win_screen(*shipsDestroyed_Player, *shipsDestroyed_cpu, 1);
		        return;
		    }
		}
		wrefresh(cpu_grid);
		delay(500);
	}
	curs_set(TRUE);
}
// Functia de randomizare efectiva a hartii la apelarea acestei optiuni
void randomize_map(WINDOW* player_grid, int **playerMatrix, int rand_map_ship_Counter[4], int **mat) {
	
	int i,j;
	
	int **playerMatrix_borded;
	playerMatrix_borded = (int **) malloc(12 * sizeof(int*));
	for(i = 0; i < 12; i++)
		playerMatrix_borded[i] = (int *) malloc(12 * sizeof(int));

	int a,b;
	for(a = 0; a <= 11; a++) {
		playerMatrix_borded[a][0] = 2;
		playerMatrix_borded[a][11] = 2;
	}
	for(b = 0; b <= 11; b++) {
		playerMatrix_borded[0][b] = 2;
		playerMatrix_borded[11][b] = 2;
	}
	for(a = 1; a <= 10; a++)
		for(b = 1; b <= 10; b++)
			playerMatrix_borded[a][b] = playerMatrix[a - 1][b - 1];

	for(i = 1; i <= 10; i++)
		for(j = 1; j <= 10; j++) {
			if(playerMatrix_borded[i][j] == 1)
				rand_map_ship_Counter[check_ship_size_rand_map(playerMatrix_borded, i, j) - 1]++;
		}
	randomize_matrix(playerMatrix, rand_map_ship_Counter);
	wclear(player_grid);
	rand_mapPrint(player_grid, playerMatrix);
	wrefresh(player_grid);
	
	for(i = 1; i <= 10; i++) {
        for(j = 1; j <= 10; j++)
            mat[i][j] = 1;
    }
    for(i = 0; i <= 11; i++) {
        mat[i][0] = 2;
        mat[i][11] = 2;
    } 
    for(j = 0; j <= 11; j++) {
        mat[0][j] = 2;
        mat[11][j] = 2;
    }
    free(playerMatrix_borded);
}
// Functia propriu-zisa de joc
void play_game(WINDOW* game_interface, WINDOW* player_grid, WINDOW* cpu_grid, int **playerMatrix, int **cpuMatrix,int **free_pos, int *shipsDestroyed_Player, int *shipsDestroyed_cpu, int *hit_counter_Player, int *hit_counter_cpu, int *game_exists, int color_choice) {

    keypad(cpu_grid, TRUE);
    curs_set(TRUE);
    
    int currentLine = 0, currentRow = 1;
    wmove(cpu_grid,currentLine,currentRow);

    char info[50] = "Press TAB to open the game options";
    char info_open[50] = "Press TAB to close the game options";
    char warning_message[70] = "Choose another cell, you have already hit this one!";

    int i,j;
    int ended = 0;

    start_color();
    init_pair(3,color_choice,-1);

    int cpu_turn = 0;
    int dest_in_adv = 0, rand_map = 0;
    int rand_map_ship_Counter[4] = {0, 0, 0, 0};
    int maxRow, maxColumn;

    getmaxyx(game_interface, maxRow, maxColumn);
    WINDOW *warning = newwin(3, maxColumn / 2 - 3, maxRow - 3, maxColumn / 2 + 3);
    WINDOW *ingame_options_win = derwin(game_interface, 1, strlen(info_open), maxRow - 1, maxColumn / 4 - strlen(info_open) / 2);

    srand(time(0));
    while(1) {
        if(cpu_turn == 0) {
            int key = wgetch(cpu_grid);
            if(key == 27)
                break;
                if(key == KEY_UP && currentLine > 0) {
                currentLine--;
                curs_set(TRUE);
                wclear(warning);
                wrefresh(warning);
            }
            if(key == KEY_DOWN && currentLine < 9) {
                currentLine++;
                curs_set(TRUE);
                wclear(warning);
                wrefresh(warning);
            }
            if(key == KEY_LEFT && currentRow > 1) {
                currentRow -= 2;
                curs_set(TRUE);
                wclear(warning);
                wrefresh(warning);
            }
            if(key == KEY_RIGHT && currentRow < 19) {
                currentRow += 2;
                curs_set(TRUE);
                wclear(warning);
                wrefresh(warning);
            }
            if(key == '\t') {
            	mvwprintw(ingame_options_win, 0, 0, "%s", info_open);
            	wrefresh(ingame_options_win);
            	load_ingame_options(&dest_in_adv, &rand_map);
            	wclear(ingame_options_win);
            	mvwprintw(ingame_options_win, 0, 0, "%s", info);
            	wrefresh(ingame_options_win);
            	if(dest_in_adv == 1) {
            		destroy_in_advance(player_grid, cpu_grid, playerMatrix, cpuMatrix, free_pos, shipsDestroyed_Player, shipsDestroyed_cpu, hit_counter_Player, hit_counter_cpu, game_exists, color_choice);
            		if((*game_exists) == 0)
            			break;
            		dest_in_adv = 0;
            	}
            	if(rand_map == 1) {
            		randomize_map(player_grid, playerMatrix, rand_map_ship_Counter, free_pos);
            		wrefresh(player_grid);
            		rand_map = 0;
            	}
            }
            if(key == 10) {
                curs_set(FALSE);
                if(cpuMatrix[currentLine + 1][currentRow / 2 + 1] == 1) {
                	cpuMatrix[currentLine + 1][currentRow / 2 + 1] = 3;
                    if(check_destroyed_cpu(cpuMatrix, currentLine + 1, currentRow / 2 + 1)) {
                    	(*shipsDestroyed_Player)++;
                    }
                    (*hit_counter_Player)++;
                    wattron(cpu_grid,COLOR_PAIR(3));
                    wprintw(cpu_grid,"X");
                    wattroff(cpu_grid,COLOR_PAIR(3));
                    if((*hit_counter_Player) == 20) {
                            *game_exists = 0;
                            load_win_screen(*shipsDestroyed_Player, *shipsDestroyed_cpu, 1);
                            break;
                        }
                }
                else if(cpuMatrix[currentLine + 1][currentRow / 2 +1] == 0) {
                    cpuMatrix[currentLine + 1][currentRow / 2 + 1] = 2;
                    wattron(cpu_grid,COLOR_PAIR(3));
                    wprintw(cpu_grid," ");
                    wattroff(cpu_grid,COLOR_PAIR(3));
                    cpu_turn = 1;
                }
                else {
                    wclear(warning);
                    wprintw(warning, "%s", warning_message);
                    wrefresh(warning);
                }
                wrefresh(cpu_grid);
            }   
        }
        if(cpu_turn == 1) {
            int cpuLine, cpuRow;
            cpuLine = rand() % 10;
            cpuRow = rand() % 10;
            if(playerMatrix[cpuLine][cpuRow] == 1 && free_pos[cpuLine + 1][cpuRow + 1] == 1) {
                wattron(player_grid,COLOR_PAIR(3));
                mvwprintw(player_grid, cpuLine, cpuRow * 2 + 1,"X");
                wattroff(player_grid,COLOR_PAIR(3));
                wrefresh(player_grid);
                playerMatrix[cpuLine][cpuRow] = 3;
                if(check_destroyed_Player(playerMatrix, cpuLine, cpuRow) == 1)
					(*shipsDestroyed_cpu)++;
                (*hit_counter_cpu)++;
                if((*hit_counter_cpu) == 20) {
                	*game_exists = 0;
                	load_win_screen(*shipsDestroyed_Player, *shipsDestroyed_cpu, 0);
                	break;
                }
                cpu_turn = 1;
                delay(1500);
            }
            else if(playerMatrix[cpuLine][cpuRow] == 0) {
                mvwprintw(player_grid, cpuLine, cpuRow * 2 + 1, "O");
                cpu_turn = 0;
                playerMatrix[cpuLine][cpuRow] = 2;
                wrefresh(player_grid);
            }
            if(free_pos[cpuLine + 1][cpuRow + 1] == 0) {
                do {
                    cpuLine = rand() % 10;
                    cpuRow = rand() % 10;
                    if(playerMatrix[cpuLine][cpuRow] == 1 && free_pos[cpuLine + 1][cpuRow + 1] == 1) {
                        wattron(player_grid,COLOR_PAIR(3));
                        mvwprintw(player_grid, cpuLine, cpuRow * 2 + 1,"X");
                        wattroff(player_grid,COLOR_PAIR(3));
                        playerMatrix[cpuLine][cpuRow] = 3;
                        wrefresh(player_grid);
                        if(check_destroyed_Player(playerMatrix, cpuLine, cpuRow) == 1)
							(*shipsDestroyed_cpu)++;
                        (*hit_counter_cpu)++;
		                if((*hit_counter_cpu) == 20) {
		                	ended = 1;
		                	*game_exists = 0;
		                	load_win_screen(*shipsDestroyed_Player, *shipsDestroyed_cpu, 0);
		                	break;
		                }
                        cpu_turn = 1;
                        delay(1500);
                    }
                    else if(playerMatrix[cpuLine][cpuRow] == 0) {
                        mvwprintw(player_grid, cpuLine, cpuRow * 2 + 1, "O");
                        cpu_turn = 0;
                        playerMatrix[cpuLine][cpuRow] = 2;
                        wrefresh(player_grid);
                    }
                } while(free_pos[cpuLine + 1][cpuRow + 1] == 0);
               	if(ended)
               		break;
            }
            free_pos[cpuLine + 1][cpuRow + 1] = 0;
        }
        wmove(cpu_grid, currentLine, currentRow);
    }
}
// Functia de incarcare a unui nou joc, cu matricile resetate
void load_new_game(int **player_matrix, int **cpu_matrix, int **free_pos, int *shipsDestroyed_Player, int *shipsDestroyed_cpu, int *hit_counter_Player, int *hit_counter_cpu, int *game_exists, int color_choice, int map_choice, char *argv[]) {
	*game_exists = 1;
    int maxRow, maxColumn;
    getmaxyx(stdscr, maxRow, maxColumn);
    WINDOW *game_interface = newwin(maxRow, maxColumn, 0, 0);
    keypad(game_interface,TRUE);
    char PlayerName[20] = "Player";
    char CPUName[20] = "CPU";
    char info[50] = "Press TAB to open the game options";
    int i = 0, j;
    for(i = 0; i <= maxRow; i++) {
        mvwprintw(game_interface, i, maxColumn / 2, "%c", '|');
    }
    mvwprintw(game_interface, 1, maxColumn / 4 - strlen(PlayerName) / 2, "%s", PlayerName);
    mvwprintw(game_interface, 1, 3 * maxColumn / 4 - strlen(CPUName) / 2, "%s",CPUName);
    mvwprintw(game_interface, maxRow - 1, maxColumn / 4 - strlen(info) / 2, "%s", info);

    FILE *playerMatrix;
    playerMatrix = fopen("player_map1", "r");
    for(i = 0; i < 10; i++) {
        for(j = 0; j < 10; j++)
            fscanf(playerMatrix, "%d", &player_matrix[i][j]);
        fgetc(playerMatrix);
    }
    fclose(playerMatrix);
    cpuMatrixGen(cpu_matrix);

    for(i = 0; i <= 11; i++) {
        free_pos[i][0] = 2;
        free_pos[i][11] = 2;
    }
    for(j = 0; j <= 11; j++) {
        free_pos[0][j] = 2;
        free_pos[11][j] = 2;
    }
    for(i = 1; i <= 10; i++)
        for(j = 1; j <= 10; j++)
            free_pos[i][j] = 1;

    WINDOW *player_grid = derwin(game_interface, 10 , 22, maxRow / 2 - 5, maxColumn / 4 - 11);
    playerGridPrint(map_choice, argv, player_grid, player_matrix);
    wrefresh(player_grid);
    WINDOW *cpu_grid = derwin(game_interface, 10, 22, maxRow/2 - 5, 3 * maxColumn / 4 -11);
    cpuGridPrint(cpu_grid);
    wrefresh(cpu_grid);
    wrefresh(game_interface);

    *shipsDestroyed_Player = 0;
    *shipsDestroyed_cpu = 0;
    *hit_counter_Player = 0;
    *hit_counter_cpu = 0;
    play_game(game_interface, player_grid, cpu_grid, player_matrix, cpu_matrix, free_pos, shipsDestroyed_Player, shipsDestroyed_cpu, hit_counter_Player, hit_counter_cpu, game_exists, color_choice);
    curs_set(FALSE);
    wclear(game_interface);
    wrefresh(game_interface);
}
// Functia de incarcare a jocului deja existent, si starea anterioara a grid-urilor
void return_game(int **player_matrix, int **cpu_matrix, int **free_pos, int *shipsDestroyed_Player, int *shipsDestroyed_cpu, int *hit_counter_Player, int *hit_counter_cpu, int *game_exists, int color_choice) {
    int maxRow, maxColumn;
    getmaxyx(stdscr, maxRow, maxColumn);
    WINDOW *game_interface = newwin(maxRow, maxColumn, 0, 0);
    keypad(game_interface,TRUE);
    char PlayerName[20] = "Player";
    char CPUName[20] = "CPU";
    char info[50] = "Press TAB to open the game options";
    int i = 0, j;
    for(i = 0; i <= maxRow; i++) {
        mvwprintw(game_interface, i, maxColumn / 2, "%c", '|');
    }
    mvwprintw(game_interface, 1, maxColumn / 4 - strlen(PlayerName) / 2, "%s", PlayerName);
    mvwprintw(game_interface, 1, 3 * maxColumn / 4 - strlen(CPUName) / 2, "%s",CPUName);
    mvwprintw(game_interface, maxRow - 1, maxColumn / 4 - strlen(info) / 2, "%s", info);

    WINDOW *player_grid = derwin(game_interface, 10 , 22, maxRow / 2 - 5, maxColumn / 4 - 11);
    playerGridPrint_modified(player_grid, player_matrix, color_choice);
    wrefresh(player_grid);
    WINDOW *cpu_grid = derwin(game_interface, 10, 22, maxRow/2 - 5, 3 * maxColumn / 4 -11);
    cpuGridPrint_modified(cpu_grid, cpu_matrix, color_choice);
    wrefresh(cpu_grid);
    wrefresh(game_interface);

    play_game(game_interface, player_grid, cpu_grid, player_matrix, cpu_matrix, free_pos, shipsDestroyed_Player, shipsDestroyed_cpu, hit_counter_Player,hit_counter_cpu, game_exists, color_choice);
    curs_set(FALSE);
    wclear(game_interface);
    wrefresh(game_interface);
}
// Functia principala a jocului, main menu, din care se apeleaza toate functiile
void load_main_menu(int argc, char *argv[]) {
    int maxRow, maxColumn;
    getmaxyx(stdscr, maxRow, maxColumn);

    WINDOW *main_menu = newwin(maxRow, maxColumn, 0, 0);

    WINDOW *menu_options = derwin(main_menu, 6, maxColumn - 20, maxRow / 2 - 4, 10);
    keypad(menu_options,TRUE);
    
    int **player_matrix, **cpu_matrix, **free_pos;
   	int index;

   	player_matrix = (int **) malloc(10 * sizeof(int*));
   	for(index = 0; index < 10; index++)
   		player_matrix[index] = (int *) malloc(10 * sizeof(int));

   	cpu_matrix = (int **) malloc(12 * sizeof(int*));
   	for(index = 0; index < 12; index++)
   		cpu_matrix[index] = (int *) malloc(12 * sizeof(int));

   	free_pos = (int **) malloc(12 * sizeof(int*));
   	for(index = 0; index < 12; index++)
   		free_pos[index] = (int *) malloc(12 * sizeof(int));

    int shipsDestroyed_Player, shipsDestroyed_cpu;
    int hit_counter_Player, hit_counter_cpu;

    int map_choice = 1, color_choice = 1;

    int menuBoxRow, menuBoxColumn;
    getmaxyx(menu_options, menuBoxRow, menuBoxColumn);

    start_color();
    use_default_colors();
    init_pair(1,1,-1);
    
    int current_option = 1;
    int game_exists = 0;
    char options[4][20] = {"New Game", "Resume Game", "Settings", "Quit to Desktop"};
    while(1) {
        box(menu_options,0,0);
        char game_logo[20] = "Battleships";
        mvwprintw(main_menu, 4, maxColumn / 2 - strlen(game_logo) / 2, "%s", game_logo);
        wrefresh(main_menu);
        int i;
        for(i = 0; i < 4; i++) {
            if(i+1 == current_option) {
                if(i == 1 && game_exists == 0)
                    wattron(menu_options,COLOR_PAIR(1));
                else
                    wattron(menu_options, A_REVERSE);
            }
            mvwprintw(menu_options, i + 1, menuBoxColumn / 2 - strlen(options[i]) / 2, "%s", options[i]);
            wattroff(menu_options,COLOR_PAIR(1));
            wattroff(menu_options,A_REVERSE);
        }
        int key = wgetch(menu_options);
        if(key == KEY_UP && current_option > 1)
            current_option--;
        else if(key == KEY_DOWN && current_option < 4)
            current_option++;
        else if(key == 'q')
            break;
        else if(current_option == 4 && key == 10)
            break;
        else if(current_option == 3 && key == 10)
                load_settings(argc, argv, &map_choice, &color_choice);
        else if(current_option == 1 && key == 10) {
            load_new_game(player_matrix, cpu_matrix, free_pos, &shipsDestroyed_Player, &shipsDestroyed_cpu, &hit_counter_Player, &hit_counter_cpu, &game_exists, color_choice, map_choice, argv);
        }
        else if(current_option == 2 && key == 10 && game_exists)
            return_game(player_matrix, cpu_matrix, free_pos, &shipsDestroyed_Player, &shipsDestroyed_cpu, &hit_counter_Player, &hit_counter_cpu, &game_exists, color_choice);
    }
    wrefresh(main_menu);
    free(player_matrix);
    free(cpu_matrix);
    free(free_pos);
}
int main(int argc, char *argv[]) {
	int i;
	if(argc == 1) {
		printf("[Error]: No input files given\n");
		return 1;
	}
	for(i = 1; i < argc; i++) {
		if(fopen(argv[i],"r") == NULL) {
			printf("[Error]: The file %s does not exist\n", argv[i]);
			return 1;
		}
	}
    initscr();
    noecho();
    cbreak();
    curs_set(FALSE);
    
    load_main_menu(argc, argv);

    endwin();
    return 0;
}