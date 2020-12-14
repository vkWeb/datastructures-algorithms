#include <stdio.h>
#include <stdlib.h>
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

unsigned int calculateDigits(unsigned int n)
{
    unsigned int digits = 0;

    do
    {
        ++digits;
        n = n / 10;
    } while (n > 0);

    return digits;
}

unsigned int calcBytesOfCommand(unsigned int n)
{
    unsigned int digits = calculateDigits(n);
    return (digits + CMDLEN + DELIMLEN + SIGNLEN + LINEENDDELIMLEN);
}

/* Main function; returns accumulator */
int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "error: expected one file as an argument\n");
        fprintf(stderr, "Correct usage: ./main input-file\n");
        exit(1);
    }

    /* Safely open input file */
    FILE *input_file = fopen(argv[1], "r");
    if (input_file == NULL)
    {
        fprintf(stderr, "error: can't open file \"%s\"\n", argv[1]);
        exit(2);
    }

    /* Index file for faster IO */
    char command[16];
    int command_argument;
    unsigned int lines_read = 0; /* State for lines that are read */

    unsigned int start_byte_pos_lines[MAXLINESIZE]; /* Start byte pos of every line */
    char executed_lines[MAXLINESIZE];               /* Array to initialize lines that are executed to '0' i.e. not executed */

    start_byte_pos_lines[0] = 0;
    executed_lines[0] = '0';
    while (fgets(command, 16, input_file) != NULL)
    {
        sscanf(command, "%*s %d", &command_argument);
        ++lines_read;
        executed_lines[lines_read] = '0';
        start_byte_pos_lines[lines_read] = start_byte_pos_lines[lines_read - 1] + calcBytesOfCommand(abs(command_argument));
    }

    // Scan lines and do commands
    int accumulator = 0;
    unsigned int current_line_index = -1;
    fseek(input_file, 0, SEEK_SET);

    while (fgets(command, 16, input_file) != NULL)
    {
        ++current_line_index;
        printf("Read %s", command); // debug

        // Check whether the current line has been executed
        if (executed_lines[current_line_index] == '1')
        {
            printf("Accumulator is: %d\n", accumulator);
            break;
        }
        else
        {
            executed_lines[current_line_index] = '1';
            char cmd_buff[4];
            sscanf(command, "%s %d", cmd_buff, &command_argument);
            if (strcmp(cmd_buff, ACC) == 0)
            {
                accumulator += command_argument;
            }
            else if (strcmp(cmd_buff, JMP) == 0)
            {
                current_line_index += command_argument;
                fseek(input_file, start_byte_pos_lines[current_line_index], SEEK_SET);
                --current_line_index;
            }
        }
    }

    fclose(input_file);
    return 0;
}
