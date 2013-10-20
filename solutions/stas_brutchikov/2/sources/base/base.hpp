#ifndef BASE__BASE_HPP
#define BASE__BASE_HPP
#pragma once

namespace task2
{
    template<typename Type, int size>
    struct fix_array
    {
        typedef Type type[size];
    };

    template<typename InStream, typename Type>
    inline void ReadValue(InStream& in, Type& t)
    {
         in.read(reinterpret_cast<char*>(&t), sizeof(Type));
    }

    template<typename OutStream, typename Type>
    inline void WriteValue(OutStream& out, const Type& t)
    {
         out.write(reinterpret_cast<const char*>(&t), sizeof(Type));
    }
} //task2

#endif BASE__BASE_HPP