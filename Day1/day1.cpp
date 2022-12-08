#include "stdafx.h"

// #define TEST_DATA 1

namespace day_1
{
	struct data
	{
		std::vector< std::pair< uint32_t, uint32_t > > calories_per_elf;

		uint32_t sum = 0u;
		uint32_t elf_id = 0u;
		uint32_t biggestcalories_provider_elf_id = 0u;
		uint32_t biggest_calories = 0u;
	};

	const std::vector< std::string > load_inputs()
	{
#ifdef TEST_DATA
		const std::vector< std::string > test_inputs =
		{
			"1000",
			"2000",
			"3000",
			"",
			"4000",
			"",
			"5000",
			"6000",
			"",
			"7000",
			"8000",
			"9000",
			"",
			"10000"
		};

		return test_inputs;
#else

		std::vector< std::string > real_inputs;

		FILE* real_inputs_file;
		auto result = fopen_s( &real_inputs_file, "data/day1/input.txt", "r" );

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
		auto set_sum = [&] ()
		{
			if ( data.biggest_calories < data.sum )
			{
				data.biggest_calories = data.sum;
				data.biggestcalories_provider_elf_id = data.elf_id;
			}

			data.calories_per_elf.push_back( std::make_pair( data.elf_id, data.sum ) );
			data.sum = 0;
			data.elf_id++;
		};

		for ( size_t i = 0u; i < inputs.size(); ++i )
		{
			const std::string& line = inputs[ i ];
			if ( line.empty() )
			{
				set_sum();
			}
			else
			{
				data.sum += static_cast< uint32_t >( atoi( line.c_str() ) );
			}
		}
		set_sum();

		std::sort( data.calories_per_elf.begin(), data.calories_per_elf.end(), [] ( const auto& left, const auto& right )
			{
				return left.second > right.second;
			}
		);
	}

	void display_result( data& data )
	{
		std::cout << "Verification:" << std::endl;
		std::cout << "Number of elves: " << data.elf_id << std::endl;
		for ( auto val : data.calories_per_elf )
		{
			std::cout << "[" << val.first << "]" << val.second << std::endl;
		}
		std::cout << "Biggest calories are: " << data.biggest_calories << " by: " << data.biggestcalories_provider_elf_id << std::endl;

		auto sum_best_3 = data.calories_per_elf[ 0 ].second + data.calories_per_elf[ 1 ].second + data.calories_per_elf[ 2 ].second;
		std::cout << "The best 3 are: " << std::endl;
		std::cout << data.calories_per_elf[ 0 ].first << std::endl;
		std::cout << data.calories_per_elf[ 1 ].first << std::endl;
		std::cout << data.calories_per_elf[ 2 ].first << std::endl;
		std::cout << "for a total of " << sum_best_3 << std::endl;
	}
}

void day_1_run()
{
	day_1::data data;

	day_1::process( day_1::load_inputs(), data );
	day_1::display_result( data );
}