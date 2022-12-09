#include "stdafx.h"

#define TEST_DATA 1

namespace day_3_part_2
{
	struct data
	{
	};

	const std::vector< std::string > load_inputs()
	{
#ifdef TEST_DATA
		const std::vector< std::string > test_inputs =
		{
		};

		return test_inputs;
#else

		std::vector< std::string > real_inputs;

		FILE* real_inputs_file;
		auto result = fopen_s( &real_inputs_file, "data/day3/input.txt", "r" );

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
	}

	void display_result( data& data )
	{
	}
}

void day_3_run_part_2()
{
	day_3_part_2::data data;

	day_3_part_2::process( day_3_part_2::load_inputs(), data );
	day_3_part_2::display_result( data );
}