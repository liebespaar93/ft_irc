#ifndef CMDUSER_HPP
#define CMDUSER_HPP

#include "Cmd.hpp"
#include <cstdlib>
#include "Utile.hpp"

class CmdUser : public Cmd
{
private:
	/* data */
	CmdUser(const CmdUser &ref){};
	CmdUser &operator=(const CmdUser &ref) { return *this; };

public:
	CmdUser() { this->_cmd = "USER"; };
	~CmdUser(){};

	void ft_recv(std::vector<std::string> msg)
	{
		std::string user_name = "";
		std::string real_name = "";
		if (!this->_user->ft_get_pass())
		{
			this->ft_set_client("462");
			this->_send_msg = ERR_ALREADYREGISTERED(this->_client);
			this->ft_send();
			return;
		}
		if (msg.size() <= 4)
		{
			this->ft_set_client("461");
			this->_send_msg = ERR_NEEDMOREPARAMS(this->_client, this->_cmd);
			this->ft_send();
			return ;
		}
		user_name = msg[1];
		if (this->_server->ft_get_user(user_name))
		{
			int i = 0;
			user_name = user_name + "_";
			while (this->_server->ft_get_user(user_name + ft_itostring(i)))
				i++;
			user_name = user_name + ft_itostring(i);
		}
		int i = 3;
		while (i < msg.size())
		{
			real_name += msg[i++];
		}
		std::cout << "user_name : " << user_name << std::endl;
		this->_server->ft_append_user_name(user_name, this->_user);
		if (this->_user->ft_get_nick_name() != "" && !this->_user->ft_get_login())
		{
			this->ft_set_client("001");
			this->_send_msg = RPL_WELCOME(this->_client, this->_server_name, this->_user->ft_get_nick_name(), this->_user->ft_get_user_name(), this->_user->ft_get_IP());
			this->ft_send();
			this->ft_set_client("002");
			this->_send_msg = RPL_YOURHOST(this->_client, this->_server_name, "v.1");
			this->ft_send();
			this->ft_set_client("003");
			this->_send_msg = RPL_CREATED(this->_client, (std::string)(this->_timestr));
			this->ft_send();
			this->_user->ft_set_login();
		}

		this->_user->ft_set_real_name(real_name);
	}
};

#endif
// USER guest 0 * :Ronnie Reagan
// Response: :*.freenode.net NOTICE gyeongjukim :*** Could not resolve your hostname: Domain not found; using your IP address (120.50.73.143) instead.
// Response: :*.freenode.net NOTICE gyeongju_ :*** Ident lookup timed out, using ~gyeongjuk instead.
// Response: :*.freenode.net 001 mynick :Welcome to the freenode IRC Network mynick!~myname@110.70.51.236
// Response: :*.freenode.net 002 mynick :Your host is *.freenode.net, running version InspIRCd-3
// Response: :*.freenode.net 003 mynick :This server was created 23:06:04 Apr 20 2022

// Response: :*.freenode.net 004 mynick *.freenode.net InspIRCd-3 BDHILRSTWcdghikorswxz ABCDEFIJKLMNOPQRSTUWXYZbcdefhijklmnoprstuvwz :BEFIJLWXYZbdefhjklovw
// Response: :*.freenode.net 005 mynick NICKLEN=30 PREFIX=(Yohv)!@%+ REMOVE SAFELIST SECURELIST=60 SILENCE=32 STATUSMSG=!@%+ TOPICLEN=390 UHNAMES USERIP USERLEN=10 USERMODES=,,s,BDHILRSTWcdghikorwxz VBANLIST :are supported by this server
// Response: :gyeongjukim!~gyeongjuk@freenode-n68.49c.2i380a.IP MODE gyeongjukim :+wRix
