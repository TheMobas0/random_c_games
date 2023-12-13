#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int bomb_count = 15;
int marked_count = 0;
int game_state = 0;
int mark_mode = 0;
char coords[2];
char *screen[10][10] = {{".", ".", ".", ".", ".", ".", ".", ".", ".", "."},
                        {".", ".", ".", ".", ".", ".", ".", ".", ".", "."},
                        {".", ".", ".", ".", ".", ".", ".", ".", ".", "."},
                        {".", ".", ".", ".", ".", ".", ".", ".", ".", "."},
                        {".", ".", ".", ".", ".", ".", ".", ".", ".", "."},
                        {".", ".", ".", ".", ".", ".", ".", ".", ".", "."},
                        {".", ".", ".", ".", ".", ".", ".", ".", ".", "."},
                        {".", ".", ".", ".", ".", ".", ".", ".", ".", "."},
                        {".", ".", ".", ".", ".", ".", ".", ".", ".", "."},
                        {".", ".", ".", ".", ".", ".", ".", ".", ".", "."}};
int bomb_map[10][10] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

void input(){
    scanf("%s", &*coords);
}

int check_mode_change(){
    if(coords[0] == 'd' && coords[1] == 'd') mark_mode = 0;
    if(coords[0] == 'm' && coords[1] == 'm') mark_mode = 1;
    if(coords[0] == 'd' && coords[1] == 'd' || coords[0] == 'm' && coords[1] == 'm') return 1;
    else return 0;
}

int calculate_coords(){
    int ix = 0;
    int jx = 0;
    if(coords[0] == 'a') jx = 0;
    if(coords[0] == 'b') jx = 1;
    if(coords[0] == 'c') jx = 2;
    if(coords[0] == 'd') jx = 3;
    if(coords[0] == 'e') jx = 4;
    if(coords[0] == 'f') jx = 5;
    if(coords[0] == 'g') jx = 6;
    if(coords[0] == 'h') jx = 7;
    if(coords[0] == 'i') jx = 8;
    if(coords[0] == 'j') jx = 9;

    if(coords[1] == '0') ix = 0;
    if(coords[1] == '1') ix = 1;
    if(coords[1] == '2') ix = 2;
    if(coords[1] == '3') ix = 3;
    if(coords[1] == '4') ix = 4;
    if(coords[1] == '5') ix = 5;
    if(coords[1] == '6') ix = 6;
    if(coords[1] == '7') ix = 7;
    if(coords[1] == '8') ix = 8;
    if(coords[1] == '9') ix = 9;


    return (ix * 10 + jx);
}

void generate_bombs(int bombs){
    for(int i = 0; i != bombs; i++){
        int bomb_x = rand() % 10;
        int bomb_y = rand() % 10;
        while(1){
            if(bomb_map[bomb_x][bomb_y] == -10 || calculate_coords()/10 == bomb_x && calculate_coords()%10 == bomb_y){
                bomb_x = rand() % 10;
                bomb_y = rand() % 10;
            }
            else break;
        }
        bomb_map[bomb_x][bomb_y] = -10;
    }
}

void generate_numbers(){
    for(int i = 0; i != 10; i++){
        for(int j = 0; j != 10; j++){
            if(bomb_map[i][j] < 0){
                if (i != 0) bomb_map[i-1][j]++;
                if (i != 9) bomb_map[i+1][j]++;
                if (j != 0) bomb_map[i][j-1]++;
                if (j != 9) bomb_map[i][j+1]++;
                if (i != 0 && j != 0) bomb_map[i-1][j-1]++;
                if (i != 9 && j != 0) bomb_map[i+1][j-1]++;
                if (i != 0 && j != 9) bomb_map[i-1][j+1]++;
                if (i != 9 && j != 9) bomb_map[i+1][j+1]++;
            }
        }
    }
}

char *int_to_char(int input){
    switch(input){
        case 1:
            return "1";
        case 2:
            return "2";
        case 3:
            return "3";
        case 4:
            return "4";
        case 5:
            return "5";
        case 6:
            return "6";
        case 7:
            return "7";
        case 8:
            return "8";
        default:
            return "0";
    }
}

void clear_tile(){
    if(bomb_map[calculate_coords()/10][calculate_coords()%10] > 0){
        screen[calculate_coords()/10][calculate_coords()%10] = int_to_char(bomb_map[calculate_coords()/10][calculate_coords()%10]);
    }
    else{
        screen[calculate_coords()/10][calculate_coords()%10] = " ";
    }
}

