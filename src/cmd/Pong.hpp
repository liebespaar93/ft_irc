#ifndef PONG_HPP
#define PONG_HPP

#include "Cmd.hpp"

class Pong : public Cmd
{
private:
	Pong(const Pong &ref){};

	Pong &operator=(const Pong &ref) { return *this; };

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
			this->ft_send();
		}
		send(this->_user->ft_get_fd(), "", 0, 0);
	}
};

#endif

// Response: :*.freenode.net 461 mynick PONG :Not enough parameters.
