#pragma once

////////////////////////////////////////////////////////////
//
// MIT License
//
// Copyright(c) 2017 Kurt Slagle - kurt_slagle@yahoo.com
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

#include "DataPacket.h"
#include <deque>

class DataStream
{
public:

  DataStream()
  {
    PacketList.emplace_front();
  }

  template<typename T>
  DataStream& operator << (const T & Data)
  {
    auto & Pkt = PacketList[CurrentInsertionPacket];

    /* If the current packet can't store the data, add a new packet and use that */
    if (!Pkt.CanPack(Data))
    {
      PacketList.emplace_back();
      ++CurrentInsertionPacket;

      PacketList.back() << Data;
    }
    else
    {
      Pkt << Data;
    }

    return *this;
  }

  template<typename T>
  DataStream& operator >> (T & Data)
  {
    if (IsFail)
      throw std::runtime_error("Data stream extraction is not in a valid state");

    if (CurrentExtractionPacket > CurrentInsertionPacket)
      throw std::runtime_error("No additional data can be extracted");

    auto & Pkt = PacketList[CurrentExtractionPacket];

    /* Ensure the data can be extracted to avoid throwing */
    if (Pkt && Pkt.CanExtract(Data))
    {
      Pkt >> Data;

      return *this;
    }

    /* If the current packet is empty AND it isn't the last packet, move on to the next one */
    else if (CurrentExtractionPacket + 1 < PacketList.size())
    {
      /* That wasn't the last packet, so increment and extract from that */
      ++CurrentExtractionPacket;

      auto & nextPkt = PacketList[CurrentExtractionPacket];

      if (nextPkt.CanExtract(Data))
      {
        nextPkt >> Data;
        return *this;
      }
    }

    /* Fail state - oops */
    IsFail = true;
    return *this;
  }

  operator bool() const
  {
    /* We are valid if we are not in a fail state */
    return ( !IsFail );
  }

  /* Reset the fail state so the user can try extraction again

  This will only reset the IsFail member if there is data available to extract
  */
  void Reset()
  {
    // Do not reset if we're over the packets stored
    if (CurrentExtractionPacket > CurrentInsertionPacket)
      return;

    // Do not reset if the packet is empty
    if (PacketList[CurrentExtractionPacket].Empty())
      return;

    IsFail = false;
  }

  bool Empty() const
  {
    /* We are empty if we have extracted all the data */
    if (PacketList[CurrentExtractionPacket].Empty())
      return true;

    return false;
  }

  size_t PacketCount() const
  {
    return PacketList.size();
  }

private:

  std::deque<NormalDataPacket> PacketList;

  size_t CurrentInsertionPacket = 0;
  size_t CurrentExtractionPacket = 0;

  bool IsFail = false;
};
