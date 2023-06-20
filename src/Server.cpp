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
	while (this->_on && this->_socket.size() < 3)
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
		if (revents & POLLERR) 
			Logger("POLLERR").ft_error();
		else if ((revents & POLLRDNORM))
			this->ft_pollin(socket_front);
		else
		{
			this->_socket.pop();
			this->_socket.push(socket_front);
		}
	}
}


void Server::ft_pollin(Socket *socket_front)
{
	int fd;
	char buf[512];
	ssize_t len;
	int socket_send_loop;

	fd = socket_front->ft_get_socket_fd(); /// 버퍼보다 큰  값이 올경우
	len = recv(fd, &buf, 511, 0);

	if (len < 0)
		throw Error("recv() failed");
	if (len == 0)
	{
		/* \r 테스트 궁금점 */
		this->_socket.pop();
		Logger("connect close").ft_socket_close(fd);
		delete socket_front;
		return;
	}
	buf[len] = '\0';
	std::vector<std::__1::string> gnl = split(buf, "\r\n");
	for (int i = 0; i < gnl.size(); i++)
	{
		this->ft_parse(gnl[i], fd);
		Logger("gnl[i]").ft_recv_msg(fd);
	}
	gnl.clear();
}

void Server::ft_set_cmd_map()
{
	this->_cmd_map.insert(std::pair<std::string, Cmd *>("JOIN" , new Join()));
	this->_cmd_map.insert(std::pair<std::string, Cmd *>("PASS" , new Pass()));
	this->_cmd_map.insert(std::pair<std::string, Cmd *>("NICK" , new Nick()));
	this->_cmd_map.insert(std::pair<std::string, Cmd *>("USER" , new CmdUser()));
	this->_cmd_map.insert(std::pair<std::string, Cmd *>("PING" , new Ping()));
	this->_cmd_map.insert(std::pair<std::string, Cmd *>("PONG" , new Pong()));
	this->_cmd_map.insert(std::pair<std::string, Cmd *>("PRIVMSG" , new Privmsg()));
	this->_cmd_map.insert(std::pair<std::string, Cmd *>("PART" , new Part()));
	
	// this->_cmd_map.insert(std::pair<std::string, Cmd *>("CAP" , new Cap()));
	// this->_cmd_map.insert(std::pair<std::string, Cmd *>("AUTHENTICATE" , new Authenticate()));
	// this->_cmd_map.insert(std::pair<std::string, Cmd *>("OPER" , new Oper()));
	// this->_cmd_map.insert(std::pair<std::string, Cmd *>("QUIT" , new Quit()));
	// this->_cmd_map.insert(std::pair<std::string, Cmd *>("TOPIC" , new Topic()));
	// this->_cmd_map.insert(std::pair<std::string, Cmd *>("LIST" , new List()));
	// this->_cmd_map.insert(std::pair<std::string, Cmd *>("INVITE" , new Invite()));
	// this->_cmd_map.insert(std::pair<std::string, Cmd *>("KICK" , new Kick()));
	// this->_cmd_map.insert(std::pair<std::string, Cmd *>("MOTD" , new Motd()));
	// this->_cmd_map.insert(std::pair<std::string, Cmd *>("ADMIN" , new Admin()));
	// this->_cmd_map.insert(std::pair<std::string, Cmd *>("CONNECT" , new Connect()));
	// this->_cmd_map.insert(std::pair<std::string, Cmd *>("LUSERS" , new Lusers()));
	// this->_cmd_map.insert(std::pair<std::string, Cmd *>("VERSION" , new Version()));
	// this->_cmd_map.insert(std::pair<std::string, Cmd *>("TIME" , new Time()));
	// this->_cmd_map.insert(std::pair<std::string, Cmd *>("STATS" , new Stats()));
	// this->_cmd_map.insert(std::pair<std::string, Cmd *>("HELP" , new Help()));
	// this->_cmd_map.insert(std::pair<std::string, Cmd *>("INFO" , new Info()));
	// this->_cmd_map.insert(std::pair<std::string, Cmd *>("MODE" , new Mode()));
	// this->_cmd_map.insert(std::pair<std::string, Cmd *>("NOTICE" , new Notice()));
	// this->_cmd_map.insert(std::pair<std::string, Cmd *>("WHO" , new Who()));
	// this->_cmd_map.insert(std::pair<std::string, Cmd *>("WHOIS" , new Whois()));
	// this->_cmd_map.insert(std::pair<std::string, Cmd *>("KILL" , new Kill()));
	// this->_cmd_map.insert(std::pair<std::string, Cmd *>("REHASH" , new Rehash()));
	// this->_cmd_map.insert(std::pair<std::string, Cmd *>("RESTART" , new Restart()));
	// this->_cmd_map.insert(std::pair<std::string, Cmd *>("SQUIT" , new Squit()));
	// this->_cmd_map.insert(std::pair<std::string, Cmd *>("AWAY" , new Away()));
	// this->_cmd_map.insert(std::pair<std::string, Cmd *>("LINKS" , new Links()));
	// this->_cmd_map.insert(std::pair<std::string, Cmd *>("USERHOST" , new Userhost()));
	// this->_cmd_map.insert(std::pair<std::string, Cmd *>("WALLOPS" , new Wallops()));
}
void Server::ft_parse(std::string buf, int fd)
{
	std::vector<std::string> msg = split(buf, " ");

	if (this->_cmd_map.find(msg.at(0)) != this->_cmd_map.end())
	{
		Cmd* cmd = this->_cmd_map.at(msg.at(0));
		cmd->ft_set_server(this);
		cmd->ft_set_user(this->ft_get_user(fd));
		cmd->ft_set_server_name("ft_irc");
		cmd->ft_set_time();
		cmd->ft_recv(msg);
	}
}


void Server::ft_server_input()
{
	std::string buf;
	struct pollfd pfd = {.fd = 0, .events = POLLIN};
	int ret_poll;
	int size = this->_socket.size();
	Socket * front = NULL;

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
