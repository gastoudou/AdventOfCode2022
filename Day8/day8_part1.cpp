#include "stdafx.h"

// #define TEST_DATA 1

namespace day_8_part_1
{
	struct data
	{
		size_t nb_visibles = 0u;
	};

	const std::vector< std::string > load_inputs()
	{
#ifdef TEST_DATA
		const std::vector< std::string > test_inputs =
		{
			"30373",
			"25512",
			"65332",
			"33549",
			"35390"
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

	void process( const std::vector< std::string >& inputs, data& data )
	{
		const size_t width = inputs[ 0 ].size();
		const size_t height = inputs.size();

		std::vector< bool > map_visibles;
		map_visibles.resize( width * height, false );

		for ( size_t i = 1u; i < inputs.size() - 1u; ++i )
		{
			// going for left to right
			{
				size_t left = 0u;
				size_t right = inputs[ i ].size() - 1u;
				int height_base = inputs[ i ][ left ] - '0';

				for ( size_t j = left + 1; j < right; ++j )
				{
					int current_height = inputs[ i ][ j ] - '0';
					if ( current_height > height_base )
					{
						map_visibles[ i * width + j ] = true;
						height_base = current_height;
					}
				}
			}

			// going for right to left
			{
				size_t left = inputs[ i ].size() - 1u;
				size_t right = 0u;
				int height_base = inputs[ i ][ left ] - '0';

				for ( size_t j = left - 1u; j > right; --j )
				{
					int current_height = inputs[ i ][ j ] - '0';
					if ( current_height > height_base )
					{
						map_visibles[ i * width + j ] = true;
						height_base = current_height;
					}
				}
			}
		}

		for ( size_t i = 1u; i < inputs[ 0 ].size() - 1u; ++i )
		{
			{
				// going for top to bottom
				size_t top = 0u;
				int height_base = inputs[ i ][ top ] - '0';
				for ( size_t j = top + 1u; j < inputs.size() - 1u; ++j )
				{

					int current_height = inputs[ i ][ j ] - '0';
					if ( current_height > height_base )
					{
						map_visibles[ i * width + j ] = true;
						height_base = current_height;
					}
				}
			}

			{
				// going for bottom to top
				size_t bottom = inputs.size() - 1;
				int height_base = inputs[ i ][ bottom ] - '0';
				for ( size_t j = bottom - 1u; j > 1u; --j )
				{

					int current_height = inputs[ i ][ j ] - '0';
					if ( current_height > height_base )
					{
						map_visibles[ i * width + j ] = true;
						height_base = current_height;
					}
				}
			}
		}

		size_t nb_visibles_interior = 0u;

		for ( size_t i = 0u; i < width; ++i )
		{
			for ( size_t j = 0u; j < height; ++j )
			{
				if ( map_visibles[ i * width + j ] )
					nb_visibles_interior++;
			}
		}

		data.nb_visibles = 2u * inputs[ 0 ].size() + ( 2u * ( inputs.size() - 2 ) ) + nb_visibles_interior;
	}

	void display_result( data& data )
	{
		std::cout << "Day 8 : Part 1" << std::endl;
		std::cout << "Trees visible: " << data.nb_visibles << std::endl;
	}
}

void day_8_run_part_1()
{
	day_8_part_1::data data;

	day_8_part_1::process( day_8_part_1::load_inputs(), data );
	day_8_part_1::display_result( data );
}