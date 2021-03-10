#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> parse(std::string a)
{
	std::vector<std::string> B;
	size_t found = a.find(':', 0);
	if (found == std::string::npos)
		return B;
	B.push_back(a.substr(0, found));
	size_t found2;
	for (found = a.find('"', found + 1); found != std::string::npos; found = a.find('"', found2 + 1 ))
	{
		found2 = a.find('"', found + 1);
		if (found2 == std::string::npos)
			return B;
		B.push_back(a.substr(found + 1, found2 - found - 1));
	}
	return B;
}
void ain()
{
	std::string a("Govno: \"jopa\" \"chlen\"");
	std::vector<std::string> B = parse(a);
	for (int i = 0; i < B.size(); i++)
		std::cout << B[i] <<"\n";
}