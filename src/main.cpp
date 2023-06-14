#include <limits>

#include "Server.hpp"
#include "Logger.hpp"

int main(int argc, char const *argv[])
{
	Server *server = NULL;
	std::string port_str, password_str;

	if (argc != 3)
	{
		Logger("argc != 3 \n[TIP] ./server [port] [password]").ft_error();
		return (1);
	}
	port_str = argv[1];
	password_str = argv[2];
	if (port_str.find_first_not_of("0123456789") != std::string::npos || std::atoll(port_str.c_str()) > 65535)
	{
		Logger("port is not digit").ft_error();
		return (2);
	}

	try
	{
		server = new Server(port_str, password_str);
		server->ft_server_on();
		delete server;
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}
	system("leaks server");
	return 0;
}
