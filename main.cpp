
#include "logger.h"



int main()
{
	double goal; // minimum time needed for patients
	vector<record> patient;
	cout << endl << endl;
	cout << "     _____ _                _" << endl;
	cout << "    |_   _(_)_ __ ___   ___| |    ___   __ _  __ _  ___ _ __" << endl;
	cout << "      | | | | '_ ` _ \\ / _ \\ |   / _ \\ / _` |/ _` |/ _ \\ '__|" << endl;
	cout << "      | | | | | | | | | ___/ |__| (_) | (_| | (_| |  __/ |" << endl;
	cout << "      |_| |_|_| |_| |_|\\___|_____\\___/ \\__, |\\__, |\\___|_|" << endl;
	cout << "                                       |___/ |___/" << endl << endl << endl;

	cout << "CAUTION: Do not exit the program with the \"X\" in the top right corner" << endl;
	cout << "         of the screen as this will cause all unsaved data to be lost." << endl << endl << endl << endl;
	cout << "         If the program is ever terminated this way, DO NOT re-open this" << endl;
	cout << "         program as all recovery data will be overwritten. Instead, run" << endl;
	cout << "         the program \"recovery.exe\" which will restore all files." << endl << endl << endl << endl;
	system("pause");
	system("cls");

	read(patient, goal);
	menu(patient, goal);
	return 0;
}

void menu(vector<record> &p, double &goal)
{
	char choice;
	record temp;
	bool sorted = true;

	do
	{
		instructions();
		cout << endl << "Time goal: " << goal << " (Minutes)" << endl << endl;
		cout << "What would you like to do?" << endl;
		
		cin >> choice;
		tolower(choice);

		switch (choice)
		{
		case 'n':
			p.push_back(create());
			sorted = false;
			while (sorted == false)
			{
				sorted = true;
				for (unsigned int i = 0; i < p.size()-1; i++)
				{
					if (strcmp(p.at(i).first, p.at(i + 1).first) > 0)
					{
						temp = p.at(i);
						p.at(i) = p.at(i + 1);
						p.at(i + 1) = temp;
						sorted = false;
					}
				}
			}
			break;
		case 'd':
			display(p, 0, goal);
			system("pause");
			break;
		case 'r':
			remove(p);
			sorted = false;
			while (sorted == false)
			{
				sorted = true;
				for (unsigned int i = 0; i < p.size()-1; i++)
				{
					if (strcmp(p.at(i).first, p.at(i + 1).first) > 0)
					{
						temp = p.at(i);
						p.at(i) = p.at(i + 1);
						p.at(i + 1) = temp;
						sorted = false;
					}
				}
			}
			break;
		case 'g':
			system("cls");
			cout << "Pick a new time goal" << endl;
			cin >> (double)goal;
			break;
		case 't':
			timer(p, goal);
			break;
		case 's':
			write(p, goal);
			system("cls");
			cout << "all changes have been saved" << endl;
			system("pause");
			break;
		case 'x':
			display(p, 1, goal);
			system("pause");
			break;
		case 'p':
			display(p, 1, goal);
			cout << endl << "The above patients are to be sent to patients.txt for printing" << endl;
			pwrite(p, goal);
			system("pause");
			break;
		case 'c':
			change(p, goal);
			sorted = false;
			while (sorted == false)
			{
				sorted = true;
				for (unsigned int i = 0; i < p.size() - 1; i++)
				{
					if (strcmp(p.at(i).first, p.at(i + 1).first) > 0)
					{
						temp = p.at(i);
						p.at(i) = p.at(i + 1);
						p.at(i + 1) = temp;
						sorted = false;
					}
				}
			}
			break;
		case 'z':
			system("cls");
			cout << "Are you sure that you want to reset the recorded time for all patients" << endl;
			cout << "back to zero? (type \"y\" for yes or \"n\" for no)" << endl;

			cin >> choice;
			tolower(choice);
			cout << endl;

			if (choice == 'y')
			{
				for (unsigned int i = 0; i < p.size(); i++)
				{
					p.at(i).time = 0;
					p.at(i).edit = false;
				}
				cout << "The times for all patients have been successfully reset to zero" << endl;
			}
			else
				cout << "The times for all patients have been left unchanged." << endl;
			system("pause");
			break;
		default:
			;
		}
		system("cls");

		swrite(p,goal);
	} while (choice != 'e');

	write(p, goal);

	return;
	
}

