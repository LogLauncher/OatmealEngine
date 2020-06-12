#include "MiniginPCH.h"
#include "BinaryReader.h"

#include <fstream>

OatmealEngine::BinaryReader::BinaryReader()
	: m_Exists{false}
	, m_pReader{nullptr}
{}
OatmealEngine::BinaryReader::~BinaryReader()
{
	Close();
}

std::string OatmealEngine::BinaryReader::ReadString()
{
	if (m_pReader == nullptr)
		return "";

	auto stringLength = Read<UINT>();

	std::stringstream ss;
	for (UINT i = 0; i < stringLength; ++i)
		ss << Read<char>();

	return ss.str();
}
std::string OatmealEngine::BinaryReader::ReadLongString()
{
	if (m_pReader == nullptr)
		return "";

	std::string text;
	getline(*m_pReader, text, '\0');

	return text;
}
std::string OatmealEngine::BinaryReader::ReadNullString()
{
	if (m_pReader == nullptr)
		return "";

	int stringLength = int(Read<char>());

	std::stringstream ss;
	for (int i = 0; i < stringLength; ++i)
		ss << Read<char>();

	return ss.str();
}

int OatmealEngine::BinaryReader::GetBufferPosition()
{
	if (m_pReader)
		return static_cast<int>(m_pReader->tellg());

	return -1;
}
bool OatmealEngine::BinaryReader::SetBufferPosition(int pos)
{
	if (m_pReader)
	{
		m_pReader->seekg(pos);
		return true;
	}

	return false;
}
bool OatmealEngine::BinaryReader::MoveBufferPosition(int move)
{
	int currPos = GetBufferPosition();
	if (currPos > 0)
		return SetBufferPosition(currPos + move);

	return false;
}

void OatmealEngine::BinaryReader::Open(const std::string& binaryFile)
{
	Close();

	auto temp = std::make_shared<std::ifstream>();
	temp->open(binaryFile, std::ios::in | std::ios::binary);
	if (temp->is_open())
	{
		m_pReader = temp;
		m_Exists = true;
	}
	else
		Close();
}

void OatmealEngine::BinaryReader::Open(char* s, UINT32 size)
{
	Close();

	std::string data(s, size);
	m_pReader = std::make_shared<std::istringstream>(data);
	m_Exists = true;
}

void OatmealEngine::BinaryReader::Close()
{
	m_Exists = false;
}
