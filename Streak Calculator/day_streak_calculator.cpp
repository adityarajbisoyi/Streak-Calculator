#include <iostream>
#include <unordered_map>

using namespace std;
class Tasks
{
public:
	unordered_map<int, string> tasks;

	void addTask(int taskNo, string taskName)
	{
		tasks[taskNo] = taskName;
	}
	void removeTask(int taskNo)
	{
		tasks.erase(taskNo);
	}
};

class StreakCounter : public Tasks
{

public:
	unordered_map<int, int> streakList;

	void intializeStreakCounter()
	{
		for (auto &pair : tasks)
		{
			streakList[pair.first] = 0;
		}
	}

	void refreshStreakList()
	{

		for (auto &pair : streakList)
		{
			auto it = tasks.find(pair.first);
			if (it == tasks.end())
			{
				streakList.erase(pair.first);
			}
		}
		for (auto &pair : tasks)
		{
			auto it = streakList.find(pair.first);
			if (it == streakList.end())
			{
				streakList[pair.first] = 0;
			}
		}
	}

	void completedTask(int taskNo)
	{
		streakList[taskNo] += 1;
	}

	void resetTask(int taskNo)
	{
		streakList[taskNo] = 0;
	}

	unordered_map<string, int> getStreakList()
	{
		unordered_map<string, int> streakListByName;
		for (auto &pair : tasks)
		{
			streakListByName[pair.second] = streakList[pair.first];
		}
		return streakListByName;
	}
};
int main()
{
	bool appOpen = true;
	StreakCounter taskStreak;
	cout << "Welcome to the streak calculator , make your own streak in your own way!" << endl;
	while (appOpen)
	{
		cout << "Enter '+' or '-' to Add or remove a task " << endl
			 << "Enter 's' to add a streak" << endl
			 << "Enter '0' to show the streaks" << endl
			 << "Enter 'r' to reset a streak" << endl;
		char userInput;
		cin >> userInput;
		int taskNo;
		string taskName;
		switch (userInput)
		{
		case '+':
			cout << "Enter the Task's Priority" << endl;
			cin >> taskNo;
			cout << "Enter the Task's Name" << endl;
			cin >> taskName;
			taskStreak.addTask(taskNo, taskName);
			break;
		case '-':
			cout << "Enter the Task Priority to remove the task" << endl;
			cin >> taskNo;
			taskStreak.removeTask(taskNo);
			break;
		case 's':
			cout << "Enter the Task Priority that you have completed today" << endl;
			cin >> taskNo;
			taskStreak.completedTask(taskNo);
			break;
		case '0':
			for (auto &pair : taskStreak.getStreakList())
			{
				cout << pair.first << "\t\t" << pair.second << " Days" << endl;
			}
			break;
		case 'r':
			cout << "Enter the Task Priority for resetting its streak" << endl;
			cin >> taskNo;
			taskStreak.resetTask(taskNo);
			break;


		case '#':
			appOpen = false;
			break;

		default:
			break;
		}
	}
}