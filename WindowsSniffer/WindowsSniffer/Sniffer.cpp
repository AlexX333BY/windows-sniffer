#pragma once

#include <stdexcept>
#include "Sniffer.h"

namespace WindowsSniffer
{
	Sniffer::Sniffer(PACKET_PROCESS_CALLBACK ppcCallback)
		: m_ppcCallback(ppcCallback)
	{
		if (ppcCallback == NULL)
		{
			throw new std::out_of_range("ppcCallback");
		}
	}
}
