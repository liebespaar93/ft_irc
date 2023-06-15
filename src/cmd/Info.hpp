#ifndef INFO_HPP
# define INFO_HPP

#include "Cmd.hpp"

class Info: public Cmd
{
private:
	/* data */
	Info(const Info& ref) {};
	Info&	operator=(const Info& ref) { return *this;};


public:
	Info() { this->_cmd = "INFO"; };
	~Info() {};


	void ft_recv(std::vector<std::string> msg)
	{
		RPL_INFO(this->_client, "kyoulee & gyeokim ft_irc");
		RPL_ENDOFINFO (this->_client);
	}

};

#endif
