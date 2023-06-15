#ifndef PING_HPP
# define PING_HPP

#include "Cmd.hpp"

class Ping: public Cmd
{
private:
	/* data */
	Ping(const Ping& ref) {};
	Ping&	operator=(const Ping& ref) { return *this; };

public:
	Ping()
	{
		this->_cmd = "PING";
	};
	~Ping() {};

	void ft_recv(std::vector<std::string> msg)
	{
		if (msg.size() == 1)
		{
			this->_send_msg = ERR_NEEDMOREPARAMS(this->_client, this->_cmd);
			this->ft_send();
			this->_send_msg += ERR_NOORIGIN(this->_client);
			this->ft_send();
		}
		else
		{
			this->_send_msg = this->_server_name + "PONG" + this->_server_name + msg[1];
			this->ft_send();
		}
	}
};

#endif