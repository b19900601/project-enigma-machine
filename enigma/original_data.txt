#include <conio.h>
#include "s1043326hw6_Enigma.h"

int main()
{
	Enigma_Files Rotor_start_file;
	Enigma_Files Rotor_arrow_file;
	Enigma_Files original_message_file;
	Enigma_Files encoded_message_file;

	std::cout << "s1043326's version" << std::endl;
	std::cout << "Read original message: \"original_data.txt\"" << std::endl;
	original_message_file.Read_file("original_data.txt");

	std::cout << "Read arrows position of [Rotor]: \"Rotor_arrow_web.txt\"" << std::endl;
	Rotor_arrow_file.Read_file("Rotor_arrow_web.txt");
	char Rotor_III_arrows = Rotor_arrow_file[0];
	char Rotor_II_arrows = Rotor_arrow_file[1];
	char Rotor_I_arrows = Rotor_arrow_file[2];

	std::cout << "Read start position of [Rotor]: \"Rotor_start_web.txt\"" << std::endl;
	Rotor_start_file.Read_file("Rotor_start_web.txt");

	std::cout << "Read [Plugboard]: \"Plugboard_web.txt\"" << std::endl;
	Plugboard plugboard("Plugboard_web.txt");

	std::cout << "Read [Rotor III]: \"Rotor_III_web.txt\"" << std::endl;
	Rotor Rotor_III("Rotor_III_web.txt", Rotor_start_file[0], Rotor_III_arrows);

	std::cout << "Read [Rotor II]: \"Rotor_II_web.txt\"" << std::endl;
	Special_Rotor Rotor_II("Rotor_II_web.txt", Rotor_start_file[1], Rotor_II_arrows);

	std::cout << "Read [Rotor I]: \"Rotor_I_web.txt\"" << std::endl;
	Rotor Rotor_I("Rotor_I_web.txt", Rotor_start_file[2], Rotor_I_arrows);

	std::cout << "Read [Reflector]: \"Reflector_web.txt\"" << std::endl;
	Reflector reflector("Reflector_web.txt");

	plugboard.Link(Rotor_III);
	Rotor_III.Link(Rotor_II);
	Rotor_II.Link(Rotor_I);
	Rotor_I.Link(reflector);

	std::cout << "*Original message: " << std::endl << original_message_file.Data() << std::endl;

	for (size_t i = 0; i < original_message_file.Length(); i++)
		encoded_message_file.Push(plugboard.Input_signal(original_message_file[i]));
	//use a chain reaction to encode all characters in the original_message_file[]

	std::cout << "(Output encoded data to \"encoded_data.txt\")" << std::endl;
	encoded_message_file.Write_file("encoded_data.txt");

	std::cout << "*Eecoded message: " << std::endl << encoded_message_file.Data() << std::endl;

	std::cout << "*Decode it back..." << std::endl;
	plugboard.Reset();
	//reset the enigma to decode encoded information back to original data
	//(make a chain reaction to reset all encoder)
	for (size_t i = 0; i < encoded_message_file.Length(); i++)
		std::cout << plugboard.Input_signal(encoded_message_file[i]);
	std::cout << std::endl;

	std::cout << "Press any key to exit...";
	std::getchar();
	return EXIT_SUCCESS;
}