record create()
{
	record n;
	n.time = 0;
	
	
	cout << endl << "Enter the patient's first name" << endl;
	
	cin >> n.first;

	cout << endl << "Enter the patient's last name" << endl;

	cin >> n.last;

	cout << endl << "Enter the patient's birthdate (MMDDYYYY)" << endl;

	cin >> n.bdate;
	


	return n;
}

void display(vector<record> p, int dtype, double goal)
{
	system("cls");
	cout << "* denotes a patient whos information has been changed since the last reset." << endl << endl;
	cout << left << setw(20) << left << "First name" << left <<
		setw(20) << left << setw(20) << left << "Last name" <<
		left << setw(20) << left << setw(20) << left << "Birthdate" <<
		left << setw(20) << left << setw(20) << left << "Time (Minutes)" << left << setw(20) << endl << endl;

	if (dtype == 0)
	{
		for (unsigned int i = 0; i < p.size(); i++)
		{
			if (p.at(i).time > goal)
			{
				cout << left << setw(20) << left << p.at(i).first <<
					left << setw(20) << left << setw(20) << left << p.at(i).last <<
					left << p.at(i).bdate[0] << p.at(i).bdate[1] <<
					"/" << p.at(i).bdate[2] << p.at(i).bdate[3] << "/" << p.at(i).bdate[4] <<
					p.at(i).bdate[5] << p.at(i).bdate[6] << setw(11) << p.at(i).bdate[7] <<
					left << setw(20) << left << setw(1) << left << goal << left << setw(20);
				if (p.at(i).edit == true)
					cout << '*' << endl;
				else
					cout << endl;
			}
			else
			{
				cout << left << setw(20) << left << p.at(i).first <<
					left << setw(20) << left << setw(20) << left << p.at(i).last <<
					left << p.at(i).bdate[0] << p.at(i).bdate[1] <<
					"/" << p.at(i).bdate[2] << p.at(i).bdate[3] << "/" << p.at(i).bdate[4] <<
					p.at(i).bdate[5] << p.at(i).bdate[6] << setw(11) << p.at(i).bdate[7] <<
					left << setw(20) << left << setw(1) << left << p.at(i).time << left << setw(20);
				if (p.at(i).edit == true)
					cout << '*' << endl;
				else
					cout << endl;
			}
		}
	}

	if (dtype == 1)
	{
		for (unsigned int i = 0; i < p.size(); i++)
		{
			if (p.at(i).time < goal)
			{
				cout << left << setw(20) << left << p.at(i).first <<
					left << setw(20) << left << setw(20) << left << p.at(i).last <<
					left << p.at(i).bdate[0] << p.at(i).bdate[1] <<
					"/" << p.at(i).bdate[2] << p.at(i).bdate[3] << "/" << p.at(i).bdate[4] <<
					p.at(i).bdate[5] << p.at(i).bdate[6] << setw(11) << p.at(i).bdate[7] <<
					left << setw(20) << left << setw(1) << left << p.at(i).time << left << setw(20);
				if (p.at(i).edit == true)
					cout << '*' << endl;
				else
					cout << endl;
			}
		}
	}

	return;
}

void instructions()
{
	cout << "d - displays all patients and time" << endl;
	cout << "n - creates a new patient record" << endl;
	cout << "r - removes a patient record" << endl;
	cout << "g - changes the time goal" << endl;
	cout << "t - times a patient" << endl;
	cout << "x - displays all patients who have less time than the current goal" << endl;
	cout << "p - sends all patients who have less time than the current goal to a .txt file to be printed" << endl;
	cout << "z - resets all the recorded time for patients back to zero" << endl;
	cout << "c - changes a patient's information" << endl;
	cout << "s - saves all changes" << endl;
	cout << "e - exit" << endl;

}

