#include "files_manager.hpp"

ReturnCode send(uint8_t moduleId, Request requestCode) {
    return ReturnCode::UNEXPECTEDERROR;
}

ReturnCode send(uint8_t moduleId) {
    return ReturnCode::UNEXPECTEDERROR;
}

ReturnCode receive(uint8_t moduleId) {
    return ReturnCode::UNEXPECTEDERROR;
}

ReturnCode receiveResponse(uint8_t moduleId) {
    return ReturnCode::UNEXPECTEDERROR;
}

int getTotalEntrants(uint8_t year) {
    return 0;
}

ReturnCode getByYear(uint8_t moduleId) {
    return ReturnCode::UNEXPECTEDERROR;
}

ReturnCode getByState(uint8_t moduleId) {
    return ReturnCode::UNEXPECTEDERROR;
} 

ReturnCode initializeDataFile(std::string path, uint8_t year, uint8_t fileType) {
    return ReturnCode::UNEXPECTEDERROR;
}

ReturnCode getTotalEntrants() {
    return ReturnCode::UNEXPECTEDERROR;
}

