#include <iostream>
#include <fstream>
#include <iomanip>
#include <bitset>

int main() {
    // File paths

    const char* inputFilePath = "output.bin";
    const char* outputFilePath = "cpp_results.txt";

    // Variables to store the output values
    unsigned char output1 = 0;
    unsigned char counter = 0;

    // Open the binary file for reading
    fopen(inputFilePath, "rb");  //this uses absolute path
    printf("Attempting to open: %s\n", inputFilePath);
    
    std::ifstream inputFile(inputFilePath, std::ios::binary);
    if (!inputFile) {
        std::cerr << "Error: Could not open input file " << inputFilePath << std::endl;
        return 1;
    }

    // Read the values from the file
    inputFile.read(reinterpret_cast<char*>(&output1), sizeof(output1));
    inputFile.read(reinterpret_cast<char*>(&counter), sizeof(counter));

    // Close the input file
    inputFile.close();

    // Display the values to console
    std::cout << "Output1: " << static_cast<int>(output1) << std::endl;
    std::cout << "Counter: " << static_cast<int>(counter) << std::endl;

    // Create and write to output file
    std::ofstream outputFile(outputFilePath);
    if (!outputFile) {
        std::cerr << "Error: Could not create output file " << outputFilePath << std::endl;
        return 1;
    }

    // Write formatted results to the output file
    outputFile << "Assembly Program Results" << std::endl;
    outputFile << "========================" << std::endl;
    outputFile << "Output1: " << static_cast<int>(output1) << std::endl;
    outputFile << "Counter: " << static_cast<int>(counter) << std::endl;
    outputFile << std::endl;
    outputFile << "Raw byte values:" << std::endl;
    outputFile << "Output1 (hex): 0x" << std::hex << std::uppercase
        << static_cast<int>(output1) << std::endl;
    outputFile << "Counter (hex): 0x" << std::hex << std::uppercase
        << static_cast<int>(counter) << std::endl;

    // Close the output file
    outputFile.close();

    std::cout << std::endl << "Results have been written to: " << outputFilePath << std::endl;

    return 0;
}