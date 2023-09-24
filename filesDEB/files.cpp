#include "files.h"

namespace fs = std::filesystem;

MyStructure :: MyStructure(std::string ste) {
	directory = ste;
	fs::path direct = directory;
	std::vector<std::string> folders{ "text", "Image", "video", "word", "excel", "exe", "Archives", "audio"};
	for (const std::string& folder : folders) {
		fs::path temp = directory + "//" + folder;
			if (!fs::exists(temp)) {
				fs::create_directories(temp);
			} else continue;
	}
}

std::vector<std::string> MyStructure::getNm(void)
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
		std::unordered_set<std::string> archiveFormats = { ".zip", ".rar", ".tar", ".7z", ".gz" };
		std::unordered_set<std::string> excelFormats = { ".xls", ".xlsx" };
		std::unordered_set<std::string> executableFormats = { ".exe", ".app", ".apk", ".deb", ".dmg", ".msi" };
		std::unordered_set<std::string> imageFormats = { ".jpg", ".jpeg", ".png", ".ico" , ".gif", ".bmp", ".tiff", ".tif", ".svg", ".psd"};
		std::unordered_set<std::string> textFormats = { ".txt", ".doc", ".docx", ".pdf", ".rtf", ".odt", ".html", ".htm", ".csv", ".xml", ".json", ".md" };
		std::unordered_set<std::string> videoFormats = { ".mp4", ".avi", ".mkv", ".mov", ".wmv", ".flv", ".webm" };
		std::unordered_set<std::string> wordFormats = { ".doc", ".docx", ".odt" };
		std::unordered_set<std::string> audioFiles = { ".mp3", ".wav", ".aac" };
		if (archiveFormats.find(extension) != archiveFormats.end()) {
			destinationFilepath = directory + "//Archives//" + name;
		}
		else if (excelFormats.find(extension) != excelFormats.end()) {
			destinationFilepath = directory + "//excel//" + name;
		}
		else if (executableFormats.find(extension) != executableFormats.end()) {
			destinationFilepath = directory + "//exe//" + name;
		}
		else if (imageFormats.find(extension) != imageFormats.end()) {
			destinationFilepath = directory + "//Image//" + name;
		}
		else if (textFormats.find(extension) != textFormats.end()) {
			destinationFilepath = directory + "//text//" + name;
		}
		else if (videoFormats.find(extension) != videoFormats.end()) {
			destinationFilepath = directory + "//video//" + name;
		}
		else if (wordFormats.find(extension) != wordFormats.end()) {
			destinationFilepath = directory + "//word//" + name;
		}

		else if (audioFiles.find(extension) != audioFiles.end()) {
			destinationFilepath = directory + "//audio//" + name;
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
