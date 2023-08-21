#pragma once

#include <iostream>

#define LOG_ERROR(text)                           \
    std::cout << "[ERROR] " << text << std::endl; \
    std::exit(1)

template<class BidirectionalIteratorT, class GetterT>
void printList(BidirectionalIteratorT begin,
               BidirectionalIteratorT end,
               GetterT getItem,
               std::string_view separator = ", ")
{
    auto lastItem = end;
    --lastItem;

    for (auto iterator = begin; iterator != lastItem; ++iterator)
    {
        std::cout << getItem(*iterator) << separator;
    }

    std::cout << getItem(*lastItem);
}
