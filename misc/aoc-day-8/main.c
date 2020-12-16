#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*  MEMORY SAFETY ASSUMPTION:
    JMP command's argument MUST NOT overflow the instructions.
    Right now, this program cannot handle that situation.
*/

/* Maximum number of lines allowed in the input file */
#define MAXINPUTSIZE 1024

/* Assembly commands */
#define ACC "acc\0"
#define JMP "jmp\0"
#define NOP "nop\0"

/* Byte length of a command */
#define CMDLEN 3

/* Boot backtrack failure code */
#define BCKTRCKFAIL -2

/* Structure to store an assembly command */
struct command
{
    char cmd[CMDLEN + 1];
    int arg;
    char is_run_flag;
};

/*  Read file line-wise, store command & argument in provided struct
    set is_run_flag to '0' i.e. false.
    Returns the number of commands read from file. */
unsigned int indexFile(struct command cmds[], unsigned int max_cmds_size, FILE *infile)
{
    unsigned int i = 0;
    char buffer[16];
    while (i < max_cmds_size && fgets(buffer, 16, infile) != NULL)
    {
        if (sscanf(buffer, "%s %d", cmds[i].cmd, &cmds[i].arg) == 2)
        {
            cmds[i].is_run_flag = '0';
        }
        else
        {
            fprintf(stderr, "error on indexFile: read failure from sscanf\n");
            exit(3);
        }
        ++i;
    }
    return i;
}

/*  Runs the assembly boot commands;
    returns (start_index + number of operations executed before boot failure
    or program end, whichever comes first) - 1 */
unsigned int boot(struct command cmds[], int acc[], unsigned int cmd_seq[], unsigned int size, unsigned int start_index)
{
    int i = start_index;
    int temp_acc = 0;
    while (i < size && cmd_seq[i] < size && cmds[cmd_seq[i]].is_run_flag == '0')
    {
        cmd_seq[i + 1] = cmd_seq[i] + 1;

        if (strcmp(cmds[cmd_seq[i]].cmd, ACC) == 0)
        {
            temp_acc += cmds[cmd_seq[i]].arg;
        }
        else if (strcmp(cmds[cmd_seq[i]].cmd, JMP) == 0)
        {
            cmd_seq[i + 1] = cmd_seq[i] + cmds[cmd_seq[i]].arg;
        }

        acc[i] = temp_acc;
        cmds[cmd_seq[i]].is_run_flag = '1';
        fprintf(stdout, "Read %s %d\n", cmds[cmd_seq[i]].cmd, cmds[cmd_seq[i]].arg); // debug
        ++i;
    }
    return i - 1;
}

/*  Update command
    if command is NOP, change to JMP and vice versa
    return '1' if success else '0' */
char updateCmd(struct command cmds[], unsigned int i)
{
    if (strcmp(cmds[i].cmd, NOP) == 0)
    {
        fprintf(stdout, "%s to %s\n", cmds[i].cmd, JMP); // debug
        strcpy(cmds[i].cmd, JMP);
        return '1';
    }
    else if (strcmp(cmds[i].cmd, JMP) == 0)
    {
        fprintf(stdout, "%s to %s\n", cmds[i].cmd, NOP); // debug
        strcpy(cmds[i].cmd, NOP);
        return '1';
    }
    return '0';
}

/*  Backtracks boot instructions until a JMP or NOP cmd is found and updated
    cmds being backtracked are marked as not-run
    returns the tracker of cmd_seq array */
signed int backtrackBoot(struct command cmds[], unsigned int cmd_seq[], unsigned int i)
{
    while (i >= 0)
    {
        cmds[cmd_seq[i]].is_run_flag = '0';
        if (updateCmd(cmds, cmd_seq[i]) == '1')
        {
            break;
        }
        else if (i == 0)
        {
            i = BCKTRCKFAIL;
            break;
        }
        --i;
    }
    return i;
}

/* Main function */
int main(int argc, char *argv[])
{
    /* Check whether we have a file as an argument */
    if (argc != 2)
    {
        fprintf(stderr, "error: expected one file as an argument\n");
        fprintf(stderr, "Correct usage: ./main input-file\n");
        exit(1);
    }

    /* Safely open & validate input file */
    FILE *input_file = fopen(argv[1], "r");
    if (input_file == NULL)
    {
        fprintf(stderr, "error: can't open file \"%s\"\n", argv[1]);
        exit(2);
    }

    /* Index file */
    struct command cmds[MAXINPUTSIZE];
    unsigned int num_of_cmds = indexFile(cmds, MAXINPUTSIZE, input_file);

    /* BOOT */
    int accumulator[num_of_cmds];
    unsigned int command_sequence[num_of_cmds + 1];
    command_sequence[0] = 0;

    int i = 0, back_i = -1;
    i = boot(cmds, accumulator, command_sequence, num_of_cmds, 0);
    while (command_sequence[i + 1] != num_of_cmds)
    {
        /* our first backtrack will start from i */
        if (back_i == -1)
        {
            back_i = i;
        }
        else
        {
            updateCmd(cmds, command_sequence[back_i]);
        }

        back_i = backtrackBoot(cmds, command_sequence, back_i);
        if (back_i == BCKTRCKFAIL)
        {
            fprintf(stderr, "fail: can't correct the corrupted assembly :(\n");
            exit(3);
        }

        i = boot(cmds, accumulator, command_sequence, num_of_cmds, back_i);
    }

    fprintf(stdout, "Accumulator = %d\n", accumulator[i]); // debug
    fclose(input_file);
    return 0;
}
