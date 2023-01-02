#include "stdafx.h"

#define TEST_DATA 1

namespace day_8_part_2
{
	struct data
	{
	};

	const std::vector< std::string > load_inputs()
	{
#ifdef TEST_DATA
		const std::vector< std::string > test_inputs =
		{
			"$ cd /",
			"$ ls",
			"dir a",
			"14848514 b.txt",
			"8504156 c.dat",
			"dir d",
			"$ cd a",
			"$ ls",
			"dir e",
			"29116 f",
			"2557 g",
			"62596 h.lst",
			"$ cd e",
			"$ ls",
			"584 i",
			"$ cd ..",
			"$ cd ..",
			"$ cd d",
			"$ ls",
			"4060174 j",
			"8033020 d.log",
			"5626152 d.ext",
			"7214296 k"
		};
		return test_inputs;
#else
		std::vector< std::string > real_inputs;

		FILE* real_inputs_file;
		auto result = fopen_s( &real_inputs_file, "data/day8/input.txt", "r" );

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

	void process( const std::vector< std::string >& /*inputs*/, data& /*data*/ )
	{
	}

	void display_result( data& /*data*/ )
	{
		std::cout << "Day 8 : Part 2" << std::endl;
	}
}

void day_8_run_part_2()
{
	day_8_part_2::data data;

	day_8_part_2::process( day_8_part_2::load_inputs(), data );
	day_8_part_2::display_result( data );
}