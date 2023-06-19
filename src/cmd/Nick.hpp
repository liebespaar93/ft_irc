#ifndef NICK_HPP
#define NICK_HPP

#include "Utile.hpp"
#include "Cmd.hpp"

class Nick : public Cmd
{
private:
	/* data */
	Nick(const Nick &ref){};
	Nick &operator=(const Nick &ref) { return *this; };

public:
	Nick() { this->_cmd = "NICK"; };
	~Nick(){};

	void ft_recv(std::vector<std::string> msg)
	{
		if (!this->_user->ft_get_pass())
			return;
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
		if (!this->_user->ft_get_user_name().size())
		{
			this->_send_msg = ":" + this->_server_name + " NOTICE * :*** Could not resolve your hostname: Domain not found; using your IP address (" + this->_user->ft_get_IP() + ") instead.";
			this->ft_send();
		}
		this->_user->ft_set_nick_name(msg[1]);
		this->_send_msg = ":" + this->_user->ft_get_nick_name() + "!~" + this->_user->ft_get_user_name() + "@" +
						  this->_user->ft_get_IP() + " " + this->_cmd + " " + ":" + msg.at(1);
		this->ft_send();
		this->_server->ft_append_nick_name(msg.at(1), this->_user);
	}
	// 실제 상용시 2번째 파람에 닉으로 변경 같을경우 안함
	// ERR_NONICKNAMEGIVEN (431)
	// ERR_ERRONEUSNICKNAME (432)
	// ERR_NICKNAMEINUSE (433)
	// ERR_NICKCOLLISION (436)
	//.nickname [ [ "!" user ] "@" host ] 성공시 밑에 예시
	// Response: :mynick!~myname@freenode-pig.su5.hqs74b.IP NICK :next_nick
	//Response: :*.freenode.net NOTICE * :*** Could not resolve your hostname: Domain not found; using your IP address (110.70.51.236) instead.
};

#endif
