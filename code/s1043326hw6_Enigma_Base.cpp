#include <string>
#include "s1043326hw6_Enigma_Base.h"
#include <Windows.h>

/*----------Enigma_Files----------*/
void Enigma_Files::Read_file(std::string file){
	std::ifstream infile(file, std::ifstream::in);
	if (!infile.good()){
		infile.close();
		std::cerr << file << " open fail!!";
		Sleep(1000); exit(1);
		return;
	}
	std::string s;
	for (; !infile.eof();){
		std::getline(infile, s);
		data += s + '\n';
	}
	infile.close();
}

void Enigma_Files::Write_file(std::string file){
	std::ofstream outfile(file, std::ifstream::out);
	if (!outfile.good()){
		outfile.close();
		std::cerr << file << " open fail!!";
		return;
	}
	outfile << data;
	outfile.close();
}

void Enigma_Files::Push(char const& c){
	data.push_back(c);
}

char const& Enigma_Files::operator [](size_t const& i){
	return data[i];
}

std::string Enigma_Files::Data(){
	return data;
}

size_t Enigma_Files::Length(){
	return data.size();
}

/*----------Enigma_Component----------*/
Enigma_Component::Enigma_Component(std::string file)
:link_next(NULL), link_previous(NULL){
	Read_table(file);
}

char Enigma_Component::Input_signal(char c){
	if (!((c >= 65 && c <= 90) || (c >= 97 && c <= 122)))return c;
	bool big = true;
	if (c > 90){
		c -= 32;//¤p¼gÂà´«¤j¼g
		big = false;
	}
	return big ? (char)(Encoding(c - 65) + 65) : (char)(Encoding(c - 65) + 65) + 32;
}

void Enigma_Component::Link(Enigma_Component & next){
	this->link_next = &next;
	next.link_previous = this;
}

void Enigma_Component::Read_table(std::string file){
	std::ifstream infile(file, std::ifstream::in);
	if (!infile.good()){
		infile.close();
		std::cerr << file << " open fail!!";
		Sleep(1000); exit(1);
		return;
	}
	for (char s, a = 'A'; a <= 'Z'; a++){
		infile >> s;
		encode_table += s;//encode data
	}
	infile.close();
}

void Enigma_Component::Reset(){
	if (link_next)
		link_next->Reset();
}
