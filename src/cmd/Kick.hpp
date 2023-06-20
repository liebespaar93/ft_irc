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
/*
Request: KICK #testroom testnick2 :
all
Response: :testnick!~testlogin@freenode-8ft.tgg.6ohrpn.IP KICK #testroom testnick2 :


*/