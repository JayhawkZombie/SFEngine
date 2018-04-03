////////////////////////////////////////////////////////////
//
// MIT License
//
// Copyright(c) 2018 Kurt Slagle - kurt_slagle@yahoo.com
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
// The origin of this software must not be misrepresented; you must not claim
// that you wrote the original software.If you use this software in a product,
// an acknowledgment of the software used is required.
//
////////////////////////////////////////////////////////////

#include "System.h"


SystemInfo::SystemInfo()
{
#ifdef SPLATFORM_WINDOWS

  SYSTEM_INFO info;
  GetSystemInfo(&info);

  switch (info.wProcessorArchitecture)
  {
    case PROCESSOR_ARCHITECTURE_AMD64:
    {
      m_Info.Arch = SystemProcessorArchitecture::AMD64; break;
    }
    case PROCESSOR_ARCHITECTURE_ARM:
    {
      m_Info.Arch = SystemProcessorArchitecture::ARM; break;
    }
    case PROCESSOR_ARCHITECTURE_ARM64:
    {
      m_Info.Arch = SystemProcessorArchitecture::ARM64; break;
    }
    case PROCESSOR_ARCHITECTURE_IA64:
    {
      m_Info.Arch = SystemProcessorArchitecture::IA64; break;
    }
    case PROCESSOR_ARCHITECTURE_INTEL:
    {
      m_Info.Arch = SystemProcessorArchitecture::IntelX86; break;
    }
    case PROCESSOR_ARCHITECTURE_UNKNOWN:
    {
      m_Info.Arch = SystemProcessorArchitecture::Unknown; break;
    }
    default:
    {
      m_Info.Arch = SystemProcessorArchitecture::Unknown;
    }
  }

  m_Info.PageSize = static_cast< uint32_t >(info.dwPageSize);
  m_Info.MinAddress = info.lpMinimumApplicationAddress;
  m_Info.MaxAddress = info.lpMaximumApplicationAddress;
  
  bool m = false;
  uint32_t mask = 1;

  for (auto & bl : m_Info.ProcMask)
  {
    bl = ((mask & info.dwActiveProcessorMask) == 0);
    mask <<= 1;
  }

  m_Info.AllocationGranularity = static_cast< uint32_t >(info.dwAllocationGranularity);

#endif
}

SystemProcessorArchitecture SystemInfo::GetProcessorArchitecture()
{
  return m_Info.Arch;
}

uint32_t SystemInfo::GetPageSize()
{
  return m_Info.PageSize;
}

void* SystemInfo::GetMinimumApplicationAddress()
{
  return m_Info.MinAddress;
}

void* SystemInfo::GetMaximumApplicationAddress()
{
  return m_Info.MaxAddress;
}

const std::array<bool, 32>& SystemInfo::GetActiveProcessorMask()
{
  return m_Info.ProcMask;
}
