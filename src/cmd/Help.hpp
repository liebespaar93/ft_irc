#ifndef HELP_HPP
# define HELP_HPP

#include "Cmd.hpp"

class Help: public Cmd
{
private:
	/* data */
	Help(const Help& ref) {};
	Help&	operator=(const Help& ref) { return *this; };

public:
	Help()
	{
		this->_cmd = "HELP";
	};
	
	~Help() {};

	void ft_recv(std::vector<std::string> msg)
	{
		/* new need   txt 를 읽어와 출력 혹은 집접 출력*/
		//RPL_HELPSTART()
		//RPL_HELPTXT()
		//RPL_ENDOFHELP()
	}
};

#endif
