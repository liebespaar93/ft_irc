#ifndef PART_HPP
#define PART_HPP

#include "Cmd.hpp"

class Part : public Cmd
{
private:
	/* data */
	Part(const Part &ref) { (void)ref; };
	Part &operator=(const Part &ref)
	{
		(void)ref;
		return *this;
	};

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
			size_t i = 3;
			while (i < msg.size())
				this->_send_msg += " " + msg[i];
		}
		this->_send_msg += "\"";
		this->ft_send();
		this->_server->ft_leave_channel(this->_user, msg[1]);
	}
};

#endif
