// Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/*!
 * @file JsonStr.cpp
 * This source file contains the definition of the described types in the IDL file.
 *
 * This file was generated by the tool gen.
 */

#ifdef _WIN32
// Remove linker warning LNK4221 on Visual Studio
namespace {
char dummy;
}  // namespace
#endif  // _WIN32

#include "JsonStr.h"
#include <fastcdr/Cdr.h>

#include <fastcdr/exceptions/BadParamException.h>
using namespace eprosima::fastcdr::exception;

#include <utility>

#define JsonStrBean_max_cdr_typesize 260ULL;
#define JsonStrBean_max_key_cdr_typesize 0ULL;

JsonStrBean::JsonStrBean()
{
    // string m_JsonString
    m_JsonString ="";

}

JsonStrBean::~JsonStrBean()
{
}

JsonStrBean::JsonStrBean(
        const JsonStrBean& x)
{
    m_JsonString = x.m_JsonString;
}

JsonStrBean::JsonStrBean(
        JsonStrBean&& x) noexcept 
{
    m_JsonString = std::move(x.m_JsonString);
}

JsonStrBean& JsonStrBean::operator =(
        const JsonStrBean& x)
{

    m_JsonString = x.m_JsonString;

    return *this;
}

JsonStrBean& JsonStrBean::operator =(
        JsonStrBean&& x) noexcept
{

    m_JsonString = std::move(x.m_JsonString);

    return *this;
}

bool JsonStrBean::operator ==(
        const JsonStrBean& x) const
{

    return (m_JsonString == x.m_JsonString);
}

bool JsonStrBean::operator !=(
        const JsonStrBean& x) const
{
    return !(*this == x);
}

size_t JsonStrBean::getMaxCdrSerializedSize(
        size_t current_alignment)
{
    static_cast<void>(current_alignment);
    return JsonStrBean_max_cdr_typesize;
}

size_t JsonStrBean::getCdrSerializedSize(
        const JsonStrBean& data,
        size_t current_alignment)
{
    (void)data;
    size_t initial_alignment = current_alignment;


    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4) + data.JsonString().size() + 1;

    return current_alignment - initial_alignment;
}

void JsonStrBean::serialize(
        eprosima::fastcdr::Cdr& scdr) const
{

    scdr << m_JsonString.c_str();

}

void JsonStrBean::deserialize(
        eprosima::fastcdr::Cdr& dcdr)
{

    dcdr >> m_JsonString;}

/*!
 * @brief This function copies the value in member JsonString
 * @param _JsonString New value to be copied in member JsonString
 */
void JsonStrBean::JsonString(
        const std::string& _JsonString)
{
    m_JsonString = _JsonString;
}

/*!
 * @brief This function moves the value in member JsonString
 * @param _JsonString New value to be moved in member JsonString
 */
void JsonStrBean::JsonString(
        std::string&& _JsonString)
{
    m_JsonString = std::move(_JsonString);
}

/*!
 * @brief This function returns a constant reference to member JsonString
 * @return Constant reference to member JsonString
 */
const std::string& JsonStrBean::JsonString() const
{
    return m_JsonString;
}

/*!
 * @brief This function returns a reference to member JsonString
 * @return Reference to member JsonString
 */
std::string& JsonStrBean::JsonString()
{
    return m_JsonString;
}


size_t JsonStrBean::getKeyMaxCdrSerializedSize(
        size_t current_alignment)
{
    static_cast<void>(current_alignment);
    return JsonStrBean_max_key_cdr_typesize;
}

bool JsonStrBean::isKeyDefined()
{
    return false;
}

void JsonStrBean::serializeKey(
        eprosima::fastcdr::Cdr& scdr) const
{
    (void) scdr;
}

