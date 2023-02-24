# include "global.h"
#include "function.h"


ft_lexer()
{
	ft_trim();	//one or more manipulete the string with space and obtain token like +cmd +arg of cmd +|something +> something +< something +>> something +<< something
/*
pay attention on how to deal with '' "" maybe do somthing to deal with like subshell so ignore it and gestiscili a parte
*/
	ft_parser();  // starting from output of lexer store the token,  

}

ft_executor()
{
	// make fork to execut child process and not kill parent 
	if ()
		builtin
	else
		ft_simplecommand();	// execve

		fd to deal with manipulation
	> 
	<
	>>
	<<
	| -->simple command pay attemptio to pass right input
	
}


int main (int argc, char *argv[], char *envp[])
{

	if (argc != 1 || argv[1])
	{
		printf("This program does not accept arguments\n");
		exit(0);
	}
	ft_makingthingready(); // set all you need env, initialize variable struct and array
	while (/* condition */)
	{
		ft_signal();  	// all about ctrl-d ... signal needed. maybe dealt with error
		ft_lexer();   	// receive in input the strign from stdin and manipulate it to obtein token must be stored in array or struct?
		ft_executor();	// receive table of command (struct or array) dealt with execv built in. decide to start command, built in or how to concern aout > < >> << | alias work with fd redirection
	
	}
	

}