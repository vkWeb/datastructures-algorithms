#include <stdio.h>
#include <string.h>

/* Maximum input size */
#define MAXLINESIZE 1024

/* Assembly commands */
#define ACC "acc\0"
#define JMP "jmp\0"
#define NOP "nop\0"

/*
    Char lengths of commands, delimiter between command & its argument,
    + / - sign and end of line delim i.e. `\n`
*/
#define CMDLEN 3
#define DELIMLEN 1
#define SIGNLEN 1
#define LINEENDDELIMLEN 1

unsigned int calculateDigits(int n)
{
    unsigned int digits = 0;

    do
    {
        ++digits;
        n = n / 10;
    } while (n > 0);

    return digits;
}

unsigned int calcBytesOfCommand(int n)
{
    unsigned int digits = calculateDigits(n);
    return digits + CMDLEN + DELIMLEN + SIGNLEN + LINEENDDELIMLEN;
}

/* Main function; returns accumulator */
int main(int argc, char *argv[])
{
    /* Check whether user provides input file */
    if (argc != 2)
    {
        fprintf(stderr, "error: expected one file as an argument\n");
        fprintf(stderr, "Correct usage: ./main input\n");
        return 1;
    }

    /* Safely open input file */
    FILE *input_file = fopen(argv[1], "r");
    /*if (input_file == NULL)
    {
        fprintf(stderr, "error: can't open file \"%s\"\n", argv[1]);
        return 2;
    }*/

    /* Index file for faster IO */
    char *command;
    int command_argument;

    unsigned int lines_read = 0;
    unsigned int start_byte_pos_lines[MAXLINESIZE];
    char executed_lines[MAXLINESIZE];
    start_byte_pos_lines[0] = 0;
    executed_lines[0] = '0';
    while (fscanf(input_file, "%s %d", command, &command_argument) == 2)
    {
        ++lines_read;
        executed_lines[lines_read] = '0';
        start_byte_pos_lines[lines_read] = calcBytesOfCommand(command_argument);
    }

    /* Scan lines and do commands */
    printf("executed_lines[4] = %c\n", executed_lines[4]); // debug
    int accumulator = 0;
    unsigned int current_line_index = -1;

    printf("outside loop\n"); // debug

    while (fscanf(input_file, "%s %d", command, &command_argument) == 2)
    {
        ++current_line_index;
        printf("on loop, line_index = %d\n", current_line_index); // debug
        /* Check whether the current line has been executed */
        if (executed_lines[current_line_index] == '1')
        {
            printf("%d\n", accumulator); // debug
            break;
        }
        else
        {
            executed_lines[current_line_index] = '1';
            if (strcmp(command, ACC) == 0)
            {
                printf("acc %d\n", command_argument); // debug
                accumulator += command_argument;
            }
            else if (strcmp(command, JMP) == 0)
            {
                printf("jmp %d\n", command_argument); // debug
                fseek(input_file, start_byte_pos_lines[current_line_index + command_argument], SEEK_SET);
            }
        }
    }

    fclose(input_file);
    return 0;
}
