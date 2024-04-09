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

int main()
{
	setlocale(LC_ALL, "PL");
	bool empty, sameName, found, exit=0, quit = 0;
	std::vector<Task> tasks;


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

		std::cout << "q - Wyjdź" << std::endl;
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
									tasks[i].status = Do_zrobienia;
									break;
								case '2':
									tasks[i].status = W_trakcie;
									break;
								case '3':
									tasks[i].status = Zrobione;
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
				quit = 1;
				break;
			default:
				break;
		}
	}
}
