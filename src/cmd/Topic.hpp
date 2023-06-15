#ifndef TOPIC_HPP
# define TOPIC_HPP

#include "Cmd.hpp"

class Topic: public Cmd
{
private:
	/* data */

public:
	Topic();
	Topic(const Topic& ref);
	~Topic();

	Topic&	operator=(const Topic& ref);
};

#endif
