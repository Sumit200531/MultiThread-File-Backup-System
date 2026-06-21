#include <iostream>
#include <fstream>
#include <filesystem>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>
#include<thread>
#include<vector>
#include<mutex>
#include "FileManager.h"

std::mutex logMutex;
std::mutex coutMutex;

void FileManager::start() {
 loadConfig();

    int choice;

    std::cout
        << "\n====================\n"
        << " File Backup System\n"
        << "====================\n"
        << "1. Create Backup\n"
        << "2. Restore Backup\n"
        << "3. Exit\n"
        << "Enter choice: ";

    std::cin >> choice;

    if(choice == 1)
    {
        scanDirectory();
        createBackup();
    }
    else if(choice == 2)
    {
        restoreBackup();
    }
    else if(choice == 3)
    {
        std::cout
            << "Exiting..."
            << std::endl;
    }
    else
    {
        std::cout
            << "Invalid choice!"
            << std::endl;
    }
}
void FileManager::loadConfig()
{
  std::ifstream file("config/config.txt");
  
  if(!file)
  {
    std::cout << "Config file not found ! " << std::endl;
   return;
  }
  
  getline(file,sourceFolder);
  std::cout << "Souce Folder loaded  "
  << sourceFolder 
  << std::endl; 

}

void FileManager::scanDirectory()
{
  

  std::cout << "\nScanning :" 
  << sourceFolder 
  << std::endl;
  

  
   for(const auto & entry :
          std::filesystem::recursive_directory_iterator(sourceFolder))
          {
            if(entry.is_regular_file()){

            std::cout
             << entry.path().filename().string()
            << std::endl;
          }
}
}

void FileManager::createBackup(){
    copiedCount  =0;
skippedCount = 0;
 std::string backupFolder =
           createTimeStampFolder();
  
std::vector<std::thread> threads;


      std::cout << "\nCreating backups...." << std::endl;

     for(const auto& entry : 
    std::filesystem::recursive_directory_iterator(sourceFolder))
  {
     if(entry.is_regular_file())
     {
      
     
auto relativePath =
std::filesystem::relative(
   entry.path(),
   sourceFolder
);

auto destination =
std::filesystem::path(backupFolder)
/relativePath;

std::filesystem::create_directories(
  destination.parent_path()
);



// creates a new thread , this thread will run instead
// of main program doing it




threads.emplace_back(
 &FileManager::copySingleFile,
    this,
  entry.path(),
  destination
);
     }
    }
  
for(auto &thread : threads){
  thread.join();
}
std::cout 
<< "\nBackup Completed\n"
<< "Files copied :"
<< copiedCount 
<< "\n Files Skipped : "
<< skippedCount 
<< std::endl;
}
  

void FileManager::writeLog(const std::string& action ,const std::string& fileName){
  
std::lock_guard<std::mutex> lock(logMutex);

  std::ofstream logFile(
    "logs/backup.log",
    std::ios::app
  );
auto now = std::chrono::system_clock::now();
std:: time_t currentTime = 
             std::chrono::system_clock::to_time_t(now);


  logFile
  << "["
  << std::put_time(
    std::localtime(&currentTime),
    "%Y-%m-%d %H:%M:%S"
  )

// %Y -> Year
// %m -> Month
// %d -> Day

// %H -> Hour (24-hour format)
// %M -> Minutes
// %S -> Seconds

  << "]"
  << action
  << " : "
  << fileName 
  << std::endl;
}

void FileManager::copySingleFile(




    const std::filesystem::path& source,
    const std::filesystem::path& destination
)
{

  if(std::filesystem::exists(destination))
  {
    auto sourceTime =
       std::filesystem::last_write_time(source);

       auto destinationTime =
       std::filesystem::last_write_time(destination);




       if(sourceTime <= destinationTime)
       {
        skippedCount++;

        writeLog(
          "SKIPPED",
          source.filename().string()
        );
        std::lock_guard<std::mutex> lock(coutMutex);
       
       std::cout
       << "Skippped : "
       << source.filename()
       << std::endl;

       return;
      }

  }
 
  if(std::filesystem::exists(destination))
  {
    std::filesystem::remove(destination);
  }

    std::filesystem::copy_file(
        source,
        destination
        
    );      
  
    copiedCount++;

    {
    std::lock_guard<std::mutex> lock(coutMutex);

    std::cout
        << "Copied : "
        << source.filename()
        << std::endl;
}
    
    writeLog(
      "COPIED",
        source.filename().string()
    );
   
}

std::string FileManager::createTimeStampFolder(){

 std::string folderName = "backups/current";
 
 std::filesystem::create_directories(
       folderName
 );
 return folderName;
}


void FileManager::restoreBackup()
{
  std::string backupFolder = "backups/current";

  std::cout
  << "\nRestoring Backup.."
  << std::endl;

  for(const auto &entry : 
          std::filesystem::recursive_directory_iterator(backupFolder))
          {
            if(entry.is_regular_file()){
              auto relativePath = 
              std::filesystem::relative(
                entry.path(),
                backupFolder
              );

              auto destination =
              std::filesystem::path(sourceFolder)
              / relativePath;

              std::filesystem::create_directories(
                destination.parent_path()
              );

              if(std::filesystem::exists(destination))
              {
                std::filesystem::remove(destination);
              }

               std::filesystem::copy_file(
                entry.path(),
                destination
            );

           
            std::cout
            << "Restored: "
            << relativePath 
            << std::endl;

             writeLog(
              "RESTORED",
              relativePath.string()
            );
            
            }
          }
          std::cout<<
       "\n Restore completed ! "
       << std::endl;
}