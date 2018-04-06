#ifndef CONFIGURATIONPARSER_H_
#define CONFIGURATIONPARSER_H_

#include <iostream>
#include <ifstream>
#include <string>

class ConfigurationParser
{

public:

	ConfigurationParser(string _configFile);

	getProgramInput();
	getMemContentsInput();
	getRegisterFileInput();
	getOutputMode();
	getDebugMode();
	getPrintMemoryContents();
	getOutputWrittenFile();
	getOutputFile();

private:

	string m_programInput;
	string m_memContentsInput;
	string m_registerFileInput;
	bool m_outputMode;
	bool m_debugMode;
	bool m_printMemoryContents;
	bool m_writeToOutputFile;
	string m_outputFile;


};





#endif