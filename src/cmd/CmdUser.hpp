#ifndef CMDUSER_HPP
#define CMDUSER_HPP

#include "Cmd.hpp"
#include <cstdlib>
#include "Utile.hpp"

class CmdUser : public Cmd
{
private:
	/* data */
	CmdUser(const CmdUser &ref) { (void)ref; };
	CmdUser &operator=(const CmdUser &ref)
	{
		(void)ref;
		return *this;
	};

public:
	CmdUser() { this->_cmd = "USER"; };
	~CmdUser(){};

	void ft_recv(std::vector<std::string> msg)
	{
		std::string user_name = "";
		std::string real_name = "";
		if (msg.size() <= 4)
		{
			this->ft_set_client("461");
			this->_send_msg = ERR_NEEDMOREPARAMS(this->_client, this->_cmd);
			this->ft_send();
			return;
		}
		user_name = msg[1];
		if (this->_server->ft_get_user(user_name))
		{
			int i = 0;
			user_name = user_name + "_";
			while (this->_server->ft_get_user(user_name + ft_itostring(i)))
				i++;
			user_name = user_name + ft_itostring(i);
		}
		size_t i = 3;
		while (i < msg.size())
		{
			real_name += msg[i++];
		}
		Logger(user_name).ft_user_name(this->_user->ft_get_fd());
		this->_server->ft_append_user_name(user_name, this->_user);
		this->_user->ft_set_real_name(real_name);
		if (this->_user->ft_get_nick_name() == "")
		{
			send(this->_user->ft_get_fd(), ":ft_irc NOTICE * :*** Looking up your ident...;", 48, 0);
			send(this->_user->ft_get_fd(), ":ft_irc NOTICE * :*** Looking up your nickname...;", 51, 0);
			return;
		}
		this->_user->ft_set_login();
		if (!this->_user->ft_get_pass())
		{
			this->ft_set_client("462");
			this->_send_msg = ERR_ALREADYREGISTERED(this->_client);
			this->ft_send();
			return;
		}
		if (this->_user->ft_get_login() && this->_user->ft_get_pass() && !this->_user->ft_get_wellcome())
		{
			this->ft_set_client("001");
			this->_send_msg = RPL_WELCOME(this->_client, this->_server_name, this->_user->ft_get_nick_name(), this->_user->ft_get_user_name(), this->_user->ft_get_IP());
			this->ft_send();
			this->ft_set_client("002");
			this->_send_msg = RPL_YOURHOST(this->_client, this->_server_name, "v.1");
			this->ft_send();
			this->ft_set_client("003");
			this->_send_msg = RPL_CREATED(this->_client, (std::string)(this->_timestr));
			this->ft_send();
			this->_user->ft_set_wellcome();
		}
	}
};

#endif
