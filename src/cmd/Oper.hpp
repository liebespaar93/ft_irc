#ifndef OPER_HPP
# define OPER_HPP

#include "Cmd.hpp"

class Oper: public Cmd
{
private:
	/* data */

public:
	Oper();
	Oper(const Oper& ref);
	~Oper();

	Oper&	operator=(const Oper& ref);
};

#endif
