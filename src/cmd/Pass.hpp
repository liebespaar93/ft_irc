#ifndef PASS_HPP
#define PASS_HPP

#include "Cmd.hpp"

class Pass : public Cmd
{
private:
	/* data */
	Pass(const Pass &ref) { (void)ref; };
	Pass &operator=(const Pass &ref)
	{
		(void)ref;
		return *this;
	};

public:
	Pass()
	{
		this->_cmd = "PASS";
	};
	~Pass(){};

	void ft_recv(std::vector<std::string> msg)
	{
		std::string password = this->_server->ft_get_password();
		if (this->_user->ft_get_pass())
			return;
		if (msg.size() == 1)
		{
			this->ft_set_client("461");
			this->_send_msg = ERR_NEEDMOREPARAMS(this->_client, this->_cmd);
			this->ft_append_msg();
			return;
		}
		if (this->_user->ft_get_pass())
		{
			this->ft_set_client("462");
			this->_send_msg = ERR_ALREADYREGISTERED(this->_client);
			this->ft_append_msg();
			return;
		}
		if (this->_server->ft_get_password().compare(msg[1]))
		{
			this->ft_set_client("464");
			this->_send_msg = ERR_PASSWDMISMATCH(this->_client);
			this->ft_append_msg();
			return;
		}
		this->_user->ft_set_pass();
		if (this->_user->ft_get_login() && this->_user->ft_get_pass() && !this->_user->ft_get_wellcome())
		{
			this->ft_set_client("001");
			this->_send_msg = RPL_WELCOME(this->_client, this->_server_name, this->_user->ft_get_nick_name(), this->_user->ft_get_user_name(), this->_user->ft_get_IP());
			this->ft_append_msg();
			this->ft_set_client("002");
			this->_send_msg = RPL_YOURHOST(this->_client, this->_server_name, "v.1");
			this->ft_append_msg();
			this->ft_set_client("003");
			this->_send_msg = RPL_CREATED(this->_client, (std::string)(this->_timestr));
			this->ft_append_msg();
			this->_user->ft_set_wellcome();
		}
		this->_send_msg = "PING :logintest";
		this->ft_append_msg();
	}
};

#endif
