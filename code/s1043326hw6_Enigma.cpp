#include "s1043326hw6_Enigma.h"

/*----------Plugboard----------*/
Plugboard::Plugboard(std::string file)
:Enigma_Component(file){
}

size_t Plugboard::Encoding(size_t const& i){//i - 65���}�C��index��
	if (link_next)
		link_next->Spin();
	size_t answer = link_next ? link_next->Encoding(encode_table[i] - 65) : encode_table[i] - 65;//�Q��call function���i��᭱�������[�K
	answer = encode_table.find(answer + 65);//�ѽX; �Q�αK�X�N��^���ĴX��
	return answer;
}

/*----------Rotor----------*/
Rotor::Rotor(std::string file, char const& start_file, char const& file_arrows)
:Enigma_Component(file), start(start_file), arrows(file_arrows), index(start - 65){
}

void Rotor::Spin(){
	index++;
	if (index > 25) index -= 26;//�p�G��@��
	if (index == arrows - 65){
		if (link_next)
			link_next->Spin();
	}
}

size_t Rotor::Find_Var(size_t const& i){
	size_t variety = i + index;//�q'A'�}�l��variety��
	if (variety > 25) variety -= 26;
	return variety;
}

size_t Rotor::Find_Pos(size_t const& diff){//diff������ 1.encode_table�ұo�쪺����r�� 2.����r���Ҧ^�����~��r��
	int pos = diff - 65 - index;//diff�o�쪺��m���q'A'�}�l����m�A�ҥH�վ㬰��index����m
	if (pos < 0) pos += 26;//�p�Gpos�����G < 0 (��A�p)�N�b��26
	return pos;
}

size_t Rotor::Encoding(size_t const& i){//i���}�Cindex��
	size_t answer = link_next ? link_next->Encoding(Find_Pos(encode_table[Find_Var(i)])) : Find_Pos(encode_table[Find_Var(i)]);//�Q��call function���i��᭱�������[�K
	answer = Find_Pos(encode_table.find((char)(Find_Var(answer) + 65)) + 65);
	return answer;
}

void Rotor::Reset(){
	index = start - 65;
	if (link_next)
		link_next->Reset();
}

/*----------Special_Rotor----------*/
Special_Rotor::Special_Rotor(std::string file, char start_file, char file_arrows)
:Rotor(file, start_file, file_arrows){
}

size_t Special_Rotor::Encoding(size_t const& i){	
	size_t answer = Rotor::Encoding(i);//�I�s�����O��Encoding
	size_t pre_arrows = arrows - 1;//�ΨӧP�_�O�_�ݭn�h��@��(�S��W�h)
	if (pre_arrows < 0) pre_arrows += 26;//�p�Gpos�����G < 0 (��A�p)�N�b��26
	if (index == pre_arrows - 65)
		Spin();
	return answer;
}

/*----------Reflector----------*/
Reflector::Reflector(std::string file)
:Enigma_Component(file){
}

size_t Reflector::Encoding(size_t const& i){
	return encode_table[i] - 65;//�^�ǤϮg���G(��m)
}