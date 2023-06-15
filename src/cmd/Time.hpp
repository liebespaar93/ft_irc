#ifndef TIME_HPP
# define TIME_HPP

#include "Cmd.hpp"

class Time: public Cmd
{
private:
	/* data */
	Time(const Time& ref) {};
	Time&	operator=(const Time& ref) { return *this;};


public:
	Time()
	{
		this->_cmd = "Time";
	};
	~Time(){};


	void ft_recv(std::vector<std::string> msg)
	{
		if (msg.size() > 1)
		{
			this->_send_msg = ERR_NOSUCHSERVER(this->_client, this->_server_name);
			this->ft_send();
			return ;
		}

		/* 
			need new 
		*/
		// RPL_TIME();
		// this->ft_send();
	}

};

#endif
