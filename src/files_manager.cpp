#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "files_manager.hpp"
#include "nucleo/estruturas.hpp"

const char* ACRONYMS[27] = {
    "AC","AL","AM","AP","BA","CE","DF","ES","GO","MA","MG","MS","MT",
    "PA","PB","PE","PI","PR","RJ","RN","RO","RR","RS","SC","SE","SP","TO"
};

typedef struct idxSocial {
    int iSexo = -1;
    int iTipoEM = -1;
    int iTreineiro = -1;
    int iSitEM = -1; 
    int iCor = -1;
    int iNac = -1;
    int iFaixa = -1;
    int iOcupPai = -1;
    int iOcupMae = -1;
    int iRenda = -1;
    int iQnt = -1;
    int iUF = -1;
} ColunsSocialIndex;

ReturnCode send(uint8_t moduleId, Request requestCode) {
    return ReturnCode::UNEXPECTEDERROR;
}

ReturnCode send(uint8_t moduleId) {
    return ReturnCode::UNEXPECTEDERROR;
}

Request receive(uint8_t moduleId) {
    Request r{};
    return r;
}

ReturnCode receiveResponse(uint8_t moduleId) {
    return ReturnCode::UNEXPECTEDERROR;
}

int getTotalEntrants(uint8_t year, uint8_t uf) {
    if(year < 24 || year > 25) return -1;
    
    std::ifstream file("files/enem_social_header_" + std::to_string((int)year) + ".dat", std::ios::binary);
    if(!file.is_open()) return -1;

    if(uf == 255) {
        int sum = 0;
        for(int i = 0; i < 27; i++) {
            int value;
            file.read((char*) &value, sizeof(int));
            sum += value;
        }
        file.close();
        return sum;
    } else {
        int value;
        file.seekg(uf * sizeof(int));
        file.read((char*) &value, sizeof(int));
        file.close();
        return value;
    }
}

ReturnCode returnData(uint8_t moduleId) {
    return ReturnCode::UNEXPECTEDERROR;
}

int toInt(const std::string& s) {
    if(s.empty()) return -1;
    char* end = nullptr;
    long v = std::strtol(s.c_str(), &end, 10);
    return (*end == '\0') ? (int)v : -1;
}

int letterToInt(const std::string& s) {
    if(s.size() != 1 || s[0] < 'A' || s[0] > 'Z') return -1;
    return s[0] - 'A';
}

int ufIndex(const std::string& sigla) {
    for(int i = 0; i < 27; i++)
        if(sigla == ACRONYMS[i]) return i;
    return 27;
}

uint8_t code(int value, int maxValid, uint8_t missing) {
    return (value >= 0 && value <= maxValid) ? (uint8_t)value : missing;
}

Personal createPersonal(const std::string &line, std::string &uf, ColunsSocialIndex indexes) {
    std::stringstream ss(line);
    std::string field;
    Personal p{};
    
    int count = 0;
    while (std::getline(ss, field, ';')) {
        if(count == indexes.iCor) PersonalData::SetRace(p.participante, code(toInt(field), 5, 0));
        else if(count == indexes.iFaixa) PersonalData::SetAge(p.participante, code(toInt(field), 20, 20));
        else if(count == indexes.iNac) PersonalData::SetNationality(p.participante, code(toInt(field), 4, 0));
        else if(count == indexes.iOcupMae) PersonalData::SetMotherOcup(p.socioeconomico, (uint8_t)letterToInt(field));
        else if(count == indexes.iOcupPai) PersonalData::SetFatherOcup(p.socioeconomico, (uint8_t)letterToInt(field));
        else if(count == indexes.iQnt) PersonalData::SetHouseQnt(p.socioeconomico, (uint8_t)toInt(field));
        else if(count == indexes.iRenda) PersonalData::SetWealth(p.socioeconomico, (uint8_t)letterToInt(field));
        else if(count == indexes.iSexo) PersonalData::SetSex(p.participante, field == "F");
        else if(count == indexes.iSitEM) PersonalData::SetSchoolSituation(p.participante, (uint8_t)(toInt(field) - 1)); // Está sendo armazenado só com 2 bits
        else if(count == indexes.iTipoEM) PersonalData::SetSchoolType(p.participante, toInt(field) == 2);
        else if(count == indexes.iTreineiro) PersonalData::SetTrainee(p.participante, toInt(field) == 1);
        else if(count == indexes.iUF) uf = field;
        count++;
    }
    return p;
}

