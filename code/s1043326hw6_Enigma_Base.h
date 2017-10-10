#pragma once

#include <iostream>
#include <fstream>
#include <string>

class Enigma_Files{

public:
	void Read_file(std::string file);
	void Write_file(std::string file);

	void Push(char const& c);
	char const& operator [] (size_t const& i);

	std::string Data();
	size_t Length();

protected:
	std::string data;

};

class Enigma_Component{

	friend class Plugboard;
	friend class Rotor;
	friend class Special_Rotor;
	friend class Reflector;

public:
	Enigma_Component(std::string file);

	char Input_signal(char c);

	void Link(Enigma_Component & next);

	virtual void Reset();

protected:
	std::string encode_table;

	Enigma_Component* link_next;
	Enigma_Component* link_previous;

	virtual size_t Encoding(size_t const& i) = 0;

	void Read_table(std::string file);

	virtual void Spin(){}
};
