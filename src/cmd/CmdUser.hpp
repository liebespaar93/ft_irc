#ifndef CMDUSER_HPP
# define CMDUSER_HPP

#include "Cmd.hpp"

class CmdUser: public Cmd
{
private:
	/* data */
	CmdUser(const CmdUser& ref) {};
	CmdUser&	operator=(const CmdUser& ref) {return *this; } ;

public:
	CmdUser() { this->_cmd = "USER";};
	~CmdUser() {};

	void ft_recv(std::vector<std::string> msg)
	{
		this->_server;
	}
};

#endif