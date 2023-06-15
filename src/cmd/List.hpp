#ifndef LIST_HPP
# define LIST_HPP

#include "Cmd.hpp"


class List : public Cmd
{
private:
	/* data */

public:
	List();
	List(const List& ref);
	~List();

	List&	operator=(const List& ref);
};

#endif
