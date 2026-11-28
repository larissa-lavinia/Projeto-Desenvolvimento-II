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

typedef struct idxResults {
    int iUF = -1;
    int iResCN = -1;
    int iResCH = -1;
    int iResLC = -1;
    int iResMT = -1;
    int iLang = -1;
    int iGabCN = -1;
    int iGabCH = -1;
    int iGabLC = -1;
    int iGabMT = -1;
    int iRed = -1;
} ColunsResultsIndex;

ReturnCode returnData(Request request);

ReturnCode module4Execution(uint8_t cod) {
    if(!cod) {
        return ReturnCode::UNEXPECTEDERROR;
    } else {
        Request r = receive(4);

        return returnData(r);
    }
}

ReturnCode send(uint8_t moduleId, Request requestCode) {
    // módulos válidos: 1 a 5
    if(moduleId < 1 || moduleId > 5) return ReturnCode::BADREQUEST;

    // arquivo de conexão do módulo receptor
    std::string path = "files/connection" + std::to_string((int)moduleId) + ".dat";

    std::ofstream connection(path, std::ios::binary | std::ios::trunc);
    if(!connection.is_open()) return ReturnCode::FILEERROR;

    // grava a requisição como veio (id do emissor, ano, estado e dado)
    connection.write((const char*)&requestCode, sizeof(Request));
    connection.close();

    return connection.fail() ? ReturnCode::FILEERROR : ReturnCode::SUCCESS;
}

Request receive(uint8_t moduleId) {
    std::string nomeArquivo = "files/connection" + std::to_string((int)moduleId) + ".dat";

    std::ifstream arquivoConexao(nomeArquivo, std::ios::binary);

    if(!arquivoConexao.is_open()) {
        return Request{};
    }

    Request r{};

    if(!arquivoConexao.read((char*)(&r), sizeof(Request))) {
        arquivoConexao.close();
        return Request{};
    }

    if(r.id < 1 || r.id > 5 || r.id == 4) {
        arquivoConexao.close();
        return Request{};
    }

    if(r.year != 24 && r.year != 25) {
        arquivoConexao.close();
        return Request{};
    }

    if(r.state < 0 || r.state > 26) {
        arquivoConexao.close();
        return Request{};
    }

    if(r.requiredData < 0 || r.requiredData > 11) {
        arquivoConexao.close();
        return Request{};
    }

    arquivoConexao.close();

    return r;
}

int getTotalEntrants(uint8_t year, uint8_t uf) {
    if(year < 24 || year > 25) return -1;

    std::ifstream file("files/enem_social_header_" + std::to_string((int)year) + ".dat", std::ios::binary);
    if(!file.is_open()) return -1;

    if(uf == 255) {
        int sum = 0;
        for(int i = 0; i < 27; i++) {
            int value;
            file.read((char*)&value, sizeof(int));
            sum += value;
        }
        file.close();
        return sum;
    } else {
        int value;
        file.seekg(uf * sizeof(int));
        file.read((char*)&value, sizeof(int));
        file.close();
        return value;
    }
}

int getPosition(std::ifstream& file, uint8_t year, uint8_t uf) {
    if(uf == 255) return 0;
    int amount = 0;
    for(int i = 0; i < uf; i++) {
        amount += getTotalEntrants(year, i);
    }
    return amount * sizeof(Personal);
}