void remove(vector<record> &p)
{
	string fname, lname, bday;

	cout << endl << "what is the first name on the file you want to remove?" << endl;

	cin >> fname;

	cout << endl;
	cout << "* denotes a patient whos information has been changed since the last reset." << endl << endl;
	cout << left << setw(20) << left << "First name" << left <<
		setw(20) << left << setw(20) << left << "Last name" <<
		left << setw(20) << left << setw(20) << left << "Birthdate" <<
		left << setw(20) << left << setw(20) << left << "Time (Minutes)" << left << setw(20) << endl << endl;


	for (unsigned int i = 0; i < p.size(); i++)
	{
		if (fname == p.at(i).first)
		{
			cout << left << setw(20) << left << p.at(i).first <<
				left << setw(20) << left << setw(20) << left << p.at(i).last <<
				left << p.at(i).bdate[0] << p.at(i).bdate[1] <<
				"/" << p.at(i).bdate[2] << p.at(i).bdate[3] << "/" << p.at(i).bdate[4] <<
				p.at(i).bdate[5] << p.at(i).bdate[6] << setw(11) << p.at(i).bdate[7] <<
				left << setw(20) << left << setw(1) << left << p.at(i).time << left << setw(20);
			if (p.at(i).edit == true)
				cout << '*' << endl;
			else
				cout << endl;
		}
	}

	cout << endl << "what is the last name on the file you would like to remove?" << endl;

	cin >> lname;
	cout << endl;

	for (unsigned int i = 0; i < p.size(); i++)
	{
		if (fname == p.at(i).first && lname == p.at(i).last)
		{
			cout << left << setw(20) << left << p.at(i).first <<
				left << setw(20) << left << setw(20) << left << p.at(i).last <<
				left << p.at(i).bdate[0] << p.at(i).bdate[1] <<
				"/" << p.at(i).bdate[2] << p.at(i).bdate[3] << "/" << p.at(i).bdate[4] <<
				p.at(i).bdate[5] << p.at(i).bdate[6] << setw(11) << p.at(i).bdate[7] <<
				left << setw(20) << left << setw(1) << left << p.at(i).time << left << setw(20);
			if (p.at(i).edit == true)
				cout << '*' << endl;
			else
				cout << endl;
		}
	}

	cout << endl << "what is the birthdate on the file you would like to remove? (mmddyyyy)" << endl;

	cin >> bday;

	for (unsigned int i = 0; i < p.size(); i++)
	{
		if (fname == p.at(i).first && lname == p.at(i).last && bday == p.at(i).bdate)
		{
			p.erase(p.begin() + i);
			system("cls");
			cout << "The patient's record was deleted" << endl << endl;
			system("pause");
			return;
		}
	}
	cout << endl << "No record of that patient was found" << endl;
	system("pause");

	return;
}

