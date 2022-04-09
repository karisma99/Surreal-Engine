#ifndef _CommandBase
#define _CommandBase

class CommandBase
{
public:
	CommandBase();
	CommandBase(const CommandBase& c) = delete;
	CommandBase& operator = (const CommandBase& t) = delete;
	virtual ~CommandBase();

	virtual void Execute();
private:

};

#endif _CommandBase
