#ifndef LIST_HPP
#define LIST_HPP

#include "Cmd.hpp"

// /channel list & /channel -> 자기가 속한 채널들

class List : public Cmd
{
private:
	/* data */

public:
	List();
	List(const List &ref);
	~List();

	List &operator=(const List &ref);
};

#endif
