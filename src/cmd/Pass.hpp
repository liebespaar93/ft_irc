#ifndef PASS_HPP
# define PASS_HPP

#include "Cmd.hpp"

class Pass: public Cmd
{
private:
	/* data */
	Pass(const Pass& ref){};
	Pass&	operator=(const Pass& ref){return *this;};

public:
	Pass()
	{
		this->_cmd = "PASS";
	};
	~Pass() {};


	void ft_recv(std::vector<std::string> msg)
	{
		if (msg.size() == 1)
		{
			this->_send_msg = ERR_NEEDMOREPARAMS(this->_client, this->_cmd);
			this->ft_send();
			return ;
		}
		// 이미 통과한 사람이면
		// if (user = pass)
		// {
		// 	ERR_ALREADYREGISTERED
		// }
		// 패스워드 불일치
		// if (password != password)
		// {
		// 	ERR_PASSWDMISMATCH(this->_client)
		// }
	}

};

#endif
