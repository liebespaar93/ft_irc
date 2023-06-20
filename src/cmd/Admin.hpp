#ifndef ADMIN_HPP
# define ADMIN_HPP

#include "Cmd.hpp"

class Admin: public Cmd
{
private:
	/* data */
	Admin(const Admin& ref) {};
	Admin&	operator=(const Admin& ref) { return *this; };

public:
	Admin()
	{
		this->_cmd = "ADMIN";
	};
	~Admin() {};

	void ft_recv(std::vector<std::string> msg)
	{
		if (msg.size() == 1)
		{
			this->_send_msg = ERR_NOSUCHSERVER(this->_client, this->_server_name);
			this->ft_send();
			return ;
		}
		RPL_ADMINME(this->_client, this->_info);
		this->ft_send();
		RPL_ADMINLOC1 (this->_client, this->_info);
		this->ft_send();
		RPL_ADMINLOC2 (this->_client, this->_info);
		this->ft_send();
		RPL_ADMINEMAIL (this->_client, this->_info);
		this->ft_send();
	}
};
//Request: ADMIN 
//Response: :*.freenode.net 256 nick_name *.freenode.net :Administrative info
//Response: :*.freenode.net 257 nick_name :Name: freenode
//Response: :*.freenode.net 258 nick_name :Nickname: Infrastructure Team
//Response: :*.freenode.net 259 nick_name :Email: infrastructure@freenode.net
#endif
