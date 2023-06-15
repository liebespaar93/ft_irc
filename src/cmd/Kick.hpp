#ifndef KICK_HPP
# define KICK_HPP


#include "Cmd.hpp"


class Kick: public Cmd
{
private:
	/* data */

public:
	Kick();
	Kick(const Kick& ref);
	~Kick();

	Kick&	operator=(const Kick& ref);
};

#endif
