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

#define DataTypeHashLengh sizeof(size_t)

template<size_t PacketBufferSize = 512>
class DataPacket
{
public:

  /* Insert data into packet */
  template<typename T>
  inline DataPacket& operator << (const T & Data)
  {
    constexpr size_t DataSize = sizeof(T);

    static_assert( DataSize <= PacketBufferSize - DataTypeHashLengh, "Data type is too large to pack" );

    /* Amount of storage needed to pack the requested data */
    size_t RequiredSpace = DataTypeHashLengh + DataSize;

    if (DataStorageOffset > PacketBufferSize - RequiredSpace)
      throw std::runtime_error("Data packet cannot store any additional data");

    auto typeinfo_hash = typeid( Data ).hash_code();

    /* Store hash of type */
    size_t * bufferPtrHash = reinterpret_cast< size_t * >( DataBuffer + DataStorageOffset );
    *bufferPtrHash = typeinfo_hash;

    DataStorageOffset += DataTypeHashLengh;

    /* Store binary of data */
    T * bufferPtrData = reinterpret_cast< T * >( DataBuffer + DataStorageOffset );
    *bufferPtrData = Data;

    DataStorageOffset += DataSize;

    ++ItemsStored;

    return *this;
  }

  /* Extract data from packet */
  template<typename T>
  inline DataPacket& operator >> (T & Data)
  {
    constexpr size_t DataSize = sizeof(T);

    static_assert( DataSize < PacketBufferSize - DataTypeHashLengh, "Data type is too large to unpack" );

    /* Amount of room required to be packed */
    size_t RequiredDataLength = DataTypeHashLengh + DataSize;

    if (PacketBufferSize - DataExtractionOffset < RequiredDataLength)
      throw std::runtime_error("Data packet does not contain enough data to unpack");

    auto typeinfo_hash = typeid( Data ).hash_code();

    /* Get the position of the hash in the buffer = DataStorageOffset - DataSize - HashSize */
    const size_t HashPosition = DataExtractionOffset;

    /* Get hash of the type that is stored */
    const size_t * hashValue = reinterpret_cast< const size_t * > ( DataBuffer + HashPosition );

    /* Ensure this hash matches the hash of the requested type */
    if (*hashValue != typeinfo_hash)
      throw std::runtime_error("Type requested does not match type stored");

    size_t DataPosition = DataExtractionOffset + DataTypeHashLengh;

    const T * dataPtr = reinterpret_cast< const T * >( DataBuffer + DataPosition );

    Data = *dataPtr;

    DataExtractionOffset += DataSize;
    DataExtractionOffset += DataTypeHashLengh;

    --ItemsStored;

    return *this;
  }

  size_t Length() const
  {
    return DataStorageOffset;
  }

  bool Full() const
  {
    return ( DataStorageOffset == PacketBufferSize );
  }

  bool Empty() const
  {
    return ( DataStorageOffset == 0 || DataExtractionOffset == DataStorageOffset );
  }

  size_t Capacity() const
  {
    return PacketBufferSize;
  }

  size_t Count() const
  {
    return ItemsStored;
  }

  template<typename T>
  bool PutBack(const T & Data)
  {
    constexpr DataSize = sizeof(T);

    static_assert( DataSize < PacketBufferSize, "Data is too large to have been packed" );

    const size_t RequiredSize = DataSize + DataTypeHashLengh;

    if (DataExtractionOffset < RequiredSize)
      return false;

    const size_t HashPosition = DataExtractionOffset - DataSize - DataTypeHashLengh;
    const size_t HashValue = typeid( Data ).hash_code();

    const size_t * StoredHashPtr = reinterpret_cast< const size_t * >( DataBuffer + HashPosition );

    if (*StoredHashPtr != HashValue)
      return false;

    /* The hash matched, so we verify the value matches the stored value and rewind if it does */

    const size_t DataPosition = DataExtractionOffset - DataSize;
    const T * StoredDataPtr = reinterpret_cast< const T * >( DataBuffer + DataPosition );

    if (*StoredDataPtr != Data)
      return false;

    /* The hash and value matched, so move the extraction offset back */

    DataExtractionOffset -= DataSize;
    DataExtractionOffset -= DataTypeHashLengh;

    return true;
  }

  operator bool() const
  {
    /* Packet is valid if we haven't extracted everything */
    return ( DataExtractionOffset < PacketBufferSize );
  }

  template<typename T>
  bool CanPack(const T & Data)
  {
    /* If we have enough space we can pack it */
    return ( DataStorageOffset + sizeof(T) + DataTypeHashLengh <= PacketBufferSize );
  }

  template<typename T>
  bool CanExtract(const T & Data)
  {
    /* If we have enough space AND the next hash matches the hash of the Data's type */

    auto typehash = typeid( Data ).hash_code();

    if (DataExtractionOffset + sizeof(T) + DataTypeHashLengh > PacketBufferSize)
      return false;

    /* Get the next hash and make sure it matches the hash of the type passed */

    const size_t *HashPtr = reinterpret_cast< const size_t * >( DataBuffer + DataExtractionOffset );

    return ( *HashPtr == typehash );
  }

private:

  /* Data buffer for storing binary packed data */

  size_t ItemsStored = 0;
  size_t DataStorageOffset = 0;
  size_t DataExtractionOffset = 0;
  char DataBuffer[PacketBufferSize] = { 0 };

};

/* Aliases for common packet sizes */

using TinyDataPacket   = DataPacket<32>;
using NormalDataPacket = DataPacket<64>;
using MediumDataPacket = DataPacket<128>;
using LargeDataPacket  = DataPacket<256>;
using HugeDataPacket   = DataPacket<512>;
