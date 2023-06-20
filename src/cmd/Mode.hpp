#ifndef MODE_HPP
#define MODE_HPP

#include "Cmd.hpp"

class Mode : public Cmd
{
private:
	/* data */
	Mode(const Mode &ref){};
	Mode &operator=(const Mode &ref) { return *this; };

public:
	Mode()
	{
		this->_cmd = "MODE";
	};
	~Mode(){};
	////// 나중에
	// irssi로 여러 클라이언트로 테스트 했는데 mode 명령어가 프로젝트대로 안먹힘 나중에 lime으로 두 클라이언트로 테스트 예정
	void ft_recv(std::vector<std::string> msg)
	{
		if (msg.size() == 1 || msg.size() > 3)
		{
			this->_send_msg = ERR_UMODEUNKNOWNFLAG(this->_client);
			this->ft_send();
			return;
		}
		std::string option;
		std::string argument;
		if (msg.size() == 2 && (msg.at(1) == "-i" || msg.at(1) == "-t"))
			option = msg.at(1);
		else if (msg.size() == 3)
			argument = msg.at(2);
		if (option == "-i")
		{
			// channel invite_only flag on
		}
		else if (option == "-t")
		{
			// channel topic restriction flag on
		}
		else if (option == "-k")
		{
			// it needs argument
		}
		else if (option == "-o")
		{
		}
		else if (option == "-l")
		{
		}
		else
		{
		}
		// ERR_INVALIDKEY
		// ERR_CHANOPRIVSNEEDED : you're not channel operator
		// ERR_NOSUCHCHANNEL : no such channel 403
	}
};

#endif
