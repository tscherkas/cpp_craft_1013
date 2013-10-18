#ifndef _MESSAGE_H
#define _MESSAGE_H

#include <iostream>
#include <cstring>

class Message {
private :
	unsigned type;
	int time;
	unsigned length;
	char* text;

public :
	Message(){
		text = 0;
	}
	Message(const Message& message);
	~Message();

	void operator=( const Message& );

	void setType(unsigned);
	void setTime(int);
	void setLength(unsigned);
	void setText(char*);

	unsigned getLength() const;
	int getTime() const;

	friend std::ostream& operator<<(std::ostream& binary_os, Message message);
	friend std::istream& operator>>(std::istream& binary_is, Message& message);
};

#endif