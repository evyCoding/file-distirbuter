#include "files.h"

namespace fs = std::filesystem;

MyStructure :: MyStructure(std::string ste) {
	directory = ste;
	fs::path direct = directory;
	std::vector<std::string> folders{ "text", "Image", "video", "word", "excel", "exe", "Archives"};
	for (const std::string& folder : folders) {
		fs::path temp = directory + "//" + folder;
			if (!fs::exists(temp)) {
				fs::create_directories(temp);
			} else continue;
	}
}

std::vector<std::string> MyStructure::getNm()
{
	std::vector<std::string> filesnames{};
	for (const auto& entry : fs::directory_iterator(directory)) {
				if (entry.is_regular_file()) {
					std::string fil = (entry.path().filename()).string();
					filesnames.push_back(fil);
				}
				else continue;
	}
	return filesnames;
}

void MyStructure::dister() {
	std::vector <std::string> filenames = this->getNm();
	if (filenames.empty())
		return;
	for (auto& name : filenames) {
		fs::path sourceFilepath = directory + "//" + name;
		std::string extension = sourceFilepath.extension().string();
		fs::path destinationFilepath;
		std::vector<std::string> archiveFormats = { ".zip", ".rar", ".tar", ".7z", ".gz" };
		std::vector<std::string> excelFormats = { ".xls", ".xlsx" };
		std::vector<std::string> executableFormats = { ".exe", ".app", ".apk", ".deb", ".dmg", ".msi" };
		std::vector<std::string> imageFormats = { ".jpg", ".jpeg", ".png", ".ico" , ".gif", ".bmp", ".tiff", ".tif", ".svg", ".psd"};
		std::vector<std::string> textFormats = { ".txt", ".doc", ".docx", ".pdf", ".rtf", ".odt", ".html", ".htm", ".csv", ".xml", ".json", ".md" };
		std::vector<std::string> videoFormats = { ".mp4", ".avi", ".mkv", ".mov", ".wmv", ".flv", ".webm" };
		std::vector<std::string> wordFormats = { ".doc", ".docx", ".odt" };

		if (std::find(archiveFormats.begin(), archiveFormats.end(), extension) != archiveFormats.end()) {
			destinationFilepath = directory + "//Archives//" + name;
		}
		else if (std::find(excelFormats.begin(), excelFormats.end(), extension) != excelFormats.end()) {
			destinationFilepath = directory + "//excel//" + name;
		}
		else if (std::find(executableFormats.begin(), executableFormats.end(), extension) != executableFormats.end()) {
			destinationFilepath = directory + "//exe//" + name;
		}
		else if (std::find(imageFormats.begin(), imageFormats.end(), extension) != imageFormats.end()) {
			destinationFilepath = directory + "//Image//" + name;
		}
		else if (std::find(textFormats.begin(), textFormats.end(), extension) != textFormats.end()) {
			destinationFilepath = directory + "//text//" + name;
		}
		else if (std::find(videoFormats.begin(), videoFormats.end(), extension) != videoFormats.end()) {
			destinationFilepath = directory + "//video//" + name;
		}
		else if (std::find(wordFormats.begin(), wordFormats.end(), extension) != wordFormats.end()) {
			destinationFilepath = directory + "//word//" + name;
		}

		if (!destinationFilepath.empty()) {
			try {
				fs::rename(sourceFilepath, destinationFilepath);
			} catch (std::exception& ex) { std::cout << "eRRor" << ex.what(); }
			
		}
		else {
			std::cout << "This file type is not recognized." << std::endl;
		}
	}
}
