#include "lexing.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>



//	use CTRL + D to exit the shell

/*
	if CTRL + D is pressed (which sends an EOF — End Of File to *line) 
	essentialy setting it to NULL which ends loop and shell terminates
	but prompt needs to be empty for CTRL + D to work (for now) .
	You may need to compile with readline lib "cc read_line.c -lreadline"
	but that may be because im using mbp, the school computers probaly
	have the libraries installed and you dont neet to include the lib.
*/


void	ft_print_line(char *line)
{
	while (*line)
		write(1, line++, 1);
	write(1, "\n", 1);
}

int main(void)
{
    char *line;

    while ((line = readline("minishell$ ")) != NULL)
    {
        if (*line)
		{

//			ft_print_line(line);
            add_history(line);
			lexing(line);
		}
        free(line);
    }

    return 0;
}
