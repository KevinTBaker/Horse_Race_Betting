#include "race.h"

class Race {

	int myarray[3] = { 1, 2, 3};

	public:

	Race() {
	}
	void readysetgo() {

		int n = sizeof(myarray)/sizeof(myarray[0]);

		for (int i = 0; i < n; i++)
		{
			int randomValue = i + ( rand() % (n - i) );
			int randomElement = myarray[randomValue];
			myarray[randomValue] = myarray[i];
			myarray[i] = randomElement;
		}
	};

	int first() {
		return myarray[0];
	}
	int second() {
		return myarray[1];
	}
	int third() {
		return myarray[2];
	}
};

void    win_or_lose(t_values *tools)
{
	if (tools->w_num == 1)
	{
		if (tools->bet_kind == "EXACTA")
		{
			cout << "You win 300 dollars!\n";
			tools->cash_balance += 300;
			cout << "Your new balance is "<< tools->cash_balance << endl;
		}
		else if (tools->bet_kind == "EXACTABOX")
		{
			cout << "You win 150 dollars\n";
			tools->cash_balance += 150;
			cout << "Your new balance is "<< tools->cash_balance << endl;
		}
	}
	else if ((tools->w_num == 0 && tools->bet_kind == "EXACTABOX") || (tools->w_num == 0 && tools->bet_kind == "EXACTA"))
	{
		cout << "sorry you lose\n";
		cout << "Your new balance is "<< tools->cash_balance << endl;
	}
}
void    check_bet(t_values *tools, Race r)
{
	if (tools->first_place == r.first() && tools->bet_kind == "EXACTA")
	{    
		tools->w_num = 1;
		if (tools->second_place == r.second() && tools->w_num == 1)
		{
			tools->w_num = 1;
			if (tools->third_place == r.third() && tools->w_num == 1)
			{
				tools->w_num == 1;
			}
			else
				tools->w_num = 0;
		}
		else
			tools->w_num = 0;
	}
	else if (tools->bet_kind == "EXACTABOX")
	{
		if (tools->first_place == r.first() || tools->first_place == r.second())
		{
			tools->w_num = 1;
		}
		if (tools->second_place == r.first() || tools->second_place == r.second())
			tools->w_num = 1;
	}
	win_or_lose(tools);
}

void    exacta_bet(t_values *tools, Race r)
{
	tools->cash_balance -= 50;
	cout << "what's your bet on first place?\n";
	cin >> tools->first_place;
	cout << "what's your bet on second place?\n";
	cin >> tools->second_place;
	cout << "what's your bet on third place?\n";
	cin >> tools->third_place;
}

void    exactabox_bet(t_values *tools, Race r)
{
	tools->cash_balance -= 25;
	cout << "what's your first bet?\n";
	cin >> tools->first_place;
	cout << "what's your second bet?\n";
	cin >> tools->second_place;
	cout << "what's your third bet?\n";
	cin >> tools->third_place;
}
void    bet_making(t_values *tools, Race r)
{
	if (tools->bet_kind == "EXACTA" && tools->cash_balance >= 50)
		exacta_bet(tools, r);
	else if (tools->bet_kind == "EXACTABOX" && tools->cash_balance >= 25)
		exactabox_bet(tools, r);
}

int main()
{
	t_values    tools;
	tools.cash_balance = 300;
	tools.w_num = 0;
	srand(time(NULL));
	Race r;
	while (tools.bet_kind != "DONE")
	{
		cout << "what kind of bet would you like to make?\n";
		cin >> tools.bet_kind;
		bet_making(&tools, r);
		r.readysetgo();
		if (tools.bet_kind != "DONE")
			cout << r.first() << " " << r.second() << " " << r.third() << endl;
		check_bet(&tools, r);
	}
}
