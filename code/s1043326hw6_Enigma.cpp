#include "s1043326hw6_Enigma.h"

/*----------Plugboard----------*/
Plugboard::Plugboard(std::string file)
:Enigma_Component(file){
}

size_t Plugboard::Encoding(size_t const& i){//i - 65為陣列的index值
	if (link_next)
		link_next->Spin();
	size_t answer = link_next ? link_next->Encoding(encode_table[i] - 65) : encode_table[i] - 65;//利用call function先進行後面部分的加密
	answer = encode_table.find(answer + 65);//解碼; 利用密碼就能回推第幾個
	return answer;
}

/*----------Rotor----------*/
Rotor::Rotor(std::string file, char const& start_file, char const& file_arrows)
:Enigma_Component(file), start(start_file), arrows(file_arrows), index(start - 65){
}

void Rotor::Spin(){
	index++;
	if (index > 25) index -= 26;//如果轉一圈
	if (index == arrows - 65){
		if (link_next)
			link_next->Spin();
	}
}

size_t Rotor::Find_Var(size_t const& i){
	size_t variety = i + index;//從'A'開始往variety個
	if (variety > 25) variety -= 26;
	return variety;
}

size_t Rotor::Find_Pos(size_t const& diff){//diff為對應 1.encode_table所得到的內圈字元 2.內圈字元所回推的外圈字元
	int pos = diff - 65 - index;//diff得到的位置為從'A'開始的位置，所以調整為離index的位置
	if (pos < 0) pos += 26;//如果pos的結果 < 0 (比A小)就在補26
	return pos;
}

size_t Rotor::Encoding(size_t const& i){//i為陣列index值
	size_t answer = link_next ? link_next->Encoding(Find_Pos(encode_table[Find_Var(i)])) : Find_Pos(encode_table[Find_Var(i)]);//利用call function先進行後面部分的加密
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
	size_t answer = Rotor::Encoding(i);//呼叫父類別的Encoding
	size_t pre_arrows = arrows - 1;//用來判斷是否需要多轉一圈(特殊規則)
	if (pre_arrows < 0) pre_arrows += 26;//如果pos的結果 < 0 (比A小)就在補26
	if (index == pre_arrows - 65)
		Spin();
	return answer;
}

/*----------Reflector----------*/
Reflector::Reflector(std::string file)
:Enigma_Component(file){
}

size_t Reflector::Encoding(size_t const& i){
	return encode_table[i] - 65;//回傳反射結果(位置)
}