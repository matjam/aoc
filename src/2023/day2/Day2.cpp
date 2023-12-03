#include <string>
#include <charconv>

#include "Day2.hpp"
#include "Split.hpp"

using namespace std;

const int maxBlue = 14;
const int maxGreen = 13;
const int maxRed = 12;

Day2::Day2(AOCRenderer* r)
{
	renderer = r;
}

void Day2::run() {
	string day2input = "resources/day2_input.txt";

	renderer->print("starting day2 ...\n");
	renderer->print(" . opening " + day2input + " ... ");
	input.open(day2input);
	if (input.bad() || input.eof()) {
		renderer->print("\n !!! error opening file :-(\n");
		return;
	}
	renderer->print("opened!\n");

	part1();
	part2();

	renderer->print(" . closing " + day2input + ".");
	input.close();
}

void Day2::part1() {
	renderer->print(" . processing part 1 ... ");

	int gameIDSum = 0;
	int lineCount = 0;

	string line;
	while (getline(input, line)) {
		lineCount++;
		bool impossible = false;

		// Split the line like
		// Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
		vector<string> gameLineData = splitString(line, ":");	
		if (gameLineData.size() != 2) {
			renderer->print("error!\n ! expected at least at least one game entry in a game.\n");
			renderer->print("   offending line: \n");
			renderer->print("[" + line + "]\n  at line " + to_string(lineCount) + "\n");
			return;
		}

		// Split the string like
		// Game 1
		vector<string> gameNumberStrings = splitString(gameLineData[0], " ");
		if (gameNumberStrings.size() != 2) {
			renderer->print("error!\n ! expected a string like [Game 1].\n");
			renderer->print("   offending line: \n");
			renderer->print("[" + line + "]\n  at line " + to_string(lineCount) + "\n");
			return;
		}
		
		int gameID = stoi(gameNumberStrings[1], nullptr, 10);
		
		// split "3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green"
		// into 3 rounds
		vector<string> rounds = splitString(gameLineData[1], ";");
		if (rounds.size() == 0) {
			renderer->print("error!\n ! expected at least one round in a game.\n");
			renderer->print("   offending line: \n");
			renderer->print("[" + line + "]\n  at line " + to_string(lineCount) + "\n");
			return;
		}

		// loop over the rounds
		for (int r = 0; r < rounds.size(); r++) {
			int redCount = 0;
			int blueCount = 0;
			int greenCount = 0;

			string round = rounds[r];

			vector<string>cubeCounts = splitString(trim_copy(round), ",");
			if (cubeCounts.size() < 1) {
				renderer->print("error!\n ! expected a string like [3 blue, 4 red].\n");
				renderer->print("   offending line: \n");
				renderer->print("[" + line + "]\n  at line " + to_string(lineCount) + "\n");
				return;
			}

			// we should have a string in cubeCounts[c] that is like [5 green].
			for (int c = 0; c < cubeCounts.size(); c++) {
				vector<string>colorValue = splitString(trim_copy(cubeCounts[c]), " ");
				if (colorValue.size() != 2) {
					renderer->print("error!\n ! expected a string like [3 blue].\n");
					renderer->print("   offending line: \n");
					renderer->print("[" + line + "]\n  at line " + to_string(lineCount) + "\n");
					return;
				}

				// now we have a vector where the first value is the count and the
				// second is the color name.
				int count = stoi(colorValue[0], nullptr, 10);
				string colorString = colorValue[1];

				// lol, its 2023 and C++ can't switch on a string value. Lame.
				if (colorString.compare("red") == 0) {
					redCount += count;
				}
				else if (colorString.compare("green") == 0) {
					greenCount += count;
				}
				else if (colorString.compare("blue") == 0) {
					blueCount += count;
				}
			}

			// is this round impossible?
			if (redCount > maxRed || greenCount > maxGreen || blueCount > maxBlue) {
				impossible = true;
			}
		}

		if (!impossible) {
			gameIDSum += gameID;
		}

	}

	renderer->print("done!\n");
	renderer->print(" . day2 part1 result: " + to_string(gameIDSum) + "\n");
}

// wow much copy pasta
void Day2::part2() {
	renderer->print(" . processing part 2 ... ");

	int gameIDSum = 0;
	int lineCount = 0;
	int powerSum = 0;

	string line; // each line is a "game";
	while (getline(input, line)) {
		lineCount++;
		
		// count of colors per game
		int redCount = 0;
		int blueCount = 0;
		int greenCount = 0;

		// Split the line like
		// Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
		vector<string> gameLineData = splitString(line, ":");
		if (gameLineData.size() != 2) {
			renderer->print("error!\n ! expected at least at least one game entry in a game.\n");
			renderer->print("   offending line: \n");
			renderer->print("[" + line + "]\n  at line " + to_string(lineCount) + "\n");
			return;
		}

		// Split the string like
		// Game 1
		vector<string> gameNumberStrings = splitString(gameLineData[0], " ");
		if (gameNumberStrings.size() != 2) {
			renderer->print("error!\n ! expected a string like [Game 1].\n");
			renderer->print("   offending line: \n");
			renderer->print("[" + line + "]\n  at line " + to_string(lineCount) + "\n");
			return;
		}

		int gameID = stoi(gameNumberStrings[1], nullptr, 10);

		// split "3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green"
		// into 3 rounds
		vector<string> rounds = splitString(gameLineData[1], ";");
		if (rounds.size() == 0) {
			renderer->print("error!\n ! expected at least one round in a game.\n");
			renderer->print("   offending line: \n");
			renderer->print("[" + line + "]\n  at line " + to_string(lineCount) + "\n");
			return;
		}


		// loop over the rounds
		for (int r = 0; r < rounds.size(); r++) {
			string round = rounds[r];

			vector<string>cubeCounts = splitString(trim_copy(round), ",");
			if (cubeCounts.size() < 1) {
				renderer->print("error!\n ! expected a string like [3 blue, 4 red].\n");
				renderer->print("   offending line: \n");
				renderer->print("[" + line + "]\n  at line " + to_string(lineCount) + "\n");
				return;
			}

			// we should have a string in cubeCounts[c] that is like [5 green].
			for (int c = 0; c < cubeCounts.size(); c++) {
				vector<string>colorValue = splitString(trim_copy(cubeCounts[c]), " ");
				if (colorValue.size() != 2) {
					renderer->print("error!\n ! expected a string like [3 blue].\n");
					renderer->print("   offending line: \n");
					renderer->print("[" + line + "]\n  at line " + to_string(lineCount) + "\n");
					return;
				}

				// now we have a vector where the first value is the count and the
				// second is the color name.
				int count = stoi(colorValue[0], nullptr, 10);
				string colorString = colorValue[1];

				// lol, its 2023 and C++ can't switch on a string value. Lame.
				if (colorString.compare("red") == 0) {
					if (count > redCount)
						redCount = count;
				}
				else if (colorString.compare("green") == 0) {
					if (count > greenCount)
						greenCount = count;
				}
				else if (colorString.compare("blue") == 0) {
					if (count > blueCount)
						blueCount = count;
				}
			}
		}

		int power = redCount * greenCount * blueCount;

		cout << "power: " << power << endl;

		powerSum += power;
	}

	renderer->print("done!\n");
	renderer->print(" . day2 part2 result: " + to_string(powerSum) + "\n");
}

