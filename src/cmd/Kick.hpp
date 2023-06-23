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
		if (!this->_user->ft_get_login())
			return;
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
		std::cout << "error passed all" << std::endl;
		this->_send_msg = ":" + this->_user->ft_get_info() + " " + this->_cmd + " " + msg[1] + " ";
		int i = 2;
		while (i < msg.size())
			this->_send_msg += msg[i++] + " ";
		std::cout << "after while loop" << std::endl;
		this->_send_msg += ":" + this->_user->ft_get_nick_name();
		std::map<std::string, User *> user_list = this->_server->ft_get_channel(msg[1])->ft_get_user_list();
		std::cout << "before for loop" << std::endl;
		for (std::map<std::string, User *>::iterator it = user_list.begin(); it != user_list.end(); it++)
		{
			this->ft_send(it->second->ft_get_fd());
		}
		std::cout << "after for loop" << std::endl;
		this->_user->ft_get_channel(msg[1])->ft_invite_append_user(this->_server->ft_get_nick(msg[i++]));
		i = 2;
		std::cout << "before the last loop" << std::endl;
		while (i < msg.size())
			this->_user->ft_get_channel(msg[1])->ft_channel_leave_user(this->_server->ft_get_nick(msg[i++]));
	}
};

#endif
/*
Request: KICK #testroom testnick2
all
Response: :testnick!~testlogin@freenode-o1j.f5h.tct02s.IP KICK #testroom testnick2 :testnick;
Response: :testnick!~testlogin@freenode-8ft.tgg.6ohrpn.IP KICK #testroom testnick2 :
*/
