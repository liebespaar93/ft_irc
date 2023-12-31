#ifndef KICK_HPP
#define KICK_HPP

#include "Cmd.hpp"

class Kick : public Cmd
{
private:
	/* data */
	Kick(const Kick &ref) { (void)ref; };
	Kick &operator=(const Kick &ref)
	{
		(void)ref;
		return *this;
	};

public:
	Kick()
	{
		this->_cmd = "KICK";
	};
	~Kick(){};

	void ft_recv(std::vector<std::string> msg)
	{
		if (!this->_user->ft_get_login())
			return;
		if (msg.size() == 1)
		{
			this->ft_set_client("461");
			this->_send_msg = ERR_NEEDMOREPARAMS(this->_client, this->_cmd);
			this->ft_append_msg();
			return;
		}
		if (!this->_server->ft_get_channel(msg[1]))
		{
			this->ft_set_client("403");
			this->_send_msg = ERR_NOSUCHCHANNEL(this->_client, msg[1]);
			this->ft_append_msg();
			return;
		}
		if (!this->_user->ft_get_channel(msg[1]))
		{
			this->ft_set_client("442");
			this->_send_msg = ERR_NOTONCHANNEL(this->_client, msg[1]);
			this->ft_append_msg();
			return;
		}
		if (!this->_user->ft_get_channel(msg[1])->ft_privilege_has_user(this->_user->ft_get_user_name()))
		{
			this->ft_set_client("482");
			this->_send_msg = ERR_CHANOPRIVSNEEDED(this->_client, msg[1]);
			this->ft_append_msg();
			return;
		}
		this->_send_msg = ":" + this->_user->ft_get_info() + " " + this->_cmd + " " + msg[1] + " ";
		size_t i = 2;
		while (i < msg.size())
			this->_send_msg += msg[i++] + " ";
		std::map<std::string, User *> user_list = this->_server->ft_get_channel(msg[1])->ft_get_user_list();
		for (std::map<std::string, User *>::iterator it = user_list.begin(); it != user_list.end(); it++)
		{
			this->ft_append_msg(it->second);
		}
		i = 2;
		while (i < msg.size())
			this->_user->ft_get_channel(msg[1])->ft_channel_leave_user(this->_server->ft_get_nick(msg[i++]));
	}
};

#endif
