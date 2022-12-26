#include "stdafx.h"

// #define TEST_DATA 1

namespace day_3_part_2
{
	static const size_t BITSET_SIZE = 52u;
	static const size_t NUM_GROUPS = 3u;

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

	constexpr int convert( const char current_char )
	{
		if ( current_char & ( 1 << 5 ) )
		{
			return current_char - 96;
		}
		else
		{
			return current_char - 38;
		}
	};

	void add_score( data& io_data, const std::vector< std::bitset< BITSET_SIZE > >& char_bitset_per_line )
	{
		std::bitset< BITSET_SIZE > mask = ~0ull;
		for ( const std::bitset< BITSET_SIZE >&chars_bitset : char_bitset_per_line )
		{
			mask &= chars_bitset;
		}

		for ( int bit = 0; bit < BITSET_SIZE; ++bit )
		{
			if ( mask[ bit ] == 1 )
			{
				io_data.score += bit + 1;
				break;
			}
		}
	};

	void process( const std::vector< std::string >& inputs, data& io_data )
	{
		size_t line_id = 0u;
		size_t current_group = 0u;

		std::vector< std::bitset< BITSET_SIZE > > char_bitset_per_line;
		char_bitset_per_line.reserve( NUM_GROUPS );

		io_data.score = 0;

		for ( auto line : inputs )
		{
			size_t group = line_id / NUM_GROUPS;
			if ( group != current_group )
			{
				add_score( io_data, char_bitset_per_line );
				char_bitset_per_line.clear();
				current_group++;
			}

			std::bitset< BITSET_SIZE > sub_bitset = 0u;
			for ( char ch : line )
			{
				sub_bitset[ convert( ch ) - 1 ] = 1;
			}
			char_bitset_per_line.push_back( sub_bitset );
			line_id++;
		}
		add_score( io_data, char_bitset_per_line );
	}

	void display_result( data& data )
	{
		std::cout << "Score: " << data.score << std::endl;
	}
}

void day_3_run_part_2()
{
	day_3_part_2::data data;

	day_3_part_2::process( day_3_part_2::load_inputs(), data );
	day_3_part_2::display_result( data );
}