ReturnCode returnData(Request request) {
    if(request.id < 1 || request.id > 5) return ReturnCode::BADREQUEST;
    if(request.requiredData > 6) return ReturnCode::BADREQUEST;
    if(request.state > 26 && request.state != 255) return ReturnCode::BADREQUEST;

    std::ifstream dataFile;
    std::ifstream headerFile;
    if(request.requiredData <= 1) {
        dataFile.open("files/enem_social_" + std::to_string((int)request.year) + ".dat", std::ios::binary);
        headerFile.open("files/enem_social_header_" + std::to_string((int)request.year) + ".dat", std::ios::binary);
        if(!dataFile.is_open() || !headerFile.is_open()) return ReturnCode::FILEERROR;
    } else {
        dataFile.open("files/enem_results_" + std::to_string((int)request.year) + ".dat", std::ios::binary);
        headerFile.open("files/enem_results_header_" + std::to_string((int)request.year) + ".dat", std::ios::binary);
        if(!dataFile.is_open() || !headerFile.is_open()) return ReturnCode::FILEERROR;
    }
    std::ofstream responseFile("files/connection" + std::to_string((int)request.id) + ".dat", std::ios::binary);
    if(!responseFile.is_open()) return ReturnCode::FILEERROR;

    int amount = getTotalEntrants(request.year, request.state);
    dataFile.seekg(getPosition(headerFile, request.year, request.state));

    switch(request.requiredData) {
    case 0: { // participante
        for(int i = 0; i < amount; i++) {
            Personal personalData;
            dataFile.read((char*)&personalData, sizeof(Personal));
            responseFile.write((const char*)&personalData.participante, sizeof(uint16_t));
        }
        break;
    }
    case 1: { // socioeconomico
        for(int i = 0; i < amount; i++) {
            Personal personalData;
            dataFile.read((char*)&personalData, sizeof(Personal));
            responseFile.write((const char*)&personalData.socioeconomico, sizeof(uint16_t));
        }
        break;
    }
    case 2: { // essay
        for(int i = 0; i < amount; i++) {
            Score scoreData;
            dataFile.read((char*)&scoreData, sizeof(Score));
            responseFile.write((const char*)&scoreData.essay, sizeof(uint16_t));
        }
        break;
    }
    case 3: { // Mat
        for(int i = 0; i < amount; i++) {
            Score scoreData;
            dataFile.read((char*)&scoreData, sizeof(Score));
            responseFile.write((const char*)&scoreData.exam[0], sizeof(AreaScore));
        }
        break;
    }
    case 4: { // C_Ex
        for(int i = 0; i < amount; i++) {
            Score scoreData;
            dataFile.read((char*)&scoreData, sizeof(Score));
            responseFile.write((const char*)&scoreData.exam[1], sizeof(AreaScore));
        }
        break;
    }
    case 5: { // C_Hu
        for(int i = 0; i < amount; i++) {
            Score scoreData;
            dataFile.read((char*)&scoreData, sizeof(Score));
            responseFile.write((const char*)&scoreData.exam[2], sizeof(AreaScore));
        }
        break;
    }
    case 6: { // Lin
        for(int i = 0; i < amount; i++) {
            Score scoreData;
            dataFile.read((char*)&scoreData, sizeof(Score));
            responseFile.write((const char*)&scoreData.exam[3], sizeof(AreaScore));
        }
        break;
    }
    }
    dataFile.close();
    headerFile.close();
    responseFile.close();
    return dataFile.fail() || headerFile.fail() || responseFile.fail() ? ReturnCode::FILEERROR : ReturnCode::SUCCESS;
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

AreaScore createAreaScore(const std::string& answers, const std::string& key) {
    AreaScore a{}; 
    if((int)answers.size() < 45 || (int)key.size() < 45) return a;

    for(int i = 0; i < 45; i++) {
        bool hit = (answers[i] == key[i]); 
        uint16_t& word = (i < 16) ? a.p1 : (i < 32) ? a.p2 : a.p3;
        Bit::SetBit(word, i % 16, hit);
    }
    Bit::SetBit(a.p3, 15, false);
    return a;
}

void compressLCResponses(std::string &key, uint8_t type) {
    if(!type) { // inglês
        key.erase(5, 5);
    } else {
        key.erase(0, 5);
    }
}

Score createScore(const std::string& line, std::string& uf, ColunsResultsIndex indexes) {
    std::stringstream ss(line);
    std::string field;
    Score s{};
    std::string sequences[8];

    int count = 0, lang;
    while(std::getline(ss, field, ';')) {
        if(count == indexes.iResCN) sequences[0] = field;
        else if(count == indexes.iResCH) sequences[1] = field;
        else if(count == indexes.iResLC) sequences[2] = field;
        else if(count == indexes.iResMT) sequences[3] = field;
        else if(count == indexes.iGabCN) sequences[4] = field;
        else if(count == indexes.iGabCH) sequences[5] = field;
        else if(count == indexes.iGabLC) sequences[6] = field;
        else if(count == indexes.iGabMT) sequences[7] = field;
        else if(count == indexes.iLang) lang = (uint8_t)toInt(field);
        else if(count == indexes.iRed) s.essay = (uint8_t)toInt(field);
        else if(count == indexes.iUF) uf = field;
        count++;
    }
    compressLCResponses(sequences[2], lang);
    s.exam[0] = createAreaScore(sequences[7], sequences[3]);
    s.exam[1] = createAreaScore(sequences[4], sequences[0]);
    s.exam[2] = createAreaScore(sequences[5], sequences[1]);
    s.exam[3] = createAreaScore(sequences[6], sequences[2]);
    return s;
}

Personal createPersonal(const std::string& line, std::string& uf, ColunsSocialIndex indexes) {
    std::stringstream ss(line);
    std::string field;
    Personal p{};

    int count = 0;
    while(std::getline(ss, field, ';')) {
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

bool fileVerification(const std::string& line, ColunsSocialIndex& indexes, ColunsResultsIndex& ResIndexes, uint8_t type) {
    std::stringstream ss(line);
    std::string data;
    int count = 0;
    if(!type) {
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
    } else {
        while(std::getline(ss, data, ';')) {
            if(data == "TX_RESPOSTAS_CN") ResIndexes.iResCN = count;
            else if(data == "TX_RESPOSTAS_CH") ResIndexes.iResCH = count;
            else if(data == "TX_RESPOSTAS_LC") ResIndexes.iResLC = count;
            else if(data == "TX_RESPOSTAS_MT") ResIndexes.iResMT = count;
            else if(data == "TP_LINGUA") ResIndexes.iLang = count;
            else if(data == "TX_GABARITO_CN") ResIndexes.iGabCN = count;
            else if(data == "TX_GABARITO_CH") ResIndexes.iGabCH = count;
            else if(data == "TX_GABARITO_LC") ResIndexes.iGabLC = count;
            else if(data == "TX_GABARITO_MT") ResIndexes.iGabMT = count;
            else if(data == "NU_NOTA_REDACAO") ResIndexes.iRed = count;
            else if(data == "SG_UF_PROVA") ResIndexes.iUF = count;
            count++;
        }
        
        return ResIndexes.iResCN != -1 && ResIndexes.iResCH != -1 && ResIndexes.iResLC != -1 && ResIndexes.iResMT
            && ResIndexes.iLang != -1 && ResIndexes.iGabCN != -1 && ResIndexes.iGabCH != -1 && ResIndexes.iGabLC
            && ResIndexes.iGabMT != -1 && ResIndexes.iRed != -1;
    }

}

ReturnCode initializeDataFile(std::string path, uint8_t year, uint8_t fileType) {
    if(year > 25 || year < 24) return ReturnCode::BADREQUEST;

    std::ifstream rawFile(path);
    if(!rawFile.is_open()) return ReturnCode::FILEERROR;

    std::string line;
    if(!std::getline(rawFile, line)) return ReturnCode::FILEERROR;
    if(line.compare(0, 3, "\xEF\xBB\xBF") == 0) line.erase(0, 3);

    ColunsSocialIndex indexesS;
    ColunsResultsIndex indexesR;
    if(!fileType) { // Social
        if(!fileVerification(line, indexesS, indexesR, 0)) return ReturnCode::BADREQUEST;

        std::ofstream newFile("files/enem_social_" + std::to_string((int)year) + ".dat", std::ios::binary);
        if(!newFile.is_open()) return ReturnCode::FILEERROR;

        std::vector<Personal> matrix[28];
        int amountByState[28] = {};
        while(std::getline(rawFile, line)) {
            if(line.empty()) continue;
            std::string uf;
            Personal personalData = createPersonal(line, uf, indexesS);

            int pos = ufIndex(uf);
            matrix[pos].push_back(personalData);
            amountByState[pos]++;
        }

        for(int i = 0; i < 28; i++) {
            while(matrix[i].size() > 0) {
                newFile.write((const char*)&matrix[i].back(), sizeof(Personal));
                matrix[i].pop_back();
            }
        }

        std::ofstream headerFile("files/enem_social_header_" + std::to_string((int)year) + ".dat", std::ios::binary);
        if(!headerFile.is_open()) return ReturnCode::FILEERROR;
        for(int i = 0; i < 27; i++) {
            headerFile.write((const char*)&amountByState[i], sizeof(int));
        }

        headerFile.close();
        newFile.close();
        return newFile.fail() || headerFile.fail() ? ReturnCode::FILEERROR : ReturnCode::SUCCESS;
    } else { // Resultados
        if(!fileVerification(line, indexesS, indexesR, 1)) return ReturnCode::BADREQUEST;

        std::ofstream newFile("files/enem_results_" + std::to_string((int)year) + ".dat", std::ios::binary);
        if(!newFile.is_open()) return ReturnCode::FILEERROR;

        std::vector<Score> matrix[28];
        int amountByState[28] = {};
        while(std::getline(rawFile, line)) {
            if(line.empty()) continue;
            std::string uf;
            Score scoreData = createScore(line, uf, indexesR);

            int pos = ufIndex(uf);
            matrix[pos].push_back(scoreData);
            amountByState[pos]++;
        }

        for(int i = 0; i < 28; i++) {
            while(matrix[i].size() > 0) {
                newFile.write((const char*)&matrix[i].back(), sizeof(Score));
                matrix[i].pop_back();
            }
        }

        std::ofstream headerFile("files/enem_results_header_" + std::to_string((int)year) + ".dat", std::ios::binary);
        if(!headerFile.is_open()) return ReturnCode::FILEERROR;
        for(int i = 0; i < 27; i++) {
            headerFile.write((const char*)&amountByState[i], sizeof(int));
        }
        headerFile.close();
        newFile.close();
        return newFile.fail() || headerFile.fail() ? ReturnCode::FILEERROR : ReturnCode::SUCCESS;
    }
}