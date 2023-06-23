#ifndef PART_HPP
#define PART_HPP

#include "Cmd.hpp"

class Part : public Cmd
{
private:
	/* data */
	Part(const Part &ref){};
	Part &operator=(const Part &ref) { return *this; };

public:
	Part()
	{
		this->_cmd = "PART";
	};
	~Part(){};

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
		this->_send_msg = this->_user->ft_get_info() + " " + this->_cmd + " " + msg[1] + " :\"" + msg[2];

		if (msg.size() > 2)
		{
			int i = 3;
			while (i < msg.size())
				this->_send_msg += " " + msg[i];
		}
		this->_send_msg += "\"";
		std::map<std::string, User *> user_list = this->_server->ft_get_channel(msg[1])->ft_get_user_list();
		for (std::map<std::string, User *>::iterator it = user_list.begin(); it != user_list.end(); it++)
			this->ft_send(it->second->ft_get_fd());
		this->_server->ft_leave_channel(this->_user, msg[1]);
	}
};

#endif

/*
Request: PART #testroom Leaving...
Response: :nick2!~login2@127.0.0.1 PART #test2:"Leaving...Leaving..."
Response: :testnick2!~testlogin@freenode-1b4.su5.hqs74b.IP PART #testroom :"Leaving..."
Response: :testnick2!~testlogin@freenode-1b4.su5.hqs74b.IP PART #testroom :"tstts"
Response: :*.freenode.net 442 testnick2 #testroom :You're not on that channel
*/
