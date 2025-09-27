#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>

int main() {
    // File paths
    const char* inputFilePath = "cpp_results.txt";
    const char* outputFilePath = "assembly_results.html";

    // Open input file for reading
    std::ifstream inputFile(inputFilePath);
    if (!inputFile) {
        std::cerr << "Error: Could not open input file " << inputFilePath << std::endl;
        std::cerr << "Make sure cpp_results.txt exists in the current directory." << std::endl;
        std::cerr << "Run ASMtoCPP.exe first to generate the results file." << std::endl;
        return 1;
    }

    // Read entire content of input file
    std::stringstream buffer;
    buffer << inputFile.rdbuf();
    std::string fileContent = buffer.str();
    inputFile.close();

    // Check if file content is empty
    if (fileContent.empty()) {
        std::cerr << "Warning: Input file is empty!" << std::endl;
        fileContent = "No data found in cpp_results.txt\nPlease run ASMtoCPP.exe first to generate results.";
    }

    std::cout << "Read " << fileContent.length() << " characters from input file." << std::endl;

    // Get current timestamp
    std::time_t now = std::time(0);
    char timestamp[100];
    std::strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", std::localtime(&now));

    // Create HTML output file
    std::ofstream outputFile(outputFilePath);
    if (!outputFile) {
        std::cerr << "Error: Could not create output file " << outputFilePath << std::endl;
        return 1;
    }

    // Write HTML content
    outputFile << "<!DOCTYPE html>\n";
    outputFile << "<html lang=\"en\">\n";
    outputFile << "<head>\n";
    outputFile << "    <meta charset=\"UTF-8\">\n";
    outputFile << "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
    outputFile << "    <title>Assembly Program Results</title>\n";
    outputFile << "    <style>\n";
    outputFile << "        body {\n";
    outputFile << "            font-family: 'Courier New', monospace;\n";
    outputFile << "            max-width: 800px;\n";
    outputFile << "            margin: 40px auto;\n";
    outputFile << "            padding: 30px;\n";
    outputFile << "            background-color: #f8f9fa;\n";
    outputFile << "            line-height: 1.6;\n";
    outputFile << "        }\n";
    outputFile << "        .container {\n";
    outputFile << "            background-color: white;\n";
    outputFile << "            padding: 40px;\n";
    outputFile << "            border-radius: 8px;\n";
    outputFile << "            box-shadow: 0 2px 10px rgba(0,0,0,0.1);\n";
    outputFile << "        }\n";
    outputFile << "        h1 {\n";
    outputFile << "            color: #2c3e50;\n";
    outputFile << "            text-align: center;\n";
    outputFile << "            border-bottom: 3px solid #3498db;\n";
    outputFile << "            padding-bottom: 10px;\n";
    outputFile << "            margin-bottom: 30px;\n";
    outputFile << "        }\n";
    outputFile << "        .results-box {\n";
    outputFile << "            background-color: #f1f2f6;\n";
    outputFile << "            border: 2px solid #ddd;\n";
    outputFile << "            border-radius: 5px;\n";
    outputFile << "            padding: 20px;\n";
    outputFile << "            margin: 20px 0;\n";
    outputFile << "            white-space: pre-wrap;\n";
    outputFile << "            font-size: 14px;\n";
    outputFile << "        }\n";
    outputFile << "        .timestamp {\n";
    outputFile << "            text-align: right;\n";
    outputFile << "            color: #7f8c8d;\n";
    outputFile << "            font-size: 12px;\n";
    outputFile << "            margin-top: 20px;\n";
    outputFile << "        }\n";
    outputFile << "        .footer {\n";
    outputFile << "            text-align: center;\n";
    outputFile << "            margin-top: 30px;\n";
    outputFile << "            padding-top: 20px;\n";
    outputFile << "            border-top: 1px solid #ecf0f1;\n";
    outputFile << "            color: #95a5a6;\n";
    outputFile << "            font-size: 12px;\n";
    outputFile << "        }\n";
    outputFile << "        @media print {\n";
    outputFile << "            body { background-color: white; }\n";
    outputFile << "            .container { box-shadow: none; }\n";
    outputFile << "        }\n";
    outputFile << "    </style>\n";
    outputFile << "</head>\n";
    outputFile << "<body>\n";
    outputFile << "    <div class=\"container\">\n";
    outputFile << "        <h1>Assembly Program Output Report</h1>\n";
    outputFile << "        \n";
    outputFile << "        <div class=\"results-box\">\n";

    // Process and format the file content
    std::istringstream iss(fileContent);
    std::string line;
    while (std::getline(iss, line)) {
        // HTML escape special characters and preserve formatting
        std::string escapedLine = line;
        size_t pos = 0;
        while ((pos = escapedLine.find("&", pos)) != std::string::npos) {
            escapedLine.replace(pos, 1, "&amp;");
            pos += 5;
        }
        pos = 0;
        while ((pos = escapedLine.find("<", pos)) != std::string::npos) {
            escapedLine.replace(pos, 1, "&lt;");
            pos += 4;
        }
        pos = 0;
        while ((pos = escapedLine.find(">", pos)) != std::string::npos) {
            escapedLine.replace(pos, 1, "&gt;");
            pos += 4;
        }

        outputFile << escapedLine << "\n";
    }

    outputFile << "        </div>\n";
    outputFile << "        \n";
    outputFile << "        <div class=\"timestamp\">\n";
    outputFile << "            Generated on: " << timestamp << "\n";
    outputFile << "        </div>\n";
    outputFile << "        \n";
    outputFile << "        <div class=\"footer\">\n";
    outputFile << "            Assembly Program Results Converter<br>\n";
    outputFile << "            Source: cpp_results.txt\n";
    outputFile << "        </div>\n";
    outputFile << "    </div>\n";
    outputFile << "</body>\n";
    outputFile << "</html>\n";

    // Close output file
    outputFile.close();

    // Display success message
    std::cout << "HTML document successfully created!" << std::endl;
    std::cout << "Output file: " << outputFilePath << std::endl;
    std::cout << "You can open this file in:" << std::endl;
    std::cout << "  - Microsoft Word (File -> Open)" << std::endl;
    std::cout << "  - Any web browser" << std::endl;
    std::cout << "  - Print directly from the browser" << std::endl;

    return 0;
}