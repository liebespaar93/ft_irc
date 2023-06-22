#ifndef INVITE_HPP
#define INVITE_HPP

#include "Cmd.hpp"

class Invite : public Cmd
{
private:
	/* data */
	Invite(const Invite &ref){};

	Invite &operator=(const Invite &ref) { return *this; };

public:
	Invite() { this->_cmd = "INVITE"; };
	~Invite(){};


	void ft_recv(std::vector<std::string> msg)
	{
		if (msg.size() < 3)
		{
			this->ft_set_client("461");
			this->_send_msg = ERR_NEEDMOREPARAMS(this->_client, this->_cmd);
			this->ft_send();
			return;
		}
		if (!this->_server->ft_get_channel(msg[2]))
		{
			this->ft_set_client("403");
			this->_send_msg = ERR_NOSUCHCHANNEL(this->_client, msg[1]);
			this->ft_send();
			return;
		}
		if (!this->_user->ft_get_channel(msg[2]))
		{
			this->ft_set_client("442");
			this->_send_msg = ERR_NOTONCHANNEL(this->_client, msg[1]);
			this->ft_send();
			return;
		}
		if (this->_server->ft_get_nick(msg[1])->ft_get_channel(msg[1]))
		{
			this->ft_set_client("443");
			this->_send_msg = ERR_USERONCHANNEL(this->_client, msg[2], msg[1]);
			this->ft_send();
			return;
		}
		if (!this->_user->ft_get_channel(msg[2])->ft_privilege_has_user(this->_user->ft_get_user_name()))
		{
			this->ft_set_client("482");
			this->_send_msg = ERR_CHANOPRIVSNEEDED(this->_client, msg[1]);
			this->ft_send();
			return;
		}
		this->_send_msg = this->_user->ft_get_info() + " " + this->_cmd + " " + msg[1] + " :" + msg[2];
		this->ft_send(this->_server->ft_get_nick(msg[1])->ft_get_fd());

		this->ft_set_client("341");
		this->_send_msg = RPL_INVITING(this->_client, msg[1], msg[2]);
		this->ft_send();
	}
};

#endif

// irssi로 여러 클라이언트를 돌리면서 /mode로 invtite only 설정을 해도 join이 되어서 테스트하기 굉장히 까다로움
// lime으로 모드 설정과 invtite 테스트 예정
// irssi로 했을시 초대받았다라는 메시지만 받고 채널 입장은 하지 않음

/*
Request: INVITE testnick2 #testroom2
Response: :testnick!~testlogin@freenode-ep7.0qi.hqs74b.IP INVITE testnick2 :#testroom2
Response: :*.freenode.net 442 testnick2 #testroom :You're not on that channel!
Response: :*.freenode.net 443 testnick testnick2 #testroom2 :is already on channel
Response: :*.freenode.net 482 testnick2 #testroom :You must be a channel half-operator
Response: :*.freenode.net 341 testnick testnick2 :#testroom2
Response: :*.freenode.net 341 testnick2 testnick :#testroom2
*/
