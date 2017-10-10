#pragma once

#include "s1043326hw6_Enigma_Base.h"

class Plugboard : public Enigma_Component{

public:
	Plugboard(std::string file);

protected:
	virtual size_t Encoding(size_t const& i);
};

class Rotor : public Enigma_Component{

public:
	Rotor(std::string file, char const& start_file, char const& file_arrows);
	virtual void Reset();
	size_t Find_Var(size_t const& i);
	size_t Find_Pos(size_t const& diff);

protected:
	char start;
	char arrows;
	size_t index;

	virtual void Spin();
	virtual size_t Encoding(size_t const& i);
};

class Special_Rotor : public Rotor{

public:
	Special_Rotor(std::string file, char start_file, char file_arrows);

protected:
	virtual size_t Encoding(size_t const& i);
};

class Reflector : public Enigma_Component{

public:
	Reflector(std::string file);

protected:
	virtual size_t Encoding(size_t const& i);
};