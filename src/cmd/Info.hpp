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
		this->ft_send();
		RPL_ENDOFINFO (this->_client);
	}

};

#endif
//Request: INFO 
//Response: :*.freenode.net 371 nick_name :                   -/\- \002InspIRCd\002 -\/-
//Response: :*.freenode.net 371 nick_name :                 November 2002 - Present
//Response: :*.freenode.net 374 nick_name :End of /INFO list