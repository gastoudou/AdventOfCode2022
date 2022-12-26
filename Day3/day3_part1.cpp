#include "stdafx.h"

// #define TEST_DATA 1

namespace day_3_part_1
{
	struct data
	{
		int score = 0;
	};

	const std::vector< std::string > load_inputs()
	{
#ifdef TEST_DATA
		const std::vector< std::string > test_inputs =
		{
			"vJrwpWtwJgWrhcsFMMfFFhFp",
			"jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL",
			"PmmdzqPrVvPwwTWBwg",
			"wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn",
			"ttgJtRGJQctTZtZT",
			"CrZsJsPPZsGzwwsLwLmpwMDw"
		};

		return test_inputs;
#else

		std::vector< std::string > real_inputs;

		FILE* real_inputs_file;
		auto result = fopen_s( &real_inputs_file, "data/day3/input.txt", "r" );

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

		auto convert = [] ( const char current_char ) -> int
		{
			if ( current_char & ( 1 << 5 ) )
				return current_char - 96;
			else
				return current_char - 38;
		};

		for ( auto line : inputs )
		{
			size_t half_size = line.size() / 2;
			for ( size_t i = 0u; i < half_size; ++i )
			{
				auto it_search = std::find( line.cbegin() + half_size, line.cend(), line[i]);
				if( it_search != line.cend() )
				{
					data.score += convert( line[ i ] );
					break;
				}
			}
		}
	}

	void display_result( data& data )
	{
		std::cout << "Score: " << data.score << std::endl;
	}
}

void day_3_run_part_1()
{
	day_3_part_1::data data;

	day_3_part_1::process( day_3_part_1::load_inputs(), data );
	day_3_part_1::display_result( data );
}