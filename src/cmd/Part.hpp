#ifndef PART_HPP
# define PART_HPP

#include "Cmd.hpp"

class Part: public Cmd
{
private:
	/* data */

public:
	Part();
	Part(const Part& ref);
	~Part();

	Part&	operator=(const Part& ref);
};

#endif
