//
// Created by NAT20 on 07/12/2023.
//

#ifndef CORE_H
#define CORE_H

#include <stdio.h>
#include <memory>
#include <vector>
#include <map>
#include <unordered_map>

namespace Framework
{
    template<typename T>
    using Uptr = std::unique_ptr<T>;

    template<typename T>
    using Sptr = std::shared_ptr<T>;

    template<typename T>
    using Wptr = std::weak_ptr<T>;

    template<typename T>
    using Vec = std::vector<T>;

    template<typename a_keyType, typename a_valueType, typename a_predicate = std::less<a_keyType>>
    using Map = std::map<a_keyType, a_valueType, a_predicate>; // a map is slower but it's ordered.

    template<typename a_keyType, typename a_valueType, typename a_hasher = std::hash<a_keyType>>
    using UMap = std::unordered_map<a_keyType, a_valueType, a_hasher>; // a hash map or dictionary is faster than a map but it's unordered.


#define GE_LOG(x, ...) printf(x "\n", ##__VA_ARGS__), fflush(stdout) // This is a macro, the 2 ## are for when there are no arguments, it will still compile.
}




#endif //CORE_H
