#ifndef QUIT_HPP
# define QUIT_HPP

#include "Cmd.hpp"

class Quit: public Cmd
{
private:
	/* data */

public:
	Quit();
	Quit(const Quit& ref);
	~Quit();

	Quit&	operator=(const Quit& ref);
};

#endif


// Request: QUIT Leaving...
// Response: ERROR :Closing link: (~login@175.223.44.157) [Quit: Leaving...]