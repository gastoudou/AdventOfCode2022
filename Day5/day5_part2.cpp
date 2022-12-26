#include "stdafx.h"

// #define TEST_DATA 1

namespace day_5_part_2
{
	struct data
	{
		std::vector< std::stack< char > > crates;
	};

	const std::vector< std::string > load_inputs()
	{
#ifdef TEST_DATA
		const std::vector< std::string > test_inputs =
		{
			"    [D]",
			"[N] [C]",
			"[Z] [M] [P]",
			" 1   2   3 ",
			"",
			"move 1 from 2 to 1",
			"move 3 from 1 to 3",
			"move 2 from 2 to 1",
			"move 1 from 1 to 2",
		};
		return test_inputs;
#else
		std::vector< std::string > real_inputs;

		FILE* real_inputs_file;
		auto result = fopen_s( &real_inputs_file, "data/day5/input.txt", "r" );

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
		int header_line_id = 0;
		int last_line_id = 0;
		for ( int i = 0; i < inputs.size(); ++i )
		{
			if ( inputs[ i ] == "" ) // stop
			{
				header_line_id = i - 1; // remove header line
				last_line_id = i - 2; // remove header line
				break;
			}
		}

		// read the header line
		std::string header = inputs[ header_line_id ].substr();
		std::string str_nb_crates = header.substr( header.size() - 2 );
		// fill crates

		size_t nb_crates = atoi( str_nb_crates.c_str() );
		data.crates.resize( nb_crates );

		for ( int i = last_line_id; i >= 0; --i )
		{
			bool found_bracket = false;
			std::string current_line_reading = inputs[ i ];
			size_t starting_position = 0u;
			do
			{
				found_bracket = false;
				size_t pos_bracket = current_line_reading.find_first_of( '[', starting_position );
				if ( pos_bracket != std::string::npos )
				{
					found_bracket = true;
					size_t crate_id = pos_bracket / 4u;
					char value = current_line_reading[ pos_bracket + 1 ];
					data.crates[ crate_id ].push( value );
					if ( pos_bracket + 4 < current_line_reading.size() )
					{
						starting_position = pos_bracket + 4;
					}
					else
					{
						current_line_reading.clear();
					}
				}

			}
			while ( found_bracket && !current_line_reading.empty() );
		}

		// now read moves - and move
		for ( size_t i = header_line_id + 2; i < inputs.size(); ++i )
		{
			// "move 1 from 2 to 1"
			std::string line = inputs[ i ];

			line = line.substr( 5 ); // remove "move "
			std::string str_how_many_to_move = line.substr( 0, line.find_first_of( ' ' ) );
			int how_many_to_move = atoi( str_how_many_to_move.c_str() );
			line = line.substr( str_how_many_to_move.size() ); // remove number

			line = line.substr( 6 ); // remove " from "
			std::string str_from = line.substr( 0, line.find_first_of( ' ' ) );
			int from_to_move = atoi( str_from.c_str() ) - 1;
			line = line.substr( str_from.size() ); // remove number

			line = line.substr( 4 ); // remove " to "
			std::string str_to = line.substr( 0, line.find_first_of( ' ' ) );
			int to_to_move = atoi( str_to.c_str() ) - 1;

			std::stack< char > temp;
			for ( int j = 0; j < how_many_to_move; ++j )
			{
				temp.push( data.crates[ from_to_move ].top() );
				data.crates[ from_to_move ].pop();
			}

			for ( int j = 0; j < how_many_to_move; ++j )
			{
				data.crates[ to_to_move ].push( temp.top() );
				temp.pop();
			}
		}
	}

	void display_result( data& data )
	{
		{
			std::cout << "result: " << std::endl;
			size_t id = 0u;
			for ( auto crate : data.crates )
			{
				std::cout << "crate " << id << std::endl;
				std::cout << "[" << crate.top() << "]" << std::endl;
				id++;
			}
		}

		{
			std::cout << "real result: " << std::endl;
			size_t id = 0u;
			for ( auto crate : data.crates )
			{
				std::cout << crate.top();
				id++;
			}
		}
		std::cout << std::endl;
	}
}

void day_5_run_part_2()
{
	day_5_part_2::data data;

	day_5_part_2::process( day_5_part_2::load_inputs(), data );
	day_5_part_2::display_result( data );
}