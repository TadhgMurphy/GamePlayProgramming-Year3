#pragma once
#include <iostream>

void FindAllVariables(char variables[1000], char code[1000])
{
	variables[0] = '\0';
	char line[1000];
	char variable[1000];
	int i = 0;
	int j = 0;

	while (code[i] != '\0')
	{
		j = 0;
		while (code[i] != '\n' && code[i] != '\0')
		{
			line[j++] = code[i++];
		}
		line[j] = '\0';
		if (code[i] == 'n')
		{
			i++;
		}

		if((line[0] == 'i' && line[1] == 'n' && line[2] == 't') || 
			(line[0] == 'c' && line[1] == 'h' && line[2] == 'a' && line[3] == 'r'))
	}
}
void FindAllVariablesInScope(char variables[1000], char code[1000], int lineNumber)
{

}