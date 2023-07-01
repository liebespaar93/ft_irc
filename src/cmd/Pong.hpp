#ifndef PONG_HPP
#define PONG_HPP

#include "Cmd.hpp"

class Pong : public Cmd
{
private:
	Pong(const Pong &ref) { (void)ref; };

	Pong &operator=(const Pong &ref)
	{
		(void)ref;
		return *this;
	};

public:
	Pong()
	{
		this->_cmd = "PONG";
	};
	~Pong(){};

	void ft_recv(std::vector<std::string> msg)
	{
		if (msg.size() == 1)
		{
			this->ft_set_client("461");
			this->_send_msg = ERR_NEEDMOREPARAMS(this->_client, this->_cmd);
			this->ft_append_msg();
		}
		this->_socket->ft_pong(msg[1]);
	}
};

#endif
