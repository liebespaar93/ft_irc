#ifndef NICK_HPP
#define NICK_HPP

#include "Utile.hpp"
#include "Cmd.hpp"

class Nick : public Cmd
{
private:
	/* data */
	Nick(const Nick &ref) { (void)ref; };
	Nick &operator=(const Nick &ref)
	{
		(void)ref;
		return *this;
	};

public:
	Nick() { this->_cmd = "NICK"; };
	~Nick(){};

	void ft_recv(std::vector<std::string> msg)
	{
		if (msg.size() != 2)
		{
			this->ft_set_client("431");
			this->_send_msg = ERR_NONICKNAMEGIVEN(this->_client);
			this->ft_send();
			return;
		}
		if (!checkAlpha(msg.at(1)))
		{
			this->ft_set_client("432");
			this->_send_msg = ERR_ERRONEUSNICKNAME(this->_client, this->_user->ft_get_nick_name() + msg.at(1));
			this->ft_send();
			return;
		}
		if (this->_server->ft_get_nick(msg.at(1)))
		{
			this->ft_set_client("433");
			this->_send_msg = ERR_NICKNAMEINUSE(this->_client, this->_user->ft_get_nick_name() + msg.at(1));
			this->ft_send();
			return;
		}
		if (this->_user->ft_get_user_name() == "")
		{
			send(this->_user->ft_get_fd(), ":ft_irc NOTICE * :*** Looking up your ident...;", 48, 0);
			send(this->_user->ft_get_fd(), ":ft_irc NOTICE * :*** Looking up your hostname...;", 51, 0);
		}
		else
		{
			this->_send_msg = this->_user->ft_get_info() + " " + this->_cmd + " " + ":" + msg.at(1);
			this->ft_send();
			this->_server->ft_send_all_in_channels(this->_user, this->_send_msg);
		}
		this->_server->ft_append_nick_name(msg.at(1), this->_user);
		if (this->_user->ft_get_user_name() == "")
		{
			this->_send_msg = ":" + this->_server_name + " NOTICE * :*** Could not resolve your hostname: Domain not found; using your IP address (" + this->_user->ft_get_IP() + ") instead.";
			this->ft_send();
			return;
		}
		this->_user->ft_set_login();
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
