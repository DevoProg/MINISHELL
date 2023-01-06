#include "../../includes/minishell.h"

void close_redi_pipe(int redi_pipe[2][2])
{
    close(redi_pipe[0][0]);
    close(redi_pipe[0][1]);
    close(redi_pipe[1][0]);
    close(redi_pipe[1][1]);
}