void clear_fog(){
    for(int k = 0; k != 100; k++){
        for(int i = 0; i != 10; i++){
            for(int j = 0; j != 10; j++){
                if(strcmp(screen[i][j]," ") == 0){
                    if(i != 0 && bomb_map[i-1][j] == 0) screen[i-1][j] = " ";
                    if(i != 9 && bomb_map[i+1][j] == 0) screen[i+1][j] = " ";
                    if(j != 0 && bomb_map[i][j-1] == 0) screen[i][j-1] = " ";
                    if(j != 9 && bomb_map[i][j+1] == 0) screen[i][j+1] = " ";
                    if(i != 0 && j != 0 && bomb_map[i-1][j-1] == 0) screen[i-1][j-1] = " ";
                    if(i != 9 && j != 0 && bomb_map[i+1][j-1] == 0) screen[i+1][j-1] = " ";
                    if(i != 0 && j != 9 && bomb_map[i-1][j+1] == 0) screen[i-1][j+1] = " ";
                    if(i != 9 && j != 9 && bomb_map[i+1][j+1] == 0) screen[i+1][j+1] = " ";

                    if(i != 0 && bomb_map[i-1][j] > 0){
                        screen[i-1][j] = int_to_char(bomb_map[i-1][j]);
                    }
                    if(i != 9 && bomb_map[i+1][j] > 0){
                        screen[i+1][j] = int_to_char(bomb_map[i+1][j]);
                    }
                    if(j != 0 && bomb_map[i][j-1] > 0){
                        screen[i][j-1] = int_to_char(bomb_map[i][j-1]);
                    }
                    if(j != 9 && bomb_map[i][j+1] > 0){
                        screen[i][j+1] = int_to_char(bomb_map[i][j+1]);
                    }
                    if(i != 0 && j != 0 && bomb_map[i-1][j-1] > 0){
                        screen[i-1][j-1] = int_to_char(bomb_map[i-1][j-1]);
                    }
                    if(i != 9 && j != 0 && bomb_map[i+1][j-1] > 0){
                        screen[i+1][j-1] = int_to_char(bomb_map[i+1][j-1]);
                    }
                    if(i != 0 && j != 9 && bomb_map[i-1][j+1] > 0){
                        screen[i-1][j+1] = int_to_char(bomb_map[i-1][j+1]);
                    }
                    if(i != 9 && j != 9 && bomb_map[i+1][j+1] > 0){
                        screen[i+1][j+1] = int_to_char(bomb_map[i+1][j+1]);
                    }
                }
            }
        }
    }
}

void reveal_bombs(){
    for(int i = 0; i != 10; i++){
        for(int j = 0; j != 10; j++){
            if(bomb_map[i][j] < 0) screen[i][j] = "x";
        }
    }
}

void print_display(){
    system("cls");
    printf("\n %d BOMBS LEFT    ", bomb_count - marked_count);
    if(mark_mode == 0) printf("DIGGING\n\n");
    else printf("MARKING\n\n");
    printf("    A B C D E F G H I J \n");
    printf("  O---------------------O\n");
    for(int i = 0; i != 10; i++){
        printf("%i | ", i);
        for(int j = 0; j != 10; j++){
            printf("%s ", screen[i][j]);
        }
        if(i == 1) printf("|   type coordinate to dig/mark it\n");
        else if(i == 2) printf("|   e.g. - 'a0'\n");
        else if(i == 4) printf("|   type 'dd' to enter digging mode\n");
        else if(i == 5) printf("|   type 'mm' to enter marking mode\n");
        else printf("|\n");
    }
    printf("  O---------------------O\n");
}

void win_check(){
    int left_tiles = 0;
    for(int i = 0; i != 10; i++){
        for(int j = 0; j != 10; j++){
            if(strcmp(screen[i][j], ".") == 0 || strcmp(screen[i][j], "*") == 0) left_tiles++;
        }
    }
    if(left_tiles == bomb_count){
        print_display();
        game_state = 1;
        printf("you win");
    }
}

void dig(){
    if(check_mode_change() == 1) return;
    if(strcmp(screen[calculate_coords()/10][calculate_coords()%10], " ") == 0) return;
    if(strcmp(screen[calculate_coords()/10][calculate_coords()%10], "*") == 0) return;
    if(bomb_map[calculate_coords()/10][calculate_coords()%10] < 0){
        game_state = 1;
        reveal_bombs();
        print_display();
        printf("you lose");
    }
    if(bomb_map[calculate_coords()/10][calculate_coords()%10] > 0) clear_tile();
    else{
        clear_tile();
        clear_fog();
    }
}

void mark(){
    if(check_mode_change() == 1) return;
    if(strcmp(screen[calculate_coords()/10][calculate_coords()%10], ".") == 0){
        screen[calculate_coords()/10][calculate_coords()%10] = "*";
        marked_count++;
    }
    else if(strcmp(screen[calculate_coords()/10][calculate_coords()%10], "*") == 0){
        screen[calculate_coords()/10][calculate_coords()%10] = ".";
        marked_count--;
    }
}

void initialize(){
    print_display();
    input();
    srand(time(NULL));
    generate_bombs(bomb_count);
    generate_numbers();
    dig();
    win_check();
}

int main(){
    initialize();

    while(1){
        if(game_state == 1) break;
        print_display();
        input();
        if(mark_mode == 0) dig();
        if(mark_mode == 1) mark();
        win_check();
    }

    getch();
}
