#ifndef JOIN_HPP
# define JOIN_HPP

#include "Cmd.hpp"
#include "Utile.hpp"

class Join: public Cmd
{
private:
	/* data */
	Join(const Join& ref) {};

	Join&	operator=(const Join& ref) {return *this;};
public:
	Join() { this->_cmd = "JOIN"; };
	~Join(){};

	void ft_recv(std::vector<std::string> msg)
	{
		Channel *channel_info;
		std::map<std::__1::string, User *> channel_user_list;
		std::vector<std::string> channel;
		std::vector<std::string> password;
		int code;

		if (msg.size() == 1)
		{
			this->_send_msg = ERR_NEEDMOREPARAMS(this->_client,this->_cmd);
			this->ft_send();
			return;
		}
		if (msg.size() > 1)
			channel = split(msg[1], ",");
		if (msg.size() > 2)
			password = split(msg[2], ",");
		int i = 0;
		while (i < channel.size())
		{
			if (password.size() > i)
				code = this->_server->ft_join_channel(this->_user, channel.at(i), password.at(i), this->_symbol);
			else
				code = this->_server->ft_join_channel(this->_user, channel.at(i), this->_symbol);
			if (code == 471)
			{
				this->ft_set_client("471");
				this->_send_msg = ERR_CHANNELISFULL(this->_client, channel.at(i));
				this->ft_send();
			}
			else if (code == 475)
			{
				this->ft_set_client("475");
				this->_send_msg = ERR_BADCHANNELKEY(this->_client, channel.at(i));
				this->ft_send();
			}
			else if (code == 0 )
			{
				channel_info = this->_server->ft_get_channel(channel[i]);
				channel_user_list = channel_info->ft_get_user_list();
				this->_prefix = channel_info->ft_privilege_has_user(this->_user->ft_get_nick_name());
				
				this->_send_msg = this->_user->ft_get_info() + " " + this->_cmd + " :" +  channel[i];
				this->ft_send();
				this->ft_set_client("353");
				this->_prefix = channel_info->ft_privilege_has_user(this->_user->ft_get_nick_name());
				this->_send_msg = RPL_NAMREPLY(this->_client, this->_symbol, channel.at(i), this->_prefix , this->_user->ft_get_nick_name());
				for (std::map<std::__1::string, User *>::iterator it = channel_user_list.begin(); it != channel_user_list.end(); it++ )
				{
					if (this->_user->ft_get_user_name() != it->first)
					{
						this->_prefix = channel_info->ft_privilege_has_user(it->first);
						this->_send_msg += " " + this->_prefix + this->_server->ft_get_user(it->first)->ft_get_nick_name();
					}
				}
				this->ft_send();
				this->ft_set_client("366");
				this->_send_msg = RPL_ENDOFNAMES(this->_client, this->_channel);
				this->ft_send();
				for (std::map<std::__1::string, User *>::iterator it = channel_user_list.begin(); it != channel_user_list.end(); it++ )
				{
					if (this->_user->ft_get_user_name() != it->first)
					{
						this->_send_msg = this->_user->ft_get_info() + " " + this->_cmd + " :" +  channel[i];
						this->ft_send(it->second->ft_get_fd());
					}
				}
			}
			i++;
		}
		
	}
};
// Request: JOIN #channel_name
// Response: :nick_name!~myname@freenode-pig.su5.hqs74b.IP JOIN :#channel_name
// Response: :ft_irc 353 nick = #test :@nick name
// Response: :*.freenode.net 353 nick_name = #channel_name :@nick_name
// Response: :*.freenode.net 366 nick_name #ar :End of /NAMES list.
// Request: MODE #channel_name +sn
// Response: :nick_name!~myname@freenode-pig.su5.hqs74b.IP MODE #channel_name :+s


// 암호 있는방
// Request: JOIN #testroom
// Response: :*.freenode.net 475 testnick2 #testroom :Cannot join channel (incorrect channel key)
#endif
