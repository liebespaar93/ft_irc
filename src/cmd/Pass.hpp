#ifndef PASS_HPP
# define PASS_HPP

#include "Cmd.hpp"

class Pass: public Cmd
{
private:
	/* data */
	Pass(const Pass& ref){};
	Pass&	operator=(const Pass& ref){return *this;};

public:
	Pass()
	{
		this->_cmd = "PASS";
	};
	~Pass() {};


	void ft_recv(std::vector<std::string> msg)
	{
		std::string password = this->_server->ft_get_password();
		if (msg.size() == 1)
		{
			this->ft_set_client("461");
			this->_send_msg = ERR_NEEDMOREPARAMS(this->_client, this->_cmd);
			this->ft_send();
			return ;
		}
		if (this->_user->ft_get_pass())
		{
			this->ft_set_client("462");
			this->_send_msg = ERR_ALREADYREGISTERED(this->_client);
			this->ft_send();
			return ;
		}
		if (this->_server->ft_get_password().compare(msg[1]))
		{
			this->ft_set_client("464");
			this->_send_msg = ERR_PASSWDMISMATCH(this->_client);
			this->ft_send();
			return ;
		}
		this->_user->ft_set_pass();
		this->_send_msg = ":" + this->_server_name + " NOTICE * :*** Looking up your ident...;";
		this->ft_send();
		this->_send_msg = ":" + this->_server_name + " NOTICE * :*** Looking up your hostname...;";
		this->ft_send();

		this->_send_msg = "PING :logintest";
		this->ft_send();
		Logger("PASS").ft_cmd_msg(this->_user->ft_get_fd());
	}

};

#endif
//Response: :*.freenode.net NOTICE mynick :*** Ident lookup timed out, using ~myname instead.
//Response: :*.freenode.net 001 mynick :Welcome to the freenode IRC Network mynick!~myname@110.70.51.236
//Response: :*.freenode.net 002 mynick :Your host is *.freenode.net, running version InspIRCd-3
//Response: :*.freenode.net 003 mynick :This server was created 23:06:04 Apr 20 2022
