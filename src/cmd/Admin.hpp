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
		/* 
			need new 
		*/
		// RPL_ADMINME();
		// this->ft_send();
		// RPL_ADMINLOC1 ();
		// this->ft_send();
		// RPL_ADMINLOC2 ();
		// this->ft_send();
		// RPL_ADMINEMAIL ();
		// this->ft_send();
	}

};

#endif
