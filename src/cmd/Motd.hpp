#ifndef MOTD_HPP
# define MOTD_HPP

#include "Cmd.hpp"

class Motd: public Cmd
{
private:
	/* data */

public:
	Motd();
	Motd(const Motd& ref);
	~Motd();

	Motd&	operator=(const Motd& ref);
};

#endif
