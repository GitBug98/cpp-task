#include <iostream>
#include <fstream>
#include <thread>
#include <vector>

using namespace std;

class Logger
{
private:
    ofstream logFile;

    Logger()
    {
        logFile.open("logfile.txt", ios::app);
        if (!logFile.is_open())
        {
            cerr << "Failed to open log file" << endl;
        }
    }

    ~Logger()
    {
        if (logFile.is_open())
        {
            logFile.close();
        }
    }

public:
    static Logger &getInstance()
    {
        static Logger instance;
        return instance;
    }

    Logger(const Logger &) = delete;
    Logger &operator=(const Logger &) = delete;

    void log(const string &message)
    {
        logFile << message << endl;
    }
};

void logMessages(int id)
{
    for (int i = 0; i < 5; ++i)
    {
        Logger::getInstance().log("Thread " + to_string(id) + " - Message " + to_string(i));
    }
}

int main()
{
    cout << "Starting logging..." << endl;
    cout << "Enter the number of threads: ";
    int numberOfThreads;
    cin >> numberOfThreads;
    cout << endl;
    vector<thread> threads(numberOfThreads);

    for (int i = 0; i < numberOfThreads; i++)
    {
        threads[i] = thread(logMessages, i);
    }

    for (int i = 0; i < numberOfThreads; i++)
    {
        threads[i].join();
    }

    cout << "Logging complete. Check logfile.txt for results." << endl;
    return 0;
}