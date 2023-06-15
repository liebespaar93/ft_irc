#ifndef NOTICE_HPP
# define NOTICE_HPP

#include "Cmd.hpp"

class Notice: public Cmd
{
private:
	/* data */

public:
	Notice();
	Notice(const Notice& ref);
	~Notice();

	Notice&	operator=(const Notice& ref);
};

#endif
