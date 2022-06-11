//
// Created by sergey on 21.05.22.
//

#ifndef LAB_23__2_MONITOR_H
#define LAB_23__2_MONITOR_H


#include <sys/stat.h>
#include "State.h"
#include "observable.h"

class FileMonitor : public Observable< FileObserver > {
public:
    FileMonitor( const char* fileName );

    void checkFile();

private:
    static FileState getFileState( const std::string& fileName );

private:
    std::string m_fileName;
    FileState m_prevFileState;
};

FileMonitor::FileMonitor( const char* fileName ) :
        m_fileName( fileName ), m_prevFileState( getFileState( m_fileName ) ) {
}

void FileMonitor::checkFile() {
    FileState fileState = getFileState( m_fileName );
    if( fileState != m_prevFileState ) {
        notifyObservers( &FileObserver::onFileChanged, fileState );
        m_prevFileState = fileState;
    }
}

FileState FileMonitor::getFileState( const std::string& fileName ) {
    FileState fileState;
    struct stat statBuf;
    fileState.exists = stat( fileName.c_str(), &statBuf ) == 0;
    fileState.size = fileState.exists ? statBuf.st_size : 0;
    return fileState;
}

#endif //LAB_23__2_MONITOR_H
