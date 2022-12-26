#include "stdafx.h"

/*#define TEST_DATA 1*/

namespace day_2_part_2
{
	struct data
	{
		int score = 0u;

		std::map< std::string, int > results_map
		{
			// 0 if you lost, 3 if the round was a draw, and 6 if you won
			{ "A A", 3 + 1 }, // Rock vs Rock			= draw + 1
			{ "A B", 6 + 2 }, // Rock vs Paper			= win  + 2
			{ "A C", 0 + 3 }, // Rock vs Scissors		= lost + 3

			{ "B A", 0 + 1 }, // Paper vs Rock			= lost + 1
			{ "B B", 3 + 2 }, // Paper vs Paper			= draw + 2
			{ "B C", 6 + 3 }, // Paper vs Scissors		= win  + 3

			{ "C A", 6 + 1 }, // Scissors vs Rock		= win  + 1
			{ "C B", 0 + 2 }, // Scissors vs Paper		= lost + 2
			{ "C C", 3 + 3 }  // Scissors vs Scissors	= draw + 3
		};

		std::map< std::string, char > new_combi_map
		{
			// X means you need to lose
			// Y means you need to end the round in a draw
			// Z means you need to win

			{ "A X", 'C' }, // to lose: Rock vs Scissors
			{ "A Y", 'A' }, // to draw: Rock vs Rock
			{ "A Z", 'B' }, // to win:  Rock vs Paper

			{ "B X", 'A' }, // to lose: Paper vs Rock
			{ "B Y", 'B' }, // to draw: Paper vs Paper
			{ "B Z", 'C' }, // to win:  Paper vs Rock

			{ "C X", 'B' }, // to lose: Scissors vs Paper
			{ "C Y", 'C' }, // to draw: Scissors vs Scissors
			{ "C Z", 'A' }  // to win:  Scissors vs Rock
		};
	};

	const std::vector< std::string > load_inputs()
	{
#ifdef TEST_DATA
		const std::vector< std::string > test_inputs =
		{
			"A Y",
			"B X",
			"C Z"
		};

		return test_inputs;
#else

		std::vector< std::string > real_inputs;

		FILE* real_inputs_file;
		auto result = fopen_s( &real_inputs_file, "data/day2/input.txt", "r" );

		if ( result == 0 )
		{
			char buffer[ 128 ];
			char* read = fgets( buffer, 128, real_inputs_file );
			while ( read )
			{
				std::string line( read );
				line = line.substr( 0, line.size() - 1 ); // remove /n
				real_inputs.push_back( line );
				read = fgets( buffer, 128, real_inputs_file );
			}
			fclose( real_inputs_file ); // ALWAYS CLOSE AN OPENED FILE
		}

		return real_inputs;

#endif
	}

	void process( const std::vector< std::string >& inputs, data& data )
	{
		data.score = 0;

		for ( auto input : inputs )
		{
			// find the correct combination
			const char my_choice = data.new_combi_map[ input ];

			// get the score
			std::string needed_combination;
			needed_combination.push_back( input[ 0 ] );
			needed_combination.push_back( ' ' );
			needed_combination.push_back( my_choice );
			data.score += data.results_map[ needed_combination ];
		}
	}

	void display_result( data& data )
	{
		std::cout << "Final score: " << data.score << std::endl;
	}
}

void day_2_run_part_2()
{
	day_2_part_2::data data;

	day_2_part_2::process( day_2_part_2::load_inputs(), data );
	day_2_part_2::display_result( data );
}