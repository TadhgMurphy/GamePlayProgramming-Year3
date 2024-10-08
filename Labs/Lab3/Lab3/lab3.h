#pragma once
#include <iostream>
/// <summary>
/// Tadhg Murphy
/// </summary>
void FindAllVariables(char variables[1000], char code[1000])
{
	int varIndex = 0;
	int i = 0;

	while (code[i] != '\0')
	{
		if (code[i] == 'i' && code[i + 1] == 'n' && code[i + 2] == 't' && code[i + 3] == ' ')
		{
			i += 4;

			while (code[i] == ' ')
			{
				i++;
			}

			while (code[i] != ' ' && code[i] != '=' && code[i] != ';' && code[i] != '\n' && code[i] != '\0')
			{
				variables[varIndex++] = code[i++];
			}
			variables[varIndex] = ',';
		}


		else if (code[i] == 'c' && code[i + 1] == 'h' && code[i + 2] == 'a' && code[i + 3] == 'r' && code[i + 4] == ' ')
		{
			i += 5;

			while (code[i] == ' ')
			{
				i++;
			}

			while (code[i] != ' ' && code[i] != '=' && code[i] != ';' && code[i] != '\n' && code[i] != '\0')
			{
				variables[varIndex++] = code[i++];
			}
			variables[varIndex] = ',';
		}

		else
		{
			i++;
		}
	}

	if (varIndex > 0 && variables[varIndex - 1] == ',')
	{
		variables[varIndex - 1] = '\0';
	}
	else
	{
		variables[varIndex] = '\0';
	}
}
void FindAllVariablesInScope(char variables[1000], char code[1000], int lineNumber)
{
	int varIndex = 0;
	int i = 0;
	int currentLine = 1;
	int scopeCount = 0;

	while (code[i] != '\0')
	{
		if (code[i] == '\n')
		{
			currentLine++;
		}

		if (currentLine == lineNumber)
		{
			while (i >= 0 && code[i] != '{')
			{
				i--;
			}

			break;
		}
		i++;
	}

	if (code[i] == '{')
	{
		scopeCount++;
		i++;

		while (scopeCount > 0 && code[i] != '\0')
		{
			if (code[i] == '{')
			{
				scopeCount++;
			}
			else if (code[i] == '}')
			{
				scopeCount--;

				if (scopeCount == 0)
				break;
			}

		}
	}
}