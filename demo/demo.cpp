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

#include <json.hpp>
#include <iostream>

namespace {

    typedef int(*test)();

    int test_1 ()
    try
    {
        json::Document document("{\"foo\":[1,\"a\"], \"bar\": 1.1}");
        json::Map root(document);
        json::List foo = root["foo"];
        std::cout
            << "foo.size() -> " << foo.size() << "."
            << std::endl;
        for (int i=0; (i < foo.size()); ++i) {
            std::cout
                << "foo["<<i<<"]: " << foo[i] << "."
                << std::endl;
        }
        std::cout << "foo: " << foo << std::endl;
        std::cout << "document: " << root << std::endl;

        return (EXIT_SUCCESS);
    }
    catch (const std::exception& error)
    {
        std::cerr
            << "Test #1: "
            << error.what()
            << std::endl;
        return (EXIT_FAILURE);
    }

    int test_2 ()
    try
    {
        json::Document document("[{\"a\":1}, {\"a\":2}]");
        json::List root(document);
        for (int i=0; (i < root.size()); ++i) {
            const json::Map item = root[i];
            std::cout
                << " " << (i+1) << " -> " << item["a"] << "."
                << std::endl;
        }
        return (EXIT_SUCCESS);
    }
    catch (const std::exception& error)
    {
        std::cerr
            << "Test #2: "
            << error.what()
            << std::endl;
        return (EXIT_FAILURE);
    }

}

int main (int, char **)
try
{
    // List tests to run.
    static const test tests[] = {
        test_1,
        test_2,
    };
    static const int n = sizeof(tests) / sizeof(test);

    // Try to run all tests, fail fast!
    int status = EXIT_SUCCESS;
    for (int i=0; ((i < n) && (status == EXIT_SUCCESS)); ++i) {
        status = (*tests[i])();
    }
    return (status);
}
catch (const std::exception& error)
{
    std::cerr
        << "Error: '" << error.what() << "'."
        << std::endl;
    return (EXIT_FAILURE);
}
catch (...)
{
    std::cerr
        << "Unknown error."
        << std::endl;
    return (EXIT_FAILURE);
}