void timer(vector<record> &p, double goal)
{
	string fname, lname, bday;
	double mins;
	clock_t start;

	system("cls");
	cout << "What is the first name of the patient you would like to time?" << endl;

	cin >> fname;
	
	cout << endl;

	cout << "* denotes a patient whos information has been changed since the last reset." << endl << endl;
	cout << left << setw(20) << left << "First name" << left <<
		setw(20) << left << setw(20) << left << "Last name" <<
		left << setw(20) << left << setw(20) << left << "Birthdate" <<
		left << setw(20) << left << setw(20) << left << "Time (Minutes)" << left << setw(20) << endl << endl;


	for (unsigned int i = 0; i < p.size(); i++)
	{
		if (fname == p.at(i).first)
		{
			cout << left << setw(20) << left << p.at(i).first <<
				left << setw(20) << left << setw(20) << left << p.at(i).last <<
				left << p.at(i).bdate[0] << p.at(i).bdate[1] <<
				"/" << p.at(i).bdate[2] << p.at(i).bdate[3] << "/" << p.at(i).bdate[4] <<
				p.at(i).bdate[5] << p.at(i).bdate[6] << setw(11) << p.at(i).bdate[7] <<
				left << setw(20) << left << setw(1) << left << p.at(i).time << left << setw(20);
			if (p.at(i).edit == true)
				cout << '*' << endl;
			else
				cout << endl;
		}
	}

	cout << endl << "what is the last name of the patient you would like to time?" << endl;

	cin >> lname;
	cout << endl;

	for (unsigned int i = 0; i < p.size(); i++)
	{
		if (fname == p.at(i).first && lname == p.at(i).last)
		{
			cout << left << setw(20) << left << p.at(i).first <<
				left << setw(20) << left << setw(20) << left << p.at(i).last <<
				left << p.at(i).bdate[0] << p.at(i).bdate[1] <<
				"/" << p.at(i).bdate[2] << p.at(i).bdate[3] << "/" << p.at(i).bdate[4] <<
				p.at(i).bdate[5] << p.at(i).bdate[6] << setw(11) << p.at(i).bdate[7] <<
				left << setw(20) << left << setw(1) << left << p.at(i).time << left << setw(20);
			if (p.at(i).edit == true)
				cout << '*' << endl;
			else
				cout << endl;
		}
	}

	cout << endl << "what is the birthdate on the file you would like to remove? (mmddyyyy)" << endl;

	cin >> bday;

	for (unsigned int i = 0; i < p.size(); i++)
	{
		if (fname == p.at(i).first && lname == p.at(i).last && bday == p.at(i).bdate)
		{
			system("cls");
			cout << "Patient: " << p.at(i).first << " " << p.at(i).last << " " << p.at(i).bdate[0]
				 << p.at(i).bdate[1] << "/" << p.at(i).bdate[2] << p.at(i).bdate[3] << "/" << p.at(i).bdate[4] 
				 << p.at(i).bdate[5] << p.at(i).bdate[6] << p.at(i).bdate[7] << endl << endl;
			cout << "Push any key to start timing" << endl;
			system("pause");
			cout << "\a";
			start = clock();
			cout << endl << endl << endl << "Timing in process" << endl << endl << endl << endl << "Push ENTER to stop timing" << endl;
			cin.ignore();
			cin.ignore();
			cout << "\a";

			mins = ((clock() - start) / (double)CLOCKS_PER_SEC) / 60.0;

			
			p.at(i).time += mins;
			system("cls");
			cout << "Patient's record has been updated" << endl << endl;
			system("pause");
			return;
		}
	}

	cout << endl << "No patient could be found by that name" << endl;
	system("pause");

	return;
}

void read(vector<record> &p, double &goal)
{
	ifstream fin;
	int n; // number of records
	record temp;

	fin.open("times.bin", ios::in | ios::binary);
	
	if (!fin) // || !sfile is needed in statement
	{
		cout << "Error! Either file \"times.bin\" or \"s_times.bin\" cannot open or is missing from the program directory." << endl;
		fin.close();
		//		sfile.close();
		return;
	}


	fin.seekg(0, ios::end);

	if ((int)fin.tellg() == 0)
	{
		fin.close();
		goal = 0;
		return;
	}

	n = ((int)fin.tellg() - sizeof(double)) / sizeof(record);
	fin.seekg(0, ios::beg);

	fin.read((char *) &goal, sizeof(double));

	for (int i = 0; i < n; i++)
	{
		fin.read((char *) &temp, sizeof(record) );
		p.push_back(temp);
	}

	fin.close();
	return;
}

void write(vector<record> &p, double goal)
{
	ofstream fout;
	record temp;

	fout.open("times.bin", ios::out | ios::trunc | ios::binary);

	if (!fout) // || !sfile is needed in statement
	{
		cout << "Error! Either file \"times.bin\" or \"s_times.bin\" cannot open or is missing from the program directory." << endl;
		fout.close();
		//		sfile.close();
		return;
	}

	fout.write((char *) &goal, sizeof(double));

	for (unsigned int i = 0; i < p.size(); i++)
	{
		temp = p.at(i);
		fout.write((char *) &temp, sizeof(record));
	}
	
	fout.close();

	return;
}

void swrite(vector<record> &p, double goal)
{

	ofstream fout;
	record temp;

	fout.open("s_times.bin", ios::out | ios::trunc | ios::binary);

	if (!fout) 
	{
		cout << "Error! Either file \"times.bin\" or \"s_times.bin\" cannot open or is missing from the program directory." << endl;
		fout.close();
		exit(0);
	}

	fout.write((char *)&goal, sizeof(double));

	for (unsigned int i = 0; i < p.size(); i++)
	{
		temp = p.at(i);
		fout.write((char *)&temp, sizeof(record));
	}

	fout.close();

	return;
}

