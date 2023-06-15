#ifndef INVITE_HPP
# define INVITE_HPP


#include "Cmd.hpp"


class Invite: public Cmd
{
private:
	/* data */
	Invite(const Invite& ref);

	Invite&	operator=(const Invite& ref);

public:
	Invite() { this->_cmd = "INVITE"; };
	~Invite(){};

	
};

#endif
