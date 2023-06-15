#ifndef MODE_HPP
#define MODE_HPP

#include "Cmd.hpp"

class Mode : public Cmd
{
private:
	/* data */
	Mode(const Mode &ref) {};
	Mode &operator=(const Mode &ref) {return *this; };

public:
	Mode()
	{
		this->_cmd = "MODE";
	};
	~Mode() {};
	////// 나중에
};

#endif
