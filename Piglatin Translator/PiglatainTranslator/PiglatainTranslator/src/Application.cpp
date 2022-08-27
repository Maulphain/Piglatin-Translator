#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;


struct WordElements
{
public:
	string data;
	bool isWord = true;
};

enum vowels
{
	A = 0, E = 4, I = 8, O = 14, U = 20
};

// Takes a string and changes the vector to have each element contain a part of the string. A "part" is either a set of only English characters or anything else
void PartitionElements(vector<WordElements>& words, const string& in);
// Translates text to it's "Latin" form
string LangToLat(const string& in);
// Translates "Latin" to the original text
string LatToLang(const string& in);
bool IsLetter(char in);
bool IsVowel(char in);
bool IsUppercase(char in);
// Removes excess spaces at the beginning and end of a string while adding a '¶' character to the end.
void FormatInput(string& in);

int main()
{
	system("cls");
	string inputStr = "";
	int option = 0;

	cout << "Please enter the text to translate:\n" << endl;
	cin.clear();
	getline(cin, inputStr);
	
	FormatInput(inputStr);

	cin.clear();
	cout << "\nEnter an option:\n[1] Translate to \"Latin\"\n[2] Translate from \"Latin\"" << endl << endl;
	cin >> option;
	if (option == 1)
		cout << "\nResult:\n\n" << LangToLat(inputStr) << endl;
	else if (option == 2)
		cout << "\nResult:\n\n" << LatToLang(inputStr) << endl;
	else
		cout << "\n\nNot a valid input.";

	cout << "\n\nApplication terminated.\n";
	while (true);
}

string LangToLat(const string& in)
{
	if (in == "")
		return "";
	vector<WordElements> words;
	PartitionElements(words, in);

	char first;
	bool wasUppercase = false;
	string out = "";
	for (WordElements e : words)
	{
		if (e.isWord)
		{
			first = e.data[0];
			wasUppercase = IsUppercase(first);
			// Make lowercase
			if (wasUppercase)
				first = (first - 'A') + 'a';
			// Move the first letter to the end
			if (IsVowel(first))
			{
				e.data.erase(0, 1);
				e.data += first;
			}
			// Remove -ay and move the original first letter to the beginning
			else
			{
				e.data.erase(0, 1);
				e.data += first;
				e.data += "ay";
			}
			// Capitalise the first letter
			if (wasUppercase)
				e.data[0] = (e.data[0] - 'a') + 'A';
		}
		out += e.data;
	}
	return out;
}


string LatToLang(const string& in)
{
	if (in == "")
		return "";
	vector<WordElements> words;
	PartitionElements(words, in);

	bool wasUppercase = false;
	string out = "";
	for (WordElements e : words)
	{
		if (e.isWord)
		{
			wasUppercase = IsUppercase(e.data[0]);
			// Make lowercase
			if (wasUppercase)
				e.data[0] = (e.data[0] - 'A') + 'a';
			// Move the last letter to the front if no -ay is appended
			if (e.data[e.data.length() - 1] == 'y')
			{
				e.data = e.data[e.data.length() - 3] + e.data;
				e.data.erase(e.data.length() - 3, 3);
			}
			// Remove -ay and move the original first letter to the beginning
			else
			{
				e.data = e.data[e.data.length() - 1] + e.data;
				e.data.erase(e.data.length() - 1, 1);
			}
			// Capitalise the first letter
			if (wasUppercase)
				e.data[0] = (e.data[0] - 'a') + 'A';
		}
		out += e.data;
	}
	return out;
}

bool IsLetter(char in)
{
	// Lowercase
	if ((in > 'a' - 1) && (in < 'z' + 1))
		return true;
	// Uppercase
	if ((in > 'A' - 1) && (in < 'Z' + 1))
		return true;
	return false;
}

void PartitionElements(vector<WordElements>& words, const string& in)
{
	string current = "";

	bool wasLastLetter = true;
	//if (IsLetter(in[0]))
	//	wasLastLetter = true;
	//else
	//	wasLastLetter = false;

	for (int i = 0; i < in.length() + 1; i++)
	{
		// Reached the termination character
		if ((in[i] == '¶') && !wasLastLetter)
		{
			words.push_back(WordElements{ current, false });
		}
		// If the last character was a letter and this one is too
		else if (wasLastLetter && IsLetter(in[i]))
		{
			current += in[i];
		}
		// Once at the end of a word
		else if (wasLastLetter && !IsLetter(in[i]))
		{
			words.push_back(WordElements{ current, true });
			current = in[i];
			wasLastLetter = false;
		}
		// If in a non-word section and the next is still a non-word
		else if (!wasLastLetter && !IsLetter(in[i]))
		{
			current += in[i];
		}
		// If in a non-word section and the next is a word
		else if (!wasLastLetter && IsLetter(in[i]))
		{
			words.push_back(WordElements{ current, false });
			current = in[i];
			wasLastLetter = true;
		}
	}
}

bool IsVowel(char in)
{
	// Lowercase
	if (in == 'a' + A) { return true; }
	else if (in == 'a' + E) { return true; }
	else if (in == 'a' + I) { return true; }
	else if (in == 'a' + O) { return true; }
	else if (in == 'a' + U) { return true; }

	// Uppercase
	else if (in == 'A' + A) { return true; }
	else if (in == 'A' + E) { return true; }
	else if (in == 'A' + I) { return true; }
	else if (in == 'A' + O) { return true; }
	else if (in == 'A' + U) { return true; }
	else return false;
}

bool IsUppercase(char in)
{
	if ((in > 'A' - 1) && (in < 'Z' + 1))
		return true;
	return false;
}

void FormatInput(string& in)
{
	if (in != "")
	{
		// Remove spaces from the front
		while (in[0] == ' ') { in.erase(0, 1); }
		// Remove spaces from the end
		while (in[in.length() - 1] == ' ') { in.erase(in.length() - 1, 1); }
		// Remove double spaces inside the text.
		for (int i = 1; i < in.length(); i++)
		{
			if ((in[i] == ' ') && (in[i - 1] == ' '))
				in.erase(i, 1);
		}
		// Add custom terminatin character
		in += '¶';
	}
}