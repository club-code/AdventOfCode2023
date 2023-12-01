#include "inputReader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <array>

#include <curl/curl.h>

constexpr size_t MAX_LINE_SIZE = 256;

std::vector<std::string> readInputFromFile(std::string const& path) {
    std::fstream inputFile;
    inputFile.open(path, std::ios::in);
    if (!inputFile.is_open()) {
        std::cerr << "Could not open the file " << path << std::endl;
        throw std::invalid_argument("Could not open the file " + path);
    }
    std::string line;
    std::vector<std::string> res;
    while (std::getline(inputFile, line)) {
        res.push_back(line.substr(0, line.find('\r')));
    }
    std::cout << "File successfully read.\n";

    return res;
}

std::vector<std::string> readInputFromURL(std::string const& url) {
	CURL* curl;
	CURLcode res;
    std::istringstream readBuffer;

    curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_SSLVERSION, CURL_SSLVERSION_TLSv1_2);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

    if (curl) {
		res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
			std::cerr << "Could not open the file " << url << std::endl;
			throw std::invalid_argument("Could not open the file " + url);
		}
		curl_easy_cleanup(curl);
	}
	std::cout << "File successfully read.\n";

    std::vector<std::string> input;

    for (std::array<char, MAX_LINE_SIZE> a; readBuffer.getline(&a[0], MAX_LINE_SIZE);) {
        input.emplace_back(&a[0]);
    }

	return input;
}