
#ifndef PRIVMSG_HPP
#define PRIVMSG_HPP

#include "Cmd.hpp"
class Privmsg : public Cmd
{
private:
	/* data */
	Privmsg(const Privmsg &ref){};
	Privmsg &operator=(const Privmsg &ref) { return *this; };

public:
	Privmsg() { this->_cmd = "PRIVMSG"; };
	~Privmsg(){};

	void ft_recv(std::vector<std::string> msg)
	{
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
		}
		else
		{
			this->ft_set_client("401");
			this->_send_msg = ERR_NOSUCHNICK(this->_client, msg[1]);
			this->ft_send();
			return;
		}
		if (!this->_user->ft_get_channel(msg[1]))
		{
			this->ft_set_client("404");
			this->_send_msg = ERR_CANNOTSENDTOCHAN(this->_client, msg[1]);
			this->ft_send();
			return;
		}

		this->_send_msg = this->_user->ft_get_info() + " " + this->_cmd + " " + msg[1] + " :" + msg[2];
		int i = 3;
		while (i < msg.size())
		{
			this->_send_msg += " " + msg[i];
			i++;
		}
		std::map<std::string, User *> user_list = this->_server->ft_get_channel(msg[1])->ft_get_user_list();

		for (std::map<std::string, User *>::iterator it = user_list.begin(); it != user_list.end(); it++ )
		{
			if (it->first != this->_user->ft_get_user_name())
				this->ft_send(it->second->ft_get_fd());
		}
	}
};

#endif

/*
Request: PRIVMSG #testroom dd
Response: :testnick2!~testlogin@freenode-8ft.tgg.6ohrpn.IP PRIVMSG #testroom :dd
/401
Response: :*.freenode.net 401 testnick2 test :No such nick

/403
Response: :*.freenode.net 403 testnick2 #testroom22 :No such channel
/404
Response: :*.freenode.net 404 testnick2 #testroom :You cannot send external messages to this channel whilst the +n (noextmsg) mode is set.
*/
