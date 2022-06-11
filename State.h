//
// Created by sergey on 21.05.22.
//

#ifndef LAB_23__2_STATE_H
#define LAB_23__2_STATE_H
#include <iostream>
#include <chrono>
#include <thread>
#include <ctime>
struct FileState {
    bool operator!=( const FileState& other ) {
        if( this == &other ) {
            return false;
        }
        return exists != other.exists || size != other.size;
    }

    bool exists;
    size_t size;
};

class FileObserver {
public:
    virtual ~FileObserver() { }

    virtual void onFileChanged( const FileState& state ) = 0;
};
class ConsoleFileObserver : public FileObserver {
public:
    ~ConsoleFileObserver();

    void onFileChanged( const FileState& state );
};

void ConsoleFileObserver::onFileChanged( const FileState& state ) {
    time_t seconds = time(NULL);
    tm* timeinfo = localtime(&seconds);
    std::cout<< " Состояние файла изменилось: " <<asctime(timeinfo)<<std::endl;
    std::cout << "  Существует: " << state.exists << std::endl;
    std::cout << "  Размер: " << state.size << std::endl;
    std::cout << std::endl << std::endl;
}

ConsoleFileObserver::~ConsoleFileObserver() {
}
#endif //LAB_23__2_STATE_H
