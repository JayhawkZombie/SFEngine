#pragma once

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

template<typename T>
class ValueBounded
{
public:
  ValueBounded(T ValMin, T ValMax)
    : m_ValMin(ValMin), m_ValMax(ValMax), m_Value(ValMin) { }

  ValueBounded(const T & val, T ValMin, T ValMax)
    : m_ValMin(ValMin), m_ValMax(ValMax), m_Value(std::clamp(val, ValMin, ValMax)) { }

  ValueBounded(const ValueBounded & val)
    : m_ValMin(val.m_ValMin)
    , m_ValMax(val.m_ValMax)
    , m_Value(std::clamp(val.m_Value, ValMin, ValMax)) { }

  explicit operator T() const
  {
    return m_Value;
  }

  inline T Min() const { return m_ValMin; }
  inline T Max() const { return m_ValMax; }

  // add

  inline friend T operator + (const ValueBounded & BVal, const T & val)
  {
    return BVal.m_Value + val;
  }

  inline friend T operator + (const T & val, const ValueBounded & BVal)
  {
    return val + BVal.m_Value;
  }

  inline ValueBounded& operator += (const T & val)
  {
    m_Value = std::clamp(m_Value + val, m_ValMin, m_ValMax);
    return *this;
  }

  inline ValueBounded& operator += (const ValueBounded & BVal)
  {
    m_Value = std::clamp(m_Value + BVal.m_Value, m_ValMin, m_ValMax);
    return *this;
  }

  // sub

  inline friend T operator - (const ValueBounded & BVal, const T & val)
  {
    return BVal.m_Value - val;
  }

  inline friend T operator - (const T & val, const ValueBounded & BVal)
  {
    return BVal.m_Value - val;
  }

  inline ValueBounded& operator -= (const T & val)
  {
    m_Value = std::clamp(m_Value - val, m_ValMin, m_ValMax);
    return *this;
  }

  inline ValueBounded& operator -= (const ValueBounded & BVal)
  {
    m_Value = std::clamp(m_Value - BVal.m_Value, m_ValMin, m_ValMax);
    return *this;
  }

  // mult

  inline friend T operator * (const ValueBounded & BVal, const T & val)
  {
    return m_Value * val;
  }

  inline friend T operator * (const T & val, const ValueBounded & BVal)
  {
    return m_Value * val;
  }

  inline ValueBounded& operator *= (const T & val)
  {
    m_Value = std::clamp(m_Value * val, m_ValMin, m_ValMax);
    return *this;
  }

  inline ValueBounded& operator *= (const ValueBounded & BVal)
  {
    m_Value = std::clamp(m_Value * BVal.m_Value, m_ValMin, m_ValMax);
    return *this;
  }

  // div

  inline friend T operator / (const ValueBounded & BVal, const T & val)
  {
    return m_Value / val;
  }

  inline friend T operator / (const T & val, const ValueBounded & BVal)
  {
    return m_Value / val;
  }

  inline ValueBounded& operator /= (const T & val)
  {
    m_Value = std::clamp(m_Value / val, m_ValMin, m_ValMax);
    return *this;
  }

  inline ValueBounded& operator /= (const ValueBounded & BVal)
  {
    m_Value = std::clamp(m_Value / BVal.m_Value, m_ValMin, m_ValMax);
    return *this;
  }

  inline ValueBounded& operator = (const T & val)
  {
    m_Value = std::clamp(val, m_ValMin, m_ValMax);
    return *this;
  }

  inline ValueBounded& operator = (const ValueBounded & BVal)
  {
    m_Value = std::clamp(BVal.m_Value, m_ValMin, m_ValMax);
    return *this;
  }

  inline T operator()() const
  {
    return m_Value;
  }

  template<class Archive>
  void serialize(Archive & ar)
  {
    ar(m_ValMin, m_ValMax, m_Value);
  }

private:

  T m_Value;
  T m_ValMin;
  T m_ValMax;

};

namespace cereal
{

  template<typename ValType>
  template<class Archive>
  void load_and_construct(Archive & ar, cereal::construct<ValueBounded<ValType>> & obj)
  {
    ValType vMin, vMax, vCur;

    ar(vMin, vMax, vCur);
    obj(vCur, vMin, vMax);
  }

}

using BoundedInt    = ValueBounded<int32_t>;
using BoundedUint   = ValueBounded<uint32_t>;
using BoundedInt32  = ValueBounded<int32_t>;
using BoundedUint32 = ValueBounded<uint32_t>;
using BoundedInt64  = ValueBounded<int64_t>;
using BoundedUint64 = ValueBounded<uint64_t>;
