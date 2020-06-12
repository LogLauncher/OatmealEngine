#pragma once
// ------------------------
// Source: Overloard engine
// ------------------------


namespace OatmealEngine
{
	class BinaryReader
	{
	public:
		BinaryReader();
		~BinaryReader();
		DEL_ROF(BinaryReader);

		template <class T>
		T Read();

		std::string ReadString();
		std::string ReadLongString();
		std::string ReadNullString();

		int GetBufferPosition();
		bool SetBufferPosition(int pos);
		bool MoveBufferPosition(int move);
		bool Exists() const { return m_Exists; }

		void Open(const std::string& binaryFile);
		void Open(char* s, UINT32 size);
		void Close();

	private:
		bool m_Exists;
		std::shared_ptr<std::istream> m_pReader;

	};

	template <class T>
	T OatmealEngine::BinaryReader::Read()
	{
		if (m_pReader == nullptr)
		{
			return T();
		}

		T value;
		m_pReader->read((char*)&value, sizeof(T));
		return value;
	}

}
