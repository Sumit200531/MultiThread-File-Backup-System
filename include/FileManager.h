#include<string>
#include<filesystem>
#include<atomic>
#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

class FileManager
 {
 private:
 std::string sourceFolder;
 std::atomic<int> copiedCount{0};
 std::atomic<int> skippedCount{0};


 public:
 void copySingleFile(
    const std::filesystem::path& source,
    const std::filesystem::path& destination
 );
    void start();
    void scanDirectory();
    void createBackup();
      void restoreBackup();
    void loadConfig();

    void writeLog(
      const std::string& action,
   const std::string& fileName 
);
   
    std::string createTimeStampFolder();

 

   };

#endif