void pwrite(vector<record> &p, double goal)
{
	ofstream fout;
	
	fout.open("patients.txt", ios::out | ios::trunc);

	if (!fout)
	{
		cout << "Error! The file was not created" << endl;
		fout.close();
		return;
	}

	fout << "The following are patients who have less than " << goal << " minutes recorded." << endl << endl;

	fout << "* denotes a patient whos information has been changed since the last reset." << endl << endl;
	fout << left << setw(20) << left << "First name" << left <<
		setw(20) << left << setw(20) << left << "Last name" <<
		left << setw(20) << left << setw(20) << left << "Birthdate" <<
		left << setw(20) << left << setw(20) << left << "Time (Minutes)" << left << setw(20) << endl << endl;

	for (unsigned int i = 0; i < p.size(); i++)
	{
		if (p.at(i).time < goal)
			fout << left << setw(20) << left << p.at(i).first <<
			left << setw(20) << left << setw(20) << left << p.at(i).last <<
			left << p.at(i).bdate[0] << p.at(i).bdate[1] <<
			"/" << p.at(i).bdate[2] << p.at(i).bdate[3] << "/" << p.at(i).bdate[4] <<
			p.at(i).bdate[5] << p.at(i).bdate[6] << setw(11) << p.at(i).bdate[7] <<
			left << setw(20) << left << setw(1) << left << p.at(i).time << left << setw(20);
		if (p.at(i).edit == true)
			fout << '*' << endl;
		else
			fout << endl;
	
	}

	fout.close();

	cout << endl << "The file was succesfully created" << endl << endl;
	return;
}

