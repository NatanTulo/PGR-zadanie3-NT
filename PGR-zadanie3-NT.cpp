#include <iostream>
#include <vector>
#include <conio.h>
#include <string>
#include <fstream>
#include <sstream>

enum TaskStatus
{
	Do_zrobienia,
	W_trakcie,
	Zrobione
};

class Task
{
	public:
		int status;
		std::string name;
		std::string description;
		std::string deadline;
		std::vector<std::string> tags;
		std::vector<std::string> assigned;

		Task(std::string name, std::string description, std::string deadline, std::vector<std::string> tags, std::vector<std::string> assigned, int status = Do_zrobienia)
		{
			this->name = name;
			this->description = description;
			this->deadline = deadline;
			this->tags = tags;
			this->assigned = assigned;
			this->status = status;
		}
		void changeStatus(int status)
		{
			this->status = status;
		}
		void showTask()
		{
			std::cout << "Nazwa: " << name << std::endl;
			std::cout << "Opis: " << description << std::endl;
			std::cout << "Deadline: " << deadline << std::endl;
			std::cout << "Tagi: ";
			for (int i = 0; i < tags.size(); i++)
			{
				std::cout << tags[i];
				if (i != tags.size() - 1)
					std::cout << ", ";
			}
			std::cout << std::endl;
			std::cout << "Przypisani: ";
			for (int i = 0; i < assigned.size(); i++)
			{
				std::cout << assigned[i];
				if (i != assigned.size() - 1)
					std::cout << ", ";
			}
			std::cout << std::endl;
			std::cout << "Status: ";
			switch (status)
			{
				case Do_zrobienia:
					std::cout << "Do zrobienia" << std::endl;
					break;
				case W_trakcie:
					std::cout << "W trakcie" << std::endl;
					break;
				case Zrobione:
					std::cout << "Zrobione" << std::endl;
					break;
			}
		}
};

const char delimiter = char(134);
void saveTasksToFile(const std::vector<Task>& tasks, const std::string& filename)
{
	std::ofstream file(filename);
	if (!file)
	{
		std::cerr << "Nie można otworzyć pliku " << filename << std::endl;
		return;
	}

	for (const auto& task : tasks)
	{
		file << "Nazwa: " << task.name << "\n";
		file << "Opis: " << task.description << "\n";
		file << "Deadline: " << task.deadline << "\n";

		file << "Tagi: ";
		if (!task.tags.empty()) {
			file << task.tags[0];
			for (size_t i = 1; i < task.tags.size(); ++i)
				file << delimiter << task.tags[i];
		}
		file << "\n";

		file << "Przypisani: ";
		if (!task.assigned.empty()) {
			file << task.assigned[0];
			for (size_t i = 1; i < task.assigned.size(); ++i)
				file << delimiter << task.assigned[i];
		}
		file << "\n";

		file << "Status: ";
		switch (task.status)
		{
		case Do_zrobienia:
			file << "Do zrobienia";
			break;
		case W_trakcie:
			file << "W trakcie";
			break;
		case Zrobione:
			file << "Zrobione";
			break;
		}
		file << "\n\n";
	}

	file.close();
}

std::vector<Task> loadTasksFromFile(const std::string& filename)
{
	std::vector<Task> tasks;

	std::ifstream file(filename);
	if (!file)
	{
		std::cerr << "Nie można otworzyć pliku " << filename << std::endl;
		return tasks;
	}

	std::string line;
	TaskStatus status;

	while (std::getline(file, line))
	{
		if (line.find("Nazwa: ") == 0)
		{
			std::string name = line.substr(7);
			std::string description, deadline;
			std::vector<std::string> tags, assigned;

			for (int i = 0; i < 5; ++i)
			{
				std::getline(file, line);
				if (line.find("Opis: ") == 0)
					description = line.substr(6);
				else if (line.find("Deadline: ") == 0)
					deadline = line.substr(10);
				else if (line.find("Tagi: ") == 0)
				{
					std::stringstream ss(line.substr(6));
					std::string tag;
					while (std::getline(ss, tag, delimiter))
						tags.push_back(tag);
				}
				else if (line.find("Przypisani: ") == 0)
				{
					std::stringstream ss(line.substr(12));
					std::string assignee;
					while (std::getline(ss, assignee, delimiter))
						assigned.push_back(assignee);
				}
				else if (line.find("Status: ") == 0)
				{
					std::string statusStr = line.substr(8);
					if (statusStr == "Do zrobienia")
						status = Do_zrobienia;
					else if (statusStr == "W trakcie")
						status = W_trakcie;
					else if (statusStr == "Zrobione")
						status = Zrobione;
				}
			}

			tasks.emplace_back(name, description, deadline, tags, assigned, status);
		}
	}
	std::cout << "Pomyślnie wczytano " << tasks.size() << " zadań" << std::endl;
	file.close();

	return tasks;
}

