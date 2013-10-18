#include "Message.h"

Message::Message(const Message &message) {
	this->type = message.type;
	this->time = message.time;
	this->length = message.length;	
	this->text = new char[ message.length + 1 ];
	strcpy(this->text, message.text );
}

Message::~Message() {
	if ( this->text ) {
		delete [] this->text;
	}
}

void Message::operator=( const Message& message) {
	this->time = message.time;
	this->type = message.type;
	if (this->length != message.length && this->text ) {
		delete [] text;
	}
	this->length = message.length;
	text = new char[ message.length + 1 ];
	strcpy( text, message.text );
}

void Message::setTime( int time ) {
	this->time = time;
}

void Message::setType( unsigned type ) {
	this->type = type;
}

void Message::setLength( unsigned length ) {
	this->length = length;
}

void Message::setText( char* text ) {
	strcpy( this->text, text );
}

unsigned Message::getLength() const {
	return this->length;
}

int Message::getTime() const {
	return this->time;	
}

std::istream& operator>>( std::istream& binary_is, Message& message ) {
	binary_is.read( reinterpret_cast< char* > ( &message.type ), sizeof( unsigned ) );
	binary_is.read( reinterpret_cast< char* > ( &message.time ), sizeof( int ) );
	binary_is.read( reinterpret_cast< char* > ( &message.length ), sizeof( unsigned ) );
	message.text = new char[ message.length + 1 ];
	binary_is.read( message.text, message.length );
	message.text[ message.length ] = 0;

	return binary_is;
}

std::ostream& operator<<( std::ostream& binary_os, Message message ) {
	binary_os.write( reinterpret_cast< const char* > ( &message.type ), sizeof( unsigned ) );
	binary_os.write( reinterpret_cast< const char* > ( &message.time ), sizeof( int ) );
	binary_os.write( reinterpret_cast< const char* > ( &message.length ), sizeof( unsigned ) );
	binary_os.write( message.text, message.length );

	return binary_os;
}