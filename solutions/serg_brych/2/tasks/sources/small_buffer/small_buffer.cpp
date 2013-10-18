#include <iostream> 
#include <fstream> 
#include <algorithm>
#include <stdint.h>
#include <map>

static const int MaxBufferSize = 2048;
static const int MaxPackageType = 100000;

struct Package
{
	uint32_t type;
	uint32_t time;
	uint32_t len;
};

struct Buffer
{
	uint32_t free_size;
	uint32_t count_of_stored_msg;
	Buffer():free_size(MaxBufferSize),count_of_stored_msg(0){}
};


// type std::pair<count_of_seconds, saved_messages>
typedef std::map<uint32_t, std::pair<uint32_t, uint32_t> >  CountOfSavedMessage;
// type std::pair<free_memory, saved_messages>
typedef std::map<uint32_t, Buffer >  CountOfSavedMessageTimed;

int main() 
{ 
	Package current_package ={0};
	uint32_t current_time = 0;
	
	CountOfSavedMessage all_saved_message;
	CountOfSavedMessageTimed msg_of_time;

	std::ifstream input_file(BINARY_DIR"input.txt", std::ifstream::binary);
	std::ofstream output_file(BINARY_DIR"output.txt", std::ifstream::binary);
	
	if(input_file.is_open() && output_file.is_open())
	{
		while(input_file.read(reinterpret_cast<char*>(&current_package), sizeof(Package)))
		{
			if(current_package.type <= MaxPackageType)
			{
				if(current_time != current_package.time)
				{
					current_time = current_package.time;

					std::for_each(msg_of_time.begin(), msg_of_time.end(), [&all_saved_message](CountOfSavedMessageTimed::value_type & i)
					{
						all_saved_message[i.first].first++;
						all_saved_message[i.first].second += (i.second.count_of_stored_msg);
					});

					msg_of_time.clear();
				}
				
				if((msg_of_time[current_package.type].free_size - sizeof(Package) + current_package.len) > 0)
				{
					msg_of_time[current_package.type].free_size -= sizeof(Package) + current_package.len;
					msg_of_time[current_package.type].count_of_stored_msg += 1;
				}
			}
			if(current_package.len > 0)
			{
				std::streampos pos = input_file.tellg();
				input_file.seekg(pos + static_cast<std::streamoff>(current_package.len));	
			}
		}
		
		std::for_each(msg_of_time.begin(), msg_of_time.end(), [&all_saved_message](CountOfSavedMessageTimed::value_type & i)
		{
			all_saved_message[i.first].first++;
			all_saved_message[i.first].second += (i.second.count_of_stored_msg);
		});
		
		std::for_each(all_saved_message.begin(), all_saved_message.end(), [&output_file] (CountOfSavedMessage::value_type & i)
		{
			output_file.write(reinterpret_cast<const char*>(&(i.first)), sizeof(i.first));
			uint32_t result = i.second.second / i.second.first;
			output_file.write(reinterpret_cast<const char*>(&result), sizeof(result));
		});


	}
	
	return 0;
}