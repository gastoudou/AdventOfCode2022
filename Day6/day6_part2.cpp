#include "stdafx.h"

// #define TEST_DATA 1

namespace day_6_part_2
{
	struct data
	{
		int char_marker = 0;
	};

	const std::string load_inputs()
	{
#ifdef TEST_DATA
		const std::string test_inputs =
		{
			// "mjqjpqmgbljsphdztnvjfqwrcgsmlb" //: after character 19
			// "bvwbjplbgvbhsrlpgdmjqwftvncz" //: after character 23
			// "nppdvjthqldpwncqszvftbrmjlhg" //: after character 23
			 "nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg" //: after character 29
			// "zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw" //: after character 26
		};
		return test_inputs;
#else
		std::string real_inputs;

		FILE* real_inputs_file;
		auto result = fopen_s( &real_inputs_file, "data/day6/input.txt", "r" );

		if ( result == 0 )
		{
			char c;
			while ( ( c = fgetc( real_inputs_file ) ) != EOF )
			{
				real_inputs += c;
			}
			fclose( real_inputs_file ); // ALWAYS CLOSE AN OPENED FILE
		}
		return real_inputs;
#endif
		}

	void process( const std::string& inputs, data& data )
	{
		const int elmt_diff = 14;

		auto convert = [] ( const char current_char ) -> int
		{
			if ( current_char & ( 1 << 5 ) )
				return current_char - 'a';
			else
				return current_char - 'A';
		};

		for ( int i = 0; i < inputs.size(); ++i )
		{
			std::bitset< 27 > alphabet;
			alphabet[ convert( inputs[ i ] ) ] = 1;

			for ( int j = 1; j < elmt_diff; ++j )
			{
				if ( i + j < inputs.size() )
				{
					alphabet[ convert( inputs[ i + j ] ) ] = 1;
				}
			}

			if ( alphabet.count() == elmt_diff )
			{
				data.char_marker = i + elmt_diff;
				return;
			}
		}

		assert( false );
	}

	void display_result( data& data )
	{
		std::cout << data.char_marker << std::endl;
	}
}

void day_6_run_part_2()
{
	day_6_part_2::data data;

	day_6_part_2::process( day_6_part_2::load_inputs(), data );
	day_6_part_2::display_result( data );
}