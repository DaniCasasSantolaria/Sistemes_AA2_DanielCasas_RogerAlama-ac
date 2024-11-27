#include "ICodable.h"

ICodable::DecodeMap* ICodable::GetDecodeMap() {
    static DecodeMap* map = new DecodeMap();

    return map;
}

std::string ICodable::GetDecodeKey() {
    return "ICodableType";
    //return "ICT";
}

void ICodable::SaveDecodeProcess(std::string className, SubClassDecode decodeProcess) {
    GetDecodeMap()->emplace(className, decodeProcess);
}