#ifndef QUIT_HPP
# define QUIT_HPP

#include "Cmd.hpp"

class Quit: public Cmd
{
private:
	/* data */
	Quit(const Quit& ref) {};
	Quit&	operator=(const Quit& ref) { return *this;};

public:
	Quit() { this->_cmd = "QUIT";};
	~Quit() {};

	void ft_recv(std::vector<std::string> msg)
	{
		if (msg.size() == 1)
		{
			this->ft_set_client("461");
			this->_send_msg = ERR_NEEDMOREPARAMS(this->_client, this->_cmd);
			this->ft_send();
			return;
		}
		this->_send_msg = "ERROR :Closing link: (!" + this->_user->ft_get_user_name() + "@" + this->_user->ft_get_IP() + ")[Quit: "; 
		if (msg.size() > 2)
		{
			int i = 3;
			this->_send_msg += msg[2];
			while (i < msg.size())
				this->_send_msg += " " + msg[i];
		}
		else
			this->_send_msg += "Leaving...";
		this->_send_msg += "]";
		this->ft_send();

	}
};

#endif


// Request: QUIT Leaving...
// Response: ERROR :Closing link: (~login@175.223.44.157) [Quit: Leaving...]
// Response: ERROR :Closing link: (~testlogin@175.223.38.114) [Quit: test]
