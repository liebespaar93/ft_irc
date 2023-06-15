#ifndef PONG_HPP
# define PONG_HPP

#include "Cmd.hpp"

class Pong: public Cmd
{
private:
	Pong(const Pong& ref) {};

	Pong&	operator=(const Pong& ref) {return *this;};
	
public:
	Pong()
	{
		this->_cmd = "PONG";
	};
	~Pong() {};

	void ft_recv(std::vector<std::string> msg)
	{
		if (msg.size() == 1)
		{
			this->_send_msg = ERR_NEEDMOREPARAMS(this->_client, this->_cmd);
			this->ft_send();
			this->_send_msg += ERR_NOORIGIN(this->_client);
			this->ft_send();
		}
	}
};

#endif