int main()
{
	setlocale(LC_ALL, "PL");
	bool empty, sameName, found, exit=0, quit = 0;
	std::vector<Task> tasks = loadTasksFromFile("tasks.txt");

	std::string name;
	std::string description;
	std::string deadline;
	std::vector<std::string> tags;
	std::vector<std::string> assigned;
	std::string tag;
	std::string assign;
	int newstatus;

    while (!quit)
    {
		std::cout << "Menu" << std::endl;
		std::cout << "1 - Wyświetl zadania" << std::endl;
		std::cout << "2 - Dodaj zadanie" << std::endl;
		std::cout << "3 - Usuń zadanie" << std::endl;		
		std::cout << "4 - Edytuj zadanie" << std::endl;
		std::cout << "q - Zapisz i wyjdź" << std::endl;
		std::cout << "Naciśnij dowolny inny klawisz aby wyczyścić obraz i przywrócić menu" << std::endl << std::endl;
		char input = _getch();
		system("cls");
		switch (input)
		{
			case '1':
				std::cout << "Wyświetlanie zadań" << std::endl;
				for (int i = 0; i < tasks.size(); i++)
				{
					std::cout << "Zadanie " << i + 1 << ':' << std::endl;
					tasks[i].showTask();
					std::cout << std::endl;
				}
				if(tasks.size() == 0)
					std::cout << "Brak zadań" << std::endl << std::endl;
				break;
			case '2':
				system("cls");
				std::cout << "Dodawanie zadania\n* oznacza obowiązkowe pole" << std::endl << std::endl;

				std::cout << "*Podaj unikalną nazwę zadania: ";
				do
				{
					sameName = 0;
					empty = 0;
					std::getline(std::cin, name);
					if (name.size() == 0)
					{
						std::cout << "Nie podano nazwy zadania\n*Podaj nazwę zadania: ";
						empty = 1;
					}
					for (int i = 0; i < tasks.size(); i++)
					{
						if (tasks[i].name == name)
						{
							std::cout << "Zadanie o podanej nazwie już istnieje\n*Podaj nazwę zadania: ";
							sameName = 1;
							break;
						}
					}
				} while (sameName || empty);

				std::cout << "*Podaj deadline zadania: ";
				std::getline(std::cin, deadline);
				while (deadline.size() == 0)
				{
					std::cout << "Nie podano deadline'u\n*Podaj deadline zadania: ";
					std::getline(std::cin, deadline);
				}

				empty = 0;
				std::cout << "*Podaj przypisanych do zadania:\nZatwierdź przypisanego klawiszem enter, pozostaw puste pole jeśli chcesz zakończyć wpisywanie przypisanych" << std::endl;
				for (int i = 1; !empty; i++)
				{
					std::cout << i << ". ";
					std::getline(std::cin, assign);
					if (assign.size() != 0)
						assigned.push_back(assign);
					else
					{
						if (i < 2)
						{
							std::cout << "Nie podano przypisanego\nPodaj przypisanych do zadania: " << std::endl;
							--i;
						}
						else
							empty = 1;
					}
				}

				std::cout << "Podaj opis zadania: ";
				std::getline(std::cin, description);

				std::cout << "Podaj tagi zadania:\nZatwierdź tag klawiszem enter, pozostaw puste pole jeśli chcesz zakończyć wpisywanie tagów" << std::endl;
				empty = 0;
				for(int i = 1; !empty; i++)
				{
					std::cout << i <<". ";
					std::getline(std::cin, tag);
					if (tag.size() != 0)
						tags.push_back(tag);
					else
						empty = 1;
				}
				
				tasks.push_back(Task(name, description, deadline, tags, assigned));
				tags.clear();
				assigned.clear();
				std::cout << "Dodano zadanie" << std::endl << std::endl;
				break;
			case '3':
				std::cout << "Usuwanie zadania" << std::endl;
				for (int i = 0; i < tasks.size(); i++)
					std::cout << "Zadanie " << i + 1 << ": " << tasks[i].name << std::endl;
				std::cout << "Podaj nazwę zadania do usunięcia: ";
				found = 0;
				std::cin >> name;
				for (int i = 0; i < tasks.size(); i++)
				{
					if (tasks[i].name == name)
					{
						tasks.erase(tasks.begin() + i);
						std::cout << "Usunięto podane zadanie" << std::endl<<std::endl;
						found = 1;
						break;
					}
				}
				if (!found)
					std::cout << "Nie znaleziono zadania o podanej nazwie" << std::endl << std::endl;
				break;
			case '4':
				exit=0;
				while (!exit) {
					system("cls");
					std::cout << "Edytowanie zadania\n* oznacza obowiązkowe pole" << std::endl;
					for (int i = 0; i < tasks.size(); i++)
						std::cout << "Zadanie " << i + 1 << ": " << tasks[i].name << std::endl;
					std::cout << "Aby wyjść, zatwierdź puste pole\nPodaj nazwę zadania do edycji: ";
					found = 0;
					std::getline(std::cin, name);
					if(name.size() == 0)
						exit = 1;
					for (int i = 0; i < tasks.size(); i++)
					{
						if (tasks[i].name == name)
						{
							tasks[i].showTask();
							std::cout << "\nWybierz element do edycji:\n1 - Nazwa\n2 - Opis\n3 - Deadline\n4 - Tagi\n5 - Przypisani\n6 - Status\n0 - Wyjście\n";
							input = _getch();
							switch (input)
							{
							case '1':
								std::cout << "Podaj nową unikalną nazwę zadania: ";
								do
								{
									sameName = 0;
									empty = 0;
									std::getline(std::cin, name);
									if (name.size() == 0)
									{
										std::cout << "Nie podano nazwy zadania\n*Podaj nazwę zadania: ";
										empty = 1;
									}
									for (int j = 0; j < tasks.size(); j++)
									{
										if (tasks[j].name == name)
										{
											std::cout << "Zadanie o podanej nazwie już istnieje\n*Podaj nazwę zadania: ";
											sameName = 1;
											break;
										}
									}
								} while (sameName || empty);
								tasks[i].name = name;
								break;
							case '2':
								std::cout << "Podaj nowy opis: ";
								std::getline(std::cin, description);
								tasks[i].description = description;
								break;
							case '3':
								std::cout << "*Podaj nowy deadline: ";
								std::getline(std::cin, deadline);
								while (deadline.size() == 0)
								{
									std::cout << "Nie podano deadline'u\n*Podaj deadline zadania: ";
									std::getline(std::cin, deadline);
								}
								tasks[i].deadline = deadline;
								break;
							case '4':
								std::cout << "Podaj nowe tagi:\nZatwierdź tag klawiszem enter, pozostaw puste pole jeśli chcesz zakończyć wpisywanie tagów" << std::endl;
								empty = 0;
								for (int i = 1; !empty; i++)
								{
									std::cout << i << ". ";
									std::getline(std::cin, tag);
									if (tag.size() != 0)
										tags.push_back(tag);
									else
										empty = 1;
								}
								tasks[i].tags = tags;
								tags.clear();
								break;
							case '5':
								std::cout << "*Podaj nowych przypisanych:\nZatwierdź przypisanego klawiszem enter, pozostaw puste pole jeśli chcesz zakończyć wpisywanie przypisanych" << std::endl;
								empty = 0;
								for (int i = 1; !empty; i++)
								{
									std::cout << i << ". ";
									std::getline(std::cin, assign);
									if (assign.size() != 0)
										assigned.push_back(assign);
									else
									{
										if (i < 2)
										{
											std::cout << "Nie podano przypisanego\nPodaj przypisanych do zadania: " << std::endl;
											--i;
										}
										else
											empty = 1;
									}
								}
								tasks[i].assigned = assigned;
								assigned.clear();
								break;
							case '6':
								std::cout << "Podaj nowy status:\n1 - Do zrobienia\n2 - W trakcie\n3 - Zrobione\n";
								newstatus = _getch();
								switch (newstatus)
								{
								case '1':
									tasks[i].changeStatus(Do_zrobienia);
									break;
								case '2':
									tasks[i].changeStatus(W_trakcie);
									break;
								case '3':
									tasks[i].changeStatus(Zrobione);
									break;
								default:
									break;
								}
								break;
							case '0':
								exit = 1;
								break;
							default:
								break;
							}
							found = 1;
							break;
						}
					}
					if (!found&&name.size()!=0)
						std::cout << "Nie znaleziono zadania o podanej nazwie" << std::endl;
				}
				break;
			case 'q':
				saveTasksToFile(tasks, "tasks.txt");
				std::cout << "Zapisano zmiany i zakończono program" << std::endl;
				quit = 1;
				break;
			default:
				break;
		}
	}
}