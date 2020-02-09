#include <iostream>
#include <fstream>
#include "mqEngine/MesgQEngine.h"

const int PROCESS_RUNNING = 1;

int main(int argc, char **argv) {
    try {
        MesgQEngine init;
        std::thread consumer(&MesgQEngine::worker, MesgQEngine());
        std::this_thread::sleep_for(std::chrono::seconds(2));

        if (argc < 2) {
            std::cout << "Please provide your query" << std::endl;
            std::string message;
            while (PROCESS_RUNNING) {
                std::cin >> message;
                std::this_thread::sleep_for(std::chrono::seconds(2));
                MesgQEngine::onMessage(message);
            }
        } else {

            std::string fileName = argv[1];
            std::ifstream myFile(fileName);
            std::string line;
            if (myFile.is_open()) {
                while (std::getline(myFile, line)) {
                    std::cout << line << std::endl;
                    MesgQEngine::onMessage(line);
                }
            } else {
                std::cout << "enable to open file" << std::endl;
            }
        }
        while (PROCESS_RUNNING) {
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    }
    catch (std::exception &e) {
        std::cout << e.what() << std::endl;

    }
    catch (...) {
        std::cout << "Error:un-handled exception " << __FILE__ << ":" << __LINE__ << std::endl;
    }
    return 0;
}
