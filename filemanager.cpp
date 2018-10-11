#include <iostream>
#include <chrono>
#include <experimental\filesystem>
#include <fstream>
#include <string>
#include <unordered_map>
#include <conio.h>
#include <direct.h>

#pragma warning(disable : 4996)

namespace fs = std::experimental::filesystem;
fs::path p = fs::current_path();
std::string base = p.string();


int main()

{
	
	std::string command;
	std::string path1;
	std::string path2;

	const static std::unordered_map<std::string, int> string_to_case{
		{ "COPY",	1 },
		{ "DEL",	2 },
		{ "RENAME", 3 },
		{ "MKDIR",	4 },
		{ "CHDIR",	5 },
		{ "MOVE",	6 },
		{ "SHOW",	7 },
		{ "../",	8 },
		{ "?",		9 }
	};

	while (true) {
		std::cout << "<" << base << ">";
		std::cin >> command;

		switch (string_to_case.at(command))
		{
			case 1: // COPY
			{
				std::cin >> path1;
				std::cin >> path2;

				try {
					fs::copy(base + "\\" + path1,
						base + "\\" + path2,
						fs::copy_options::recursive);
				}
				catch (fs::filesystem_error& e) {
					try {
						fs::copy(path1,
							path2,
							fs::copy_options::recursive);
					}
					catch (fs::filesystem_error& e) {
						try {
							fs::copy(base + "\\" + path1,
								path2,
								fs::copy_options::recursive);
						}
						catch (fs::filesystem_error& e) {
							try {
								fs::copy(path1,
									base + "\\" + path2,
									fs::copy_options::recursive);
							}
							catch (fs::filesystem_error& e) {
								std::cout << e.what() << '\n';
							}
						}
					}
				}
				break;
			}
			case 2: //DEL
			{
				std::cin >> path1;
				try {
					fs::remove_all(base + "\\" + path1);
				}
				catch (fs::filesystem_error& e) {
					fs::remove_all(path1);
				}
				break;
			}
			case 3: //RENAME
			{
				std::cin >> path1;
				std::cin >> path2;
				try {
					fs::rename(base + "\\" + path1, base + "\\" + path2);
				}
				catch (fs::filesystem_error& e) {
					try {
						fs::rename(path1, path2);
					}
					catch (fs::filesystem_error& e) {
						try {
							fs::rename(base + "\\" + path1, path2);
						}
						catch (fs::filesystem_error& e) {
							try {
								fs::rename(path1, base + "\\" + path2);
							}
							catch (fs::filesystem_error& e) {
								std::cout << e.what() << '\n';
							}
						}
					}
				}
				break;
			}
			case 4: //MKDIR komandasi (folder yaratmaq)
			{
				std::cin >> path1;
				try {
					fs::create_directories(base + "\\" + path1);
				}
				catch (fs::filesystem_error& e) {
					try {
						fs::create_directories(path1);
					}
					catch (fs::filesystem_error& e) {
						std::cout << e.what() << '\n';
					}
				}
				break;
			}
			case 5: //CHDIR komandasi (current directory deyishmek uchun)
			{
				std::cin >> path1;
				base = path1;
				_chdir(base.c_str());
				break;
			}
			case 6: //MOVE
			{
				std::cin >> path1;
				std::cin >> path2;

				try {
					fs::rename(base + "\\" + path1, base + "\\" + path2);
				}
				catch (fs::filesystem_error& e) {
					try {
						fs::rename(path1, path2);
					}
					catch (fs::filesystem_error& e) {
						try {
							fs::rename(base + "\\" + path1, path2);
						}
						catch (fs::filesystem_error& e) {
							try {
								fs::rename(path1, base + "\\" + path2);
							}
							catch (fs::filesystem_error& e) {
								std::cout << e.what() << '\n';
							}
						}
					}
				}

				break;
			}
			case 7: //SHOW
			{
				for (auto p : fs::recursive_directory_iterator(base))
				{
					auto ftime = fs::last_write_time(p);
					std::time_t time = std::chrono::system_clock::to_time_t(ftime);
					std::cout << "Filename: " << p << '\n';
					if (!fs::is_directory(p)) {
						std::cout << "Size: " << (fs::file_size(p)) / 1024 << " kb , "
							<< (fs::file_size(p)) / 1024 / 1024 << " mb \n";
					}
					std::cout << "Last modified: " << std::asctime(std::localtime(&time)) << ' ';
				}
				break;
			}
			case 8: //CHDIR ../
			{
				std::size_t found = base.find_last_of("\\");
				base = base.substr(0, found);
				break;
			}
			case 9:
			{
				std::cout << "Please choose true command :\n";
				std::cout << "Delete : DEL_PATH\n";
				std::cout << "Copy : COPY_PATH1_PATH2\n";
				std::cout << "Rename : RENAME_FIRSTNAME_CHENGENAME\n";
				std::cout << "Create foler : MKDIR_FILENAME\n";
				std::cout << "Change base path : CHDIR_PATH\n";
				std::cout << "Move : MOVE_FOLDERNAME_SECONDNAME\n";
				std::cout << "Show in the folder : SHOW\n";
				break;
			}
		}
	}

	system("pause");

}