#ifndef INVITE_HPP
# define INVITE_HPP


#include "Cmd.hpp"


class Invite: public Cmd
{
private:
	/* data */

public:
	Invite();
	Invite(const Invite& ref);
	~Invite();

	Invite&	operator=(const Invite& ref);
};

#endif
