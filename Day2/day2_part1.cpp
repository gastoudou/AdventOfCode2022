#include "stdafx.h"

// #define TEST_DATA 1

namespace day_2_part_1
{
	struct data
	{
		int score = 0u;

		std::map< std::string, int > results_map
		{
			// 0 if you lost, 3 if the round was a draw, and 6 if you won
			{ "A X", 3 + 1 }, // Rock vs Rock			= draw + 1
			{ "A Y", 6 + 2 }, // Rock vs Paper			= win  + 2
			{ "A Z", 0 + 3 }, // Rock vs Scissors		= lost + 3

			{ "B X", 0 + 1 }, // Paper vs Rock			= lost + 1
			{ "B Y", 3 + 2 }, // Paper vs Paper			= draw + 2
			{ "B Z", 6 + 3 }, // Paper vs Scissors		= win  + 3

			{ "C X", 6 + 1 }, // Scissors vs Rock		= win  + 1
			{ "C Y", 0 + 2 }, // Scissors vs Paper		= lost + 2
			{ "C Z", 3 + 3 }  // Scissors vs Scissors	= draw + 3
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
			char* read;
			while ( read = fgets( buffer, 128, real_inputs_file ) )
			{
				std::string line( read );
				line = line.substr( 0, line.size() - 1 ); // remove /n
				real_inputs.push_back( line );
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
			data.score += data.results_map[ input ];
		}
	}

	void display_result( data& data )
	{
		std::cout << "Final score: " << data.score << std::endl;
	}
}

void day_2_run_part_1()
{
	day_2_part_1::data data;

	day_2_part_1::process( day_2_part_1::load_inputs(), data );
	day_2_part_1::display_result( data );
}