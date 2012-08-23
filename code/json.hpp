#ifndef _json_hpp__
#define _json_hpp__

// Copyright (c) 2012, Andre Caron (andre.l.caron@gmail.com)
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

/*!
 * @file json.hpp
 * @brief C++ interface to the cJSON library.
 */

#include <cJSON.h>
#include <iosfwd>
#include <string>
#include <vector>

namespace json {

    /*!
     * @brief Dynamically typed value.
     *
     * @note Instances of this class must be entirely scoped within the
     *  lifetime of the root @c Document object from which they are extracted.
     */
    class Any
    {
        /* data. */
    private:
        ::cJSON * myData;

        /* construction. */
    public:
        /*!
         * @internal
         * @brief Wraps the underlying implementation.
         * @param data Handle to the JSON data structure.
         */
        explicit Any (::cJSON * data)
            : myData(data)
        {}

        /* methods. */
    public:
        /*!
         * @internal
         * @brief Access the underlying implementation.
         * @return Handle to the JSON data structure.
         */
        ::cJSON * data () const {
            return (myData);
        }

        /*!
         * @brief Checks if the value is null.
         * @return @c true if the value is null, else @c false.
         */
        bool is_null () const {
            return (myData->type == cJSON_NULL);
        }

        /*!
         * @brief Checks if the value is a boolean.
         * @return @c true if the value is a boolean, else @c false.
         *
         * @see operator bool()
         */
        bool is_bool () const {
            return ((myData->type == cJSON_True) ||
                    (myData->type == cJSON_False));
        }

        /*!
         * @brief Checks if the value is a number.
         * @return @c true if the value is a number, else @c false.
         *
         * @note There is no way to determine if the value is an integer or a
         *  real number.  The application should determine if it can deal with
         *  real values or if it only accepts integers.
         *
         * @see operator int()
         * @see operator double()
         */
        bool is_number () const {
            return (myData->type == cJSON_Number);
        }

        /*!
         * @brief Checks if the value is a string.
         * @return @c true if the value is a string, else @c false.
         *
         * @see operator std::string()
         */
        bool is_string () const {
            return (myData->type == cJSON_String);
        }

        /*!
         * @brief Checks if the value is a list.
         * @return @c true if the value is a list, else @c false.
         *
         * @see List::List(const Any&)
         */
        bool is_list () const {
            return (myData->type == cJSON_Array);
        }

        /*!
         * @brief Checks if the value is a map.
         * @return @c true if the value is a map, else @c false.
         *
         * @see Map::Map(const Any&)
         */
        bool is_map () const {
            return (myData->type == cJSON_Object);
        }

        /* operators. */
    public:
        /*!
         * @brief Interpret the value as a boolean.
         * @return The underlying boolean value.
         *
         * @pre is_bool()
         * @throw std::bad_cast The value is not a boolean.
         */
        operator bool () const
        {
            switch (myData->type)
            {
                case cJSON_False: {
                    return (false);
                }
                case cJSON_True: {
                    return (true);
                }
                default: {
                    throw (std::bad_cast());
                }
            }
        }

        /*!
         * @brief Interpret the value as an integer.
         * @return The underlying integer value.
         *
         * @pre is_number()
         * @throw std::bad_cast The value is not a number.
         *
         * @see operator double()
         */
        operator int () const
        {
            if (!is_number()) {
                throw (std::bad_cast());
            }
            return (myData->valueint);
        }

        /*!
         * @brief Interpret the value as a real number.
         * @return The underlying real number.
         *
         * @pre is_number()
         * @throw std::bad_cast The value is not a number.
         *
         * @see operator int()
         */
        operator double () const
        {
            if (!is_number()) {
                throw (std::bad_cast());
            }
            return (myData->valuedouble);
        }

        /*!
         * @brief Interpret the value as a string.
         * @return The underlying string.
         *
         * @pre is_string()
         * @throw std::bad_cast The value is not a string.
         */
        operator std::string () const
        {
            if (!is_string()) {
                throw (std::bad_cast());
            }
            return (myData->valuestring);
        }
    };

    /*!
     * @brief Ordered group of values.
     *
     * @note Instances of this class must be entirely scoped within the
     *  lifetime of the root @c Document object from which they are extracted.
     */
    class List
    {
        /* data. */
    private:
        ::cJSON * myData;

        /* construction. */
    public:
        /*!
         * @internal
         * @brief Wraps the underlying implementation.
         * @param data Handle to the JSON data structure.
         *
         * @pre data->type == cJSON_Array
         * @throw std::bad_cast @a data does not hold a list.
         */
        explicit List (::cJSON * data)
            : myData(data)
        {
            if (myData->type != cJSON_Array) {
                throw (std::bad_cast());
            }
        }

        /*!
         * @brief Converts from a dynamically typed value.
         * @param object Value to interpret as a @c List.
         *
         * @pre object.is_list() == true
         * @throw std::bad_cast @a data does not hold a list.
         */
        List (const Any& object)
            : myData(object.data())
        {
            if (myData->type != cJSON_Array) {
                throw (std::bad_cast());
            }
        }

        /* methods. */
    public:
        /*!
         * @internal
         * @brief Access the underlying implementation.
         * @return Handle to the JSON data structure.
         */
        ::cJSON * data () const {
            return (myData);
        }

        /*!
         * @brief Obtain the number of items in the list.
         * @return Number of items in the list.
         */
        int size () const {
            return (::cJSON_GetArraySize(myData));
        }

