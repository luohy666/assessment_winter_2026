#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>

int main() {
    std::string path;
    std::getline(std::cin, path);
    std::ifstream file(path);
  
    int info_cnt = 0, warn_cnt = 0, error_cnt = 0;
    long long total_ms = 0;
    int max_ms = -1;
    std::string max_line;

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::istringstream iss(line);
        std::string level;
        int ms;
        if (!(iss >> level >> ms)) continue;

        if (level == "INFO") ++info_cnt;
        else if (level == "WARN") ++warn_cnt;
        else if (level == "ERROR") ++error_cnt;
        else continue;

        total_ms += ms;

        if (ms > max_ms) {
            max_ms = ms;
            max_line = level + " " + std::to_string(ms);
        }
      }
      

    file.close();

    int total_lines = info_cnt + warn_cnt + error_cnt;
    double avg = total_lines > 0 ? static_cast<double>(total_ms) / total_lines : 0.0;

    std::cout << "INFO=" << info_cnt << "\n";
    std::cout << "WARN=" << warn_cnt << "\n";
    std::cout << "ERROR=" << error_cnt << "\n";
    std::cout << std::fixed << std::setprecision(2) << "avg=" << avg << "\n";
    std::cout << "max=" << max_line << "\n";

    return 0;
}