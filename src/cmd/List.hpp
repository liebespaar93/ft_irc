#ifndef LIST_HPP
#define LIST_HPP

#include "Cmd.hpp"
#include "Utile.hpp"

class List : public Cmd
{
private:
	/* data */
	List(const List &ref) { (void)ref; };
	List &operator=(const List &ref)
	{
		(void)ref;
		return *this;
	};

public:
	List() { this->_cmd = "LIST"; };
	~List(){};
	void ft_recv(std::vector<std::string> msg)
	{
		(void)msg;
		this->ft_set_client("321");
		this->_send_msg = RPL_LISTSTART(this->_client);
		this->ft_send();
		this->ft_set_client("322");
		for (std::map<const std::string, Channel *>::iterator it = this->_server->ft_get_channel_map()->begin(); it != this->_server->ft_get_channel_map()->end(); it++)
		{
			this->_send_msg = RPL_LIST(this->_client, it->first, ft_itostring(it->second->ft_get_user_list().size()), ": [not ready]");
			this->ft_send();
		}
		this->ft_set_client("323");
		this->_send_msg = RPL_LISTEND(this->_client);
		this->ft_send();
	}
};

#endif
