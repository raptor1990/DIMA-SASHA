#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX 20
#define MIN_LIMIT 7

struct bintr {
    char *word;
    int count;
    int index;
    int array_size;
    int *array_p;
    struct bintr *left;
    struct bintr *right;    
};

struct bintr *add(struct bintr *, char *);
void print(struct bintr *, int);
int getword(char *, int);
void find_max_count(struct bintr *);

static int max_count = 0;
static int strcount = 1;

int main()
{
    char word[MAX];
    struct bintr *root;

    root = NULL;
    while (getword(word, MAX) != EOF) {
        if (isalpha(word[0])) {
            root = add(root, word);
        }
    }
    find_max_count(root);
    for ( ; max_count > MIN_LIMIT; max_count--) {
        print(root, max_count);
    }
    return 0;
}

#include <string.h>

char *strdupl(char *);
struct bintr *talloc(void);

struct bintr *add(struct bintr *p, char *w)
{
    int cond, i;   

    if (p == NULL) {
        p = talloc();
        p->word = strdupl(w);
        p->count = 1;
        p->index = 0;
        p->array_size = MAX;
        p->array_p = (int *) malloc(sizeof(int *) * p->array_size);
        p->array_p = &strcount;
        p->array_p++;
        p->index++;
        p->left = NULL;
        p->right = NULL;
    }
    else {
        if ((cond = strcmp(p->word, w)) == 0) {
            p->count++;
            if (p->array_size == p->index) {
                p->array_p = (int *) realloc(p->array_p, sizeof(int *) * (p->array_size * 2));
                p->array_size *= 2;
            }
            p->array_p = &strcount;
            p->array_p++;
            p->index++;
        }
        else if (cond < 0) {
            p->right = add(p->right, w);
        }
        else {
            p->left = add(p->left, w);
        }
    }
    return p;
}

int getch(void);
void ungetch(int);
char lower(char);

int getword(char *word, int m)
{
    int c, j;
    char *w = word;

    c = getch();
    if (c == '\n') {
        strcount++;
    }
    if (c != EOF) {
        *w = c;
        w++;
    }
    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }
    for ( ; --m > 0; w++) {
        if (!isalnum(*w = getch())) {
            ungetch(*w);
            break;
        }
    }
    *w = '\0';
    for (j = 0; word[j] != '\0'; j++) {
        word[j] = lower(word[j]);  
    }
    if (strlen(word) < 3) {
        word[0] = '\0';
    }
    return word[0];
}

char lower(char c)
{
    if (isupper(c))
        return c - 'A' + 'a';
    else
        return c;
}

void find_max_count(struct bintr *p) 
{
    if (p != NULL) {
        find_max_count(p->left);
        if (p->count > max_count) {
            max_count = p->count;                    
        }
        find_max_count(p->right);
    }
}

void print(struct bintr *p, int max) 
{
    int i;

    if (p != NULL) {
        print(p->left, max);
        if (p->count == max) {
            printf("%3d - %-10s - ", p->count, p->word);
            for (i = p->index; i > 0; i--) {
                printf("%d", *p->array_p);
                p->array_p--;
                if (i != 1) {
                    printf(", ");
                }
            }
        printf("\n");    
        }
        print(p->right, max);
    }
}

int buf[MAX];
int bufp = 0;

int getch(void)
{
    return (bufp == 0) ? getchar() : buf[--bufp];
}

void ungetch(int c)
{
    if (bufp < MAX) {
        buf[bufp++] = c;
    }
}

struct bintr *talloc(void)
{
    return (struct bintr *) malloc(sizeof(struct bintr));
}

char *strdupl(char *w)
{
    char *p = (char *) malloc(strlen(w));
    if (p != NULL) {
        strcpy(p, w);
    }
    return p;
}
