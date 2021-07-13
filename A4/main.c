/*
Theo Rowlett
CS-201 Spring 2021
A4: Application that takes at least 2 arguments and not more than 15 and does math on them from a menu.
*/
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

#define MENU_ELEMENTS 7
#define MAX_STRING 22

void menu();
int hex_parse(char * argument);
void addition(int argc, char * argv[]);
void subtraction(int argc, char * argv[]);
void multiplication(int argc, char * argv[]);
void division(int argc, char * argv[]);
void modulus(int argc, char * argv[]);
void reverse_input(int argc, char * argv[]);

struct
Menu {
    char ** choices;
    int options;
};

int
main(int argc, char * argv[])
{
    typedef void (*Options)(int argc, char* argv[]);
    Options Table[] =
    {
        addition,
        subtraction,
        multiplication,
        division,
        modulus,
        reverse_input
    };

    int selection;
    int result;
    float div_result;

    if (argc > 16 || argc < 2)
    {
        printf("Invalid number of arguments. Terminating Application.\n");
        exit(1);
    }

    do
    {
        menu();
        printf("Menu item: ");
        scanf("%d",&selection);
        if (selection != 0 && selection < MENU_ELEMENTS)
            Table[selection-1](argc,argv);
        else if(selection >= MENU_ELEMENTS)
            printf("Invalid selection. Try again.\n\n");
    } while (selection != 0);
    
    exit(0);
}

void
menu()
{
    int i = 0;
    struct Menu Main_menu;
    Main_menu.options = MENU_ELEMENTS;
    Main_menu.choices = malloc(sizeof(char*)*MENU_ELEMENTS);
    for (i; i < MENU_ELEMENTS; i++)
		Main_menu.choices[i] = malloc(MAX_STRING+1);

    strncpy(Main_menu.choices[0],"Exit",MAX_STRING);
    strncpy(Main_menu.choices[1],"Addition",MAX_STRING);
    strncpy(Main_menu.choices[2],"Subtraction",MAX_STRING);
    strncpy(Main_menu.choices[3],"Multiplication",MAX_STRING);
    strncpy(Main_menu.choices[4],"Division",MAX_STRING);
    strncpy(Main_menu.choices[5],"Modulo",MAX_STRING);
    strncpy(Main_menu.choices[6],"Reverse Input",MAX_STRING);

    i = 0;
    for (i;i<MENU_ELEMENTS;++i)
    {
        printf("%d.\t%s\n",i,Main_menu.choices[i]);
        free(Main_menu.choices[i]);
    }
    free(Main_menu.choices);
    return;
}

int
hex_parse(char * argument)
{
    char dest[256];
    int return_val;

    strncpy(dest,argument,2);
    if (strncmp(dest,"0x",2)==0  || strncmp(dest,"0X",2)==0)
    {
        sscanf(argument,"%x",&return_val);
    }
    else
    {
        sscanf(argument,"%d",&return_val);
    }
    return return_val;
}

void
addition(int argc, char * argv[])
{
    int i = 1;
    int sum = 0;
    int addend;
    for (i; i < argc; ++i)
    {
        addend = hex_parse(argv[i]);
        if (argc==i+1)
        {
            printf("%d = ",addend);
        }
        else
            printf("%d + ",addend);

        sum += addend;
    }
    printf("%d\n\n",sum);
    return;
}

void
subtraction(int argc, char * argv[])
{
    int i = 2;
    int total = hex_parse(argv[1]);
    printf("%d - ",total);
    int subtrahend;
    for (i; i < argc; ++i)
    {
        subtrahend = hex_parse(argv[i]);
        if (argc==i+1)
        {
            printf("%d = ",subtrahend);
        }
        else
            printf("%d - ",subtrahend);

        total -= subtrahend;
    }
    printf("%d\n\n",total);
    return;
}

void
multiplication(int argc, char * argv[])
{
    int i = 1;
    int total = 1;
    int multiplicand;
    for (i; i < argc; ++i)
    {
        multiplicand = hex_parse(argv[i]);
        if (argc==i+1)
        {
            printf("%d = ",multiplicand);
        }
        else
            printf("%d * ",multiplicand);

        total = total * multiplicand;
    }
    printf("%d\n\n",total);
    return;
}

void
division(int argc,char * argv[])
{
    printf("%s / %s = ",argv[1],argv[2]);
    printf("%f\n\n",(float)hex_parse(argv[1])/(float)hex_parse(argv[2]));
    return;
}

void
modulus(int argc, char * argv[])
{
    printf("%s %% %s = ",argv[1],argv[2]);
    printf("%d\n\n",hex_parse(argv[1])%hex_parse(argv[2]));
    return;
}

void
reverse_input(int argc, char * argv[])
{
    int i = argc - 1;
    int size = 0;
    for (i;i>0;--i)
    {
        size = strlen(argv[i]);
        for (size;size>0;--size)
        {
            printf("%c",argv[i][size-1]);
        }
        printf(" ");
    }
    printf("\n\n");
    return;
}