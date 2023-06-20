#ifndef KICK_HPP
#define KICK_HPP

#include "Cmd.hpp"

class Kick : public Cmd
{
private:
	/* data */
	Kick(const Kick &ref){};
	Kick &operator=(const Kick &ref) { return *this; };

public:
	Kick()
	{
		this->_cmd = "KICK";
	};
	~Kick(){};

	void ft_recv(std::vector<std::string> msg)
	{
		if (msg.size() == 1)
		{
			this->ft_set_client("461");
			this->_send_msg = ERR_NEEDMOREPARAMS(this->_client, this->_cmd);
			this->ft_send();
			return;
		}
		if (!this->_server->ft_get_channel(msg[1]))
		{
			this->ft_set_client("403");
			this->_send_msg = ERR_NOSUCHCHANNEL(this->_client, msg[1]);
			this->ft_send();
			return;
		}
		if (!this->_user->ft_get_channel(msg[1]))
		{
			this->ft_set_client("442");
			this->_send_msg = ERR_NOTONCHANNEL(this->_client, msg[1]);
			this->ft_send();
			return;
		}
		if (!this->_user->ft_get_channel(msg[1])->ft_privilege_has_user(this->_user->ft_get_user_name()))
		{
			this->ft_set_client("482");
			this->_send_msg = ERR_CHANOPRIVSNEEDED(this->_client, msg[1]);
			this->ft_send();
			return;
		}
		this->_user->ft_delete_channel(msg[1]);
		this->_send_msg = this->_user->ft_get_info() + " " + this->_cmd + " " + msg[1] + " " + this->_user->ft_get_nick_name() + " :";
		int i = 2;
		while (i < msg.size())
			this->_send_msg += msg[i] + " ";
	}
};

#endif
/*
Request: KICK #testroom testnick2
all
Response: :testnick!~testlogin@freenode-8ft.tgg.6ohrpn.IP KICK #testroom testnick2 :
*/
