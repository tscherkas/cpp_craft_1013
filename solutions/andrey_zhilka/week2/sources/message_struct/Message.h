#ifndef _MESSAGE_H
#define _MESSAGE_H

#include <iostream>
#include <cstring>

class Message {
private :
	unsigned type;
	unsigned time;
	unsigned length;
	char* text;

	void operator=( const Message& ){};
	Message(const Message& message);

public :
	Message(){
		text = 0;
	}
	~Message();

	void setType(unsigned);
	void setTime(unsigned);
	void setLength(unsigned);
	void setText(char*);

	unsigned getLength() const;
	unsigned getTime() const;
	unsigned getType() const;

	friend std::ostream& operator<<(std::ostream& binary_os, const Message& message);
	friend std::istream& operator>>(std::istream& binary_is, Message& message);
};

#endif