#ifndef JOIN_HPP
# define JOIN_HPP

#include "Cmd.hpp"

class Join: public Cmd
{
private:
	/* data */

public:
	Join();
	Join(const Join& ref);
	~Join();

	Join&	operator=(const Join& ref);
};

#endif
