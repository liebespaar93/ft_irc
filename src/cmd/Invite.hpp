#ifndef INVITE_HPP
#define INVITE_HPP

#include "Cmd.hpp"

class Invite : public Cmd
{
private:
	/* data */
	Invite(const Invite &ref){};

	Invite &operator=(const Invite &ref) { return *this; };

public:
	Invite() { this->_cmd = "INVITE"; };
	~Invite(){};


	void ft_recv(std::vector<std::string> msg)
	{
		if (!this->_user->ft_get_login())
			return;
		if (msg.size() < 3)
		{
			this->ft_set_client("461");
			this->_send_msg = ERR_NEEDMOREPARAMS(this->_client, this->_cmd);
			this->ft_send();
			return;
		}
		if (!this->_server->ft_get_channel(msg[2]))
		{
			this->ft_set_client("403");
			this->_send_msg = ERR_NOSUCHCHANNEL(this->_client, msg[1]);
			this->ft_send();
			return;
		}
		if (!this->_user->ft_get_channel(msg[2]))
		{
			this->ft_set_client("442");
			this->_send_msg = ERR_NOTONCHANNEL(this->_client, msg[1]);
			this->ft_send();
			return;
		}
		if (this->_server->ft_get_nick(msg[1])->ft_get_channel(msg[1]))
		{
			this->ft_set_client("443");
			this->_send_msg = ERR_USERONCHANNEL(this->_client, msg[2], msg[1]);
			this->ft_send();
			return;
		}
		if (!this->_user->ft_get_channel(msg[2])->ft_privilege_has_user(this->_user->ft_get_user_name()))
		{
			this->ft_set_client("482");
			this->_send_msg = ERR_CHANOPRIVSNEEDED(this->_client, msg[1]);
			this->ft_send();
			return;
		}
		this->_send_msg = this->_user->ft_get_info() + " " + this->_cmd + " " + msg[1] + " :" + msg[2];
		this->ft_send(this->_server->ft_get_nick(msg[1])->ft_get_fd());

		this->ft_set_client("341");
		this->_send_msg = RPL_INVITING(this->_client, msg[1], msg[2]);
		this->ft_send();
	}
};

#endif
