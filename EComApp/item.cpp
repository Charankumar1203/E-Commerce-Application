#include "global.h"
#include "item.h"

item item::returnCopy(){
    item it;
    it.name = name;
    it.price = price;
    it.count = count;
    return it;
}