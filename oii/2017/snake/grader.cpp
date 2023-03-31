#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define SEED1 17044003190456494363ULL
#define SEED2 14282861847990642329ULL

typedef struct
{
    int riga;
    int colonna;
} cella_t;

typedef enum
{
    SOPRA,
    SOTTO,
    DESTRA,
    SINISTRA
} direzione_t;

void gioca(int, int);

#define EMPTY 0
#define SNAKE 1
#define APPLE 2

typedef struct _node_t
{
    cella_t pos;
    struct _node_t* next;
    struct _node_t* prev;
} node_t;

static int R, C;
static cella_t apple;
static int snake_length = 0;
static node_t* snake_head = NULL;
static node_t* snake_tail = NULL;
static int** grid;
static cella_t* empty_cells;
static int empty_cells_size = 0;

static void finalize()
{
    int i;
    node_t* tmp;
    while(snake_head)
    {
        tmp = snake_head;
        snake_head = tmp->next;
        free(tmp);
    }
    for(i = 0; i < R; i++)
        free(grid[i]);
    free(grid);
    free(empty_cells);
    printf("%d\n", snake_length);
}

static unsigned long long int xorshift128plus()
{
    static unsigned long long int s[2] = {SEED1, SEED2};
    unsigned long long int x = s[0];
    const unsigned long long int y = s[1];
    s[0] = y;
    x ^= x << 23;
    s[1] = x ^ y ^ (x >> 17) ^ (y >> 26);
    return s[1] + y;
}

static cella_t extract_random_free_cell()
{
    int i, j;
    size_t pos;
    empty_cells_size = 0;
    for(i = 0; i < R; i++)
    {
        for(j = 0; j < C; j++)
        {
            if(grid[i][j] != EMPTY)
                continue;
            empty_cells[empty_cells_size].riga = i;
            empty_cells[empty_cells_size].colonna = j;
            empty_cells_size++;
        }
    }
    pos = xorshift128plus() % empty_cells_size;
    return empty_cells[pos];
}

static void new_apple()
{
    apple = extract_random_free_cell();
    grid[apple.riga][apple.colonna] = APPLE;
}

cella_t posizione_mela()
{
    return apple;
}

void muovi(direzione_t d)
{
    cella_t pos = snake_head->pos;
    node_t* new_head;
    node_t* old_tail;
    if(d == SOPRA)
        pos.riga--;
    else if(d == SOTTO)
        pos.riga++;
    else if(d == DESTRA)
        pos.colonna++;
    else if(d == SINISTRA)
        pos.colonna--;
    else
        exit(EXIT_FAILURE);
    if(pos.riga < 0 || pos.riga >= R)
        exit(EXIT_SUCCESS);
    if(pos.colonna < 0 || pos.colonna >= C)
        exit(EXIT_SUCCESS);
    if(grid[pos.riga][pos.colonna] == SNAKE && !(pos.riga == snake_tail->pos.riga && pos.colonna == snake_tail->pos.colonna))
    {
        exit(EXIT_SUCCESS);
    }
    else if(grid[pos.riga][pos.colonna] == APPLE)
    {
        grid[pos.riga][pos.colonna] = SNAKE;
        new_head = (node_t*)malloc(sizeof(node_t));
        assert(new_head);
        new_head->next = snake_head;
        snake_head->prev = new_head;
        new_head->pos = pos;
        snake_head = new_head;
        snake_length++;
        if(snake_length == R * C)
            exit(EXIT_SUCCESS);
        else
            new_apple();
    }
    else
    {
        grid[pos.riga][pos.colonna] = SNAKE;
        new_head = (node_t*)malloc(sizeof(node_t));
        assert(new_head);
        new_head->next = snake_head;
        snake_head->prev = new_head;
        new_head->pos = pos;
        snake_head = new_head;
        old_tail = snake_tail;
        snake_tail = old_tail->prev;
        snake_tail->next = NULL;
        grid[old_tail->pos.riga][old_tail->pos.colonna] = EMPTY;
        free(old_tail);
    }
}

int main()
{
    int i;
    node_t* snake;
    scanf("%d", &R);
    scanf("%d", &C);
    empty_cells = (cella_t*)calloc(R * C, sizeof(cella_t));
    assert(empty_cells);
    grid = (int**)calloc(R, sizeof(int*));
    assert(grid);
    for(i = 0; i < R; i++)
    {
        grid[i] = (int*)calloc(C, sizeof(int));
        assert(grid[i]);
    }
    snake = (node_t*)malloc(sizeof(node_t));
    assert(snake);
    snake->pos.riga = snake->pos.colonna = 0;
    snake->next = NULL;
    snake->prev = NULL;
    snake_head = snake_tail = snake;
    grid[0][0] = SNAKE;
    snake_length = 1;
    new_apple();
    atexit(finalize);
    gioca(R, C);
    return EXIT_SUCCESS;
}