bool fileVerification(const std::string &line, ColunsSocialIndex &indexes) {
    std::stringstream ss(line);
    std::string data;
    int count = 0;
    while(std::getline(ss, data, ';')) {     
        if(data == "TP_FAIXA_ETARIA") indexes.iFaixa = count;
        else if(data == "TP_SEXO") indexes.iSexo = count;
        else if(data == "TP_COR_RACA") indexes.iCor = count;
        else if(data == "TP_NACIONALIDADE") indexes.iNac = count;
        else if(data == "IN_TREINEIRO") indexes.iTreineiro = count;
        else if(data == "TP_ENSINO") indexes.iTipoEM = count;
        else if(data == "TP_ST_CONCLUSAO") indexes.iSitEM = count;
        else if(data == "Q003") indexes.iOcupPai = count;
        else if(data == "Q004") indexes.iOcupMae = count;
        else if(data == "Q005") indexes.iQnt = count;
        else if(data == "Q007") indexes.iRenda = count;
        else if(data == "SG_UF_PROVA") indexes.iUF = count;
        count++;
    }

    return indexes.iSexo != -1 && indexes.iSitEM != -1 && indexes.iOcupMae != -1 && indexes.iTreineiro != -1 &&
        indexes.iCor != -1 && indexes.iFaixa != -1 && indexes.iOcupPai != -1 && indexes.iTipoEM != -1 &&
        indexes.iNac != -1 && indexes.iRenda != -1 && indexes.iQnt != -1 && indexes.iUF != -1;
}

ReturnCode initializeDataFile(std::string path, uint8_t year, uint8_t fileType) {
    if(year > 25 || year < 24) return ReturnCode::BADREQUEST;

    std::ifstream rawFile(path);
    if(!rawFile.is_open()) return ReturnCode::FILEERROR;

    std::string line;
    if(!std::getline(rawFile, line)) return ReturnCode::FILEERROR;
    if(line.compare(0, 3, "\xEF\xBB\xBF") == 0) line.erase(0, 3);

    if(!fileType) { // Social
        ColunsSocialIndex indexes;
        if(!fileVerification(line, indexes)) return ReturnCode::BADREQUEST;         

        std::ofstream newFile("files/enem_social_" + std::to_string((int)year) + ".dat", std::ios::binary);
        if(!newFile.is_open()) return ReturnCode::FILEERROR;

        std::vector<Personal> matrix[28];
        int amountByState[28] = {};
        while(std::getline(rawFile, line)) {
            if(line.empty()) continue;
            std::string uf;
            Personal personalData = createPersonal(line, uf, indexes);

            int pos = ufIndex(uf);
            matrix[pos].push_back(personalData);
            amountByState[pos]++;
        }

        for(int i = 0; i < 28; i++) {
            while(matrix[i].size() > 0) {
                newFile.write((const char*) &matrix[i].back(), sizeof(Personal));
                matrix[i].pop_back();
            }
        }

        std::ofstream headerFile("files/enem_social_header_" + std::to_string((int)year) + ".dat", std::ios::binary);
        if(!headerFile.is_open()) return ReturnCode::FILEERROR;
        for(int i = 0; i < 27; i++) {
            headerFile.write((const char*) &amountByState[i], sizeof(int));
        }

        headerFile.close();
        newFile.close();
        return newFile.fail() || headerFile.fail() ? ReturnCode::FILEERROR : ReturnCode::SUCCESS;
    } else { // Resultados

        return ReturnCode::UNEXPECTEDERROR;
    }
}