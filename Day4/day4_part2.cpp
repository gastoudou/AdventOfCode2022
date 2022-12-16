#include "stdafx.h"

// #define TEST_DATA 1

namespace day_4_part_2
{
	struct data
	{
		int overlaps = 0;
	};

	const std::vector< std::string > load_inputs()
	{
#ifdef TEST_DATA
		const std::vector< std::string > test_inputs =
		{
			"2-4,6-8",
			"2-3,4-5",
			"5-7,7-9",
			"2-8,3-7",
			"6-6,4-6",
			"2-6,4-8"
		};
		return test_inputs;
#else
		std::vector< std::string > real_inputs;

		FILE* real_inputs_file;
		auto result = fopen_s( &real_inputs_file, "data/day4/input.txt", "r" );

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
		data.overlaps = 0;

		for ( auto line : inputs )
		{
			struct assignment
			{
				assignment( const std::string str )
				{
					size_t position_of_separator = str.find( "-" );
					auto start_str = str.substr( 0, position_of_separator );
					auto end_str = str.substr( position_of_separator + 1, str.size() - position_of_separator - 1 );

					start = atoi( start_str.c_str() );
					end = atoi( end_str.c_str() );

					for ( int i = start; i <= end; ++i )
					{
						mask[ i ] = 1;
					}
				}

				int start = 0;
				int end = 0;
				std::bitset< 1500 > mask;
			};

			size_t position_of_separator = line.find( "," );
			auto left_str = line.substr( 0, position_of_separator );
			auto right_str = line.substr( position_of_separator + 1, line.size() - position_of_separator - 1 );

			assignment left( left_str );
			assignment right( right_str );

			auto mask_global = left.mask & right.mask;

			if ( mask_global.any() ) // prune collision test
			{
				data.overlaps++;
			}
		}
	}

	void display_result( data& data )
	{
		std::cout << "Overlaps: " << data.overlaps << std::endl;
	}
}

void day_4_run_part_2()
{
	day_4_part_2::data data;

	day_4_part_2::process( day_4_part_2::load_inputs(), data );
	day_4_part_2::display_result( data );
}