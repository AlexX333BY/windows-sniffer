#include "DataLengthPair.h"
#include <stdexcept>

namespace WindowsSniffer
{
	DataLengthPair::DataLengthPair(LPVOID lpData, DWORD dwLength)
		: m_lpData(lpData), m_dwLength(dwLength)
	{
		if (lpData == NULL)
		{
			throw new std::invalid_argument("lpData");
		}
	}

	LPVOID DataLengthPair::GetData()
	{
		return m_lpData;
	}

	DWORD DataLengthPair::GetLength()
	{
		return m_dwLength;
	}
}
