#include <vector>

#include "Server.hpp"
#include "Logger.hpp"
#include "Error.hpp"
#include "Utile.hpp"

#include "Cmds.hpp"

Server::Server(std::string port, std::string password)
	: UserControl(), _password(password), _on(1)
{
	this->_server = new Socket("0.0.0.0", port.c_str());
	this->ft_set_cmd_map();
	Logger("Server Craete").ft_create();
}

Server::~Server()
{
	Socket *socket_del;

	while (!this->_socket.empty())
	{
		socket_del = this->_socket.front();
		this->_socket.pop();
		delete socket_del;
	}
	delete this->_server;
}

void Server::ft_server_on()
{
	Socket *accept_socket;
	while (this->_on)
	{
		accept_socket = this->_server->ft_accept();
		if (accept_socket)
			this->ft_connect_socket(accept_socket);
		this->ft_server_check_socket_fd();
		ft_server_input();
	}
}

void Server::ft_connect_socket(Socket *accept_socket)
{
	this->_socket.push(accept_socket);
	User *new_user = new User(accept_socket->ft_get_socket_fd());
	new_user->ft_set_IP(accept_socket->ft_get_socket_IP());
	this->ft_append_user(new_user);
}

void Server::ft_server_check_socket_fd()
{
	int revents;
	int socket_size;
	Socket *socket_front;

	socket_size = this->_socket.size();

	while (socket_size--)
	{
		socket_front = this->_socket.front();
		revents = socket_front->ft_poll();
		if (revents & (POLLERR | POLLHUP | POLLNVAL))
		{
			Logger("POLLERR").ft_error();
			this->ft_user_destory(this->ft_get_user(socket_front->ft_get_socket_fd()));
			this->_socket.pop();
			delete socket_front;
		}
		else if ((revents & POLLRDNORM))
		{
			this->ft_pollin(socket_front);
		}
		else
		{
			if (socket_front->ft_ping())
			{
				this->ft_user_destory(this->ft_get_user(socket_front->ft_get_socket_fd()));
				this->_socket.pop();
				delete socket_front;
			}
			else
			{
				this->_socket.pop();
				this->_socket.push(socket_front);
			}
		}
	}
}

void Server::ft_pollin(Socket *socket_front)
{
	int fd;
	char buf[512];
	std::string msg;
	ssize_t len;
	int socket_send_loop;

	fd = socket_front->ft_get_socket_fd();
	len = recv(fd, &buf, 511, 0);
	socket_front->ft_set_time();
	if (len < 0)
		throw Error("recv() failed");
	if (len == 0)
	{
		this->_socket.pop();
		this->ft_delete_user(this->ft_get_user(socket_front->ft_get_socket_fd()));
		Logger("connect close").ft_socket_close(fd);
		delete socket_front;
		return;
	}
	buf[len] = '\0';
	msg = socket_front->ft_push_msg(buf);
	if (msg.find_first_of("\n") != std::string::npos)
	{
		socket_front->ft_set_msg(msg.substr(msg.find_first_of("\n") + 1));
		std::vector<std::__1::string> gnl = split(msg.c_str(), "\r\n");
		for (int i = 0; i < gnl.size(); i++)
		{
			this->ft_parse(gnl[i], socket_front);
			Logger(gnl[i]).ft_recv_msg(fd);
		}
		gnl.clear();
	}
}

void Server::ft_set_cmd_map()
{
	this->_cmd_map.insert(std::pair<std::string, Cmd *>("JOIN", new Join()));
	this->_cmd_map.insert(std::pair<std::string, Cmd *>("PASS", new Pass()));
	this->_cmd_map.insert(std::pair<std::string, Cmd *>("NICK", new Nick()));
	this->_cmd_map.insert(std::pair<std::string, Cmd *>("USER", new CmdUser()));
	this->_cmd_map.insert(std::pair<std::string, Cmd *>("PING", new Ping()));
	this->_cmd_map.insert(std::pair<std::string, Cmd *>("PONG", new Pong()));
	this->_cmd_map.insert(std::pair<std::string, Cmd *>("PRIVMSG", new Privmsg()));
	this->_cmd_map.insert(std::pair<std::string, Cmd *>("PART", new Part()));
	this->_cmd_map.insert(std::pair<std::string, Cmd *>("QUIT", new Quit()));
	this->_cmd_map.insert(std::pair<std::string, Cmd *>("KICK", new Kick()));
	this->_cmd_map.insert(std::pair<std::string, Cmd *>("INVITE", new Invite()));
	this->_cmd_map.insert(std::pair<std::string, Cmd *>("MODE", new Mode()));
	this->_cmd_map.insert(std::pair<std::string, Cmd *>("TOPIC", new Topic()));
	this->_cmd_map.insert(std::pair<std::string, Cmd *>("HELP", new Help()));
	this->_cmd_map.insert(std::pair<std::string, Cmd *>("LIST" , new List()));
}
void Server::ft_parse(std::string buf, Socket *socket_front)
{
	std::vector<std::string> msg = split(buf, " ");

	if (this->_cmd_map.find(msg.at(0)) != this->_cmd_map.end())
	{
		Cmd *cmd = this->_cmd_map.at(msg.at(0));
		cmd->ft_set_server(this);
		cmd->ft_set_user(this->ft_get_user(socket_front->ft_get_socket_fd()));
		cmd->ft_set_server_name("ft_irc");
		cmd->ft_set_time();
		cmd->ft_set_socket(socket_front);
		cmd->ft_recv(msg);
	}
}

void Server::ft_user_destory(User *user)
{
	std::map<std::string, Channel *> channnel_list = user->ft_get_channel_list();
	for (std::map<std::string, Channel *>::iterator it = channnel_list.begin(); it != channnel_list.end(); it++)
		this->ft_leave_channel(user, it->first);
	this->ft_delete_user(user);
}

void Server::ft_server_input()
{
	std::string buf;
	struct pollfd pfd = {.fd = 0, .events = POLLIN};
	int ret_poll;
	int size = this->_socket.size();
	Socket *front = NULL;

	ret_poll = poll(&pfd, 1, 0);
	if (ret_poll > 0)
	{
		std::getline(std::cin, buf);
		buf.append("\r\n");
		while (size--)
		{
			front = this->_socket.front();
			send(front->ft_get_socket_fd(), buf.c_str(), buf.size(), 0);
			Logger("server send").ft_server_msg(front->ft_get_socket_fd());
			this->_socket.pop();
			this->_socket.push(front);
		}
	}
}
