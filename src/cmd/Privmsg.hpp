
#ifndef PRIVMSG_HPP
#define PRIVMSG_HPP

#include "Cmd.hpp"
class Privmsg : public Cmd
{
private:
	/* data */
	Privmsg(const Privmsg &ref) { (void)ref; };
	Privmsg &operator=(const Privmsg &ref)
	{
		(void)ref;
		return *this;
	};

public:
	Privmsg() { this->_cmd = "PRIVMSG"; };
	~Privmsg(){};

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
		if (msg[1].at(0) == '#')
		{
			if (!this->_server->ft_get_channel(msg[1]))
			{
				this->ft_set_client("403");
				this->_send_msg = ERR_NOSUCHCHANNEL(this->_client, msg[1]);
				this->ft_send();
				return;
			}
			if (!this->_user->ft_get_channel(msg[1]) && !this->_server->ft_get_nick(msg[1]))
			{
				this->ft_set_client("404");
				this->_send_msg = ERR_CANNOTSENDTOCHAN(this->_client, msg[1]);
				this->ft_send();
				return;
			}
			this->_send_msg = this->_user->ft_get_info() + " " + this->_cmd + " " + msg[1] + " :" + msg[2];
			size_t i = 3;
			while (i < msg.size())
			{
				this->_send_msg += " " + msg[i];
				i++;
			}
			std::map<std::string, User *> user_list = this->_server->ft_get_channel(msg[1])->ft_get_user_list();

			for (std::map<std::string, User *>::iterator it = user_list.begin(); it != user_list.end(); it++)
			{
				if (it->first != this->_user->ft_get_user_name())
					this->ft_send(it->second->ft_get_fd());
			}
			return;
		}
		else if (!this->_server->ft_get_nick(msg[1]))
		{
			this->ft_set_client("401");
			this->_send_msg = ERR_NOSUCHNICK(this->_client, msg[1]);
			this->ft_send();
			return;
		}
		this->_send_msg = this->_user->ft_get_info() + " " + this->_cmd + " " + msg[1] + " :" + msg[2];
		size_t i = 3;
		while (i < msg.size())
		{
			this->_send_msg += " " + msg[i];
			i++;
		}
		this->ft_send(this->_server->ft_get_nick(msg[1])->ft_get_fd());
	}
};

#endif
