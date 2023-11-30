#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int snake_x = 5;
int snake_y = 5;
int score = 0;
int point_x = 0;
int point_y = 0;
char *screen[10][10] = {{" ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
                        {" ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
                        {" ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
                        {" ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
                        {" ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
                        {" ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
                        {" ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
                        {" ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
                        {" ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
                        {" ", " ", " ", " ", " ", " ", " ", " ", " ", " "}};
int tail[100][2] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0},
                     {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0},
                     {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0},
                     {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0},
                     {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0},
                     {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0},
                     {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0},
                     {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0},
                     {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0},
                     {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0},
                     {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0},
                     {0, 0}};

int awsd_input(){
    switch(getch()) {
        case 119:         // W - UP
            return 1;
        case 115:         // S - DOWN
            return 2;
        case 100:         // D - RIGHT
            return 3;
        case 97:          // A - LEFT
            return 4;
        case 27:          // ESC - STOP
            return 5;
        default:
            return 0;
    }
}

void clear_snake(){
    screen[snake_x][snake_y] = " ";
}

void write_snake(int p){
    char *snake_head;
    switch(p){
        case 1:
            snake_head = "U";
            break;
        case 2:
            snake_head = "^";
            break;
        case 3:
            snake_head = "<";
            break;
        case 4:
            snake_head = ">";
            break;
        default:
            snake_head = "s";
            break;
    }
    screen[snake_x][snake_y] = snake_head;
}

void tail_history(int x, int y, int l){
    for(int i = l; i != 0; i--){
        tail[i][0] = tail[i-1][0];
        tail[i][1] = tail[i-1][1];
    }
    tail[0][0] = x;
    tail[0][1] = y;
}

void clear_tail(int l){
    screen[tail[l][0]][tail[l][1]] = " ";
}

void write_tail(int l){
    for(int i = 0; i != l; i++){
        screen[tail[i][0]][tail[i][1]] = "~";
    }
}

void snake_tail(int x, int y, int l){
    tail_history(x, y, l);
    clear_tail(l);
    write_tail(l);
}

void generate_score_coordinates(){
    point_x = rand() % 10;
    point_y = rand() % 10;
}

int check_overlapping(int l){
    for(int i = 0; i != l; i++){
        if(point_x == tail[i][0] && point_y == tail[i][1]){
            return 1;
        }
    }
    if(point_x == snake_x && point_y == snake_y){
        return 1;
    }
    else{
        return 0;
    }
}

void spawn_score(){
    generate_score_coordinates();
    while(1){
        if(check_overlapping(score)){
            generate_score_coordinates();
        }
        else{
            break;
        }
    }
    screen[point_x][point_y] = "o";
}

void update_score(){
    if(snake_x == point_x && snake_y == point_y){
        score = score + 1;
        spawn_score();
    }
}

int check_collisions(int d){
    switch(d){
        case 1:
            if(snake_x == 0) return 1;
            if(strcmp(screen[snake_x-1][snake_y], "~") == 0) return 1;
            else return 0;
        case 2:
            if(snake_x == 9) return 1;
            if(strcmp(screen[snake_x+1][snake_y], "~") == 0) return 1;
            else return 0;
        case 3:
            if(snake_y == 9) return 1;
            if(strcmp(screen[snake_x][snake_y+1], "~") == 0) return 1;
            else return 0;
        case 4:
            if(snake_y == 0) return 1;
            if(strcmp(screen[snake_x][snake_y-1], "~") == 0) return 1;
            else return 0;
        default:
            return 0;
    }
}

int check_if_stuck(){
    if(check_collisions(1) && check_collisions(2) &&
    check_collisions(3) && check_collisions(4)){
        return 1;
    }
    else return 0;
}

void move_snake(int l){
    switch(l){
        case 1:
            if(check_collisions(l)) return;
            clear_snake();
            snake_tail(snake_x, snake_y, score);
            snake_x = snake_x - 1;
            update_score();
            write_snake(1);
            return;
        case 2:
            if(check_collisions(l)) return;
            clear_snake();
            snake_tail(snake_x, snake_y, score);
            snake_x = snake_x + 1;
            update_score();
            write_snake(2);
            return;
        case 3:
            if(check_collisions(l)) return;
            clear_snake();
            snake_tail(snake_x, snake_y, score);
            snake_y = snake_y + 1;
            update_score();
            write_snake(3);
            return;
        case 4:
            if(check_collisions(l)) return;
            clear_snake();
            snake_tail(snake_x, snake_y, score);
            snake_y = snake_y - 1;
            update_score();
            write_snake(4);
            return;
        default:
            return;
    }
}

void print_display(){
    system("cls");
    printf("SCORE - %d      AWSD to move\n\n", score);
    printf("O--------------------O\n");
    for(int i = 0; i != 10; i++){
        printf("|");
        for(int j = 0; j != 10; j++){
            printf("%c ", *screen[i][j]);
        }
        printf("|\n");
    }
    printf("O--------------------O\n");
}



int main(){
    int input;

    srand(time(NULL));

    spawn_score();
    write_snake(0);
    print_display();

    while(1){
        input = awsd_input();
        if(input == 5) break;
        if(input != 0){
            move_snake(input);
            print_display();
            if(check_if_stuck()){
                printf("\n\nYOU GOT STUCK DUMBASS\n\n");
                break;
            }
            if (score == 99)0{
                printf("\n\nYOU WON\n\n");
                break;
            }
        }
    }
    printf("\nPress any key to quit\n");
    getch();
}