        /* operators. */
    public:
        /*!
         * @brief Convert to dynamically typed value.
         */
        operator Any () const {
            return (Any(myData));
        }

        /*!
         * @brief Access a field by position.
         * @param key Position of the field to extract.
         * @return The field value.
         * @throw std::exception No field at position @a key.
         */
        Any operator[] (int key) const
        {
            ::cJSON *const item = ::cJSON_GetArrayItem(myData, key);
            if (item == 0) {
                throw (std::exception());
            }
            return (Any(item));
        }
    };

    /*!
     * @brief Group of named values.
     *
     * @note Instances of this class must be entirely scoped within the
     *  lifetime of the root @c Document object from which they are extracted.
     */
    class Map
    {
        /* data. */
    private:
        ::cJSON * myData;

        /* construction. */
    public:
        /*!
         * @internal
         * @brief Wraps the underlying implementation.
         * @param data Handle to the JSON data structure.
         *
         * @pre data->type == cJSON_Object
         * @throw std::bad_cast @a data does not hold a map.
         */
        explicit Map (::cJSON * data)
            : myData(data)
        {
            if (myData->type != cJSON_Object) {
                throw (std::bad_cast());
            }
        }

        /*!
         * @brief Converts from a dynamically typed value.
         * @param object Value to interpret as a @c Map.
         *
         * @pre object.is_map() == true
         * @throw std::bad_cast @a data does not hold a map.
         */
        Map (const Any& object)
            : myData(object.data())
        {
            if (myData->type != cJSON_Object) {
                throw (std::bad_cast());
            }
        }

        /* operators. */
    public:
        /*!
         * @internal
         * @brief Access the underlying implementation.
         * @return Handle to the JSON data structure.
         */
        ::cJSON * data () const {
            return (myData);
        }

        /*!
         * @brief Convert to dynamically typed value.
         */
        operator Any () const {
            return (Any(myData));
        }

        /*!
         * @brief Access a field by name.
         * @param key Name of the field to extract.
         * @return The field value.
         * @throw std::exception No field is named @a key.
         */
        Any operator[] (const std::string& key) const
        {
            ::cJSON *const item = ::cJSON_GetObjectItem(myData, key.c_str());
            if (item == 0) {
                throw (std::exception());
            }
            return (Any(item));
        }
    };

    /*!
     * @brief Parser, placeholder for document root object.
     *
     * @note Instances of this class must outlive the lifetime of @c Any, @c
     *  List and @c Map objects extracted from it.
     */
    class Document :
        public Map
    {
        /* class methods. */
    private:
        /*!
         * @internal
         * @brief Parse the JSON document in @a text.
         * @param text Serialized JSON document.
         * @return A handle to the JSON data structure.
         */
        static ::cJSON * parse (const std::string& text)
        {
            ::cJSON *const root = ::cJSON_Parse(text.c_str());
            if (root == 0) {
                // cJSON_GetErrorPtr()
                throw (std::exception());
            }
            return (root);
        }

        /* construction. */
    public:
        /*!
         * @brief Parse the JSON document in @a text.
         * @param text Serialized JSON document.
         */
        explicit Document (const std::string& text)
            : Map(parse(text.c_str()))
        {}

        /*!
         * @brief Release the memory held by the underlying data structure.
         */
        ~Document () {
            ::cJSON_Delete(data());
        }
    };

    // Forward declared.
    std::ostream& operator<< (std::ostream& stream, const Any& value);

    /*!
     * @brief Serialize @a list.
     * @param stream The output stream.
     * @param list The value to serialize.
     * @return @a stream
     */
    std::ostream& operator<< (std::ostream& stream, const List& list)
    {
        stream << '[';
        for (int i=0; (i < list.size()-1); ++i) {
            stream << list[i] << ',';
        }
        if (list.size() > 0) {
            stream << list[list.size()-1];
        }
        return (stream << ']');
    }

    /*!
     * @brief Serialize @a map.
     * @param stream The output stream.
     * @param map The value to serialize.
     * @return @a stream
     */
    std::ostream& operator<< (std::ostream& stream, const Map& map)
    {
        stream << '{';
        ::cJSON * node = map.data()->child;
        for (; (node != 0); node = node->next)
        {
            stream
                << "\"" << node->string << "\":" << Any(node);
            if (node->next != 0) {
                stream << ",";
            }
        }
        return (stream << '}');
    }

    /*!
     * @brief Serialize @a value.
     * @param stream The output stream.
     * @param value The value to serialize.
     * @return @a stream
     *
     * @bug Boolean values output depends on @c std::boolalpha and locale
     *  settings.  They should always be serialized as @c "true" and @c
     *  "false".
     * @bug Double quotes are not escaped in strings.
     */
    std::ostream& operator<< (std::ostream& stream, const Any& value)
    {
        if (value.is_null()) {
            return (stream << "null");
        }
        if (value.is_bool()) {
            // TODO: boolalpha?
            return (stream << bool(value));
        }
        if (value.is_number()) {
            return (stream << double(value));
        }
        if (value.is_string()) {
            // TODO: escape double quotes.
            return (stream << '"' << std::string(value) << '"');
        }
        if (value.is_list()) {
            return (stream << List(value));
        }
        if (value.is_map()) {
            return (stream << Map(value));
        }
        return (stream);
    }

}

#endif /* _json_hpp__ */