void change(vector<record> &p, double goal)
{
	string fname, lname, bday;
	char choice;

	cout << endl << "what is the first name on the file you want to edit?" << endl;

	cin >> fname;

	cout << endl;

	cout << "* denotes a patient whos information has been changed since the last reset." << endl << endl;
	cout << left << setw(20) << left << "First name" << left <<
		setw(20) << left << setw(20) << left << "Last name" <<
		left << setw(20) << left << setw(20) << left << "Birthdate" <<
		left << setw(20) << left << setw(20) << left << "Time (Minutes)" << left << setw(20) << endl << endl;


	for (unsigned int i = 0; i < p.size(); i++)
	{
		if (fname == p.at(i).first)
		{
			cout << left << setw(20) << left << p.at(i).first <<
				left << setw(20) << left << setw(20) << left << p.at(i).last <<
				left << p.at(i).bdate[0] << p.at(i).bdate[1] <<
				"/" << p.at(i).bdate[2] << p.at(i).bdate[3] << "/" << p.at(i).bdate[4] <<
				p.at(i).bdate[5] << p.at(i).bdate[6] << setw(11) << p.at(i).bdate[7] <<
				left << setw(20) << left << setw(1) << left << p.at(i).time << left << setw(20);
			if (p.at(i).edit == true)
				cout << '*' << endl;
			else
				cout << endl;
		}
	}

	cout << endl << "what is the last name on the file you would like to edit?" << endl;

	cin >> lname;
	cout << endl;

	for (unsigned int i = 0; i < p.size(); i++)
	{
		if (fname == p.at(i).first && lname == p.at(i).last)
		{
			cout << left << setw(20) << left << p.at(i).first <<
				left << setw(20) << left << setw(20) << left << p.at(i).last <<
				left << p.at(i).bdate[0] << p.at(i).bdate[1] <<
				"/" << p.at(i).bdate[2] << p.at(i).bdate[3] << "/" << p.at(i).bdate[4] <<
				p.at(i).bdate[5] << p.at(i).bdate[6] << setw(11) << p.at(i).bdate[7] <<
				left << setw(20) << left << setw(1) << left << p.at(i).time << left << setw(20);
			if (p.at(i).edit == true)
				cout << '*' << endl;
			else
				cout << endl;
		}
	}

	cout << endl << "what is the birthdate on the file you would like to edit? (mmddyyyy)" << endl;

	cin >> bday;

	for (unsigned int i = 0; i < p.size(); i++)
	{
		if (fname == p.at(i).first && lname == p.at(i).last && bday == p.at(i).bdate)
		{
			system("cls");
		
			do
			{
				cout << "Patient: " << p.at(i).first << " " << p.at(i).last << " " << p.at(i).bdate[0]
					<< p.at(i).bdate[1] << "/" << p.at(i).bdate[2] << p.at(i).bdate[3] << "/" << p.at(i).bdate[4]
					<< p.at(i).bdate[5] << p.at(i).bdate[6] << p.at(i).bdate[7] << endl << endl;
				cout << "f - edit the selected patient's first name" << endl;
				cout << "l - edit the selected patient's last name" << endl;
				cout << "d - edit the selected patient's date of birth" << endl;
				cout << "t - edit the selected patient's recorded time" << endl;
				cout << "b - back to previous menu" << endl << endl;
				cout << "What would you like to do?" << endl;

				cin >> choice;
				tolower(choice);

				switch (choice)
				{
				case 'f':
					system("cls");
					cout << "Patient: " << p.at(i).first << " " << p.at(i).last << " " << p.at(i).bdate[0]
						<< p.at(i).bdate[1] << "/" << p.at(i).bdate[2] << p.at(i).bdate[3] << "/" << p.at(i).bdate[4]
						<< p.at(i).bdate[5] << p.at(i).bdate[6] << p.at(i).bdate[7] << endl << endl;
					cout << "Enter a new first name" << endl;
					cin >> p.at(i).first;
					p.at(i).edit = true;
					system("cls");
					cout << "Patient's first name was successfully updated" << endl;
					system("pause");
					system("cls");
					break;

				case 'l':
					system("cls");
					cout << "Patient: " << p.at(i).first << " " << p.at(i).last << " " << p.at(i).bdate[0]
						<< p.at(i).bdate[1] << "/" << p.at(i).bdate[2] << p.at(i).bdate[3] << "/" << p.at(i).bdate[4]
						<< p.at(i).bdate[5] << p.at(i).bdate[6] << p.at(i).bdate[7] << endl << endl;
					cout << "Enter a new last name" << endl;
					cin >> p.at(i).last;
					p.at(i).edit = true;
					system("cls");
					cout << "Patient's last name was successfully updated" << endl;
					system("pause");
					system("cls");
					break;

				case 'd':
					system("cls");
					cout << "Patient: " << p.at(i).first << " " << p.at(i).last << " " << p.at(i).bdate[0]
						<< p.at(i).bdate[1] << "/" << p.at(i).bdate[2] << p.at(i).bdate[3] << "/" << p.at(i).bdate[4]
						<< p.at(i).bdate[5] << p.at(i).bdate[6] << p.at(i).bdate[7] << endl << endl;
					cout << "Enter a new date of birth (mmddyyyy)" << endl;
					cin >> p.at(i).bdate;
					p.at(i).edit = true;
					system("cls");
					cout << "Patient's date of birth was successfully updated" << endl;
					system("pause");
					system("cls");
					break;

				case 't':
					system("cls");
					cout << "Patient: " << p.at(i).first << " " << p.at(i).last << " " << p.at(i).bdate[0]
						<< p.at(i).bdate[1] << "/" << p.at(i).bdate[2] << p.at(i).bdate[3] << "/" << p.at(i).bdate[4]
						<< p.at(i).bdate[5] << p.at(i).bdate[6] << p.at(i).bdate[7] << endl << endl;
					cout << "Enter the ammount of time spent with this patient" << endl;
					cin >> p.at(i).time;
					p.at(i).edit = true;
					system("cls");
					cout << "Patient's recorded time was successfully updated" << endl;
					system("pause");
					system("cls");
					break;

				case 'b':
					break;

				default:
					system("cls");
					cout << "Invalid input. Please re-input a command" << endl;
					system("pause");
					system("cls");
				}

			} while (choice != 'b');
			return;
		}
	}
	cout << endl << "No record of that patient was found" << endl;
	system("pause");

	return;
}